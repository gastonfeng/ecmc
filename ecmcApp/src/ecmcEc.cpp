/*
 * ecmcEc.cpp
 *
 *  Created on: Dec 1, 2015
 *      Author: anderssandstrom
 */

#include "ecmcEc.h"

ecmcEc::ecmcEc()
{
  initVars();
  simSlave_=new ecmcEcSlave(NULL,0,0,0,0);
}

void ecmcEc::initVars()
{
  errorReset();
  slaveCounter_=0;
  initDone_=false;
  diag_=true;
  sdoCounter_=0;
  simSlave_=NULL;
  master_=NULL;
  domain_=NULL;
  dsOld_.redundancy_active=0;
  dsOld_.wc_state=EC_WC_ZERO;
  dsOld_.working_counter=0;
  msOld_.slaves_responding=0;
  msOld_.link_up=0;
  msOld_.al_states=0;
  domainPd_=0;

  for(int i=1; i < EC_MAX_SLAVES; i++){
    slaveArray_[i]=NULL;
  }
  for(int i=0; i < EC_MAX_ENTRIES; i++){
    sdoArray_[i]=NULL;
    pdoByteOffsetArray_[i]=0;
    pdoBitOffsetArray_[i]=0;
    slaveEntriesReg_[i].alias=0;
    slaveEntriesReg_[i].bit_position=0;
    slaveEntriesReg_[i].index=0;
    slaveEntriesReg_[i].offset=0;
    slaveEntriesReg_[i].position=0;
    slaveEntriesReg_[i].product_code=0;
    slaveEntriesReg_[i].subindex=0;
    slaveEntriesReg_[i].vendor_id=0;
  }
}

int ecmcEc::init(int nMasterIndex)
{
  master_ = ecrt_request_master(nMasterIndex);

  if (!master_){
    return setErrorID(ERROR_EC_MAIN_REQUEST_FAILED);
  }

  domain_ = ecrt_master_create_domain(master_);
  if (!domain_){
    return setErrorID(ERROR_EC_MAIN_CREATE_DOMAIN_FAILED);
  }
  initDone_=true;
  return 0;
}

ecmcEc::~ecmcEc()
{
  printf("INFO:\t\tDeleting Ec\n");
  for(int i=0; i < slaveCounter_; i++){
    delete slaveArray_[i];
    slaveArray_[i]=NULL;
  }

  for(int i=0; i < sdoCounter_; i++){
    delete sdoArray_[i];
    sdoArray_[i]=NULL;
  }

  if(simSlave_!=NULL){
    delete simSlave_;
    simSlave_=NULL;
  }
}

bool ecmcEc::getInitDone()
{
  return initDone_;
}

ec_domain_t *ecmcEc::getDomain()
{
  return domain_;
}

ec_master_t *ecmcEc::getMaster()
{
  return master_;
}

//Step 1
int ecmcEc::addSlave(
  uint16_t alias, /**< Slave alias. */
  uint16_t position, /**< Slave position. */
  uint32_t vendorId, /**< Expected vendor ID. */
  uint32_t productCode /**< Expected product code. */)
{

  if(slaveCounter_<EC_MAX_SLAVES-1){
    slaveArray_[slaveCounter_]=new ecmcEcSlave(master_,alias,position,vendorId,productCode);
    slaveCounter_++;
    return slaveCounter_-1;
  }
  else
    return setErrorID(ERROR_EC_MAIN_SLAVE_ARRAY_FULL);
}

ecmcEcSlave *ecmcEc::getSlave(int slaveIndex)
{
  if(slaveIndex>=EC_MAX_SLAVES || slaveIndex<-1 || slaveIndex>=slaveCounter_){
    setErrorID(ERROR_EC_MAIN_INVALID_SLAVE_INDEX);
    return NULL;
  }

  if(slaveIndex==-1){
    return simSlave_;
  }

  if(slaveArray_[slaveIndex]==NULL){
    setErrorID(ERROR_EC_MAIN_INVALID_SLAVE_INDEX);
    return NULL;
  }

  return slaveArray_[slaveIndex];
}

int ecmcEc::activate()
{
  printf("INFO:\t\tActivating master...\n");
  if (ecrt_master_activate(master_)){
    return setErrorID(ERROR_EC_MAIN_MASTER_ACTIVATE_FAILED);
  }

  if (!(domainPd_ = ecrt_domain_data(domain_))) {
    return setErrorID(ERROR_EC_MAIN_DOMAIN_DATA_FAILED);
  }

  mcu_ec_slave_info_light slaveinfo;
  printf("INFO:\t\tWriting process data offsets to entries!\n");
  for(int slaveIndex=0; slaveIndex<slaveCounter_;slaveIndex++){
    if(slaveArray_[slaveIndex]==NULL){
      printf("WARNING:\tActivate: Slave==NULL...\n");
      return setErrorID(ERROR_EC_MAIN_SLAVE_NULL);
    }
    if(slaveArray_[slaveIndex]->getSlaveInfo(&slaveinfo)){  //Get slave info
      return setErrorID(ERROR_EC_MAIN_GET_SLAVE_INFO_FAILED);
    }
    int nEntryCount=slaveArray_[slaveIndex]->getEntryCount();
    for(int entryIndex=0;entryIndex<nEntryCount;entryIndex++){
      ecmcEcEntry *tempEntry=slaveArray_[slaveIndex]->getEntry(entryIndex);
      if(tempEntry==NULL){
        printf("WARNING:\tActivate: Entry==NULL...\n");
        return setErrorID(ERROR_EC_MAIN_ENTRY_NULL);
      }
      tempEntry->setDomainAdr(domainPd_);
    }
  }
  return 0;
}

int ecmcEc::compileRegInfo()
{
  printf("INFO:\t\tEntering ecmcEc::compileRegInfo.\n");
  mcu_ec_slave_info_light slaveinfo;
  ec_pdo_entry_info_t entryinfo;
  int entryCounter=0;
  for(int slaveIndex=0; slaveIndex<slaveCounter_;slaveIndex++){
    if(slaveArray_[slaveIndex]==NULL){
      printf("WARNING:\tRegInfo: Slave==NULL...\n");
      return setErrorID(ERROR_EC_MAIN_SLAVE_NULL);
    }
    if(slaveArray_[slaveIndex]->getSlaveInfo(&slaveinfo)){  //Get slave info
      return setErrorID(ERROR_EC_MAIN_GET_SLAVE_INFO_FAILED);
    }
    slaveArray_[slaveIndex]->configPdos(domain_);
    int entryCountInSlave=slaveArray_[slaveIndex]->getEntryCount();
    for(int entryIndex=0;entryIndex<entryCountInSlave;entryIndex++){
      if(slaveArray_[slaveIndex]->getEntryInfo(entryIndex, &entryinfo)){ //Get entry info
        return setErrorID(ERROR_EC_MAIN_GET_ENTRY_INFO_FAILED);
      }
      slaveEntriesReg_[entryCounter].alias=slaveinfo.alias;
      slaveEntriesReg_[entryCounter].position=  slaveinfo.position;
      slaveEntriesReg_[entryCounter].vendor_id=slaveinfo.vendor_id;;
      slaveEntriesReg_[entryCounter].product_code=slaveinfo.product_code;;
      slaveEntriesReg_[entryCounter].index=entryinfo.index; //0x7000
      slaveEntriesReg_[entryCounter].subindex=entryinfo.subindex;//0x0
      slaveEntriesReg_[entryCounter].offset=&pdoByteOffsetArray_[entryCounter]; //Output byte address offset
      slaveEntriesReg_[entryCounter].bit_position=&pdoBitOffsetArray_[entryCounter]; //Output address bit offset
      entryCounter++;
    }
  }
  // slave_entries_reg filled
  printf("INFO:\t\tSlave reg entries structure filled:\n");
  for(int i=0;i<entryCounter;i++){
    printf("\t\t{%d\t%d\t%x\t%x\t%x\t%x}\n",slaveEntriesReg_[i].alias,slaveEntriesReg_[i].position,slaveEntriesReg_[i].vendor_id,slaveEntriesReg_[i].product_code,slaveEntriesReg_[i].index,slaveEntriesReg_[i].subindex/*,slave_entries_reg[i].offset*//*,slave_entries_reg[i].bit_position*/);
  }
  //Register to get offsets!
  if (ecrt_domain_reg_pdo_entry_list(domain_, slaveEntriesReg_)) {  //Now offsets are stored in slave_enties reg
    fprintf(stderr, "ERROR:\tRegistration of entry list failed!\n");
    return setErrorID(ERROR_EC_MAIN_DOM_REG_PDO_ENTRY_LIST_FAILED);
  }
  printf("INFO:\t\tWriting address offsets to entry objects\n");
  entryCounter=0;
  //Write offstes to entries
  for(int slaveIndex=0; slaveIndex<slaveCounter_;slaveIndex++){
    if(slaveArray_[slaveIndex]==NULL){
      printf("WARNING:\tWriting offsets to RegInfo: Slave==NULL...\n");
      return setErrorID(ERROR_EC_MAIN_SLAVE_NULL);
    }
    if(slaveArray_[slaveIndex]->getSlaveInfo(&slaveinfo)){  //Get slave info
      printf("WARNING:\tgetSlaveInfo failed...\n");
      return setErrorID(ERROR_EC_MAIN_GET_SLAVE_INFO_FAILED);
    }
    int entryCountInSlave=slaveArray_[slaveIndex]->getEntryCount();
    for(int entryIndex=0;entryIndex<entryCountInSlave;entryIndex++){
      ecmcEcEntry *tempEntry=slaveArray_[slaveIndex]->getEntry(entryIndex);
      if(tempEntry==NULL){
        printf("WARNING:\tRegInfo: Entry==NULL...\n");
        return setErrorID(ERROR_EC_MAIN_ENTRY_NULL);
      }
      tempEntry->setAdrOffsets(pdoByteOffsetArray_[entryCounter],pdoBitOffsetArray_[entryCounter]);
      entryCounter++;
    }
  }
  printf("INFO:\t\tLeaving ecmcEc::compileRegInfo. Entries registered: %d\n",entryCounter);
  return 0;
}

void ecmcEc::checkDomainState(void)
{
  if(diag_){
    ec_domain_state_t ds;
    ecrt_domain_state(domain_, &ds);
    if (ds.working_counter != dsOld_.working_counter)
      printf("INFO:\t\tDomain1: WC %u.\n", ds.working_counter);
    if (ds.wc_state != dsOld_.wc_state)
      printf("INFO:\t\tDomain1: State %u.\n", ds.wc_state);
    dsOld_=ds;
  }
}

bool ecmcEc::checkSlavesConfState()
{
  if(diag_){
    bool retVal=true;
    for(int i=0;i<slaveCounter_;i++){
      retVal=retVal && checkSlaveConfState(i)==0;
    }
    return retVal;
  }
  return true;
}

int ecmcEc::checkSlaveConfState(int slaveIndex)
{
  if(!diag_){
    return 0;
  }

  if(slaveIndex>=EC_MAX_SLAVES || slaveIndex >=slaveCounter_){
    return setErrorID(ERROR_EC_MAIN_INVALID_SLAVE_INDEX);
  }

  if(slaveArray_[slaveIndex]==NULL){
    return setErrorID(ERROR_EC_MAIN_SLAVE_NULL);
  }

  return slaveArray_[slaveIndex]->checkConfigState();
}

bool ecmcEc::checkState(void)
{
  if(!diag_){
    return true;
  }
  ec_master_state_t ms;
  ecrt_master_state(master_, &ms);

  if (ms.slaves_responding != msOld_.slaves_responding){
    printf("INFO:\t\t%u slave(s).\n", ms.slaves_responding);
  }
  if (ms.al_states != msOld_.al_states)
    printf("INFO:\t\tAL states: 0x%02X.\n", ms.al_states);

  if (ms.link_up != msOld_.link_up){
    printf("INFO:\t\tLink is %s.\n", ms.link_up ? "up" : "down");
  }
  msOld_ = ms;
  return ms.link_up;
}

void ecmcEc::receive()
{
  ecrt_master_receive(master_);
  ecrt_domain_process(domain_);
  updateInputProcessImage();
}

void ecmcEc::send()
{
  updateOutProcessImage();
  ecrt_domain_queue(domain_);
  ecrt_master_send(master_);
}

int ecmcEc::setDiagnostics(bool bDiag)
{
  diag_=bDiag;
  return 0;
}

int ecmcEc::addSDOWrite(uint16_t slavePosition,uint16_t sdoIndex,uint8_t sdoSubIndex,uint32_t writeValue, int byteSize)
{
  if(sdoCounter_>=EC_MAX_ENTRIES-1){
    return setErrorID(ERROR_EC_MAIN_SDO_ARRAY_FULL);
  }
  sdoArray_[sdoCounter_]=new ecmcEcSDO(master_,slavePosition,sdoIndex,sdoSubIndex,writeValue, byteSize);
  sdoCounter_++;
  return 0;
}

int ecmcEc::writeAndVerifySDOs()
{
  for(int i=0;i<sdoCounter_;i++){
    if(sdoArray_[i]==NULL){
      printf("ERROR:\t\t SDO entry==NULL.\n");
      return setErrorID(ERROR_EC_MAIN_SDO_ENTRY_NULL);
    }
    int iRet;
    if((iRet=sdoArray_[i]->writeAndVerify())){
      printf("ERROR:\tSDO write and verify failed. Index=%d.\n",i);
      return setErrorID(iRet);
    }
  }
  return 0;
}

int ecmcEc::writeSDO(uint16_t slavePosition,uint16_t sdoIndex,uint8_t sdoSubIndex,uint32_t value, int byteSize)
{
  ecmcEcSDO * sdo=new ecmcEcSDO(master_,slavePosition,sdoIndex,sdoSubIndex, byteSize);
  int nRet=sdo->write(value);
  delete sdo;
  return nRet;
}

uint32_t ecmcEc::readSDO(uint16_t slavePosition,uint16_t sdoIndex,uint8_t sdoSubIndex, int byteSize)
{
  ecmcEcSDO * sdo=new ecmcEcSDO(master_,slavePosition,sdoIndex,sdoSubIndex, byteSize);
  if(sdo->read()){
    printf("ERROR:\t\t SDO read failed\n");
    setErrorID(ERROR_EC_MAIN_SDO_READ_FAILED);
    delete sdo;
    return 0;
  }
  uint32_t nRet=sdo->getReadValue();
  delete sdo;
  return nRet;
}

int ecmcEc::updateInputProcessImage()
{
  for(int i=0;i<slaveCounter_;i++){
    if(slaveArray_[i]!=NULL){
      slaveArray_[i]->updateInputProcessImage();
    }
  }
  return 0;
}

int ecmcEc::updateOutProcessImage()
{
  for(int i=0;i<slaveCounter_;i++){
    if(slaveArray_[i]!=NULL){
      slaveArray_[i]->updateOutProcessImage();
    }
  }
  return 0;
}

int ecmcEc::addEntry(
    uint16_t       position, /**< Slave position. */
    uint32_t       vendorId, /**< Expected vendor ID. */
    uint32_t       productCode, /**< Expected product code. */
    ec_direction_t direction,
    uint8_t        syncMangerIndex,
    uint16_t       pdoIndex,
    uint16_t       entryIndex,
    uint8_t        entrySubIndex,
    uint8_t        bits,
    std::string    id
    )
{
  ecmcEcSlave *slave=findSlave(position);
  if(slave==NULL){
    int slaveIndex=addSlave(0,position,vendorId,productCode);
    slave=slaveArray_[slaveIndex]; //last added slave
  }
  slave->addEntry(direction,syncMangerIndex,pdoIndex,entryIndex,entrySubIndex,bits,id);

  return 0;
}

ecmcEcSlave *ecmcEc::findSlave(int busPosition)
{
  if(busPosition==-1){
     return simSlave_;
  }

  for(int i=0;i< slaveCounter_;i++){
    if(slaveArray_[i]!=NULL){
      if(slaveArray_[i]->getSlaveBusPosition()==busPosition){
        return slaveArray_[i];
      }
    }
  }
  return NULL;
}

int ecmcEc::findSlaveIndex(int busPosition,int *slaveIndex)
{
  if(busPosition==-1){
    *slaveIndex=busPosition;
    return 0;
  }

  for(int i=0;i< slaveCounter_;i++){
    if(slaveArray_[i]!=NULL){
      if(slaveArray_[i]->getSlaveBusPosition()==busPosition){
        *slaveIndex=i;
        return 0;
      }
    }
  }
  return setErrorID(ERROR_EC_MAIN_SLAVE_NULL);
}
