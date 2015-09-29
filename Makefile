##########------------------------------------------------------##########
##########              Project-specific Details                ##########
##########    Check these every time you start a new project    ##########
##########------------------------------------------------------##########

MCU   = atmega16
F_CPU = 8000000UL
BAUD  = 9600UL
## Also try BAUD = 19200 or 38400 if you're feeling lucky.

BOOTSTART = 0x1800
LIBRARYSTART =0x0AF6 # 8k - 5k

SRCDIR = src
OBJDIR = obj

## A directory for common include files and the simple USART library.
## If you move either the current folder or the Library folder, you'll
##  need to change this path to match.
LIBDIR = lib


##########------------------------------------------------------##########
##########                 Programmer Defaults                  ##########
##########          Set up once, then forget about it           ##########
##########        (Can override.  See bottom of file.)          ##########
##########------------------------------------------------------##########

PROGRAMMER_TYPE = jtag1
# extra arguments to avrdude: baud rate, chip type, -F flag, etc.
PROGRAMMER_ARGS = -P /dev/tty.usbserial-A104BYXE

##########------------------------------------------------------##########
##########                  Program Locations                   ##########
##########     Won't need to change if they're in your PATH     ##########
##########------------------------------------------------------##########

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRSIZE = avr-size
AVRDUDE = avrdude

##########------------------------------------------------------##########
##########                   Makefile Magic!                    ##########
##########         Summary:                                     ##########
##########             We want a .hex file                      ##########
##########        Compile source files into .elf                ##########
##########        Convert .elf file into .hex                   ##########
##########        You shouldn't need to edit below.             ##########
##########------------------------------------------------------##########

## The name of your project (without the .c)
# TARGET = blinkLED
## Or name it automatically after the enclosing directory
TARGET = bootloader
LINK_SCRIPT = ld_script_boot.x

# Object files: will find all .c/.h files in current directory
#  and in LIBDIR.  If you have any other (sub-)directories with code,
#  you can add them in to SOURCES below in the wildcard statement.
# SOURCES=$(wildcard $(SRCDIR)/*.c )
SOURCES:=$(wildcard src/*.c)
SOURCES+=$(wildcard src/*/*.c)
# SOURCES := $(shell find $(SOURCEDIR) --name '*.c')
OBJECTS=$(patsubst src/%.c,obj/%.o,$(SOURCES))
HEADERS=$(SOURCES:.c=.h)

## Compilation options, type man avr-gcc if you're curious.
CPPFLAGS = -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -I. -I$(LIBDIR) -MP -MD
CFLAGS = -Os -std=gnu99 -Wall
CFLAGS += -DDEBUG
## Use short (8-bit) data types
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -fms-extensions
## Splits up object files per function
CFLAGS += -ffunction-sections -fdata-sections
LDFLAGS = -Wl,-Map,$(TARGET).map,--cref
## Optional, but often ends up with smaller code
## LDFLAGS += -Wl,--gc-sections
## Relax shrinks code even more, but makes disassembly messy
LDFLAGS += -Wl,--relax

## LDFLAGS += -Wl,--section-start=.text=$(BOOTSTART)
## LDFLAGS += -Wl,-Ttext=$(BOOTSTART)
## LDFLAGS += -Wl,--section-start=.library=$(LIBRARYSTART)
LDFLAGS += -T $(LINK_SCRIPT)

## LDFLAGS += -Wl,-u,vfprintf -lprintf_flt -lm  ## for floating-point printf
## LDFLAGS += -Wl,-u,vfprintf -lprintf_min      ## for smaller printf
TARGET_ARCH = -mmcu=$(MCU)

-include $(SRC:.c=.d)

all: $(TARGET).hex


$(OBJECTS): | $(OBJDIR)

$(OBJDIR):
		find "$(SRCDIR)" -type d | sed -e "s?$(SRCDIR)?$(OBJDIR)?" | xargs mkdir -p

## Explicit pattern rules:
##  To make .o files from .c files
obj/%.o: src/%.c # src/$(HEADERS)
	@echo "Making: " $@
	 $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<;

$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

%.hex: %.elf
	 $(OBJCOPY)  -O ihex $< $@

%.eeprom: %.elf
	$(OBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@

%.lst: %.elf
	$(OBJDUMP) -S $< > $@

## These targets don't have files named after them
.PHONY: all disassemble disasm eeprom size clean squeaky_clean flash fuses symbols library


debug:
	@echo $(TARGET)
	@echo "Source files:"   $(SOURCES)
	@echo "Headers:" $(HEADERS)
	@echo "Objects:" $(OBJECTS)
	@echo "MCU, F_CPU, BAUD:"  $(MCU), $(F_CPU), $(BAUD)
	@echo

symbols: $(TARGET).elf
	$(OBJCOPY) --wildcard --strip-symbol=main --strip-symbol="_*" $(TARGET).elf $(TARGET).syms

library: $(OBJECTS)
	avr-ar rcs lib$(TARGET).a $(OBJECTS)
# Optionally create listing file from .elf
# This creates approximate assembly-language equivalent of your code.
# Useful for debugging time-sensitive bits,
# or making sure the compiler does what you want.
disassemble: $(TARGET).lst

disasm: disassemble

# Optionally show how big the resulting program is
size:  $(TARGET).elf
	$(AVRSIZE) --format=SysV $(TARGET).elf

clean:
	find . -name "*.o" -type f -delete
	find . -name "*.hex" -type f -delete
	find . -name "*.elf" -type f -delete
	find . -name "*.d" -type f -delete
	find . -name "*.map" -type f -delete
	find . -name "*.syms" -type f -delete
	find . -name "*.a" -type f -delete

squeaky_clean: | clean
	rm -rf obj

##########------------------------------------------------------##########
##########              Programmer-specific details             ##########
##########           Flashing code to AVR using avrdude         ##########
##########------------------------------------------------------##########

flash: $(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

## An alias
program: flash

flash_eeprom: $(TARGET).eeprom
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U eeprom:w:$<

avrdude_terminal:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -nt

##########------------------------------------------------------##########
##########       Fuse settings 													        ##########
##########------------------------------------------------------##########

# For computing fuse byte values for other devices and options see
# the fuse bit calculator at http://www.engbedded.com/fusecalc/
## LFUSE = 0x64
LFUSE = 0xE4
#0x24 - now with no brownout
## HFUSE = 0xd8
HFUSE = 0x98
#0xd9 - moved BOOTRST
##EFUSE = 0x00
EFUSE = 0x07
## avrdude reads back unimplemented bits as 0, causes error for 0xff
## Generic -U efuse:w:$(EFUSE):m
FUSE_STRING = -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m

fuses:
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) $(FUSE_STRING)
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -nv
