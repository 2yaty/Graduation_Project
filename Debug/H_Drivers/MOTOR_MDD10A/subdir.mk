################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A.c \
../H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A_Lcfg.c 

OBJS += \
./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A.o \
./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A_Lcfg.o 

C_DEPS += \
./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A.d \
./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A_Lcfg.d 


# Each subdirectory must supply rules for building sources it contributes
H_Drivers/MOTOR_MDD10A/%.o H_Drivers/MOTOR_MDD10A/%.su H_Drivers/MOTOR_MDD10A/%.cyclo: ../H_Drivers/MOTOR_MDD10A/%.c H_Drivers/MOTOR_MDD10A/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/App_Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-H_Drivers-2f-MOTOR_MDD10A

clean-H_Drivers-2f-MOTOR_MDD10A:
	-$(RM) ./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A.cyclo ./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A.d ./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A.o ./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A.su ./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A_Lcfg.cyclo ./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A_Lcfg.d ./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A_Lcfg.o ./H_Drivers/MOTOR_MDD10A/MOTOR_MDD10A_Lcfg.su

.PHONY: clean-H_Drivers-2f-MOTOR_MDD10A

