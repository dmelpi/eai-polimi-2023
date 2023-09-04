/**
  ******************************************************************************
  * @file    PnPL_Init.c
  * @author  SRA
  * @brief   PnPL Components initialization functions
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

#include "PnPL_Init.h"

static IPnPLComponent_t *pLsm6dsv16x_Acc_PnPLObj = NULL;
static IPnPLComponent_t *pFirmware_Info_PnPLObj = NULL;
static IPnPLComponent_t *pAi_Application_Mcu_PnPLObj = NULL;
static IPnPLComponent_t *pAi_Application_Mlc_PnPLObj = NULL;
static IPnPLComponent_t *pAi_Application_Ispu_PnPLObj = NULL;
static IPnPLComponent_t *pController_PnPLObj = NULL;
static IPnPLComponent_t *pDeviceinformation_PnPLObj = NULL;

uint8_t PnPL_Components_Alloc()
{
  /* PnPL Components Allocation */
  pLsm6dsv16x_Acc_PnPLObj = Lsm6dsv16x_Acc_PnPLAlloc();
  pFirmware_Info_PnPLObj = Firmware_Info_PnPLAlloc();
  pAi_Application_Mcu_PnPLObj = Ai_Application_Mcu_PnPLAlloc();
  pAi_Application_Mlc_PnPLObj = Ai_Application_Mlc_PnPLAlloc();
  pAi_Application_Ispu_PnPLObj = Ai_Application_Ispu_PnPLAlloc();
  pController_PnPLObj = Controller_PnPLAlloc();
  pDeviceinformation_PnPLObj = Deviceinformation_PnPLAlloc();
  return 0;
}

uint8_t PnPL_Components_Init(IAi_Application_Mcu_t iAi_Application_Mcu, IAi_Application_Mlc_t iAi_Application_Mlc, IAi_Application_Ispu_t iAi_Application_Ispu, IController_t iController)
{
  /* Init&Add PnPL Components */
  Lsm6dsv16x_Acc_PnPLInit(pLsm6dsv16x_Acc_PnPLObj);
  Firmware_Info_PnPLInit(pFirmware_Info_PnPLObj);
  Ai_Application_Mcu_PnPLInit(pAi_Application_Mcu_PnPLObj, &iAi_Application_Mcu);
  Ai_Application_Mlc_PnPLInit(pAi_Application_Mlc_PnPLObj, &iAi_Application_Mlc);
  Ai_Application_Ispu_PnPLInit(pAi_Application_Ispu_PnPLObj, &iAi_Application_Ispu);
  Controller_PnPLInit(pController_PnPLObj, &iController);
  Deviceinformation_PnPLInit(pDeviceinformation_PnPLObj);
  return 0;
}
