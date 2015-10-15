#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdio.h>

#define APP_BYTES_MAX 8192

void flash_app(char* path) __attribute__((section(".boot")));

#endif
