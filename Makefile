OFFSET			= 0x700
DEVICE			= atmega8
CLOCK			 = 8000000
BAUD				= 9600
PROGRAMMER	= -c USBasp #-c stk500v2 -P avrdoper
FUSES			 = -U hfuse:w:0xd9:m -U lfuse:w:0x24:m
TARGET			= main


CC = avr-gcc
CFLAGS = -c -Wall -g -Os	-DF_CPU=$(CLOCK) -DBAUD=$(BAUD) -DOFFSET=$(OFFSET) -mmcu=$(DEVICE) -ffunction-sections -fdata-sections
LD = $(CC)
LDFLAGS = -Wl,--gc-sections #-Wl,--section-start=.foo=$(OFFSET)



OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)

$(info Building objects: $(OBJECTS))

all: $(TARGET).hex

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $^ $(LDFLAGS)

# You don't even need to be explicit here,
# compiling C files is handled automagically by Make.
%.o: %.c
				$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(TARGET).elf: $(OBJECTS)
				$(CC) $(LDFLAGS) -o $(TARGET).elf $(OBJECTS)

$(TARGET).hex: $(TARGET).elf
				rm -f $(TARGET).hex
				avr-objcopy -j .text -j .data  -O ihex $(TARGET).elf $(TARGET).hex
				avr-size --format=SysV  $(TARGET).elf

flash: all
				$(AVRDUDE) -U flash:w:$(TARGET).hex:i

fuse:
				$(AVRDUDE) $(FUSES)

clean:
				rm -f m$(TARGET) $(OBJECTS) $(TARGET).elf $(TARGET).hex
