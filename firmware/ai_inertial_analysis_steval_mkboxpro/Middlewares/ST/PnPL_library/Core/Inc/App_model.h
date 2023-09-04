/**
  ******************************************************************************
  * @file    App_model.h
  * @author  SRA
  * @brief   App Application Model and PnPL Components APIs
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  *
  ******************************************************************************
  */

/**
  ******************************************************************************
  * This file has been auto generated from the following Device Template Model:
  * dtmi:vespucci:steval_stwinbx1:ai_inertial_analysis_steval_stwinbx1;1
  *
  * Created by: DTDL2PnPL_cGen version 1.0.0
  *
  * WARNING! All changes made to this file will be lost if this is regenerated
  ******************************************************************************
  */

/**
  ******************************************************************************
  * Component APIs *************************************************************
  * - Component init function
  *    <comp_name>_comp_init(void)
  * - Component get_key function
  *    <comp_name>_get_key(void)
  * - Component GET/SET Properties APIs ****************************************
  *  - GET Functions
  *    uint8_t <comp_name>_get_<prop_name>(prop_type *value)
  *      if prop_type == char --> (char **value)
  *  - SET Functions
  *    uint8_t <comp_name>_set_<prop_name>(prop_type value)
  *      if prop_type == char --> (char *value)
  *  - Component COMMAND Reaction Functions
  *      uint8_t <comp_name>_<command_name>(I<Compname>_t * ifn,
  *                     field1_type field1_name, field2_type field2_name, ...,
  *                     fieldN_type fieldN_name); //ifn: Interface Functions
  *  - Component TELEMETRY Send Functions
  *      uint8_t <comp_name>_create_telemetry(tel1_type tel1_name,
  *                     tel2_type tel2_name, ..., telN_type telN_name,
  *                     char **telemetry, uint32_t *size)
  ******************************************************************************
  */

#ifndef APP_MODEL_H_
#define APP_MODEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
#include "stdbool.h"
#include "PnPLCompManager.h"
#include "IAi_Application_Mcu.h"
#include "IAi_Application_Mcu_vtbl.h"
#include "IAi_Application_Mlc.h"
#include "IAi_Application_Mlc_vtbl.h"
#include "IAi_Application_Ispu.h"
#include "IAi_Application_Ispu_vtbl.h"
#include "IController.h"
#include "IController_vtbl.h"
/* USER includes -------------------------------------------------------------*/

#define COMP_TYPE_SENSOR          0x00
#define COMP_TYPE_ALGORITHM       0x01
#define COMP_TYPE_OTHER           0x02
#define COMP_TYPE_ACTUATOR        0x03

#define LOG_CTRL_MODE_SD          0x00
#define LOG_CTRL_MODE_USB         0x01
#define LOG_CTRL_MODE_BLE         0x02

#define SENSOR_NUMBER             1
#define ALGORITHM_NUMBER	        0
#define ACTUATOR_NUMBER	          0
#define OTHER_COMP_NUMBER	        5

typedef struct _StreamParams_t
{
  int8_t stream_id;
  int8_t usb_ep;
  uint16_t spts;
  uint32_t usb_dps;
  uint32_t sd_dps;
  float ioffset;
  float bandwidth;
  /* Stream Parameters Model USER code */
} StreamParams_t;

typedef struct _SensorModel_t
{
  /* E.g. IIS3DWB Component is a sensor (look @ schema field)
     so, its model has the following structure */
  uint8_t id;
  char *comp_name;
  StreamParams_t streamParams;
  /* Sensor Components Model USER code */
} SensorModel_t;

typedef struct _FirmwareInfoModel_t
{
  char *comp_name;
  /* FirmwareInfo Component Model USER code */
} FirmwareInfoModel_t;

typedef struct _AiApplicationMcuModel_t
{
  char *comp_name;
  /* AiApplicationMcu Component Model USER code */
} AiApplicationMcuModel_t;

typedef struct _AiApplicationMlcModel_t
{
  char *comp_name;
  /* AiApplicationMlc Component Model USER code */
} AiApplicationMlcModel_t;

typedef struct _AiApplicationIspuModel_t
{
  char *comp_name;
  /* AiApplicationIspu Component Model USER code */
} AiApplicationIspuModel_t;

typedef struct _ControllerModel_t
{
  char *comp_name;
  /* Controller Component Model USER code */
} ControllerModel_t;

typedef struct _AppModel_t
{
  SensorModel_t *s_models[SENSOR_NUMBER];
  FirmwareInfoModel_t firmware_info_model;
  AiApplicationMcuModel_t ai_application_mcu_model;
  AiApplicationMlcModel_t ai_application_mlc_model;
  AiApplicationIspuModel_t ai_application_ispu_model;
  ControllerModel_t controller_model;
  /* Insert here your custom App Model code */
} AppModel_t;

AppModel_t *getAppModel(void);

/* Device Components APIs ----------------------------------------------------*/

/* ISM330DHCX_ACC PnPL Component ---------------------------------------------*/
uint8_t lsm6dsv16x_acc_comp_init(void);
char* lsm6dsv16x_acc_get_key(void);
uint8_t lsm6dsv16x_acc_get_odr(float *value);
uint8_t lsm6dsv16x_acc_get_fs(float *value);
uint8_t lsm6dsv16x_acc_get_stream_id(int8_t *value);
uint8_t lsm6dsv16x_acc_get_ep_id(int8_t *value);

/* Firmware Information PnPL Component ---------------------------------------*/
uint8_t firmware_info_comp_init(void);
char* firmware_info_get_key(void);
uint8_t firmware_info_get_alias(char **value);
uint8_t firmware_info_get_fw_name(char **value);
uint8_t firmware_info_get_fw_version(char **value);
uint8_t firmware_info_get_serial_number(char **value);
uint8_t firmware_info_get_device_url(char **value);
uint8_t firmware_info_get_fw_url(char **value);

/* AI Application MCU PnPL Component -----------------------------------------*/
uint8_t ai_application_mcu_comp_init(void);
char* ai_application_mcu_get_key(void);
uint8_t ai_application_mcu_get_enabled(bool *value);
uint8_t ai_application_mcu_start(IAi_Application_Mcu_t *ifn);
uint8_t ai_application_mcu_stop(IAi_Application_Mcu_t *ifn);
uint8_t ai_application_mcu_create_telemetry(int label_id, float accuracy, char **telemetry, uint32_t *size);

/* AI Application MLC PnPL Component -----------------------------------------*/
uint8_t ai_application_mlc_comp_init(void);
char* ai_application_mlc_get_key(void);
uint8_t ai_application_mlc_get_enabled(bool *value);
uint8_t ai_application_mlc_start(IAi_Application_Mlc_t *ifn);
uint8_t ai_application_mlc_stop(IAi_Application_Mlc_t *ifn);
uint8_t ai_application_mlc_load_ucf(IAi_Application_Mlc_t *ifn, int32_t ucf_content_size, const char *ucf_content);
uint8_t ai_application_mlc_create_telemetry(int label_id, char **telemetry, uint32_t *size);

/* AI Application ISPU PnPL Component ----------------------------------------*/
uint8_t ai_application_ispu_comp_init(void);
char* ai_application_ispu_get_key(void);
uint8_t ai_application_ispu_get_enabled(bool *value);
uint8_t ai_application_ispu_start(IAi_Application_Ispu_t *ifn);
uint8_t ai_application_ispu_stop(IAi_Application_Ispu_t *ifn);
uint8_t ai_application_ispu_load_ucf(IAi_Application_Ispu_t *ifn, int32_t ucf_content_size, const char *ucf_content);
uint8_t ai_application_ispu_create_telemetry(int label_id, char **telemetry, uint32_t *size);

/* Controller PnPL Component -------------------------------------------------*/
uint8_t controller_comp_init(void);
char* controller_get_key(void);
uint8_t controller_switch_bank(IController_t *ifn);

/* Device Information PnPL Component -----------------------------------------*/
uint8_t DeviceInformation_comp_init(void);
char* DeviceInformation_get_key(void);
uint8_t DeviceInformation_get_manufacturer(char **value);
uint8_t DeviceInformation_get_model(char **value);
uint8_t DeviceInformation_get_swVersion(char **value);
uint8_t DeviceInformation_get_osName(char **value);
uint8_t DeviceInformation_get_processorArchitecture(char **value);
uint8_t DeviceInformation_get_processorManufacturer(char **value);
uint8_t DeviceInformation_get_totalStorage(float *value);
uint8_t DeviceInformation_get_totalMemory(float *value);

#ifdef __cplusplus
}
#endif

#endif /* APP_MODEL_H_ */
