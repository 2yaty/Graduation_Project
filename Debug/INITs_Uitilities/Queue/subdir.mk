################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../INITs_Uitilities/Queue/queue.c 

OBJS += \
./INITs_Uitilities/Queue/queue.o 

C_DEPS += \
./INITs_Uitilities/Queue/queue.d 


# Each subdirectory must supply rules for building sources it contributes
INITs_Uitilities/Queue/%.o INITs_Uitilities/Queue/%.su INITs_Uitilities/Queue/%.cyclo: ../INITs_Uitilities/Queue/%.c INITs_Uitilities/Queue/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Modules" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/INITs_Uitilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-INITs_Uitilities-2f-Queue

clean-INITs_Uitilities-2f-Queue:
	-$(RM) ./INITs_Uitilities/Queue/queue.cyclo ./INITs_Uitilities/Queue/queue.d ./INITs_Uitilities/Queue/queue.o ./INITs_Uitilities/Queue/queue.su

.PHONY: clean-INITs_Uitilities-2f-Queue

