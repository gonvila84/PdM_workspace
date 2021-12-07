################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f429xx.s 

OBJS += \
./Startup/startup_stm32f429xx.o 

S_DEPS += \
./Startup/startup_stm32f429xx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Drivers/CMSIS/Include" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Drivers/BSP/STM32F4xx_Nucleo_144" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Inc" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Drivers/Core/Inc" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Drivers/API/inc" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Drivers/API/src" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Drivers/API" -I"/home/gonzalo/Work/ProgMicroproc/PdmEjerciciosEntregables/Entrega_Ej3/Drivers" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

