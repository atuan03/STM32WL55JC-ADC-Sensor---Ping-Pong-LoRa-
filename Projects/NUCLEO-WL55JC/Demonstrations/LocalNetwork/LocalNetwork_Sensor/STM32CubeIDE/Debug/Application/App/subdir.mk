################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/SISLAB/STM32Cube_FW_WL_V1.3.0/Projects/NUCLEO-WL55JC/Demonstrations/LocalNetwork/LocalNetwork_Sensor/SubGHz_Phy/App/demo_sensor.c 

OBJS += \
./Application/App/demo_sensor.o 

C_DEPS += \
./Application/App/demo_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
Application/App/demo_sensor.o: D:/SISLAB/STM32Cube_FW_WL_V1.3.0/Projects/NUCLEO-WL55JC/Demonstrations/LocalNetwork/LocalNetwork_Sensor/SubGHz_Phy/App/demo_sensor.c Application/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32WL55xx -DCORE_CM4 -DDEBUG -c -I../../Core/Inc -I../../SubGHz_Phy/App -I../../SubGHz_Phy/Target -I../../../LocalNetwork_Concentrator/Common/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-App

clean-Application-2f-App:
	-$(RM) ./Application/App/demo_sensor.cyclo ./Application/App/demo_sensor.d ./Application/App/demo_sensor.o ./Application/App/demo_sensor.su

.PHONY: clean-Application-2f-App

