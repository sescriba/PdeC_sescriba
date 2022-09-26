################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/dev/src/mpu9250.c \
../Drivers/dev/src/port.c 

OBJS += \
./Drivers/dev/src/mpu9250.o \
./Drivers/dev/src/port.o 

C_DEPS += \
./Drivers/dev/src/mpu9250.d \
./Drivers/dev/src/port.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/dev/src/%.o Drivers/dev/src/%.su: ../Drivers/dev/src/%.c Drivers/dev/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Documents/CESE/Protocolos_Comunicacion/proyecto_final/PdeC_sescriba/MPU9250/inc" -I"D:/Documents/CESE/Protocolos_Comunicacion/proyecto_final/PdeC_sescriba/MPU9250/src" -I"D:/Documents/CESE/Protocolos_Comunicacion/proyecto_final/PdeC_sescriba/MPU9250/Drivers/dev/src" -I"D:/Documents/CESE/Protocolos_Comunicacion/proyecto_final/PdeC_sescriba/MPU9250/Drivers/dev/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-dev-2f-src

clean-Drivers-2f-dev-2f-src:
	-$(RM) ./Drivers/dev/src/mpu9250.d ./Drivers/dev/src/mpu9250.o ./Drivers/dev/src/mpu9250.su ./Drivers/dev/src/port.d ./Drivers/dev/src/port.o ./Drivers/dev/src/port.su

.PHONY: clean-Drivers-2f-dev-2f-src
