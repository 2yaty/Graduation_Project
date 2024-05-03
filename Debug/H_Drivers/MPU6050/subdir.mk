################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../H_Drivers/MPU6050/MPU.c \
../H_Drivers/MPU6050/MPU_Lcfg.c 

OBJS += \
./H_Drivers/MPU6050/MPU.o \
./H_Drivers/MPU6050/MPU_Lcfg.o 

C_DEPS += \
./H_Drivers/MPU6050/MPU.d \
./H_Drivers/MPU6050/MPU_Lcfg.d 


# Each subdirectory must supply rules for building sources it contributes
H_Drivers/MPU6050/%.o H_Drivers/MPU6050/%.su H_Drivers/MPU6050/%.cyclo: ../H_Drivers/MPU6050/%.c H_Drivers/MPU6050/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Modules" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/INITs_Uitilities" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers/TF_Lidar" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Application" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-H_Drivers-2f-MPU6050

clean-H_Drivers-2f-MPU6050:
	-$(RM) ./H_Drivers/MPU6050/MPU.cyclo ./H_Drivers/MPU6050/MPU.d ./H_Drivers/MPU6050/MPU.o ./H_Drivers/MPU6050/MPU.su ./H_Drivers/MPU6050/MPU_Lcfg.cyclo ./H_Drivers/MPU6050/MPU_Lcfg.d ./H_Drivers/MPU6050/MPU_Lcfg.o ./H_Drivers/MPU6050/MPU_Lcfg.su

.PHONY: clean-H_Drivers-2f-MPU6050

