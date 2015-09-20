#ifndef _BUFFER_H
#define _BUFFER_H

#include <stdint.h>

#define FRAME_BUFFER_SIZE 816
#define SD_BUFFER_SIZE 128
#define FLASH_BUFFER_SIZE 64
typedef union {
  uint8_t fb[FRAME_BUFFER_SIZE];
  uint8_t sd[SD_BUFFER_SIZE];
  uint8_t flash_page[FLASH_BUFFER_SIZE];
} buffer_t;
#endif
