################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/Queue/queue.c 

OBJS += \
./Modules/Queue/queue.o 

C_DEPS += \
./Modules/Queue/queue.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/Queue/%.o Modules/Queue/%.su Modules/Queue/%.cyclo: ../Modules/Queue/%.c Modules/Queue/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Initializations" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-Queue

clean-Modules-2f-Queue:
	-$(RM) ./Modules/Queue/queue.cyclo ./Modules/Queue/queue.d ./Modules/Queue/queue.o ./Modules/Queue/queue.su

.PHONY: clean-Modules-2f-Queue

