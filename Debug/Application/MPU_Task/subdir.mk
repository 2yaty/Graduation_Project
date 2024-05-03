################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/MPU_Task/MPU_Mod.c 

OBJS += \
./Application/MPU_Task/MPU_Mod.o 

C_DEPS += \
./Application/MPU_Task/MPU_Mod.d 


# Each subdirectory must supply rules for building sources it contributes
Application/MPU_Task/%.o Application/MPU_Task/%.su Application/MPU_Task/%.cyclo: ../Application/MPU_Task/%.c Application/MPU_Task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Modules" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/INITs_Uitilities" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers/TF_Lidar" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-MPU_Task

clean-Application-2f-MPU_Task:
	-$(RM) ./Application/MPU_Task/MPU_Mod.cyclo ./Application/MPU_Task/MPU_Mod.d ./Application/MPU_Task/MPU_Mod.o ./Application/MPU_Task/MPU_Mod.su

.PHONY: clean-Application-2f-MPU_Task

