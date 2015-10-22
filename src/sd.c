#include "sd.h"
#include "graphics.h"
#include <stdio.h>
FATFS fs;


#define DEBUG
uint8_t sd_init(void) {
  //DSTATUS sd_status;
  FRESULT result;

  SD_PORT_INIT(); // from HAL/sd

  spi_setting_t spi_settings;
  spi_settings.endianness = SPI_MSB_FIRST;
  spi_settings.bus_mode = SPI_BUSMODE_MASTER;
  spi_settings.trans_mode = SPI_MODE_0;
  spi_settings.clock_rate = SPI_CLOCKDIV_64;
  spi_settings.double_clock =  SPI_DBLCLK_ENABLE;
  spi_init(&spi_settings); // spi clk ~ 250 kHz


  //sd_status = disk_initialize();
  result = pf_mount(&fs);

  spi_settings.clock_rate = SPI_CLOCKDIV_4;
  spi_settings.double_clock = SPI_DBLCLK_ENABLE;
  spi_init(&spi_settings);  // return to full speed spi

  //if (sd_status) {
  //  return SD_INIT_FAIL_INIT;
  //}
  // attempt to mount
  if (result) {
    return SD_INIT_FAIL_MOUNT;
  }
  return SD_INIT_SUCCESS;
}
