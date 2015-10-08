#include "sd.h"
#include "graphics.h"
FATFS* fs;
#define DEBUG
uint8_t sd_init(void) {
  DSTATUS sd_status;
  FRESULT fs_result;
  spi_setting_t spi_settings;
  spi_settings.endianness = SPI_MSB_FIRST;
  spi_settings.bus_mode = SPI_BUSMODE_MASTER;
  spi_settings.trans_mode = SPI_MODE_0;
  spi_settings.clock_rate = SPI_CLOCKDIV_64;
  spi_settings.double_clock =  SPI_DBLCLK_ENABLE;
  spi_init(spi_settings); // spi clk ~ 250 kHz

	SD_PORT_INIT(); // from HAL/sd

  int count = 20;
  do {
    sd_status = disk_initialize();
  #ifdef DEBUG
    if (sd_status & STA_NODISK) {
      term_puts_P(term_redirected, PSTR("ND"));
      //gfx_draw_string(0,1, "ND");
    }
    if (sd_status & STA_NOINIT) {
      //gfx_draw_string(40,1, "NOINIT");
      term_puts_P(term_redirected, PSTR("NOINIT"));
    }
    lcd_fill();
  #endif
} while (!sd_status  && count--);

  /*if (!sd_status) {
  #ifdef DEBUG
    gfx_draw_string(0,2, "SD failure");
    lcd_fill();
  #endif
    return SD_INIT_FAILURE;
  }*/
  //_delay_ms(200);
#ifdef DEBUG
  //gfx_draw_string(0,3, "Mounting");
  term_puts_P(term_redirected, PSTR("Mounting"));
  lcd_fill();
#endif
  //_delay_ms(50);

  spi_settings.clock_rate = SPI_CLOCKDIV_4;
  spi_settings.double_clock = SPI_DBLCLK_ENABLE;
  spi_init(spi_settings);  // return to full speed spi

  /* Try to mount the SD card */
  count  = 20;  // mounting tries before failure
  do {
    fs_result = pf_mount(fs);
    #ifdef DEBUG
    switch(sd_status) {
      case FR_OK:
        //gfx_draw_string(0,4, "Mount OK");
        term_puts_P(term_redirected, PSTR("Mount OK"));

        break;
      case FR_NOT_READY:
        //gfx_draw_string(0,4, "Not ready");
        term_puts_P(term_redirected, PSTR("Not Ready"));

        break;
      case FR_DISK_ERR:
        //gfx_draw_string(0,4, "Disk error");
        term_puts_P(term_redirected, PSTR("Disk Err."));

        break;
      case FR_NO_FILESYSTEM:
        //gfx_draw_string(0,4, "No FS");
        term_puts_P(term_redirected, PSTR("No FS"));

        break;
      default:
        //gfx_draw_string(0,4, "Mount error");
        break;
    }
    lcd_fill();
  #endif
    //_delay_ms(10);
  } while ((count-- > 0) && fs_result != FR_OK);

  //_delay_ms(600);
  if (fs_result != FR_OK) {
  #ifdef DEBUG
    //gfx_draw_string(0,5, "Mount failed.");
    term_puts_P(term_redirected, PSTR("Mount Failed"));

  #endif
    return SD_INIT_FAILURE;
  }
  #ifdef DEBUG
  //gfx_draw_string(0,5, "Mount success!");
  term_puts_P(term_redirected, PSTR("Mount success!"));

  lcd_fill();
  #endif
  return SD_INIT_SUCCESS;
}
/*
FRESULT sd_scan_files (char* path) {
    FRESULT res;
    FILINFO fno;
    DIR dir;
    int j;
    res = pf_opendir(&dir, path);
    if (res == FR_OK) {

        for (;;) {
            res = pf_readdir(&dir, &fno);
            if (res != FR_OK || fno.fname[0] == 0) break;
            lcd_putchar((fno.fattrib & AM_DIR) ? 'D' : 'F');
            lcd_putchar(' ');
            j = 0;
            while ((path[j++]) != '\0') {
              lcd_putchar(path[j]);
            }
            lcd_putchar('/');
            //gfx_draw_string(1,1,fno.fname);
            while ((fno.fname[j++]) != '\0') {
              lcd_putchar(fno.fname[j]);
            }
            lcd_fill();
            //putchar('\n');
            //printf("[%c]%s/%s\n", (fno.fattrib & AM_DIR) ? 'D' : 'F', path, fno.fname);
        }
    }
    return res;
}
*/
