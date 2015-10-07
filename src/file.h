#ifndef FILE_H
#define FILE_H

#include "sd.h"

FRESULT sd_scan_files (char* path);

uint8_t dir_list(char* path);
#endif
