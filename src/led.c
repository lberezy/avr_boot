#include "led.h"

inline void led_init(void) {
  USER_LED_INIT();
  BACKLIGHT_LED_INIT();
  BACKLIGHT_LED_PWM_INIT();
}

inline void led_user_on(void) {
  USER_LED_ON();
}
inline void led_user_off(void) {
  USER_LED_OFF();
}
inline void led_user_toggle(void) {
  USER_LED_TOGGLE();
}

inline void led_backlight_on(void) {
  BACKLIGHT_LED_ON();
}

inline void led_backlight_off(void) {
  BACKLIGHT_LED_OFF();
}

inline void led_backlight_level(uint8_t level) {
  BACKLIGHT_PWM_LEVEL = level;
}
