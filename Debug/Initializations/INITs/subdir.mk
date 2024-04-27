################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Initializations/INITs/INITs.c 

OBJS += \
./Initializations/INITs/INITs.o 

C_DEPS += \
./Initializations/INITs/INITs.d 


# Each subdirectory must supply rules for building sources it contributes
Initializations/INITs/%.o Initializations/INITs/%.su Initializations/INITs/%.cyclo: ../Initializations/INITs/%.c Initializations/INITs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Initializations" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Initializations-2f-INITs

clean-Initializations-2f-INITs:
	-$(RM) ./Initializations/INITs/INITs.cyclo ./Initializations/INITs/INITs.d ./Initializations/INITs/INITs.o ./Initializations/INITs/INITs.su

.PHONY: clean-Initializations-2f-INITs

