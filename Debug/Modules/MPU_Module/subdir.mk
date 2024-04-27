################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/MPU_Module/MPU_Mod.c 

OBJS += \
./Modules/MPU_Module/MPU_Mod.o 

C_DEPS += \
./Modules/MPU_Module/MPU_Mod.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/MPU_Module/%.o Modules/MPU_Module/%.su Modules/MPU_Module/%.cyclo: ../Modules/MPU_Module/%.c Modules/MPU_Module/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Modules" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/INITs_Uitilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-MPU_Module

clean-Modules-2f-MPU_Module:
	-$(RM) ./Modules/MPU_Module/MPU_Mod.cyclo ./Modules/MPU_Module/MPU_Mod.d ./Modules/MPU_Module/MPU_Mod.o ./Modules/MPU_Module/MPU_Mod.su

.PHONY: clean-Modules-2f-MPU_Module

