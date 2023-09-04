################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Middlewares/ST/ai_app_library/ai_app.c 

OBJS += \
./Middlewares/X-CUBE-VESPUCCI/Application\ Library/AI\ Library/ai_app.o 

C_DEPS += \
./Middlewares/X-CUBE-VESPUCCI/Application\ Library/AI\ Library/ai_app.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/X-CUBE-VESPUCCI/Application\ Library/AI\ Library/ai_app.o: C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Middlewares/ST/ai_app_library/ai_app.c Middlewares/X-CUBE-VESPUCCI/Application\ Library/AI\ Library/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../../X-CUBE-MEMS1/Target -I../../Vespucci/App -I../../Middlewares/ST/PnPL_library/Core/Inc -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/pre_processing_library/Inc -I../../Middlewares/ST/pre_processing_library -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../Middlewares/ST/ai_app_library -I../../Middlewares/ST/DSP/Include -I../../Middlewares/ST/PnPL_library/PnPL/Inc -I../../Middlewares/ST/PnPL_library/PnPLCompManager/Inc -I../../Middlewares/ST/PnPL_library/Third_Party/parson -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components/lsm6dsv16x -I../../Middlewares/ST/AI/Inc -I../../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Middlewares/X-CUBE-VESPUCCI/Application Library/AI Library/ai_app.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-X-2d-CUBE-2d-VESPUCCI-2f-Application-20-Library-2f-AI-20-Library

clean-Middlewares-2f-X-2d-CUBE-2d-VESPUCCI-2f-Application-20-Library-2f-AI-20-Library:
	-$(RM) ./Middlewares/X-CUBE-VESPUCCI/Application\ Library/AI\ Library/ai_app.cyclo ./Middlewares/X-CUBE-VESPUCCI/Application\ Library/AI\ Library/ai_app.d ./Middlewares/X-CUBE-VESPUCCI/Application\ Library/AI\ Library/ai_app.o ./Middlewares/X-CUBE-VESPUCCI/Application\ Library/AI\ Library/ai_app.su

.PHONY: clean-Middlewares-2f-X-2d-CUBE-2d-VESPUCCI-2f-Application-20-Library-2f-AI-20-Library

