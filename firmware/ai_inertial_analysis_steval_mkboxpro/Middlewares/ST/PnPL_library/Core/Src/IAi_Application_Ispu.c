/**
  ******************************************************************************
  * @file    IAi_Application_Ispu.c
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
  * dtmi:vespucci:steval_stwinbx1:ai_inertial_analysis_steval_stwinbx1:other:ai_application_ispu;1
  *
  * Created by: DTDL2PnPL_cGen version 1.0.0
  *
  * WARNING! All changes made to this file will be lost if this is regenerated
  ******************************************************************************
  */

#include "IAi_Application_Ispu.h"
#include "IAi_Application_Ispu_vtbl.h"

/**
 * GCC requires one function forward declaration in only one .c source
 * in order to manage the inline.
 * See also http://stackoverflow.com/questions/26503235/c-inline-function-and-gcc
 */
#if defined (__GNUC__) || defined(__ICCARM__)
extern uint8_t IAi_Application_Ispu_start(IAi_Application_Ispu_t *_this);
extern uint8_t IAi_Application_Ispu_stop(IAi_Application_Ispu_t *_this);
extern uint8_t IAi_Application_Ispu_load_ucf(IAi_Application_Ispu_t *_this, uint32_t ucf_content_size, const char *ucf_content);
#endif
