#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>
volatile uint32_t global_tick;


void systick_init();
#endif
