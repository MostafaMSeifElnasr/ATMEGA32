################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_program.c \
../CLCD2_program.c \
../DC_program.c \
../DIO_program.c \
../Delay_program.c \
../EEPROM_program.c \
../GIE_program.c \
../LED_program.c \
../PWM_program.c \
../TWI_program.c \
../Timer_program.c \
../USART_program.c \
../main.c 

OBJS += \
./ADC_program.o \
./CLCD2_program.o \
./DC_program.o \
./DIO_program.o \
./Delay_program.o \
./EEPROM_program.o \
./GIE_program.o \
./LED_program.o \
./PWM_program.o \
./TWI_program.o \
./Timer_program.o \
./USART_program.o \
./main.o 

C_DEPS += \
./ADC_program.d \
./CLCD2_program.d \
./DC_program.d \
./DIO_program.d \
./Delay_program.d \
./EEPROM_program.d \
./GIE_program.d \
./LED_program.d \
./PWM_program.d \
./TWI_program.d \
./Timer_program.d \
./USART_program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


