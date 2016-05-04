/*
 * ecmcEcSlave.h
 *
 *  Created on: Nov 30, 2015
 *      Author: anderssandstrom
 */

#ifndef ECMCECSLAVE_H_
#define ECMCECSLAVE_H_

#include "ecrt.h"
#include "stdio.h"
#include <string>

#include "ecmcDefinitions.h"
#include "ecmcEcEntry.h"
#include "ecmcEcSyncManager.h"
#include "ecmcError.h"
#include "ecmcErrorsList.h"

#define SIMULATION_ENTRIES 2

typedef struct
{
    uint16_t position; /**< Offset of the slave in the ring. */
    uint32_t vendor_id; /**< Vendor-ID stored on the slave. */
    uint32_t product_code; /**< Product-Code stored on the slave. */
    uint16_t alias; /**< The slaves alias if not equal to 0. */
} mcu_ec_slave_info_light;

class ecmcEcSlave : public ecmcError
{
public:
  ecmcEcSlave(
    ec_master_t *master, /**< EtherCAT master */
    uint16_t alias, /**< Slave alias. */
    uint16_t position, /**< Slave position. */
    uint32_t vendorId, /**< Expected vendor ID. */
    uint32_t productCode /**< Expected product code. */);
  ~ecmcEcSlave();
  int addSyncManager(ec_direction_t direction,uint8_t syncMangerIndex); //Step 3 Iterate if needed
  ecmcEcSyncManager *getSyncManager(int syncManagerIndex);
  int getSlaveInfo(mcu_ec_slave_info_light *info);
  int getEntryCount();
  int getEntryInfo(int entryIndex, ec_pdo_entry_info_t *info);
  ecmcEcEntry *getEntry(int entryIndex);
  int configPdos( ec_domain_t *domain); //Step 4  //For all entries in slave!!
  int checkConfigState(void);
  void setDomainBaseAdr(uint8_t * domainAdr);
  int updateInputProcessImage();
  int updateOutProcessImage();
  int getSlaveBusPosition();
  int addEntry(
      ec_direction_t direction,
      uint8_t        syncMangerIndex,
      uint16_t       pdoIndex,
      uint16_t       entryIndex,
      uint8_t        entrySubIndex,
      uint8_t        bits,
      std::string    id);
  int configDC(
      uint16_t assignActivate, /**< AssignActivate word. */
      uint32_t sync0Cycle, /**< SYNC0 cycle time [ns]. */
      int32_t sync0Shift, /**< SYNC0 shift time [ns]. */
      uint32_t sync1Ccycle, /**< SYNC1 cycle time [ns]. */
      int32_t sync1Shift /**< SYNC1 shift time [ns]. */);
  ecmcEcEntry *findEntry(std::string id);
  int findEntryIndex(std::string id);

private:
  void initVars();
  ecmcEcSyncManager *findSyncMan(uint8_t syncMangerIndex);
  int configSlave() ;
  ec_master_t *master_; /**< EtherCAT master */
  uint16_t alias_; /**< Slave alias. */
  uint16_t slavePosition_; /**< Slave position. */
  uint32_t vendorId_; /**< Expected vendor ID. */
  uint32_t productCode_; /**< Expected product code. */
  ec_slave_config_t *slaveConfig_;
  ecmcEcSyncManager *syncManagerArray_[EC_MAX_SYNC_MANAGERS];
  ec_pdo_entry_info_t slavePdoEntries_[EC_MAX_ENTRIES];
  ec_pdo_info_t slavePdos_[EC_MAX_PDOS];
  ec_sync_info_t slaveSyncs_[EC_MAX_SYNC_MANAGERS];
  ecmcEcEntry *entryList_[EC_MAX_ENTRIES];
  int entriesArrayIndex_;
  int pdosArrayIndex_;
  int syncManArrayIndex_;
  int syncManCounter_;
  void writePdoStruct();
  void writeSyncsStruct();
  void writeEntriesStruct();
  int pdosInSMCount_;
  ec_slave_config_state_t sOld_;
  bool simSlave_;  //used to simulate endswitches Consider make derived simulation class insteaed
  uint8_t simBuffer_[8*SIMULATION_ENTRIES]; //used to simulate endswitches
  ecmcEcEntry *simEntries_[SIMULATION_ENTRIES]; //used to simulate endswitches
};
#endif /* ECMCECSLAVE_H_ */
