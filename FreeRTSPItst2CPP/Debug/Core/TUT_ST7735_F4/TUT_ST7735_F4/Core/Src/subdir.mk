################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/GFX_FUNCTIONS.c \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/ST7735.c \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/fonts.c \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/main.c \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_hal_msp.c \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_it.c \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/syscalls.c \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/sysmem.c \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/GFX_FUNCTIONS.o \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/ST7735.o \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/fonts.o \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/main.o \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_hal_msp.o \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_it.o \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/syscalls.o \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/sysmem.o \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/GFX_FUNCTIONS.d \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/ST7735.d \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/fonts.d \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/main.d \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_hal_msp.d \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_it.d \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/syscalls.d \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/sysmem.d \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/%.o Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/%.su: ../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/%.c Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-TUT_ST7735_F4-2f-TUT_ST7735_F4-2f-Core-2f-Src

clean-Core-2f-TUT_ST7735_F4-2f-TUT_ST7735_F4-2f-Core-2f-Src:
	-$(RM) ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/GFX_FUNCTIONS.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/GFX_FUNCTIONS.o ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/GFX_FUNCTIONS.su ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/ST7735.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/ST7735.o ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/ST7735.su ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/fonts.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/fonts.o ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/fonts.su ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/main.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/main.o ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/main.su ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_hal_msp.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_hal_msp.o ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_hal_msp.su ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_it.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_it.o ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/stm32f4xx_it.su ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/syscalls.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/syscalls.o ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/syscalls.su ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/sysmem.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/sysmem.o ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/sysmem.su ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/system_stm32f4xx.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/system_stm32f4xx.o ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-TUT_ST7735_F4-2f-TUT_ST7735_F4-2f-Core-2f-Src

