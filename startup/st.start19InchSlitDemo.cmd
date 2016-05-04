require asyn
require streamdevice
require motor,6.10.3-ESS
require ecmc,anderssandstrom


## Configure devices
drvAsynECMCPortConfigure("MC_CPU1", 0, 0, 0)
asynOctetSetOutputEos("MC_CPU1", -1, ";\n")
asynOctetSetInputEos("MC_CPU1", -1, ";\n")

#asynSetTraceMask("MC_CPU1", -1, 0xFF)
##asynSetTraceMask("MC_CPU1", -1, 0x48)
asynSetTraceMask("MC_CPU1", -1, 0x41)

asynSetTraceIOMask("MC_CPU1", -1, 2)
asynSetTraceIOMask("MC_CPU1", -1, 6)

asynSetTraceInfoMask("MC_CPU1", -1, 15)

#-----------------------
ecmcCreateController("MCU1", "MC_CPU1", "32", "200", "1000", "")

############################################################

ecmcConfigController "MCU1", "Cfg.SetEnableFuncCallDiag(0)"
ecmcConfigController "MCU1", "Cfg.EcSetMaster(0)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(0,0x2,0x03fa3052,2,0,0x1a00,0x6000,0x1,1,INPUT_0)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(0,0x2,0x03fa3052,2,0,0x1a01,0x6010,0x1,1,INPUT_1)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(0,0x2,0x03fa3052,2,0,0x1a02,0x6020,0x1,1,INPUT_2)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(0,0x2,0x03fa3052,2,0,0x1a03,0x6030,0x1,1,INPUT_3)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(0,0x2,0x03fa3052,2,0,0x1a04,0x6040,0x1,1,INPUT_4)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(0,0x2,0x03fa3052,2,0,0x1a05,0x6050,0x1,1,INPUT_5)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(0,0x2,0x03fa3052,2,0,0x1a06,0x6060,0x1,1,INPUT_6)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(0,0x2,0x03fa3052,2,0,0x1a07,0x6070,0x1,1,INPUT_7)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(1,0x2,0x0af83052,1,0,0x1600,0x7000,0x1,1,OUTPUT_0)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(1,0x2,0x0af83052,1,0,0x1601,0x7010,0x1,1,OUTPUT_1)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(1,0x2,0x0af83052,1,0,0x1602,0x7020,0x1,1,OUTPUT_2)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(1,0x2,0x0af83052,1,0,0x1603,0x7030,0x1,1,OUTPUT_3)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(1,0x2,0x0af83052,1,0,0x1604,0x7040,0x1,1,OUTPUT_4)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(1,0x2,0x0af83052,1,0,0x1605,0x7050,0x1,1,OUTPUT_5)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(1,0x2,0x0af83052,1,0,0x1606,0x7060,0x1,1,OUTPUT_6)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(1,0x2,0x0af83052,1,0,0x1607,0x7070,0x1,1,OUTPUT_7)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(2,0x2,0x13ed3052,1,2,0x1600,0x7000,0x01,8,CONTROL)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(2,0x2,0x13ed3052,1,2,0x1600,0x7000,0x02,16,VALUE)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(2,0x2,0x13ed3052,2,3,0x1a03,0x6010,0x00,16,STATUS)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(2,0x2,0x13ed3052,2,3,0x1a03,0x6010,0x10,16,POSITION)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(2,0x2,0x13ed3052,2,3,0x1a03,0x6010,0x20,16,LATCH_POSITION)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(3,0x2,0x13ed3052,1,2,0x1600,0x7000,0x01,8,CONTROL)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(3,0x2,0x13ed3052,1,2,0x1600,0x7000,0x02,16,VALUE)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(3,0x2,0x13ed3052,2,3,0x1a03,0x6010,0x00,16,STATUS)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(3,0x2,0x13ed3052,2,3,0x1a03,0x6010,0x10,16,POSITION)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(3,0x2,0x13ed3052,2,3,0x1a03,0x6010,0x20,16,LATCH_POSITION)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(7,0x2,0x1b7d3052,1,2,0x1602,0x7010,0x1,16,ENABLE)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(7,0x2,0x1b7d3052,1,2,0x1604,0x7010,0x21,16,VELOCITY_SETPOINT)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(7,0x2,0x1b7d3052,2,3,0x1a00,0x6000,0x0,16,STATUS)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(7,0x2,0x1b7d3052,2,3,0x1a00,0x6000,0x11,16,POSITION)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(7,0x2,0x1b7d3052,2,3,0x1a00,0x6000,0x12,16,LATCH_POSITION)"
ecmcConfigController "MCU1", "Cfg.EcAddSdo(7,0x8010,0x1,1000,2)"
ecmcConfigController "MCU1", "Cfg.EcAddSdo(7,0x8012,0x5,1,1)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(8,0x2,0x1b7d3052,1,2,0x1602,0x7010,0x1,16,ENABLE)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(8,0x2,0x1b7d3052,1,2,0x1604,0x7010,0x21,16,VELOCITY_SETPOINT)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(8,0x2,0x1b7d3052,2,3,0x1a00,0x6000,0x0,16,STATUS)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(8,0x2,0x1b7d3052,2,3,0x1a00,0x6000,0x11,16,POSITION)"
ecmcConfigController "MCU1", "Cfg.EcAddEntryComplete(8,0x2,0x1b7d3052,2,3,0x1a00,0x6000,0x12,16,LATCH_POSITION)"
ecmcConfigController "MCU1", "Cfg.EcAddSdo(8,0x8010,0x1,1000,2)"
ecmcConfigController "MCU1", "Cfg.EcAddSdo(8,0x8012,0x5,1,1)"
ecmcConfigController "MCU1", "Cfg.EcApplyConfig(1)"
ecmcConfigController "MCU1", "WriteEcEntry(1,0,1)"
ecmcConfigController "MCU1", "WriteEcEntry(1,1,1)"
ecmcConfigController "MCU1", "WriteEcEntry(1,2,1)"
ecmcConfigController "MCU1", "WriteEcEntry(1,5,1)"
ecmcConfigController "MCU1", "WriteEcEntry(1,6,1)"
ecmcConfigController "MCU1", "WriteEcEntry(1,7,1)"
ecmcConfigController "MCU1", "Cfg.CreateAxis(1,2)"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajStartPos(1,0)"
ecmcConfigController "MCU1", "Main.M1.fAcceleration=20"
ecmcConfigController "MCU1", "Main.M1.fDeceleration=40"
ecmcConfigController "MCU1", "Cfg.SetAxisEmergDeceleration(1,1000)"
ecmcConfigController "MCU1", "Main.M1.fVelocity=20"
ecmcConfigController "MCU1", "Main.M1.nCommand=3"
ecmcConfigController "MCU1", "Cfg.SetAxisJogVel(1,100.0)"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5001,16#D,8,5=-10000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5001,16#E,8,5=10000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5001,16#B,2,2=0"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5001,16#C,2,2=0"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(-1,ONE,1,0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(-1,ONE,1,1)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(-1,ONE,1,2)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTol(1,0.05)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTime(1,100)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableAtTargetMon(1,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTol(1,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTime(1,10)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableLagMon(1,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVel(1,1000)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableMaxVel(1,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVelTrajILDelay(1,200)"
ecmcConfigController "MCU1", "Cfg.CreateAxis(2,2)"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajStartPos(2,0)"
ecmcConfigController "MCU1", "Main.M2.fAcceleration=20"
ecmcConfigController "MCU1", "Main.M2.fDeceleration=40"
ecmcConfigController "MCU1", "Cfg.SetAxisEmergDeceleration(2,1000)"
ecmcConfigController "MCU1", "Main.M2.fVelocity=20"
ecmcConfigController "MCU1", "Main.M2.nCommand=3"
ecmcConfigController "MCU1", "Cfg.SetAxisJogVel(2,100.0)"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5002,16#D,8,5=-10000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5002,16#E,8,5=10000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5002,16#B,2,2=0"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5002,16#C,2,2=0"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(-1,ONE,2,0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(-1,ONE,2,1)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(-1,ONE,2,2)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTol(2,0.05)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTime(2,100)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableAtTargetMon(2,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTol(2,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTime(2,10)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableLagMon(2,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVel(2,1000)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableMaxVel(2,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVelTrajILDelay(2,200)"
ecmcConfigController "MCU1", "Cfg.CreateDefaultAxis(3)"
ecmcConfigController "MCU1", "Main.M3.fAcceleration=20"
ecmcConfigController "MCU1", "Main.M3.fDeceleration=20"
ecmcConfigController "MCU1", "Cfg.SetAxisEmergDeceleration(3,200)"
ecmcConfigController "MCU1", "Main.M3.fVelocity=5"
ecmcConfigController "MCU1", "Main.M3.nCommand=3"
ecmcConfigController "MCU1", "Cfg.SetAxisJogVel(3,100.0)"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5003,16#D,8,5=-5000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5003,16#E,8,5=5000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5003,16#B,2,2=0"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5003,16#C,2,2=0"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#4003,16#6,8,5=10"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#4003,16#7,8,5=5"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlKp(3,15.0)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlKi(3,0.02)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlKd(3,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlKff(3,26.3)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlOutHL(3,8000.0)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlOutLL(3,-8000.0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisEncoder(2,POSITION,3,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncScaleDenom(3,2000)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncScaleNum(3,60)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncType(3,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncBits(3,16)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisDrive(7,ENABLE,3,0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisDrive(7,VELOCITY_SETPOINT,3,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisDrvScaleDenom(3,32768.0)"
ecmcConfigController "MCU1", "Cfg.SetAxisDrvScaleNum(3,-16000.0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(0,INPUT_1,3,0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(0,INPUT_3,3,1)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(0,INPUT_2,3,2)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTol(3,0.1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTime(3,100)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableAtTargetMon(3,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTol(3,0.5)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTime(3,10)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableLagMon(3,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVel(3,100)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableMaxVel(3,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVelDriveILDelay(3,100)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVelTrajILDelay(3,200)"
ecmcConfigController "MCU1", "Cfg.CreateDefaultAxis(4)"
ecmcConfigController "MCU1", "Main.M4.fAcceleration=20"
ecmcConfigController "MCU1", "Main.M4.fDeceleration=20"
ecmcConfigController "MCU1", "Cfg.SetAxisEmergDeceleration(4,200)"
ecmcConfigController "MCU1", "Main.M4.fVelocity=5"
ecmcConfigController "MCU1", "Main.M4.nCommand=3"
ecmcConfigController "MCU1", "Cfg.SetAxisJogVel(4,100.0)"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5004,16#D,8,5=-5000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5004,16#E,8,5=5000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5004,16#B,2,2=0"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5004,16#C,2,2=0"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#4004,16#6,8,5=10"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#4004,16#7,8,5=5"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlKp(4,15.0)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlKi(4,0.02)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlKd(4,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlKff(4,26.3)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlOutHL(4,8000.0)"
ecmcConfigController "MCU1", "Cfg.SetAxisCntrlOutLL(4,-8000.0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisEncoder(3,POSITION,4,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncScaleDenom(4,-2000)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncScaleNum(4,60)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncType(4,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncBits(4,16)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisDrive(8,ENABLE,4,0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisDrive(8,VELOCITY_SETPOINT,4,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisDrvScaleDenom(4,32768.0)"
ecmcConfigController "MCU1", "Cfg.SetAxisDrvScaleNum(4,16000.0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(0,INPUT_0,4,0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(0,INPUT_4,4,1)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(0,INPUT_5,4,2)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTol(4,0.1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTime(4,100)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableAtTargetMon(4,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTol(4,0.5)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTime(4,10)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableLagMon(4,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVel(4,100)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableMaxVel(4,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVelDriveILDelay(4,100)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVelTrajILDelay(4,200)"
ecmcConfigController "MCU1", "Cfg.CreateAxis(5,2)"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajStartPos(5,0)"
ecmcConfigController "MCU1", "Main.M5.fAcceleration=20"
ecmcConfigController "MCU1", "Main.M5.fDeceleration=40"
ecmcConfigController "MCU1", "Cfg.SetAxisEmergDeceleration(5,1000)"
ecmcConfigController "MCU1", "Main.M5.fVelocity=200"
ecmcConfigController "MCU1", "Main.M5.nCommand=1"
ecmcConfigController "MCU1", "Cfg.SetAxisJogVel(5,100.0)"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5005,16#D,8,5=-10000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5005,16#E,8,5=10000"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5005,16#B,2,2=0"
ecmcConfigController "MCU1", "ADSPORT=501/.ADR.16#5005,16#C,2,2=0"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(-1,ONE,5,0)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(-1,ONE,5,1)"
ecmcConfigController "MCU1", "Cfg.LinkEcEntryToAxisMonitor(-1,ONE,5,2)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTol(5,0.05)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonAtTargetTime(5,100)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableAtTargetMon(5,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTol(5,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonPosLagTime(5,10)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableLagMon(5,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVel(5,1000)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonEnableMaxVel(5,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisMonMaxVelTrajILDelay(5,200)"
ecmcConfigController "MCU1", "Main.M1.nCommand=3"
ecmcConfigController "MCU1", "Main.M2.nCommand=3"
ecmcConfigController "MCU1", "Main.M3.nCommand=3"
ecmcConfigController "MCU1", "Main.M4.nCommand=3"
ecmcConfigController "MCU1", "Cfg.SetAxisEncTransExpr(1)=out:=(enc3+22+enc4-20)/2#ilock:=1#"
ecmcConfigController "MCU1", "Cfg.SetAxisEncSourceType(1,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncTransExpr(2)=out:=(enc3+22)-(enc4-20)#ilock:=1#"
ecmcConfigController "MCU1", "Cfg.SetAxisEncSourceType(2,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajTransExpr(3)=out:=traj1+traj2/2-22#ilock:=1#"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajSourceType(3,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajTransExpr(4)=out:=traj1-traj2/2+20#ilock:=1#"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajSourceType(4,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajTransExpr(1)=out:=10*sin(traj5/100)#ilock:=1#"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajSourceType(1,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajTransExpr(2)=out:=10*sin(traj5/100)#ilock:=1#"
ecmcConfigController "MCU1", "Cfg.SetAxisTrajSourceType(2,0)"
ecmcConfigController "MCU1", "Cfg.SetAxisEncTransExpr(5)=out:=traj5#ilock:=1#"
ecmcConfigController "MCU1", "Cfg.SetAxisEncSourceType(5,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisEnableCommandsFromOtherAxis(3,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisEnableCommandsFromOtherAxis(4,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisEnableCommandsFromOtherAxis(1,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisEnableCommandsFromOtherAxis(2,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisEnableCommandsTransform(1,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisTransformCommandExpr(1)=ex3:=ex1+ex2#ex4:=ex1+ex2#en3:=en1+en2#en4:=en1+en2#"
ecmcConfigController "MCU1", "Cfg.SetAxisEnableCommandsTransform(2,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisTransformCommandExpr(2)=ex3:=ex1+ex2#ex4:=ex1+ex2#en3:=en1+en2#en4:=en1+en2#"
ecmcConfigController "MCU1", "Cfg.SetAxisEnableCommandsTransform(5,1)"
ecmcConfigController "MCU1", "Cfg.SetAxisTransformCommandExpr(5)=ex1:=ex5#ex2:=ex5#en1:=en5#en2:=en5#"
ecmcConfigController "MCU1", "Cfg.EcSetDiagnostics(0)"
ecmcConfigController "MCU1", "Cfg.SetDiagAxisIndex(1)"
ecmcConfigController "MCU1", "Cfg.SetDiagAxisFreq(1)"
ecmcConfigController "MCU1", "Cfg.SetDiagAxisEnable(0)"


#Go to runtime
ecmcConfigController "MCU1", "Cfg.SetAppMode(1)"


#############################################################

#Parameter 3 ecmcCreateAxis
#define AMPLIFIER_ON_FLAG_CREATE_AXIS  (1)
#define AMPLIFIER_ON_FLAG_WHEN_HOMING  (1<<1)
#define AMPLIFIER_ON_FLAG_USING_CNEN   (1<<2)

ecmcCreateAxis("MCU1", "1", "6", "")
ecmcCreateAxis("MCU1", "2", "6", "")
ecmcCreateAxis("MCU1", "3", "6", "")
ecmcCreateAxis("MCU1", "4", "6", "")

#ecmcCreateAxis("MCU1", "1", "6", "cfgFile=SlitX-xp.cfg")
#ecmcCreateAxis("MCU1", "2", "6", "cfgFile=SlitX-xg.cfg")
#ecmcCreateAxis("MCU1", "3", "6", "cfgFile=SlitX-xl.cfg")
#ecmcCreateAxis("MCU1", "4", "6", "cfgFile=SlitX-xr.cfg")


dbLoadTemplate("SlitX-xp.substitutions")
dbLoadTemplate("SlitX-xp-extra.substitutions")
dbLoadTemplate("SlitX-xg.substitutions")
dbLoadTemplate("SlitX-xg-extra.substitutions")
dbLoadTemplate("SlitX-xl.substitutions")
dbLoadTemplate("SlitX-xl-extra.substitutions")
dbLoadTemplate("SlitX-xr.substitutions")
dbLoadTemplate("SlitX-xr-extra.substitutions")



#Stream device

dbLoadTemplate("andersTest.substitutions")
#var streamDebug 1

