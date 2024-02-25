################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App_Drivers/Movement/MOv.c \
../App_Drivers/Movement/Queue.c 

OBJS += \
./App_Drivers/Movement/MOv.o \
./App_Drivers/Movement/Queue.o 

C_DEPS += \
./App_Drivers/Movement/MOv.d \
./App_Drivers/Movement/Queue.d 


# Each subdirectory must supply rules for building sources it contributes
App_Drivers/Movement/%.o App_Drivers/Movement/%.su App_Drivers/Movement/%.cyclo: ../App_Drivers/Movement/%.c App_Drivers/Movement/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/H_Drivers" -I"D:/Abd Elghafar/STM_v14_WORKSPACE/STM_APP/App_Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App_Drivers-2f-Movement

clean-App_Drivers-2f-Movement:
	-$(RM) ./App_Drivers/Movement/MOv.cyclo ./App_Drivers/Movement/MOv.d ./App_Drivers/Movement/MOv.o ./App_Drivers/Movement/MOv.su ./App_Drivers/Movement/Queue.cyclo ./App_Drivers/Movement/Queue.d ./App_Drivers/Movement/Queue.o ./App_Drivers/Movement/Queue.su

.PHONY: clean-App_Drivers-2f-Movement

