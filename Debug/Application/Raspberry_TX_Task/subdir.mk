################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Raspberry_TX_Task/Ras_TX_Task.c 

OBJS += \
./Application/Raspberry_TX_Task/Ras_TX_Task.o 

C_DEPS += \
./Application/Raspberry_TX_Task/Ras_TX_Task.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Raspberry_TX_Task/%.o Application/Raspberry_TX_Task/%.su Application/Raspberry_TX_Task/%.cyclo: ../Application/Raspberry_TX_Task/%.c Application/Raspberry_TX_Task/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Modules" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/INITs_Uitilities" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers/TF_Lidar" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Raspberry_TX_Task

clean-Application-2f-Raspberry_TX_Task:
	-$(RM) ./Application/Raspberry_TX_Task/Ras_TX_Task.cyclo ./Application/Raspberry_TX_Task/Ras_TX_Task.d ./Application/Raspberry_TX_Task/Ras_TX_Task.o ./Application/Raspberry_TX_Task/Ras_TX_Task.su

.PHONY: clean-Application-2f-Raspberry_TX_Task

