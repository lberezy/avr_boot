#ifndef _SPI_H
#define _SPI_H

#include <stdint.h>

#define __SPI_PORT PORTB
#define __SPI_DDR DDRB




void spi_init(uint8_t lsbfirst,
              uint8_t master,
              uint8_t mode,
              uint8_t clkrate,
              uint8_t dblclk);

uint8_t spi_send(uint8_t value);

#endif
