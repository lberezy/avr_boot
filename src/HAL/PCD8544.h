#ifndef PCD8544_H
#define PCD8544_H


#ifdef LCD_DRIVER
#error LCD controller already selected. Can only have one controller in use.
#else
#define LCD_CONTROLLER PCD8544
#endif

#define PCD8544

#define PCD8544_NOP 0
#define PCD8544_FUNCTION_SET          (1<<5)
#define PCD8544_POWER_DOWN            (1<<2)
#define PCD8544_HORIZONTAL_ADDRESSING 0
#define PCD8544_VERTICAL_ADDRESSING   (1<<1)
#define PCD8544_EXTENDED_INSTRUCTION  (1<<0)
/**@}*/

/**
 * \name Basic instruction set (H=0)
 * @{
 */
#define PCD8544_DISPLAY_CONTROL  (1<<3)
#define PCD8544_DISPLAY_BLANK    0x0
#define PCD8544_DISPLAY_NORMAL   (1<<2)
#define PCD8544_DISPLAY_ALL_ON   (1<<0)
#define PCD8544_DISPLAY_INVERTED (1<<2|1<<0)
#define PCD8544_SET_Y_ADDRESS       0x40
#define PCD8544_SET_X_ADDRESS       0x80
/**@}*/

/**
 * \name Extended instruction set (H=1)
 * @{
 */
#define PCD8544_SET_TEMP (1<<2)
#define PCD8544_TEMPCO_0 0b00
#define PCD8544_TEMPCO_1 0b01
#define PCD8544_TEMPCO_2 0b10
#define PCD8544_TEMPCO_3 0b11

/** \todo Check if these instructions are from this group */
#define PCD8544_SET_BIAS (1<<4)
#define PCD8544_SET_VOP  (1<<7)
/**@}*/

#define PCD8544_MAX_BANKS 6
#define PCD8544_MAX_COLS  84

#define DISPLAY_WIDTH PCD8544_MAX_COLS
#define DISPLAY_HEIGHT (PCD8544_MAX_BANKS * 8)

#endif

/* driver section */

#ifdef LCD_DRIVER

#ifdef PCD8544
/*
#define LCD_PORT PORTB
#define LCD_DDR DDRB

#define LCD_RST_PIN PB0
#define LCD_CE_PIN PB6
#define LCD_DC_PIN PB1
#define LCD_BACKLIGHT_PIN PB4

#define LCD_CE_ACTIVATE() (LCD_PORT &= ~(_BV(LCD_CE_PIN))) // active low
#define LCD_CE_DEACTIVATE() (LCD_PORT |= _BV(LCD_CE_PIN))
#define LCD_DC_DATA() (LCD_PORT |= _BV(LCD_DC_PIN))
#define LCD_DC_COMM() (LCD_PORT &= ~(_BV(LCD_DC_PIN)))
#define LCD_RST_ACTIVATE() (LCD_PORT &= ~(_BV(LCD_RST_PIN)))
#define LCD_RST_DEACTIVATE() (LCD_PORT |= _BV(LCD_RST_PIN))

#define LCD_BACKLIGHT_ACTIVATE() (LCD_PORT |= _BV(LCD_BACKLIGHT_PIN))
#define LCD_BACKLIGHT_DEACTIVATE() (LCD_PORT &= ~(_BV(LCD_BACKLIGHT_PIN)))
#define LCD_PORT_INIT() (LCD_DDR |= _BV(LCD_RST_PIN) | _BV(LCD_CE_PIN) | _BV(LCD_DC_PIN) | _BV(LCD_BACKLIGHT_PIN))

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
    //Each bank is a single row 8 bits tall
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
*/

#undef LCD_DRIVER
#endif
