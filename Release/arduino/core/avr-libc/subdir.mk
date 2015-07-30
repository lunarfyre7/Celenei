################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Jake/Programs/arduino-1.5.5-r2/hardware/arduino/avr/cores/arduino/avr-libc/malloc.c \
C:/Users/Jake/Programs/arduino-1.5.5-r2/hardware/arduino/avr/cores/arduino/avr-libc/realloc.c 

C_DEPS += \
./arduino/malloc.c.d \
./arduino/realloc.c.d 

AR_OBJ += \
./arduino/malloc.c.o \
./arduino/realloc.c.o 


# Each subdirectory must supply rules for building sources it contributes
arduino/malloc.c.o: C:/Users/Jake/Programs/arduino-1.5.5-r2/hardware/arduino/avr/cores/arduino/avr-libc/malloc.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Users/Jake/Programs/arduino-1.5.5-r2/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155-r2 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\hardware\arduino\avr\cores\arduino" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\hardware\arduino\avr\variants\standard" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\hardware\arduino\avr\libraries\Wire" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\libraries\LiquidCrystal" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\libraries\LiquidCrystal\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '

arduino/realloc.c.o: C:/Users/Jake/Programs/arduino-1.5.5-r2/hardware/arduino/avr/cores/arduino/avr-libc/realloc.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"C:/Users/Jake/Programs/arduino-1.5.5-r2/hardware/tools/avr/bin/avr-gcc" -c -g -Os -ffunction-sections -fdata-sections -MMD -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=155-r2 -DARDUINO_AVR_UNO -DARDUINO_ARCH_AVR    -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\hardware\arduino\avr\cores\arduino" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\hardware\arduino\avr\variants\standard" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\hardware\arduino\avr\libraries\Wire" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\hardware\arduino\avr\libraries\Wire\utility" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\libraries\LiquidCrystal" -I"C:\Users\Jake\Programs\arduino-1.5.5-r2\libraries\LiquidCrystal\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"   -Wall
	@echo 'Finished building: $<'
	@echo ' '


