#ifndef LED_H
#define LED_H

#include "HAL/board.h"
#include <avr/io.h>
#define USER_LED_INIT()   do{USER_LED_DDR  |=   _BV(USER_LED_PIN); USER_LED_PORT |= _BV(USER_LED_PIN);}while(0)
#define USER_LED_OFF()    do{USER_LED_PORT |=   _BV(USER_LED_PIN);}while(0)
#define USER_LED_ON()     do{USER_LED_PORT &=  ~_BV(USER_LED_PIN);}while(0)
#define USER_LED_TOGGLE() do{USER_LED_PORT ^=   _BV(USER_LED_PIN);}while(0)


#define BACKLIGHT_LED_INIT()    do{BACKLIGHT_LED_DDR  |=  _BV(BACKLIGHT_LED_PIN); BACKLIGHT_LED_PORT &= ~_BV(BACKLIGHT_LED_PIN);}while(0)
#define BACKLIGHT_LED_ON()      do{BACKLIGHT_LED_PORT |=  _BV(BACKLIGHT_LED_PIN);}while(0)
#define BACKLIGHT_LED_OFF()     do{BACKLIGHT_LED_PORT &= ~_BV(BACKLIGHT_LED_PIN);}while(0)
#define BACKLIGHT_LED_TOGGLE()  do{BACKLIGHT_LED_PORT ^=  _BV(BACKLIGHT_LED_PIN);}while(0)

#define BACKLIGHT_PWM_MODE      (_BV(WGM20) | _BV(WGM21))   // fast PWM
#define BACKLIGHT_PWM_OUTMODE   (_BV(COM21) | _BV(COM20))   // inverted output
#define BACKLIGHT_PWM_CLOCK     (_BV(CS20)) // F_CPU / 2
#define BACKLIGHT_PWM_LEVEL     OCR1B
#define BACKLIGHT_MAX           250
#define BACKLIGHT_FULL_MAX      255
#define BACKLIGHT_MIN           0
#define BACKLIGHT_INCREMENT     (BACKLIGHT_MAX / 10)
// initialise backlight and set to half brightness
#define BACKLIGHT_LED_PWM_INIT() do{OCR1AL = BACKLIGHT_MAX; TCCR1A |= _BV(COM1B1) | _BV(COM1B0) | _BV(WGM10); TCCR1B |= _BV(CS10) | _BV(WGM12);} while(0)

void led_init(void);
void led_user_on(void);
void led_user_off(void);
void led_user_toggle(void);
void led_backlight_on(void);
void led_backlight_off(void);
void led_backlight_on(void);
void led_backlight_level(uint8_t level);

#endif
