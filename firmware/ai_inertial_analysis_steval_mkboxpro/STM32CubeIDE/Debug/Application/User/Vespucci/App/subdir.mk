################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Vespucci/App/app_vespucci.c 

OBJS += \
./Application/User/Vespucci/App/app_vespucci.o 

C_DEPS += \
./Application/User/Vespucci/App/app_vespucci.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Vespucci/App/app_vespucci.o: C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Vespucci/App/app_vespucci.c Application/User/Vespucci/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../../X-CUBE-MEMS1/Target -I../../Vespucci/App -I../../Middlewares/ST/PnPL_library/Core/Inc -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/pre_processing_library/Inc -I../../Middlewares/ST/pre_processing_library -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../Middlewares/ST/ai_app_library -I../../Middlewares/ST/DSP/Include -I../../Middlewares/ST/PnPL_library/PnPL/Inc -I../../Middlewares/ST/PnPL_library/PnPLCompManager/Inc -I../../Middlewares/ST/PnPL_library/Third_Party/parson -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components/lsm6dsv16x -I../../Middlewares/ST/AI/Inc -I../../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Vespucci-2f-App

clean-Application-2f-User-2f-Vespucci-2f-App:
	-$(RM) ./Application/User/Vespucci/App/app_vespucci.cyclo ./Application/User/Vespucci/App/app_vespucci.d ./Application/User/Vespucci/App/app_vespucci.o ./Application/User/Vespucci/App/app_vespucci.su

.PHONY: clean-Application-2f-User-2f-Vespucci-2f-App

