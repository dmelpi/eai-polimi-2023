/**
  ******************************************************************************
  * @file    App_Model.c
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

#include "app_vespucci.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* USER includes -------------------------------------------------------------*/

/* USER private function prototypes ------------------------------------------*/

/* USER defines --------------------------------------------------------------*/

static uint8_t sensors_cnt = 0;

extern ucf_line_t default_mlc_conf[];
extern ucf_line_t* mlc_conf;
extern uint32_t mlc_conf_size;

AppModel_t app_model;

static void ToggleFlashBank(void)
{
	FLASH_OBProgramInitTypeDef    OBInit;
	/* Set BFB2 bit to enable boot from Flash Bank2 */
	/* Allow Access to Flash control registers and user Flash */
	HAL_FLASH_Unlock();

	/* Allow Access to option bytes sector */
	HAL_FLASH_OB_Unlock();

	/* Get the Dual boot configuration status */
	HAL_FLASHEx_OBGetConfig(&OBInit);

	/* Enable/Disable dual boot feature */
	OBInit.OptionType = OPTIONBYTE_USER;
	OBInit.USERType   = OB_USER_SWAP_BANK;

	if (((OBInit.USERConfig) & (FLASH_OPTR_SWAP_BANK)) == FLASH_OPTR_SWAP_BANK)
	{
		OBInit.USERConfig &= ~FLASH_OPTR_SWAP_BANK;
	}
	else
	{
		OBInit.USERConfig = FLASH_OPTR_SWAP_BANK;
	}

	//SYS_DEBUGF(SYS_DBG_LEVEL_WARNING, ("HW: Switching Bank\r\n"));
	if(HAL_FLASHEx_OBProgram (&OBInit) != HAL_OK)
	{
		/*
	    Error occurred while setting option bytes configuration.
	    User can add here some code to deal with this error.
	    To know the code error, user can call function 'HAL_FLASH_GetError()'
		 */
		while(1);
	}

	/* Start the Option Bytes programming process */
	if (HAL_FLASH_OB_Launch() != HAL_OK) {
		/*
	    Error occurred while reloading option bytes configuration.
	    User can add here some code to deal with this error.
	    To know the code error, user can call function 'HAL_FLASH_GetError()'
		 */
		while(1);
	}
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}

AppModel_t* getAppModel(void)
{
  return &app_model;
}

/* Device Components APIs ----------------------------------------------------*/

/* LSM6DSV16X_ACC PnPL Component ---------------------------------------------*/
static SensorModel_t lsm6dsv16x_acc_model;

uint8_t lsm6dsv16x_acc_comp_init(void)
{
  lsm6dsv16x_acc_model.comp_name = lsm6dsv16x_acc_get_key();

  uint16_t id = sensors_cnt;
  sensors_cnt +=1;
  app_model.s_models[id] = &lsm6dsv16x_acc_model;

  /* USER Component initialization code */
  return 0;
}
char* lsm6dsv16x_acc_get_key(void)
{
  return "lsm6dsv16x_acc";
}

uint8_t lsm6dsv16x_acc_get_odr(float *value)
{
  /* USER Code */
  return 0;
}
uint8_t lsm6dsv16x_acc_get_fs(float *value)
{
  /* USER Code */
  return 0;
}
uint8_t lsm6dsv16x_acc_get_stream_id(int8_t *value)
{
  /* USER Code */
  return 0;
}
uint8_t lsm6dsv16x_acc_get_ep_id(int8_t *value)
{
  /* USER Code */
  return 0;
}

/* Firmware Information PnPL Component ---------------------------------------*/
uint8_t firmware_info_comp_init(void)
{
  app_model.firmware_info_model.comp_name = firmware_info_get_key();

  /* USER Component initialization code */
  return 0;
}
char* firmware_info_get_key(void)
{
  return "firmware_info";
}

uint8_t firmware_info_get_alias(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t firmware_info_get_fw_name(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t firmware_info_get_fw_version(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t firmware_info_get_serial_number(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t firmware_info_get_device_url(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t firmware_info_get_fw_url(char **value)
{
  /* USER Code */
  return 0;
}

/* AI Application MCU PnPL Component -----------------------------------------*/
uint8_t ai_application_mcu_comp_init(void)
{
  app_model.ai_application_mcu_model.comp_name = ai_application_mcu_get_key();

  /* USER Component initialization code */
  return 0;
}
char* ai_application_mcu_get_key(void)
{
  return "ai_application_mcu";
}

uint8_t ai_application_mcu_get_enabled(bool *value)
{
  /* USER Code */
  return 0;
}
uint8_t ai_application_mcu_start(IAi_Application_Mcu_t *ifn)
{
#ifndef MCU_DISABLED
	sensor_init();
        // Set the FIFO to Continuous/Stream Mode.
	MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(SENSOR_0,  LSM6DSV16X_STREAM_MODE);
	mcu_inference = 1;
	return 0;
#endif
}
uint8_t ai_application_mcu_stop(IAi_Application_Mcu_t *ifn)
{
#ifndef MCU_DISABLED
        // Set the FIFO to Bypass Mode.
	MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(SENSOR_0,  LSM6DSV16X_BYPASS_MODE);
	mcu_inference = 0;
	return 0;
#endif
}
uint8_t ai_application_mcu_create_telemetry(int label_id, float accuracy, char **telemetry, uint32_t *size)
{
  PnPLTelemetry_t telemetries[2];
  strcpy(telemetries[0].telemetry_name, "label_id");
  telemetries[0].telemetry_value = (void*)& label_id;
  telemetries[0].telemetry_type = PNPL_INT;
  telemetries[0].n_sub_telemetries = 0;
  strcpy(telemetries[1].telemetry_name, "accuracy");
  telemetries[1].telemetry_value = (void*)& accuracy;
  telemetries[1].telemetry_type = PNPL_FLOAT;
  telemetries[1].n_sub_telemetries = 0;

  PnPLSerializeTelemetry("ai_application_mcu", telemetries, 2, telemetry, size, 0);
  return 0;
}

/* AI Application MLC PnPL Component -----------------------------------------*/
uint8_t ai_application_mlc_comp_init(void)
{
  app_model.ai_application_mlc_model.comp_name = ai_application_mlc_get_key();

  /* USER Component initialization code */
  return 0;
}
char* ai_application_mlc_get_key(void)
{
  return "ai_application_mlc";
}

uint8_t ai_application_mlc_get_enabled(bool *value)
{
  /* USER Code */
  return 0;
}
uint8_t ai_application_mlc_start(IAi_Application_Mlc_t *ifn)
{
#ifndef MLC_DISABLED
	sensor_init();
	load_mlc_configuration((ucf_line_t*) &mlc_conf, mlc_conf_size);
	mlc_inference = 1;
#endif
	return 0;
}
uint8_t ai_application_mlc_stop(IAi_Application_Mlc_t *ifn)
{
#ifndef MLC_DISABLED
	mlc_inference = 0;
	if (mcu_inference) {
		sensor_init();
                // Set the FIFO to Continuous/Stream Mode.
		MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(SENSOR_0,  LSM6DSV16X_STREAM_MODE);
	}

#endif
	return 0;
}
#if 0
uint8_t ai_application_mlc_load_ucf(IAi_Application_Mlc_t *ifn, int32_t ucf_content_size, const char *ucf_content)
{
#ifndef MLC_DISABLED

	sensor_init();

	if(flag_load_ucf_mlc == 1) {
		flag_load_ucf_mlc = 0;
	}

	// Load the compressed UCF file.
	load_compressed_ucf(ucf_content, (uint32_t)strlen(ucf_content));

	// Starting MLC inference.
	RESET_STRING(load_ucf_command);
	free(load_ucf_command);
	mlc_inference = 1;
	flag_load_ucf_mlc = 1;
#endif
	return 0;
}
#else
uint8_t ai_application_mlc_load_ucf(IAi_Application_Mlc_t *ifn, int32_t ucf_content_size, const char *ucf_content)
{
	/* USER Code */
#ifndef MLC_DISABLED
	static ucf_line_t* loaded_mlc_conf;

	// De-allocating space for the MLC configuration structure.
    free(loaded_mlc_conf);

	// Allocating space for the MLC configuration structure.
    mlc_conf_size = get_ucf_number_of_lines(ucf_content_size, ucf_content);
	loaded_mlc_conf = (ucf_line_t*) calloc(mlc_conf_size, sizeof(ucf_line_t));

	// Getting MLC register from UCF file.
	get_mlc_register(ucf_content, &mlc_register);

	// Filling MLC configuration structure from UCF file.
	fill_mlc_configuration(ucf_content, loaded_mlc_conf);

	// Update MLC configuration structure.
	mlc_conf = loaded_mlc_conf;

	// Loading MLC configuration into MLC registers.
	load_mlc_configuration(mlc_conf, mlc_conf_size);

	// Starting MLC inference.
	mlc_inference = 1;
#endif
	return 0;
}
#endif
uint8_t ai_application_mlc_create_telemetry(int label_id, char **telemetry, uint32_t *size)
{
  PnPLTelemetry_t telemetries[1];
  strcpy(telemetries[0].telemetry_name, "label_id");
  telemetries[0].telemetry_value = (void*)& label_id;
  telemetries[0].telemetry_type = PNPL_INT;
  telemetries[0].n_sub_telemetries = 0;

	PnPLSerializeTelemetry("ai_application_mlc", telemetries, 1, telemetry, size, 0);
	return 0;
}

/* AI Application ISPU PnPL Component ----------------------------------------*/
uint8_t ai_application_ispu_comp_init(void)
{
	app_model.ai_application_ispu_model.comp_name = ai_application_ispu_get_key();

	/* USER Component initialization code */
	return 0;
}
char* ai_application_ispu_get_key(void)
{
	return "ai_application_ispu";
}

uint8_t ai_application_ispu_get_enabled(bool *value)
{
	/* USER Code */
	return 0;
}
uint8_t ai_application_ispu_start(IAi_Application_Ispu_t *ifn)
{
#ifndef ISPU_DISABLED

	sensor_init();
	//load_ispu_configuration((ucf_line_ext_t*) &ispu_conf, sizeof(ispu_conf) / sizeof(ucf_line_ext_t));
	ispu_inference = 1;
#endif
	return 0;
}
uint8_t ai_application_ispu_stop(IAi_Application_Ispu_t *ifn)
{
#ifndef ISPU_DISABLED
	ispu_inference = 0;
	if (mcu_inference) {
		sensor_init();
                // Set the FIFO to Continuous/Stream Mode.
		MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(SENSOR_0,  LSM6DSV16X_STREAM_MODE);
	}
#endif
	return 0;
}
uint8_t ai_application_ispu_load_ucf(IAi_Application_Ispu_t *ifn, int32_t ucf_content_size, const char *ucf_content)
{
#if 0
#ifndef ISPU_DISABLED

	sensor_init();

	if (flag_load_ucf_ispu == 1) {
		flag_load_ucf_ispu = 0;
	}

	// Load the compressed UCF file.
	load_compressed_ucf(ucf_content, (uint32_t)strlen(ucf_content));

	// Starting ISPU inference.
	RESET_STRING(load_ucf_command);
	free(load_ucf_command);
	ispu_inference = 1;
	flag_load_ucf_ispu = 1;
#endif
#endif
	return 0;
}
uint8_t ai_application_ispu_create_telemetry(int label_id, char **telemetry, uint32_t *size)
{
	PnPLTelemetry_t telemetries[1];
	strcpy(telemetries[0].telemetry_name, "label_id");
	telemetries[0].telemetry_value = (void*)& label_id;
	telemetries[0].telemetry_type = PNPL_INT;
	telemetries[0].n_sub_telemetries = 0;

	PnPLSerializeTelemetry("ai_application_ispu", telemetries, 1, telemetry, size, 0);
	return 0;
}

/* Controller PnPL Component -------------------------------------------------*/
uint8_t controller_comp_init(void)
{
  app_model.controller_model.comp_name = controller_get_key();

  /* USER Component initialization code */
  return 0;
}
char* controller_get_key(void)
{
  return "controller";
}

uint8_t controller_switch_bank(IController_t *ifn)
{
	ToggleFlashBank();
	return 0;
}

/* Device Information PnPL Component -----------------------------------------*/
uint8_t DeviceInformation_comp_init(void)
{

  /* USER Component initialization code */
  return 0;
}
char* DeviceInformation_get_key(void)
{
  return "DeviceInformation";
}

uint8_t DeviceInformation_get_manufacturer(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t DeviceInformation_get_model(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t DeviceInformation_get_swVersion(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t DeviceInformation_get_osName(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t DeviceInformation_get_processorArchitecture(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t DeviceInformation_get_processorManufacturer(char **value)
{
  /* USER Code */
  return 0;
}
uint8_t DeviceInformation_get_totalStorage(float *value)
{
  /* USER Code */
  return 0;
}
uint8_t DeviceInformation_get_totalMemory(float *value)
{
  /* USER Code */
  return 0;
}

