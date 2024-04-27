################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../H_Drivers/Bluetooth/Bluetooth.c 

OBJS += \
./H_Drivers/Bluetooth/Bluetooth.o 

C_DEPS += \
./H_Drivers/Bluetooth/Bluetooth.d 


# Each subdirectory must supply rules for building sources it contributes
H_Drivers/Bluetooth/%.o H_Drivers/Bluetooth/%.su H_Drivers/Bluetooth/%.cyclo: ../H_Drivers/Bluetooth/%.c H_Drivers/Bluetooth/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/Modules" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/INITs_Uitilities" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-H_Drivers-2f-Bluetooth

clean-H_Drivers-2f-Bluetooth:
	-$(RM) ./H_Drivers/Bluetooth/Bluetooth.cyclo ./H_Drivers/Bluetooth/Bluetooth.d ./H_Drivers/Bluetooth/Bluetooth.o ./H_Drivers/Bluetooth/Bluetooth.su

.PHONY: clean-H_Drivers-2f-Bluetooth

