################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../H_Drivers/Led/Led.c \
../H_Drivers/Led/Led_Lcfg.c 

OBJS += \
./H_Drivers/Led/Led.o \
./H_Drivers/Led/Led_Lcfg.o 

C_DEPS += \
./H_Drivers/Led/Led.d \
./H_Drivers/Led/Led_Lcfg.d 


# Each subdirectory must supply rules for building sources it contributes
H_Drivers/Led/%.o H_Drivers/Led/%.su H_Drivers/Led/%.cyclo: ../H_Drivers/Led/%.c H_Drivers/Led/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/App_Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-H_Drivers-2f-Led

clean-H_Drivers-2f-Led:
	-$(RM) ./H_Drivers/Led/Led.cyclo ./H_Drivers/Led/Led.d ./H_Drivers/Led/Led.o ./H_Drivers/Led/Led.su ./H_Drivers/Led/Led_Lcfg.cyclo ./H_Drivers/Led/Led_Lcfg.d ./H_Drivers/Led/Led_Lcfg.o ./H_Drivers/Led/Led_Lcfg.su

.PHONY: clean-H_Drivers-2f-Led

