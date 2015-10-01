#include "lcd.h"

#define stringify(x)  #x
#define expand_and_stringify(x) stringify(x)

#define LCD_DRIVER
#include "HAL/UC1701.h"


//#include "HAL/PCD8544.h"


/****** BEGIN LCD DRIVER IMPLEMENTATION ******/

#ifdef LCD_DRIVER
#undef LCD_DRIVER

#define LCD_PORT  PORTD
#define LCD_DDR   DDRD

#define LCD_RST_PIN PD1
#define LCD_CE_PIN  PD0
#define LCD_DC_PIN  PD3

#define LCD_CE_ACTIVATE()     (LCD_PORT &= ~(_BV(LCD_CE_PIN)))  /* active low */
#define LCD_CE_DEACTIVATE()   (LCD_PORT |= _BV(LCD_CE_PIN))
#define LCD_DC_DATA()         (LCD_PORT |= _BV(LCD_DC_PIN))
#define LCD_DC_COMM()         (LCD_PORT &= ~(_BV(LCD_DC_PIN)))
#define LCD_RST_LOW()         (LCD_PORT &= ~(_BV(LCD_RST_PIN))) /* active low */
#define LCD_RST_HIGH()        (LCD_PORT |= _BV(LCD_RST_PIN))

#define LCD_PORT_INIT() (LCD_DDR |= _BV(LCD_RST_PIN) | _BV(LCD_CE_PIN) | _BV(LCD_DC_PIN))

#include "spi.h"

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

  spi_setting_t spi_settings;
  spi_settings.endianness = SPI_MSB_FIRST;
  spi_settings.bus_mode = SPI_BUSMODE_MASTER;
  spi_settings.trans_mode = SPI_MODE_0;
  spi_settings.clock_rate = SPI_CLOCKDIV_4;
  spi_settings.double_clock =  SPI_DBLCLK_ENABLE;
  spi_init(spi_settings); // spi clk ~ 4 MHz


  LCD_PORT_INIT();
  LCD_CE_DEACTIVATE();
  LCD_RST_LOW();
  _delay_ms(20); // delay required for RST procedure
  LCD_RST_HIGH();
  _delay_ms(20); // delay required for RST procedure
  lcd_command(UC1701_SET_SCROLL_LINE | 0);  // Display start line 0
  lcd_command(UC1701_SET_SEG_DIR | UC1701_SET_SEG_DIR_MIRROR);  // reverse seg drivers
  lcd_command(UC1701_SET_COM_DIR | UC1701_SET_COM_DIR_NORM);
  lcd_command(UC1701_SET_ALL_PX | UC1701_SET_ALL_OFF);  // display from sram
  lcd_command(UC1701_SET_INV_DISP | UC1701_SET_INV_DISP_ON);
  lcd_command(UC1701_SET_BIAS_RATIO | UC1701_SET_BIAS_1_9); // set bias ratio
  // enable voltage generators for LCD
  lcd_command(UC1701_SET_POWER_CTRL | UC1701_SET_POWER_BOOST_ON | UC1701_SET_POWER_REG_ON | UC1701_SET_POWER_FOLL_ON);
  lcd_command(UC1701_SET_VLCD_RATIO | UC1701_SET_VLCD_DEFAULT); // set LCD bias
  lcd_command(UC1701_SET_EL_VOL_1); // set contrast (2-part command)
  lcd_command(UC1701_SET_EL_VOL_2 | (UC1701_SET_EL_VOL_MASK & ((uint8_t)16))); // set contrast [0..63]
  lcd_command(UC1701_SET_DISP_EN | UC1701_SET_DISP_EN_ON);  // enable display
}

void lcd_fill(void) {
  for (uint8_t bank = 0; bank < (DISPLAY_HEIGHT); bank++) {
    /* Each bank is a single row 8 bits tall */
    uint8_t column;

    lcd_command(UC1701_SET_PAGE_ADDR | bank);
    lcd_command(UC1701_SET_COL_ADDR_LSB | 0);
    lcd_command(UC1701_SET_COL_ADDR_MSB | 0);

    for (column = 0; column < DISPLAY_WIDTH; column++)
    {
      lcd_data(buffer.fb[(bank * UC1701_MAX_COLS) + column]);
      buffer.fb[(bank * UC1701_MAX_COLS) + column] = 0x00;
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
