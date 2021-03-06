#include "fram.h"

#include "HAL/board.h"
#include "spi.h"
#include <util/delay.h>


#define FRAM_SEND_WRITE_EN() do { SPI_SCK_LOW(); FRAM_CS_ACTIVATE(); spi_send(FRAM_WRITE_ENABLE);} while(0)


void fram_init() {
  // initialise SPI in mode 0
  spi_setting_t spi_settings;
  spi_settings.endianness = SPI_MSB_FIRST;
  spi_settings.bus_mode = SPI_BUSMODE_MASTER;
  spi_settings.trans_mode = SPI_MODE_0;
  spi_settings.clock_rate = SPI_CLOCKDIV_4;
  spi_settings.double_clock =  SPI_DBLCLK_ENABLE;
  spi_init(&spi_settings); // spi clk (F_CPU / 2) ~= 4 MHz
  // initialise FRAM control pins
  FRAM_PORT_INIT();
  //_delay_ms(20); // ensure t_PU is satisfied

  uint8_t status = fram_read_status();
  // if lock bits are set, clear them
  if (status & (FRAM_STATUS_BP0 | FRAM_STATUS_BP1)) {
    FRAM_CS_ACTIVATE();
    spi_send(FRAM_WRITE_ENABLE);
    spi_send(FRAM_WRITE_STATUS);
    spi_send(0); // disable WPEN, BP1, BP0
    FRAM_CS_DEACTIVATE();
  }
}

uint8_t fram_read_byte(uint16_t addr) {
  uint8_t result;
  FRAM_CS_ACTIVATE();
  spi_send(FRAM_READ_MEMORY); // issue read opcode
  spi_send(addr >> 8);// & FRAM_MSB_MASK)); // send MSB of address
  spi_send(addr); // send LSB of address
  result = spi_send(FRAM_DUMMY_PACKET); // issue 8 clocks to recieve data on
  FRAM_CS_DEACTIVATE();
  return result;
}

void fram_read_n_bytes(uint16_t start_addr, uint16_t n, uint8_t* buff) {
  FRAM_CS_ACTIVATE();
  spi_send(FRAM_READ_MEMORY); // issue read opcode
  spi_send(start_addr >> 8); //& FRAM_MSB_MASK)); // send MSB of address
  spi_send(start_addr); //& 0xFF)); // send LSB of address
  for(uint16_t i = 0; i < n; i++) {
    buff[i] = spi_send(FRAM_DUMMY_PACKET); // issue 8 clocks to recieve data on
  }
  FRAM_CS_DEACTIVATE();
}

void fram_write_byte(uint16_t addr, uint8_t c) {
  //FRAM_SEND_WRITE_EN();
  //SPI_SCK_LOW(); // FRAM decides if SPI is operating in mode 0 if SCK starts low
  FRAM_CS_ACTIVATE();
  spi_send(FRAM_WRITE_ENABLE);
  FRAM_CS_DEACTIVATE();
  //_delay_us(100);

  FRAM_CS_ACTIVATE();
  spi_send(FRAM_WRITE_MEMORY); // issue write opcode
  spi_send(addr >> 8); //& FRAM_MSB_MASK)); // send MSB of address
  spi_send(addr); //& 0xFF)); // send LSB of address
  spi_send(c); // clock out data byte
  FRAM_CS_DEACTIVATE();
}

void fram_write_n_bytes(uint16_t start_addr, uint16_t n, uint8_t* buff) {
  FRAM_CS_ACTIVATE();
  spi_send(FRAM_WRITE_ENABLE);
  FRAM_CS_DEACTIVATE();

  FRAM_CS_ACTIVATE();
  spi_send(FRAM_WRITE_MEMORY); // issue write opcode
  spi_send(start_addr >> 8); //& FRAM_MSB_MASK)); // send MSB of address
  spi_send(start_addr); //& 0xFF)); // send LSB of address
  for(uint16_t i = 0; i < n; i++) {
    spi_send(buff[i]); // clock out data byte
  }
  FRAM_CS_DEACTIVATE();
}

void fram_clear_n_bytes(uint16_t start_addr, uint16_t n) {
  FRAM_CS_ACTIVATE();
  spi_send(FRAM_WRITE_ENABLE);
  FRAM_CS_DEACTIVATE();
  //_delay_us(100);

  FRAM_CS_ACTIVATE();
  spi_send(FRAM_WRITE_MEMORY); // issue write opcode
  spi_send(start_addr >> 8); //& FRAM_MSB_MASK)); // send MSB of address
  spi_send(start_addr); //& 0xFF)); // send LSB of address
  while(n-- > 0) {
    spi_send(0); // clock out data byte
  }
  FRAM_CS_DEACTIVATE();
}

uint8_t fram_read_status() {
  uint8_t result;
  FRAM_CS_ACTIVATE();
  spi_send(FRAM_READ_STATUS);
  result = spi_send(0);
  FRAM_CS_DEACTIVATE();
  return result;
}
