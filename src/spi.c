#include "spi.h"
#include "led.h"

//initialize the SPI bus
void spi_init(spi_setting_t* settings) {

  //set outputs
  SPI_DDR |= (_BV(SPI_MOSI_PIN) | _BV(SPI_SCK_PIN));
  SPI_DDR &= ~(_BV(SPI_MISO_PIN));
  // enable pull-ups
  SPI_PIN |= (_BV(SPI_MISO_PIN));
  //set inputs
  SPI_DDR &= ~_BV(SPI_MISO_PIN);
  SPI_PORT |= _BV(SPI_MISO_PIN); //turn on pull-up resistor
  //set SPI control register
  SPCR = (
           _BV(SPE) | //enable SPI
           ((settings->endianness & SPI_LSBFIRST_MASK) << DORD) | //set msb/lsb ordering
           ((settings->bus_mode & SPI_MASTER_MASK) << MSTR) | //set master/slave mode
           ((settings->trans_mode & SPI_MODE_MASK) << CPHA) | //set mode
           (settings->clock_rate & SPI_SPEED_MASK << SPR0) //set speed
         );
  //set double speed bit
  SPSR = ((settings->double_clock  & SPI_DBLCLK_MASK) << SPI2X);
}

//shifts out 8 bits of data
uint8_t spi_send(uint8_t value){
  //shift the first byte of the value
  SPDR = value;
  //wait for the SPI bus to finish
  while(!(SPSR & _BV(SPIF))) {
    // busy loop
  };
  //get the received data
  return SPDR;
}
