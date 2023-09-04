/**
  ******************************************************************************
  * @file    Controller_PnPL.c
  * @author  SRA
  * @brief   Controller PnPL Component Manager
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

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "App_model.h"
#include "IPnPLComponent.h"
#include "IPnPLComponent_vtbl.h"
#include "PnPLCompManager.h"

#include "Controller_PnPL.h"
#include "Controller_PnPL_vtbl.h"

static const IPnPLComponent_vtbl sController_PnPL_CompIF_vtbl =
{
  Controller_PnPL_vtblGetKey,
  Controller_PnPL_vtblGetNCommands,
  Controller_PnPL_vtblGetCommandKey,
  Controller_PnPL_vtblGetStatus,
  Controller_PnPL_vtblSetProperty,
  Controller_PnPL_vtblExecuteFunction
};

/**
  *  Controller_PnPL internal structure.
  */
struct _Controller_PnPL
{
  /**
    * Implements the IPnPLComponent interface.
    */
  IPnPLComponent_t component_if;
  /**
    * Contains Controller functions pointers.
    */
  IController_t *cmdIF;
};

/* Objects instance ----------------------------------------------------------*/
static Controller_PnPL sController_PnPL;

/* Public API definition -----------------------------------------------------*/
IPnPLComponent_t *Controller_PnPLAlloc()
{
  IPnPLComponent_t *pxObj = (IPnPLComponent_t *) &sController_PnPL;
  if (pxObj != NULL)
  {
    pxObj->vptr = &sController_PnPL_CompIF_vtbl;
  }
  return pxObj;
}

uint8_t Controller_PnPLInit(IPnPLComponent_t *_this,  IController_t *inf)
{
  IPnPLComponent_t *component_if = _this;
  PnPLAddComponent(component_if);
  Controller_PnPL *p_if_owner = (Controller_PnPL *) _this;
  p_if_owner->cmdIF = inf;
  controller_comp_init();
  return 0;
}


/* IPnPLComponent virtual functions definition -------------------------------*/
char *Controller_PnPL_vtblGetKey(IPnPLComponent_t *_this)
{
  return controller_get_key();
}

uint8_t Controller_PnPL_vtblGetNCommands(IPnPLComponent_t *_this)
{
  return 1;
}

char *Controller_PnPL_vtblGetCommandKey(IPnPLComponent_t *_this, uint8_t id)
{
  switch (id)
  {
  case 0:
    return "controller*switch_bank";
    break;
  }
  return 0;
}

uint8_t Controller_PnPL_vtblGetStatus(IPnPLComponent_t *_this, char **serializedJSON, uint32_t *size, uint8_t pretty)
{
  JSON_Value *tempJSON;
  JSON_Object *JSON_Status;

  tempJSON = json_value_init_object();
  JSON_Status = json_value_get_object(tempJSON);

  json_object_dotset_number(JSON_Status, "controller.c_type", COMP_TYPE_OTHER);

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

uint8_t Controller_PnPL_vtblSetProperty(IPnPLComponent_t *_this, char *serializedJSON)
{
  return 0;
}

uint8_t Controller_PnPL_vtblExecuteFunction(IPnPLComponent_t *_this, char *serializedJSON)
{
  Controller_PnPL *p_if_owner = (Controller_PnPL *) _this;
  JSON_Value *tempJSON = json_parse_string(serializedJSON);
  JSON_Object *tempJSONObject = json_value_get_object(tempJSON);
  if (json_object_dothas_value(tempJSONObject, "controller*switch_bank"))
  {
    controller_switch_bank(p_if_owner->cmdIF);
  }
  json_value_free(tempJSON);
  return 0;
}
