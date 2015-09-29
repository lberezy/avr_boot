#ifndef SPI_HARDWARE_H
#define SPI_HARDWARE_H

#include <avr/io.h>


#define __SPI_PORT PORTB
#define __SPI_PIN PINB
#define __SPI_DDR DDRB

static const uint8_t __SPI_MOSI = PB3;
static const uint8_t __SPI_MISO = PB4;
static const uint8_t __SPI_SCK = PB5;
static const uint8_t __SPI_LSBFIRST_MASK = 0b00000001;
static const uint8_t __SPI_MASTER_MASK = 0b00000001;
static const uint8_t __SPI_MODE_MASK = 0b00000011;
static const uint8_t __SPI_SPEED_MASK = 0b00000011;
static const uint8_t __SPI_DBLCLK_MASK = 0b00000001;


#endif
