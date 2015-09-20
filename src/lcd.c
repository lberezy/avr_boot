#include "lcd.h"

#ifdef PCD8544
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
// frame buffer
uint8_t fb[PCD8544_MAX_BANKS * PCD8544_MAX_COLS];
//terminal buffer



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
  LCD_PORT_INIT();
  LCD_RST_ACTIVATE();
  _delay_ms(220); // delay required for RST procedure
  LCD_RST_DEACTIVATE();
  lcd_command(PCD8544_FUNCTION_SET | PCD8544_EXTENDED_INSTRUCTION);
  lcd_command(PCD8544_SET_BIAS | 0x2);
  lcd_command(PCD8544_SET_VOP | 80);
  lcd_command(PCD8544_FUNCTION_SET);
  lcd_command(PCD8544_DISPLAY_CONTROL | PCD8544_DISPLAY_NORMAL);
  LCD_BACKLIGHT_DEACTIVATE();
}

void lcd_fill(void) {
  for (uint8_t bank = 0; bank < PCD8544_MAX_BANKS; bank++) {
    /* Each bank is a single row 8 bits tall */
    uint8_t column;

    lcd_command(PCD8544_SET_Y_ADDRESS | bank);
    lcd_command(PCD8544_SET_X_ADDRESS | 0);

    for (column = 0; column < PCD8544_MAX_COLS; column++)
    {
      lcd_data(buffer.fb[(bank * PCD8544_MAX_COLS) + column]);
      buffer.fb[(bank * PCD8544_MAX_COLS) + column] = 0x00;
    }
  }
}
#endif


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
