################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MyDrivers/Src/EXTI.c \
../MyDrivers/Src/GPIO.c \
../MyDrivers/Src/RCC.c \
../MyDrivers/Src/SPI.c \
../MyDrivers/Src/uart.c 

OBJS += \
./MyDrivers/Src/EXTI.o \
./MyDrivers/Src/GPIO.o \
./MyDrivers/Src/RCC.o \
./MyDrivers/Src/SPI.o \
./MyDrivers/Src/uart.o 

C_DEPS += \
./MyDrivers/Src/EXTI.d \
./MyDrivers/Src/GPIO.d \
./MyDrivers/Src/RCC.d \
./MyDrivers/Src/SPI.d \
./MyDrivers/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MyDrivers/Src/%.o: ../MyDrivers/Src/%.c MyDrivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I"D:/gomuluyazilim/Driver_Development/MyDrivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MyDrivers-2f-Src

clean-MyDrivers-2f-Src:
	-$(RM) ./MyDrivers/Src/EXTI.d ./MyDrivers/Src/EXTI.o ./MyDrivers/Src/GPIO.d ./MyDrivers/Src/GPIO.o ./MyDrivers/Src/RCC.d ./MyDrivers/Src/RCC.o ./MyDrivers/Src/SPI.d ./MyDrivers/Src/SPI.o ./MyDrivers/Src/uart.d ./MyDrivers/Src/uart.o

.PHONY: clean-MyDrivers-2f-Src

