################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/API/src/EDTF_API_debounce.c \
../Drivers/API/src/EDTF_API_delay.c \
../Drivers/API/src/EDTF_API_led.c \
../Drivers/API/src/EDTF_API_uart.c \
../Drivers/API/src/EDTF_CommandServer.c 

OBJS += \
./Drivers/API/src/EDTF_API_debounce.o \
./Drivers/API/src/EDTF_API_delay.o \
./Drivers/API/src/EDTF_API_led.o \
./Drivers/API/src/EDTF_API_uart.o \
./Drivers/API/src/EDTF_CommandServer.o 

C_DEPS += \
./Drivers/API/src/EDTF_API_debounce.d \
./Drivers/API/src/EDTF_API_delay.d \
./Drivers/API/src/EDTF_API_led.d \
./Drivers/API/src/EDTF_API_uart.d \
./Drivers/API/src/EDTF_CommandServer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/API/src/%.o: ../Drivers/API/src/%.c Drivers/API/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F429ZITx -DSTM32F4 -DNUCLEO_F429ZI -DUSE_HAL_DRIVER -DSTM32F429xx -c -I../Inc -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_TPFinal/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_TPFinal/Drivers/CMSIS/Include" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_TPFinal/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_TPFinal/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_TPFinal/Drivers/Core/Inc" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_TPFinal/Drivers/API/inc" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_TPFinal/Drivers/API/src" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_TPFinal/Drivers/API" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_TPFinal/Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

