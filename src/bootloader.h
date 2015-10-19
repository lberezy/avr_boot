#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdio.h>

#include "config.h"

void flash_app(char* path) __attribute__((section(".boot")));

#endif
