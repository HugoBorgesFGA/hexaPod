################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fsm_timerB.c \
../global.c \
../init.c \
../interrupcoes.c \
../main.c \
../ordenacao.c 

OBJS += \
./fsm_timerB.o \
./global.o \
./init.o \
./interrupcoes.o \
./main.o \
./ordenacao.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 C Compiler'
	C:\msp-toolchain\bin\msp430-gcc -O0 -g -Wall -mmcu=msp430g2553 -std=gnu89 -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


