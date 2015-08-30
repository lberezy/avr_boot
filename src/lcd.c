#include "lcd.h"




#define LCD_PORT PORTB
#define LCD_DDR DDRB

#define LCD_RST_PIN PB0
#define LCD_CE_PIN PB6
#define LCD_DC_PIN PB1
#define LCD_BACKLIGHT_PIN PB4

#define LCD_CE_ACTIVATE() (LCD_PORT &= ~(_BV(LCD_CE_PIN))) /* active low */
#define LCD_CE_DEACTIVATE() (LCD_PORT |= _BV(LCD_CE_PIN))
#define LCD_DC_DATA() (LCD_PORT |= _BV(LCD_DC_PIN))
#define LCD_DC_COMM() (LCD_PORT &= ~(_BV(LCD_DC_PIN)))
#define LCD_RST_ACTIVATE() (LCD_PORT &= ~(_BV(LCD_RST_PIN)))
#define LCD_RST_DEACTIVATE() (LCD_PORT |= _BV(LCD_RST_PIN))

#define LCD_BACKLIGHT_ACTIVATE() (LCD_PORT |= _BV(LCD_BACKLIGHT_PIN))
#define LCD_BACKLIGHT_DEACTIVATE() (LCD_PORT &= ~(_BV(LCD_BACKLIGHT_PIN)))
#define LCD_PORT_INIT() (LCD_DDR |= _BV(LCD_RST_PIN) | _BV(LCD_CE_PIN) | _BV(LCD_DC_PIN) | _BV(LCD_BACKLIGHT_PIN))

uint8_t fb[PCD8544_MAX_BANKS * PCD8544_MAX_COLS];

void lcd_command(char c) {
  LCD_DC_COMM();
  LCD_CE_ACTIVATE();
  spi_send(c);
  LCD_CE_DEACTIVATE();
}

void lcd_data(char c) {
  LCD_DC_DATA();
  LCD_CE_ACTIVATE();
  spi_send(c);
  LCD_CE_DEACTIVATE();
}

void lcd_init(void) {
  LCD_PORT_INIT();PORTD ^= 0x01;
  LCD_RST_ACTIVATE();PORTD ^= 0x01;
  _delay_ms(220);PORTD ^= 0x01;
  LCD_RST_DEACTIVATE();PORTD ^= 0x01;
  lcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);PORTD ^= 0x01;
  lcd_command(PCD8544_SET_BIAS | 0x2);PORTD ^= 0x01;
  lcd_command(PCD8544_SET_VOP | 80);PORTD ^= 0x01;
  lcd_command(PCD8544_FUNCTION_SET);PORTD ^= 0x01;
  lcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);PORTD ^= 0x01;
  LCD_BACKLIGHT_DEACTIVATE();PORTD ^= 0x01;
}
void set_led() {
  DDRD = 0xff;
  PORTD ^= 0xff;
}

void lcd_draw_point(uint8_t x, uint8_t y) {
  fb[x + (y/8) * PCD8544_MAX_COLS] |= ( 1 << (y%8));
}

/*void characterG(float charX, float charY, float scale){
  lcd_draw_line(charX+((scale/2-((scale/5)*2))*4),charY-scale/2,charX-((scale/2-((scale/5)*2))*4),charY-scale/2);
  lcd_draw_line(charX+((scale/2-((scale/5)*2))*4),charY-scale/3,charX-((scale/2-((scale/5)*2))*2),charY-scale/3);
  lcd_draw_line(charX+((scale/2-((scale/5)*2))*4),charY-scale/2,charX+((scale/2-((scale/5)*2))*4),charY-scale/3);
  lcd_draw_line(charX-((scale/2-((scale/5)*2))*4),charY-scale/2,charX-((scale/2-((scale/5)*2))*4),charY+scale/2);
  lcd_draw_line(charX-((scale/2-((scale/5)*2))*2),charY+scale/3,charX-((scale/2-((scale/5)*2))*2),charY-scale/3);
  lcd_draw_line(charX-((scale/2-((scale/5)*2))*4),charY+scale/2,charX+((scale/2-((scale/5)*2))*4),charY+scale/2);
  lcd_draw_line(charX-((scale/2-((scale/5)*2))*2),charY+scale/3,charX+((scale/2-((scale/5)*2))*2),charY+scale/3);
  lcd_draw_line(charX+((scale/2-((scale/5)*2))*4),charY+scale/2,charX+((scale/2-((scale/5)*2))*4),charY-(scale/2-((scale/5)*2)));
  lcd_draw_line(charX+((scale/2-((scale/5)*2))*2),charY+scale/3,charX+((scale/2-((scale/5)*2))*2),charY+(scale/2-((scale/5)*2)));
  lcd_draw_line(charX+((scale/2-((scale/5)*2))*2),charY+(scale/2-((scale/5)*2)),charX,charY+(scale/2-((scale/5)*2)));
  lcd_draw_line(charX+((scale/2-((scale/5)*2))*4),charY-(scale/2-((scale/5)*2)),charX,charY-(scale/2-((scale/5)*2)));
  lcd_draw_line(charX,charY+(scale/2-((scale/5)*2)),charX,charY-(scale/2-((scale/5)*2)));
}*/

void swap(uint8_t* a, uint8_t* b)
{
    uint8_t temp = *a;
    *a = *b;
    *b = temp;
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
	uint8_t i;

	/* Only works for fonts < 8 bits in height */
  const uint8_t font_width = 5;
	for ( i = 0; i < font_width; i++ ) {
    fb[x + (line * PCD8544_MAX_COLS)] = Font5x7[ ((c - 32) * (font_width)) + i ];
    x++;
	}
}

void lcd_draw_string(uint8_t x, uint8_t line, char *str) {
	while (*str) {
		lcd_draw_char(x, line, *str++);
		x += (5 + 1);
		if ((x + 5 + 1) >= 84) {
			x = 0; /* Ran out of this line */
			line++;
		}
		if (line >= (48/(7 + 1)))
			return; /* Ran out of space :( */
	}
}

void lcd_fill(void) {
  for (uint8_t bank = 0; bank < PCD8544_MAX_BANKS; bank++) {
    /* Each bank is a single row 8 bits tall */
    uint8_t column;

    lcd_command(PCD8544_SET_Y_ADDRESS | bank);
    lcd_command(PCD8544_SET_X_ADDRESS | 0);

    for (column = 0; column < PCD8544_MAX_COLS; column++)
    {
      lcd_data(fb[(bank * PCD8544_MAX_COLS) + column]);
      fb[(bank * PCD8544_MAX_COLS) + column] = 0x00;
    }
  }
}
