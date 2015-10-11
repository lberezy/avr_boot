#include "lcd.h"

#include "buffer.h"
#include "fram.h"

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

  _delay_ms(10);
  LCD_PORT_INIT();
  LCD_RST_HIGH();

  LCD_CE_ACTIVATE();
  LCD_RST_HIGH();
  LCD_DC_COMM();

  LCD_RST_LOW();
  _delay_ms(5); // delay required for RST procedure
  LCD_RST_HIGH();
  _delay_ms(10); // delay required for RST procedure
  lcd_command(UC1701_SET_SEG_DIR | UC1701_SET_SEG_DIR_MIRROR);  // reverse seg drivers
  lcd_command(UC1701_SET_COM_DIR | UC1701_SET_COM_DIR_NORM);
  lcd_command(UC1701_SET_ALL_PX | UC1701_SET_ALL_OFF);
  lcd_command(UC1701_SET_INV_DISP | UC1701_SET_INV_DISP_OFF);
  _delay_ms(120);
  lcd_command(UC1701_SET_BIAS_RATIO | UC1701_SET_BIAS_1_9); // set bias ratio
  lcd_command(UC1701_SET_POWER_CTRL | UC1701_SET_POWER_BOOST_ON | UC1701_SET_POWER_REG_ON | UC1701_SET_POWER_FOLL_ON);
  lcd_command(UC1701_SET_EL_VOL_1); // set contrast (2-part command)
  lcd_command(UC1701_SET_EL_VOL_2 | (UC1701_SET_EL_VOL_MASK & ((uint8_t)LCD_CONTRAST))); // set contrast [0..63]
  lcd_command(UC1701_SET_ADV_PROG_1);
  lcd_command(UC1701_SET_ADV_PROG_2 | UC1701_ADV_PROG_TEMPCO_1);
  lcd_command(UC1701_SET_DISP_EN | UC1701_SET_DISP_EN_ON);  // enable display
}

#include "led.h"
#include <util/delay.h>
/**
*
*/
void lcd_fill(void) {
  const uint8_t offset = 0;
  for (uint8_t page = 0; page < UC1701_NUM_PAGES; page++) {
    //Each bank is a single row 8 bits tall
    /* No longer need to manually set page and reset column cursor - handled by lcd */
    lcd_command(UC1701_SET_PAGE_ADDR | ((page) & 0b00001111));
    lcd_command(UC1701_SET_COL_ADDR_LSB | ((offset >> 4) & UC1701_SET_COL_MASK) );
    lcd_command(UC1701_SET_COL_ADDR_MSB | (offset & UC1701_SET_COL_MASK));
    for (uint8_t column = 0; column < DISPLAY_WIDTH; column++)
    {
      //lcd_data(buffer.fb[(page * DISPLAY_WIDTH) + column]);
      lcd_data(BUFFER_GET_BYTE((page * DISPLAY_WIDTH) + column));
    }
  }
}

void lcd_clear_buffer(void) {
#ifdef BUFFER_USE_SRAM
  for (uint8_t page = 0; page < UC1701_NUM_PAGES; page++) {
    for (uint8_t column = 0; column < DISPLAY_WIDTH; column++)
    {
      BUFFER_SET_BYTE((page * DISPLAY_WIDTH) + column, 0x00);
    }
  }
#else
  fram_clear_n_bytes( FRAM_FB_START, UC1701_NUM_PAGES * DISPLAY_WIDTH);
#endif
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
