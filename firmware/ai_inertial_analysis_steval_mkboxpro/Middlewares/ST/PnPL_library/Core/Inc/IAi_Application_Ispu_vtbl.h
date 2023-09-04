/**
  ******************************************************************************
  * @file    IAi_Application_Ispu_vtbl.h
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

#ifndef INCLUDE_IAI_APPLICATION_ISPU_VTBL_H_
#define INCLUDE_IAI_APPLICATION_ISPU_VTBL_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
  * Create a type name for IAi_Application_Ispu_vtbl.
  */
typedef struct _IAi_Application_Ispu_vtbl IAi_Application_Ispu_vtbl;

struct _IAi_Application_Ispu_vtbl
{
  uint8_t (*ai_application_ispu_start)(IAi_Application_Ispu_t * _this);
  uint8_t (*ai_application_ispu_stop)(IAi_Application_Ispu_t * _this);
  uint8_t (*ai_application_ispu_load_ucf)(IAi_Application_Ispu_t * _this, uint32_t ucf_content_size, const char *ucf_content);
};

struct _IAi_Application_Ispu_t
{
  /**
    * Pointer to the virtual table for the class.
    */
  const IAi_Application_Ispu_vtbl *vptr;
};

/* Inline functions definition -----------------------------------------------*/
inline uint8_t IAi_Application_Ispu_start(IAi_Application_Ispu_t *_this)
{
  return _this->vptr->ai_application_ispu_start(_this);
}
inline uint8_t IAi_Application_Ispu_stop(IAi_Application_Ispu_t *_this)
{
  return _this->vptr->ai_application_ispu_stop(_this);
}
inline uint8_t IAi_Application_Ispu_load_ucf(IAi_Application_Ispu_t *_this, uint32_t ucf_content_size, const char *ucf_content)
{
  return _this->vptr->ai_application_ispu_load_ucf(_this, ucf_content_size, ucf_content);
}

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_IAI_APPLICATION_ISPU_VTBL_H_ */