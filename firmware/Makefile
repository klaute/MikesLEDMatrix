# Name: Makefile
# Project: hid-mouse example
# Author: Christian Starkjohann
# Creation Date: 2008-04-07
# Tabsize: 4
# Copyright: (c) 2008 by OBJECTIVE DEVELOPMENT Software GmbH
# License: GNU GPL v2 (see License.txt), GNU GPL v3 or proprietary (CommercialLicense.txt)
# This Revision: $Id: Makefile 692 2008-11-07 15:07:40Z cs $

#DEVICE  = atmega8
DEVICE  = atmega32
F_CPU   = 16000000	# in Hz
FUSE_L  = # see below for fuse values for particular devices
FUSE_H  =
#AVRDUDE = avrdude -c avrisp2 -p $(DEVICE) -P /dev/ttyUSB0 # edit this line for your programmer
AVRDUDE = avrdude -c usbasp -p $(DEVICE) # edit this line for your programmer

CFLAGS  = -Iusbdrv
CFLAGS += -I.
CFLAGS += -I/home/klaute/dev/avrlib
CFLAGS += -DDEBUG_LEVEL=0
CFLAGS += -MD -MP -MF .dep/$(@F).d
#OBJECTS = main.o ledcube.o block0.o animations.o ab.o rotation.o translation.o equalizer.o usbdrv/usbdrv.o usbdrv/usbdrvasm.o
OBJECTS = main.o ledcube.o blockeq.o equalizer.o usbdrv/usbdrv.o usbdrv/usbdrvasm.o

COMPILE  = avr-gcc
COMPILE += -Wall
COMPILE += -Os
COMPILE += -DF_CPU=$(F_CPU)
COMPILE += $(CFLAGS)
COMPILE += -mmcu=$(DEVICE)
COMPILE += -funsigned-char
COMPILE += -funsigned-bitfields
COMPILE += -fpack-struct
COMPILE += -fshort-enums
COMPILE += -fgnu89-inline
COMPILE += -Wstrict-prototypes
#COMPILE += -mint8
COMPILE += -mtiny-stack
COMPILE += -mcall-prologues
COMPILE += -mno-tablejump
#COMPILE += -Wa,-adhlns=$(<:.c=.lst)

AVRSIZE = avr-size

all: program 
#writeeep

# symbolic targets:
help:
	@echo "This Makefile has no default rule. Use one of the following:"
	@echo "make hex ....... to build main.hex"
	@echo "make program ... to flash firmware"
	@echo "make flash ..... to flash the firmware (use this on metaboard)"
	@echo "make clean ..... to delete objects and hex file"
	@echo "To flash fuses, have a look at the included USBasploader Makefile."

hex: main.hex

program: clean hex flash

# rule for uploading firmware:
flash: main.hex
	$(AVRDUDE) -e
	$(AVRDUDE) -U flash:w:main.hex:i

# rule for deleting dependent files (those which can be built by Make):
clean:
	rm -f main.hex main.lst main.obj main.cof main.list main.map main.eep.hex main.elf *.o usbdrv/*.o main.s usbdrv/usbdrv.s

# Generic rule for compiling C files:
.c.o:
	$(COMPILE) -c $< -o $@

# Generic rule for assembling Assembler source files:
.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

# Generic rule for compiling C to assembler, used for debugging only.
.c.s:
	$(COMPILE) -S $< -o $@

# file targets:

main.elf: usbdrv $(OBJECTS)	# usbdrv dependency only needed because we copy it
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex main.eep.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	$(AVRSIZE) --target=ihex main.hex
	$(AVRSIZE) --mcu=atmega32 -C main.elf
	$(AVRSIZE) -x *.o

# debugging targets:

disasm:	main.elf
	avr-objdump -d main.elf

cpp:
	$(COMPILE) -E main.c

readeep:
	$(AVRDUDE) -U eeprom:r:eep.hex:i

writeeep:
	$(AVRDUDE) -U eeprom:w:eep.hex:i

