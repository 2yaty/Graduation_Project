################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../H_Drivers/FCW_Application/FCW_App.c 

OBJS += \
./H_Drivers/FCW_Application/FCW_App.o 

C_DEPS += \
./H_Drivers/FCW_Application/FCW_App.d 


# Each subdirectory must supply rules for building sources it contributes
H_Drivers/FCW_Application/%.o H_Drivers/FCW_Application/%.su H_Drivers/FCW_Application/%.cyclo: ../H_Drivers/FCW_Application/%.c H_Drivers/FCW_Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Modules" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/INITs_Uitilities" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers/TF_Lidar" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-H_Drivers-2f-FCW_Application

clean-H_Drivers-2f-FCW_Application:
	-$(RM) ./H_Drivers/FCW_Application/FCW_App.cyclo ./H_Drivers/FCW_Application/FCW_App.d ./H_Drivers/FCW_Application/FCW_App.o ./H_Drivers/FCW_Application/FCW_App.su

.PHONY: clean-H_Drivers-2f-FCW_Application

