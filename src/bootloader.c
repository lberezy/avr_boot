#include "bootloader.h"

#include <stdint.h>

#include <avr/boot.h>
#include <util/atomic.h>
#include "buffer.h"
#include "pfatfs/pff.h"
#include "led.h"
#include <stdio.h>
#include "terminal.h"

void flash_app(char* path) {
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    FRESULT result = pf_open(path);
    if (result == FR_OK) {
      puts_P(PSTR("Open OK"));
    } else if(result == FR_NO_FILE) {
      puts_P(PSTR("NOFILE"));
    } else if(result == FR_DISK_ERR) {
      puts_P(PSTR("DISK ERR"));
    } else if(result == FR_NOT_ENABLED) {
      puts_P(PSTR("NOT MOUNTED"));
    } else {
      puts_P(PSTR("OPEN ERROR"));
    }
    uint8_t flash_page = 0;
    uint8_t bytes_read = 0;
    uint16_t total_bytes = 0;
    do {
      // fill buffer from file
      pf_read(buffer.sd, SD_BUFFER_SIZE, &bytes_read);
      uint8_t bytes_remaining = bytes_read;
      uint8_t processed_segment = 0;
      // process portions of file buffer into flash buffer and write flash buffer
      uint8_t buff_pt = 0;
      do {
        // take SPM_PAGESIZE or remaining bytes from buffer
        for (uint8_t i = 0; i < SPM_PAGESIZE && (bytes_remaining >= 2); i += 2) {
          bytes_remaining -= 2;
          // fill buffer with word
          uint16_t w = buffer.sd[buff_pt++];
          w += (buffer.sd[buff_pt++]) << 8;
          boot_page_fill ((flash_page * SPM_PAGESIZE) + i, w);
          total_bytes += 2;
          USER_LED_TOGGLE();
        }
        boot_page_write(flash_page * SPM_PAGESIZE);
        boot_spm_busy_wait();
        flash_page++;
      } while(bytes_remaining);
    } while (bytes_read == SD_BUFFER_SIZE && (total_bytes <= APP_BYTES_MAX));
    boot_rww_enable();  // enable jumping to flashed application
  }
}
