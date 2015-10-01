#include "graphics.h"


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
	/* Only works for fonts <= 8 bits in height */
	for (uint8_t i = 0; i < FONT_GLYPH_WIDTH; i++ ) {
    // need to use pgm_read_byte to access font data
    buffer.fb[x + (line * DISPLAY_WIDTH)] = font_data[ (((c - FONT_FIRST_ASCII) % FONT_LAST_ASCII) * (FONT_GLYPH_WIDTH)) + i  ];
    x++;
	}
}

void lcd_draw_string(uint8_t x, uint8_t line, char *str) {
	while (*str) {
		lcd_draw_char(x, line, *str++);
		x += (FONT_GLYPH_WIDTH + 1);
		if ((x + FONT_GLYPH_WIDTH + 1) >= DISPLAY_WIDTH) {
			x = 0; /* Ran out of this line */
			line++;
		}
		if (line >= (DISPLAY_HEIGHT / (FONT_GLYPH_HEIGHT + 1)))
			return; /* Ran out of space :( */
	}
}

void lcd_draw_point(uint8_t x, uint8_t y) {
  buffer.fb[x + (y << 3) * DISPLAY_WIDTH] |= ( 1 << (y % 8));
}
