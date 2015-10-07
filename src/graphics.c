#include "graphics.h"
#include <avr/pgmspace.h>

void swap(uint8_t* a, uint8_t* b)
{
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
}


void gfx_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
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
			gfx_draw_point(y0, x0);
		} else {
			gfx_draw_point(x0, y0);
		}
		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
}

void gfx_draw_char(uint8_t x, uint8_t line, char c)
{
  // check bounds
  if (x + FONT_GLYPH_WIDTH > DISPLAY_WIDTH  || line > DISPLAY_HEIGHT / 8) {
    return;
  }
  // check if character in font, else replace with space
  if (c > FONT_LAST_ASCII || c < FONT_FIRST_ASCII) {
    c = ' ';
  }
	/* Only works for fonts <= 8 bits in height */
	for (uint8_t i = 0; i < FONT_GLYPH_WIDTH; i++ ) {
    // need to use pgm_read_byte to access font data
    buffer.fb[x + (line * DISPLAY_WIDTH)] |= pgm_read_byte(&font_data[ (((c - FONT_FIRST_ASCII)) * (FONT_GLYPH_WIDTH)) + i  ]);
    x++;
	}
}

void gfx_draw_string(uint8_t x, uint8_t line, const char* str) {
  uint8_t cursor_x = x;
  uint8_t cursor_y = line;
  while(*str != '\0') {
    // Go to next line if character won't fit or newline character encountered
    if ((cursor_x + FONT_GLYPH_WIDTH) > DISPLAY_WIDTH || *str == '\n') {
      if (cursor_y + 1 <= (DISPLAY_HEIGHT / 8)) {
        cursor_y++;   //  move y cursor down one line
        cursor_x = 0; // reset x cursor to start of new line
      } else {
        return; // ran out of space for more characters on screen
      }
    }

    gfx_draw_char(cursor_x, cursor_y, *str);
    cursor_x += 1 + FONT_GLYPH_WIDTH; // increment cursor pos by width of character + 1 pixel
    str++; // increment string pointer
  }
}

void gfx_draw_point(uint8_t x, uint8_t y) {
  buffer.fb[x + (y / 8) * DISPLAY_WIDTH] |= ( 1 << (y % 8));
}
