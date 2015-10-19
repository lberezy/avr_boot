#include "sd.h"
#include "graphics.h"
#include <stdio.h>
FATFS fs;


#define DEBUG
uint8_t sd_init(void) {
  DSTATUS sd_status;
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


/*FRESULT sd_scan_files (char* path) {
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int j;
  /*  res = pf_opendir(&dir, path);
    if (res == FR_OK) {
      i = strlen(path);
        for (;;) {
            res = pf_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;
            if (fno.fattrib & AM_DIR) {
              putchar('/');
              fputs(fno.fname, stdout);
              res = scan_files(path);
              if (res != FR_OK) break;
              path[i] = 0;
            } else {
              fputs(path, stdout);
              putchar('/');
              puts(fno.fname);
            }
            term_draw(term_redirected);
            lcd_fill();
            lcd_clear_buffer();
        }*
    }
    return res;
}*/
