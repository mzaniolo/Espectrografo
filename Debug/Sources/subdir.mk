################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Flash.c \
../Sources/main.c \
../Sources/mcg_hal.c \
../Sources/util.c 

OBJS += \
./Sources/Flash.o \
./Sources/main.o \
./Sources/mcg_hal.o \
./Sources/util.o 

C_DEPS += \
./Sources/Flash.d \
./Sources/main.d \
./Sources/mcg_hal.d \
./Sources/util.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -D"CPU_MKL25Z128VLK4" -I"../Sources" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MKL25Z4/include" -I/opt/Freescale/SKD1.3/platform/drivers/inc -I/opt/Freescale/SKD1.3/platform/utilities/inc -I/opt/Freescale/SKD1.3/platform/system/inc -I/opt/Freescale/SKD1.3/platform/osa/inc -I/opt/Freescale/SKD1.3/platform/hal/inc -I"/opt/Freescale/SKD1.3/platform/utilities/inc" -I"/opt/Freescale/SKD1.3/platform/utilities/src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


