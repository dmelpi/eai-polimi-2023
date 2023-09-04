/**
  ******************************************************************************
  * @file    Ai_Application_Mlc_PnPL.c
  * @author  SRA
  * @brief   Ai_Application_Mlc PnPL Component Manager
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
  * dtmi:vespucci:steval_stwinbx1:ai_inertial_analysis_steval_stwinbx1:other:ai_application_mlc;1
  *
  * Created by: DTDL2PnPL_cGen version 1.0.0
  *
  * WARNING! All changes made to this file will be lost if this is regenerated
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "App_model.h"
#include "IPnPLComponent.h"
#include "IPnPLComponent_vtbl.h"
#include "PnPLCompManager.h"

#include "Ai_Application_Mlc_PnPL.h"
#include "Ai_Application_Mlc_PnPL_vtbl.h"

static const IPnPLComponent_vtbl sAi_Application_Mlc_PnPL_CompIF_vtbl =
{
  Ai_Application_Mlc_PnPL_vtblGetKey,
  Ai_Application_Mlc_PnPL_vtblGetNCommands,
  Ai_Application_Mlc_PnPL_vtblGetCommandKey,
  Ai_Application_Mlc_PnPL_vtblGetStatus,
  Ai_Application_Mlc_PnPL_vtblSetProperty,
  Ai_Application_Mlc_PnPL_vtblExecuteFunction
};

/**
  *  Ai_Application_Mlc_PnPL internal structure.
  */
struct _Ai_Application_Mlc_PnPL
{
  /**
    * Implements the IPnPLComponent interface.
    */
  IPnPLComponent_t component_if;
  /**
    * Contains Ai_Application_Mlc functions pointers.
    */
  IAi_Application_Mlc_t *cmdIF;
};

/* Objects instance ----------------------------------------------------------*/
static Ai_Application_Mlc_PnPL sAi_Application_Mlc_PnPL;

/* Public API definition -----------------------------------------------------*/
IPnPLComponent_t *Ai_Application_Mlc_PnPLAlloc()
{
  IPnPLComponent_t *pxObj = (IPnPLComponent_t *) &sAi_Application_Mlc_PnPL;
  if (pxObj != NULL)
  {
    pxObj->vptr = &sAi_Application_Mlc_PnPL_CompIF_vtbl;
  }
  return pxObj;
}

uint8_t Ai_Application_Mlc_PnPLInit(IPnPLComponent_t *_this,  IAi_Application_Mlc_t *inf)
{
  IPnPLComponent_t *component_if = _this;
  PnPLAddComponent(component_if);
  Ai_Application_Mlc_PnPL *p_if_owner = (Ai_Application_Mlc_PnPL *) _this;
  p_if_owner->cmdIF = inf;
  ai_application_mlc_comp_init();
  return 0;
}


/* IPnPLComponent virtual functions definition -------------------------------*/
char *Ai_Application_Mlc_PnPL_vtblGetKey(IPnPLComponent_t *_this)
{
  return ai_application_mlc_get_key();
}

uint8_t Ai_Application_Mlc_PnPL_vtblGetNCommands(IPnPLComponent_t *_this)
{
  return 3;
}

char *Ai_Application_Mlc_PnPL_vtblGetCommandKey(IPnPLComponent_t *_this, uint8_t id)
{
  switch (id)
  {
  case 0:
    return "ai_application_mlc*start";
    break;
  case 1:
    return "ai_application_mlc*stop";
    break;
  case 2:
    return "ai_application_mlc*load_ucf";
    break;
  }
  return 0;
}

uint8_t Ai_Application_Mlc_PnPL_vtblGetStatus(IPnPLComponent_t *_this, char **serializedJSON, uint32_t *size, uint8_t pretty)
{
  JSON_Value *tempJSON;
  JSON_Object *JSON_Status;

  tempJSON = json_value_init_object();
  JSON_Status = json_value_get_object(tempJSON);

  bool temp_b = 0;
  ai_application_mlc_get_enabled(&temp_b);
  json_object_dotset_boolean(JSON_Status, "ai_application_mlc.enabled", temp_b);
  json_object_dotset_number(JSON_Status, "ai_application_mlc.c_type", COMP_TYPE_OTHER);

  if (pretty == 1)
  {
    *serializedJSON = json_serialize_to_string_pretty(tempJSON);
    *size = json_serialization_size_pretty(tempJSON);
  }
  else
  {
    *serializedJSON = json_serialize_to_string(tempJSON);
    *size = json_serialization_size(tempJSON);
  }

  /* No need to free temp_j as it is part of tempJSON */
  json_value_free(tempJSON);

  return 0;
}

uint8_t Ai_Application_Mlc_PnPL_vtblSetProperty(IPnPLComponent_t *_this, char *serializedJSON)
{
  return 0;
}

uint8_t Ai_Application_Mlc_PnPL_vtblExecuteFunction(IPnPLComponent_t *_this, char *serializedJSON)
{
  Ai_Application_Mlc_PnPL *p_if_owner = (Ai_Application_Mlc_PnPL *) _this;
  JSON_Value *tempJSON = json_parse_string(serializedJSON);
  JSON_Object *tempJSONObject = json_value_get_object(tempJSON);
  if (json_object_dothas_value(tempJSONObject, "ai_application_mlc*start"))
  {
    ai_application_mlc_start(p_if_owner->cmdIF);
  }
  if (json_object_dothas_value(tempJSONObject, "ai_application_mlc*stop"))
  {
    ai_application_mlc_stop(p_if_owner->cmdIF);
  }
  if (json_object_dothas_value(tempJSONObject, "ai_application_mlc*load_ucf.arguments"))
  {
    int32_t ucf_content_size;
    const char *ucf_content;
    if (json_object_dothas_value(tempJSONObject, "ai_application_mlc*load_ucf.arguments.ucf_content_size"))
    {
      ucf_content_size =(int32_t) json_object_dotget_number(tempJSONObject, "ai_application_mlc*load_ucf.arguments.ucf_content_size");
      if (json_object_dothas_value(tempJSONObject, "ai_application_mlc*load_ucf.arguments.ucf_content"))
      {
        ucf_content = json_object_dotget_string(tempJSONObject, "ai_application_mlc*load_ucf.arguments.ucf_content");
        ai_application_mlc_load_ucf(p_if_owner->cmdIF, ucf_content_size, (char*) ucf_content);
      }
    }
  }
  json_value_free(tempJSON);
  return 0;
}
