#ifndef SPI_HARDWARE_H
#define SPI_HARDWARE_H

#include <avr/io.h>


#define SPI_PORT  PORTB
#define SPI_PIN   PINB
#define SPI_DDR   DDRB

#define SPI_MOSI_PIN  PB5
#define SPI_MISO_PIN  PB6
#define SPI_SCK_PIN   PB7
#define SPI_LSBFIRST_MASK   0b00000001
#define SPI_MASTER_MASK     0b00000001
#define SPI_MODE_MASK       0b00000011
#define SPI_SPEED_MASK      0b00000011
#define SPI_DBLCLK_MASK     0b00000001

#define SPI_SCK_LOW()   (SPI_PORT &= ~(_BV(SPI_SCK_PIN)))
#define SPI_SCK_HIGH()  (SPI_PORT |= (_BV(SPI_SCK_PIN)))



#endif
