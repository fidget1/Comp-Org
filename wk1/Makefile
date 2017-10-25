# Project name
#SOURCE          = main.c
#ADDITIONAL      = 
# Get base name so we can create .elf file
#NAME            = $(basename $(SOURCE))
# MSP430 MCU to compile for
#CPU             = msp430g2553
# Optimisation level
#OPTIMIZATION    = -O0
# Extra variables
#CFLAGS          = -mmcu=$(CPU) $(OPTIMIZATION) -std=c99 -Wall -g -fomit-frame-pointer

# Build and link executable
$(NAME).elf: $(SOURCE) $(ADDITIONAL)
	gcc -o conv main.c conv.c conv.h;
#	msp430-gcc $(CFLAGS) -o $@ $(SOURCE) $(ADDITIONAL)
#	msp430-objdump -D $(NAME).elf > $(NAME).hex
