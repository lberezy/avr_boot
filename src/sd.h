#ifndef SD_H
#define SD_H

#include <string.h>

#include "pfatfs/diskio.h"
#include "pfatfs/pff.h"
#include "spi.h"

#include "graphics.h"

enum {
  SD_INIT_SUCCESS = 0,
  SD_INIT_FAILURE = 1
};

uint8_t sd_init(void);
FRESULT sd_scan_files (char* path);
#endif
