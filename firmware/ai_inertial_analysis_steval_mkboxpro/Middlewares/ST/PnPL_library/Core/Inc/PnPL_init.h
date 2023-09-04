/**
  ******************************************************************************
  * @file    PnPL_Init.h
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

#ifndef PNPL_INIT_H_
#define PNPL_INIT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "PnPLCompManager.h"
#include "Lsm6dsv16x_Acc_PnPL.h"
#include "Firmware_Info_PnPL.h"
#include "Ai_Application_Mcu_PnPL.h"
#include "Ai_Application_Mlc_PnPL.h"
#include "Ai_Application_Ispu_PnPL.h"
#include "Controller_PnPL.h"
#include "Deviceinformation_PnPL.h"

#include "IAi_Application_Mcu.h"
#include "IAi_Application_Mcu_vtbl.h"
#include "IAi_Application_Mlc.h"
#include "IAi_Application_Mlc_vtbl.h"
#include "IAi_Application_Ispu.h"
#include "IAi_Application_Ispu_vtbl.h"
#include "IController.h"
#include "IController_vtbl.h"


uint8_t PnPL_Components_Alloc();
uint8_t PnPL_Components_Init(IAi_Application_Mcu_t iAi_Application_Mcu, IAi_Application_Mlc_t iAi_Application_Mlc, IAi_Application_Ispu_t iAi_Application_Ispu, IController_t iController);


#ifdef __cplusplus
}
#endif

#endif /* PNPL_INIT_H_ */
