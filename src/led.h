#ifndef LED_H
#define LED_H

#include "HAL/board.h"

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
#define BACKLIGHT_PWM_LEVEL     OCR2
// initialise backlight and set to half brightness
#define BACKLIGHT_LED_PWM_INIT() do{TCCR2 |= (BACKLIGHT_PWM_MODE | BACKLIGHT_PWM_OUTMODE | BACKLIGHT_PWM_CLOCK); BACKLIGHT_PWM_LEVEL = 196;} while(0)

void led_init(void);
void led_user_on(void);
void led_user_off(void);
void led_user_toggle(void);
void led_backlight_on(void);
void led_backlight_off(void);
void led_backlight_on(void);
void led_backlight_level(uint8_t level);

#endif
