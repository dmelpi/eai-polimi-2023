/**
  ******************************************************************************
  * @file    custom_mems_conf.h
  * @author  MEMS Application Team
  * @brief   This file contains definitions of the MEMS components bus interfaces for custom boards
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
#ifndef __CUSTOM_MEMS_CONF_H__
#define __CUSTOM_MEMS_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal.h"
#include "custom_bus.h"
#include "custom_errno.h"

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#define USE_CUSTOM_MOTION_SENSOR_LSM6DSV16X_0     1U

#define CUSTOM_LSM6DSV16X_0_SPI_Init BSP_SPI2_Init
#define CUSTOM_LSM6DSV16X_0_SPI_DeInit BSP_SPI2_DeInit
#define CUSTOM_LSM6DSV16X_0_SPI_Send BSP_SPI2_Send
#define CUSTOM_LSM6DSV16X_0_SPI_Recv BSP_SPI2_Recv

#define CUSTOM_LSM6DSV16X_0_CS_PORT GPIOI
#define CUSTOM_LSM6DSV16X_0_CS_PIN GPIO_PIN_5

#ifdef __cplusplus
}
#endif

#endif /* __CUSTOM_MEMS_CONF_H__*/
