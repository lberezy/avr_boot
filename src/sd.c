#include "sd.h"
#include "graphics.h"
FATFS* fs;

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

  int count = 20;
  do {
    sd_status = disk_initialize();
  #ifdef DEBUG
    switch(sd_status) {
      case STA_NODISK:
        lcd_draw_string(1,1, "No disk");
        break;
      case STA_NOINIT:
        lcd_draw_string(1,1, "Not initialised");
        break;
      case (0x00):
        lcd_draw_string(1,1, "Initialised successfully");
        break;
      default:
        lcd_draw_string(1,1, "Initialisation error");
        break;
    }
    lcd_fill();
  #endif
  } while (!sd_status && count--);

  if (!sd_status || count == 0) {
  #ifdef DEBUG
    lcd_draw_string(1,1, "SD failure");
    lcd_fill();
  #endif
    return SD_INIT_FAILURE;
  }
  _delay_ms(200);
#if DEBUG
  lcd_draw_string(1,1, "Mounting");
  lcd_fill();
#endif
  _delay_ms(50);

  spi_settings.clock_rate = SPI_CLOCKDIV_4;
  spi_settings.double_clock =SPI_DBLCLK_ENABLE;
  spi_init(spi_settings);  // return to full speed spi

  /* Try to mount the SD card */
  count  = 20;  // mounting tries before failure
  do {
    fs_result = pf_mount(fs);
    switch(sd_status) {
    #ifdef DEBUG
      case FR_OK:
        lcd_draw_string(1,1, "Mount OK");
        break;
      case FR_NOT_READY:
        lcd_draw_string(1,1, "Not ready");
        break;
      case FR_DISK_ERR:
        lcd_draw_string(1,1, "Disk error");
        break;
      case FR_NO_FILESYSTEM:
        lcd_draw_string(1,1, "No FS");
        break;
      default:
        lcd_draw_string(1,1, "Mount error");
        break;
    }
    lcd_fill();
  #endif
    PORTD ^= 0xff;   // blink LED
    _delay_ms(10);
  } while (count-- > 0 && fs_result != FR_OK);

  _delay_ms(600);
  if (fs_result != FR_OK) {
  #ifdef DEBUG
    lcd_draw_string(1,1, "Mount failed.");
  #endif
    return SD_INIT_FAILURE;
  }
  #ifdef DEBUG
  lcd_draw_string(1,1, "Mount success!");
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
            //lcd_draw_string(1,1,fno.fname);
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
