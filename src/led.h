#ifndef LED_H
#define LED_H

#include "HAL/board.h"

#define USER_LED_INIT()   do{USER_LED_DDR |= _BV(USER_LED_PIN);}while(0)
#define USER_LED_OFF()     do{USER_LED_PORT |= _BV(USER_LED_PIN);}while(0)
#define USER_LED_ON()    do{USER_LED_PORT &= ~_BV(USER_LED_PIN);}while(0)
#define USER_LED_TOGGLE() do{USER_LED_PORT ^= _BV(USER_LED_PIN);}while(0)

#endif
