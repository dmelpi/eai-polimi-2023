/**
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

#ifndef MLC_CONF_H
#define MLC_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifndef MEMS_UCF_SHARED_TYPES
#define MEMS_UCF_SHARED_TYPES

/** Common data block definition **/
typedef struct {
  uint8_t address;
  uint8_t data;
} ucf_line_t;

#endif /* MEMS_UCF_SHARED_TYPES */

/** Configuration array generated from Unico Tool **/
ucf_line_t default_mlc_conf[] = {
		{.address = 0x10, .data = 0x00,},
		{.address = 0x11, .data = 0x00,},
		{.address = 0x01, .data = 0x80,},
		{.address = 0x04, .data = 0x00,},
		{.address = 0x05, .data = 0x00,},
		{.address = 0x17, .data = 0x40,},
		{.address = 0x02, .data = 0x11,},
		{.address = 0x08, .data = 0xEA,},
		{.address = 0x09, .data = 0x1C,},
		{.address = 0x09, .data = 0x02,},
		{.address = 0x09, .data = 0x30,},
		{.address = 0x09, .data = 0x02,},
		{.address = 0x09, .data = 0x01,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x14,},
		{.address = 0x09, .data = 0x01,},
		{.address = 0x09, .data = 0x0F,},
		{.address = 0x02, .data = 0x11,},
		{.address = 0x08, .data = 0xFA,},
		{.address = 0x09, .data = 0x14,},
		{.address = 0x09, .data = 0x02,},
		{.address = 0x09, .data = 0x32,},
		{.address = 0x09, .data = 0x02,},
		{.address = 0x09, .data = 0x3E,},
		{.address = 0x09, .data = 0x02,},
		{.address = 0x02, .data = 0x21,},
		{.address = 0x08, .data = 0x14,},
		{.address = 0x09, .data = 0x3F,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x18,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x1F,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x02, .data = 0x21,},
		{.address = 0x08, .data = 0x32,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x01, .data = 0x00,},
		{.address = 0x01, .data = 0x80,},
		{.address = 0x17, .data = 0x40,},
		{.address = 0x02, .data = 0x21,},
		{.address = 0x08, .data = 0x3E,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x00,},
		{.address = 0x09, .data = 0x02,},
		{.address = 0x09, .data = 0x80,},
		{.address = 0x09, .data = 0x66,},
		{.address = 0x09, .data = 0xB2,},
		{.address = 0x09, .data = 0x84,},
		{.address = 0x09, .data = 0xE0,},
		{.address = 0x09, .data = 0x66,},
		{.address = 0x09, .data = 0x32,},
		{.address = 0x09, .data = 0x08,},
		{.address = 0x09, .data = 0xE0,},
		{.address = 0x01, .data = 0x80,},
		{.address = 0x17, .data = 0x00,},
		{.address = 0x04, .data = 0x00,},
		{.address = 0x05, .data = 0x10,},
		{.address = 0x02, .data = 0x01,},
		{.address = 0x01, .data = 0x00,},
		{.address = 0x5E, .data = 0x02,},
		{.address = 0x01, .data = 0x80,},
		{.address = 0x0D, .data = 0x01,},
		{.address = 0x60, .data = 0x25,},
		{.address = 0x45, .data = 0x02,},
		{.address = 0x01, .data = 0x00,},
		{.address = 0x15, .data = 0x01,},
		{.address = 0x17, .data = 0x01,},
		{.address = 0x10, .data = 0x05,},
		{.address = 0x11, .data = 0x05,}
};


#ifdef __cplusplus
}
#endif

#endif /* MLC_CONF_H */

