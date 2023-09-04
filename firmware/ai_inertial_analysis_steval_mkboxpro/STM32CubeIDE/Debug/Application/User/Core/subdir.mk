################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/App_model.c \
C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/custom_bus.c \
C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/main.c \
C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/stm32u5xx_hal_msp.c \
C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/stm32u5xx_it.c \
../Application/User/Core/syscalls.c \
../Application/User/Core/sysmem.c 

OBJS += \
./Application/User/Core/App_model.o \
./Application/User/Core/custom_bus.o \
./Application/User/Core/main.o \
./Application/User/Core/stm32u5xx_hal_msp.o \
./Application/User/Core/stm32u5xx_it.o \
./Application/User/Core/syscalls.o \
./Application/User/Core/sysmem.o 

C_DEPS += \
./Application/User/Core/App_model.d \
./Application/User/Core/custom_bus.d \
./Application/User/Core/main.d \
./Application/User/Core/stm32u5xx_hal_msp.d \
./Application/User/Core/stm32u5xx_it.d \
./Application/User/Core/syscalls.d \
./Application/User/Core/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/Core/App_model.o: C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/App_model.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../../X-CUBE-MEMS1/Target -I../../Vespucci/App -I../../Middlewares/ST/PnPL_library/Core/Inc -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/pre_processing_library/Inc -I../../Middlewares/ST/pre_processing_library -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../Middlewares/ST/ai_app_library -I../../Middlewares/ST/DSP/Include -I../../Middlewares/ST/PnPL_library/PnPL/Inc -I../../Middlewares/ST/PnPL_library/PnPLCompManager/Inc -I../../Middlewares/ST/PnPL_library/Third_Party/parson -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components/lsm6dsv16x -I../../Middlewares/ST/AI/Inc -I../../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/custom_bus.o: C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/custom_bus.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../../X-CUBE-MEMS1/Target -I../../Vespucci/App -I../../Middlewares/ST/PnPL_library/Core/Inc -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/pre_processing_library/Inc -I../../Middlewares/ST/pre_processing_library -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../Middlewares/ST/ai_app_library -I../../Middlewares/ST/DSP/Include -I../../Middlewares/ST/PnPL_library/PnPL/Inc -I../../Middlewares/ST/PnPL_library/PnPLCompManager/Inc -I../../Middlewares/ST/PnPL_library/Third_Party/parson -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components/lsm6dsv16x -I../../Middlewares/ST/AI/Inc -I../../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/main.o: C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/main.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../../X-CUBE-MEMS1/Target -I../../Vespucci/App -I../../Middlewares/ST/PnPL_library/Core/Inc -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/pre_processing_library/Inc -I../../Middlewares/ST/pre_processing_library -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../Middlewares/ST/ai_app_library -I../../Middlewares/ST/DSP/Include -I../../Middlewares/ST/PnPL_library/PnPL/Inc -I../../Middlewares/ST/PnPL_library/PnPLCompManager/Inc -I../../Middlewares/ST/PnPL_library/Third_Party/parson -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components/lsm6dsv16x -I../../Middlewares/ST/AI/Inc -I../../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/stm32u5xx_hal_msp.o: C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/stm32u5xx_hal_msp.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../../X-CUBE-MEMS1/Target -I../../Vespucci/App -I../../Middlewares/ST/PnPL_library/Core/Inc -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/pre_processing_library/Inc -I../../Middlewares/ST/pre_processing_library -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../Middlewares/ST/ai_app_library -I../../Middlewares/ST/DSP/Include -I../../Middlewares/ST/PnPL_library/PnPL/Inc -I../../Middlewares/ST/PnPL_library/PnPLCompManager/Inc -I../../Middlewares/ST/PnPL_library/Third_Party/parson -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components/lsm6dsv16x -I../../Middlewares/ST/AI/Inc -I../../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/stm32u5xx_it.o: C:/workspace/firmware/ai_inertial_analysis_steval_mkboxpro/Core/Src/stm32u5xx_it.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../../X-CUBE-MEMS1/Target -I../../Vespucci/App -I../../Middlewares/ST/PnPL_library/Core/Inc -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/pre_processing_library/Inc -I../../Middlewares/ST/pre_processing_library -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../Middlewares/ST/ai_app_library -I../../Middlewares/ST/DSP/Include -I../../Middlewares/ST/PnPL_library/PnPL/Inc -I../../Middlewares/ST/PnPL_library/PnPLCompManager/Inc -I../../Middlewares/ST/PnPL_library/Third_Party/parson -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components/lsm6dsv16x -I../../Middlewares/ST/AI/Inc -I../../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/Core/%.o Application/User/Core/%.su Application/User/Core/%.cyclo: ../Application/User/Core/%.c Application/User/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U585xx -c -I../../X-CUBE-MEMS1/Target -I../../Vespucci/App -I../../Middlewares/ST/PnPL_library/Core/Inc -I../../USB_Device/App -I../../USB_Device/Target -I../../Core/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/ST/pre_processing_library/Inc -I../../Middlewares/ST/pre_processing_library -I../../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../../Middlewares/ST/ai_app_library -I../../Middlewares/ST/DSP/Include -I../../Middlewares/ST/PnPL_library/PnPL/Inc -I../../Middlewares/ST/PnPL_library/PnPLCompManager/Inc -I../../Middlewares/ST/PnPL_library/Third_Party/parson -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Drivers/BSP/Components/Common -I../../Drivers/BSP/Components/lsm6dsv16x -I../../Middlewares/ST/AI/Inc -I../../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-Core

clean-Application-2f-User-2f-Core:
	-$(RM) ./Application/User/Core/App_model.cyclo ./Application/User/Core/App_model.d ./Application/User/Core/App_model.o ./Application/User/Core/App_model.su ./Application/User/Core/custom_bus.cyclo ./Application/User/Core/custom_bus.d ./Application/User/Core/custom_bus.o ./Application/User/Core/custom_bus.su ./Application/User/Core/main.cyclo ./Application/User/Core/main.d ./Application/User/Core/main.o ./Application/User/Core/main.su ./Application/User/Core/stm32u5xx_hal_msp.cyclo ./Application/User/Core/stm32u5xx_hal_msp.d ./Application/User/Core/stm32u5xx_hal_msp.o ./Application/User/Core/stm32u5xx_hal_msp.su ./Application/User/Core/stm32u5xx_it.cyclo ./Application/User/Core/stm32u5xx_it.d ./Application/User/Core/stm32u5xx_it.o ./Application/User/Core/stm32u5xx_it.su ./Application/User/Core/syscalls.cyclo ./Application/User/Core/syscalls.d ./Application/User/Core/syscalls.o ./Application/User/Core/syscalls.su ./Application/User/Core/sysmem.cyclo ./Application/User/Core/sysmem.d ./Application/User/Core/sysmem.o ./Application/User/Core/sysmem.su

.PHONY: clean-Application-2f-User-2f-Core

