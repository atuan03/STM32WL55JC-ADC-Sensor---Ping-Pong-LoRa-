################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/SISLAB/STM32Cube_FW_WL_V1.3.0/Projects/NUCLEO-WL55JC/Demonstrations/LocalNetwork/LocalNetwork_Concentrator/Common/Src/demo_radio_utils.c \
D:/SISLAB/STM32Cube_FW_WL_V1.3.0/Projects/NUCLEO-WL55JC/Demonstrations/LocalNetwork/LocalNetwork_Concentrator/Common/Src/demo_regions.c \
D:/SISLAB/STM32Cube_FW_WL_V1.3.0/Projects/NUCLEO-WL55JC/Demonstrations/LocalNetwork/LocalNetwork_Concentrator/Common/Src/demo_utils.c 

OBJS += \
./Application/Common/demo_radio_utils.o \
./Application/Common/demo_regions.o \
./Application/Common/demo_utils.o 

C_DEPS += \
./Application/Common/demo_radio_utils.d \
./Application/Common/demo_regions.d \
./Application/Common/demo_utils.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Common/demo_radio_utils.o: D:/SISLAB/STM32Cube_FW_WL_V1.3.0/Projects/NUCLEO-WL55JC/Demonstrations/LocalNetwork/LocalNetwork_Concentrator/Common/Src/demo_radio_utils.c Application/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32WL55xx -DCORE_CM4 -DDEBUG -c -I../../Core/Inc -I../../SubGHz_Phy/App -I../../SubGHz_Phy/Target -I../../../LocalNetwork_Concentrator/Common/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/Common/demo_regions.o: D:/SISLAB/STM32Cube_FW_WL_V1.3.0/Projects/NUCLEO-WL55JC/Demonstrations/LocalNetwork/LocalNetwork_Concentrator/Common/Src/demo_regions.c Application/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32WL55xx -DCORE_CM4 -DDEBUG -c -I../../Core/Inc -I../../SubGHz_Phy/App -I../../SubGHz_Phy/Target -I../../../LocalNetwork_Concentrator/Common/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Application/Common/demo_utils.o: D:/SISLAB/STM32Cube_FW_WL_V1.3.0/Projects/NUCLEO-WL55JC/Demonstrations/LocalNetwork/LocalNetwork_Concentrator/Common/Src/demo_utils.c Application/Common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32WL55xx -DCORE_CM4 -DDEBUG -c -I../../Core/Inc -I../../SubGHz_Phy/App -I../../SubGHz_Phy/Target -I../../../LocalNetwork_Concentrator/Common/Inc -I../../../../../../../Drivers/STM32WLxx_HAL_Driver/Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32WLxx/Include -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy -I../../../../../../../Middlewares/Third_Party/SubGHz_Phy/stm32_radio_driver -I../../../../../../../Utilities/lpm/tiny_lpm -I../../../../../../../Utilities/misc -I../../../../../../../Utilities/sequencer -I../../../../../../../Utilities/timer -I../../../../../../../Utilities/trace/adv_trace -I../../../../../../../Drivers/BSP/STM32WLxx_Nucleo -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-2f-Common

clean-Application-2f-Common:
	-$(RM) ./Application/Common/demo_radio_utils.cyclo ./Application/Common/demo_radio_utils.d ./Application/Common/demo_radio_utils.o ./Application/Common/demo_radio_utils.su ./Application/Common/demo_regions.cyclo ./Application/Common/demo_regions.d ./Application/Common/demo_regions.o ./Application/Common/demo_regions.su ./Application/Common/demo_utils.cyclo ./Application/Common/demo_utils.d ./Application/Common/demo_utils.o ./Application/Common/demo_utils.su

.PHONY: clean-Application-2f-Common

