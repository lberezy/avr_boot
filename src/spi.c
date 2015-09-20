#include "spi.h"



//initialize the SPI bus
//  uint8_t lsbfirst - if 0: most significant bit is transmitted first
//  uint8_t master - if 1: use master mode, if 0: slave mode is used
//  uint8_t mode - sets the transfer mode:
//                 mode   leading clock edge   trailing clock edge
//                 -----------------------------------------------
//                 0      sample (rising)      setup  (falling)
//                 1      setup  (rising)      sample (falling)
//                 2      sample (falling)     setup  (rising)
//                 3      setup  (falling)     sample (rising)
//  uint8_t clkrate - spi bus clock rate, valid speeds are 0-3
//                    rate   speed
//                    ------------
//                    0      CPUCLK/4
//                    1      CPUCLK/16
//                    2      CPUCLK/64
//                    3      CPUCLK/128
//  uint8_t dblclk - if 1: doubles the SPI clock rate in master mode
//  EXAMPLE: spi_init(0, 1, 0, 3, 0)
void spi_init(spi_setting_t settings) {
  // enable pull-ups
  __SPI_PIN |= ((1 << __SPI_MISO));
  //set outputs
  __SPI_DDR |= ((1<<__SPI_MOSI) | (1<<__SPI_SCK));
  //set inputs
  __SPI_DDR &= ~(1<<__SPI_MISO);
  __SPI_PORT |= (1<<__SPI_MISO); //turn on pull-up resistor
  //set SPI control register
  SPCR = (
           (1<<SPE) | //enable SPI
           ((settings.endianness & __SPI_LSBFIRST_MASK)<<DORD) | //set msb/lsb ordering
           ((settings.bus_mode & __SPI_MASTER_MASK)<<MSTR) | //set master/slave mode
           ((settings.trans_mode & __SPI_MODE_MASK)<<CPHA) | //set mode
           (settings.clock_rate & __SPI_SPEED_MASK<<SPR0) //set speed
         );
  //set double speed bit
  SPSR = ((settings.double_clock  & __SPI_DBLCLK_MASK)<<SPI2X);
}

//shifts out 8 bits of data
//  uint8_t data - the data to be shifted out
//  returns uint8_t - the data received during sending
uint8_t spi_send(uint8_t value){
  uint8_t result;

  //shift the first byte of the value
  SPDR = value;
  //wait for the SPI bus to finish
  while(!(SPSR & (1<<SPIF)));
  //get the received data
  result = SPDR;

  return result;
}
