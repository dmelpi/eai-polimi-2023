/**
  ******************************************************************************
  * @file    PnPL_Usage_README.txt
  * @author  SRA
  * @brief   Helper code snippets for PnPL features integration
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


/* PnPL Components Manager and PnPL Components includes --------------------- */
include "PnPLInit.h"
/* -------------------------------------------------------------------------- */

/* PnPL Components Command interfaces Objects */
static IAi_Application_Mcu_t iAi_Application_Mcu;
static IAi_Application_Mlc_t iAi_Application_Mlc;
static IAi_Application_Ispu_t iAi_Application_Ispu;
static IController_t iController;

/* --- PnPL Components Commands Interfaces functions assignment Helpers:
    PnPL Components with Commands in their DTDL definition will be
    associated with an Interface that contains all the necessary
    functions to respond to each specific Command defined.
    Empty functions are provided, ready to be incorporated into the
    appropriate interface instance. The user will populate these
    functions with the correct logic, which only they know.
    Subsequently, these interfaces will be passed as parameters to
    the correct PnPL initialization function.*/

static const IAi_Application_Mcu_vtbl ai_application_mcu_functions =
{
  ai_application_mcu_start_func,
  ai_application_mcu_stop_func
};

uint8_t ai_application_mcu_start_func(IAi_Application_Mcu_t *_this)
{
  /* USER Code */
  return 0;
}

uint8_t ai_application_mcu_stop_func(IAi_Application_Mcu_t *_this)
{
  /* USER Code */
  return 0;
}

static const IAi_Application_Mlc_vtbl ai_application_mlc_functions =
{
  ai_application_mlc_start_func,
  ai_application_mlc_stop_func,
  ai_application_mlc_load_ucf_func
};

uint8_t ai_application_mlc_start_func(IAi_Application_Mlc_t *_this)
{
  /* USER Code */
  return 0;
}

uint8_t ai_application_mlc_stop_func(IAi_Application_Mlc_t *_this)
{
  /* USER Code */
  return 0;
}

uint8_t ai_application_mlc_load_ucf_func(IAi_Application_Mlc_t *_this, int32_t ucf_content_size, const char *ucf_content)
{
  /* USER Code */
  return 0;
}

static const IAi_Application_Ispu_vtbl ai_application_ispu_functions =
{
  ai_application_ispu_start_func,
  ai_application_ispu_stop_func,
  ai_application_ispu_load_ucf_func
};

uint8_t ai_application_ispu_start_func(IAi_Application_Ispu_t *_this)
{
  /* USER Code */
  return 0;
}

uint8_t ai_application_ispu_stop_func(IAi_Application_Ispu_t *_this)
{
  /* USER Code */
  return 0;
}

uint8_t ai_application_ispu_load_ucf_func(IAi_Application_Ispu_t *_this, int32_t ucf_content_size, const char *ucf_content)
{
  /* USER Code */
  return 0;
}

static const IController_vtbl controller_functions =
{
  controller_switch_bank_func
};

uint8_t controller_switch_bank_func(IController_t *_this)
{
  /* USER Code */
  return 0;
}

/* [MODE 1] PnPL Components initialization ---------------------------------- */
/* - Simplified PnPL Components initialization Code */

/* --- PnPL Components Allocation and Initialization. */
PnPL_Components_Alloc();
iAi_Application_Mcu.vptr = &ai_application_mcu_functions;
iAi_Application_Mlc.vptr = &ai_application_mlc_functions;
iAi_Application_Ispu.vptr = &ai_application_ispu_functions;
iController.vptr = &controller_functions;
PnPL_Components_Init(iAi_Application_Mcu, iAi_Application_Mlc, iAi_Application_Ispu, iController);

/* [MODE 1] End of initialization code -------------------------------------- */

/* [MODE 2] PnPL Components initialization ---------------------------------- */
/* - If required by the context, it is also possible to call the Alloc
   and Init function for each PnPL Component individually. */

/* --- PnPL Components Objects declaration */
static IPnPLComponent_t *pIsm330dhcx_Acc_PnPLObj = NULL;
static IPnPLComponent_t *pFirmware_Info_PnPLObj = NULL;
static IPnPLComponent_t *pAi_Application_Mcu_PnPLObj = NULL;
static IPnPLComponent_t *pAi_Application_Mlc_PnPLObj = NULL;
static IPnPLComponent_t *pAi_Application_Ispu_PnPLObj = NULL;
static IPnPLComponent_t *pController_PnPLObj = NULL;
static IPnPLComponent_t *pDeviceinformation_PnPLObj = NULL;

/* --- PnPL Components Allocation */
pIsm330dhcx_Acc_PnPLObj = Ism330dhcx_Acc_PnPLAlloc();
pFirmware_Info_PnPLObj = Firmware_Info_PnPLAlloc();
pAi_Application_Mcu_PnPLObj = Ai_Application_Mcu_PnPLAlloc();
pAi_Application_Mlc_PnPLObj = Ai_Application_Mlc_PnPLAlloc();
pAi_Application_Ispu_PnPLObj = Ai_Application_Ispu_PnPLAlloc();
pController_PnPLObj = Controller_PnPLAlloc();
pDeviceinformation_PnPLObj = Deviceinformation_PnPLAlloc();

/* --- Init and Add PnPL Components to PnPL Component Manager */
Ism330dhcx_Acc_PnPLInit(pIsm330dhcx_Acc_PnPLObj);
Firmware_Info_PnPLInit(pFirmware_Info_PnPLObj);
Ai_Application_Mcu_PnPLInit(pAi_Application_Mcu_PnPLObj, &iAi_Application_Mcu);
Ai_Application_Mlc_PnPLInit(pAi_Application_Mlc_PnPLObj, &iAi_Application_Mlc);
Ai_Application_Ispu_PnPLInit(pAi_Application_Ispu_PnPLObj, &iAi_Application_Ispu);
Controller_PnPLInit(pController_PnPLObj, &iController);
Deviceinformation_PnPLInit(pDeviceinformation_PnPLObj);

/* [MODE 2] End of initialization code -------------------------------------- */

/* EXAMPLE of PnPL messages handling ---------------------------------------- */
/* Parse/Serialize received PnPL messages (Get Status, Set Properties or Commands) */

/* PnPLCommand object declaration */
PnPLCommand_t PnPLCommand;

/* Parse received input message. (received_msg is the received input message to parse) */
PnPLParseCommand((char *)received_msg, &PnPLCommand);

/* PnPLCommand object is filled by the PnPLParseCommand function.*/
if(PnPLCommand.comm_type == PNPL_CMD_GET)   /* Check PnPLCommand type. If it is a GET Message, generate a response.*/
{

  /* Declare Serialized JSON response message and size */
  char *SerializedJSON;
  uint32_t size;

  /* Serialize message response */
  PnPLSerializeResponse(&PnPLCommand, &SerializedJSON, &size,0);

  /* --> SerializedJSON contains the serialized message and size contains the serialized message size */
  /* User code to send the serialized message response */
}
/* -------------------------------------------------------------------------- */

/* EXAMPLE of PnPL Telemetry handling --------------------------------------- */
/* Creation of a PnPL Telemetry message with N fields*/

/* Declare telemetry message and size */
char *telemetry = NULL;
uint32_t size;

/* Telemetry field values (they could be int, float, bool or char*) */
int telemetry_field_1 = <an_integer_value>;
/* ... */
float telemetry_field_N = <a_string_value>;

/* Create the PnPL Telemetry message using the dedicated Component <comp_name> function defined in App_model*/
<comp_name>_create_telemetry(telemetry_field_1, ..., telemetry_field_N, &telemetry, &size);

/* Check null pointer exception */
if(telemetry)
{
  /* User Code to send PnPL Telemetry via a Communication interface */

  /* Clear telemetry msg after sending */
  json_free_serialized_string(telemetry);
}
/* -------------------------------------------------------------------------- */
