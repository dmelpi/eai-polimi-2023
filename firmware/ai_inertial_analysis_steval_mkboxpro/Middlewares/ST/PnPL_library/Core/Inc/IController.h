/**
  ******************************************************************************
  * @file    IController.h
  * @author  SRA
  * @brief
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
  * This file has been auto generated from the following DTDL Component:
  * dtmi:vespucci:steval_stwinbx1:ai_inertial_analysis_steval_stwinbx1:other:controller;1
  *
  * Created by: DTDL2PnPL_cGen version 1.0.0
  *
  * WARNING! All changes made to this file will be lost if this is regenerated
  ******************************************************************************
  */

#ifndef INCLUDE_ICONTROLLER_H_
#define INCLUDE_ICONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

/**
  * Create  type name for IController.
  */
typedef struct _IController_t IController_t;

/* Public API declarations ---------------------------------------------------*/

/* Public interface */
inline uint8_t IController_switch_bank(IController_t *_this);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_ICONTROLLER_H_ */
