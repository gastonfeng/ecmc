/*
 * ecmcPLC_libDs.h
 *
 *  Created on: Nov 19, 2018
 *      Author: anderssandstrom
 */

#ifndef ecmcPLC_libDs_H_
#define ecmcPLC_libDs_H_

#define CHECK_PLC_DATA_STORAGE_RETURN_IF_ERROR(dsIndex) {     \
  ds_errorCode=0;                                             \
  if(dsIndex>=ECMC_MAX_DATA_STORAGE_OBJECTS || dsIndex<=0){   \
    ds_errorCode=ERROR_PLC_DATA_STORAGE_INDEX_OUT_OF_RANGE;   \
    LOGERR("ERROR: Data Storage index out of range.\n");      \
    return (double)ERROR_PLC_DATA_STORAGE_INDEX_OUT_OF_RANGE;}\
    if(ecmcPLC::statDs_[dsIndex]==NULL){                      \
      ds_errorCode=ERROR_PLC_DATA_STORAGE_OBJECT_NULL;        \
      LOGERR("ERROR: Data Storage object NULL\n");            \
      return (double)ERROR_PLC_DATA_STORAGE_OBJECT_NULL;      \
    }                                                         \
  }                                                           \

#define CHECK_PLC_DATA_STORAGE_RETURN_ZERO_IF_ERROR(dsIndex) {\
  ds_errorCode=0;                                             \
  if(dsIndex>=ECMC_MAX_DATA_STORAGE_OBJECTS || dsIndex<=0){   \
    ds_errorCode=ERROR_PLC_DATA_STORAGE_INDEX_OUT_OF_RANGE;   \
    LOGERR("ERROR: Data Storage index out of range.\n");      \
    return 0;}                                                \
    if(ecmcPLC::statDs_[dsIndex]==NULL){                      \
      ds_errorCode=ERROR_PLC_DATA_STORAGE_OBJECT_NULL;        \
      LOGERR("ERROR: Data Storage object NULL\n");            \
      return 0;                                               \
    }                                                         \
  }                                                           \

#define CHECK_PLC_DATA_STORAGE_RETURN_MINUS_ONE_IF_ERROR(dsIndex) {\
  ds_errorCode=0;                                             \
  if(dsIndex>=ECMC_MAX_DATA_STORAGE_OBJECTS || dsIndex<=0){   \
    ds_errorCode=ERROR_PLC_DATA_STORAGE_INDEX_OUT_OF_RANGE;   \
    LOGERR("ERROR: Data Storage index out of range.\n");      \
    return -1;}                                               \
    if(ecmcPLC::statDs_[dsIndex]==NULL){                      \
      ds_errorCode=ERROR_PLC_DATA_STORAGE_OBJECT_NULL;        \
      LOGERR("ERROR: Data Storage object NULL\n");            \
      return -1;                                              \
    }                                                         \
  }                                                           \

const char* dsLibCmdList[] = { "ds_append_data(",
                               "ds_clear_data(",
                               "ds_get_data(",
                               "ds_set_data(",
                               "ds_get_buff_id(",
                               "ds_set_buff_id(",
                               "ds_get_err(",
                               "ds_is_full(",
                               "ds_get_size(",                               
                              };

static int ds_errorCode=0;
static int ds_cmd_count=sizeof(dsLibCmdList)/sizeof(dsLibCmdList[0]);

inline double ds_append_data(double dsIndex,double data)
{
  int index=(int)dsIndex;
  CHECK_PLC_DATA_STORAGE_RETURN_IF_ERROR(index);  
  ds_errorCode=ecmcPLC::statDs_[index]->appendData(data);
  return (double) ds_errorCode;
}

inline double ds_clear_data(double dsIndex)
{
  int index=(int)dsIndex;
  CHECK_PLC_DATA_STORAGE_RETURN_IF_ERROR(index);  
  ds_errorCode=ecmcPLC::statDs_[index]->clearBuffer();
  return (double) ds_errorCode;
}

inline double ds_get_data(double dsIndex,double dataIndex)
{
  int index=(int)dsIndex;
  CHECK_PLC_DATA_STORAGE_RETURN_ZERO_IF_ERROR(index);  
  double temp=0;
  ds_errorCode=ecmcPLC::statDs_[index]->getDataElement(int(dataIndex),&temp);
  return temp;
}

inline double ds_set_data(double dsIndex,double dataIndex, double data)
{
  int index=(int)dsIndex;
  CHECK_PLC_DATA_STORAGE_RETURN_IF_ERROR(index);    
  ds_errorCode=ecmcPLC::statDs_[index]->setDataElement(int(dataIndex),data);
  return (double)ds_errorCode;
}

inline double ds_get_buff_id(double dsIndex)
{
  int index=(int)dsIndex;
  CHECK_PLC_DATA_STORAGE_RETURN_MINUS_ONE_IF_ERROR(index);    
  return ecmcPLC::statDs_[index]->getCurrentIndex();
}

inline double ds_set_buff_id(double dsIndex, double bufferIndex)
{
  int index=(int)dsIndex;
  CHECK_PLC_DATA_STORAGE_RETURN_IF_ERROR(index);
  ds_errorCode=ecmcPLC::statDs_[index]->setCurrentPosition(bufferIndex);
  return (double) ds_errorCode;
}

inline double ds_get_err()
{  
  return (double)ds_errorCode;
}

inline double ds_is_full(double dsIndex)
{
  int index=(int)dsIndex;
  CHECK_PLC_DATA_STORAGE_RETURN_MINUS_ONE_IF_ERROR(index);    
  ds_errorCode=0;
  return (double)ecmcPLC::statDs_[index]->isStorageFull();
}

inline double ds_get_size(double dsIndex)
{
  int index=(int)dsIndex;
  CHECK_PLC_DATA_STORAGE_RETURN_MINUS_ONE_IF_ERROR(index);    
  ds_errorCode=0;
  return (double)ecmcPLC::statDs_[index]->getSize();
}

#endif /* ecmcPLC_libDs_H_ */

