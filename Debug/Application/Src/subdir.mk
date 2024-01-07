################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Src/AD8403.c \
../Application/Src/BasicUart.c \
../Application/Src/CAN_Bus.c \
../Application/Src/CAN_config.c \
../Application/Src/LTC1380.c \
../Application/Src/LTC6811.c \
../Application/Src/SystemInfo.c \
../Application/Src/adc_inputs.c \
../Application/Src/app_info.c \
../Application/Src/error.c \
../Application/Src/imd.c \
../Application/Src/inputs.c \
../Application/Src/millis.c \
../Application/Src/my_math.c \
../Application/Src/outputs.c 

OBJS += \
./Application/Src/AD8403.o \
./Application/Src/BasicUart.o \
./Application/Src/CAN_Bus.o \
./Application/Src/CAN_config.o \
./Application/Src/LTC1380.o \
./Application/Src/LTC6811.o \
./Application/Src/SystemInfo.o \
./Application/Src/adc_inputs.o \
./Application/Src/app_info.o \
./Application/Src/error.o \
./Application/Src/imd.o \
./Application/Src/inputs.o \
./Application/Src/millis.o \
./Application/Src/my_math.o \
./Application/Src/outputs.o 

C_DEPS += \
./Application/Src/AD8403.d \
./Application/Src/BasicUart.d \
./Application/Src/CAN_Bus.d \
./Application/Src/CAN_config.d \
./Application/Src/LTC1380.d \
./Application/Src/LTC6811.d \
./Application/Src/SystemInfo.d \
./Application/Src/adc_inputs.d \
./Application/Src/app_info.d \
./Application/Src/error.d \
./Application/Src/imd.d \
./Application/Src/inputs.d \
./Application/Src/millis.d \
./Application/Src/my_math.d \
./Application/Src/outputs.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Src/%.o Application/Src/%.su Application/Src/%.cyclo: ../Application/Src/%.c Application/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F767xx -c -I../Application/Inc -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Src

clean-Application-2f-Src:
	-$(RM) ./Application/Src/AD8403.cyclo ./Application/Src/AD8403.d ./Application/Src/AD8403.o ./Application/Src/AD8403.su ./Application/Src/BasicUart.cyclo ./Application/Src/BasicUart.d ./Application/Src/BasicUart.o ./Application/Src/BasicUart.su ./Application/Src/CAN_Bus.cyclo ./Application/Src/CAN_Bus.d ./Application/Src/CAN_Bus.o ./Application/Src/CAN_Bus.su ./Application/Src/CAN_config.cyclo ./Application/Src/CAN_config.d ./Application/Src/CAN_config.o ./Application/Src/CAN_config.su ./Application/Src/LTC1380.cyclo ./Application/Src/LTC1380.d ./Application/Src/LTC1380.o ./Application/Src/LTC1380.su ./Application/Src/LTC6811.cyclo ./Application/Src/LTC6811.d ./Application/Src/LTC6811.o ./Application/Src/LTC6811.su ./Application/Src/SystemInfo.cyclo ./Application/Src/SystemInfo.d ./Application/Src/SystemInfo.o ./Application/Src/SystemInfo.su ./Application/Src/adc_inputs.cyclo ./Application/Src/adc_inputs.d ./Application/Src/adc_inputs.o ./Application/Src/adc_inputs.su ./Application/Src/app_info.cyclo ./Application/Src/app_info.d ./Application/Src/app_info.o ./Application/Src/app_info.su ./Application/Src/error.cyclo ./Application/Src/error.d ./Application/Src/error.o ./Application/Src/error.su ./Application/Src/imd.cyclo ./Application/Src/imd.d ./Application/Src/imd.o ./Application/Src/imd.su ./Application/Src/inputs.cyclo ./Application/Src/inputs.d ./Application/Src/inputs.o ./Application/Src/inputs.su ./Application/Src/millis.cyclo ./Application/Src/millis.d ./Application/Src/millis.o ./Application/Src/millis.su ./Application/Src/my_math.cyclo ./Application/Src/my_math.d ./Application/Src/my_math.o ./Application/Src/my_math.su ./Application/Src/outputs.cyclo ./Application/Src/outputs.d ./Application/Src/outputs.o ./Application/Src/outputs.su

.PHONY: clean-Application-2f-Src

