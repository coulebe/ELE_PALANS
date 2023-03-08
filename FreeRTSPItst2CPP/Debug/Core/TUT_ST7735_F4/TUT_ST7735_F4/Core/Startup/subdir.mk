################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Startup/startup_stm32f446retx.s 

OBJS += \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Startup/startup_stm32f446retx.o 

S_DEPS += \
./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Startup/startup_stm32f446retx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Startup/%.o: ../Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Startup/%.s Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m7 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-TUT_ST7735_F4-2f-TUT_ST7735_F4-2f-Core-2f-Startup

clean-Core-2f-TUT_ST7735_F4-2f-TUT_ST7735_F4-2f-Core-2f-Startup:
	-$(RM) ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Startup/startup_stm32f446retx.d ./Core/TUT_ST7735_F4/TUT_ST7735_F4/Core/Startup/startup_stm32f446retx.o

.PHONY: clean-Core-2f-TUT_ST7735_F4-2f-TUT_ST7735_F4-2f-Core-2f-Startup

