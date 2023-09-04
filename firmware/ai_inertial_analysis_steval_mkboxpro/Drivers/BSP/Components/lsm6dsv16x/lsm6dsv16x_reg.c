/**
  ******************************************************************************
  * @file    lsm6dsv16x_reg.c
  * @author  Sensors Software Solution Team
  * @brief   LSM6DSV16X driver file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "lsm6dsv16x_reg.h"

/**
  * @defgroup  LSM6DSV16X
  * @brief     This file provides a set of functions needed to drive the
  *            lsm6dsv16x enhanced inertial module.
  * @{
  *
  */

/**
  * @defgroup  Interfaces functions
  * @brief     This section provide a set of functions used to read and
  *            write a generic register of the device.
  *            MANDATORY: return 0 -> no Error.
  * @{
  *
  */

/**
  * @brief  Read generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to read.
  * @param  data  buffer for data read.(ptr)
  * @param  len   number of consecutive register to read.
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_read_reg(stmdev_ctx_t *ctx, uint8_t reg,
                            uint8_t *data,
                            uint16_t len)
{
  int32_t ret;

  ret = ctx->read_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @brief  Write generic device register
  *
  * @param  ctx   communication interface handler.(ptr)
  * @param  reg   first register address to write.
  * @param  data  the buffer contains data to be written.(ptr)
  * @param  len   number of consecutive register to write.
  * @retval       interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_write_reg(stmdev_ctx_t *ctx, uint8_t reg,
                             uint8_t *data,
                             uint16_t len)
{
  int32_t ret;

  ret = ctx->write_reg(ctx->handle, reg, data, len);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Private functions
  * @brief     Section collect all the utility functions needed by APIs.
  * @{
  *
  */

static void bytecpy(uint8_t *target, uint8_t *source)
{
  if ((target != NULL) && (source != NULL))
  {
    *target = *source;
  }
}

/**
  * @}
  *
  */

/**
  * @defgroup  Sensitivity
  * @brief     These functions convert raw-data into engineering units.
  * @{
  *
  */
float_t lsm6dsv16x_from_sflp_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.061f;
}

float_t lsm6dsv16x_from_fs2_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.061f;
}

float_t lsm6dsv16x_from_fs4_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.122f;
}

float_t lsm6dsv16x_from_fs8_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.244f;
}

float_t lsm6dsv16x_from_fs16_to_mg(int16_t lsb)
{
  return ((float_t)lsb) * 0.488f;
}

float_t lsm6dsv16x_from_fs125_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 4.375f;
}

float_t lsm6dsv16x_from_fs250_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 8.750f;
}

float_t lsm6dsv16x_from_fs500_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 17.50f;
}

float_t lsm6dsv16x_from_fs1000_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 35.0f;
}

float_t lsm6dsv16x_from_fs2000_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 70.0f;
}

float_t lsm6dsv16x_from_fs4000_to_mdps(int16_t lsb)
{
  return ((float_t)lsb) * 140.0f;
}

float_t lsm6dsv16x_from_lsb_to_celsius(int16_t lsb)
{
  return (((float_t)lsb / 256.0f) + 25.0f);
}

float_t lsm6dsv16x_from_lsb_to_nsec(uint32_t lsb)
{
  return ((float_t)lsb * 21750.0f);
}

/**
  * @}
  *
  */

/**
  * @defgroup  Accelerometer user offset correction
  * @brief      This section groups all the functions concerning the
  *             usage of Accelerometer user offset correction
  * @{
  *
  */

/**
  * @brief  Enables accelerometer user offset correction block; it is valid for the low-pass path.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables accelerometer user offset correction block; it is valid for the low-pass path.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_offset_on_out_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  if (ret == 0)
  {
    ctrl9.usr_off_on_out = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  }

  return ret;
}

/**
  * @brief  Enables accelerometer user offset correction block; it is valid for the low-pass path.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables accelerometer user offset correction block; it is valid for the low-pass path.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_offset_on_out_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  *val = ctrl9.usr_off_on_out;

  return ret;
}

/**
  * @brief  Accelerometer user offset correction values in mg.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Accelerometer user offset correction values in mg.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_offset_mg_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_xl_offset_mg_t val)
{
  lsm6dsv16x_z_ofs_usr_t z_ofs_usr;
  lsm6dsv16x_y_ofs_usr_t y_ofs_usr;
  lsm6dsv16x_x_ofs_usr_t x_ofs_usr;
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;
  float_t tmp;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_Z_OFS_USR, (uint8_t *)&z_ofs_usr, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_Y_OFS_USR, (uint8_t *)&y_ofs_usr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_X_OFS_USR, (uint8_t *)&x_ofs_usr, 1);
  }


  if ((val.x_mg < (0.0078125f * 127.0f)) && (val.x_mg > (0.0078125f * -127.0f)) &&
      (val.y_mg < (0.0078125f * 127.0f)) && (val.y_mg > (0.0078125f * -127.0f)) &&
      (val.z_mg < (0.0078125f * 127.0f)) && (val.z_mg > (0.0078125f * -127.0f)))
  {
    ctrl9.usr_off_w = 0;

    tmp = val.z_mg / 0.0078125f;
    z_ofs_usr.z_ofs_usr = (uint8_t)tmp;

    tmp = val.y_mg / 0.0078125f;
    y_ofs_usr.y_ofs_usr = (uint8_t)tmp;

    tmp = val.x_mg / 0.0078125f;
    x_ofs_usr.x_ofs_usr = (uint8_t)tmp;
  }
  else if ((val.x_mg < (0.125f * 127.0f)) && (val.x_mg > (0.125f * -127.0f)) &&
           (val.y_mg < (0.125f * 127.0f)) && (val.y_mg > (0.125f * -127.0f)) &&
           (val.z_mg < (0.125f * 127.0f)) && (val.z_mg > (0.125f * -127.0f)))
  {
    ctrl9.usr_off_w = 1;

    tmp = val.z_mg / 0.125f;
    z_ofs_usr.z_ofs_usr = (uint8_t)tmp;

    tmp = val.y_mg / 0.125f;
    y_ofs_usr.y_ofs_usr = (uint8_t)tmp;

    tmp = val.x_mg / 0.125f;
    x_ofs_usr.x_ofs_usr = (uint8_t)tmp;
  }
  else // out of limit
  {
    ctrl9.usr_off_w = 1;
    z_ofs_usr.z_ofs_usr = 0xFFU;
    y_ofs_usr.y_ofs_usr = 0xFFU;
    x_ofs_usr.x_ofs_usr = 0xFFU;
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_Z_OFS_USR, (uint8_t *)&z_ofs_usr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_Y_OFS_USR, (uint8_t *)&y_ofs_usr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_X_OFS_USR, (uint8_t *)&x_ofs_usr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  }
  return ret;
}

/**
  * @brief  Accelerometer user offset correction values in mg.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Accelerometer user offset correction values in mg.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_offset_mg_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_xl_offset_mg_t *val)
{
  lsm6dsv16x_z_ofs_usr_t z_ofs_usr;
  lsm6dsv16x_y_ofs_usr_t y_ofs_usr;
  lsm6dsv16x_x_ofs_usr_t x_ofs_usr;
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_Z_OFS_USR, (uint8_t *)&z_ofs_usr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_Y_OFS_USR, (uint8_t *)&y_ofs_usr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_X_OFS_USR, (uint8_t *)&x_ofs_usr, 1);
  }

  if (ctrl9.usr_off_w == PROPERTY_DISABLE)
  {
    val->z_mg = ((float_t)z_ofs_usr.z_ofs_usr * 0.0078125f);
    val->y_mg = ((float_t)y_ofs_usr.y_ofs_usr * 0.0078125f);
    val->x_mg = ((float_t)x_ofs_usr.x_ofs_usr * 0.0078125f);
  }
  else
  {
    val->z_mg = ((float_t)z_ofs_usr.z_ofs_usr * 0.125f);
    val->y_mg = ((float_t)y_ofs_usr.y_ofs_usr * 0.125f);
    val->x_mg = ((float_t)x_ofs_usr.x_ofs_usr * 0.125f);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @brief  Reset of the device.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Reset of the device.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_reset_set(stmdev_ctx_t *ctx, lsm6dsv16x_reset_t val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  lsm6dsv16x_ctrl3_t ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL3, (uint8_t *)&ctrl3, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  }

  ctrl3.boot = ((uint8_t)val & 0x04U) >> 2;
  ctrl3.sw_reset = ((uint8_t)val & 0x02U) >> 1;
  func_cfg_access.sw_por = (uint8_t)val & 0x01U;

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL3, (uint8_t *)&ctrl3, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  }

  return ret;
}

/**
  * @brief  Global reset of the device.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Global reset of the device.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_reset_get(stmdev_ctx_t *ctx, lsm6dsv16x_reset_t *val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  lsm6dsv16x_ctrl3_t ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL3, (uint8_t *)&ctrl3, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  }

  switch ((ctrl3.sw_reset << 2) + (ctrl3.boot << 1) + func_cfg_access.sw_por)
  {
    case LSM6DSV16X_READY:
      *val = LSM6DSV16X_READY;
      break;

    case LSM6DSV16X_GLOBAL_RST:
      *val = LSM6DSV16X_GLOBAL_RST;
      break;

    case LSM6DSV16X_RESTORE_CAL_PARAM:
      *val = LSM6DSV16X_RESTORE_CAL_PARAM;
      break;

    case LSM6DSV16X_RESTORE_CTRL_REGS:
      *val = LSM6DSV16X_RESTORE_CTRL_REGS;
      break;

    default:
      *val = LSM6DSV16X_GLOBAL_RST;
      break;
  }
  return ret;
}

/**
  * @brief  Change memory bank.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      MAIN_MEM_BANK, EMBED_FUNC_MEM_BANK,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mem_bank_set(stmdev_ctx_t *ctx, lsm6dsv16x_mem_bank_t val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);

  if (ret == 0)
  {
    func_cfg_access.shub_reg_access = ((uint8_t)val & 0x02U) >> 1;
    func_cfg_access.emb_func_reg_access = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  }

  return ret;
}

/**
  * @brief  Change memory bank.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      MAIN_MEM_BANK, SENSOR_HUB_MEM_BANK, EMBED_FUNC_MEM_BANK,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mem_bank_get(stmdev_ctx_t *ctx, lsm6dsv16x_mem_bank_t *val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);

  switch ((func_cfg_access.shub_reg_access << 1) + func_cfg_access.emb_func_reg_access)
  {
    case LSM6DSV16X_MAIN_MEM_BANK:
      *val = LSM6DSV16X_MAIN_MEM_BANK;
      break;

    case LSM6DSV16X_EMBED_FUNC_MEM_BANK:
      *val = LSM6DSV16X_EMBED_FUNC_MEM_BANK;
      break;

    case LSM6DSV16X_SENSOR_HUB_MEM_BANK:
      *val = LSM6DSV16X_SENSOR_HUB_MEM_BANK;
      break;

    default:
      *val = LSM6DSV16X_MAIN_MEM_BANK;
      break;
  }
  return ret;
}

/**
  * @brief  Device ID.[get] THis function works also for OIS
  *        (WHO_AM_I and SPI2_WHO_AM_I have same address)
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Device ID.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_device_id_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WHO_AM_I, val, 1);

  return ret;
}

/**
  * @brief  Accelerometer output data rate (ODR) selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ODR_OFF, XL_ODR_AT_1Hz875, XL_ODR_AT_7Hz5, XL_ODR_AT_15Hz, XL_ODR_AT_30Hz, XL_ODR_AT_60Hz, XL_ODR_AT_120Hz, XL_ODR_AT_240Hz, XL_ODR_AT_480Hz, XL_ODR_AT_960Hz, XL_ODR_AT_1920Hz, XL_ODR_AT_3840Hz, XL_ODR_AT_7680Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_data_rate_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_xl_data_rate_t val)
{
  lsm6dsv16x_ctrl1_t ctrl1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL1, (uint8_t *)&ctrl1, 1);
  if (ret == 0)
  {
    ctrl1.odr_xl = (uint8_t)val & 0x0Fu;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL1, (uint8_t *)&ctrl1, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer output data rate (ODR) selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ODR_OFF, XL_ODR_AT_1Hz875, XL_ODR_AT_7Hz5, XL_ODR_AT_15Hz, XL_ODR_AT_30Hz, XL_ODR_AT_60Hz, XL_ODR_AT_120Hz, XL_ODR_AT_240Hz, XL_ODR_AT_480Hz, XL_ODR_AT_960Hz, XL_ODR_AT_1920Hz, XL_ODR_AT_3840Hz, XL_ODR_AT_7680Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_data_rate_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_xl_data_rate_t *val)
{
  lsm6dsv16x_ctrl1_t ctrl1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL1, (uint8_t *)&ctrl1, 1);

  switch (ctrl1.odr_xl)
  {
    case LSM6DSV16X_XL_ODR_OFF:
      *val = LSM6DSV16X_XL_ODR_OFF;
      break;

    case LSM6DSV16X_XL_ODR_AT_1Hz875:
      *val = LSM6DSV16X_XL_ODR_AT_1Hz875;
      break;

    case LSM6DSV16X_XL_ODR_AT_7Hz5:
      *val = LSM6DSV16X_XL_ODR_AT_7Hz5;
      break;

    case LSM6DSV16X_XL_ODR_AT_15Hz:
      *val = LSM6DSV16X_XL_ODR_AT_15Hz;
      break;

    case LSM6DSV16X_XL_ODR_AT_30Hz:
      *val = LSM6DSV16X_XL_ODR_AT_30Hz;
      break;

    case LSM6DSV16X_XL_ODR_AT_60Hz:
      *val = LSM6DSV16X_XL_ODR_AT_60Hz;
      break;

    case LSM6DSV16X_XL_ODR_AT_120Hz:
      *val = LSM6DSV16X_XL_ODR_AT_120Hz;
      break;

    case LSM6DSV16X_XL_ODR_AT_240Hz:
      *val = LSM6DSV16X_XL_ODR_AT_240Hz;
      break;

    case LSM6DSV16X_XL_ODR_AT_480Hz:
      *val = LSM6DSV16X_XL_ODR_AT_480Hz;
      break;

    case LSM6DSV16X_XL_ODR_AT_960Hz:
      *val = LSM6DSV16X_XL_ODR_AT_960Hz;
      break;

    case LSM6DSV16X_XL_ODR_AT_1920Hz:
      *val = LSM6DSV16X_XL_ODR_AT_1920Hz;
      break;

    case LSM6DSV16X_XL_ODR_AT_3840Hz:
      *val = LSM6DSV16X_XL_ODR_AT_3840Hz;
      break;

    case LSM6DSV16X_XL_ODR_AT_7680Hz:
      *val = LSM6DSV16X_XL_ODR_AT_7680Hz;
      break;

    default:
      *val = LSM6DSV16X_XL_ODR_OFF;
      break;
  }
  return ret;
}

/**
  * @brief  Accelerometer operating mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_HIGH_PERFORMANCE_MD, XL_HIGH_ACCURANCY_ODR_MD, XL_LOW_POWER_2_AVG_MD, XL_LOW_POWER_4_AVG_MD, XL_LOW_POWER_8_AVG_MD, XL_NORMAL_MD,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_mode_set(stmdev_ctx_t *ctx, lsm6dsv16x_xl_mode_t val)
{
  lsm6dsv16x_ctrl1_t ctrl1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL1, (uint8_t *)&ctrl1, 1);

  if (ret == 0)
  {
    ctrl1.op_mode_xl = (uint8_t)val & 0x07U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL1, (uint8_t *)&ctrl1, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer operating mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_HIGH_PERFORMANCE_MD, XL_HIGH_ACCURANCY_ODR_MD, XL_LOW_POWER_2_AVG_MD, XL_LOW_POWER_4_AVG_MD, XL_LOW_POWER_8_AVG_MD, XL_NORMAL_MD,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_mode_get(stmdev_ctx_t *ctx, lsm6dsv16x_xl_mode_t *val)
{
  lsm6dsv16x_ctrl1_t ctrl1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL1, (uint8_t *)&ctrl1, 1);

  switch (ctrl1.op_mode_xl)
  {
    case LSM6DSV16X_XL_HIGH_PERFORMANCE_MD:
      *val = LSM6DSV16X_XL_HIGH_PERFORMANCE_MD;
      break;

    case LSM6DSV16X_XL_HIGH_ACCURANCY_ODR_MD:
      *val = LSM6DSV16X_XL_HIGH_ACCURANCY_ODR_MD;
      break;

    case LSM6DSV16X_XL_LOW_POWER_2_AVG_MD:
      *val = LSM6DSV16X_XL_LOW_POWER_2_AVG_MD;
      break;

    case LSM6DSV16X_XL_LOW_POWER_4_AVG_MD:
      *val = LSM6DSV16X_XL_LOW_POWER_4_AVG_MD;
      break;

    case LSM6DSV16X_XL_LOW_POWER_8_AVG_MD:
      *val = LSM6DSV16X_XL_LOW_POWER_8_AVG_MD;
      break;

    case LSM6DSV16X_XL_NORMAL_MD:
      *val = LSM6DSV16X_XL_NORMAL_MD;
      break;

    default:
      *val = LSM6DSV16X_XL_HIGH_PERFORMANCE_MD;
      break;
  }
  return ret;
}

/**
  * @brief  Gyroscope output data rate (ODR) selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_ODR_OFF, GY_ODR_AT_7Hz5, GY_ODR_AT_15Hz, GY_ODR_AT_30Hz, GY_ODR_AT_60Hz, GY_ODR_AT_120Hz, GY_ODR_AT_240Hz, GY_ODR_AT_480Hz, GY_ODR_AT_960Hz, GY_ODR_AT_1920Hz, GY_ODR_AT_3840Hz, GY_ODR_AT_7680Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_data_rate_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_gy_data_rate_t val)
{
  lsm6dsv16x_ctrl2_t ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL2, (uint8_t *)&ctrl2, 1);

  if (ret == 0)
  {
    ctrl2.odr_g = (uint8_t)val & 0x0Fu;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL2, (uint8_t *)&ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope output data rate (ODR) selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_ODR_OFF, GY_ODR_AT_7Hz5, GY_ODR_AT_15Hz, GY_ODR_AT_30Hz, GY_ODR_AT_60Hz, GY_ODR_AT_120Hz, GY_ODR_AT_240Hz, GY_ODR_AT_480Hz, GY_ODR_AT_960Hz, GY_ODR_AT_1920Hz, GY_ODR_AT_3840Hz, GY_ODR_AT_7680Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_data_rate_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_gy_data_rate_t *val)
{
  lsm6dsv16x_ctrl2_t ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL2, (uint8_t *)&ctrl2, 1);

  switch (ctrl2.odr_g)
  {
    case LSM6DSV16X_GY_ODR_OFF:
      *val = LSM6DSV16X_GY_ODR_OFF;
      break;

    case LSM6DSV16X_GY_ODR_AT_7Hz5:
      *val = LSM6DSV16X_GY_ODR_AT_7Hz5;
      break;

    case LSM6DSV16X_GY_ODR_AT_15Hz:
      *val = LSM6DSV16X_GY_ODR_AT_15Hz;
      break;

    case LSM6DSV16X_GY_ODR_AT_30Hz:
      *val = LSM6DSV16X_GY_ODR_AT_30Hz;
      break;

    case LSM6DSV16X_GY_ODR_AT_60Hz:
      *val = LSM6DSV16X_GY_ODR_AT_60Hz;
      break;

    case LSM6DSV16X_GY_ODR_AT_120Hz:
      *val = LSM6DSV16X_GY_ODR_AT_120Hz;
      break;

    case LSM6DSV16X_GY_ODR_AT_240Hz:
      *val = LSM6DSV16X_GY_ODR_AT_240Hz;
      break;

    case LSM6DSV16X_GY_ODR_AT_480Hz:
      *val = LSM6DSV16X_GY_ODR_AT_480Hz;
      break;

    case LSM6DSV16X_GY_ODR_AT_960Hz:
      *val = LSM6DSV16X_GY_ODR_AT_960Hz;
      break;

    case LSM6DSV16X_GY_ODR_AT_1920Hz:
      *val = LSM6DSV16X_GY_ODR_AT_1920Hz;
      break;

    case LSM6DSV16X_GY_ODR_AT_3840Hz:
      *val = LSM6DSV16X_GY_ODR_AT_3840Hz;
      break;

    case LSM6DSV16X_GY_ODR_AT_7680Hz:
      *val = LSM6DSV16X_GY_ODR_AT_7680Hz;
      break;

    default:
      *val = LSM6DSV16X_GY_ODR_OFF;
      break;
  }
  return ret;
}

/**
  * @brief  Gyroscope operating mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_HIGH_PERFORMANCE_MD, GY_HIGH_ACCURANCY_ODR_MD, GY_SLEEP_MD, GY_LOW_POWER_MD,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_mode_set(stmdev_ctx_t *ctx, lsm6dsv16x_gy_mode_t val)
{
  lsm6dsv16x_ctrl2_t ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL2, (uint8_t *)&ctrl2, 1);
  if (ret == 0)
  {
    ctrl2.op_mode_g = (uint8_t)val & 0x07U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL2, (uint8_t *)&ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope operating mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_HIGH_PERFORMANCE_MD, GY_HIGH_ACCURANCY_ODR_MD, GY_SLEEP_MD, GY_LOW_POWER_MD,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_mode_get(stmdev_ctx_t *ctx, lsm6dsv16x_gy_mode_t *val)
{
  lsm6dsv16x_ctrl2_t ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL2, (uint8_t *)&ctrl2, 1);
  switch (ctrl2.op_mode_g)
  {
    case LSM6DSV16X_GY_HIGH_PERFORMANCE_MD:
      *val = LSM6DSV16X_GY_HIGH_PERFORMANCE_MD;
      break;

    case LSM6DSV16X_GY_HIGH_ACCURANCY_ODR_MD:
      *val = LSM6DSV16X_GY_HIGH_ACCURANCY_ODR_MD;
      break;

    case LSM6DSV16X_GY_SLEEP_MD:
      *val = LSM6DSV16X_GY_SLEEP_MD;
      break;

    case LSM6DSV16X_GY_LOW_POWER_MD:
      *val = LSM6DSV16X_GY_LOW_POWER_MD;
      break;

    default:
      *val = LSM6DSV16X_GY_HIGH_PERFORMANCE_MD;
      break;
  }
  return ret;
}

/**
  * @brief  Register address automatically incremented during a multiple byte access with a serial interface (enable by default).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Register address automatically incremented during a multiple byte access with a serial interface (enable by default).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_auto_increment_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl3_t ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL3, (uint8_t *)&ctrl3, 1);
  if (ret == 0)
  {
    ctrl3.if_inc = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL3, (uint8_t *)&ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Register address automatically incremented during a multiple byte access with a serial interface (enable by default).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Register address automatically incremented during a multiple byte access with a serial interface (enable by default).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_auto_increment_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl3_t ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL3, (uint8_t *)&ctrl3, 1);
  *val = ctrl3.if_inc;


  return ret;
}

/**
  * @brief  Block Data Update (BDU): output registers are not updated until LSB and MSB have been read). [set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Block Data Update (BDU): output registers are not updated until LSB and MSB have been read).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_block_data_update_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl3_t ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL3, (uint8_t *)&ctrl3, 1);

  if (ret == 0)
  {
    ctrl3.bdu = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL3, (uint8_t *)&ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Block Data Update (BDU): output registers are not updated until LSB and MSB have been read). [get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Block Data Update (BDU): output registers are not updated until LSB and MSB have been read).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_block_data_update_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl3_t ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL3, (uint8_t *)&ctrl3, 1);
  *val = ctrl3.bdu;

  return ret;
}

/**
  * @brief  Enables pulsed data-ready mode (~75 us).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DRDY_LATCHED, DRDY_PULSED,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_data_ready_mode_set(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_data_ready_mode_t val)
{
  lsm6dsv16x_ctrl4_t ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL4, (uint8_t *)&ctrl4, 1);

  if (ret == 0)
  {
    ctrl4.drdy_pulsed = (uint8_t)val & 0x1U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL4, (uint8_t *)&ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  Enables pulsed data-ready mode (~75 us).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DRDY_LATCHED, DRDY_PULSED,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_data_ready_mode_get(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_data_ready_mode_t *val)
{
  lsm6dsv16x_ctrl4_t ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL4, (uint8_t *)&ctrl4, 1);

  switch (ctrl4.drdy_pulsed)
  {
    case LSM6DSV16X_DRDY_LATCHED:
      *val = LSM6DSV16X_DRDY_LATCHED;
      break;

    case LSM6DSV16X_DRDY_PULSED:
      *val = LSM6DSV16X_DRDY_PULSED;
      break;

    default:
      *val = LSM6DSV16X_DRDY_LATCHED;
      break;
  }
  return ret;
}

/**
  * @brief  Gyroscope full-scale selection[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      125dps, 250dps, 500dps, 1000dps, 2000dps, 4000dps,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_full_scale_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_gy_full_scale_t val)
{
  lsm6dsv16x_ctrl6_t ctrl6;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL6, (uint8_t *)&ctrl6, 1);

  if (ret == 0)
  {
    ctrl6.fs_g = (uint8_t)val & 0xfu;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL6, (uint8_t *)&ctrl6, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope full-scale selection[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      125dps, 250dps, 500dps, 1000dps, 2000dps, 4000dps,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_full_scale_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_gy_full_scale_t *val)
{
  lsm6dsv16x_ctrl6_t ctrl6;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL6, (uint8_t *)&ctrl6, 1);

  switch (ctrl6.fs_g)
  {
    case LSM6DSV16X_125dps:
      *val = LSM6DSV16X_125dps;
      break;

    case LSM6DSV16X_250dps:
      *val = LSM6DSV16X_250dps;
      break;

    case LSM6DSV16X_500dps:
      *val = LSM6DSV16X_500dps;
      break;

    case LSM6DSV16X_1000dps:
      *val = LSM6DSV16X_1000dps;
      break;

    case LSM6DSV16X_2000dps:
      *val = LSM6DSV16X_2000dps;
      break;

    case LSM6DSV16X_4000dps:
      *val = LSM6DSV16X_4000dps;
      break;

    default:
      *val = LSM6DSV16X_125dps;
      break;
  }
  return ret;
}

/**
  * @brief  Accelerometer full-scale selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      2g, 4g, 8g, 16g,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_full_scale_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_xl_full_scale_t val)
{
  lsm6dsv16x_ctrl8_t ctrl8;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL8, (uint8_t *)&ctrl8, 1);

  if (ret == 0)
  {
    ctrl8.fs_xl = (uint8_t)val & 0x3U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL8, (uint8_t *)&ctrl8, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer full-scale selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      2g, 4g, 8g, 16g,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_full_scale_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_xl_full_scale_t *val)
{
  lsm6dsv16x_ctrl8_t ctrl8;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL8, (uint8_t *)&ctrl8, 1);

  switch (ctrl8.fs_xl)
  {
    case LSM6DSV16X_2g:
      *val = LSM6DSV16X_2g;
      break;

    case LSM6DSV16X_4g:
      *val = LSM6DSV16X_4g;
      break;

    case LSM6DSV16X_8g:
      *val = LSM6DSV16X_8g;
      break;

    case LSM6DSV16X_16g:
      *val = LSM6DSV16X_16g;
      break;

    default:
      *val = LSM6DSV16X_2g;
      break;
  }
  return ret;
}

/**
  * @brief  It enables the accelerometer Dual channel mode: data with selected full scale and data with maximum full scale are sent simultaneously to two different set of output registers.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      It enables the accelerometer Dual channel mode: data with selected full scale and data with maximum full scale are sent simultaneously to two different set of output registers.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_dual_channel_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl8_t ctrl8;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL8, (uint8_t *)&ctrl8, 1);

  if (ret == 0)
  {
    ctrl8.xl_dualc_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL8, (uint8_t *)&ctrl8, 1);
  }

  return ret;
}

/**
  * @brief  It enables the accelerometer Dual channel mode: data with selected full scale and data with maximum full scale are sent simultaneously to two different set of output registers.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      It enables the accelerometer Dual channel mode: data with selected full scale and data with maximum full scale are sent simultaneously to two different set of output registers.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_dual_channel_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl8_t ctrl8;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL8, (uint8_t *)&ctrl8, 1);
  *val = ctrl8.xl_dualc_en;

  return ret;
}

/**
  * @brief  Accelerometer self-test selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ST_DISABLE, XL_ST_POSITIVE, XL_ST_NEGATIVE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_self_test_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_xl_self_test_t val)
{
  lsm6dsv16x_ctrl10_t ctrl10;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);

  if (ret == 0)
  {
    ctrl10.st_xl = (uint8_t)val & 0x3U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer self-test selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ST_DISABLE, XL_ST_POSITIVE, XL_ST_NEGATIVE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_xl_self_test_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_xl_self_test_t *val)
{
  lsm6dsv16x_ctrl10_t ctrl10;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);

  switch (ctrl10.st_xl)
  {
    case LSM6DSV16X_XL_ST_DISABLE:
      *val = LSM6DSV16X_XL_ST_DISABLE;
      break;

    case LSM6DSV16X_XL_ST_POSITIVE:
      *val = LSM6DSV16X_XL_ST_POSITIVE;
      break;

    case LSM6DSV16X_XL_ST_NEGATIVE:
      *val = LSM6DSV16X_XL_ST_NEGATIVE;
      break;

    default:
      *val = LSM6DSV16X_XL_ST_DISABLE;
      break;
  }
  return ret;
}

/**
  * @brief  Gyroscope self-test selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ST_DISABLE, XL_ST_POSITIVE, XL_ST_NEGATIVE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_self_test_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_gy_self_test_t val)
{
  lsm6dsv16x_ctrl10_t ctrl10;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);

  if (ret == 0)
  {
    ctrl10.st_g = (uint8_t)val & 0x3U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope self-test selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ST_DISABLE, XL_ST_POSITIVE, XL_ST_NEGATIVE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_self_test_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_gy_self_test_t *val)
{
  lsm6dsv16x_ctrl10_t ctrl10;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);

  switch (ctrl10.st_g)
  {
    case LSM6DSV16X_GY_ST_DISABLE:
      *val = LSM6DSV16X_GY_ST_DISABLE;
      break;

    case LSM6DSV16X_GY_ST_POSITIVE:
      *val = LSM6DSV16X_GY_ST_POSITIVE;
      break;

    case LSM6DSV16X_GY_ST_NEGATIVE:
      *val = LSM6DSV16X_GY_ST_NEGATIVE;
      break;

    default:
      *val = LSM6DSV16X_GY_ST_DISABLE;
      break;
  }
  return ret;
}

/**
  * @brief  SPI2 Accelerometer self-test selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ST_DISABLE, XL_ST_POSITIVE, XL_ST_NEGATIVE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_xl_self_test_set(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_ois_xl_self_test_t val)
{
  lsm6dsv16x_spi2_int_ois_t spi2_int_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SPI2_INT_OIS, (uint8_t *)&spi2_int_ois, 1);

  if (ret == 0)
  {
    spi2_int_ois.st_xl_ois = ((uint8_t)val & 0x3U);
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SPI2_INT_OIS, (uint8_t *)&spi2_int_ois, 1);
  }

  return ret;
}

/**
  * @brief  SPI2 Accelerometer self-test selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ST_DISABLE, XL_ST_POSITIVE, XL_ST_NEGATIVE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_xl_self_test_get(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_ois_xl_self_test_t *val)
{
  lsm6dsv16x_spi2_int_ois_t spi2_int_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SPI2_INT_OIS, (uint8_t *)&spi2_int_ois, 1);

  switch (spi2_int_ois.st_xl_ois)
  {
    case LSM6DSV16X_OIS_XL_ST_DISABLE:
      *val = LSM6DSV16X_OIS_XL_ST_DISABLE;
      break;

    case LSM6DSV16X_OIS_XL_ST_POSITIVE:
      *val = LSM6DSV16X_OIS_XL_ST_POSITIVE;
      break;

    case LSM6DSV16X_OIS_XL_ST_NEGATIVE:
      *val = LSM6DSV16X_OIS_XL_ST_NEGATIVE;
      break;

    default:
      *val = LSM6DSV16X_OIS_XL_ST_DISABLE;
      break;
  }
  return ret;
}

/**
  * @brief  SPI2 Accelerometer self-test selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_ST_DISABLE, GY_ST_POSITIVE, GY_ST_NEGATIVE, LSM6DSV16X_OIS_GY_ST_CLAMP_POS, LSM6DSV16X_OIS_GY_ST_CLAMP_NEG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_gy_self_test_set(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_ois_gy_self_test_t val)
{
  lsm6dsv16x_spi2_int_ois_t spi2_int_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SPI2_INT_OIS, (uint8_t *)&spi2_int_ois, 1);

  if (ret == 0)
  {
    spi2_int_ois.st_g_ois = ((uint8_t)val & 0x3U);
    spi2_int_ois.st_ois_clampdis = ((uint8_t)val & 0x04U) >> 2;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SPI2_INT_OIS, (uint8_t *)&spi2_int_ois, 1);
  }

  return ret;
}

/**
  * @brief  SPI2 Accelerometer self-test selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_ST_DISABLE, GY_ST_POSITIVE, GY_ST_NEGATIVE, LSM6DSV16X_OIS_GY_ST_CLAMP_POS, LSM6DSV16X_OIS_GY_ST_CLAMP_NEG
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_gy_self_test_get(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_ois_gy_self_test_t *val)
{
  lsm6dsv16x_spi2_int_ois_t spi2_int_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SPI2_INT_OIS, (uint8_t *)&spi2_int_ois, 1);

  switch (spi2_int_ois.st_g_ois)
  {
    case LSM6DSV16X_OIS_GY_ST_DISABLE:
      *val = LSM6DSV16X_OIS_GY_ST_DISABLE;
      break;

    case LSM6DSV16X_OIS_GY_ST_POSITIVE:
      *val = (spi2_int_ois.st_ois_clampdis == 1U) ? LSM6DSV16X_OIS_GY_ST_CLAMP_POS : LSM6DSV16X_OIS_GY_ST_POSITIVE;
      break;

    case LSM6DSV16X_OIS_GY_ST_NEGATIVE:
      *val = (spi2_int_ois.st_ois_clampdis == 1U) ? LSM6DSV16X_OIS_GY_ST_CLAMP_NEG : LSM6DSV16X_OIS_GY_ST_NEGATIVE;
      break;

    default:
      *val = LSM6DSV16X_OIS_GY_ST_DISABLE;
      break;
  }
  return ret;
}

/**
  * @defgroup   interrupt_pins
  * @brief      This section groups all the functions that manage
  *             interrupt pins
  * @{
  *
  */

/**
  * @brief   Select the signal that need to route on int1 pad[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    the signals to route on int1 pin.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsv16x_pin_int1_route_set(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_pin_int_route_t *val)
{
  lsm6dsv16x_int1_ctrl_t          int1_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INT1_CTRL, (uint8_t *)&int1_ctrl, 1);

  int1_ctrl.int1_drdy_xl       = val->drdy_xl;
  int1_ctrl.int1_drdy_g        = val->drdy_g;
  int1_ctrl.int1_fifo_th       = val->fifo_th;
  int1_ctrl.int1_fifo_ovr      = val->fifo_ovr;
  int1_ctrl.int1_fifo_full     = val->fifo_full;
  int1_ctrl.int1_cnt_bdr       = val->cnt_bdr;

  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_INT1_CTRL, (uint8_t *)&int1_ctrl,
                              1);

  return ret;
}

/**
  * @brief  Select the signal that need to route on int1 pad.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    the signals that are routed on int1 pin.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsv16x_pin_int1_route_get(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_pin_int_route_t *val)
{
  lsm6dsv16x_int1_ctrl_t          int1_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INT1_CTRL, (uint8_t *)&int1_ctrl, 1);

  val->drdy_xl   = int1_ctrl.int1_drdy_xl;
  val->drdy_g    = int1_ctrl.int1_drdy_g;
  val->fifo_th   = int1_ctrl.int1_fifo_th;
  val->fifo_ovr  = int1_ctrl.int1_fifo_ovr;
  val->fifo_full = int1_ctrl.int1_fifo_full;
  val->cnt_bdr   = int1_ctrl.int1_cnt_bdr;

  return ret;
}

/**
  * @brief   Select the signal that need to route on int2 pad[set]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    the signals to route on int1 pin.
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsv16x_pin_int2_route_set(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_pin_int_route_t *val)
{
  lsm6dsv16x_int2_ctrl_t          int2_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INT2_CTRL, (uint8_t *)&int2_ctrl, 1);

  int2_ctrl.int2_drdy_xl          = val->drdy_xl;
  int2_ctrl.int2_drdy_g           = val->drdy_g;
  int2_ctrl.int2_fifo_th          = val->fifo_th;
  int2_ctrl.int2_fifo_ovr         = val->fifo_ovr;
  int2_ctrl.int2_fifo_full        = val->fifo_full;
  int2_ctrl.int2_cnt_bdr          = val->cnt_bdr;
  int2_ctrl.int2_drdy_g_eis       = val->drdy_g_eis;
  int2_ctrl.int2_emb_func_endop   = val->emb_func_endop;

  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_INT2_CTRL, (uint8_t *)&int2_ctrl,
                              1);

  return ret;
}

/**
  * @brief  Select the signal that need to route on int2 pad.[get]
  *
  * @param  ctx    Read / write interface definitions.(ptr)
  * @param  val    the signals that are routed on int1 pin.(ptr)
  * @retval        Interface status (MANDATORY: return 0 -> no Error).
  *
  */
int32_t lsm6dsv16x_pin_int2_route_get(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_pin_int_route_t *val)
{
  lsm6dsv16x_int2_ctrl_t          int2_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INT2_CTRL, (uint8_t *)&int2_ctrl, 1);

  val->drdy_xl        = int2_ctrl.int2_drdy_xl;
  val->drdy_g         = int2_ctrl.int2_drdy_g;
  val->fifo_th        = int2_ctrl.int2_fifo_th;
  val->fifo_ovr       = int2_ctrl.int2_fifo_ovr;
  val->fifo_full      = int2_ctrl.int2_fifo_full;
  val->cnt_bdr        = int2_ctrl.int2_cnt_bdr;
  val->drdy_g_eis     = int2_ctrl.int2_drdy_g_eis;
  val->emb_func_endop = int2_ctrl.int2_emb_func_endop;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @brief  Get the status of all the interrupt sources.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Get the status of all the interrupt sources.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_all_sources_get(stmdev_ctx_t *ctx,
                                   lsm6dsv16x_all_sources_t *val)
{
  lsm6dsv16x_emb_func_status_mainpage_t emb_func_status_mainpage;
  lsm6dsv16x_emb_func_exec_status_t emb_func_exec_status;
  lsm6dsv16x_fsm_status_mainpage_t fsm_status_mainpage;
  lsm6dsv16x_mlc_status_mainpage_t mlc_status_mainpage;
  lsm6dsv16x_functions_enable_t functions_enable;
  lsm6dsv16x_emb_func_src_t emb_func_src;
  lsm6dsv16x_fifo_status2_t fifo_status2;
  lsm6dsv16x_all_int_src_t all_int_src;
  lsm6dsv16x_wake_up_src_t wake_up_src;
  lsm6dsv16x_status_reg_t status_reg;
  lsm6dsv16x_d6d_src_t d6d_src;
  lsm6dsv16x_tap_src_t tap_src;
  lsm6dsv16x_ui_status_reg_ois_t status_reg_ois;
  lsm6dsv16x_status_master_t status_shub;
  uint8_t buff[8];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  if (ret == 0)
  {
    functions_enable.dis_rst_lir_all_int = PROPERTY_ENABLE;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_STATUS1, (uint8_t *)&buff, 4);
  }
  bytecpy((uint8_t *)&fifo_status2, &buff[1]);
  bytecpy((uint8_t *)&all_int_src, &buff[2]);
  bytecpy((uint8_t *)&status_reg, &buff[3]);

  val->fifo_ovr = fifo_status2.fifo_ovr_ia;
  val->fifo_bdr = fifo_status2.counter_bdr_ia;
  val->fifo_full = fifo_status2.fifo_full_ia;
  val->fifo_th = fifo_status2.fifo_wtm_ia;

  val->free_fall = all_int_src.ff_ia;
  val->wake_up = all_int_src.wu_ia;
  val->six_d = all_int_src.d6d_ia;

  val->drdy_xl = status_reg.xlda;
  val->drdy_gy = status_reg.gda;
  val->drdy_temp = status_reg.tda;
  val->drdy_ah_qvar = status_reg.ah_qvarda;
  val->drdy_eis = status_reg.gda_eis;
  val->drdy_ois = status_reg.ois_drdy;
  val->timestamp = status_reg.timestamp_endcount;

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  }
  if (ret == 0)
  {
    functions_enable.dis_rst_lir_all_int = PROPERTY_DISABLE;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_STATUS_REG_OIS, (uint8_t *)&buff, 8);
  }

  bytecpy((uint8_t *)&status_reg_ois, &buff[0]);
  bytecpy((uint8_t *)&wake_up_src, &buff[1]);
  bytecpy((uint8_t *)&tap_src, &buff[2]);
  bytecpy((uint8_t *)&d6d_src, &buff[3]);
  bytecpy((uint8_t *)&emb_func_status_mainpage, &buff[5]);
  bytecpy((uint8_t *)&fsm_status_mainpage, &buff[6]);
  bytecpy((uint8_t *)&mlc_status_mainpage, &buff[7]);

  val->gy_settling = status_reg_ois.gyro_settling;
  val->sleep_change = wake_up_src.sleep_change_ia;
  val->wake_up_x = wake_up_src.x_wu;
  val->wake_up_y = wake_up_src.y_wu;
  val->wake_up_z = wake_up_src.z_wu;
  val->sleep_state = wake_up_src.sleep_state;

  val->tap_x = tap_src.x_tap;
  val->tap_y = tap_src.y_tap;
  val->tap_z = tap_src.z_tap;
  val->tap_sign = tap_src.tap_sign;
  val->double_tap = tap_src.double_tap;
  val->single_tap = tap_src.single_tap;

  val->six_d_zl = d6d_src.zl;
  val->six_d_zh = d6d_src.zh;
  val->six_d_yl = d6d_src.yl;
  val->six_d_yh = d6d_src.yh;
  val->six_d_xl = d6d_src.xl;
  val->six_d_xh = d6d_src.xh;

  val->step_detector = emb_func_status_mainpage.is_step_det;
  val->tilt = emb_func_status_mainpage.is_tilt;
  val->sig_mot = emb_func_status_mainpage.is_sigmot;
  val->fsm_lc = emb_func_status_mainpage.is_fsm_lc;

  val->fsm1 = fsm_status_mainpage.is_fsm1;
  val->fsm2 = fsm_status_mainpage.is_fsm2;
  val->fsm3 = fsm_status_mainpage.is_fsm3;
  val->fsm4 = fsm_status_mainpage.is_fsm4;
  val->fsm5 = fsm_status_mainpage.is_fsm5;
  val->fsm6 = fsm_status_mainpage.is_fsm6;
  val->fsm7 = fsm_status_mainpage.is_fsm7;
  val->fsm8 = fsm_status_mainpage.is_fsm8;

  val->mlc1 = mlc_status_mainpage.is_mlc1;
  val->mlc2 = mlc_status_mainpage.is_mlc2;
  val->mlc3 = mlc_status_mainpage.is_mlc3;
  val->mlc4 = mlc_status_mainpage.is_mlc4;


  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EXEC_STATUS, (uint8_t *)&emb_func_exec_status, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_SRC, (uint8_t *)&emb_func_src, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  val->emb_func_stand_by = emb_func_exec_status.emb_func_endop;
  val->emb_func_time_exceed = emb_func_exec_status.emb_func_exec_ovr;
  val->step_count_inc = emb_func_src.stepcounter_bit_set;
  val->step_count_overflow = emb_func_src.step_overflow;
  val->step_on_delta_time = emb_func_src.step_count_delta_ia;

  val->step_detector = emb_func_src.step_detected;

  /* sensor hub */
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_STATUS_MASTER, (uint8_t *)&status_shub, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  val->sh_endop = status_shub.sens_hub_endop;
  val->sh_wr_once = status_shub.wr_once_done;
  val->sh_slave3_nack = status_shub.slave3_nack;
  val->sh_slave2_nack = status_shub.slave2_nack;
  val->sh_slave1_nack = status_shub.slave1_nack;
  val->sh_slave0_nack = status_shub.slave0_nack;

  return ret;
}

int32_t lsm6dsv16x_flag_data_ready_get(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_data_ready_t *val)
{
  lsm6dsv16x_status_reg_t status;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_STATUS_REG, (uint8_t *)&status, 1);
  val->drdy_xl = status.xlda;
  val->drdy_gy = status.gda;
  val->drdy_temp = status.tda;

  return ret;
}

/**
  * @brief  Mask status bit reset[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Mask to prevent status bit being reset
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_int_ack_mask_set(stmdev_ctx_t *ctx, uint8_t val)
{
  int32_t ret;

  ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_INT_ACK_MASK, &val, 1);

  return ret;
}

/**
  * @brief  Mask status bit reset[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Mask to prevent status bit being reset
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_int_ack_mask_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INT_ACK_MASK, val, 1);

  return ret;
}

/**
  * @brief  Temperature data output register[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Temperature data output register
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_temperature_raw_get(stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_OUT_TEMP_L, &buff[0], 2);
  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Angular rate sensor.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Angular rate sensor.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_angular_rate_raw_get(stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_OUTX_L_G, &buff[0], 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  Angular rate sensor.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS Angular rate sensor (thru SPI2).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_angular_rate_raw_get(stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SPI2_OUTX_L_G_OIS, &buff[0], 6);
  val[0] = (int16_t)buff[1];
  val[0] = (*val * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (*val * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (*val * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  Angular rate sensor for OIS gyro or the EIS gyro channel.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Angular rate sensor for OIS gyro or the EIS gyro channel.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_eis_angular_rate_raw_get(stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_OUTX_L_G_OIS_EIS, &buff[0], 6);
  val[0] = (int16_t)buff[1];
  val[0] = (*val * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (*val * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (*val * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  Linear acceleration sensor.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Linear acceleration sensor.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_acceleration_raw_get(stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_OUTX_L_A, &buff[0], 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  Linear acceleration sensor for Dual channel mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Linear acceleration sensor or Dual channel mode.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_dual_acceleration_raw_get(stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_OUTX_L_A_OIS_DUALC, &buff[0], 6);
  val[0] = (int16_t)buff[1];
  val[0] = (val[0] * 256) + (int16_t)buff[0];
  val[1] = (int16_t)buff[3];
  val[1] = (val[1] * 256) + (int16_t)buff[2];
  val[2] = (int16_t)buff[5];
  val[2] = (val[2] * 256) + (int16_t)buff[4];

  return ret;
}

/**
  * @brief  ah_qvar data output register.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      ah_qvar data output register.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ah_qvar_raw_get(stmdev_ctx_t *ctx, int16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_AH_QVAR_OUT_L, &buff[0], 2);
  *val = (int16_t)buff[1];
  *val = (*val * 256) + (int16_t)buff[0];

  return ret;
}

/**
  * @brief  Difference in percentage of the effective ODR (and timestamp rate) with respect to the typical. Step: 0.13%. 8-bit format, 2's complement.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Difference in percentage of the effective ODR (and timestamp rate) with respect to the typical. Step: 0.13%. 8-bit format, 2's complement.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_odr_cal_reg_get(stmdev_ctx_t *ctx, int8_t *val)
{
  lsm6dsv16x_internal_freq_t internal_freq;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INTERNAL_FREQ, (uint8_t *)&internal_freq, 1);
  *val = (int8_t)internal_freq.freq_fine;

  return ret;
}

/**
  * @brief  Write buffer in a page.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Write buffer in a page.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ln_pg_write(stmdev_ctx_t *ctx, uint16_t address,
                               uint8_t *buf, uint8_t len)
{
  lsm6dsv16x_page_address_t  page_address;
  lsm6dsv16x_page_sel_t page_sel;
  lsm6dsv16x_page_rw_t page_rw;
  uint8_t msb;
  uint8_t lsb;
  int32_t ret;
  uint8_t i ;

  msb = ((uint8_t)(address >> 8) & 0x0FU);
  lsb = (uint8_t)address & 0xFFU;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);

  /* set page write */
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PAGE_RW, (uint8_t *)&page_rw, 1);
  page_rw.page_read = PROPERTY_DISABLE;
  page_rw.page_write = PROPERTY_ENABLE;
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_RW, (uint8_t *)&page_rw, 1);

  /* select page */
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);
  page_sel.page_sel = msb;
  page_sel.not_used0 = 1; // Default value
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);

  /* set page addr */
  page_address.page_addr = lsb;
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_ADDRESS,
                              (uint8_t *)&page_address, 1);

  for (i = 0; ((i < len) && (ret == 0)); i++)
  {
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_VALUE, &buf[i], 1);
    lsb++;

    /* Check if page wrap */
    if (((lsb & 0xFFU) == 0x00U) && (ret == 0))
    {
      msb++;
      ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);

      if (ret == 0)
      {
        page_sel.page_sel = msb;
        page_sel.not_used0 = 1; // Default value
        ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);
      }
    }
  }

  page_sel.page_sel = 0;
  page_sel.not_used0 = 1;// Default value
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);

  /* unset page write */
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PAGE_RW, (uint8_t *)&page_rw, 1);
  page_rw.page_read = PROPERTY_DISABLE;
  page_rw.page_write = PROPERTY_DISABLE;
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_RW, (uint8_t *)&page_rw, 1);

  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  return ret;
}

/**
  * @defgroup Common
  * @brief     This section groups common useful functions.
  * @{/
  *
  */

/**
  * @brief  Read buffer in a page.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Write buffer in a page.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ln_pg_read(stmdev_ctx_t *ctx, uint16_t address, uint8_t *buf,
                              uint8_t len)
{
  lsm6dsv16x_page_address_t  page_address;
  lsm6dsv16x_page_sel_t page_sel;
  lsm6dsv16x_page_rw_t page_rw;
  uint8_t msb;
  uint8_t lsb;
  int32_t ret;
  uint8_t i ;

  msb = ((uint8_t)(address >> 8) & 0x0FU);
  lsb = (uint8_t)address & 0xFFU;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);

  /* set page write */
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PAGE_RW, (uint8_t *)&page_rw, 1);
  page_rw.page_read = PROPERTY_ENABLE;
  page_rw.page_write = PROPERTY_DISABLE;
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_RW, (uint8_t *)&page_rw, 1);

  /* select page */
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);
  page_sel.page_sel = msb;
  page_sel.not_used0 = 1; // Default value
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);

  /* set page addr */
  page_address.page_addr = lsb;
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_ADDRESS,
                              (uint8_t *)&page_address, 1);

  for (i = 0; ((i < len) && (ret == 0)); i++)
  {
    ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PAGE_VALUE, &buf[i], 1);
    lsb++;

    /* Check if page wrap */
    if (((lsb & 0xFFU) == 0x00U) && (ret == 0))
    {
      msb++;
      ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);

      if (ret == 0)
      {
        page_sel.page_sel = msb;
        page_sel.not_used0 = 1; // Default value
        ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);
      }
    }
  }

  page_sel.page_sel = 0;
  page_sel.not_used0 = 1;// Default value
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_SEL, (uint8_t *)&page_sel, 1);

  /* unset page write */
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PAGE_RW, (uint8_t *)&page_rw, 1);
  page_rw.page_read = PROPERTY_DISABLE;
  page_rw.page_write = PROPERTY_DISABLE;
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PAGE_RW, (uint8_t *)&page_rw, 1);

  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  return ret;
}

/**
  * @brief  Enable debug mode for embedded functions [set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      0, 1
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_emb_function_dbg_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl10_t ctrl10;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);

  if (ret == 0)
  {
    ctrl10.emb_func_debug = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);
  }

  return ret;
}

/**
  * @brief  Enable debug mode for embedded functions [get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      0, 1
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_emb_function_dbg_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl10_t ctrl10;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);

  if (ret == 0)
  {
    *val = ctrl10.emb_func_debug;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Data ENable (DEN)
  * @brief     This section groups all the functions concerning
  *            DEN functionality.
  * @{
  *
  */

/**
  * @brief  It changes the polarity of INT2 pin input trigger for data enable (DEN) or embedded functions.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DEN_ACT_LOW, DEN_ACT_HIGH,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_den_polarity_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_den_polarity_t val)
{
  lsm6dsv16x_ctrl4_t ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL4, (uint8_t *)&ctrl4, 1);

  if (ret == 0)
  {
    ctrl4.int2_in_lh = (uint8_t)val & 0x1U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL4, (uint8_t *)&ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  It changes the polarity of INT2 pin input trigger for data enable (DEN) or embedded functions.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DEN_ACT_LOW, DEN_ACT_HIGH,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_den_polarity_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_den_polarity_t *val)
{
  lsm6dsv16x_ctrl4_t ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL4, (uint8_t *)&ctrl4, 1);
  switch (ctrl4.int2_in_lh)
  {
    case LSM6DSV16X_DEN_ACT_LOW:
      *val = LSM6DSV16X_DEN_ACT_LOW;
      break;

    case LSM6DSV16X_DEN_ACT_HIGH:
      *val = LSM6DSV16X_DEN_ACT_HIGH;
      break;

    default:
      *val = LSM6DSV16X_DEN_ACT_LOW;
      break;
  }
  return ret;
}

/**
  * @brief  Data ENable (DEN) configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Data ENable (DEN) configuration.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_den_conf_set(stmdev_ctx_t *ctx, lsm6dsv16x_den_conf_t val)
{
  lsm6dsv16x_den_t den;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_DEN, (uint8_t *)&den, 1);
  if (ret == 0)
  {
    den.den_z = val.den_z;
    den.den_y = val.den_y;
    den.den_x = val.den_x;

    den.lvl2_en = (uint8_t)val.mode & 0x1U;
    den.lvl1_en = ((uint8_t)val.mode & 0x2U) >> 1;

    if (val.stamp_in_gy_data == PROPERTY_ENABLE && val.stamp_in_xl_data == PROPERTY_ENABLE)
    {
      den.den_xl_g = PROPERTY_DISABLE;
      den.den_xl_en = PROPERTY_ENABLE;
    }
    else if (val.stamp_in_gy_data == PROPERTY_ENABLE && val.stamp_in_xl_data == PROPERTY_DISABLE)
    {
      den.den_xl_g = PROPERTY_DISABLE;
      den.den_xl_en = PROPERTY_DISABLE;
    }
    else if (val.stamp_in_gy_data == PROPERTY_DISABLE && val.stamp_in_xl_data == PROPERTY_ENABLE)
    {
      den.den_xl_g = PROPERTY_ENABLE;
      den.den_xl_en = PROPERTY_DISABLE;
    }
    else
    {
      den.den_xl_g = PROPERTY_DISABLE;
      den.den_xl_en = PROPERTY_DISABLE;
      den.den_z = PROPERTY_DISABLE;
      den.den_y = PROPERTY_DISABLE;
      den.den_x = PROPERTY_DISABLE;
      den.lvl2_en = PROPERTY_DISABLE;
      den.lvl1_en = PROPERTY_DISABLE;
    }

    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_DEN, (uint8_t *)&den, 1);
  }

  return ret;
}


/**
  * @brief  Data ENable (DEN) configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Data ENable (DEN) configuration.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_den_conf_get(stmdev_ctx_t *ctx, lsm6dsv16x_den_conf_t *val)
{
  lsm6dsv16x_den_t den;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_DEN, (uint8_t *)&den, 1);

  val->den_z = den.den_z;
  val->den_y = den.den_y;
  val->den_x = den.den_x;

  if ((den.den_z | den.den_z | den.den_z) == PROPERTY_ENABLE)
  {
    if (den.den_xl_g == PROPERTY_DISABLE && den.den_xl_en == PROPERTY_ENABLE)
    {
      val->stamp_in_gy_data = PROPERTY_ENABLE;
      val->stamp_in_xl_data = PROPERTY_ENABLE;
    }
    else if (den.den_xl_g == PROPERTY_DISABLE && den.den_xl_en == PROPERTY_DISABLE)
    {
      val->stamp_in_gy_data = PROPERTY_ENABLE;
      val->stamp_in_xl_data = PROPERTY_DISABLE;
    }
    else // ( (den.den_xl_g & !den.den_xl_en) == PROPERTY_ENABLE )
    {
      val->stamp_in_gy_data = PROPERTY_DISABLE;
      val->stamp_in_xl_data = PROPERTY_ENABLE;
    }
  }
  else
  {
    val->stamp_in_gy_data = PROPERTY_DISABLE;
    val->stamp_in_xl_data = PROPERTY_DISABLE;
  }

  switch ((den.lvl1_en << 1) + den.lvl2_en)
  {
    case LSM6DSV16X_LEVEL_TRIGGER:
      val->mode = LSM6DSV16X_LEVEL_TRIGGER;
      break;

    case LSM6DSV16X_LEVEL_LATCHED:
      val->mode = LSM6DSV16X_LEVEL_LATCHED;
      break;

    default:
      val->mode = LSM6DSV16X_DEN_NOT_DEFINED;
      break;
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup Electronic Image Stabilization (EIS)
  * @brief    Electronic Image Stabilization (EIS)
  * @{/
  *
  */

/**
  * @brief  Gyroscope full-scale selection for EIS channel. WARNING: 4000dps will be available only if also User Interface chain is set to 4000dps[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      125dps, 250dps, 500dps, 1000dps, 2000dps, 4000dps,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_eis_gy_full_scale_set(stmdev_ctx_t *ctx,
                                         lsm6dsv16x_eis_gy_full_scale_t val)
{
  lsm6dsv16x_ctrl_eis_t ctrl_eis;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);

  if (ret == 0)
  {
    ctrl_eis.fs_g_eis = (uint8_t)val & 0x7U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope full-scale selection for EIS channel. WARNING: 4000dps will be available only if also User Interface chain is set to 4000dps[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      125dps, 250dps, 500dps, 1000dps, 2000dps
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_eis_gy_full_scale_get(stmdev_ctx_t *ctx,
                                         lsm6dsv16x_eis_gy_full_scale_t *val)
{
  lsm6dsv16x_ctrl_eis_t ctrl_eis;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);

  switch (ctrl_eis.fs_g_eis)
  {
    case LSM6DSV16X_EIS_125dps:
      *val = LSM6DSV16X_EIS_125dps;
      break;

    case LSM6DSV16X_EIS_250dps:
      *val = LSM6DSV16X_EIS_250dps;
      break;

    case LSM6DSV16X_EIS_500dps:
      *val = LSM6DSV16X_EIS_500dps;
      break;

    case LSM6DSV16X_EIS_1000dps:
      *val = LSM6DSV16X_EIS_1000dps;
      break;

    case LSM6DSV16X_EIS_2000dps:
      *val = LSM6DSV16X_EIS_2000dps;
      break;

    default:
      *val = LSM6DSV16X_EIS_125dps;
      break;
  }
  return ret;
}

/**
  * @brief  Enables routing of gyroscope EIS outputs on SPI2 (OIS interface). The gyroscope data on SPI2 (OIS interface) cannot be read from User Interface (UI).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables routing of gyroscope EIS outputs on SPI2 (OIS interface). The gyroscope data on SPI2 (OIS interface) cannot be read from User Interface (UI).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_eis_gy_on_spi2_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl_eis_t ctrl_eis;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);

  if (ret == 0)
  {
    ctrl_eis.g_eis_on_g_ois_out_reg = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);
  }

  return ret;
}

/**
  * @brief  Enables routing of gyroscope EIS outputs on SPI2 (OIS interface). The gyroscope data on SPI2 (OIS interface) cannot be read from User Interface (UI).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables routing of gyroscope EIS outputs on SPI2 (OIS interface). The gyroscope data on SPI2 (OIS interface) cannot be read from User Interface (UI).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_eis_gy_on_spi2_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl_eis_t ctrl_eis;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);
  *val = ctrl_eis.g_eis_on_g_ois_out_reg;

  return ret;
}

/**
  * @brief  Enables and selects the ODR of the gyroscope EIS channel.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      EIS_1920Hz, EIS_960Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_eis_data_rate_set(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_gy_eis_data_rate_t val)
{
  lsm6dsv16x_ctrl_eis_t ctrl_eis;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);

  if (ret == 0)
  {
    ctrl_eis.odr_g_eis = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);
  }

  return ret;
}

/**
  * @brief  Enables and selects the ODR of the gyroscope EIS channel.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      EIS_1920Hz, EIS_960Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_gy_eis_data_rate_get(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_gy_eis_data_rate_t *val)
{
  lsm6dsv16x_ctrl_eis_t ctrl_eis;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);

  switch (ctrl_eis.odr_g_eis)
  {
    case LSM6DSV16X_EIS_ODR_OFF:
      *val = LSM6DSV16X_EIS_ODR_OFF;
      break;

    case LSM6DSV16X_EIS_1920Hz:
      *val = LSM6DSV16X_EIS_1920Hz;
      break;

    case LSM6DSV16X_EIS_960Hz:
      *val = LSM6DSV16X_EIS_960Hz;
      break;

    default:
      *val = LSM6DSV16X_EIS_1920Hz;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  FIFO
  * @brief     This section group all the functions concerning the FIFO usage
  * @{
  *
  */

/**
  * @brief  FIFO watermark threshold (1 LSb = TAG (1 Byte) + 1 sensor (6 Bytes) written in FIFO).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FIFO watermark threshold (1 LSb = TAG (1 Byte) + 1 sensor (6 Bytes) written in FIFO).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_watermark_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_fifo_ctrl1_t fifo_ctrl1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL1, (uint8_t *)&fifo_ctrl1, 1);

  if (ret == 0)
  {
    fifo_ctrl1.wtm = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL1, (uint8_t *)&fifo_ctrl1, 1);
  }

  return ret;
}

/**
  * @brief  FIFO watermark threshold (1 LSb = TAG (1 Byte) + 1 sensor (6 Bytes) written in FIFO).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FIFO watermark threshold (1 LSb = TAG (1 Byte) + 1 sensor (6 Bytes) written in FIFO).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_watermark_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_fifo_ctrl1_t fifo_ctrl1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL1, (uint8_t *)&fifo_ctrl1, 1);
  *val = fifo_ctrl1.wtm;

  return ret;
}

/**
  * @brief  When dual channel mode is enabled, this function enables FSM-triggered batching in FIFO of accelerometer channel 2.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      When dual channel mode is enabled, this function enables FSM-triggered batching in FIFO of accelerometer channel 2.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_xl_dual_fsm_batch_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  if (ret == 0)
  {
    fifo_ctrl2.xl_dualc_batch_from_fsm = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  When dual channel mode is enabled, this function enables FSM-triggered batching in FIFO of accelerometer channel 2.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      When dual channel mode is enabled, this function enables FSM-triggered batching in FIFO of accelerometer channel 2.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_xl_dual_fsm_batch_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  *val = fifo_ctrl2.xl_dualc_batch_from_fsm;


  return ret;
}

/**
  * @brief  It configures the compression algorithm to write non-compressed data at each rate.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      CMP_DISABLE, CMP_ALWAYS, CMP_8_TO_1, CMP_16_TO_1, CMP_32_TO_1,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_compress_algo_set(stmdev_ctx_t *ctx,
                                          lsm6dsv16x_fifo_compress_algo_t val)
{
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  if (ret == 0)
  {
    fifo_ctrl2.uncompr_rate = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  It configures the compression algorithm to write non-compressed data at each rate.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      CMP_DISABLE, CMP_ALWAYS, CMP_8_TO_1, CMP_16_TO_1, CMP_32_TO_1,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_compress_algo_get(stmdev_ctx_t *ctx,
                                          lsm6dsv16x_fifo_compress_algo_t *val)
{
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  switch (fifo_ctrl2.uncompr_rate)
  {
    case LSM6DSV16X_CMP_DISABLE:
      *val = LSM6DSV16X_CMP_DISABLE;
      break;

    case LSM6DSV16X_CMP_8_TO_1:
      *val = LSM6DSV16X_CMP_8_TO_1;
      break;

    case LSM6DSV16X_CMP_16_TO_1:
      *val = LSM6DSV16X_CMP_16_TO_1;
      break;

    case LSM6DSV16X_CMP_32_TO_1:
      *val = LSM6DSV16X_CMP_32_TO_1;
      break;

    default:
      *val = LSM6DSV16X_CMP_DISABLE;
      break;
  }
  return ret;
}

/**
  * @brief  Enables ODR CHANGE virtual sensor to be batched in FIFO.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables ODR CHANGE virtual sensor to be batched in FIFO.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_virtual_sens_odr_chg_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  if (ret == 0)
  {
    fifo_ctrl2.odr_chg_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Enables ODR CHANGE virtual sensor to be batched in FIFO.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables ODR CHANGE virtual sensor to be batched in FIFO.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_virtual_sens_odr_chg_get(stmdev_ctx_t *ctx,
                                                 uint8_t *val)
{
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  *val = fifo_ctrl2.odr_chg_en;

  return ret;
}

/**
  * @brief  Enables/Disables compression algorithm runtime.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables/Disables compression algorithm runtime.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_compress_algo_real_time_set(stmdev_ctx_t *ctx,
                                                    uint8_t val)
{
  lsm6dsv16x_emb_func_en_b_t emb_func_en_b;
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;

  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  if (ret == 0)
  {
    fifo_ctrl2.fifo_compr_rt_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_B, (uint8_t *)&emb_func_en_b, 1);
  }
  if (ret == 0)
  {
    emb_func_en_b.fifo_compr_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_B, (uint8_t *)&emb_func_en_b, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enables/Disables compression algorithm runtime.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables/Disables compression algorithm runtime.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_compress_algo_real_time_get(stmdev_ctx_t *ctx,
                                                    uint8_t *val)
{
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);

  *val = fifo_ctrl2.fifo_compr_rt_en;

  return ret;
}

/**
  * @brief  Sensing chain FIFO stop values memorization at threshold level.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Sensing chain FIFO stop values memorization at threshold level.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_stop_on_wtm_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  if (ret == 0)
  {
    fifo_ctrl2.stop_on_wtm = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  }

  return ret;
}

/**
  * @brief  Sensing chain FIFO stop values memorization at threshold level.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Sensing chain FIFO stop values memorization at threshold level.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_stop_on_wtm_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_fifo_ctrl2_t fifo_ctrl2;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL2, (uint8_t *)&fifo_ctrl2, 1);
  *val = fifo_ctrl2.stop_on_wtm;

  return ret;
}

/**
  * @brief  Selects Batch Data Rate (write frequency in FIFO) for accelerometer data.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_NOT_BATCHED, XL_BATCHED_AT_1Hz875, XL_BATCHED_AT_7Hz5, XL_BATCHED_AT_15Hz, XL_BATCHED_AT_30Hz, XL_BATCHED_AT_60Hz, XL_BATCHED_AT_120Hz, XL_BATCHED_AT_240Hz, XL_BATCHED_AT_480Hz, XL_BATCHED_AT_960Hz, XL_BATCHED_AT_1920Hz, XL_BATCHED_AT_3840Hz, XL_BATCHED_AT_7680Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_xl_batch_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_fifo_xl_batch_t val)
{
  lsm6dsv16x_fifo_ctrl3_t fifo_ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL3, (uint8_t *)&fifo_ctrl3, 1);
  if (ret == 0)
  {
    fifo_ctrl3.bdr_xl = (uint8_t)val & 0xFu;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL3, (uint8_t *)&fifo_ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batch Data Rate (write frequency in FIFO) for accelerometer data.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_NOT_BATCHED, XL_BATCHED_AT_1Hz875, XL_BATCHED_AT_7Hz5, XL_BATCHED_AT_15Hz, XL_BATCHED_AT_30Hz, XL_BATCHED_AT_60Hz, XL_BATCHED_AT_120Hz, XL_BATCHED_AT_240Hz, XL_BATCHED_AT_480Hz, XL_BATCHED_AT_960Hz, XL_BATCHED_AT_1920Hz, XL_BATCHED_AT_3840Hz, XL_BATCHED_AT_7680Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_xl_batch_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_fifo_xl_batch_t *val)
{
  lsm6dsv16x_fifo_ctrl3_t fifo_ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL3, (uint8_t *)&fifo_ctrl3, 1);
  switch (fifo_ctrl3.bdr_xl)
  {
    case LSM6DSV16X_XL_NOT_BATCHED:
      *val = LSM6DSV16X_XL_NOT_BATCHED;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_1Hz875:
      *val = LSM6DSV16X_XL_BATCHED_AT_1Hz875;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_7Hz5:
      *val = LSM6DSV16X_XL_BATCHED_AT_7Hz5;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_15Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_15Hz;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_30Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_30Hz;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_60Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_60Hz;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_120Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_120Hz;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_240Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_240Hz;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_480Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_480Hz;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_960Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_960Hz;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_1920Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_1920Hz;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_3840Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_3840Hz;
      break;

    case LSM6DSV16X_XL_BATCHED_AT_7680Hz:
      *val = LSM6DSV16X_XL_BATCHED_AT_7680Hz;
      break;

    default:
      *val = LSM6DSV16X_XL_NOT_BATCHED;
      break;
  }
  return ret;
}

/**
  * @brief  Selects Batch Data Rate (write frequency in FIFO) for gyroscope data.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_NOT_BATCHED, GY_BATCHED_AT_1Hz875, GY_BATCHED_AT_7Hz5, GY_BATCHED_AT_15Hz, GY_BATCHED_AT_30Hz, GY_BATCHED_AT_60Hz, GY_BATCHED_AT_120Hz, GY_BATCHED_AT_240Hz, GY_BATCHED_AT_480Hz, GY_BATCHED_AT_960Hz, GY_BATCHED_AT_1920Hz, GY_BATCHED_AT_3840Hz, GY_BATCHED_AT_7680Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_gy_batch_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_fifo_gy_batch_t val)
{
  lsm6dsv16x_fifo_ctrl3_t fifo_ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL3, (uint8_t *)&fifo_ctrl3, 1);
  if (ret == 0)
  {
    fifo_ctrl3.bdr_gy = (uint8_t)val & 0x0Fu;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL3, (uint8_t *)&fifo_ctrl3, 1);
  }

  return ret;
}

/**
  * @brief  Selects Batch Data Rate (write frequency in FIFO) for gyroscope data.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_NOT_BATCHED, GY_BATCHED_AT_1Hz875, GY_BATCHED_AT_7Hz5, GY_BATCHED_AT_15Hz, GY_BATCHED_AT_30Hz, GY_BATCHED_AT_60Hz, GY_BATCHED_AT_120Hz, GY_BATCHED_AT_240Hz, GY_BATCHED_AT_480Hz, GY_BATCHED_AT_960Hz, GY_BATCHED_AT_1920Hz, GY_BATCHED_AT_3840Hz, GY_BATCHED_AT_7680Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_gy_batch_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_fifo_gy_batch_t *val)
{
  lsm6dsv16x_fifo_ctrl3_t fifo_ctrl3;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL3, (uint8_t *)&fifo_ctrl3, 1);
  switch (fifo_ctrl3.bdr_gy)
  {
    case LSM6DSV16X_GY_NOT_BATCHED:
      *val = LSM6DSV16X_GY_NOT_BATCHED;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_1Hz875:
      *val = LSM6DSV16X_GY_BATCHED_AT_1Hz875;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_7Hz5:
      *val = LSM6DSV16X_GY_BATCHED_AT_7Hz5;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_15Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_15Hz;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_30Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_30Hz;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_60Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_60Hz;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_120Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_120Hz;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_240Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_240Hz;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_480Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_480Hz;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_960Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_960Hz;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_1920Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_1920Hz;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_3840Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_3840Hz;
      break;

    case LSM6DSV16X_GY_BATCHED_AT_7680Hz:
      *val = LSM6DSV16X_GY_BATCHED_AT_7680Hz;
      break;

    default:
      *val = LSM6DSV16X_GY_NOT_BATCHED;
      break;
  }
  return ret;
}


/**
  * @brief  FIFO mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      BYPASS_MODE, FIFO_MODE, STREAM_WTM_TO_FULL_MODE, STREAM_TO_FIFO_MODE, BYPASS_TO_STREAM_MODE, STREAM_MODE, BYPASS_TO_FIFO_MODE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_mode_set(stmdev_ctx_t *ctx, lsm6dsv16x_fifo_mode_t val)
{
  lsm6dsv16x_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  if (ret == 0)
  {
    fifo_ctrl4.fifo_mode = (uint8_t)val & 0x07U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  FIFO mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      BYPASS_MODE, FIFO_MODE, STREAM_WTM_TO_FULL_MODE, STREAM_TO_FIFO_MODE, BYPASS_TO_STREAM_MODE, STREAM_MODE, BYPASS_TO_FIFO_MODE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_mode_get(stmdev_ctx_t *ctx, lsm6dsv16x_fifo_mode_t *val)
{
  lsm6dsv16x_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  switch (fifo_ctrl4.fifo_mode)
  {
    case LSM6DSV16X_BYPASS_MODE:
      *val = LSM6DSV16X_BYPASS_MODE;
      break;

    case LSM6DSV16X_FIFO_MODE:
      *val = LSM6DSV16X_FIFO_MODE;
      break;

    case LSM6DSV16X_STREAM_WTM_TO_FULL_MODE:
      *val = LSM6DSV16X_STREAM_WTM_TO_FULL_MODE;
      break;

    case LSM6DSV16X_STREAM_TO_FIFO_MODE:
      *val = LSM6DSV16X_STREAM_TO_FIFO_MODE;
      break;

    case LSM6DSV16X_BYPASS_TO_STREAM_MODE:
      *val = LSM6DSV16X_BYPASS_TO_STREAM_MODE;
      break;

    case LSM6DSV16X_STREAM_MODE:
      *val = LSM6DSV16X_STREAM_MODE;
      break;

    case LSM6DSV16X_BYPASS_TO_FIFO_MODE:
      *val = LSM6DSV16X_BYPASS_TO_FIFO_MODE;
      break;

    default:
      *val = LSM6DSV16X_BYPASS_MODE;
      break;
  }
  return ret;
}

/**
  * @brief  Enables FIFO batching of EIS gyroscope output values.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables FIFO batching of EIS gyroscope output values.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_gy_eis_batch_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  if (ret == 0)
  {
    fifo_ctrl4.g_eis_fifo_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  Enables FIFO batching of EIS gyroscope output values.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables FIFO batching of EIS gyroscope output values.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_gy_eis_batch_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  *val = fifo_ctrl4.g_eis_fifo_en;

  return ret;
}

/**
  * @brief  Selects batch data rate (write frequency in FIFO) for temperature data.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      TEMP_NOT_BATCHED, TEMP_BATCHED_AT_1Hz875, TEMP_BATCHED_AT_15Hz, TEMP_BATCHED_AT_60Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_temp_batch_set(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_fifo_temp_batch_t val)
{
  lsm6dsv16x_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  if (ret == 0)
  {
    fifo_ctrl4.odr_t_batch = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  Selects batch data rate (write frequency in FIFO) for temperature data.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      TEMP_NOT_BATCHED, TEMP_BATCHED_AT_1Hz875, TEMP_BATCHED_AT_15Hz, TEMP_BATCHED_AT_60Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_temp_batch_get(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_fifo_temp_batch_t *val)
{
  lsm6dsv16x_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  switch (fifo_ctrl4.odr_t_batch)
  {
    case LSM6DSV16X_TEMP_NOT_BATCHED:
      *val = LSM6DSV16X_TEMP_NOT_BATCHED;
      break;

    case LSM6DSV16X_TEMP_BATCHED_AT_1Hz875:
      *val = LSM6DSV16X_TEMP_BATCHED_AT_1Hz875;
      break;

    case LSM6DSV16X_TEMP_BATCHED_AT_15Hz:
      *val = LSM6DSV16X_TEMP_BATCHED_AT_15Hz;
      break;

    case LSM6DSV16X_TEMP_BATCHED_AT_60Hz:
      *val = LSM6DSV16X_TEMP_BATCHED_AT_60Hz;
      break;

    default:
      *val = LSM6DSV16X_TEMP_NOT_BATCHED;
      break;
  }
  return ret;
}

/**
  * @brief  Selects decimation for timestamp batching in FIFO. Write rate will be the maximum rate between XL and GYRO BDR divided by decimation decoder.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      TMSTMP_NOT_BATCHED, TMSTMP_DEC_1, TMSTMP_DEC_8, TMSTMP_DEC_32,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_timestamp_batch_set(stmdev_ctx_t *ctx,
                                            lsm6dsv16x_fifo_timestamp_batch_t val)
{
  lsm6dsv16x_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  if (ret == 0)
  {
    fifo_ctrl4.dec_ts_batch = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  }

  return ret;
}

/**
  * @brief  Selects decimation for timestamp batching in FIFO. Write rate will be the maximum rate between XL and GYRO BDR divided by decimation decoder.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      TMSTMP_NOT_BATCHED, TMSTMP_DEC_1, TMSTMP_DEC_8, TMSTMP_DEC_32,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_timestamp_batch_get(stmdev_ctx_t *ctx,
                                            lsm6dsv16x_fifo_timestamp_batch_t *val)
{
  lsm6dsv16x_fifo_ctrl4_t fifo_ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_CTRL4, (uint8_t *)&fifo_ctrl4, 1);
  switch (fifo_ctrl4.dec_ts_batch)
  {
    case LSM6DSV16X_TMSTMP_NOT_BATCHED:
      *val = LSM6DSV16X_TMSTMP_NOT_BATCHED;
      break;

    case LSM6DSV16X_TMSTMP_DEC_1:
      *val = LSM6DSV16X_TMSTMP_DEC_1;
      break;

    case LSM6DSV16X_TMSTMP_DEC_8:
      *val = LSM6DSV16X_TMSTMP_DEC_8;
      break;

    case LSM6DSV16X_TMSTMP_DEC_32:
      *val = LSM6DSV16X_TMSTMP_DEC_32;
      break;

    default:
      *val = LSM6DSV16X_TMSTMP_NOT_BATCHED;
      break;
  }
  return ret;
}

/**
  * @brief  The threshold for the internal counter of batch events. When this counter reaches the threshold, the counter is reset and the interrupt flag is set to 1.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      The threshold for the internal counter of batch events. When this counter reaches the threshold, the counter is reset and the interrupt flag is set to 1.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_counter_threshold_set(stmdev_ctx_t *ctx,
                                                    uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_COUNTER_BDR_REG1, (uint8_t *)&buff[0], 2);

  return ret;
}

/**
  * @brief  The threshold for the internal counter of batch events. When this counter reaches the threshold, the counter is reset and the interrupt flag is set to 1.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      The threshold for the internal counter of batch events. When this counter reaches the threshold, the counter is reset and the interrupt flag is set to 1.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_counter_threshold_get(stmdev_ctx_t *ctx,
                                                    uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_COUNTER_BDR_REG1, &buff[0], 2);
  *val = buff[1];
  *val = (*val * 256U) + buff[0];

  return ret;
}

/**
  * @brief  Selects the trigger for the internal counter of batch events between the accelerometer, gyroscope and EIS gyroscope.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_BATCH_EVENT, GY_BATCH_EVENT, GY_EIS_BATCH_EVENT,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_cnt_event_set(stmdev_ctx_t *ctx,
                                            lsm6dsv16x_fifo_batch_cnt_event_t val)
{
  lsm6dsv16x_counter_bdr_reg1_t counter_bdr_reg1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_COUNTER_BDR_REG1, (uint8_t *)&counter_bdr_reg1, 1);
  if (ret == 0)
  {
    counter_bdr_reg1.trig_counter_bdr = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_COUNTER_BDR_REG1, (uint8_t *)&counter_bdr_reg1, 1);
  }

  return ret;
}

/**
  * @brief  Selects the trigger for the internal counter of batch events between the accelerometer, gyroscope and EIS gyroscope.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_BATCH_EVENT, GY_BATCH_EVENT, GY_EIS_BATCH_EVENT,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_cnt_event_get(stmdev_ctx_t *ctx,
                                            lsm6dsv16x_fifo_batch_cnt_event_t *val)
{
  lsm6dsv16x_counter_bdr_reg1_t counter_bdr_reg1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_COUNTER_BDR_REG1, (uint8_t *)&counter_bdr_reg1, 1);
  switch (counter_bdr_reg1.trig_counter_bdr)
  {
    case LSM6DSV16X_XL_BATCH_EVENT:
      *val = LSM6DSV16X_XL_BATCH_EVENT;
      break;

    case LSM6DSV16X_GY_BATCH_EVENT:
      *val = LSM6DSV16X_GY_BATCH_EVENT;
      break;

    case LSM6DSV16X_GY_EIS_BATCH_EVENT:
      *val = LSM6DSV16X_GY_EIS_BATCH_EVENT;
      break;

    default:
      *val = LSM6DSV16X_XL_BATCH_EVENT;
      break;
  }
  return ret;
}

int32_t lsm6dsv16x_fifo_status_get(stmdev_ctx_t *ctx,
                                   lsm6dsv16x_fifo_status_t *val)
{
  uint8_t buff[2];
  lsm6dsv16x_fifo_status2_t status;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_STATUS1, (uint8_t *)&buff[0], 2);
  bytecpy((uint8_t *)&status, &buff[1]);

  val->fifo_bdr = status.counter_bdr_ia;
  val->fifo_ovr = status.fifo_ovr_ia;
  val->fifo_full = status.fifo_full_ia;
  val->fifo_th = status.fifo_wtm_ia;

  val->fifo_level = (uint16_t)buff[1] & 0x01U;
  val->fifo_level = (val->fifo_level * 256U) + buff[0];

  return ret;
}


/**
  * @brief  FIFO data output[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FIFO_EMPTY, GY_NC_TAG, XL_NC_TAG, TIMESTAMP_TAG,
                     TEMPERATURE_TAG, CFG_CHANGE_TAG, XL_NC_T_2_TAG,
                     XL_NC_T_1_TAG, XL_2XC_TAG, XL_3XC_TAG, GY_NC_T_2_TAG,
                     GY_NC_T_1_TAG, GY_2XC_TAG, GY_3XC_TAG, SENSORHUB_SLAVE0_TAG,
                     SENSORHUB_SLAVE1_TAG, SENSORHUB_SLAVE2_TAG, SENSORHUB_SLAVE3_TAG,
                     STEP_COUNTER_TAG, SFLP_GAME_ROTATION_VECTOR_TAG, SFLP_GYROSCOPE_BIAS_TAG,
                     SFLP_GRAVITY_VECTOR_TAG, SENSORHUB_NACK_TAG, MLC_RESULT_TAG,
                     MLC_FILTER, MLC_FEATURE, XL_DUAL_CORE, GY_ENHANCED_EIS,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_out_raw_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_fifo_out_raw_t *val)
{
  lsm6dsv16x_fifo_data_out_tag_t fifo_data_out_tag;
  uint8_t buff[7];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FIFO_DATA_OUT_TAG, buff, 7);
  bytecpy((uint8_t *)&fifo_data_out_tag, &buff[0]);

  switch (fifo_data_out_tag.tag_sensor)
  {
    case LSM6DSV16X_FIFO_EMPTY:
      val->tag = LSM6DSV16X_FIFO_EMPTY;
      break;

    case LSM6DSV16X_GY_NC_TAG:
      val->tag = LSM6DSV16X_GY_NC_TAG;
      break;

    case LSM6DSV16X_XL_NC_TAG:
      val->tag = LSM6DSV16X_XL_NC_TAG;
      break;

    case LSM6DSV16X_TIMESTAMP_TAG:
      val->tag = LSM6DSV16X_TIMESTAMP_TAG;
      break;

    case LSM6DSV16X_TEMPERATURE_TAG:
      val->tag = LSM6DSV16X_TEMPERATURE_TAG;
      break;

    case LSM6DSV16X_CFG_CHANGE_TAG:
      val->tag = LSM6DSV16X_CFG_CHANGE_TAG;
      break;

    case LSM6DSV16X_XL_NC_T_2_TAG:
      val->tag = LSM6DSV16X_XL_NC_T_2_TAG;
      break;

    case LSM6DSV16X_XL_NC_T_1_TAG:
      val->tag = LSM6DSV16X_XL_NC_T_1_TAG;
      break;

    case LSM6DSV16X_XL_2XC_TAG:
      val->tag = LSM6DSV16X_XL_2XC_TAG;
      break;

    case LSM6DSV16X_XL_3XC_TAG:
      val->tag = LSM6DSV16X_XL_3XC_TAG;
      break;

    case LSM6DSV16X_GY_NC_T_2_TAG:
      val->tag = LSM6DSV16X_GY_NC_T_2_TAG;
      break;

    case LSM6DSV16X_GY_NC_T_1_TAG:
      val->tag = LSM6DSV16X_GY_NC_T_1_TAG;
      break;

    case LSM6DSV16X_GY_2XC_TAG:
      val->tag = LSM6DSV16X_GY_2XC_TAG;
      break;

    case LSM6DSV16X_GY_3XC_TAG:
      val->tag = LSM6DSV16X_GY_3XC_TAG;
      break;

    case LSM6DSV16X_SENSORHUB_SLAVE0_TAG:
      val->tag = LSM6DSV16X_SENSORHUB_SLAVE0_TAG;
      break;

    case LSM6DSV16X_SENSORHUB_SLAVE1_TAG:
      val->tag = LSM6DSV16X_SENSORHUB_SLAVE1_TAG;
      break;

    case LSM6DSV16X_SENSORHUB_SLAVE2_TAG:
      val->tag = LSM6DSV16X_SENSORHUB_SLAVE2_TAG;
      break;

    case LSM6DSV16X_SENSORHUB_SLAVE3_TAG:
      val->tag = LSM6DSV16X_SENSORHUB_SLAVE3_TAG;
      break;

    case LSM6DSV16X_STEP_COUNTER_TAG:
      val->tag = LSM6DSV16X_STEP_COUNTER_TAG;
      break;

    case LSM6DSV16X_SFLP_GAME_ROTATION_VECTOR_TAG:
      val->tag = LSM6DSV16X_SFLP_GAME_ROTATION_VECTOR_TAG;
      break;

    case LSM6DSV16X_SFLP_GYROSCOPE_BIAS_TAG:
      val->tag = LSM6DSV16X_SFLP_GYROSCOPE_BIAS_TAG;
      break;

    case LSM6DSV16X_SFLP_GRAVITY_VECTOR_TAG:
      val->tag = LSM6DSV16X_SFLP_GRAVITY_VECTOR_TAG;
      break;

    case LSM6DSV16X_SENSORHUB_NACK_TAG:
      val->tag = LSM6DSV16X_SENSORHUB_NACK_TAG;
      break;

    case LSM6DSV16X_MLC_RESULT_TAG:
      val->tag = LSM6DSV16X_MLC_RESULT_TAG;
      break;

    case LSM6DSV16X_MLC_FILTER:
      val->tag = LSM6DSV16X_MLC_FILTER;
      break;

    case LSM6DSV16X_MLC_FEATURE:
      val->tag = LSM6DSV16X_MLC_FEATURE;
      break;

    case LSM6DSV16X_XL_DUAL_CORE:
      val->tag = LSM6DSV16X_XL_DUAL_CORE;
      break;

    case LSM6DSV16X_GY_ENHANCED_EIS:
      val->tag = LSM6DSV16X_GY_ENHANCED_EIS;
      break;

    default:
      val->tag = LSM6DSV16X_FIFO_EMPTY;
      break;
  }

  val->cnt = fifo_data_out_tag.tag_cnt;

  val->data[0] = buff[1];
  val->data[1] = buff[2];
  val->data[2] = buff[3];
  val->data[3] = buff[4];
  val->data[4] = buff[5];
  val->data[5] = buff[6];

  return ret;
}

/**
  * @brief  Batching in FIFO buffer of step counter value.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Batching in FIFO buffer of step counter value.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_stpcnt_batch_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_emb_func_fifo_en_a_t emb_func_fifo_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_A, (uint8_t *)&emb_func_fifo_en_a, 1);
  }

  if (ret == 0)
  {
    emb_func_fifo_en_a.step_counter_fifo_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_A, (uint8_t *)&emb_func_fifo_en_a, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Batching in FIFO buffer of step counter value.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Batching in FIFO buffer of step counter value.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_stpcnt_batch_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_emb_func_fifo_en_a_t emb_func_fifo_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_A, (uint8_t *)&emb_func_fifo_en_a, 1);
  }

  *val = emb_func_fifo_en_a.step_counter_fifo_en;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Batching in FIFO buffer of machine learning core results.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Batching in FIFO buffer of machine learning core results.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_mlc_batch_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_emb_func_fifo_en_a_t emb_func_fifo_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_A, (uint8_t *)&emb_func_fifo_en_a, 1);
  }

  if (ret == 0)
  {
    emb_func_fifo_en_a.mlc_fifo_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_A, (uint8_t *)&emb_func_fifo_en_a, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Batching in FIFO buffer of machine learning core results.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Batching in FIFO buffer of machine learning core results.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_mlc_batch_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_emb_func_fifo_en_a_t emb_func_fifo_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_A, (uint8_t *)&emb_func_fifo_en_a, 1);
  }

  *val = emb_func_fifo_en_a.mlc_fifo_en;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enables batching in FIFO buffer of machine learning core filters and features.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables batching in FIFO buffer of machine learning core filters and features.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_mlc_filt_batch_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_emb_func_fifo_en_b_t emb_func_fifo_en_b;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_B, (uint8_t *)&emb_func_fifo_en_b, 1);
  }

  if (ret == 0)
  {
    emb_func_fifo_en_b.mlc_filter_feature_fifo_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_B, (uint8_t *)&emb_func_fifo_en_b, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enables batching in FIFO buffer of machine learning core filters and features.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables batching in FIFO buffer of machine learning core filters and features.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_mlc_filt_batch_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_emb_func_fifo_en_b_t emb_func_fifo_en_b;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_B, (uint8_t *)&emb_func_fifo_en_b, 1);
  }

  *val = emb_func_fifo_en_b.mlc_filter_feature_fifo_en;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO data batching of first slave.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable FIFO data batching of first slave.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_sh_slave_0_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV0_CONFIG, (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    slv0_config.batch_ext_sens_0_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV0_CONFIG, (uint8_t *)&slv0_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO data batching of first slave.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable FIFO data batching of first slave.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_sh_slave_0_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV0_CONFIG, (uint8_t *)&slv0_config, 1);
  }

  *val = slv0_config.batch_ext_sens_0_en;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO data batching of second slave.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable FIFO data batching of second slave.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_sh_slave_1_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_slv1_config_t slv1_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV1_CONFIG, (uint8_t *)&slv1_config, 1);
  }

  if (ret == 0)
  {
    slv1_config.batch_ext_sens_1_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV1_CONFIG, (uint8_t *)&slv1_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO data batching of second slave.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable FIFO data batching of second slave.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_sh_slave_1_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_slv1_config_t slv1_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV1_CONFIG, (uint8_t *)&slv1_config, 1);
  }

  *val = slv1_config.batch_ext_sens_1_en;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO data batching of third slave.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable FIFO data batching of third slave.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_sh_slave_2_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_slv2_config_t slv2_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV2_CONFIG, (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    slv2_config.batch_ext_sens_2_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV2_CONFIG, (uint8_t *)&slv2_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO data batching of third slave.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable FIFO data batching of third slave.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_sh_slave_2_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_slv2_config_t slv2_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV2_CONFIG, (uint8_t *)&slv2_config, 1);
  }

  *val = slv2_config.batch_ext_sens_2_en;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO data batching of fourth slave.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable FIFO data batching of fourth slave.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_sh_slave_3_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_slv3_config_t slv3_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV3_CONFIG, (uint8_t *)&slv3_config, 1);
  }

  if (ret == 0)
  {
    slv3_config.batch_ext_sens_3_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV3_CONFIG, (uint8_t *)&slv3_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enable FIFO data batching of fourth slave.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable FIFO data batching of fourth slave.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_batch_sh_slave_3_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_slv3_config_t slv3_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV3_CONFIG, (uint8_t *)&slv3_config, 1);
  }

  *val = slv3_config.batch_ext_sens_3_en;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Batching in FIFO buffer of SFLP.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Batching in FIFO buffer of SFLP values.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_sflp_batch_set(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_fifo_sflp_raw_t val)
{
  lsm6dsv16x_emb_func_fifo_en_a_t emb_func_fifo_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_A, (uint8_t *)&emb_func_fifo_en_a, 1);
    emb_func_fifo_en_a.sflp_game_fifo_en = val.game_rotation;
    emb_func_fifo_en_a.sflp_gravity_fifo_en = val.gravity;
    emb_func_fifo_en_a.sflp_gbias_fifo_en = val.gbias;
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_A,
                                (uint8_t *)&emb_func_fifo_en_a, 1);
  }

  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  return ret;
}

/**
  * @brief  Batching in FIFO buffer of SFLP.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Batching in FIFO buffer of SFLP values.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fifo_sflp_batch_get(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_fifo_sflp_raw_t *val)
{
  lsm6dsv16x_emb_func_fifo_en_a_t emb_func_fifo_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_FIFO_EN_A, (uint8_t *)&emb_func_fifo_en_a, 1);

    val->game_rotation = emb_func_fifo_en_a.sflp_game_fifo_en;
    val->gravity = emb_func_fifo_en_a.sflp_gravity_fifo_en;
    val->gbias = emb_func_fifo_en_a.sflp_gbias_fifo_en;
  }

  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Filters
  * @brief     This section group all the functions concerning the
  *            filters configuration
  * @{
  *
  */

/**
  * @brief  Protocol anti-spike filters.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      AUTO, ALWAYS_ACTIVE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_anti_spike_set(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_filt_anti_spike_t val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);

  if (ret == 0)
  {
    if_cfg.asf_ctrl = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Protocol anti-spike filters.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      AUTO, ALWAYS_ACTIVE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_anti_spike_get(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_filt_anti_spike_t *val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  switch (if_cfg.asf_ctrl)
  {
    case LSM6DSV16X_AUTO:
      *val = LSM6DSV16X_AUTO;
      break;

    case LSM6DSV16X_ALWAYS_ACTIVE:
      *val = LSM6DSV16X_ALWAYS_ACTIVE;
      break;

    default:
      *val = LSM6DSV16X_AUTO;
      break;
  }
  return ret;
}

/**
  * @brief  It masks DRDY and Interrupts RQ until filter settling ends.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      It masks DRDY and Interrupts RQ until filter settling ends.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_settling_mask_set(stmdev_ctx_t *ctx,
                                          lsm6dsv16x_filt_settling_mask_t val)
{
  lsm6dsv16x_emb_func_cfg_t emb_func_cfg;
  lsm6dsv16x_ui_int_ois_t ui_int_ois;
  lsm6dsv16x_ctrl4_t ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL4, (uint8_t *)&ctrl4, 1);

  if (ret == 0)
  {
    ctrl4.drdy_mask = val.drdy;

    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL4, (uint8_t *)&ctrl4, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_CFG, (uint8_t *)&emb_func_cfg, 1);
  }

  if (ret == 0)
  {
    emb_func_cfg.emb_func_irq_mask_xl_settl = val.irq_xl;
    emb_func_cfg.emb_func_irq_mask_g_settl = val.irq_g;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_CFG, (uint8_t *)&emb_func_cfg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_INT_OIS, (uint8_t *)&ui_int_ois, 1);
  }

  if (ret == 0)
  {
    ui_int_ois.drdy_mask_ois = val.ois_drdy;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_INT_OIS, (uint8_t *)&ui_int_ois, 1);
  }

  return ret;
}

/**
  * @brief  It masks DRDY and Interrupts RQ until filter settling ends.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      It masks DRDY and Interrupts RQ until filter settling ends.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_settling_mask_get(stmdev_ctx_t *ctx,
                                          lsm6dsv16x_filt_settling_mask_t *val)
{
  lsm6dsv16x_emb_func_cfg_t emb_func_cfg;
  lsm6dsv16x_ui_int_ois_t ui_int_ois;
  lsm6dsv16x_ctrl4_t ctrl4;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL4, (uint8_t *)&ctrl4, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_CFG, (uint8_t *)&emb_func_cfg, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_INT_OIS, (uint8_t *)&ui_int_ois, 1);
  }

  val->irq_xl = emb_func_cfg.emb_func_irq_mask_xl_settl;
  val->irq_g = emb_func_cfg.emb_func_irq_mask_g_settl;
  val->drdy = ctrl4.drdy_mask;

  return ret;
}

/**
  * @brief  It masks DRDY and Interrupts RQ until filter settling ends.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      It masks DRDY and Interrupts RQ until filter settling ends from OIS interface.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_ois_settling_mask_set(stmdev_ctx_t *ctx,
                                              lsm6dsv16x_filt_ois_settling_mask_t val)
{
  lsm6dsv16x_spi2_int_ois_t spi2_int_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SPI2_INT_OIS, (uint8_t *)&spi2_int_ois, 1);

  if (ret == 0)
  {
    spi2_int_ois.drdy_mask_ois = val.ois_drdy;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SPI2_INT_OIS, (uint8_t *)&spi2_int_ois, 1);
  }

  return ret;
}

/**
  * @brief  It masks DRDY and Interrupts RQ until filter settling ends.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      It masks DRDY and Interrupts RQ until filter settling ends.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_ois_settling_mask_get(stmdev_ctx_t *ctx,
                                              lsm6dsv16x_filt_ois_settling_mask_t *val)
{

  lsm6dsv16x_spi2_int_ois_t spi2_int_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SPI2_INT_OIS, (uint8_t *)&spi2_int_ois, 1);
  val->ois_drdy = spi2_int_ois.drdy_mask_ois;

  return ret;
}

/**
  * @brief  Gyroscope low-pass filter (LPF1) bandwidth selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_ULTRA_LIGHT, GY_VERY_LIGHT, GY_LIGHT, GY_MEDIUM, GY_STRONG, GY_VERY_STRONG, GY_AGGRESSIVE, GY_XTREME,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_gy_lp1_bandwidth_set(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_filt_gy_lp1_bandwidth_t val)
{
  lsm6dsv16x_ctrl6_t ctrl6;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL6, (uint8_t *)&ctrl6, 1);
  if (ret == 0)
  {
    ctrl6.lpf1_g_bw = (uint8_t)val & 0x0Fu;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL6, (uint8_t *)&ctrl6, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope low-pass filter (LPF1) bandwidth selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GY_ULTRA_LIGHT, GY_VERY_LIGHT, GY_LIGHT, GY_MEDIUM, GY_STRONG, GY_VERY_STRONG, GY_AGGRESSIVE, GY_XTREME,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_gy_lp1_bandwidth_get(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_filt_gy_lp1_bandwidth_t *val)
{
  lsm6dsv16x_ctrl6_t ctrl6;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL6, (uint8_t *)&ctrl6, 1);
  switch (ctrl6.lpf1_g_bw)
  {
    case LSM6DSV16X_GY_ULTRA_LIGHT:
      *val = LSM6DSV16X_GY_ULTRA_LIGHT;
      break;

    case LSM6DSV16X_GY_VERY_LIGHT:
      *val = LSM6DSV16X_GY_VERY_LIGHT;
      break;

    case LSM6DSV16X_GY_LIGHT:
      *val = LSM6DSV16X_GY_LIGHT;
      break;

    case LSM6DSV16X_GY_MEDIUM:
      *val = LSM6DSV16X_GY_MEDIUM;
      break;

    case LSM6DSV16X_GY_STRONG:
      *val = LSM6DSV16X_GY_STRONG;
      break;

    case LSM6DSV16X_GY_VERY_STRONG:
      *val = LSM6DSV16X_GY_VERY_STRONG;
      break;

    case LSM6DSV16X_GY_AGGRESSIVE:
      *val = LSM6DSV16X_GY_AGGRESSIVE;
      break;

    case LSM6DSV16X_GY_XTREME:
      *val = LSM6DSV16X_GY_XTREME;
      break;

    default:
      *val = LSM6DSV16X_GY_ULTRA_LIGHT;
      break;
  }
  return ret;
}

/**
  * @brief  It enables gyroscope digital LPF1 filter. If the OIS chain is disabled, the bandwidth can be selected through LPF1_G_BW.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      It enables gyroscope digital LPF1 filter. If the OIS chain is disabled, the bandwidth can be selected through LPF1_G_BW.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_gy_lp1_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl7_t ctrl7;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL7, (uint8_t *)&ctrl7, 1);
  if (ret == 0)
  {
    ctrl7.lpf1_g_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL7, (uint8_t *)&ctrl7, 1);
  }

  return ret;
}


/**
  * @brief  It enables gyroscope digital LPF1 filter. If the OIS chain is disabled, the bandwidth can be selected through LPF1_G_BW.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      It enables gyroscope digital LPF1 filter. If the OIS chain is disabled, the bandwidth can be selected through LPF1_G_BW.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_gy_lp1_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl7_t ctrl7;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL7, (uint8_t *)&ctrl7, 1);
  *val = ctrl7.lpf1_g_en;

  return ret;
}

/**
  * @brief  Accelerometer LPF2 and high pass filter configuration and cutoff setting.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ULTRA_LIGHT, XL_VERY_LIGHT, XL_LIGHT, XL_MEDIUM, XL_STRONG, XL_VERY_STRONG, XL_AGGRESSIVE, XL_XTREME,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_lp2_bandwidth_set(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_filt_xl_lp2_bandwidth_t val)
{
  lsm6dsv16x_ctrl8_t ctrl8;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL8, (uint8_t *)&ctrl8, 1);
  if (ret == 0)
  {
    ctrl8.hp_lpf2_xl_bw = (uint8_t)val & 0x07U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL8, (uint8_t *)&ctrl8, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer LPF2 and high pass filter configuration and cutoff setting.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_ULTRA_LIGHT, XL_VERY_LIGHT, XL_LIGHT, XL_MEDIUM, XL_STRONG, XL_VERY_STRONG, XL_AGGRESSIVE, XL_XTREME,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_lp2_bandwidth_get(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_filt_xl_lp2_bandwidth_t *val)
{
  lsm6dsv16x_ctrl8_t ctrl8;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL8, (uint8_t *)&ctrl8, 1);
  switch (ctrl8.hp_lpf2_xl_bw)
  {
    case LSM6DSV16X_XL_ULTRA_LIGHT:
      *val = LSM6DSV16X_XL_ULTRA_LIGHT;
      break;

    case LSM6DSV16X_XL_VERY_LIGHT:
      *val = LSM6DSV16X_XL_VERY_LIGHT;
      break;

    case LSM6DSV16X_XL_LIGHT:
      *val = LSM6DSV16X_XL_LIGHT;
      break;

    case LSM6DSV16X_XL_MEDIUM:
      *val = LSM6DSV16X_XL_MEDIUM;
      break;

    case LSM6DSV16X_XL_STRONG:
      *val = LSM6DSV16X_XL_STRONG;
      break;

    case LSM6DSV16X_XL_VERY_STRONG:
      *val = LSM6DSV16X_XL_VERY_STRONG;
      break;

    case LSM6DSV16X_XL_AGGRESSIVE:
      *val = LSM6DSV16X_XL_AGGRESSIVE;
      break;

    case LSM6DSV16X_XL_XTREME:
      *val = LSM6DSV16X_XL_XTREME;
      break;

    default:
      *val = LSM6DSV16X_XL_ULTRA_LIGHT;
      break;
  }
  return ret;
}

/**
  * @brief  Enable accelerometer LPS2 (Low Pass Filter 2) filtering stage.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable accelerometer LPS2 (Low Pass Filter 2) filtering stage.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_lp2_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  if (ret == 0)
  {
    ctrl9.lpf2_xl_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  }

  return ret;
}

/**
  * @brief  Enable accelerometer LPS2 (Low Pass Filter 2) filtering stage.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable accelerometer LPS2 (Low Pass Filter 2) filtering stage.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_lp2_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  *val = ctrl9.lpf2_xl_en;

  return ret;
}

/**
  * @brief  Accelerometer slope filter / high-pass filter selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Accelerometer slope filter / high-pass filter selection.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_hp_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  if (ret == 0)
  {
    ctrl9.hp_slope_xl_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer slope filter / high-pass filter selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Accelerometer slope filter / high-pass filter selection.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_hp_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  *val = ctrl9.hp_slope_xl_en;

  return ret;
}

/**
  * @brief  Enables accelerometer LPF2 and HPF fast-settling mode. The filter sets the first sample.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables accelerometer LPF2 and HPF fast-settling mode. The filter sets the first sample.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_fast_settling_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  if (ret == 0)
  {
    ctrl9.xl_fastsettl_mode = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  }

  return ret;
}

/**
  * @brief  Enables accelerometer LPF2 and HPF fast-settling mode. The filter sets the first sample.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables accelerometer LPF2 and HPF fast-settling mode. The filter sets the first sample.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_fast_settling_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  *val = ctrl9.xl_fastsettl_mode;

  return ret;
}

/**
  * @brief  Accelerometer high-pass filter mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      HP_MD_NORMAL, HP_MD_REFERENCE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_hp_mode_set(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_filt_xl_hp_mode_t val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  if (ret == 0)
  {
    ctrl9.hp_ref_mode_xl = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  }

  return ret;
}

/**
  * @brief  Accelerometer high-pass filter mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      HP_MD_NORMAL, HP_MD_REFERENCE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_hp_mode_get(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_filt_xl_hp_mode_t *val)
{
  lsm6dsv16x_ctrl9_t ctrl9;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL9, (uint8_t *)&ctrl9, 1);
  switch (ctrl9.hp_ref_mode_xl)
  {
    case LSM6DSV16X_HP_MD_NORMAL:
      *val = LSM6DSV16X_HP_MD_NORMAL;
      break;

    case LSM6DSV16X_HP_MD_REFERENCE:
      *val = LSM6DSV16X_HP_MD_REFERENCE;
      break;

    default:
      *val = LSM6DSV16X_HP_MD_NORMAL;
      break;
  }
  return ret;
}

/**
  * @brief  HPF or SLOPE filter selection on wake-up and Activity/Inactivity functions.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      WK_FEED_SLOPE, WK_FEED_HIGH_PASS, WK_FEED_LP_WITH_OFFSET,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_wkup_act_feed_set(stmdev_ctx_t *ctx,
                                          lsm6dsv16x_filt_wkup_act_feed_t val)
{
  lsm6dsv16x_wake_up_ths_t wake_up_ths;
  lsm6dsv16x_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_THS, (uint8_t *)&wake_up_ths, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);
  }

  if (ret == 0)
  {
    tap_cfg0.slope_fds = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);
  }
  if (ret == 0)
  {
    wake_up_ths.usr_off_on_wu = ((uint8_t)val & 0x02U) >> 1;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_WAKE_UP_THS, (uint8_t *)&wake_up_ths, 1);
  }

  return ret;
}

/**
  * @brief  HPF or SLOPE filter selection on wake-up and Activity/Inactivity functions.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      WK_FEED_SLOPE, WK_FEED_HIGH_PASS, WK_FEED_LP_WITH_OFFSET,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_wkup_act_feed_get(stmdev_ctx_t *ctx,
                                          lsm6dsv16x_filt_wkup_act_feed_t *val)
{
  lsm6dsv16x_wake_up_ths_t wake_up_ths;
  lsm6dsv16x_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_THS, (uint8_t *)&wake_up_ths, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);
  }

  switch ((wake_up_ths.usr_off_on_wu << 1) + tap_cfg0.slope_fds)
  {
    case LSM6DSV16X_WK_FEED_SLOPE:
      *val = LSM6DSV16X_WK_FEED_SLOPE;
      break;

    case LSM6DSV16X_WK_FEED_HIGH_PASS:
      *val = LSM6DSV16X_WK_FEED_HIGH_PASS;
      break;

    case LSM6DSV16X_WK_FEED_LP_WITH_OFFSET:
      *val = LSM6DSV16X_WK_FEED_LP_WITH_OFFSET;
      break;

    default:
      *val = LSM6DSV16X_WK_FEED_SLOPE;
      break;
  }
  return ret;
}

/**
  * @brief  Mask hw function triggers when xl is settling.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      0 or 1,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mask_trigger_xl_settl_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);

  if (ret == 0)
  {
    tap_cfg0.hw_func_mask_xl_settl = val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);
  }

  return ret;
}

/**
  * @brief  Mask hw function triggers when xl is settling.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      0 or 1,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mask_trigger_xl_settl_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);
  *val = tap_cfg0.hw_func_mask_xl_settl;

  return ret;
}

/**
  * @brief  LPF2 filter on 6D (sixd) function selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SIXD_FEED_ODR_DIV_2, SIXD_FEED_LOW_PASS,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_sixd_feed_set(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_filt_sixd_feed_t val)
{
  lsm6dsv16x_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);

  if (ret == 0)
  {
    tap_cfg0.low_pass_on_6d = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);
  }

  return ret;
}

/**
  * @brief  LPF2 filter on 6D (sixd) function selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SIXD_FEED_ODR_DIV_2, SIXD_FEED_LOW_PASS,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_sixd_feed_get(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_filt_sixd_feed_t *val)
{
  lsm6dsv16x_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);

  switch (tap_cfg0.low_pass_on_6d)
  {
    case LSM6DSV16X_SIXD_FEED_ODR_DIV_2:
      *val = LSM6DSV16X_SIXD_FEED_ODR_DIV_2;
      break;

    case LSM6DSV16X_SIXD_FEED_LOW_PASS:
      *val = LSM6DSV16X_SIXD_FEED_LOW_PASS;
      break;

    default:
      *val = LSM6DSV16X_SIXD_FEED_ODR_DIV_2;
      break;
  }
  return ret;
}

/**
  * @brief  Gyroscope digital LPF_EIS filter bandwidth selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      EIS_LP_NORMAL, EIS_LP_LIGHT,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_gy_eis_lp_bandwidth_set(stmdev_ctx_t *ctx,
                                                lsm6dsv16x_filt_gy_eis_lp_bandwidth_t val)
{
  lsm6dsv16x_ctrl_eis_t ctrl_eis;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);

  if (ret == 0)
  {
    ctrl_eis.lpf_g_eis_bw = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope digital LPF_EIS filter bandwidth selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      EIS_LP_NORMAL, EIS_LP_LIGHT,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_gy_eis_lp_bandwidth_get(stmdev_ctx_t *ctx,
                                                lsm6dsv16x_filt_gy_eis_lp_bandwidth_t *val)
{
  lsm6dsv16x_ctrl_eis_t ctrl_eis;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL_EIS, (uint8_t *)&ctrl_eis, 1);

  switch (ctrl_eis.lpf_g_eis_bw)
  {
    case LSM6DSV16X_EIS_LP_NORMAL:
      *val = LSM6DSV16X_EIS_LP_NORMAL;
      break;

    case LSM6DSV16X_EIS_LP_LIGHT:
      *val = LSM6DSV16X_EIS_LP_LIGHT;
      break;

    default:
      *val = LSM6DSV16X_EIS_LP_NORMAL;
      break;
  }
  return ret;
}

/**
  * @brief  Gyroscope OIS digital LPF1 filter bandwidth selection. This function works also on OIS interface (SPI2_CTRL2_OIS = UI_CTRL2_OIS).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_GY_LP_NORMAL, OIS_GY_LP_STRONG, OIS_GY_LP_AGGRESSIVE, OIS_GY_LP_LIGHT,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_gy_ois_lp_bandwidth_set(stmdev_ctx_t *ctx,
                                                lsm6dsv16x_filt_gy_ois_lp_bandwidth_t val)
{
  lsm6dsv16x_ui_ctrl2_ois_t ui_ctrl2_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL2_OIS, (uint8_t *)&ui_ctrl2_ois, 1);

  if (ret == 0)
  {
    ui_ctrl2_ois.lpf1_g_ois_bw = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_CTRL2_OIS, (uint8_t *)&ui_ctrl2_ois, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope OIS digital LPF1 filter bandwidth selection. This function works also on OIS interface (SPI2_CTRL2_OIS = UI_CTRL2_OIS).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_GY_LP_NORMAL, OIS_GY_LP_STRONG, OIS_GY_LP_AGGRESSIVE, OIS_GY_LP_LIGHT,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_gy_ois_lp_bandwidth_get(stmdev_ctx_t *ctx,
                                                lsm6dsv16x_filt_gy_ois_lp_bandwidth_t *val)
{

  lsm6dsv16x_ui_ctrl2_ois_t ui_ctrl2_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL2_OIS, (uint8_t *)&ui_ctrl2_ois, 1);

  switch (ui_ctrl2_ois.lpf1_g_ois_bw)
  {
    case LSM6DSV16X_OIS_GY_LP_NORMAL:
      *val = LSM6DSV16X_OIS_GY_LP_NORMAL;
      break;

    case LSM6DSV16X_OIS_GY_LP_STRONG:
      *val = LSM6DSV16X_OIS_GY_LP_STRONG;
      break;

    case LSM6DSV16X_OIS_GY_LP_AGGRESSIVE:
      *val = LSM6DSV16X_OIS_GY_LP_AGGRESSIVE;
      break;

    case LSM6DSV16X_OIS_GY_LP_LIGHT:
      *val = LSM6DSV16X_OIS_GY_LP_LIGHT;
      break;

    default:
      *val = LSM6DSV16X_OIS_GY_LP_NORMAL;
      break;
  }
  return ret;
}

/**
  * @brief  Selects accelerometer OIS channel bandwidth. This function works also on OIS interface (SPI2_CTRL3_OIS = UI_CTRL3_OIS).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_XL_LP_ULTRA_LIGHT, OIS_XL_LP_VERY_LIGHT, OIS_XL_LP_LIGHT, OIS_XL_LP_NORMAL, OIS_XL_LP_STRONG, OIS_XL_LP_VERY_STRONG, OIS_XL_LP_AGGRESSIVE, OIS_XL_LP_XTREME,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_ois_lp_bandwidth_set(stmdev_ctx_t *ctx,
                                                lsm6dsv16x_filt_xl_ois_lp_bandwidth_t val)
{
  lsm6dsv16x_ui_ctrl3_ois_t ui_ctrl3_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL3_OIS, (uint8_t *)&ui_ctrl3_ois, 1);

  if (ret == 0)
  {
    ui_ctrl3_ois.lpf_xl_ois_bw = (uint8_t)val & 0x07U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_CTRL3_OIS, (uint8_t *)&ui_ctrl3_ois, 1);
  }

  return ret;
}

/**
  * @brief  Selects accelerometer OIS channel bandwidth. This function works also on OIS interface (SPI2_CTRL3_OIS = UI_CTRL3_OIS).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_XL_LP_ULTRA_LIGHT, OIS_XL_LP_VERY_LIGHT, OIS_XL_LP_LIGHT, OIS_XL_LP_NORMAL, OIS_XL_LP_STRONG, OIS_XL_LP_VERY_STRONG, OIS_XL_LP_AGGRESSIVE, OIS_XL_LP_XTREME,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_filt_xl_ois_lp_bandwidth_get(stmdev_ctx_t *ctx,
                                                lsm6dsv16x_filt_xl_ois_lp_bandwidth_t *val)
{
  lsm6dsv16x_ui_ctrl3_ois_t ui_ctrl3_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL3_OIS, (uint8_t *)&ui_ctrl3_ois, 1);

  switch (ui_ctrl3_ois.lpf_xl_ois_bw)
  {
    case LSM6DSV16X_OIS_XL_LP_ULTRA_LIGHT:
      *val = LSM6DSV16X_OIS_XL_LP_ULTRA_LIGHT;
      break;

    case LSM6DSV16X_OIS_XL_LP_VERY_LIGHT:
      *val = LSM6DSV16X_OIS_XL_LP_VERY_LIGHT;
      break;

    case LSM6DSV16X_OIS_XL_LP_LIGHT:
      *val = LSM6DSV16X_OIS_XL_LP_LIGHT;
      break;

    case LSM6DSV16X_OIS_XL_LP_NORMAL:
      *val = LSM6DSV16X_OIS_XL_LP_NORMAL;
      break;

    case LSM6DSV16X_OIS_XL_LP_STRONG:
      *val = LSM6DSV16X_OIS_XL_LP_STRONG;
      break;

    case LSM6DSV16X_OIS_XL_LP_VERY_STRONG:
      *val = LSM6DSV16X_OIS_XL_LP_VERY_STRONG;
      break;

    case LSM6DSV16X_OIS_XL_LP_AGGRESSIVE:
      *val = LSM6DSV16X_OIS_XL_LP_AGGRESSIVE;
      break;

    case LSM6DSV16X_OIS_XL_LP_XTREME:
      *val = LSM6DSV16X_OIS_XL_LP_XTREME;
      break;

    default:
      *val = LSM6DSV16X_OIS_XL_LP_ULTRA_LIGHT;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Finite State Machine (FSM)
  * @brief     This section groups all the functions that manage the
  *            state_machine.
  * @{
  *
  */

/**
  * @brief  Enables the control of the CTRL registers to FSM (FSM can change some configurations of the device autonomously).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      PROTECT_CTRL_REGS, WRITE_CTRL_REG,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_permission_set(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_fsm_permission_t val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);

  if (ret == 0)
  {
    func_cfg_access.fsm_wr_ctrl_en = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  }

  return ret;
}

/**
  * @brief  Enables the control of the CTRL registers to FSM (FSM can change some configurations of the device autonomously).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      PROTECT_CTRL_REGS, WRITE_CTRL_REG,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_permission_get(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_fsm_permission_t *val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);

  switch (func_cfg_access.fsm_wr_ctrl_en)
  {
    case LSM6DSV16X_PROTECT_CTRL_REGS:
      *val = LSM6DSV16X_PROTECT_CTRL_REGS;
      break;

    case LSM6DSV16X_WRITE_CTRL_REG:
      *val = LSM6DSV16X_WRITE_CTRL_REG;
      break;

    default:
      *val = LSM6DSV16X_PROTECT_CTRL_REGS;
      break;
  }
  return ret;
}

/**
  * @brief  Get the FSM permission status
  *
  * @param  ctx      read / write interface definitions
  * @param  val      0: All reg writable from std if - 1: some regs are under FSM control.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_permission_status(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ctrl_status_t ctrl_status;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL_STATUS, (uint8_t *)&ctrl_status, 1);

  *val = ctrl_status.fsm_wr_ctrl_status;

  return ret;
}

/**
  * @brief  Enable Finite State Machine (FSM) feature.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable Finite State Machine (FSM) feature.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_mode_set(stmdev_ctx_t *ctx, lsm6dsv16x_fsm_mode_t val)
{
  lsm6dsv16x_emb_func_en_b_t emb_func_en_b;
  lsm6dsv16x_fsm_enable_t fsm_enable;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_B, (uint8_t *)&emb_func_en_b, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FSM_ENABLE, (uint8_t *)&fsm_enable, 1);
  }
  if ((val.fsm1_en | val.fsm2_en | val.fsm1_en | val.fsm1_en
       | val.fsm1_en | val.fsm2_en | val.fsm1_en | val.fsm1_en) == PROPERTY_ENABLE)
  {
    emb_func_en_b.fsm_en = PROPERTY_ENABLE;
  }
  else
  {
    emb_func_en_b.fsm_en = PROPERTY_DISABLE;
  }
  if (ret == 0)
  {
    fsm_enable.fsm1_en = val.fsm1_en;
    fsm_enable.fsm2_en = val.fsm2_en;
    fsm_enable.fsm3_en = val.fsm3_en;
    fsm_enable.fsm4_en = val.fsm4_en;
    fsm_enable.fsm5_en = val.fsm5_en;
    fsm_enable.fsm6_en = val.fsm6_en;
    fsm_enable.fsm7_en = val.fsm7_en;
    fsm_enable.fsm8_en = val.fsm8_en;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FSM_ENABLE, (uint8_t *)&fsm_enable, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_B, (uint8_t *)&emb_func_en_b, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Enable Finite State Machine (FSM) feature.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable Finite State Machine (FSM) feature.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_mode_get(stmdev_ctx_t *ctx, lsm6dsv16x_fsm_mode_t *val)
{
  lsm6dsv16x_fsm_enable_t fsm_enable;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FSM_ENABLE, (uint8_t *)&fsm_enable, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  val->fsm1_en = fsm_enable.fsm1_en;
  val->fsm2_en = fsm_enable.fsm2_en;
  val->fsm3_en = fsm_enable.fsm3_en;
  val->fsm4_en = fsm_enable.fsm4_en;
  val->fsm5_en = fsm_enable.fsm5_en;
  val->fsm6_en = fsm_enable.fsm6_en;
  val->fsm7_en = fsm_enable.fsm7_en;
  val->fsm8_en = fsm_enable.fsm8_en;

  return ret;
}

/**
  * @brief  FSM long counter status register. Long counter value is an unsigned integer value (16-bit format).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM long counter status register. Long counter value is an unsigned integer value (16-bit format).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_long_cnt_set(stmdev_ctx_t *ctx, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));

  ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FSM_LONG_COUNTER_L, (uint8_t *)&buff[0], 2);
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  FSM long counter status register. Long counter value is an unsigned integer value (16-bit format).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM long counter status register. Long counter value is an unsigned integer value (16-bit format).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_long_cnt_get(stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FSM_LONG_COUNTER_L, &buff[0], 2);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  *val = buff[1];
  *val = (*val * 256U) + buff[0];

  return ret;
}

/**
  * @brief  FSM output registers[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM output registers
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_out_get(stmdev_ctx_t *ctx, lsm6dsv16x_fsm_out_t *val)
{
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FSM_OUTS1, (uint8_t *)val, 8);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Finite State Machine Output Data Rate (ODR) configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM_15Hz, FSM_30Hz, FSM_60Hz, FSM_120Hz, FSM_240Hz, FSM_480Hz, FSM_960Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_data_rate_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_fsm_data_rate_t val)
{
  lsm6dsv16x_fsm_odr_t fsm_odr;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FSM_ODR, (uint8_t *)&fsm_odr, 1);
  }

  if (ret == 0)
  {
    fsm_odr.fsm_odr = (uint8_t)val & 0x07U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FSM_ODR, (uint8_t *)&fsm_odr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Finite State Machine Output Data Rate (ODR) configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM_15Hz, FSM_30Hz, FSM_60Hz, FSM_120Hz, FSM_240Hz, FSM_480Hz, FSM_960Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_data_rate_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_fsm_data_rate_t *val)
{
  lsm6dsv16x_fsm_odr_t fsm_odr;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FSM_ODR, (uint8_t *)&fsm_odr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }


  switch (fsm_odr.fsm_odr)
  {
    case LSM6DSV16X_FSM_15Hz:
      *val = LSM6DSV16X_FSM_15Hz;
      break;

    case LSM6DSV16X_FSM_30Hz:
      *val = LSM6DSV16X_FSM_30Hz;
      break;

    case LSM6DSV16X_FSM_60Hz:
      *val = LSM6DSV16X_FSM_60Hz;
      break;

    case LSM6DSV16X_FSM_120Hz:
      *val = LSM6DSV16X_FSM_120Hz;
      break;

    case LSM6DSV16X_FSM_240Hz:
      *val = LSM6DSV16X_FSM_240Hz;
      break;

    case LSM6DSV16X_FSM_480Hz:
      *val = LSM6DSV16X_FSM_480Hz;
      break;

    case LSM6DSV16X_FSM_960Hz:
      *val = LSM6DSV16X_FSM_960Hz;
      break;

    default:
      *val = LSM6DSV16X_FSM_15Hz;
      break;
  }
  return ret;
}

/*
 * Original conversion routines taken from: https://github.com/numpy/numpy
 *
 * uint16_t npy_floatbits_to_halfbits(uint32_t f);
 * uint16_t npy_float_to_half(float_t f);
 *
 * Released under BSD-3-Clause License
 */
static uint16_t npy_floatbits_to_halfbits(uint32_t f)
{
  uint32_t f_exp, f_sig;
  uint16_t h_sgn, h_exp, h_sig;

  h_sgn = (uint16_t)((f & 0x80000000u) >> 16);
  f_exp = (f & 0x7f800000u);

  /* Exponent overflow/NaN converts to signed inf/NaN */
  if (f_exp >= 0x47800000u)
  {
    if (f_exp == 0x7f800000u)
    {
      /* Inf or NaN */
      f_sig = (f & 0x007fffffu);
      if (f_sig != 0)
      {
        /* NaN - propagate the flag in the significand... */
        uint16_t ret = (uint16_t)(0x7c00u + (f_sig >> 13));
        /* ...but make sure it stays a NaN */
        if (ret == 0x7c00u)
        {
          ret++;
        }
        return h_sgn + ret;
      }
      else
      {
        /* signed inf */
        return (uint16_t)(h_sgn + 0x7c00u);
      }
    }
    else
    {
      /* overflow to signed inf */
#if NPY_HALF_GENERATE_OVERFLOW
      npy_set_floatstatus_overflow();
#endif
      return (uint16_t)(h_sgn + 0x7c00u);
    }
  }

  /* Exponent underflow converts to a subnormal half or signed zero */
  if (f_exp <= 0x38000000u)
  {
    /*
     * Signed zeros, subnormal floats, and floats with small
     * exponents all convert to signed zero half-floats.
     */
    if (f_exp < 0x33000000u)
    {
#if NPY_HALF_GENERATE_UNDERFLOW
      /* If f != 0, it underflowed to 0 */
      if ((f & 0x7fffffff) != 0)
      {
        npy_set_floatstatus_underflow();
      }
#endif
      return h_sgn;
    }
    /* Make the subnormal significand */
    f_exp >>= 23;
    f_sig = (0x00800000u + (f & 0x007fffffu));
#if NPY_HALF_GENERATE_UNDERFLOW
    /* If it's not exactly represented, it underflowed */
    if ((f_sig & (((uint32_t)1 << (126 - f_exp)) - 1)) != 0)
    {
      npy_set_floatstatus_underflow();
    }
#endif
    /*
     * Usually the significand is shifted by 13. For subnormals an
     * additional shift needs to occur. This shift is one for the largest
     * exponent giving a subnormal `f_exp = 0x38000000 >> 23 = 112`, which
     * offsets the new first bit. At most the shift can be 1+10 bits.
     */
    f_sig >>= (113 - f_exp);
    /* Handle rounding by adding 1 to the bit beyond half precision */
#if NPY_HALF_ROUND_TIES_TO_EVEN
    /*
     * If the last bit in the half significand is 0 (already even), and
     * the remaining bit pattern is 1000...0, then we do not add one
     * to the bit after the half significand. However, the (113 - f_exp)
     * shift can lose up to 11 bits, so the || checks them in the original.
     * In all other cases, we can just add one.
     */
    if (((f_sig & 0x00003fffu) != 0x00001000u) || (f & 0x000007ffu))
    {
      f_sig += 0x00001000u;
    }
#else
    f_sig += 0x00001000u;
#endif
    h_sig = (uint16_t)(f_sig >> 13);
    /*
     * If the rounding causes a bit to spill into h_exp, it will
     * increment h_exp from zero to one and h_sig will be zero.
     * This is the correct result.
     */
    return (uint16_t)(h_sgn + h_sig);
  }

  /* Regular case with no overflow or underflow */
  h_exp = (uint16_t)((f_exp - 0x38000000u) >> 13);
  /* Handle rounding by adding 1 to the bit beyond half precision */
  f_sig = (f & 0x007fffffu);
#if NPY_HALF_ROUND_TIES_TO_EVEN
  /*
   * If the last bit in the half significand is 0 (already even), and
   * the remaining bit pattern is 1000...0, then we do not add one
   * to the bit after the half significand.  In all other cases, we do.
   */
  if ((f_sig & 0x00003fffu) != 0x00001000u)
  {
    f_sig += 0x00001000u;
  }
#else
  f_sig += 0x00001000u;
#endif
  h_sig = (uint16_t)(f_sig >> 13);
  /*
   * If the rounding causes a bit to spill into h_exp, it will
   * increment h_exp by one and h_sig will be zero.  This is the
   * correct result.  h_exp may increment to 15, at greatest, in
   * which case the result overflows to a signed inf.
   */
#if NPY_HALF_GENERATE_OVERFLOW
  h_sig += h_exp;
  if (h_sig == 0x7c00u)
  {
    npy_set_floatstatus_overflow();
  }
  return h_sgn + h_sig;
#else
  return h_sgn + h_exp + h_sig;
#endif
}

static uint16_t npy_float_to_half(float_t f)
{
  union
  {
    float_t f;
    uint32_t fbits;
  } conv;
  conv.f = f;
  return npy_floatbits_to_halfbits(conv.fbits);
}

/**
  * @brief  SFLP GBIAS value. The register value is expressed as half-precision
  *         floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent
  *          bits; F: 10 fraction bits).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      GBIAS x/y/z val.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sflp_game_gbias_set(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_sflp_gbias_t *val)
{
  lsm6dsv16x_sflp_data_rate_t sflp_odr;
  lsm6dsv16x_emb_func_exec_status_t emb_func_sts;
  lsm6dsv16x_data_ready_t drdy;
  lsm6dsv16x_xl_full_scale_t xl_fs;
  lsm6dsv16x_ctrl10_t ctrl10;
  uint8_t master_config;
  uint8_t emb_func_en_saved[2];
  uint8_t conf_saved[2];
  uint8_t reg_zero[2] = {0x0, 0x0};
  uint16_t gbias_hf[3];
  float_t k = 0.005f;
  int16_t xl_data[3];
  int32_t data_tmp;
  uint8_t *data_ptr = (uint8_t *)&data_tmp;
  uint8_t i, j;
  int32_t ret;

  ret = lsm6dsv16x_sflp_data_rate_get(ctx, &sflp_odr);
  if (ret != 0)
  {
    return ret;
  }

  /* Calculate k factor */
  switch (sflp_odr)
  {
    case LSM6DSV16X_SFLP_15Hz:
      k = 0.04f;
      break;
    case LSM6DSV16X_SFLP_30Hz:
      k = 0.02f;
      break;
    case LSM6DSV16X_SFLP_60Hz:
      k = 0.01f;
      break;
    case LSM6DSV16X_SFLP_120Hz:
      k = 0.005f;
      break;
    case LSM6DSV16X_SFLP_240Hz:
      k = 0.0025f;
      break;
    case LSM6DSV16X_SFLP_480Hz:
      k = 0.00125f;
      break;
  }

  /* compute gbias as half precision float in order to be put in embedded advanced feature register */
  gbias_hf[0] = npy_float_to_half(val->gbias_x * (3.14159265358979323846f / 180.0f) / k);
  gbias_hf[1] = npy_float_to_half(val->gbias_y * (3.14159265358979323846f / 180.0f) / k);
  gbias_hf[2] = npy_float_to_half(val->gbias_z * (3.14159265358979323846f / 180.0f) / k);

  /* Save sensor configuration and set high-performance mode (if the sensor is in power-down mode, turn it on) */
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL1, conf_saved, 2);
  ret += lsm6dsv16x_xl_mode_set(ctx, LSM6DSV16X_XL_HIGH_PERFORMANCE_MD);
  ret += lsm6dsv16x_gy_mode_set(ctx, LSM6DSV16X_GY_HIGH_PERFORMANCE_MD);
  if ((conf_saved[0] & 0x0FU) == LSM6DSV16X_XL_ODR_OFF)
  {
    ret += lsm6dsv16x_xl_data_rate_set(ctx, LSM6DSV16X_XL_ODR_AT_120Hz);
  }

  /* Make sure to turn the sensor-hub master off */
  ret += lsm6dsv16x_sh_master_get(ctx, &master_config);
  ret += lsm6dsv16x_sh_master_set(ctx, 0);

  /* disable algos */
  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, emb_func_en_saved, 2);
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, reg_zero, 2);
  do
  {
    ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EXEC_STATUS,
                               (uint8_t *)&emb_func_sts, 1);
  } while (emb_func_sts.emb_func_endop != 1);
  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  // enable gbias setting
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);
  ctrl10.emb_func_debug = 1;
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);

  /* enable algos */
  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  emb_func_en_saved[0] |= 0x02; /* force SFLP GAME en */
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, emb_func_en_saved,
                              2);
  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  ret += lsm6dsv16x_xl_full_scale_get(ctx, &xl_fs);

  /* Read XL data */
  do
  {
    ret += lsm6dsv16x_flag_data_ready_get(ctx, &drdy);
  } while (drdy.drdy_xl != 1);
  ret += lsm6dsv16x_acceleration_raw_get(ctx, xl_data);

  /* force sflp initialization */
  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  for (i = 0; i < 3; i++)
  {
    j = 0;
    data_tmp = (int32_t)xl_data[i];
    data_tmp <<= xl_fs; // shift based on current fs
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SENSOR_HUB_1 + 3 * i,
                                &data_ptr[j++], 1);
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SENSOR_HUB_2 + 3 * i,
                                &data_ptr[j++], 1);
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SENSOR_HUB_3 + 3 * i, &data_ptr[j],
                                1);
  }
  for (i = 0; i < 3; i++)
  {
    j = 0;
    data_tmp = 0;
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SENSOR_HUB_10 + 3 * i,
                                &data_ptr[j++], 1);
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SENSOR_HUB_11 + 3 * i,
                                &data_ptr[j++], 1);
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SENSOR_HUB_12 + 3 * i, &data_ptr[j],
                                1);
  }
  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  // wait end_op (and at least 30 us)
  ctx->mdelay(1);
  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  do
  {
    ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EXEC_STATUS,
                               (uint8_t *)&emb_func_sts, 1);
  } while (emb_func_sts.emb_func_endop != 1);
  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  /* write gbias in embedded advanced features registers */
  ret += lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_SFLP_GAME_GBIASX_L,
                                (uint8_t *)gbias_hf, 6);

  /* reload previous sensor configuration */
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL1, conf_saved, 2);

  // disable gbias setting
  ctrl10.emb_func_debug = 0;
  ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL10, (uint8_t *)&ctrl10, 1);

  /* reload previous master configuration */
  ret += lsm6dsv16x_sh_master_set(ctx, master_config);

  return ret;
}

/**
  * @brief  External sensor sensitivity value register for the Finite State Machine (r/w). This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). Default value is 0x1624 (when using an external magnetometer this value corresponds to 0.0015 gauss/LSB).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      External sensor sensitivity value register for the Finite State Machine (r/w). This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). Default value is 0x1624 (when using an external magnetometer this value corresponds to 0.0015 gauss/LSB).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_sensitivity_set(stmdev_ctx_t *ctx, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_FSM_EXT_SENSITIVITY_L, (uint8_t *)&buff[0], 2);

  return ret;
}

/**
  * @brief  External sensor sensitivity value register for the Finite State Machine (r/w). This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). Default value is 0x1624 (when using an external magnetometer this value corresponds to 0.0015 gauss/LSB).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      External sensor sensitivity value register for the Finite State Machine (r/w). This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). Default value is 0x1624 (when using an external magnetometer this value corresponds to 0.0015 gauss/LSB).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_sensitivity_get(stmdev_ctx_t *ctx,
                                                uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_FSM_EXT_SENSITIVITY_L, &buff[0], 2);
  *val = buff[1];
  *val = (*val * 256U) + buff[0];

  return ret;
}

/**
  * @brief  External sensor offsets (X,Y,Z). The values are expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      External sensor offsets (X,Y,Z). The values are expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_offset_set(stmdev_ctx_t *ctx,
                                           lsm6dsv16x_xl_fsm_ext_sens_offset_t val)
{
  uint8_t buff[6];
  int32_t ret;

  buff[1] = (uint8_t)(val.x / 256U);
  buff[0] = (uint8_t)(val.x - (buff[1] * 256U));
  buff[3] = (uint8_t)(val.y / 256U);
  buff[2] = (uint8_t)(val.y - (buff[3] * 256U));
  buff[5] = (uint8_t)(val.z / 256U);
  buff[4] = (uint8_t)(val.z - (buff[5] * 256U));
  ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_FSM_EXT_OFFX_L, (uint8_t *)&buff[0], 6);

  return ret;
}

/**
  * @brief  External sensor offsets (X,Y,Z). The values are expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      External sensor offsets (X,Y,Z). The values are expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_offset_get(stmdev_ctx_t *ctx,
                                           lsm6dsv16x_xl_fsm_ext_sens_offset_t *val)
{
  uint8_t buff[6];
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_FSM_EXT_OFFX_L, &buff[0], 6);

  val->x = buff[1];
  val->x = (val->x * 256U) + buff[0];
  val->y = buff[3];
  val->y = (val->y * 256U) + buff[2];
  val->z = buff[5];
  val->z = (val->z * 256U) + buff[4];

  return ret;
}

/**
  * @brief  External sensor transformation matrix. The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      External sensor transformation matrix. The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_matrix_set(stmdev_ctx_t *ctx,
                                           lsm6dsv16x_xl_fsm_ext_sens_matrix_t val)
{
  uint8_t buff[12];
  int32_t ret;

  buff[1] = (uint8_t)(val.xx / 256U);
  buff[0] = (uint8_t)(val.xx - (buff[1] * 256U));
  buff[3] = (uint8_t)(val.xy / 256U);
  buff[2] = (uint8_t)(val.xy - (buff[3] * 256U));
  buff[5] = (uint8_t)(val.xz / 256U);
  buff[4] = (uint8_t)(val.xz - (buff[5] * 256U));
  buff[7] = (uint8_t)(val.yy / 256U);
  buff[6] = (uint8_t)(val.yy - (buff[7] * 256U));
  buff[9] = (uint8_t)(val.yz / 256U);
  buff[8] = (uint8_t)(val.yz - (buff[9] * 256U));
  buff[11] = (uint8_t)(val.zz / 256U);
  buff[10] = (uint8_t)(val.zz - (buff[11] * 256U));
  ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_FSM_EXT_MATRIX_XX_L, (uint8_t *)&buff[0], 12);

  return ret;
}

/**
  * @brief  External sensor transformation matrix. The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      External sensor transformation matrix. The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_matrix_get(stmdev_ctx_t *ctx,
                                           lsm6dsv16x_xl_fsm_ext_sens_matrix_t *val)
{
  uint8_t buff[12];
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_FSM_EXT_MATRIX_XX_L, &buff[0], 12);

  val->xx = buff[1];
  val->xx = (val->xx * 256U) + buff[0];
  val->xy = buff[3];
  val->xy = (val->xy * 256U) + buff[2];
  val->xz = buff[5];
  val->xz = (val->xz * 256U) + buff[4];
  val->yy = buff[7];
  val->yy = (val->yy * 256U) + buff[6];
  val->yz = buff[9];
  val->yz = (val->yz * 256U) + buff[8];
  val->zz = buff[11];
  val->zz = (val->zz * 256U) + buff[10];

  return ret;
}

/**
  * @brief  External sensor z-axis coordinates rotation.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Z_EQ_Y, Z_EQ_MIN_Y, Z_EQ_X, Z_EQ_MIN_X, Z_EQ_MIN_Z, Z_EQ_Z,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_z_orient_set(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_fsm_ext_sens_z_orient_t val)
{
  lsm6dsv16x_ext_cfg_a_t ext_cfg_a;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EXT_CFG_A, (uint8_t *)&ext_cfg_a, 1);
  if (ret == 0)
  {
    ext_cfg_a.ext_z_axis = (uint8_t)val & 0x07U;
    ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EXT_CFG_A, (uint8_t *)&ext_cfg_a, 1);
  }

  return ret;
}

/**
  * @brief  External sensor z-axis coordinates rotation.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Z_EQ_Y, Z_EQ_MIN_Y, Z_EQ_X, Z_EQ_MIN_X, Z_EQ_MIN_Z, Z_EQ_Z,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_z_orient_get(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_fsm_ext_sens_z_orient_t *val)
{
  lsm6dsv16x_ext_cfg_a_t ext_cfg_a;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EXT_CFG_A, (uint8_t *)&ext_cfg_a, 1);
  switch (ext_cfg_a.ext_z_axis)
  {
    case LSM6DSV16X_Z_EQ_Y:
      *val = LSM6DSV16X_Z_EQ_Y;
      break;

    case LSM6DSV16X_Z_EQ_MIN_Y:
      *val = LSM6DSV16X_Z_EQ_MIN_Y;
      break;

    case LSM6DSV16X_Z_EQ_X:
      *val = LSM6DSV16X_Z_EQ_X;
      break;

    case LSM6DSV16X_Z_EQ_MIN_X:
      *val = LSM6DSV16X_Z_EQ_MIN_X;
      break;

    case LSM6DSV16X_Z_EQ_MIN_Z:
      *val = LSM6DSV16X_Z_EQ_MIN_Z;
      break;

    case LSM6DSV16X_Z_EQ_Z:
      *val = LSM6DSV16X_Z_EQ_Z;
      break;

    default:
      *val = LSM6DSV16X_Z_EQ_Y;
      break;
  }
  return ret;
}

/**
  * @brief  External sensor Y-axis coordinates rotation.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Y_EQ_Y, Y_EQ_MIN_Y, Y_EQ_X, Y_EQ_MIN_X, Y_EQ_MIN_Z, Y_EQ_Z,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_y_orient_set(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_fsm_ext_sens_y_orient_t val)
{
  lsm6dsv16x_ext_cfg_a_t ext_cfg_a;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EXT_CFG_A, (uint8_t *)&ext_cfg_a, 1);
  if (ret == 0)
  {
    ext_cfg_a.ext_y_axis = (uint8_t)val & 0x7U;
    ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EXT_CFG_A, (uint8_t *)&ext_cfg_a, 1);
  }

  return ret;
}

/**
  * @brief  External sensor Y-axis coordinates rotation.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Y_EQ_Y, Y_EQ_MIN_Y, Y_EQ_X, Y_EQ_MIN_X, Y_EQ_MIN_Z, Y_EQ_Z,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_y_orient_get(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_fsm_ext_sens_y_orient_t *val)
{
  lsm6dsv16x_ext_cfg_a_t ext_cfg_a;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EXT_CFG_A, (uint8_t *)&ext_cfg_a, 1);
  switch (ext_cfg_a.ext_y_axis)
  {
    case LSM6DSV16X_Y_EQ_Y:
      *val = LSM6DSV16X_Y_EQ_Y;
      break;

    case LSM6DSV16X_Y_EQ_MIN_Y:
      *val = LSM6DSV16X_Y_EQ_MIN_Y;
      break;

    case LSM6DSV16X_Y_EQ_X:
      *val = LSM6DSV16X_Y_EQ_X;
      break;

    case LSM6DSV16X_Y_EQ_MIN_X:
      *val = LSM6DSV16X_Y_EQ_MIN_X;
      break;

    case LSM6DSV16X_Y_EQ_MIN_Z:
      *val = LSM6DSV16X_Y_EQ_MIN_Z;
      break;

    case LSM6DSV16X_Y_EQ_Z:
      *val = LSM6DSV16X_Y_EQ_Z;
      break;

    default:
      *val = LSM6DSV16X_Y_EQ_Y;
      break;
  }
  return ret;
}

/**
  * @brief  External sensor X-axis coordinates rotation.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      X_EQ_Y, X_EQ_MIN_Y, X_EQ_X, X_EQ_MIN_X, X_EQ_MIN_Z, X_EQ_Z,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_x_orient_set(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_fsm_ext_sens_x_orient_t val)
{
  lsm6dsv16x_ext_cfg_b_t ext_cfg_b;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EXT_CFG_B, (uint8_t *)&ext_cfg_b, 1);
  if (ret == 0)
  {
    ext_cfg_b.ext_x_axis = (uint8_t)val & 0x7U;
    ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EXT_CFG_B, (uint8_t *)&ext_cfg_b, 1);
  }

  return ret;
}

/**
  * @brief  External sensor X-axis coordinates rotation.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      X_EQ_Y, X_EQ_MIN_Y, X_EQ_X, X_EQ_MIN_X, X_EQ_MIN_Z, X_EQ_Z,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_ext_sens_x_orient_get(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_fsm_ext_sens_x_orient_t *val)
{
  lsm6dsv16x_ext_cfg_b_t ext_cfg_b;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EXT_CFG_B, (uint8_t *)&ext_cfg_b, 1);
  switch (ext_cfg_b.ext_x_axis)
  {
    case LSM6DSV16X_X_EQ_Y:
      *val = LSM6DSV16X_X_EQ_Y;
      break;

    case LSM6DSV16X_X_EQ_MIN_Y:
      *val = LSM6DSV16X_X_EQ_MIN_Y;
      break;

    case LSM6DSV16X_X_EQ_X:
      *val = LSM6DSV16X_X_EQ_X;
      break;

    case LSM6DSV16X_X_EQ_MIN_X:
      *val = LSM6DSV16X_X_EQ_MIN_X;
      break;

    case LSM6DSV16X_X_EQ_MIN_Z:
      *val = LSM6DSV16X_X_EQ_MIN_Z;
      break;

    case LSM6DSV16X_X_EQ_Z:
      *val = LSM6DSV16X_X_EQ_Z;
      break;

    default:
      *val = LSM6DSV16X_X_EQ_Y;
      break;
  }
  return ret;
}

/**
  * @brief  FSM long counter timeout. The long counter timeout value is an unsigned integer value (16-bit format). When the long counter value reached this value, the FSM generates an interrupt.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM long counter timeout. The long counter timeout value is an unsigned integer value (16-bit format). When the long counter value reached this value, the FSM generates an interrupt.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_long_cnt_timeout_set(stmdev_ctx_t *ctx, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_FSM_LC_TIMEOUT_L, (uint8_t *)&buff[0], 2);

  return ret;
}

/**
  * @brief  FSM long counter timeout. The long counter timeout value is an unsigned integer value (16-bit format). When the long counter value reached this value, the FSM generates an interrupt.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM long counter timeout. The long counter timeout value is an unsigned integer value (16-bit format). When the long counter value reached this value, the FSM generates an interrupt.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_long_cnt_timeout_get(stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_FSM_LC_TIMEOUT_L, &buff[0], 2);
  *val = buff[1];
  *val = (*val * 256U) + buff[0];

  return ret;
}

/**
  * @brief  FSM number of programs.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM number of programs.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_number_of_programs_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_fsm_programs_t fsm_programs;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_FSM_PROGRAMS, (uint8_t *)&fsm_programs, 1);
  if (ret == 0)
  {
    fsm_programs.fsm_n_prog = val;
    ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_FSM_PROGRAMS, (uint8_t *)&fsm_programs, 1);
  }

  return ret;
}

/**
  * @brief  FSM number of programs.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM number of programs.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_number_of_programs_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_fsm_programs_t fsm_programs;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_FSM_PROGRAMS, (uint8_t *)&fsm_programs, 1);
  *val = fsm_programs.fsm_n_prog;

  return ret;
}

/**
  * @brief  FSM start address. First available address is 0x35C.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM start address. First available address is 0x35C.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_start_address_set(stmdev_ctx_t *ctx, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_FSM_START_ADD_L, (uint8_t *)&buff[0], 2);

  return ret;
}

/**
  * @brief  FSM start address. First available address is 0x35C.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      FSM start address. First available address is 0x35C.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_fsm_start_address_get(stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_FSM_START_ADD_L, &buff[0], 2);
  *val = buff[1];
  *val = (*val * 256U) + buff[0];

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Free fall
  * @brief     This section group all the functions concerning the free
  *            fall detection.
  * @{
  *
  */

/**
  * @brief  Time windows configuration for Free Fall detection 1 LSB = 1/ODR_XL time[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Time windows configuration for Free Fall detection 1 LSB = 1/ODR_XL time
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ff_time_windows_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_wake_up_dur_t wake_up_dur;
  lsm6dsv16x_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_DUR, (uint8_t *)&wake_up_dur, 1);
  if (ret == 0)
  {
    wake_up_dur.ff_dur = ((uint8_t)val & 0x20U) >> 5;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_WAKE_UP_DUR, (uint8_t *)&wake_up_dur, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FREE_FALL, (uint8_t *)&free_fall, 1);
  }

  if (ret == 0)
  {
    free_fall.ff_dur = (uint8_t)val & 0x1FU;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FREE_FALL, (uint8_t *)&free_fall, 1);
  }

  return ret;
}

/**
  * @brief  Time windows configuration for Free Fall detection 1 LSB = 1/ODR_XL time[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Time windows configuration for Free Fall detection 1 LSB = 1/ODR_XL time
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ff_time_windows_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_wake_up_dur_t wake_up_dur;
  lsm6dsv16x_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_DUR, (uint8_t *)&wake_up_dur, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FREE_FALL, (uint8_t *)&free_fall, 1);
  }

  *val = (wake_up_dur.ff_dur << 5) + free_fall.ff_dur;

  return ret;
}

/**
  * @brief  Free fall threshold setting.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      156_mg, 219_mg, 250_mg, 312_mg, 344_mg, 406_mg, 469_mg, 500_mg,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ff_thresholds_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_ff_thresholds_t val)
{
  lsm6dsv16x_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FREE_FALL, (uint8_t *)&free_fall, 1);
  if (ret == 0)
  {
    free_fall.ff_ths = (uint8_t)val & 0x7U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FREE_FALL, (uint8_t *)&free_fall, 1);
  }

  return ret;
}

/**
  * @brief  Free fall threshold setting.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      156_mg, 219_mg, 250_mg, 312_mg, 344_mg, 406_mg, 469_mg, 500_mg,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ff_thresholds_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_ff_thresholds_t *val)
{
  lsm6dsv16x_free_fall_t free_fall;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FREE_FALL, (uint8_t *)&free_fall, 1);
  switch (free_fall.ff_ths)
  {
    case LSM6DSV16X_156_mg:
      *val = LSM6DSV16X_156_mg;
      break;

    case LSM6DSV16X_219_mg:
      *val = LSM6DSV16X_219_mg;
      break;

    case LSM6DSV16X_250_mg:
      *val = LSM6DSV16X_250_mg;
      break;

    case LSM6DSV16X_312_mg:
      *val = LSM6DSV16X_312_mg;
      break;

    case LSM6DSV16X_344_mg:
      *val = LSM6DSV16X_344_mg;
      break;

    case LSM6DSV16X_406_mg:
      *val = LSM6DSV16X_406_mg;
      break;

    case LSM6DSV16X_469_mg:
      *val = LSM6DSV16X_469_mg;
      break;

    case LSM6DSV16X_500_mg:
      *val = LSM6DSV16X_500_mg;
      break;

    default:
      *val = LSM6DSV16X_156_mg;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Machine Learning Core (MLC)
  * @brief      This section group all the functions concerning the
  *             usage of Machine Learning Core
  * @{
  *
  */

/**
  * @brief  It enables Machine Learning Core feature (MLC). When the Machine Learning Core is enabled the Finite State Machine (FSM) programs are executed before executing the MLC algorithms.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DISABLE, MLC_BEFORE_FSM, MLC_AFTER_FSM,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mlc_mode_set(stmdev_ctx_t *ctx, lsm6dsv16x_mlc_mode_t val)
{
  lsm6dsv16x_emb_func_en_b_t emb_func_en_b;
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_B, (uint8_t *)&emb_func_en_b, 1);
  }
  emb_func_en_a.mlc_before_fsm_en = (uint8_t)val & 0x01U;
  emb_func_en_b.mlc_en = ((uint8_t)val & 0x02U) >> 1;
  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {

    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_B, (uint8_t *)&emb_func_en_b, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  It enables Machine Learning Core feature (MLC). When the Machine Learning Core is enabled the Finite State Machine (FSM) programs are executed before executing the MLC algorithms.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DISABLE, MLC_BEFORE_FSM, MLC_AFTER_FSM,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mlc_mode_get(stmdev_ctx_t *ctx, lsm6dsv16x_mlc_mode_t *val)
{
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  lsm6dsv16x_emb_func_en_b_t emb_func_en_b;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_B, (uint8_t *)&emb_func_en_b, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  switch ((emb_func_en_b.mlc_en << 1) + emb_func_en_a.mlc_before_fsm_en)
  {
    case LSM6DSV16X_DISABLE:
      *val = LSM6DSV16X_DISABLE;
      break;

    case LSM6DSV16X_MLC_BEFORE_FSM:
      *val = LSM6DSV16X_MLC_BEFORE_FSM;
      break;

    case LSM6DSV16X_MLC_AFTER_FSM:
      *val = LSM6DSV16X_MLC_AFTER_FSM;
      break;

    default:
      *val = LSM6DSV16X_DISABLE;
      break;
  }
  return ret;
}

/**
  * @brief  Machine Learning Core Output Data Rate (ODR) configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      MLC_15Hz, MLC_30Hz, MLC_60Hz, MLC_120Hz, MLC_240Hz, MLC_480Hz, MLC_960Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mlc_data_rate_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_mlc_data_rate_t val)
{
  lsm6dsv16x_mlc_odr_t mlc_odr;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MLC_ODR, (uint8_t *)&mlc_odr, 1);
  }

  if (ret == 0)
  {
    mlc_odr.mlc_odr = (uint8_t)val & 0x07U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_MLC_ODR, (uint8_t *)&mlc_odr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Machine Learning Core Output Data Rate (ODR) configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      MLC_15Hz, MLC_30Hz, MLC_60Hz, MLC_120Hz, MLC_240Hz, MLC_480Hz, MLC_960Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mlc_data_rate_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_mlc_data_rate_t *val)
{
  lsm6dsv16x_mlc_odr_t mlc_odr;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MLC_ODR, (uint8_t *)&mlc_odr, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  switch (mlc_odr.mlc_odr)
  {
    case LSM6DSV16X_MLC_15Hz:
      *val = LSM6DSV16X_MLC_15Hz;
      break;

    case LSM6DSV16X_MLC_30Hz:
      *val = LSM6DSV16X_MLC_30Hz;
      break;

    case LSM6DSV16X_MLC_60Hz:
      *val = LSM6DSV16X_MLC_60Hz;
      break;

    case LSM6DSV16X_MLC_120Hz:
      *val = LSM6DSV16X_MLC_120Hz;
      break;

    case LSM6DSV16X_MLC_240Hz:
      *val = LSM6DSV16X_MLC_240Hz;
      break;

    case LSM6DSV16X_MLC_480Hz:
      *val = LSM6DSV16X_MLC_480Hz;
      break;

    case LSM6DSV16X_MLC_960Hz:
      *val = LSM6DSV16X_MLC_960Hz;
      break;

    default:
      *val = LSM6DSV16X_MLC_15Hz;
      break;
  }
  return ret;
}

/**
  * @brief  Output value of all MLC decision trees.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Output value of all MLC decision trees.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mlc_out_get(stmdev_ctx_t *ctx, lsm6dsv16x_mlc_out_t *val)
{
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MLC1_SRC, (uint8_t *)val, 4);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }
  return ret;
}

/**
  * @brief  External sensor sensitivity value register for the Machine Learning Core. This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).Default value is 0x3C00 (when using an external magnetometer this value corresponds to 1 gauss/LSB).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      External sensor sensitivity value register for the Machine Learning Core. This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).Default value is 0x3C00 (when using an external magnetometer this value corresponds to 1 gauss/LSB).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mlc_ext_sens_sensitivity_set(stmdev_ctx_t *ctx, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));

  ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_MLC_EXT_SENSITIVITY_L, (uint8_t *)&buff[0], 2);

  return ret;
}

/**
  * @brief  External sensor sensitivity value register for the Machine Learning Core. This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).Default value is 0x3C00 (when using an external magnetometer this value corresponds to 1 gauss/LSB).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      External sensor sensitivity value register for the Machine Learning Core. This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits).Default value is 0x3C00 (when using an external magnetometer this value corresponds to 1 gauss/LSB).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_mlc_ext_sens_sensitivity_get(stmdev_ctx_t *ctx,
                                                uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_MLC_EXT_SENSITIVITY_L, &buff[0], 2);
  *val = buff[1];
  *val = (*val * 256U) + buff[0];

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Optical Image Stabilization (OIS)
  * @brief     This section groups all the functions concerning
  *            Optical Image Stabilization (OIS).
  * @{
  *
  */

/**
  * @brief  Enable the full control of OIS configurations from the UI (User Interface).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_CTRL_FROM_OIS, OIS_CTRL_FROM_UI,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_ctrl_mode_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_ois_ctrl_mode_t val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  if (ret == 0)
  {
    func_cfg_access.ois_ctrl_from_ui = (uint8_t)val & 0x1U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  }

  return ret;
}

/**
  * @brief  Enable the full control of OIS configurations from the UI (User Interface).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_CTRL_FROM_OIS, OIS_CTRL_FROM_UI,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_ctrl_mode_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_ois_ctrl_mode_t *val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  switch (func_cfg_access.ois_ctrl_from_ui)
  {
    case LSM6DSV16X_OIS_CTRL_FROM_OIS:
      *val = LSM6DSV16X_OIS_CTRL_FROM_OIS;
      break;

    case LSM6DSV16X_OIS_CTRL_FROM_UI:
      *val = LSM6DSV16X_OIS_CTRL_FROM_UI;
      break;

    default:
      *val = LSM6DSV16X_OIS_CTRL_FROM_OIS;
      break;
  }
  return ret;
}

/**
  * @brief  Resets the control registers of OIS from the UI (User Interface)[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Resets the control registers of OIS from the UI (User Interface)
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_reset_set(stmdev_ctx_t *ctx, int8_t val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  if (ret == 0)
  {
    func_cfg_access.spi2_reset = (uint8_t)val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  }

  return ret;
}

/**
  * @brief  Resets the control registers of OIS from the UI (User Interface)[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Resets the control registers of OIS from the UI (User Interface)
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_reset_get(stmdev_ctx_t *ctx, int8_t *val)
{
  lsm6dsv16x_func_cfg_access_t func_cfg_access;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNC_CFG_ACCESS, (uint8_t *)&func_cfg_access, 1);
  *val = (int8_t)func_cfg_access.spi2_reset;

  return ret;
}

/**
  * @brief  Enable/disable pull up on OIS interface.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable/disable pull up on OIS interface.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_interface_pull_up_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  if (ret == 0)
  {
    pin_ctrl.ois_pu_dis = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  Enable/disable pull up on OIS interface.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable/disable pull up on OIS interface.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_interface_pull_up_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  *val = pin_ctrl.ois_pu_dis;

  return ret;
}

/**
  * @brief  Handshake for (User Interface) UI / (OIS interface) SPI2 shared registers. ACK: This bit acknowledges the handshake. If the secondary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED registers is allowed on the primary interface. REQ: This bit is used by the primary interface master to request access to the UI_SPI2_SHARED registers. When the R/W operation is finished, the master must reset this bit.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Handshake for (User Interface) UI / (OIS interface) SPI2 shared registers. ACK: This bit acknowledges the handshake. If the secondary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED registers is allowed on the primary interface. REQ: This bit is used by the primary interface master to request access to the UI_SPI2_SHARED registers. When the R/W operation is finished, the master must reset this bit.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_handshake_from_ui_set(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_ois_handshake_t val)
{
  lsm6dsv16x_ui_handshake_ctrl_t ui_handshake_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_HANDSHAKE_CTRL, (uint8_t *)&ui_handshake_ctrl, 1);
  if (ret == 0)
  {
    ui_handshake_ctrl.ui_shared_ack = val.ack;
    ui_handshake_ctrl.ui_shared_req = val.req;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_HANDSHAKE_CTRL, (uint8_t *)&ui_handshake_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  Handshake for (User Interface) UI / (OIS interface) SPI2 shared registers. ACK: This bit acknowledges the handshake. If the secondary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED registers is allowed on the primary interface. REQ: This bit is used by the primary interface master to request access to the UI_SPI2_SHARED registers. When the R/W operation is finished, the master must reset this bit.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Handshake for (User Interface) UI / (OIS interface) SPI2 shared registers. ACK: This bit acknowledges the handshake. If the secondary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED registers is allowed on the primary interface. REQ: This bit is used by the primary interface master to request access to the UI_SPI2_SHARED registers. When the R/W operation is finished, the master must reset this bit.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_handshake_from_ui_get(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_ois_handshake_t *val)
{
  lsm6dsv16x_ui_handshake_ctrl_t ui_handshake_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_HANDSHAKE_CTRL, (uint8_t *)&ui_handshake_ctrl, 1);
  val->ack = ui_handshake_ctrl.ui_shared_ack;
  val->req = ui_handshake_ctrl.ui_shared_req;

  return ret;
}

/**
  * @brief  Handshake for (User Interface) UI / (OIS interface) SPI2 shared registers. ACK: This bit acknowledges the handshake. If the secondary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED registers is allowed on the primary interface. REQ: This bit is used by the primary interface master to request access to the UI_SPI2_SHARED registers. When the R/W operation is finished, the master must reset this bit.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Handshake for (User Interface) UI / (OIS interface) SPI2 shared registers. ACK: This bit acknowledges the handshake. If the secondary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED registers is allowed on the primary interface. REQ: This bit is used by the primary interface master to request access to the UI_SPI2_SHARED registers. When the R/W operation is finished, the master must reset this bit.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_handshake_from_ois_set(stmdev_ctx_t *ctx,
                                              lsm6dsv16x_ois_handshake_t val)
{
  lsm6dsv16x_spi2_handshake_ctrl_t spi2_handshake_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SPI2_HANDSHAKE_CTRL, (uint8_t *)&spi2_handshake_ctrl, 1);
  if (ret == 0)
  {
    spi2_handshake_ctrl.spi2_shared_ack = val.ack;
    spi2_handshake_ctrl.spi2_shared_req = val.req;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SPI2_HANDSHAKE_CTRL, (uint8_t *)&spi2_handshake_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  Handshake for (User Interface) UI / (OIS interface) SPI2 shared registers. ACK: This bit acknowledges the handshake. If the secondary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED registers is allowed on the primary interface. REQ: This bit is used by the primary interface master to request access to the UI_SPI2_SHARED registers. When the R/W operation is finished, the master must reset this bit.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Handshake for (User Interface) UI / (OIS interface) SPI2 shared registers. ACK: This bit acknowledges the handshake. If the secondary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED registers is allowed on the primary interface. REQ: This bit is used by the primary interface master to request access to the UI_SPI2_SHARED registers. When the R/W operation is finished, the master must reset this bit.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_handshake_from_ois_get(stmdev_ctx_t *ctx,
                                              lsm6dsv16x_ois_handshake_t *val)
{
  lsm6dsv16x_spi2_handshake_ctrl_t spi2_handshake_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SPI2_HANDSHAKE_CTRL, (uint8_t *)&spi2_handshake_ctrl, 1);
  val->ack = spi2_handshake_ctrl.spi2_shared_ack;
  val->req = spi2_handshake_ctrl.spi2_shared_req;

  return ret;
}

/**
  * @brief  User interface (UI) / SPI2 (OIS) shared registers[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      User interface (UI) / SPI2 (OIS) shared registers
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_shared_set(stmdev_ctx_t *ctx, uint8_t val[6])
{
  int32_t ret;

  ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_SPI2_SHARED_0, val, 6);

  return ret;
}

/**
  * @brief  User interface (UI) / SPI2 (OIS) shared registers[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      User interface (UI) / SPI2 (OIS) shared registers
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_shared_get(stmdev_ctx_t *ctx, uint8_t val[6])
{
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_SPI2_SHARED_0, val, 6);

  return ret;
}

/**
  * @brief  In User Interface (UI) full control mode, enables SPI2 (OIS Interface) for reading OIS data. This function works also on OIS (UI_CTRL1_OIS = SPI2_CTRL1_OIS).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      In User Interface (UI) full control mode, enables SPI2 (OIS Interface) for reading OIS data.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_on_spi2_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_ui_ctrl1_ois_t ui_ctrl1_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL1_OIS, (uint8_t *)&ui_ctrl1_ois, 1);
  if (ret == 0)
  {
    ui_ctrl1_ois.spi2_read_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_CTRL1_OIS, (uint8_t *)&ui_ctrl1_ois, 1);
  }

  return ret;
}

/**
  * @brief  In User Interface (UI) full control mode, enables SPI2 (OIS Interface) for reading OIS data. This function works also on OIS (UI_CTRL1_OIS = SPI2_CTRL1_OIS).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      In User Interface (UI) full control mode, enables SPI2 (OIS Interface) for reading OIS data.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_on_spi2_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_ui_ctrl1_ois_t ui_ctrl1_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL1_OIS, (uint8_t *)&ui_ctrl1_ois, 1);
  *val = ui_ctrl1_ois.spi2_read_en;

  return ret;
}

/**
  * @brief  Enables gyroscope/accelerometer OIS chain. This function works also on OIS (UI_CTRL1_OIS = SPI2_CTRL1_OIS).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables gyroscope/accelerometer OIS chain.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_chain_set(stmdev_ctx_t *ctx, lsm6dsv16x_ois_chain_t val)
{
  lsm6dsv16x_ui_ctrl1_ois_t ui_ctrl1_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL1_OIS, (uint8_t *)&ui_ctrl1_ois, 1);
  if (ret == 0)
  {
    ui_ctrl1_ois.ois_g_en = val.gy;
    ui_ctrl1_ois.ois_xl_en = val.xl;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_CTRL1_OIS, (uint8_t *)&ui_ctrl1_ois, 1);
  }

  return ret;
}

/**
  * @brief  Enables gyroscope/accelerometer OIS chain.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables gyroscope/accelerometer OIS chain.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_chain_get(stmdev_ctx_t *ctx, lsm6dsv16x_ois_chain_t *val)
{
  lsm6dsv16x_ui_ctrl1_ois_t ui_ctrl1_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL1_OIS, (uint8_t *)&ui_ctrl1_ois, 1);
  val->gy = ui_ctrl1_ois.ois_g_en;
  val->xl = ui_ctrl1_ois.ois_xl_en;

  return ret;
}

/**
  * @brief  Gyroscope OIS full-scale selection[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_125dps, OIS_250dps, OIS_500dps, OIS_1000dps, OIS_2000dps,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_gy_full_scale_set(stmdev_ctx_t *ctx,
                                         lsm6dsv16x_ois_gy_full_scale_t val)
{
  lsm6dsv16x_ui_ctrl2_ois_t ui_ctrl2_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL2_OIS, (uint8_t *)&ui_ctrl2_ois, 1);
  if (ret == 0)
  {
    ui_ctrl2_ois.fs_g_ois = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_CTRL2_OIS, (uint8_t *)&ui_ctrl2_ois, 1);
  }

  return ret;
}

/**
  * @brief  Gyroscope OIS full-scale selection[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_125dps, OIS_250dps, OIS_500dps, OIS_1000dps, OIS_2000dps,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_gy_full_scale_get(stmdev_ctx_t *ctx,
                                         lsm6dsv16x_ois_gy_full_scale_t *val)
{
  lsm6dsv16x_ui_ctrl2_ois_t ui_ctrl2_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL2_OIS, (uint8_t *)&ui_ctrl2_ois, 1);
  switch (ui_ctrl2_ois.fs_g_ois)
  {
    case LSM6DSV16X_OIS_125dps:
      *val = LSM6DSV16X_OIS_125dps;
      break;

    case LSM6DSV16X_OIS_250dps:
      *val = LSM6DSV16X_OIS_250dps;
      break;

    case LSM6DSV16X_OIS_500dps:
      *val = LSM6DSV16X_OIS_500dps;
      break;

    case LSM6DSV16X_OIS_1000dps:
      *val = LSM6DSV16X_OIS_1000dps;
      break;

    case LSM6DSV16X_OIS_2000dps:
      *val = LSM6DSV16X_OIS_2000dps;
      break;

    default:
      *val = LSM6DSV16X_OIS_125dps;
      break;
  }
  return ret;
}

/**
  * @brief  Selects accelerometer OIS channel full-scale.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_2g, OIS_4g, OIS_8g, OIS_16g,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_xl_full_scale_set(stmdev_ctx_t *ctx,
                                         lsm6dsv16x_ois_xl_full_scale_t val)
{
  lsm6dsv16x_ui_ctrl3_ois_t ui_ctrl3_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL3_OIS, (uint8_t *)&ui_ctrl3_ois, 1);
  if (ret == 0)
  {
    ui_ctrl3_ois.fs_xl_ois = (uint8_t)val & 0x3U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_CTRL3_OIS, (uint8_t *)&ui_ctrl3_ois, 1);
  }

  return ret;
}

/**
  * @brief  Selects accelerometer OIS channel full-scale.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      OIS_2g, OIS_4g, OIS_8g, OIS_16g,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ois_xl_full_scale_get(stmdev_ctx_t *ctx,
                                         lsm6dsv16x_ois_xl_full_scale_t *val)
{
  lsm6dsv16x_ui_ctrl3_ois_t ui_ctrl3_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL3_OIS, (uint8_t *)&ui_ctrl3_ois, 1);
  switch (ui_ctrl3_ois.fs_xl_ois)
  {
    case LSM6DSV16X_OIS_2g:
      *val = LSM6DSV16X_OIS_2g;
      break;

    case LSM6DSV16X_OIS_4g:
      *val = LSM6DSV16X_OIS_4g;
      break;

    case LSM6DSV16X_OIS_8g:
      *val = LSM6DSV16X_OIS_8g;
      break;

    case LSM6DSV16X_OIS_16g:
      *val = LSM6DSV16X_OIS_16g;
      break;

    default:
      *val = LSM6DSV16X_OIS_2g;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Orientation 6D (and 4D)
  * @brief     This section groups all the functions concerning six position
  *            detection (6D).
  * @{
  *
  */

/**
  * @brief  Threshold for 4D/6D function.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DEG_80, DEG_70, DEG_60, DEG_50,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_6d_threshold_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_6d_threshold_t val)
{
  lsm6dsv16x_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_THS_6D, (uint8_t *)&tap_ths_6d, 1);
  if (ret == 0)
  {
    tap_ths_6d.sixd_ths = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_THS_6D, (uint8_t *)&tap_ths_6d, 1);
  }

  return ret;
}

/**
  * @brief  Threshold for 4D/6D function.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      DEG_80, DEG_70, DEG_60, DEG_50,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_6d_threshold_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_6d_threshold_t *val)
{
  lsm6dsv16x_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_THS_6D, (uint8_t *)&tap_ths_6d, 1);
  switch (tap_ths_6d.sixd_ths)
  {
    case LSM6DSV16X_DEG_80:
      *val = LSM6DSV16X_DEG_80;
      break;

    case LSM6DSV16X_DEG_70:
      *val = LSM6DSV16X_DEG_70;
      break;

    case LSM6DSV16X_DEG_60:
      *val = LSM6DSV16X_DEG_60;
      break;

    case LSM6DSV16X_DEG_50:
      *val = LSM6DSV16X_DEG_50;
      break;

    default:
      *val = LSM6DSV16X_DEG_80;
      break;
  }
  return ret;
}

/**
  * @brief  4D orientation detection enable. Z-axis position detection is disabled.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      4D orientation detection enable. Z-axis position detection is disabled.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_4d_mode_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_THS_6D, (uint8_t *)&tap_ths_6d, 1);
  if (ret == 0)
  {
    tap_ths_6d.d4d_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_THS_6D, (uint8_t *)&tap_ths_6d, 1);
  }

  return ret;
}

/**
  * @brief  4D orientation detection enable. Z-axis position detection is disabled.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      4D orientation detection enable. Z-axis position detection is disabled.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_4d_mode_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_tap_ths_6d_t tap_ths_6d;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_THS_6D, (uint8_t *)&tap_ths_6d, 1);
  *val = tap_ths_6d.d4d_en;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  AH_QVAR
  * @brief     This section group all the functions concerning the
  *            usage of AH_QVAR
  * @{
  *
  */

/**
  * @brief  Configures the equivalent input impedance of the AH_QVAR buffers.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      2400MOhm, 730MOhm, 300MOhm, 255MOhm,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ah_qvar_zin_set(stmdev_ctx_t *ctx,
                                   lsm6dsv16x_ah_qvar_zin_t val)
{
  lsm6dsv16x_ctrl7_t ctrl7;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL7, (uint8_t *)&ctrl7, 1);
  if (ret == 0)
  {
    ctrl7.ah_qvar_c_zin = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL7, (uint8_t *)&ctrl7, 1);
  }

  return ret;
}

/**
  * @brief  Configures the equivalent input impedance of the AH_QVAR buffers.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      2400MOhm, 730MOhm, 300MOhm, 255MOhm,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ah_qvar_zin_get(stmdev_ctx_t *ctx,
                                   lsm6dsv16x_ah_qvar_zin_t *val)
{
  lsm6dsv16x_ctrl7_t ctrl7;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL7, (uint8_t *)&ctrl7, 1);
  switch (ctrl7.ah_qvar_c_zin)
  {
    case LSM6DSV16X_2400MOhm:
      *val = LSM6DSV16X_2400MOhm;
      break;

    case LSM6DSV16X_730MOhm:
      *val = LSM6DSV16X_730MOhm;
      break;

    case LSM6DSV16X_300MOhm:
      *val = LSM6DSV16X_300MOhm;
      break;

    case LSM6DSV16X_255MOhm:
      *val = LSM6DSV16X_255MOhm;
      break;

    default:
      *val = LSM6DSV16X_2400MOhm;
      break;
  }
  return ret;
}

/**
  * @brief  Enables AH_QVAR chain. When this bit is set to '1', the AH_QVAR buffers are connected to the SDx/AH1/Qvar1 and SCx/AH2/Qvar2 pins. Before setting this bit to 1, the accelerometer and gyroscope sensor have to be configured in power-down mode.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables AH_QVAR chain. When this bit is set to '1', the AH_QVAR buffers are connected to the SDx/AH1/Qvar1 and SCx/AH2/Qvar2 pins. Before setting this bit to 1, the accelerometer and gyroscope sensor have to be configured in power-down mode.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ah_qvar_mode_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_ah_qvar_mode_t val)
{
  lsm6dsv16x_ctrl7_t ctrl7;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL7, (uint8_t *)&ctrl7, 1);
  if (ret == 0)
  {
    ctrl7.ah_qvar_en = val.ah_qvar_en;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL7, (uint8_t *)&ctrl7, 1);
  }

  return ret;
}

/**
  * @brief  Enables AH_QVAR chain. When this bit is set to '1', the AH_QVAR buffers are connected to the SDx/AH1/Qvar1 and SCx/AH2/Qvar2 pins. Before setting this bit to 1, the accelerometer and gyroscope sensor have to be configured in power-down mode.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables AH_QVAR chain. When this bit is set to '1', the AH_QVAR buffers are connected to the SDx/AH1/Qvar1 and SCx/AH2/Qvar2 pins. Before setting this bit to 1, the accelerometer and gyroscope sensor have to be configured in power-down mode.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ah_qvar_mode_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_ah_qvar_mode_t *val)
{
  lsm6dsv16x_ctrl7_t ctrl7;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL7, (uint8_t *)&ctrl7, 1);
  val->ah_qvar_en = ctrl7.ah_qvar_en;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  SenseWire (I3C)
  * @brief     This section group all the functions concerning the
  *            usage of SenseWire (I3C)
  * @{
  *
  */

/**
  * @brief  Selects the action the device will perform after "Reset whole chip" I3C pattern.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SW_RST_DYN_ADDRESS_RST, GLOBAL_RST,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_i3c_reset_mode_set(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_i3c_reset_mode_t val)
{
  lsm6dsv16x_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  if (ret == 0)
  {
    pin_ctrl.ibhr_por_en = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  Selects the action the device will perform after "Reset whole chip" I3C pattern.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SW_RST_DYN_ADDRESS_RST, I3C_GLOBAL_RST,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_i3c_reset_mode_get(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_i3c_reset_mode_t *val)
{
  lsm6dsv16x_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  switch (pin_ctrl.ibhr_por_en)
  {
    case LSM6DSV16X_SW_RST_DYN_ADDRESS_RST:
      *val = LSM6DSV16X_SW_RST_DYN_ADDRESS_RST;
      break;

    case LSM6DSV16X_I3C_GLOBAL_RST:
      *val = LSM6DSV16X_I3C_GLOBAL_RST;
      break;

    default:
      *val = LSM6DSV16X_SW_RST_DYN_ADDRESS_RST;
      break;
  }
  return ret;
}

/**
  * @brief  Select the us activity time for IBI (In-Band Interrupt) with I3C[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      IBI_2us, IBI_50us, IBI_1ms, IBI_25ms,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_i3c_ibi_time_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_i3c_ibi_time_t val)
{
  lsm6dsv16x_ctrl5_t ctrl5;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL5, (uint8_t *)&ctrl5, 1);
  if (ret == 0)
  {
    ctrl5.bus_act_sel = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_CTRL5, (uint8_t *)&ctrl5, 1);
  }

  return ret;
}

/**
  * @brief  Select the us activity time for IBI (In-Band Interrupt) with I3C[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      IBI_2us, IBI_50us, IBI_1ms, IBI_25ms,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_i3c_ibi_time_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_i3c_ibi_time_t *val)
{
  lsm6dsv16x_ctrl5_t ctrl5;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_CTRL5, (uint8_t *)&ctrl5, 1);
  switch (ctrl5.bus_act_sel)
  {
    case LSM6DSV16X_IBI_2us:
      *val = LSM6DSV16X_IBI_2us;
      break;

    case LSM6DSV16X_IBI_50us:
      *val = LSM6DSV16X_IBI_50us;
      break;

    case LSM6DSV16X_IBI_1ms:
      *val = LSM6DSV16X_IBI_1ms;
      break;

    case LSM6DSV16X_IBI_25ms:
      *val = LSM6DSV16X_IBI_25ms;
      break;

    default:
      *val = LSM6DSV16X_IBI_2us;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Sensor hub
  * @brief     This section groups all the functions that manage the
  *            sensor hub.
  * @{
  *
  */

/**
  * @brief  Sensor Hub master I2C pull-up enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Sensor Hub master I2C pull-up enable.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_master_interface_pull_up_set(stmdev_ctx_t *ctx,
                                                   uint8_t val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  if (ret == 0)
  {
    if_cfg.shub_pu_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Sensor Hub master I2C pull-up enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Sensor Hub master I2C pull-up enable.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_master_interface_pull_up_get(stmdev_ctx_t *ctx,
                                                   uint8_t *val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  *val = if_cfg.shub_pu_en;

  return ret;
}

/**
  * @brief  Sensor hub output registers.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Sensor hub output registers.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_read_data_raw_get(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_emb_sh_read_t *val,
                                        uint8_t len)
{
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SENSOR_HUB_1, (uint8_t *) val,
                              len);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }


  return ret;
}

/**
  * @brief  Number of external sensors to be read by the sensor hub.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SLV_0, SLV_0_1, SLV_0_1_2, SLV_0_1_2_3,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_slave_connected_set(stmdev_ctx_t *ctx,
                                          lsm6dsv16x_sh_slave_connected_t val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.aux_sens_on = (uint8_t)val & 0x3U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Number of external sensors to be read by the sensor hub.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SLV_0, SLV_0_1, SLV_0_1_2, SLV_0_1_2_3,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_slave_connected_get(stmdev_ctx_t *ctx,
                                          lsm6dsv16x_sh_slave_connected_t *val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  switch (master_config.aux_sens_on)
  {
    case LSM6DSV16X_SLV_0:
      *val = LSM6DSV16X_SLV_0;
      break;

    case LSM6DSV16X_SLV_0_1:
      *val = LSM6DSV16X_SLV_0_1;
      break;

    case LSM6DSV16X_SLV_0_1_2:
      *val = LSM6DSV16X_SLV_0_1_2;
      break;

    case LSM6DSV16X_SLV_0_1_2_3:
      *val = LSM6DSV16X_SLV_0_1_2_3;
      break;

    default:
      *val = LSM6DSV16X_SLV_0;
      break;
  }
  return ret;
}

/**
  * @brief  Sensor hub I2C master enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Sensor hub I2C master enable.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_master_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.master_on = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub I2C master enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Sensor hub I2C master enable.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_master_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }

  *val = master_config.master_on;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  I2C interface pass-through.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      I2C interface pass-through.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_pass_through_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.pass_through_mode = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  I2C interface pass-through.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      I2C interface pass-through.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_pass_through_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }

  *val = master_config.pass_through_mode;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub trigger signal selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SH_TRG_XL_GY_DRDY, SH_TRIG_INT2,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_syncro_mode_set(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_sh_syncro_mode_t val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.start_config = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Sensor hub trigger signal selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SH_TRG_XL_GY_DRDY, SH_TRIG_INT2,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_syncro_mode_get(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_sh_syncro_mode_t *val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  switch (master_config.start_config)
  {
    case LSM6DSV16X_SH_TRG_XL_GY_DRDY:
      *val = LSM6DSV16X_SH_TRG_XL_GY_DRDY;
      break;

    case LSM6DSV16X_SH_TRIG_INT2:
      *val = LSM6DSV16X_SH_TRIG_INT2;
      break;

    default:
      *val = LSM6DSV16X_SH_TRG_XL_GY_DRDY;
      break;
  }
  return ret;
}

/**
  * @brief  Slave 0 write operation is performed only at the first sensor hub cycle.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      EACH_SH_CYCLE, ONLY_FIRST_CYCLE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_write_mode_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_sh_write_mode_t val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.write_once = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Slave 0 write operation is performed only at the first sensor hub cycle.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      EACH_SH_CYCLE, ONLY_FIRST_CYCLE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_write_mode_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_sh_write_mode_t *val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }


  switch (master_config.write_once)
  {
    case LSM6DSV16X_EACH_SH_CYCLE:
      *val = LSM6DSV16X_EACH_SH_CYCLE;
      break;

    case LSM6DSV16X_ONLY_FIRST_CYCLE:
      *val = LSM6DSV16X_ONLY_FIRST_CYCLE;
      break;

    default:
      *val = LSM6DSV16X_EACH_SH_CYCLE;
      break;
  }
  return ret;
}

/**
  * @brief  Reset Master logic and output registers. Must be set to '1' and then set it to '0'.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Reset Master logic and output registers. Must be set to '1' and then set it to '0'.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_reset_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }

  if (ret == 0)
  {
    master_config.rst_master_regs = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Reset Master logic and output registers. Must be set to '1' and then set it to '0'.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Reset Master logic and output registers. Must be set to '1' and then set it to '0'.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_reset_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_master_config_t master_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_MASTER_CONFIG, (uint8_t *)&master_config, 1);
  }

  *val = master_config.rst_master_regs;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 0 for perform a write.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      a structure that contain
  *                      - uint8_t slv1_add;    8 bit i2c device address
  *                      - uint8_t slv1_subadd; 8 bit register device address
  *                      - uint8_t slv1_data;   8 bit data to write
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_cfg_write(stmdev_ctx_t *ctx,
                                lsm6dsv16x_sh_cfg_write_t *val)
{
  lsm6dsv16x_slv0_add_t reg;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    reg.slave0_add = val->slv0_add;
    reg.rw_0 = 0;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV0_ADD, (uint8_t *)&reg, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV0_SUBADD,
                               &(val->slv0_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_DATAWRITE_SLV0,
                               &(val->slv0_data), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Rate at which the master communicates.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SH_15Hz, SH_30Hz, SH_60Hz, SH_120Hz, SH_240Hz, SH_480Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_data_rate_set(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_sh_data_rate_t val)
{
  lsm6dsv16x_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV0_CONFIG, (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    slv0_config.shub_odr = (uint8_t)val & 0x07U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV0_CONFIG, (uint8_t *)&slv0_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Rate at which the master communicates.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SH_15Hz, SH_30Hz, SH_60Hz, SH_120Hz, SH_240Hz, SH_480Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_data_rate_get(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_sh_data_rate_t *val)
{
  lsm6dsv16x_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV0_CONFIG, (uint8_t *)&slv0_config, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  switch (slv0_config.shub_odr)
  {
    case LSM6DSV16X_SH_15Hz:
      *val = LSM6DSV16X_SH_15Hz;
      break;

    case LSM6DSV16X_SH_30Hz:
      *val = LSM6DSV16X_SH_30Hz;
      break;

    case LSM6DSV16X_SH_60Hz:
      *val = LSM6DSV16X_SH_60Hz;
      break;

    case LSM6DSV16X_SH_120Hz:
      *val = LSM6DSV16X_SH_120Hz;
      break;

    case LSM6DSV16X_SH_240Hz:
      *val = LSM6DSV16X_SH_240Hz;
      break;

    case LSM6DSV16X_SH_480Hz:
      *val = LSM6DSV16X_SH_480Hz;
      break;

    default:
      *val = LSM6DSV16X_SH_15Hz;
      break;
  }
  return ret;
}

/**
  * @brief  Configure slave 0 for perform a read.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Structure that contain
  *                      - uint8_t slv1_add;    8 bit i2c device address
  *                      - uint8_t slv1_subadd; 8 bit register device address
  *                      - uint8_t slv1_len;    num of bit to read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_slv0_cfg_read(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_sh_cfg_read_t *val)
{
  lsm6dsv16x_slv0_add_t slv0_add;
  lsm6dsv16x_slv0_config_t slv0_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);

  if (ret == 0)
  {
    slv0_add.slave0_add = val->slv_add;
    slv0_add.rw_0 = 1;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV0_ADD, (uint8_t *)&slv0_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV0_SUBADD,
                               &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV0_CONFIG,
                              (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    slv0_config.slave0_numop = val->slv_len;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV0_CONFIG,
                               (uint8_t *)&slv0_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 0 for perform a write/read.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Structure that contain
  *                      - uint8_t slv1_add;    8 bit i2c device address
  *                      - uint8_t slv1_subadd; 8 bit register device address
  *                      - uint8_t slv1_len;    num of bit to read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_slv1_cfg_read(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_sh_cfg_read_t *val)
{
  lsm6dsv16x_slv1_add_t slv1_add;
  lsm6dsv16x_slv1_config_t slv1_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);

  if (ret == 0)
  {
    slv1_add.slave1_add = val->slv_add;
    slv1_add.r_1 = 1;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV1_ADD, (uint8_t *)&slv1_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV1_SUBADD,
                               &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV1_CONFIG,
                              (uint8_t *)&slv1_config, 1);
  }

  if (ret == 0)
  {
    slv1_config.slave1_numop = val->slv_len;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV1_CONFIG,
                               (uint8_t *)&slv1_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Configure slave 0 for perform a write/read.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Structure that contain
  *                      - uint8_t slv2_add;    8 bit i2c device address
  *                      - uint8_t slv2_subadd; 8 bit register device address
  *                      - uint8_t slv2_len;    num of bit to read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_slv2_cfg_read(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_sh_cfg_read_t *val)
{
  lsm6dsv16x_slv2_add_t slv2_add;
  lsm6dsv16x_slv2_config_t slv2_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);

  if (ret == 0)
  {
    slv2_add.slave2_add = val->slv_add;
    slv2_add.r_2 = 1;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV2_ADD, (uint8_t *)&slv2_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV2_SUBADD,
                               &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV2_CONFIG,
                              (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    slv2_config.slave2_numop = val->slv_len;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV2_CONFIG,
                               (uint8_t *)&slv2_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief Configure slave 0 for perform a write/read.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Structure that contain
  *                      - uint8_t slv3_add;    8 bit i2c device address
  *                      - uint8_t slv3_subadd; 8 bit register device address
  *                      - uint8_t slv3_len;    num of bit to read
  * @retval             interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sh_slv3_cfg_read(stmdev_ctx_t *ctx,
                                    lsm6dsv16x_sh_cfg_read_t *val)
{
  lsm6dsv16x_slv3_add_t slv3_add;
  lsm6dsv16x_slv3_config_t slv3_config;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_SENSOR_HUB_MEM_BANK);

  if (ret == 0)
  {
    slv3_add.slave3_add = val->slv_add;
    slv3_add.r_3 = 1;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV3_ADD, (uint8_t *)&slv3_add, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV3_SUBADD,
                               &(val->slv_subadd), 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SLV3_CONFIG,
                              (uint8_t *)&slv3_config, 1);
  }

  if (ret == 0)
  {
    slv3_config.slave3_numop = val->slv_len;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SLV3_CONFIG,
                               (uint8_t *)&slv3_config, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Serial interfaces
  * @brief     This section groups all the functions concerning
  *            serial interfaces management (not auxiliary)
  * @{
  *
  */

/**
  * @brief  Enables pull-up on SDO pin of UI (User Interface).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables pull-up on SDO pin of UI (User Interface).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ui_sdo_pull_up_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  if (ret == 0)
  {
    pin_ctrl.sdo_pu_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  }

  return ret;
}

/**
  * @brief  Enables pull-up on SDO pin of UI (User Interface).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables pull-up on SDO pin of UI (User Interface).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ui_sdo_pull_up_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_pin_ctrl_t pin_ctrl;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_PIN_CTRL, (uint8_t *)&pin_ctrl, 1);
  *val = pin_ctrl.sdo_pu_en;

  return ret;
}

/**
  * @brief  Disables I2C and I3C on UI (User Interface).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      I2C_I3C_ENABLE, I2C_I3C_DISABLE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ui_i2c_i3c_mode_set(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_ui_i2c_i3c_mode_t val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  if (ret == 0)
  {
    if_cfg.i2c_i3c_disable = (uint8_t)val & 0x1U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Disables I2C and I3C on UI (User Interface).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      I2C_I3C_ENABLE, I2C_I3C_DISABLE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ui_i2c_i3c_mode_get(stmdev_ctx_t *ctx,
                                       lsm6dsv16x_ui_i2c_i3c_mode_t *val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  switch (if_cfg.i2c_i3c_disable)
  {
    case LSM6DSV16X_I2C_I3C_ENABLE:
      *val = LSM6DSV16X_I2C_I3C_ENABLE;
      break;

    case LSM6DSV16X_I2C_I3C_DISABLE:
      *val = LSM6DSV16X_I2C_I3C_DISABLE;
      break;

    default:
      *val = LSM6DSV16X_I2C_I3C_ENABLE;
      break;
  }
  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SPI_4_WIRE, SPI_3_WIRE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_spi_mode_set(stmdev_ctx_t *ctx, lsm6dsv16x_spi_mode_t val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  if (ret == 0)
  {
    if_cfg.sim = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  }

  return ret;
}

/**
  * @brief  SPI Serial Interface Mode selection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SPI_4_WIRE, SPI_3_WIRE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_spi_mode_get(stmdev_ctx_t *ctx, lsm6dsv16x_spi_mode_t *val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  switch (if_cfg.sim)
  {
    case LSM6DSV16X_SPI_4_WIRE:
      *val = LSM6DSV16X_SPI_4_WIRE;
      break;

    case LSM6DSV16X_SPI_3_WIRE:
      *val = LSM6DSV16X_SPI_3_WIRE;
      break;

    default:
      *val = LSM6DSV16X_SPI_4_WIRE;
      break;
  }
  return ret;
}

/**
  * @brief  Enables pull-up on SDA pin.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables pull-up on SDA pin.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ui_sda_pull_up_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  if (ret == 0)
  {
    if_cfg.sda_pu_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  }

  return ret;
}

/**
  * @brief  Enables pull-up on SDA pin.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables pull-up on SDA pin.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_ui_sda_pull_up_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_if_cfg_t if_cfg;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_IF_CFG, (uint8_t *)&if_cfg, 1);
  *val = if_cfg.sda_pu_en;

  return ret;
}

/**
  * @brief  SPI2 (OIS Inteface) Serial Interface Mode selection. This function works also on OIS (UI_CTRL1_OIS = SPI2_CTRL1_OIS).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SPI2_4_WIRE, SPI2_3_WIRE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_spi2_mode_set(stmdev_ctx_t *ctx, lsm6dsv16x_spi2_mode_t val)
{
  lsm6dsv16x_ui_ctrl1_ois_t ui_ctrl1_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL1_OIS, (uint8_t *)&ui_ctrl1_ois, 1);
  if (ret == 0)
  {
    ui_ctrl1_ois.sim_ois = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_UI_CTRL1_OIS, (uint8_t *)&ui_ctrl1_ois, 1);
  }

  return ret;
}

/**
  * @brief  SPI2 (OIS Inteface) Serial Interface Mode selection. This function works also on OIS (UI_CTRL1_OIS = SPI2_CTRL1_OIS).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SPI2_4_WIRE, SPI2_3_WIRE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_spi2_mode_get(stmdev_ctx_t *ctx, lsm6dsv16x_spi2_mode_t *val)
{
  lsm6dsv16x_ui_ctrl1_ois_t ui_ctrl1_ois;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_UI_CTRL1_OIS, (uint8_t *)&ui_ctrl1_ois, 1);
  switch (ui_ctrl1_ois.sim_ois)
  {
    case LSM6DSV16X_SPI2_4_WIRE:
      *val = LSM6DSV16X_SPI2_4_WIRE;
      break;

    case LSM6DSV16X_SPI2_3_WIRE:
      *val = LSM6DSV16X_SPI2_3_WIRE;
      break;

    default:
      *val = LSM6DSV16X_SPI2_4_WIRE;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Significant motion detection
  * @brief     This section groups all the functions that manage the
  *            significant motion detection.
  * @{
  *
  */


/**
  * @brief  Enables significant motion detection function.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables significant motion detection function.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sigmot_mode_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {
    emb_func_en_a.sign_motion_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }


  return ret;
}

/**
  * @brief  Enables significant motion detection function.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables significant motion detection function.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sigmot_mode_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  *val = emb_func_en_a.sign_motion_en;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Step Counter (Pedometer)
  * @brief     This section groups all the functions that manage pedometer.
  * @{
  *
  */

/**
  * @brief  Step counter mode[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Step counter mode
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_stpcnt_mode_set(stmdev_ctx_t *ctx,
                                   lsm6dsv16x_stpcnt_mode_t val)
{
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  lsm6dsv16x_emb_func_en_b_t emb_func_en_b;
  lsm6dsv16x_pedo_cmd_reg_t pedo_cmd_reg;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_B, (uint8_t *)&emb_func_en_b, 1);
  }
  if ((val.false_step_rej == PROPERTY_ENABLE)
      && ((emb_func_en_a.mlc_before_fsm_en & emb_func_en_b.mlc_en) ==
          PROPERTY_DISABLE))
  {
    emb_func_en_a.mlc_before_fsm_en = PROPERTY_ENABLE;
  }
  if (ret == 0)
  {
    emb_func_en_a.pedo_en = val.step_counter_enable;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_PEDO_CMD_REG, (uint8_t *)&pedo_cmd_reg, 1);
  }
  if (ret == 0)
  {
    pedo_cmd_reg.fp_rejection_en = val.false_step_rej;
    ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_PEDO_CMD_REG, (uint8_t *)&pedo_cmd_reg, 1);
  }

  return ret;
}

/**
  * @brief  Step counter mode[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      false_step_rej, step_counter, step_detector,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_stpcnt_mode_get(stmdev_ctx_t *ctx,
                                   lsm6dsv16x_stpcnt_mode_t *val)
{
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  lsm6dsv16x_pedo_cmd_reg_t pedo_cmd_reg;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_PEDO_CMD_REG, (uint8_t *)&pedo_cmd_reg, 1);
  }
  val->false_step_rej = pedo_cmd_reg.fp_rejection_en;
  val->step_counter_enable = emb_func_en_a.pedo_en;

  return ret;
}

/**
  * @brief  Step counter output, number of detected steps.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Step counter output, number of detected steps.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_stpcnt_steps_get(stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_STEP_COUNTER_L, &buff[0], 2);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }
  *val = buff[1];
  *val = (*val * 256U) + buff[0];

  return ret;
}

/**
  * @brief  Reset step counter.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Reset step counter.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_stpcnt_rst_step_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_emb_func_src_t emb_func_src;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_SRC, (uint8_t *)&emb_func_src, 1);
  }

  if (ret == 0)
  {
    emb_func_src.pedo_rst_step = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_SRC, (uint8_t *)&emb_func_src, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Reset step counter.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Reset step counter.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_stpcnt_rst_step_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_emb_func_src_t emb_func_src;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_SRC, (uint8_t *)&emb_func_src, 1);
  }

  *val = emb_func_src.pedo_rst_step;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Pedometer debounce configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Pedometer debounce configuration.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_stpcnt_debounce_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_pedo_deb_steps_conf_t pedo_deb_steps_conf;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_PEDO_DEB_STEPS_CONF, (uint8_t *)&pedo_deb_steps_conf, 1);
  if (ret == 0)
  {
    pedo_deb_steps_conf.deb_step = val;
    ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_PEDO_DEB_STEPS_CONF, (uint8_t *)&pedo_deb_steps_conf, 1);
  }

  return ret;
}

/**
  * @brief  Pedometer debounce configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Pedometer debounce configuration.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_stpcnt_debounce_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_pedo_deb_steps_conf_t pedo_deb_steps_conf;
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_PEDO_DEB_STEPS_CONF, (uint8_t *)&pedo_deb_steps_conf, 1);
  *val = pedo_deb_steps_conf.deb_step;

  return ret;
}

/**
  * @brief  Time period register for step detection on delta time.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Time period register for step detection on delta time.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_stpcnt_period_set(stmdev_ctx_t *ctx, uint16_t val)
{
  uint8_t buff[2];
  int32_t ret;

  buff[1] = (uint8_t)(val / 256U);
  buff[0] = (uint8_t)(val - (buff[1] * 256U));
  ret = lsm6dsv16x_ln_pg_write(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_PEDO_SC_DELTAT_L, (uint8_t *)&buff[0], 2);

  return ret;
}

/**
  * @brief  Time period register for step detection on delta time.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Time period register for step detection on delta time.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_stpcnt_period_get(stmdev_ctx_t *ctx, uint16_t *val)
{
  uint8_t buff[2];
  int32_t ret;

  ret = lsm6dsv16x_ln_pg_read(ctx, LSM6DSV16X_EMB_ADV_PG_1 + LSM6DSV16X_PEDO_SC_DELTAT_L, &buff[0], 2);
  *val = buff[1];
  *val = (*val * 256U) + buff[0];

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Sensor Fusion Low Power (SFLP)
  * @brief     This section groups all the functions that manage pedometer.
  * @{
  *
  */

/**
  * @brief  Enable SFLP Game Rotation Vector (6x).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable/Disable game rotation value (0/1).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sflp_game_rotation_set(stmdev_ctx_t *ctx, uint16_t val)
{
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
    emb_func_en_a.sflp_game_en = val;
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A,
                                (uint8_t *)&emb_func_en_a, 1);
  }

  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  return ret;
}

/**
  * @brief  Enable SFLP Game Rotation Vector (6x).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable/Disable game rotation value (0/1).
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sflp_game_rotation_get(stmdev_ctx_t *ctx, uint16_t *val)
{
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
    *val = emb_func_en_a.sflp_game_en;
  }

  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  return ret;
}

/**
  * @brief  SFLP Data Rate (ODR) configuration.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SFLP_15Hz, SFLP_30Hz, SFLP_60Hz, SFLP_120Hz, SFLP_240Hz, SFLP_480Hz
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sflp_data_rate_set(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_sflp_data_rate_t val)
{
  lsm6dsv16x_sflp_odr_t sflp_odr;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SFLP_ODR, (uint8_t *)&sflp_odr, 1);
    sflp_odr.sflp_game_odr = (uint8_t)val & 0x07U;
    ret += lsm6dsv16x_write_reg(ctx, LSM6DSV16X_SFLP_ODR, (uint8_t *)&sflp_odr, 1);
  }

  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  return ret;
}

/**
  * @brief  SFLP Data Rate (ODR) configuration.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SFLP_15Hz, SFLP_30Hz, SFLP_60Hz, SFLP_120Hz, SFLP_240Hz, SFLP_480Hz
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_sflp_data_rate_get(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_sflp_data_rate_t *val)
{
  lsm6dsv16x_sflp_odr_t sflp_odr;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  ret += lsm6dsv16x_read_reg(ctx, LSM6DSV16X_SFLP_ODR, (uint8_t *)&sflp_odr, 1);
  ret += lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);

  switch (sflp_odr.sflp_game_odr)
  {
    case LSM6DSV16X_SFLP_15Hz:
      *val = LSM6DSV16X_SFLP_15Hz;
      break;

    case LSM6DSV16X_SFLP_30Hz:
      *val = LSM6DSV16X_SFLP_30Hz;
      break;

    case LSM6DSV16X_SFLP_60Hz:
      *val = LSM6DSV16X_SFLP_60Hz;
      break;

    case LSM6DSV16X_SFLP_120Hz:
      *val = LSM6DSV16X_SFLP_120Hz;
      break;

    case LSM6DSV16X_SFLP_240Hz:
      *val = LSM6DSV16X_SFLP_240Hz;
      break;

    case LSM6DSV16X_SFLP_480Hz:
      *val = LSM6DSV16X_SFLP_480Hz;
      break;

    default:
      *val = LSM6DSV16X_SFLP_15Hz;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Tap - Double Tap
  * @brief     This section groups all the functions that manage the
  *            tap and double tap event generation.
  * @{
  *
  */

/**
  * @brief  Enable axis for Tap - Double Tap detection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable axis for Tap - Double Tap detection.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_detection_set(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_tap_detection_t val)
{
  lsm6dsv16x_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);
  if (ret == 0)
  {
    tap_cfg0.tap_z_en = val.tap_x_en;
    tap_cfg0.tap_y_en = val.tap_y_en;
    tap_cfg0.tap_x_en = val.tap_z_en;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);
  }

  return ret;
}

/**
  * @brief  Enable axis for Tap - Double Tap detection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enable axis for Tap - Double Tap detection.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_detection_get(stmdev_ctx_t *ctx,
                                     lsm6dsv16x_tap_detection_t *val)
{
  lsm6dsv16x_tap_cfg0_t tap_cfg0;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG0, (uint8_t *)&tap_cfg0, 1);
  val->tap_x_en = tap_cfg0.tap_z_en;
  val->tap_y_en = tap_cfg0.tap_y_en;
  val->tap_z_en = tap_cfg0.tap_z_en;

  return ret;
}

/**
  * @brief  axis Tap - Double Tap recognition thresholds.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      axis Tap - Double Tap recognition thresholds.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_thresholds_set(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_tap_thresholds_t val)
{
  lsm6dsv16x_tap_ths_6d_t tap_ths_6d;
  lsm6dsv16x_tap_cfg2_t tap_cfg2;
  lsm6dsv16x_tap_cfg1_t tap_cfg1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG1, (uint8_t *)&tap_cfg1, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG2, (uint8_t *)&tap_cfg2, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_THS_6D, (uint8_t *)&tap_ths_6d, 1);
  }

  tap_cfg1.tap_ths_x = val.x;
  tap_cfg2.tap_ths_y = val.y;
  tap_ths_6d.tap_ths_z = val.z;

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_THS_6D, (uint8_t *)&tap_ths_6d, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_CFG2, (uint8_t *)&tap_cfg2, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_CFG1, (uint8_t *)&tap_cfg1, 1);
  }

  return ret;
}

/**
  * @brief  axis Tap - Double Tap recognition thresholds.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      axis Tap - Double Tap recognition thresholds.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_thresholds_get(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_tap_thresholds_t *val)
{
  lsm6dsv16x_tap_ths_6d_t tap_ths_6d;
  lsm6dsv16x_tap_cfg2_t tap_cfg2;
  lsm6dsv16x_tap_cfg1_t tap_cfg1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG1, (uint8_t *)&tap_cfg1, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG2, (uint8_t *)&tap_cfg2, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_THS_6D, (uint8_t *)&tap_ths_6d, 1);
  }

  val->x  = tap_cfg1.tap_ths_x;
  val->y = tap_cfg2.tap_ths_y;
  val->z = tap_ths_6d.tap_ths_z;

  return ret;
}

/**
  * @brief  Selection of axis priority for TAP detection.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XYZ , YXZ , XZY, ZYX , YZX , ZXY ,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_axis_priority_set(stmdev_ctx_t *ctx,
                                         lsm6dsv16x_tap_axis_priority_t val)
{
  lsm6dsv16x_tap_cfg1_t tap_cfg1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG1, (uint8_t *)&tap_cfg1, 1);
  if (ret == 0)
  {
    tap_cfg1.tap_priority = (uint8_t)val & 0x7U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_CFG1, (uint8_t *)&tap_cfg1, 1);
  }

  return ret;
}

/**
  * @brief  Selection of axis priority for TAP detection.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XYZ , YXZ , XZY, ZYX , YZX , ZXY ,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_axis_priority_get(stmdev_ctx_t *ctx,
                                         lsm6dsv16x_tap_axis_priority_t *val)
{
  lsm6dsv16x_tap_cfg1_t tap_cfg1;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_CFG1, (uint8_t *)&tap_cfg1, 1);
  switch (tap_cfg1.tap_priority)
  {
    case LSM6DSV16X_XYZ :
      *val = LSM6DSV16X_XYZ ;
      break;

    case LSM6DSV16X_YXZ :
      *val = LSM6DSV16X_YXZ ;
      break;

    case LSM6DSV16X_XZY:
      *val = LSM6DSV16X_XZY;
      break;

    case LSM6DSV16X_ZYX :
      *val = LSM6DSV16X_ZYX ;
      break;

    case LSM6DSV16X_YZX :
      *val = LSM6DSV16X_YZX ;
      break;

    case LSM6DSV16X_ZXY :
      *val = LSM6DSV16X_ZXY ;
      break;

    default:
      *val = LSM6DSV16X_XYZ ;
      break;
  }
  return ret;
}

/**
  * @brief  Time windows configuration for Tap - Double Tap SHOCK, QUIET, DUR : SHOCK Maximum duration is the maximum time of an overthreshold signal detection to be recognized as a tap event. The default value of these bits is 00b which corresponds to 4/ODR_XL time. If the SHOCK bits are set to a different value, 1LSB corresponds to 8/ODR_XL time. QUIET Expected quiet time after a tap detection. Quiet time is the time after the first detected tap in which there must not be any overthreshold event. The default value of these bits is 00b which corresponds to 2/ODR_XL time. If the QUIET bits are set to a different value, 1LSB corresponds to 4/ODR_XL time. DUR Duration of maximum time gap for double tap recognition. When double tap recognition is enabled, this register expresses the maximum time between two consecutive detected taps to determine a double tap event. The default value of these bits is 0000b which corresponds to 16/ODR_XL time. If the DUR_[3:0] bits are set to a different value, 1LSB corresponds to 32/ODR_XL time.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Time windows configuration for Tap - Double Tap SHOCK, QUIET, DUR : SHOCK Maximum duration is the maximum time of an overthreshold signal detection to be recognized as a tap event. The default value of these bits is 00b which corresponds to 4/ODR_XL time. If the SHOCK bits are set to a different value, 1LSB corresponds to 8/ODR_XL time. QUIET Expected quiet time after a tap detection. Quiet time is the time after the first detected tap in which there must not be any overthreshold event. The default value of these bits is 00b which corresponds to 2/ODR_XL time. If the QUIET bits are set to a different value, 1LSB corresponds to 4/ODR_XL time. DUR Duration of maximum time gap for double tap recognition. When double tap recognition is enabled, this register expresses the maximum time between two consecutive detected taps to determine a double tap event. The default value of these bits is 0000b which corresponds to 16/ODR_XL time. If the DUR_[3:0] bits are set to a different value, 1LSB corresponds to 32/ODR_XL time.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_time_windows_set(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_tap_time_windows_t val)
{
  lsm6dsv16x_tap_dur_t tap_dur;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_DUR, (uint8_t *)&tap_dur, 1);
  if (ret == 0)
  {
    tap_dur.shock = val.shock;
    tap_dur.quiet = val.quiet;
    tap_dur.dur = val.tap_gap;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_TAP_DUR, (uint8_t *)&tap_dur, 1);
  }

  return ret;
}

/**
  * @brief  Time windows configuration for Tap - Double Tap SHOCK, QUIET, DUR : SHOCK Maximum duration is the maximum time of an overthreshold signal detection to be recognized as a tap event. The default value of these bits is 00b which corresponds to 4/ODR_XL time. If the SHOCK bits are set to a different value, 1LSB corresponds to 8/ODR_XL time. QUIET Expected quiet time after a tap detection. Quiet time is the time after the first detected tap in which there must not be any overthreshold event. The default value of these bits is 00b which corresponds to 2/ODR_XL time. If the QUIET bits are set to a different value, 1LSB corresponds to 4/ODR_XL time. DUR Duration of maximum time gap for double tap recognition. When double tap recognition is enabled, this register expresses the maximum time between two consecutive detected taps to determine a double tap event. The default value of these bits is 0000b which corresponds to 16/ODR_XL time. If the DUR_[3:0] bits are set to a different value, 1LSB corresponds to 32/ODR_XL time.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Time windows configuration for Tap - Double Tap SHOCK, QUIET, DUR : SHOCK Maximum duration is the maximum time of an overthreshold signal detection to be recognized as a tap event. The default value of these bits is 00b which corresponds to 4/ODR_XL time. If the SHOCK bits are set to a different value, 1LSB corresponds to 8/ODR_XL time. QUIET Expected quiet time after a tap detection. Quiet time is the time after the first detected tap in which there must not be any overthreshold event. The default value of these bits is 00b which corresponds to 2/ODR_XL time. If the QUIET bits are set to a different value, 1LSB corresponds to 4/ODR_XL time. DUR Duration of maximum time gap for double tap recognition. When double tap recognition is enabled, this register expresses the maximum time between two consecutive detected taps to determine a double tap event. The default value of these bits is 0000b which corresponds to 16/ODR_XL time. If the DUR_[3:0] bits are set to a different value, 1LSB corresponds to 32/ODR_XL time.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_time_windows_get(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_tap_time_windows_t *val)
{
  lsm6dsv16x_tap_dur_t tap_dur;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TAP_DUR, (uint8_t *)&tap_dur, 1);
  val->shock = tap_dur.shock;
  val->quiet = tap_dur.quiet;
  val->tap_gap = tap_dur.dur;

  return ret;
}

/**
  * @brief  Single/double-tap event enable.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      ONLY_SINGLE, BOTH_SINGLE_DOUBLE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_mode_set(stmdev_ctx_t *ctx, lsm6dsv16x_tap_mode_t val)
{
  lsm6dsv16x_wake_up_ths_t wake_up_ths;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_THS, (uint8_t *)&wake_up_ths, 1);
  if (ret == 0)
  {
    wake_up_ths.single_double_tap = (uint8_t)val & 0x01U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_WAKE_UP_THS, (uint8_t *)&wake_up_ths, 1);
  }

  return ret;
}

/**
  * @brief  Single/double-tap event enable.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      ONLY_SINGLE, BOTH_SINGLE_DOUBLE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tap_mode_get(stmdev_ctx_t *ctx, lsm6dsv16x_tap_mode_t *val)
{
  lsm6dsv16x_wake_up_ths_t wake_up_ths;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_THS, (uint8_t *)&wake_up_ths, 1);
  switch (wake_up_ths.single_double_tap)
  {
    case LSM6DSV16X_ONLY_SINGLE:
      *val = LSM6DSV16X_ONLY_SINGLE;
      break;

    case LSM6DSV16X_BOTH_SINGLE_DOUBLE:
      *val = LSM6DSV16X_BOTH_SINGLE_DOUBLE;
      break;

    default:
      *val = LSM6DSV16X_ONLY_SINGLE;
      break;
  }
  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Tilt detection
  * @brief     This section groups all the functions that manage the tilt
  *            event detection.
  * @{
  *
  */

/**
  * @brief  Tilt calculation.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Tilt calculation.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tilt_mode_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {
    emb_func_en_a.tilt_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @brief  Tilt calculation.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Tilt calculation.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_tilt_mode_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_emb_func_en_a_t emb_func_en_a;
  int32_t ret;

  ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_EMBED_FUNC_MEM_BANK);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_EMB_FUNC_EN_A, (uint8_t *)&emb_func_en_a, 1);
  }
  *val = emb_func_en_a.tilt_en;

  if (ret == 0)
  {
    ret = lsm6dsv16x_mem_bank_set(ctx, LSM6DSV16X_MAIN_MEM_BANK);
  }

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Timestamp
  * @brief     This section groups all the functions that manage the
  *            timestamp generation.
  * @{
  *
  */

/**
  * @brief  Timestamp data output.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Timestamp data output.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_timestamp_raw_get(stmdev_ctx_t *ctx, uint32_t *val)
{
  uint8_t buff[4];
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_TIMESTAMP0, &buff[0], 4);
  *val = buff[3];
  *val = (*val * 256U) + buff[2];
  *val = (*val * 256U) + buff[1];
  *val = (*val * 256U) + buff[0];

  return ret;
}

/**
  * @brief  Enables timestamp counter.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables timestamp counter.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_timestamp_set(stmdev_ctx_t *ctx, uint8_t val)
{
  lsm6dsv16x_functions_enable_t functions_enable;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  if (ret == 0)
  {
    functions_enable.timestamp_en = val;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  }

  return ret;
}

/**
  * @brief  Enables timestamp counter.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Enables timestamp counter.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_timestamp_get(stmdev_ctx_t *ctx, uint8_t *val)
{
  lsm6dsv16x_functions_enable_t functions_enable;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  *val = functions_enable.timestamp_en;

  return ret;
}

/**
  * @}
  *
  */

/**
  * @defgroup  Wake Up - Activity - Inactivity (Sleep)
  * @brief     This section groups all the functions that manage the Wake Up
  *            event generation.
  * @{
  *
  */

/**
  * @brief  Enable activity/inactivity (sleep) function.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_AND_GY_NOT_AFFECTED, XL_LOW_POWER_GY_NOT_AFFECTED, XL_LOW_POWER_GY_SLEEP, XL_LOW_POWER_GY_POWER_DOWN,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_mode_set(stmdev_ctx_t *ctx, lsm6dsv16x_act_mode_t val)
{
  lsm6dsv16x_functions_enable_t functions_enable;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  if (ret == 0)
  {
    functions_enable.inact_en = (uint8_t)val & 0x3U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  }

  return ret;
}

/**
  * @brief  Enable activity/inactivity (sleep) function.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      XL_AND_GY_NOT_AFFECTED, XL_LOW_POWER_GY_NOT_AFFECTED, XL_LOW_POWER_GY_SLEEP, XL_LOW_POWER_GY_POWER_DOWN,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_mode_get(stmdev_ctx_t *ctx, lsm6dsv16x_act_mode_t *val)
{
  lsm6dsv16x_functions_enable_t functions_enable;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_FUNCTIONS_ENABLE, (uint8_t *)&functions_enable, 1);
  switch (functions_enable.inact_en)
  {
    case LSM6DSV16X_XL_AND_GY_NOT_AFFECTED:
      *val = LSM6DSV16X_XL_AND_GY_NOT_AFFECTED;
      break;

    case LSM6DSV16X_XL_LOW_POWER_GY_NOT_AFFECTED:
      *val = LSM6DSV16X_XL_LOW_POWER_GY_NOT_AFFECTED;
      break;

    case LSM6DSV16X_XL_LOW_POWER_GY_SLEEP:
      *val = LSM6DSV16X_XL_LOW_POWER_GY_SLEEP;
      break;

    case LSM6DSV16X_XL_LOW_POWER_GY_POWER_DOWN:
      *val = LSM6DSV16X_XL_LOW_POWER_GY_POWER_DOWN;
      break;

    default:
      *val = LSM6DSV16X_XL_AND_GY_NOT_AFFECTED;
      break;
  }
  return ret;
}

/**
  * @brief  Duration in the transition from Stationary to Motion (from Inactivity to Activity).[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SLEEP_TO_ACT_AT_1ST_SAMPLE, SLEEP_TO_ACT_AT_2ND_SAMPLE, SLEEP_TO_ACT_AT_3RD_SAMPLE, SLEEP_TO_ACT_AT_4th_SAMPLE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_from_sleep_to_act_dur_set(stmdev_ctx_t *ctx,
                                                 lsm6dsv16x_act_from_sleep_to_act_dur_t val)
{
  lsm6dsv16x_inactivity_dur_t inactivity_dur;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INACTIVITY_DUR, (uint8_t *)&inactivity_dur, 1);
  if (ret == 0)
  {
    inactivity_dur.inact_dur = (uint8_t)val & 0x3U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_INACTIVITY_DUR, (uint8_t *)&inactivity_dur, 1);
  }

  return ret;
}

/**
  * @brief  Duration in the transition from Stationary to Motion (from Inactivity to Activity).[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      SLEEP_TO_ACT_AT_1ST_SAMPLE, SLEEP_TO_ACT_AT_2ND_SAMPLE, SLEEP_TO_ACT_AT_3RD_SAMPLE, SLEEP_TO_ACT_AT_4th_SAMPLE,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_from_sleep_to_act_dur_get(stmdev_ctx_t *ctx,
                                                 lsm6dsv16x_act_from_sleep_to_act_dur_t *val)
{
  lsm6dsv16x_inactivity_dur_t inactivity_dur;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INACTIVITY_DUR, (uint8_t *)&inactivity_dur, 1);
  switch (inactivity_dur.inact_dur)
  {
    case LSM6DSV16X_SLEEP_TO_ACT_AT_1ST_SAMPLE:
      *val = LSM6DSV16X_SLEEP_TO_ACT_AT_1ST_SAMPLE;
      break;

    case LSM6DSV16X_SLEEP_TO_ACT_AT_2ND_SAMPLE:
      *val = LSM6DSV16X_SLEEP_TO_ACT_AT_2ND_SAMPLE;
      break;

    case LSM6DSV16X_SLEEP_TO_ACT_AT_3RD_SAMPLE:
      *val = LSM6DSV16X_SLEEP_TO_ACT_AT_3RD_SAMPLE;
      break;

    case LSM6DSV16X_SLEEP_TO_ACT_AT_4th_SAMPLE:
      *val = LSM6DSV16X_SLEEP_TO_ACT_AT_4th_SAMPLE;
      break;

    default:
      *val = LSM6DSV16X_SLEEP_TO_ACT_AT_1ST_SAMPLE;
      break;
  }
  return ret;
}

/**
  * @brief  Selects the accelerometer data rate during Inactivity.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      1Hz875, 15Hz, 30Hz, 60Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_sleep_xl_odr_set(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_act_sleep_xl_odr_t val)
{
  lsm6dsv16x_inactivity_dur_t inactivity_dur;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INACTIVITY_DUR, (uint8_t *)&inactivity_dur, 1);
  if (ret == 0)
  {
    inactivity_dur.xl_inact_odr = (uint8_t)val & 0x03U;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_INACTIVITY_DUR, (uint8_t *)&inactivity_dur, 1);
  }

  return ret;
}

/**
  * @brief  Selects the accelerometer data rate during Inactivity.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      1Hz875, 15Hz, 30Hz, 60Hz,
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_sleep_xl_odr_get(stmdev_ctx_t *ctx,
                                        lsm6dsv16x_act_sleep_xl_odr_t *val)
{
  lsm6dsv16x_inactivity_dur_t inactivity_dur;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INACTIVITY_DUR, (uint8_t *)&inactivity_dur, 1);
  switch (inactivity_dur.xl_inact_odr)
  {
    case LSM6DSV16X_1Hz875:
      *val = LSM6DSV16X_1Hz875;
      break;

    case LSM6DSV16X_15Hz:
      *val = LSM6DSV16X_15Hz;
      break;

    case LSM6DSV16X_30Hz:
      *val = LSM6DSV16X_30Hz;
      break;

    case LSM6DSV16X_60Hz:
      *val = LSM6DSV16X_60Hz;
      break;

    default:
      *val = LSM6DSV16X_1Hz875;
      break;
  }
  return ret;
}

/**
  * @brief  Wakeup and activity/inactivity threshold.[set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Wakeup and activity/inactivity threshold.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_thresholds_set(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_act_thresholds_t val)
{
  lsm6dsv16x_inactivity_ths_t inactivity_ths;
  lsm6dsv16x_inactivity_dur_t inactivity_dur;
  lsm6dsv16x_wake_up_ths_t wake_up_ths;
  int32_t ret;
  float_t tmp;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INACTIVITY_DUR, (uint8_t *)&inactivity_dur, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INACTIVITY_THS, (uint8_t *)&inactivity_ths, 1);
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_THS, (uint8_t *)&wake_up_ths, 1);
  }

  if ((val.wk_ths_mg < (uint32_t)(7.8125f * 63.0f))
      && (val.inact_ths_mg < (uint32_t)(7.8125f * 63.0f)))
  {
    inactivity_dur.wu_inact_ths_w = 0;

    tmp = (float_t)val.inact_ths_mg / 7.8125f;
    inactivity_ths.inact_ths = (uint8_t)tmp;

    tmp = (float_t)val.wk_ths_mg / 7.8125f;
    wake_up_ths.wk_ths = (uint8_t)tmp;
  }
  else if ((val.wk_ths_mg < (uint32_t)(15.625f * 63.0f))
           && (val.inact_ths_mg < (uint32_t)(15.625f * 63.0f)))
  {
    inactivity_dur.wu_inact_ths_w = 1;

    tmp = (float_t)val.inact_ths_mg / 15.625f;
    inactivity_ths.inact_ths = (uint8_t)tmp;

    tmp = (float_t)val.wk_ths_mg / 15.625f;
    wake_up_ths.wk_ths = (uint8_t)tmp;
  }
  else if ((val.wk_ths_mg < (uint32_t)(31.25f * 63.0f))
           && (val.inact_ths_mg < (uint32_t)(31.25f * 63.0f)))
  {
    inactivity_dur.wu_inact_ths_w = 2;

    tmp = (float_t)val.inact_ths_mg / 31.25f;
    inactivity_ths.inact_ths = (uint8_t)tmp;

    tmp = (float_t)val.wk_ths_mg / 31.25f;
    wake_up_ths.wk_ths = (uint8_t)tmp;
  }
  else if ((val.wk_ths_mg < (uint32_t)(62.5f * 63.0f))
           && (val.inact_ths_mg < (uint32_t)(62.5f * 63.0f)))
  {
    inactivity_dur.wu_inact_ths_w = 3;

    tmp = (float_t)val.inact_ths_mg / 62.5f;
    inactivity_ths.inact_ths = (uint8_t)tmp;

    tmp = (float_t)val.wk_ths_mg / 62.5f;
    wake_up_ths.wk_ths = (uint8_t)tmp;
  }
  else if ((val.wk_ths_mg < (uint32_t)(125.0f * 63.0f))
           && (val.inact_ths_mg < (uint32_t)(125.0f * 63.0f)))
  {
    inactivity_dur.wu_inact_ths_w = 4;

    tmp = (float_t)val.inact_ths_mg / 125.0f;
    inactivity_ths.inact_ths = (uint8_t)tmp;

    tmp = (float_t)val.wk_ths_mg / 125.0f;
    wake_up_ths.wk_ths = (uint8_t)tmp;
  }
  else if ((val.wk_ths_mg < (uint32_t)(250.0f * 63.0f))
           && (val.inact_ths_mg < (uint32_t)(250.0f * 63.0f)))
  {
    inactivity_dur.wu_inact_ths_w = 5;

    tmp = (float_t)val.inact_ths_mg / 250.0f;
    inactivity_ths.inact_ths = (uint8_t)tmp;

    tmp = (float_t)val.wk_ths_mg / 250.0f;
    wake_up_ths.wk_ths = (uint8_t)tmp;
  }
  else // out of limit
  {
    inactivity_dur.wu_inact_ths_w = 5;
    inactivity_ths.inact_ths = 0x3FU;
    wake_up_ths.wk_ths = 0x3FU;
  }

  if (ret == 0)
  {
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_INACTIVITY_DUR, (uint8_t *)&inactivity_dur, 1);
  }
  if (ret == 0)
  {

    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_INACTIVITY_THS, (uint8_t *)&inactivity_ths, 1);
  }
  if (ret == 0)
  {

    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_WAKE_UP_THS, (uint8_t *)&wake_up_ths, 1);
  }

  return ret;
}

/**
  * @brief  Wakeup and activity/inactivity threshold.[get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Wakeup and activity/inactivity threshold.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_thresholds_get(stmdev_ctx_t *ctx,
                                      lsm6dsv16x_act_thresholds_t *val)
{
  lsm6dsv16x_inactivity_dur_t inactivity_dur;
  lsm6dsv16x_inactivity_ths_t inactivity_ths;
  lsm6dsv16x_wake_up_ths_t wake_up_ths;
  int32_t ret;
  float_t tmp;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INACTIVITY_DUR, (uint8_t *)&inactivity_dur, 1);
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_INACTIVITY_THS, (uint8_t *)&inactivity_ths, 1);
  }
  if (ret == 0)
  {
    ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_THS, (uint8_t *)&wake_up_ths, 1);
  }

  switch (inactivity_dur.wu_inact_ths_w)
  {
    case 0:
      tmp = (float_t)wake_up_ths.wk_ths * 7.8125f;
      val->wk_ths_mg = (uint32_t)tmp;

      tmp = (float_t)inactivity_ths.inact_ths * 7.8125f;
      val->inact_ths_mg = (uint32_t)tmp;
      break;

    case 1:
      tmp = (float_t)wake_up_ths.wk_ths * 15.625f;
      val->wk_ths_mg = (uint32_t)tmp;

      tmp = (float_t)inactivity_ths.inact_ths * 15.625f;
      val->inact_ths_mg = (uint32_t)tmp;
      break;

    case 2:
      tmp = (float_t)wake_up_ths.wk_ths * 31.25f;
      val->wk_ths_mg = (uint32_t)tmp;

      tmp = (float_t)inactivity_ths.inact_ths * 31.25f;
      val->inact_ths_mg = (uint32_t)tmp;
      break;

    case 3:
      tmp = (float_t)wake_up_ths.wk_ths * 62.5f;
      val->wk_ths_mg = (uint32_t)tmp;

      tmp = (float_t)inactivity_ths.inact_ths * 62.5f;
      val->inact_ths_mg = (uint32_t)tmp;
      break;

    case 4:
      tmp = (float_t)wake_up_ths.wk_ths * 125.0f;
      val->wk_ths_mg = (uint32_t)tmp;

      tmp = (float_t)inactivity_ths.inact_ths * 125.0f;
      val->inact_ths_mg = (uint32_t)tmp;
      break;

    default:
      tmp = (float_t)wake_up_ths.wk_ths * 250.0f;
      val->wk_ths_mg = (uint32_t)tmp;

      tmp = (float_t)inactivity_ths.inact_ths * 250.0f;
      val->inact_ths_mg = (uint32_t)tmp;
      break;
  }

  return ret;
}

/**
  * @brief  Time windows configuration for Wake Up - Activity - Inactivity (SLEEP, WAKE). Duration to go in sleep mode. Default value: 0000 (this corresponds to 16 ODR) 1 LSB = 512/ODR_XL time. Wake up duration event. 1 LSB = 1/ODR_XL time. [set]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Time windows configuration for Wake Up - Activity - Inactivity (SLEEP, WAKE). Duration to go in sleep mode. Default value: 0000 (this corresponds to 16 ODR) 1 LSB = 512/ODR_XL time. Wake up duration event. 1 LSB = 1/ODR_XL time.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_wkup_time_windows_set(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_act_wkup_time_windows_t val)
{
  lsm6dsv16x_wake_up_dur_t wake_up_dur;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_DUR, (uint8_t *)&wake_up_dur, 1);
  if (ret == 0)
  {
    wake_up_dur.wake_dur = val.shock;
    wake_up_dur.sleep_dur = val.quiet;
    ret = lsm6dsv16x_write_reg(ctx, LSM6DSV16X_WAKE_UP_DUR, (uint8_t *)&wake_up_dur, 1);
  }

  return ret;
}

/**
  * @brief  Time windows configuration for Wake Up - Activity - Inactivity (SLEEP, WAKE). Duration to go in sleep mode. Default value: 0000 (this corresponds to 16 ODR) 1 LSB = 512/ODR_XL time. Wake up duration event. 1 LSB = 1/ODR_XL time. [get]
  *
  * @param  ctx      read / write interface definitions
  * @param  val      Time windows configuration for Wake Up - Activity - Inactivity (SLEEP, WAKE). Duration to go in sleep mode. Default value: 0000 (this corresponds to 16 ODR) 1 LSB = 512/ODR_XL time. Wake up duration event. 1 LSB = 1/ODR_XL time.
  * @retval          interface status (MANDATORY: return 0 -> no Error)
  *
  */
int32_t lsm6dsv16x_act_wkup_time_windows_get(stmdev_ctx_t *ctx,
                                             lsm6dsv16x_act_wkup_time_windows_t *val)
{
  lsm6dsv16x_wake_up_dur_t wake_up_dur;
  int32_t ret;

  ret = lsm6dsv16x_read_reg(ctx, LSM6DSV16X_WAKE_UP_DUR, (uint8_t *)&wake_up_dur, 1);
  val->shock = wake_up_dur.wake_dur;
  val->quiet = wake_up_dur.sleep_dur;

  return ret;
}

/**
  * @}
  *
  */