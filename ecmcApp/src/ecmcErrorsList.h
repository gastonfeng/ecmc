/*
 * ESSOSMCU-errors.h
 *
 *  Created on: Jan 29, 2016
 *      Author: anderssandstrom
 */

#ifndef ECMCERRORSLIST_H_
#define ECMCERRORSLIST_H_



//AXIS
#define ERROR_AXIS_OBJECTS_NULL_OR_EC_INIT_FAIL 0x14300
#define ERROR_AXIS_DRV_OBJECT_NULL 0x14301
#define ERROR_AXIS_ENC_OBJECT_NULL 0x14302
#define ERROR_AXIS_MON_OBJECT_NULL 0x14303
#define ERROR_AXIS_TRAJ_OBJECT_NULL 0x14304
#define ERROR_AXIS_CNTRL_OBJECT_NULL 0x14305
#define ERROR_AXIS_SEQ_ERROR_WRONG_SENSOR_EDGE 0x14306
#define ERROR_AXIS_UNDEFINED_TYPE 0x14307
#define ERROR_AXIS_FORWARD_TRANSFORM_NULL 0x14308
#define ERROR_AXIS_INVERSE_TRANSFORM_NULL 0x14309
#define ERROR_AXIS_TRANSFORM_ERROR_OR_NOT_COMPILED 0x1430A
#define ERROR_AXIS_FUNCTION_NOT_SUPPRTED 0x1430B
#define ERROR_AXIS_MASTER_AXIS_OBJECT_NULL 0x1430C
#define ERROR_AXIS_MASTER_AXIS_ENCODER_NULL 0x1430D
#define ERROR_AXIS_MASTER_AXIS_TRAJECTORY_NULL 0x1430E
#define ERROR_AXIS_MASTER_AXIS_TRANSFORM_NULL 0x1430F
#define ERROR_AXIS_SOURCE_TYPE_NOT_DEFINED 0x14310
#define ERROR_AXIS_CMD_NOT_ALLOWED_WHEN_ENABLED 0x14311
#define ERROR_AXIS_CONFIGURED_COUNT_ZERO 0x14312
#define ERROR_AXIS_CASCADED_AXIS_INDEX_OUT_OF_RANGE 0x14313

//DRIVE
#define ERROR_DRV_DRIVE_INTERLOCKED 0x14600
#define ERROR_DRV_ASSIGN_ENTRY_FAILED 0x14601
#define ERROR_DRV_SCALE_DENOM_ZERO 0x14602
#define ERROR_DRV_ENABLE_ENTRY_NULL 0x14603
#define ERROR_DRV_VEL_SET_ENTRY_NULL 0x14604

//ENCODER
#define ERROR_ENC_ASSIGN_ENTRY_FAILED 0x14400
#define ERROR_ENC_TYPE_NOT_SUPPORTED 0x14401
#define ERROR_ENC_SCALE_DENOM_ZERO 0x14402
#define ERROR_ENC_INVALID_RATE 0x14403
#define ERROR_ENC_ENTRY_NULL 0x14404
#define ERROR_ENC_ENTRY_READ_FAIL 0x14405
#define ERROR_ENC_TRANSFORM_NULL 0x14406
#define ERROR_ENC_EXT_MASTER_SOURCE_NULL 0x14407
#define ERROR_ENC_EXT_MASTER_SOURCE_COUNT_ZERO 0x14408
#define ERROR_ENC_INVALID_SAMPLE_TIME 0x14409
#define ERROR_ENC_TRANSFORM_VALIDATION_ERROR 0x1440A
#define ERROR_ENC_SLAVE_INTERFACE_NULL 0x1440B

//MONITOR
#define ERROR_MON_ASSIGN_ENTRY_FAILED 0x14C00
#define ERROR_MON_ENTRY_READ_FAIL 0x14C01
#define ERROR_MON_ENTRY_HARD_BWD_NULL 0x14C02
#define ERROR_MON_ENTRY_HARD_FWD_NULL 0x14C03
#define ERROR_MON_ENTRY_HOME_NULL 0x14C04

//SEQUENCER
#define ERROR_SEQ_TRAJ_NULL 0x14D00
#define ERROR_SEQ_ENC_NULL 0x14D01
#define ERROR_SEQ_MON_NULL 0x14D02
#define ERROR_SEQ_CNTRL_NULL 0x14D03
#define ERROR_SEQ_SEQ_FAILED 0x14D04
#define ERROR_SEQ_COMMAND_NOT_SUPPORTED 0x14D05
#define ERROR_SEQ_SOFT_LIMIT_FWD 0x14D06
#define ERROR_SEQ_SOFT_LIMIT_BWD 0x14D07
#define ERROR_SEQ_TIMEOUT 0x14D08

//TRAJECTORY
#define ERROR_TRAJ_EXT_ENC_NULL 0x14E00
#define ERROR_TRAJ_EXT_TRAJ_NULL 0x14E01
#define ERROR_TRAJ_NOT_ENABLED 0x14E02
#define ERROR_TRAJ_GEAR_RATIO_DENOM_ZERO 0x14E03
#define ERROR_TRAJ_SOFT_LIMIT_FWD_INTERLOCK 0x14E04
#define ERROR_TRAJ_SOFT_LIMIT_BWD_INTERLOCK  0x14E05
#define ERROR_TRAJ_HARD_LIMIT_FWD_INTERLOCK  0x14E06
#define ERROR_TRAJ_HARD_LIMIT_BWD_INTERLOCK  0x14E07
#define ERROR_TRAJ_POS_LAG_INTERLOCK 0x14E08
#define ERROR_TRAJ_BOTH_LIMIT_INTERLOCK 0x14E09
#define ERROR_TRAJ_EXTERNAL_INTERLOCK 0x14E0A
#define ERROR_TRAJ_EXECUTE_BUT_NO_ENABLE 0x14E0B
#define ERROR_TRAJ_EXT_TRANSFORM_NULL 0x14E0C
#define ERROR_TRAJ_TRANSFORM_NOT_COMPILED 0x14E0D
#define ERROR_TRAJ_TRANSFORM_INTERLOCK_ERROR 0x14E0E
#define ERROR_TRAJ_TRANSFORM_NULL 0x14E0F
#define ERROR_TRAJ_EXT_MASTER_SOURCE_NULL 0x14E10
#define ERROR_TRAJ_EXT_MASTER_SOURCE_COUNT_ZERO 0x14E11
#define ERROR_TRAJ_INVALID_SAMPLE_TIME 0x14E12
#define ERROR_TRAJ_TRANSFORM_VALIDATION_ERROR 0x14E13
#define ERROR_TRAJ_SLAVE_INTERFACE_NULL 0x14E14
#define ERROR_TRAJ_MAX_SPEED_INTERLOCK 0x14E15

//VIRTUAL AXIS
#define ERROR_VIRT_AXIS_TRAJ_NULL 0x14F00
#define ERROR_VIRT_AXIS_CREATE_TRANSFORM_INDEX_OUT_OF_RANGE 0x14F01
#define ERROR_VIRT_AXIS_INDEX_OUT_OF_RANGE 0x14F02
#define ERROR_VIRT_AXIS_LINKED_AXIS_TRAJ_NULL 0x14F03
#define ERROR_VIRT_AXIS_INDEX_NULL 0x14F04

//CONTROLLER
#define ERROR_CNTRL_INVALID_SAMPLE_TIME 0x15000

//TRANSFORM
#define ERROR_TRANSFORM_EXPR_NOT_COMPILED 0x30000
#define ERROR_TRANSFORM_INPUT_INDEX_OUT_OF_RANGE 0x30001
#define ERROR_TRANSFORM_COMPILE_ERROR 0x30002
#define ERROR_TRANSFORM_INPUT_DATA_SOURCE_NULL 0x30003
#define ERROR_TRANSFORM_ERROR_ADD_VARIABLE 0x30004
#define ERROR_TRANSFORM_INPUT_DATA_SOURCE_COUNT_ZERO 0x30005
#define ERROR_TRANSFORM_NOT_ENABLED 0x30006

//MASTERDATA INTERFACE
#define ERROR_MASTER_DATA_IF_INDEX_OUT_OF_RANGE 0x30100

//ECENTRY
#define ERROR_EC_ENTRY_DATA_POINTER_NULL 0x21000
#define ERROR_EC_ENTRY_INVALID_OFFSET 0x21001
#define ERROR_EC_ENTRY_INVALID_DOMAIN_ADR 0x21002
#define ERROR_EC_ENTRY_INVALID_BIT_LENGTH 0x21003

//ECPDO
#define ERROR_EC_PDO_ENTRY_ARRAY_FULL 0x22000

//ECSDO
#define ERROR_EC_SDO_SIZE_TO_LARGE 0x23000
#define ERROR_EC_SDO_WRITE_FAILED 0x23001
#define ERROR_EC_SDO_READ_FAILED 0x23002
#define ERROR_EC_SDO_VERIFY_FAILED 0x23003

//ECSLAVE
#define ERROR_EC_SLAVE_CONFIG_FAILED 0x24000
#define ERROR_EC_SLAVE_CALL_NOT_ALLOWED_IN_SIM_MODE 0x24001
#define ERROR_EC_SLAVE_SM_ARRAY_FULL 0x24002
#define ERROR_EC_SLAVE_SM_INDEX_OUT_OF_RANGE 0x24003
#define ERROR_EC_SLAVE_ENTRY_INFO_STRUCT_NULL 0x24004
#define ERROR_EC_SLAVE_ENTRY_INDEX_OUT_OF_RANGE 0x24005
#define ERROR_EC_SLAVE_SLAVE_INFO_STRUCT_NULL 0x24006
#define ERROR_EC_SLAVE_CONFIG_PDOS_FAILED 0x24007
#define ERROR_EC_SLAVE_ENTRY_NULL 0x24008
#define ERROR_EC_SLAVE_STATE_CHANGED 0x24009
#define ERROR_EC_SLAVE_ONLINE_OFFLINE_CHANGED 0x2400A
#define ERROR_EC_SLAVE_OPERATIONAL_CHANGED 0x2400B
#define ERROR_EC_SLAVE_CONFIG_NULL 0x2400C

//ECSYNCMANAGER
#define ERROR_EC_SM_PDO_ARRAY_FULL 0x25000
#define ERROR_EC_SM_PDO_INDEX_OUT_OF_RANGE 0x25001
#define ERROR_EC_SM_ENTRY_INFO_STRUCT_NULL 0x25002

//EC
#define ERROR_EC_MAIN_REQUEST_FAILED 0x26000
#define ERROR_EC_MAIN_CREATE_DOMAIN_FAILED 0x26001
#define ERROR_EC_MAIN_INVALID_SLAVE_INDEX 0x26002
#define ERROR_EC_MAIN_MASTER_ACTIVATE_FAILED 0x26003
#define ERROR_EC_MAIN_SLAVE_NULL 0x26004
#define ERROR_EC_MAIN_GET_SLAVE_INFO_FAILED 0x26005
#define ERROR_EC_MAIN_ENTRY_NULL 0x26006
#define ERROR_EC_MAIN_GET_ENTRY_INFO_FAILED 0x26007
#define ERROR_EC_MAIN_DOM_REG_PDO_ENTRY_LIST_FAILED 0x26008
#define ERROR_EC_MAIN_SDO_ARRAY_FULL 0x26009
#define ERROR_EC_MAIN_SDO_ENTRY_NULL 0x2600A
#define ERROR_EC_MAIN_SDO_READ_FAILED 0x2600B
#define ERROR_EC_MAIN_DOMAIN_DATA_FAILED 0x2600C
#define ERROR_EC_MAIN_SLAVE_ARRAY_FULL 0x2600D

//HW_MOTOR
#define ERROR_MAIN_APP_MODE_NOT_SUPPORTED 0x20000
#define ERROR_MAIN_DEMO_EC_ACITVATE_FAILED 0x20001
#define ERROR_MAIN_AXIS_INDEX_OUT_OF_RANGE 0x20002
#define ERROR_MAIN_AXIS_OBJECT_NULL 0x20004
#define ERROR_MAIN_ENCODER_INDEX_OUT_OF_RANGE 0x20005
#define ERROR_MAIN_ENCODER_OBJECT_NULL 0x20006
#define ERROR_MAIN_CONTROLLER_INDEX_OUT_OF_RANGE 0x20007
#define ERROR_MAIN_CONTROLLER_OBJECT_NULL 0x20008
#define ERROR_MAIN_TRAJECTORY_INDEX_OUT_OF_RANGE 0x20009
#define ERROR_MAIN_TRAJECTORY_OBJECT_NULL 0x2000A
#define ERROR_MAIN_DRIVE_INDEX_OUT_OF_RANGE 0x2000B
#define ERROR_MAIN_DRIVE_OBJECT_NULL 0x2000C
#define ERROR_MAIN_MONITOR_INDEX_OUT_OF_RANGE 0x2000D
#define ERROR_MAIN_MONITOR_OBJECT_NULL 0x2000E
#define ERROR_MAIN_AXIS_TRAJ_OBJECT_NULL 0x2000F
#define ERROR_MAIN_EC_NOT_INITIALIZED 0x20010
#define ERROR_MAIN_EC_SLAVE_NULL 0x20011
#define ERROR_MAIN_EC_SM_NULL 0x20012
#define ERROR_MAIN_EC_PDO_NULL 0x20013
#define ERROR_MAIN_EC_ENTRY_NULL 0x20014
#define ERROR_MAIN_ENCODER_ENTRY_INDEX_OUT_OF_RANGE 0x20015
#define ERROR_MAIN_DRIVE_ENTRY_INDEX_OUT_OF_RANGE 0x20016
#define ERROR_MAIN_MONITOR_ENTRY_INDEX_OUT_OF_RANGE 0x20017
#define ERROR_MAIN_DIAG_AXIS_INDEX_OUT_OF_RANGE 0x20018
#define ERROR_MAIN_DIAG_AXIS_FREQ_OUT_OF_RANGE 0x20019
#define ERROR_MAIN_APP_MODE_ALREADY_RUNTIME 0x2001A
#define ERROR_MAIN_EC_ACTIVATE_FAILED 0x2001B
#define ERROR_MAIN_ENC_SET_SCALE_FAIL_DRV_ENABLED 0x2001C
#define ERROR_MAIN_AXIS_ERROR_EXECUTE_INTERLOCKED 0x2001D
#define ERROR_MAIN_VIRT_AXIS_FUNCTION_NOT_SUPPORTED 0x2001E
#define ERROR_MAIN_AXIS_TYPE_UNKNOWN 0x2001F
#define ERROR_MAIN_SEQUENCE_OBJECT_NULL 0x20020
#define ERROR_MAIN_TRAJ_TRANSFORM_OBJECT_NULL 0x20021
#define ERROR_MAIN_ENC_TRANSFORM_OBJECT_NULL 0x20022
#define ERROR_MAIN_EXTERNAL_DATA_SOURCE_INVALID 0x20023
#define ERROR_MAIN_TRANSFORM_OUTPUT_VAR_MISSING 0x20024

#endif /* ECMCERRORSLIST_H_ */

