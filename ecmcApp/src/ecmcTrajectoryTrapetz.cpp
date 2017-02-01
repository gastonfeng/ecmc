#include "ecmcTrajectoryTrapetz.hpp"

#include <stdio.h>

ecmcTrajectoryTrapetz::ecmcTrajectoryTrapetz(ecmcAxisData *axisData,double sampleTime) : ecmcError()
{
  initVars();
  data_=axisData;
  sampleTime_=sampleTime;
  initTraj();
}

ecmcTrajectoryTrapetz::ecmcTrajectoryTrapetz(ecmcAxisData *axisData,double velocityTarget, double acceleration, double deceleration, double jerk,double sampleTime) : ecmcError()
{
  initVars();
  data_=axisData;
  velocityTarget_=velocityTarget;
  acceleration_=acceleration;
  deceleration_=deceleration;
  decelerationEmergency_=deceleration;
  jerk_=jerk;
  sampleTime_=sampleTime;
  initTraj();
}

ecmcTrajectoryTrapetz::~ecmcTrajectoryTrapetz()
{

}

void ecmcTrajectoryTrapetz::initVars()
{
  errorReset();
  distToStop_=0;
  velocityTarget_=0;
  acceleration_=0;
  deceleration_=0;
  decelerationEmergency_=0;
  jerk_=0;
  sampleTime_=1;
  posSetMinus1_=0;
  posSetMinus2_=0;
  targetPosition_=0;
  currentPositionSetpoint_=0;
  stepACC_=0;
  stepDEC_=0;
  stepNOM_=0;
  stepDECEmerg_=0;
  velocity_=0;
  trajInProgress_=false;
  index_=0;
  execute_=0;
  executeOld_=0;
  currentPosInterlock_=true;
  startPosition_=0;
  enable_=false;
  enableOld_=false;
  motionMode_=ECMC_MOVE_MODE_POS;
  prevStepSize_=0;
  setDirection_=ECMC_DIR_FORWARD;
  actDirection_=ECMC_DIR_FORWARD;
  stopping_=false;
  latchedStopMode_=ECMC_STOP_MODE_RUN;
}

void ecmcTrajectoryTrapetz::initTraj()
{
  stepNOM_=std::abs(velocityTarget_)*sampleTime_;
  stepACC_=0.5*acceleration_*sampleTime_*sampleTime_*2; //WHY*2?????
  stepDEC_=0.5*deceleration_*sampleTime_*sampleTime_*2;
  stepDECEmerg_=0.5*decelerationEmergency_*sampleTime_*sampleTime_*2;
}

double ecmcTrajectoryTrapetz::getCurrentPosSet()
{
  return currentPositionSetpoint_;
}

void ecmcTrajectoryTrapetz::setCurrentPosSet(double posSet)
{
  currentPositionSetpoint_=posSet;
  posSetMinus2_=currentPositionSetpoint_;
  posSetMinus1_=currentPositionSetpoint_;
  prevStepSize_=0;
  velocity_=0;
  setDirection_=ECMC_DIR_STANDSTILL;
  actDirection_=ECMC_DIR_STANDSTILL;
}

double ecmcTrajectoryTrapetz::getNextPosSet()
{
  //"Main" of trajectory generator. Needs to be called exactly once per cycle. Updates trajectory setpoint

  double nextSetpoint=currentPositionSetpoint_;
  double nextVelocity=velocity_;

  bool stopped=false;

  if (!trajInProgress_ || !enable_){

    if(execute_ && !enable_){
      setErrorID(__FILE__,__FUNCTION__,__LINE__,ERROR_TRAJ_EXECUTE_BUT_NO_ENABLE);
    }
    posSetMinus2_=currentPositionSetpoint_;
    posSetMinus1_=currentPositionSetpoint_;
    prevStepSize_=0;
    velocity_=0;
    setDirection_=ECMC_DIR_STANDSTILL;
    actDirection_=ECMC_DIR_STANDSTILL;
    stopping_=false;
    return currentPositionSetpoint_;
  }
  index_++;

  if(!execute_){
    data_->interlocks_.noExecuteInterlock=true;
    data_->refreshInterlocks();
    stopping_=true;
  }

   if(!data_->interlocks_.trajSummaryInterlock && !stopping_){
    nextSetpoint=internalTraj(&nextVelocity);
    actDirection_=checkDirection(currentPositionSetpoint_,nextSetpoint);
  }
  else{
    if(!stopping_){
      stopping_=true;
      latchedStopMode_=data_->interlocks_.currStopMode;
    }

    nextSetpoint=moveStop(latchedStopMode_,currentPositionSetpoint_, velocity_,velocityTarget_,&stopped,&nextVelocity);

    if(stopped){
      stopping_=false;
      latchedStopMode_=ECMC_STOP_MODE_RUN;
      trajInProgress_=false;
      nextVelocity=0;
    }
  }

  currentPositionSetpoint_=updateSetpoint(nextSetpoint,nextVelocity);

  return currentPositionSetpoint_;
}

double ecmcTrajectoryTrapetz::updateSetpoint(double nextSetpoint,double nextVelocity)
{
  posSetMinus2_=posSetMinus1_;
  posSetMinus1_=currentPositionSetpoint_;
  currentPositionSetpoint_=nextSetpoint;
  prevStepSize_=currentPositionSetpoint_-posSetMinus1_;
  velocity_=nextVelocity;
  distToStop_=distToStop(velocity_);
  return currentPositionSetpoint_;
}

double ecmcTrajectoryTrapetz::internalTraj(double *actVelocity)
{
  double posSetTemp=currentPositionSetpoint_;
  switch(motionMode_){
    case ECMC_MOVE_MODE_POS:
      posSetTemp=movePos(currentPositionSetpoint_,targetPosition_,distToStop_,velocity_,velocityTarget_,&trajInProgress_);
      break;
    case ECMC_MOVE_MODE_VEL:
      posSetTemp=moveVel(currentPositionSetpoint_, velocity_,velocityTarget_,&trajInProgress_);
      break;
  }
  *actVelocity=0;
  if(trajInProgress_){
    *actVelocity=(posSetTemp-currentPositionSetpoint_)/sampleTime_;
  }
  return posSetTemp;
}

double ecmcTrajectoryTrapetz::moveVel(double currSetpoint, double currVelo,double targetVelo,bool *trajBusy)
{
  double positionStep=0;
  double posSetTemp=0;
  *trajBusy=true;

  if(std::abs(currVelo)<std::abs(targetVelo)){
    positionStep=std::abs(prevStepSize_)+stepACC_;
  }
  else{
    positionStep=stepNOM_;
  }

  if(setDirection_==ECMC_DIR_FORWARD){
    posSetTemp=currSetpoint+positionStep;
  }
  else{
    posSetTemp=currSetpoint-positionStep;
  }
  return posSetTemp;
}

double ecmcTrajectoryTrapetz::movePos(double currSetpoint,double targetSetpoint,double stopDistance, double currVelo,double targetVelo, bool *trajBusy)
{
  double positionStep=0;
  double posSetTemp=0;
  bool timeToStop=false;
  bool changeDir=false;
  *trajBusy=true;
  changeDir=((targetSetpoint-currSetpoint)*currVelo<0 && std::abs(currVelo))>0;
  timeToStop=stopDistance > std::abs(targetSetpoint-currSetpoint) || changeDir;

  if(!timeToStop){
    if(std::abs(currVelo)<std::abs(targetVelo)){
      positionStep=std::abs(prevStepSize_)+stepACC_;
    }
    else{
      positionStep=stepNOM_;
    }
  }
  else{
    positionStep=std::abs(prevStepSize_)-stepDEC_;
  }

  if (setDirection_==ECMC_DIR_FORWARD){
    if(currVelo>=0){
      posSetTemp=currSetpoint+positionStep;
    }
    else{
      posSetTemp=currSetpoint-positionStep;
    }
    if(posSetTemp>=targetSetpoint){
      posSetTemp=targetSetpoint;
      *trajBusy=false;
    }
  }
  else{//Negative
    if (currVelo<=0){
      posSetTemp=currSetpoint-positionStep;
    }
    else{
      posSetTemp=currSetpoint+positionStep;
    }

    if(posSetTemp<=targetSetpoint){
      posSetTemp=targetSetpoint;
      *trajBusy=false;
    }
  }
  return posSetTemp;
}


double ecmcTrajectoryTrapetz::moveStop(stopMode stopMode,double currSetpoint, double currVelo,double targetVelo, bool *stopped,double *velocity)
{
  double positionStep;
  double posSetTemp=0;
  *stopped=false;
  motionDirection nDir=ECMC_DIR_STANDSTILL;
  if(currVelo>0){
    nDir=ECMC_DIR_FORWARD;
  }
  else
    if(currVelo<0){
      nDir=ECMC_DIR_BACKWARD;
    }

  if(stopMode==ECMC_STOP_MODE_EMERGENCY){
    positionStep=std::abs(prevStepSize_)-stepDECEmerg_;
  }
  else{
    positionStep=std::abs(prevStepSize_)-stepDEC_;
  }

  if(nDir==ECMC_DIR_FORWARD){
    posSetTemp=currSetpoint+positionStep;
  }
  else if(nDir==ECMC_DIR_BACKWARD){
    posSetTemp=currSetpoint-positionStep;
  }

  *velocity=(posSetTemp-currSetpoint)/sampleTime_;

  if(nDir==ECMC_DIR_STANDSTILL || (nDir==ECMC_DIR_FORWARD && positionStep<=0) || (nDir==ECMC_DIR_BACKWARD && positionStep>=0)){
    *stopped=true;
    *velocity=0;
    return currSetpoint;
  }

  return posSetTemp;
}

double ecmcTrajectoryTrapetz::distToStop(double vel)
{
  return std::abs(0.5*vel*vel/deceleration_)+2*std::abs(vel*sampleTime_)-2*stepDEC_;;
}

void ecmcTrajectoryTrapetz::setTargetPos(double pos)
{
  targetPosition_=pos;
  index_=0;
}

bool ecmcTrajectoryTrapetz::getBusy()
{
  return trajInProgress_;
}

int ecmcTrajectoryTrapetz::getIndex()
{
  return index_;
}

double ecmcTrajectoryTrapetz::getVel()
{
  double absVelTarget=std::abs(velocityTarget_);
  if(velocity_>=absVelTarget && setDirection_==ECMC_DIR_FORWARD){
    return absVelTarget;
  }
  if(velocity_<=-absVelTarget && setDirection_==ECMC_DIR_BACKWARD){
    return -absVelTarget;
  }

  return velocity_;
}

void ecmcTrajectoryTrapetz::setTargetVel(double velTarget)
{
  velocityTarget_=velTarget;
  initTraj();
}

double ecmcTrajectoryTrapetz::getTargetVel()
{
  return velocityTarget_;
}

void ecmcTrajectoryTrapetz::setAcc(double acc)
{
  acceleration_=acc;
  initTraj();
}

void ecmcTrajectoryTrapetz::setEmergDec(double dec)
{
  decelerationEmergency_=dec;
  initTraj();
}

void ecmcTrajectoryTrapetz::setDec(double dec)
{
  deceleration_=dec;
  if(decelerationEmergency_==0){
    decelerationEmergency_=deceleration_*3;
  }
  initTraj();
}

void ecmcTrajectoryTrapetz::setJerk(double jerk)  //Not used
{
  jerk_=jerk;
  initTraj();
}

double ecmcTrajectoryTrapetz::getAcc()
{
  return acceleration_;
}

double ecmcTrajectoryTrapetz::getDec()
{
  return deceleration_;
}

double ecmcTrajectoryTrapetz::getJerk()
{
  return jerk_; //Not used
}

double ecmcTrajectoryTrapetz::getTargetPos()
{
  return targetPosition_;
}

bool ecmcTrajectoryTrapetz::getExecute()
{
  return execute_;
}

void ecmcTrajectoryTrapetz::setEnable(bool enable)
{
  enableOld_=enable_;
  enable_=enable;
  velocity_=0;
  if(!enableOld_ && enable_ ){
    posSetMinus2_=startPosition_;
    posSetMinus1_=startPosition_;
    currentPositionSetpoint_=startPosition_;
    prevStepSize_=0;
    velocity_=0;
    distToStop_=0;
  }
}

bool ecmcTrajectoryTrapetz::getEnable()
{
  return enable_;
}

void ecmcTrajectoryTrapetz::setExecute(bool execute)
{
  LOGINFO6("%s/%s:%d: INFO: setExecute=%d.\n",__FILE__, __FUNCTION__, __LINE__,execute);
  executeOld_=execute_;
  execute_=execute;
  if(!enable_ && execute_){
    LOGERR("%s/%s:%d: ERROR: Trajectory not enabled (0x%x).\n",__FILE__, __FUNCTION__, __LINE__,ERROR_TRAJ_NOT_ENABLED);
    setErrorID(__FILE__,__FUNCTION__,__LINE__,ERROR_TRAJ_NOT_ENABLED);
    execute_=false;
    velocity_=0;
    return;
  }

  if(!executeOld_ && execute_){
    currentPositionSetpoint_=startPosition_;
    switch(motionMode_){
      case ECMC_MOVE_MODE_VEL:
        if(velocityTarget_<0){
          setDirection_=ECMC_DIR_BACKWARD;
        }
        else{
          setDirection_=ECMC_DIR_FORWARD;
        }
        break;
      case ECMC_MOVE_MODE_POS:
        if(targetPosition_<currentPositionSetpoint_){
          setDirection_=ECMC_DIR_BACKWARD;
        }
        else{
          setDirection_=ECMC_DIR_FORWARD;
        }
        break;
    }
    if(!trajInProgress_){
      posSetMinus1_=currentPositionSetpoint_;
      posSetMinus2_=currentPositionSetpoint_;
      velocity_=0;
    }
    initTraj();
    currentPositionSetpoint_=startPosition_;
    trajInProgress_=true; //Trigger new trajectory

    data_->interlocks_.noExecuteInterlock=false;
    data_->refreshInterlocks();

    LOGINFO7("%s/%s:%d: INFO: New trajectory triggered.\n",__FILE__, __FUNCTION__, __LINE__);
  }
}

void ecmcTrajectoryTrapetz::setStartPos(double pos)
{
  startPosition_=pos;
  currentPosInterlock_=false;
}

void  ecmcTrajectoryTrapetz::setMotionMode(motionMode mode)
{
  motionMode_=mode;
}

interlockTypes ecmcTrajectoryTrapetz::getInterlockStatus()
{
  return interlockStatus_;
}

double ecmcTrajectoryTrapetz::getSampleTime()
{
  return sampleTime_;
}

int ecmcTrajectoryTrapetz::validate()
{
  if(sampleTime_<=0){
    return setErrorID(__FILE__,__FUNCTION__,__LINE__,ERROR_TRAJ_INVALID_SAMPLE_TIME);
  }
  return 0;
}

motionDirection ecmcTrajectoryTrapetz::checkDirection(double oldPos,double newPos)
{
  if(newPos>oldPos){
    return ECMC_DIR_FORWARD;
  }
  else if(newPos<oldPos){
    return ECMC_DIR_BACKWARD;
  }

  return ECMC_DIR_STANDSTILL;
}

int ecmcTrajectoryTrapetz::initStopRamp(double currentPos, double currentVel, double currentAcc)
{
  enable_=1;
  trajInProgress_=true;
  currentPositionSetpoint_=currentPos;
  velocity_=currentVel;
  return 0;
}