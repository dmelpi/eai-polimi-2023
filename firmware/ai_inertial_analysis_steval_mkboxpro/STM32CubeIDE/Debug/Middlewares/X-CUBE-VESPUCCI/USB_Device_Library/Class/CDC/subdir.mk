################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c 

OBJS += \
./Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Class/CDC/usbd_cdc.o 

C_DEPS += \
./Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Class/CDC/usbd_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Class/CDC/usbd_cdc.o: C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/usbd_cdc.c Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Class/CDC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../../X-CUBE-MEMS1/Target -I../../Vespucci/App -I../../Middlewares/ST/PnPL_library/Core/Inc -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/pre_processing_library/Inc -I../../Middlewares/ST/pre_processing_library -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../Middlewares/ST/ai_app_library -I../../Middlewares/ST/DSP/Include -I../../Middlewares/ST/PnPL_library/PnPL/Inc -I../../Middlewares/ST/PnPL_library/PnPLCompManager/Inc -I../../Middlewares/ST/PnPL_library/Third_Party/parson -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components/lsm6dsv16x -I../../Middlewares/ST/AI/Inc -I../../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-X-2d-CUBE-2d-VESPUCCI-2f-USB_Device_Library-2f-Class-2f-CDC

clean-Middlewares-2f-X-2d-CUBE-2d-VESPUCCI-2f-USB_Device_Library-2f-Class-2f-CDC:
	-$(RM) ./Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Class/CDC/usbd_cdc.cyclo ./Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Class/CDC/usbd_cdc.d ./Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Class/CDC/usbd_cdc.o ./Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Class/CDC/usbd_cdc.su

.PHONY: clean-Middlewares-2f-X-2d-CUBE-2d-VESPUCCI-2f-USB_Device_Library-2f-Class-2f-CDC

