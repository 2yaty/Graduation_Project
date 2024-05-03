################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../INITs_Uitilities/cJSON/cJSON.c 

OBJS += \
./INITs_Uitilities/cJSON/cJSON.o 

C_DEPS += \
./INITs_Uitilities/cJSON/cJSON.d 


# Each subdirectory must supply rules for building sources it contributes
INITs_Uitilities/cJSON/%.o INITs_Uitilities/cJSON/%.su INITs_Uitilities/cJSON/%.cyclo: ../INITs_Uitilities/cJSON/%.c INITs_Uitilities/cJSON/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Modules" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/INITs_Uitilities" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers/TF_Lidar" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-INITs_Uitilities-2f-cJSON

clean-INITs_Uitilities-2f-cJSON:
	-$(RM) ./INITs_Uitilities/cJSON/cJSON.cyclo ./INITs_Uitilities/cJSON/cJSON.d ./INITs_Uitilities/cJSON/cJSON.o ./INITs_Uitilities/cJSON/cJSON.su

.PHONY: clean-INITs_Uitilities-2f-cJSON

