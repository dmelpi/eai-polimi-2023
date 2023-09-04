################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Core/subdir.mk
-include Middlewares/X-CUBE-VESPUCCI/USB_Device_Library/Class/CDC/subdir.mk
-include Middlewares/X-CUBE-VESPUCCI/Application\ Library/Pre\ Processing\ Library/subdir.mk
-include Middlewares/X-CUBE-VESPUCCI/Application\ Library/PnPL\ Library/subdir.mk
-include Middlewares/X-CUBE-VESPUCCI/Application\ Library/AI\ Library/subdir.mk
-include Drivers/STM32U5xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/Components/subdir.mk
-include Application/User/X-CUBE-MEMS1/Target/subdir.mk
-include Application/User/X-CUBE-AI/App/subdir.mk
-include Application/User/Vespucci/App/subdir.mk
-include Application/User/USB_Device/Target/subdir.mk
-include Application/User/USB_Device/App/subdir.mk
-include Application/User/Startup/subdir.mk
-include Application/User/Core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := ai_inertial_analysis_steval_mkboxpro
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ai_inertial_analysis_steval_mkboxpro.elf \

MAP_FILES += \
ai_inertial_analysis_steval_mkboxpro.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ai_inertial_analysis_steval_mkboxpro.list \

OBJCOPY_BIN += \
ai_inertial_analysis_steval_mkboxpro.bin \


# All Target
all: main-build

# Main-build Target
main-build: ai_inertial_analysis_steval_mkboxpro.elf secondary-outputs

# Tool invocations
ai_inertial_analysis_steval_mkboxpro.elf ai_inertial_analysis_steval_mkboxpro.map: $(OBJS) $(USER_OBJS) C:\workspace\firmware\ai_inertial_analysis_steval_mkboxpro\STM32CubeIDE\STM32U585AIIXQ_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ai_inertial_analysis_steval_mkboxpro.elf" @"objects.list" $(USER_OBJS) -Wl,--start-group $(LIBS) -Wl,--end-group -mcpu=cortex-m33 -T"C:\workspace\firmware\ai_inertial_analysis_steval_mkboxpro\STM32CubeIDE\STM32U585AIIXQ_FLASH.ld" --specs=nosys.specs -Wl,-Map="ai_inertial_analysis_steval_mkboxpro.map" -Wl,--gc-sections -static -L../../Middlewares/ST/DSP/Lib/GCC -L../../Middlewares/ST/AI/Lib --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ai_inertial_analysis_steval_mkboxpro.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ai_inertial_analysis_steval_mkboxpro.list"
	@echo 'Finished building: $@'
	@echo ' '

ai_inertial_analysis_steval_mkboxpro.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ai_inertial_analysis_steval_mkboxpro.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ai_inertial_analysis_steval_mkboxpro.bin ai_inertial_analysis_steval_mkboxpro.elf ai_inertial_analysis_steval_mkboxpro.list ai_inertial_analysis_steval_mkboxpro.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
