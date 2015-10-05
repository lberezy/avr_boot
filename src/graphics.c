#include "graphics.h"
#include <avr/pgmspace.h>

void swap(uint8_t* a, uint8_t* b)
{
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}

void lcd_draw_term(terminal_t* term) {
  // todo: handle \n
  uint8_t max_rows = term->rows;
  uint8_t cursor_current_col = term->cursor_y;
  for(uint8_t y = 0; y < term->rows; y++) {
      for (uint8_t x = 0; x < term->cols; x++) {
        lcd_draw_char(x * FONT_GLYPH_WIDTH, (cursor_current_col + y) % max_rows, (term->buffer)[x + (cursor_current_col + y) % max_rows * max_rows]);
      }
  }
}

void lcd_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
	uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
	uint8_t dx, dy;
	int8_t err;
	int8_t ystep;

	if (steep) {
		swap(&x0, &y0);
		swap(&x1, &y1);
	}

	if (x0 > x1) {
		swap(&x0, &x1);
		swap(&y0, &y1);
	}


	dx = x1 - x0;
	dy = abs(y1 - y0);

	err = dx / 2;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0<=x1; x0++) {
		if (steep) {
			lcd_draw_point(y0, x0);
		} else {
			lcd_draw_point(x0, y0);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void lcd_draw_char(uint8_t x, uint8_t line, char c)
{
  if (x + FONT_GLYPH_WIDTH > DISPLAY_WIDTH  || line > DISPLAY_HEIGHT / 8) {
    return;
  }
	/* Only works for fonts <= 8 bits in height */
	for (uint8_t i = 0; i < FONT_GLYPH_WIDTH; i++ ) {
    // need to use pgm_read_byte to access font data
    buffer.fb[x + (line * DISPLAY_WIDTH)] = pgm_read_byte(&font_data[ (((c - FONT_FIRST_ASCII)) * (FONT_GLYPH_WIDTH)) + i  ]);
    x++;
	}
}
#include "led.h"``
void gfx_draw_string(uint8_t x, uint8_t line, const char* str) {
  uint8_t cursor_x = x;
  uint8_t cursor_y = line;
  while(*str != '\0') {
    // test if character will fit, if not, wrap to next line
    if ((cursor_x + FONT_GLYPH_WIDTH) > DISPLAY_WIDTH) {
      if (cursor_y + 1 <= (DISPLAY_HEIGHT / 8)) {
        cursor_y++;   //  move y cursor down one line
        cursor_x = 0; // reset x cursor to start of new line
      }
    }

    lcd_draw_char(cursor_x, cursor_y, *str);
    cursor_x += 1 + FONT_GLYPH_WIDTH; // increment cursor pos by width of character + 1 pixel
    str++; // increment string pointer
  }
}
void lcd_draw_string(uint8_t x, uint8_t line, char *str) {
  const uint8_t space_width = 1;
  uint8_t str_pos = 0;
  uint8_t x_pos = x;
  uint8_t y_pos = line;
	while (str[str_pos] != '\0') {
    if ((x_pos + FONT_GLYPH_WIDTH + space_width) >= DISPLAY_WIDTH) {
      x_pos = 0; /* Ran out of this line */
      y_pos++;
    }
    if (y_pos >= (DISPLAY_HEIGHT / (FONT_GLYPH_HEIGHT)))
      return; /* Ran out of space :( */
  }
		lcd_draw_char(x_pos, y_pos, str[str_pos]);
		x_pos += (FONT_GLYPH_WIDTH + space_width); // incremement cursor
    str_pos++;
}

void lcd_draw_point(uint8_t x, uint8_t y) {
  buffer.fb[x + (y / 8) * DISPLAY_WIDTH] |= ( 1 << (y % 8));
}
