################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/CortexM3_Core_Systick.c \
../Src/HAL_Adc.c \
../Src/HAL_Gpio.c \
../Src/HAL_Timer.c \
../Src/HAL_Usart.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/CortexM3_Core_Systick.o \
./Src/HAL_Adc.o \
./Src/HAL_Gpio.o \
./Src/HAL_Timer.o \
./Src/HAL_Usart.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/CortexM3_Core_Systick.d \
./Src/HAL_Adc.d \
./Src/HAL_Gpio.d \
./Src/HAL_Timer.d \
./Src/HAL_Usart.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"H:/EmbeddedSystems/STMF103/Chip_Headers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/EmbeddedSystems/STMF103/Chip_Headers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

