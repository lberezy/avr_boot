#ifndef _SPI_H
#define _SPI_H

#include <stdint.h>
#include <avr/io.h>
#include "HAL/board.h"


typedef enum {
  SPI_LSB_FIRST = 1,
  SPI_MSB_FIRST = 0
} spi_endianness_t;
typedef enum {
  SPI_BUSMODE_SLAVE = 0,
  SPI_BUSMODE_MASTER = 1,
} spi_bus_mode_t;
typedef enum {
  SPI_MODE_0 = 0,
  SPI_MODE_1 = 1,
  SPI_MODE_2 = 2,
  SPI_MODE_3 = 3,
} spi_trans_mode_t;
typedef enum {
  SPI_CLOCKDIV_4 = 0,
  SPI_CLOCKDIV_16 = 1,
  SPI_CLOCKDIV_64 = 2,
  SPI_CLOCKDIV_128 = 3,
} spi_clock_rate_t;
typedef enum  {
  SPI_DBLCLK_DISABLE = 0,
  SPI_DBLCLK_ENABLE = 1,
} spi_double_clock_t;

typedef
union {
  struct __attribute__ ((packed)) {
    spi_endianness_t endianness : 1;
    spi_bus_mode_t bus_mode : 1;
    spi_trans_mode_t trans_mode : 2;
    spi_clock_rate_t clock_rate : 2;
    spi_double_clock_t double_clock : 1;
  };
  uint8_t intRep;
} spi_setting_t;

void spi_init(spi_setting_t* settings);

uint8_t spi_send(uint8_t value);

#endif
