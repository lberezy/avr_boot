#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#include "lcd.h"  // for display size constants

#define SD_BUFFER_SIZE 128

#define FRAME_BUFFER_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT / 8)

#define FLASH_BUFFER_SIZE 64
typedef union {
  uint8_t fb[FRAME_BUFFER_SIZE];
  uint8_t sd[SD_BUFFER_SIZE];
  uint8_t flash_page[FLASH_BUFFER_SIZE];
} buffer_t;

buffer_t buffer; // instantiate buffer in SRAM

#endif
