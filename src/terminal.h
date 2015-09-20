#ifndef _TERMINAL_H
#define _TERMINAL_H

typedef struct {
  uint8_t scroll_x;
  uint8_t rows;
  uint8_t cols;
  uint8_t cursor_x;
  uint8_t cursor_y;
  char* buffer;
} terminal_t;

terminal_t term_init(uint8_t width, uint8_t height);

void term_putchar(terminal_t* term, char c);

#endif
