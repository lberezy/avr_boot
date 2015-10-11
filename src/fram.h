#ifndef FRAM_H
#define FRAM_H

#include <stdint.h>

void fram_init();

uint8_t fram_read_byte(uint16_t addr);
void fram_write_byte(uint16_t addr, uint8_t c);

void fram_read_n_byte(uint16_t start_addr, uint16_t n, uint8_t* buff);
void fram_write_n_byte(uint16_t start_addr, uint16_t n, uint8_t* buff);

uint8_t fram_read_status();

#endif
