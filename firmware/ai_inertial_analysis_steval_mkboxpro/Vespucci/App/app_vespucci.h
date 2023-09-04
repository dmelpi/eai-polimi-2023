/**
  ******************************************************************************
  * File Name          : app_vespucci.h
  * Description        : This file provides code for the configuration
  *                      of the STMicroelectronics.X-CUBE-VESPUCCI.0.0.36 instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_VESPUCCI_H
#define __APP_VESPUCCI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "pre_processing_app.h"
#include "ai_app.h"
#include "params.h"
#include "custom_motion_sensors_ex.h"
//#include "custom_ispu_motion_sensors_ex.h"
#include "ispu_conf.h"
//#include "mlc_conf.h"
#include "arm_math.h"
#include "network.h"
#include "MEMS_integration.h"
#include "custom_bus.h"
#include "App_model.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#include "PnPL_Init.h"
#include "IAi_Application_Mcu.h"
#include "Ai_Application_Mcu_PnPL.h"
#include "IAi_Application_Mcu_vtbl.h"
#include "IAi_Application_Mlc.h"
#include "Ai_Application_Mlc_PnPL.h"
#include "IAi_Application_Mlc_vtbl.h"
#include "IAi_Application_Ispu.h"
#include "Ai_Application_Ispu_PnPL.h"
#include "IAi_Application_Ispu_vtbl.h"
#include "IController.h"
#include "Controller_PnPL.h"
#include "IController_vtbl.h"
#include "PnPLCompManager.h"

/* Exported defines ----------------------------------------------------------*/
#define     SENSOR_ODR     ISM330DHCX_ACC_ODR
#define     SENSOR_FS      ISM330DHCX_ACC_FS
#define     SENSOR_0       CUSTOM_LSM6DSV16X_0              // Sensor used
//#define     SENSOR_ISPU    CUSTOM_ISM330IS_0              // Sensor ISPU used
#define     COMMAND_BUFFER_SIZE  (128*1024)                 // 128KB
#define     PRINTED_BUFFER_SIZE  (8*1024)
#define     COMPRESSED_UCF_LINE_WIDTH  4U

#define CHECK_BSP_FUNCTION(function) \
		{ \
	if ((ret = function) != BSP_ERROR_NONE) { \
		return ret; \
	} \
		}

#define RESET_STRING(string) \
		{ \
	memset(string, 0, strlen(string)); \
		}

#define PRINT(message, ...) \
		{ \
	RESET_STRING(buffer_to_write); \
	uint32_t n = snprintf(buffer_to_write, PRINTED_BUFFER_SIZE, message, ##__VA_ARGS__); \
	CDC_Transmit_FS((uint8_t*) buffer_to_write, n); \
		}

typedef enum {
	MCU,
	MLC,
	ISPU,
	CONTROLLER
} ai_type_t;

typedef enum {
	INVALID_CMD = 0,
	VALID_CMD,
	MLC_LOAD_UCF_CMD,
	ISPU_LOAD_UCF_CMD
} command_t;

// List of possible commands.
// MCU
#if 0
#define MCU_START_CMD_STR       "{\"ai_application_mcu*start\":\"\"}"
#define MCU_STOP_CMD_STR        "{\"ai_application_mcu*stop\":\"\"}"
// MLC
#define MLC_START_CMD_STR       "{\"ai_application_mlc*start\":\"\"}"
#define MLC_STOP_CMD_STR        "{\"ai_application_mlc*stop\":\"\"}"
#define MLC_LOAD_UCF_CMD_STR    "{\"ai_application_mlc*load_ucf\":{\"arguments\":{\"ucf_content_size\":"
// ISPU
#define ISPU_START_CMD_STR      "{\"ai_application_ispu*start\":\"\"}"
#define ISPU_STOP_CMD_STR       "{\"ai_application_ispu*stop\":\"\"}"
#define ISPU_LOAD_UCF_CMD_STR   "{\"ai_application_ispu*load_ucf\":{\"arguments\":{\"ucf_content_size\":"
// CONTROLLER
#define SWITCH_BANK_CMD_STR     "{\"controller*switch_bank\":\"\"}"
#endif

/* Public variables   --------------------------------------------------------*/
//extern char *command_buffer_ptr;
//extern char *command_buffer_write_ptr;
//extern bool command_received;
extern char buffer_to_write[PRINTED_BUFFER_SIZE];        // Buffer to be printed (it will contain the telemetries).
extern ai_type_t default_ai;                             // Selected use-case.
extern int mcu_inference;                                // Flag when the application MCU is working.
extern int mlc_inference;                                // Flag when the application MLC is working.
extern int ispu_inference;                               // Flag when the application ISPU is working.
extern uint32_t mlc_register;                            // MLC Output Register number.


/* Exported functions --------------------------------------------------------*/
int32_t MX_Vespucci_Init(void);
int32_t MX_Vespucci_Process(void);
int32_t send_telemetries_mcu();
int32_t send_telemetries_mlc();
int32_t send_telemetries_ispu();
int32_t debug_fifo_status();
int32_t sensor_init();
int32_t is_size_present(char* input_command);
void pnpl_init();
void pnpl_process();
void read_mlc_output(uint8_t* mlc_output_reg);
void read_ispu_output(uint8_t* ispu_output_reg);
void load_mlc_configuration(ucf_line_t* mlc_configuration, uint32_t ucf_number_of_lines);
void load_ispu_configuration(ucf_line_ext_t* ispu_configuration, uint32_t ucf_number_of_lines);
uint32_t get_ucf_number_of_lines(int32_t ucf_content_size, const char *ucf_content);
void fill_mlc_configuration(const char* ucf_content, ucf_line_t* mlc_configuration);
void get_mlc_register(const char* ucf_content, uint32_t *mlc_register);


#ifdef __cplusplus
}
#endif

#endif /* __APP_VESPUCCI_H */

