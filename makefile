################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Application/Src/subdir.mk
-include subdir.mk
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

# recompile version.h dependants when GIT_VERSION changes, uses temporary file version~
.PHONY: force
../Application/Inc/git.h: force
	@echo "#ifndef _GIT_H_ /* Definiere Klasse _GIT_H_ */" > $@
	@echo "#define _GIT_H_ /* GIT_H */" >> $@
	@echo "" >> $@
	@echo "#define GIT_COMMIT \"$(shell git describe --always)\"" >> $@
	@echo "#define GIT_BRANCH \"$(shell git branch --show-current)\"" >> $@
	@echo "#define GIT_HASH \"$(shell git rev-parse HEAD)\"" >> $@
	@echo "#define GIT_TAG \"$(shell git tag)\"" >> $@
	@echo "" >> $@
	@echo "#define BUILD_DATE \"$(shell date +"%Y-%m-%d")\"" >> $@
	@echo "#define BUILD_TIME \"$(shell date +"%H:%M:%S")\"" >> $@
	@echo "#endif /* GIT_H */" >> $@

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
STM32F767ZI.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
STM32F767ZI.list \

OBJCOPY_BIN += \
STM32F767ZI.bin \


# All Target
all: ../Application/Inc/git.h STM32F767ZI.elf secondary-outputs

# Tool invocations
STM32F767ZI.elf: $(OBJS) $(USER_OBJS) C:\Users\Frederik\Documents\Git\STM32F767ZIT\STM32F767ZITX_FLASH.ld
	arm-none-eabi-gcc -o "STM32F767ZI.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\Frederik\Documents\Git\STM32F767ZIT\STM32F767ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="STM32F767ZI.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

STM32F767ZI.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "STM32F767ZI.list"
	@echo 'Finished building: $@'
	@echo ' '

STM32F767ZI.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "STM32F767ZI.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
