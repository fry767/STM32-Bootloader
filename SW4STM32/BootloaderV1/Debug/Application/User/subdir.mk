################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/User/bootlib.c \
../Application/User/bootloaderhw.c \
H:/Documents/New\ Folder/BootloaderV1/Src/can.c \
../Application/User/com_interface.c \
H:/Documents/New\ Folder/BootloaderV1/Src/crc.c \
H:/Documents/New\ Folder/BootloaderV1/Src/dma.c \
H:/Documents/New\ Folder/BootloaderV1/Src/gpio.c \
H:/Documents/New\ Folder/BootloaderV1/Src/i2c.c \
H:/Documents/New\ Folder/BootloaderV1/Src/main.c \
../Application/User/protocole.c \
H:/Documents/New\ Folder/BootloaderV1/Src/spi.c \
H:/Documents/New\ Folder/BootloaderV1/Src/stm32f1xx_hal_msp.c \
H:/Documents/New\ Folder/BootloaderV1/Src/stm32f1xx_it.c \
../Application/User/test_FLASH_HW.c \
../Application/User/test_comm.c \
H:/Documents/New\ Folder/BootloaderV1/Src/tim.c \
H:/Documents/New\ Folder/BootloaderV1/Src/usart.c 

OBJS += \
./Application/User/bootlib.o \
./Application/User/bootloaderhw.o \
./Application/User/can.o \
./Application/User/com_interface.o \
./Application/User/crc.o \
./Application/User/dma.o \
./Application/User/gpio.o \
./Application/User/i2c.o \
./Application/User/main.o \
./Application/User/protocole.o \
./Application/User/spi.o \
./Application/User/stm32f1xx_hal_msp.o \
./Application/User/stm32f1xx_it.o \
./Application/User/test_FLASH_HW.o \
./Application/User/test_comm.o \
./Application/User/tim.o \
./Application/User/usart.o 

C_DEPS += \
./Application/User/bootlib.d \
./Application/User/bootloaderhw.d \
./Application/User/can.d \
./Application/User/com_interface.d \
./Application/User/crc.d \
./Application/User/dma.d \
./Application/User/gpio.d \
./Application/User/i2c.d \
./Application/User/main.d \
./Application/User/protocole.d \
./Application/User/spi.d \
./Application/User/stm32f1xx_hal_msp.d \
./Application/User/stm32f1xx_it.d \
./Application/User/test_FLASH_HW.d \
./Application/User/test_comm.d \
./Application/User/tim.d \
./Application/User/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/%.o: ../Application/User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/can.o: H:/Documents/New\ Folder/BootloaderV1/Src/can.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/can.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/crc.o: H:/Documents/New\ Folder/BootloaderV1/Src/crc.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/crc.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/dma.o: H:/Documents/New\ Folder/BootloaderV1/Src/dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/dma.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/gpio.o: H:/Documents/New\ Folder/BootloaderV1/Src/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/gpio.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/i2c.o: H:/Documents/New\ Folder/BootloaderV1/Src/i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/i2c.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: H:/Documents/New\ Folder/BootloaderV1/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/main.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/spi.o: H:/Documents/New\ Folder/BootloaderV1/Src/spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/spi.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f1xx_hal_msp.o: H:/Documents/New\ Folder/BootloaderV1/Src/stm32f1xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/stm32f1xx_hal_msp.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f1xx_it.o: H:/Documents/New\ Folder/BootloaderV1/Src/stm32f1xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/stm32f1xx_it.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/tim.o: H:/Documents/New\ Folder/BootloaderV1/Src/tim.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/tim.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/usart.o: H:/Documents/New\ Folder/BootloaderV1/Src/usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F103xB -I"H:/Documents/New Folder/BootloaderV1/Inc" -I"H:/Documents/New Folder/BootloaderV1/SW4STM32/BootloaderV1/Application/User" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc" -I"H:/Documents/New Folder/BootloaderV1/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"H:/Documents/New Folder/BootloaderV1/Drivers/CMSIS/Include" -I"H:/Documents/New Folder/BootloaderV1/Inc"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"Application/User/usart.d" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


