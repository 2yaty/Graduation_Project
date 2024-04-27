################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../INITs_Uitilities/INITs/INITs.c 

OBJS += \
./INITs_Uitilities/INITs/INITs.o 

C_DEPS += \
./INITs_Uitilities/INITs/INITs.d 


# Each subdirectory must supply rules for building sources it contributes
INITs_Uitilities/INITs/%.o INITs_Uitilities/INITs/%.su INITs_Uitilities/INITs/%.cyclo: ../INITs_Uitilities/INITs/%.c INITs_Uitilities/INITs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Modules" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/INITs_Uitilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-INITs_Uitilities-2f-INITs

clean-INITs_Uitilities-2f-INITs:
	-$(RM) ./INITs_Uitilities/INITs/INITs.cyclo ./INITs_Uitilities/INITs/INITs.d ./INITs_Uitilities/INITs/INITs.o ./INITs_Uitilities/INITs/INITs.su

.PHONY: clean-INITs_Uitilities-2f-INITs

