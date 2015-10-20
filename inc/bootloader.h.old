#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdio.h>

#include "config.h"

void flash_app(char* path) __attribute__((section(".boot")));

#endif
#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "lcd.h"  // for display size constants
#define SD_BUFFER_SIZE 256

#define FRAME_BUFFER_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT / 8)

#define FLASH_BUFFER_SIZE SPM_PAGESIZE
typedef union {
#ifdef GRAPHICS_USE_SRAM
  volatile uint8_t fb[FRAME_BUFFER_SIZE];
#endif
#ifdef GRAPHICS_USE_FRAM
  volatile uint8_t pagebuffer[DISPLAY_WIDTH];
#endif
  volatile uint8_t sd[SD_BUFFER_SIZE];
  volatile uint8_t flash_page[FLASH_BUFFER_SIZE];
} buffer_t;
volatile buffer_t buffer; // instantiate buffer in SRAM


// buffer location in FRAM
#define FRAM_FB_START   0x00
#define FRAM_FB_END     (FRAM_FB_START + FRAME_BUFFER_SIZE)

#ifdef GRAPHICS_USE_SRAM
  #define BUFFER_SET_BYTE(addr, b) (buffer.fb[(addr)] = (b))
  #define BUFFER_GET_BYTE(addr) (buffer.fb[(addr)])
#endif

#ifdef GRAPHICS_USE_FRAM
  #define BUFFER_SET_BYTE(addr, b) (fram_write_byte(FRAM_FB_START + (addr), (b)))
  #define BUFFER_GET_BYTE(addr) (fram_read_byte(FRAM_FB_START + (addr)))
#endif


#endif
#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "HAL/board.h"

/* hardware abstractions */
#define BTN_DIR_MASK    (BTN_UP_PIN | BTN_DOWN_PIN | BTN_LEFT_PIN | BTN_RIGHT_PIN)
#define BTN_INPUT_MASK  (BTN_A_PIN | BTN_B_PIN)


#define BTN_FLAG_BITPOS 7
/* software-only representation - matches with hardware*/
typedef enum {
  BTN_A             = BTN_A_PIN,
  BTN_B             = BTN_B_PIN,
  BTN_UP            = BTN_UP_PIN,
  BTN_DOWN          = BTN_UP_PIN,
  BTN_LEFT          = BTN_LEFT_PIN,
  BTN_RIGHT         = BTN_RIGHT_PIN,
  BTN_FLAG_POLLING  = _BV(BTN_FLAG_BITPOS)
} button_t;

#define BTN_ALL_MASK (BTN_A | BTN_B | BTN_UP | BTN_DOWN | BTN_LEFT | BTN_RIGHT)
typedef uint8_t btn_state_t;


uint8_t buttons_isset(button_t button_mask);
void buttons_init(void);
void buttons_poll(void);
#endif
#ifndef CONFIG_H
#define CONFIG_H

#define APP_FILENAME "alice.txt"

#define APP_START_ADDR 0
#define APP_END_ADDR 8192

//#define GRAPHICS_USE_SRAM
#define GRAPHICS_USE_FRAM

#endif
#ifndef DEBUG_H
#define DEBUG_H

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#endif
#ifndef _FONT_H
#define _FONT_H

/* typedef struct {
  const char first_ascii;
  const uint8_t num_glyphs;
  const uint8_t width_px;
  const uint8_t height_px;
  const uint8_t font_data[];
} font_t; */
#include <stdint.h>
/* defines global "font" variable */
//#include "fonts/font_5x7.h"
#include "fonts/font_BMplain.h"
const uint8_t* font_data;

#endif
#ifndef _FONT_5X7_H
#define _FONT_5X7_H

#include "../font.h"
#include <avr/pgmspace.h>
#include <stdint.h>

/*#define FONT_FIRST_ASCII  ' '   // first ASCII point
#define FONT_LAST_ASCII   '}'   // number of ASCII characters covered from point
#define FONT_GLYPH_WIDTH  5     // glyph width in px
#define FONT_GLYPH_HEIGHT 7     // glyph height in px
*/
#endif
#ifndef _FONT_BMPLAIN_H
#define _FONT_BMPLAIN_H

#include "../font.h"
#include <avr/pgmspace.h>
#include <stdint.h>

#define FONT_FIRST_ASCII  ' '   // first ASCII point
#define FONT_LAST_ASCII   '~'   // number of ASCII characters covered from point
#define FONT_GLYPH_WIDTH  6     // glyph width in px
#define FONT_GLYPH_HEIGHT 8     // glyph height in px

#endif
#ifndef FRAM_H
#define FRAM_H

#include <stdint.h>

void fram_init();

uint8_t fram_read_byte(uint16_t addr);
void fram_write_byte(uint16_t addr, uint8_t c);

void fram_read_n_bytes(uint16_t start_addr, uint16_t n, uint8_t* buff);
void fram_write_n_bytes(uint16_t start_addr, uint16_t n, uint8_t* buff);

void fram_clear_n_bytes(uint16_t start_addr, uint16_t n);

uint8_t fram_read_status();

#endif
#ifndef _GRAPHICS_H
#define _GRAPHICS_H

//#include "lcd.h"
#include "font.h"
#include "buffer.h"
#include "terminal.h"
#include "stdlib.h"
#include "lcd.h"
/*FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
stdout = &uart_output;
stdin  = &uart_input;*/
#define TERM_WIDTH_PX   DISPLAY_WIDTH
#define TERM_HEIGHT_PX  DISPLAY_HEIGHT
#define TERM_ROWS       (TERM_HEIGHT_PX / FONT_HEIGHT)
#define TERM_COLS       (TERM_WIDTH_PX /  (FONT_WIDTH + 1))



void gfx_draw_point(uint8_t x, uint8_t y);
void gfx_draw_char(uint8_t x, uint8_t line, char c);
void gfx_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void gfx_putchar(char c);
void gfx_draw_term(terminal_t* term);
void gfx_draw_string(uint8_t x, uint8_t line, const char* str);

#endif
#ifndef ADC_H
#define ADC_H

#define BAT_ADC_PIN PA1
#define BAT_CONF_INPUT() do{DDRA &= ~_BV(BAT_ADC_PIN);} while(0)
#define
#endif
#ifndef BOARD_H
#define BOARD_H

#include "led_hardware.h"
#include "lcd_hardware.h"
#include "button_hardware.h"
#include "spi_hardware.h"
#include "timer_hardware.h"
#include "fram_hardware.h"
#include "sd_hardware.h"

#endif
#ifndef BUTTON_HARDWARE_H
#define BUTTON_HARDWARE_H

#define BTN_INPUT_PORT PORTD
#define BTN_INPUT_PORTIN PIND
#define BTN_INPUT_DDR DDRD

#define BTN_DIR_PORT PORTB
#define BTN_DIR_PORTIN PINB
#define BTN_DIR_DDR DDRB

#include <avr/io.h>

/* typesafe hardware pin mapping */
enum {
  BTN_A_PIN     = _BV(6),
  BTN_B_PIN     = _BV(5),
  BTN_UP_PIN    = _BV(1),
  BTN_DOWN_PIN  = _BV(2),
  BTN_LEFT_PIN  = _BV(0),
  BTN_RIGHT_PIN = _BV(3),
} button_pin;

#endif
#ifndef FRAM_HARDWARE_H
#define FRAM_HARDWARE_H

#define FRAM_PORT PORTB
#define FRAM_DDR  DDRB

#define FRAM_CS_PIN PB4

#define FRAM_SIZE_BYTES 2048

#define FRAM_PORT_INIT()          (FRAM_DDR |= _BV(FRAM_CS_PIN))
#define FRAM_CS_DEACTIVATE()      (FRAM_PORT |= _BV(FRAM_CS_PIN))
#define FRAM_CS_ACTIVATE()        (FRAM_PORT &= ~(_BV(FRAM_CS_PIN)))

// opcodes
#define FRAM_WRITE_ENABLE   (0b00000110)
#define FRAM_WRITE_DISABLE  (0b00000100)
#define FRAM_READ_STATUS    (0b00000101)
#define FRAM_WRITE_STATUS   (0b00000001)
#define FRAM_READ_MEMORY    (0b00000011)
#define FRAM_WRITE_MEMORY   (0b00000010)

// status register bits
#define FRAM_STATUS_WEL   _BV(1)
#define FRAM_STATUS_BP0   _BV(2)
#define FRAM_STATUS_BP1   _BV(3)
#define FRAM_STATUS_WPEN  _BV(7)


#define FRAM_MSB_MASK       (0b00011111)

#define FRAM_DUMMY_PACKET   0x00

#endif
#ifndef LCD_HARDWARE_H
#define LCD_HARDWARE_H


/* select appropriate LCD controller */
//#include "PCD8544.h"
#include "UC1701.h"

#endif
#ifndef LED_HARDWARE_H
#define LED_HARDWARE_H

#define USER_LED_PORT PORTC
#define USER_LED_DDR  DDRC
#define USER_LED_PIN  PC6

#define BACKLIGHT_LED_PORT  PORTD
#define BACKLIGHT_LED_DDR   DDRD
#define BACKLIGHT_LED_PIN   PD4

#endif
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
#ifndef SD_HARDWARE_H
#define SD_HARDWARE_H

#define SD_PORT PORTA
#define SD_DDR  DDRA

#define SD_CS_PIN PA0


#define SD_PORT_INIT()          (SD_DDR |= _BV(SD_CS_PIN))
#define SD_CS_DEACTIVATE()      (SD_PORT |= _BV(SD_CS_PIN))
#define SD_CS_ACTIVATE()        (SD_PORT &= ~(_BV(SD_CS_PIN)))

#endif
#ifndef SPI_HARDWARE_H
#define SPI_HARDWARE_H

#include <avr/io.h>


#define SPI_PORT  PORTB
#define SPI_PIN   PINB
#define SPI_DDR   DDRB

#define SPI_MOSI_PIN  PB5
#define SPI_MISO_PIN  PB6
#define SPI_SCK_PIN   PB7

#define SPI_LSBFIRST_MASK   0b00000001
#define SPI_MASTER_MASK     0b00000001
#define SPI_MODE_MASK       0b00000011
#define SPI_SPEED_MASK      0b00000011
#define SPI_DBLCLK_MASK     0b00000001

#define SPI_SCK_LOW()   (SPI_PORT &= ~(_BV(SPI_SCK_PIN)))
#define SPI_SCK_HIGH()  (SPI_PORT |= (_BV(SPI_SCK_PIN)))



#endif
#ifndef TIMER_HARDWARE_H
#define TIMER_HARDWARE_H

/* TCCR0 */


#define TIMER0_CLK_SHIFT    0x02
#define TIMER0_CLK_DIV_STOP 0x00
#define TIMER0_CLK_DIV_1    0x01
#define TIMER0_CLK_DIV_8    0x02
#define TIMER0_CLK_DIV_64   0x03
#define TIMER0_CLK_DIV_256  0x04
#define TIMER0_CLK_DIV_1024 0x05

/* TIMSK */
#define TIMER0_COMP_MATCH_INT 0x01
#define TIMER0_OVERFLOW_INT   0x00

/* TIFR */
#define TIMER0_OUT_COMP_FLAG  0x01
#define TIMER0_OVERFLOW_FLAG  0x01

/* SFIOR */
#define TIMER0_PRESCALE_RST   0x00

#endif
#ifndef UC1701_H
#define UC1701_H

#ifdef _LCD_DRIVER
#error LCD controller already selected. Can only have one controller in use.
#else
#define LCD_CONTROLLER UC1701
#endif

/* control registers */

#define UC1701_SL
#define UC1701_STATUS_BZ            _BV(7)
#define UC1701_STATUS_MX            _BV(6)
#define UC1701_STATUS_DE            _BV(5)
#define UC1701_STATUS_RST           _BV(4)

#define UC1701_SET_COL_ADDR_LSB     (0b00000000)
#define UC1701_SET_COL_ADDR_MSB     (0b00010000)
#define UC1701_SET_COL_MASK         (0b00001111)

#define UC1701_SET_POWER_CTRL       (0b00101000)
#define UC1701_SET_POWER_BOOST_ON   (0b00000001)
#define UC1701_SET_POWER_BOOST_OFF  (0b00000000)
#define UC1701_SET_POWER_REG_ON     (0b00000010)
#define UC1701_SET_POWER_REG_OFF    (0b00000000)
#define UC1701_SET_POWER_FOLL_ON    (0b00000100)
#define UC1701_SET_POWER_FOLL_OFF   (0b00000000)

#define UC1701_SET_SCROLL_LINE      (0b01000000)
#define UC1701_SET_SCROLL_MASK      (0b00111111)

#define UC1701_SET_PAGE_ADDR        (0b10110000)
#define UV1701_SET_PAGE_MASK        (0b00001111)

#define UC1701_SET_VLCD_RATIO       (0b00100000)
#define UC1701_SET_VLCD_DEFAULT     (0b00000111)
#define UC1701_SET_VLCD_MASK        (0b00000111)

/* two byte command */
/* default value: 32 */
#define UC1701_SET_EL_VOL_1         (0b10000001)
#define UC1701_SET_EL_VOL_2         (0b00000000)
#define UC1701_SET_EL_VOL_MASK      (0b00111111)

#define UC1701_SET_ALL_PX           (0b10100100)
#define UC1701_SET_ALL_ON           (0b00000001)
#define UC1701_SET_ALL_OFF          (0b00000000)

#define UC1701_SET_INV_DISP         (0b10100110)
#define UC1701_SET_INV_DISP_ON      (0b00000001)
#define UC1701_SET_INV_DISP_OFF     (0b00000000)

#define UC1701_SET_DISP_EN          (0b10101110)
#define UC1701_SET_DISP_EN_ON       (0b00000001)
#define UC1701_SET_DISP_EN_OFF      (0b00000000)

#define UC1701_SET_SEG_DIR          (0b10100000)
#define UC1701_SET_SEG_DIR_NORM     (0b00000000)
#define UC1701_SET_SEG_DIR_MIRROR   (0b00000001)

#define UC1701_SET_COM_DIR          (0b11000000)
#define UC1701_SET_COM_DIR_NORM     (0b00000000)
#define UC1701_SET_COM_DIR_MIRROR   (0b00001000)

#define UC1701_SYS_RESET            (0b11100010)

/* varies according to duty */
/*
Default: 0
DUTY | BR = 0 | BR = 1
----------------------
1/65*|   1/9  |  1/7
1/49 |   1/8  |  1/6
1/33 |   1/6  |  1/5
1/55 |   1/8  |  1/6
*/

#define UC1701_SET_BIAS_RATIO       (0b10100010)
#define UC1701_SET_BIAS_1_7         (0b00000001)
#define UC1701_SET_BIAS_1_9         (0b00000000)

#define UC1701_NOP                  (0b11100011)

#define UC1701_SET_CUR_MODE         (0b11100000)
#define UC1701_RESET_CUR_MODE       (0b11101110)

#define UC1701_SET_STAT_IND_OFF     (0b10101100)
/* two byte command, 2nd byte is don't-care */
#define UC1701_SET_STAT_IND_OFF_2   (0b10101101)

#define UC1701_SET_BOOST_1          (0b11111000)
#define UC1701_SET_BOOST_2          (0b00000000)

/* two byte command */

#define UC1701_SET_ADV_PROG_1       (0b11111010)
#define UC1701_SET_ADV_PROG_2       (0b00010000)
#define UC1701_ADV_PROG_WRAP_COL    (0b00000010)
#define UC1701_ADV_PROG_WRAP_ROW    (0b00000001)
#define UC1701_ADV_PROG_TEMPCO_0    (0b00000000)
#define UC1701_ADV_PROG_TEMPCO_1    (0b10000000)

/* compound command */
#define UC1701_SET_POWER_SAVE       (0b00000000)

#define UC1701_NUM_PAGES 8
#define UC1701_PAGE_BIT_SIZE 8

#define DISPLAY_WIDTH 102
#define DISPLAY_HEIGHT UC1701_NUM_PAGES * UC1701_PAGE_BIT_SIZE




#endif
#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "spi.h"
#include "HAL/board.h"
#include "buffer.h"

#define LCD_CONTRAST 16
/* standard interface that all LCD controllers must implement */
void lcd_init(void);
void lcd_fill(void);
void lcd_clear_buffer(void);
#endif
#ifndef LED_H
#define LED_H

#include "HAL/board.h"

#define USER_LED_INIT()   do{USER_LED_DDR  |=   _BV(USER_LED_PIN); USER_LED_PORT |= _BV(USER_LED_PIN);}while(0)
#define USER_LED_OFF()    do{USER_LED_PORT |=   _BV(USER_LED_PIN);}while(0)
#define USER_LED_ON()     do{USER_LED_PORT &=  ~_BV(USER_LED_PIN);}while(0)
#define USER_LED_TOGGLE() do{USER_LED_PORT ^=   _BV(USER_LED_PIN);}while(0)


#define BACKLIGHT_LED_INIT()    do{BACKLIGHT_LED_DDR  |=  _BV(BACKLIGHT_LED_PIN); BACKLIGHT_LED_PORT &= ~_BV(BACKLIGHT_LED_PIN);}while(0)
#define BACKLIGHT_LED_ON()      do{BACKLIGHT_LED_PORT |=  _BV(BACKLIGHT_LED_PIN);}while(0)
#define BACKLIGHT_LED_OFF()     do{BACKLIGHT_LED_PORT &= ~_BV(BACKLIGHT_LED_PIN);}while(0)
#define BACKLIGHT_LED_TOGGLE()  do{BACKLIGHT_LED_PORT ^=  _BV(BACKLIGHT_LED_PIN);}while(0)

#define BACKLIGHT_PWM_MODE      (_BV(WGM20) | _BV(WGM21))   // fast PWM
#define BACKLIGHT_PWM_OUTMODE   (_BV(COM21) | _BV(COM20))   // inverted output
#define BACKLIGHT_PWM_CLOCK     (_BV(CS20)) // F_CPU / 2
#define BACKLIGHT_PWM_LEVEL     OCR2
// initialise backlight and set to half brightness
#define BACKLIGHT_LED_PWM_INIT() do{TCCR2 |= (BACKLIGHT_PWM_MODE | BACKLIGHT_PWM_OUTMODE | BACKLIGHT_PWM_CLOCK); BACKLIGHT_PWM_LEVEL = 196;} while(0)

void led_init(void);
void led_user_on(void);
void led_user_off(void);
void led_user_toggle(void);
void led_backlight_on(void);
void led_backlight_off(void);
void led_backlight_on(void);
void led_backlight_level(uint8_t level);

#endif
/*-----------------------------------------------------------------------
/  PFF - Low level disk interface modlue include file    (C)ChaN, 2009
/-----------------------------------------------------------------------*/

#ifndef _DISKIO

#include "integer.h"


/* Status of Disk Functions */
typedef BYTE	DSTATUS;


/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Function succeeded */
	RES_ERROR,		/* 1: Disk error */
	RES_NOTRDY,		/* 2: Not ready */
	RES_PARERR		/* 3: Invalid parameter */
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */

DSTATUS disk_initialize (void)
__attribute__((section(".library"), used));
DRESULT disk_readp (BYTE*, DWORD, WORD, WORD)
__attribute__((section(".library"), used));
DRESULT disk_writep (const BYTE*, DWORD)
__attribute__((section(".library"), used));

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */

/* Card type flags (CardType) */
#define CT_MMC				0x01	/* MMC ver 3 */
#define CT_SD1				0x02	/* SD ver 1 */
#define CT_SD2				0x04	/* SD ver 2 */
#define CT_SDC				(CT_SD1|CT_SD2)	/* SD */
#define CT_BLOCK			0x08	/* Block addressing */

#define _DISKIO
#endif
/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _INTEGER
#define _INTEGER

#ifdef _WIN32	/* FatFs development platform */

#include <windows.h>
#include <tchar.h>

#else			/* Embedded platform */
#include <stdint.h>
/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef int8_t  CHAR;
typedef uint8_t	UCHAR;
typedef uint8_t	BYTE;

/* These types must be 16-bit integer */
typedef int16_t			SHORT;
typedef uint16_t	USHORT;
typedef uint16_t	WORD;
typedef uint16_t	WCHAR;

/* These types must be 32-bit integer */
typedef long			    LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

#endif

#endif
/*---------------------------------------------------------------------------/
/  Petit FatFs - FAT file system module include file  R0.02a   (C)ChaN, 2010
/----------------------------------------------------------------------------/
/ Petit FatFs module is an open source software to implement FAT file system to
/ small embedded systems. This is a free software and is opened for education,
/ research and commercial developments under license policy of following trems.
/
/  Copyright (C) 2010, ChaN, all right reserved.
/
/ * The Petit FatFs module is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial use UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/----------------------------------------------------------------------------*/

#include "integer.h"

/*---------------------------------------------------------------------------/
/ Petit FatFs Configuration Options
/
/ CAUTION! Do not forget to make clean the project after any changes to
/ the configuration options.
/
/----------------------------------------------------------------------------*/
#ifndef _FATFS
#define _FATFS

#define	_USE_READ	1	/* 1:Enable pf_read() */

#define	_USE_DIR	1	/* 1:Enable pf_opendir() and pf_readdir() */

#define	_USE_LSEEK	0	/* 1:Enable pf_lseek() */

#define	_USE_WRITE	0	/* 1:Enable pf_write() */

#define _FS_FAT12	0	/* 1:Enable FAT12 support */
#define _FS_FAT32	1	/* 1:Enable FAT32 support */


#define	_CODE_PAGE	1
/* Defines which code page is used for path name. Supported code pages are:
/  932, 936, 949, 950, 437, 720, 737, 775, 850, 852, 855, 857, 858, 862, 866,
/  874, 1250, 1251, 1252, 1253, 1254, 1255, 1257, 1258 and 1 (ASCII only).
/  SBCS code pages except for 1 requiers a case conversion table. This
/  might occupy 128 bytes on the RAM on some platforms, e.g. avr-gcc. */


#define _WORD_ACCESS	0
/* The _WORD_ACCESS option defines which access method is used to the word
/  data in the FAT structure.
/
/   0: Byte-by-byte access. Always compatible with all platforms.
/   1: Word access. Do not choose this unless following condition is met.
/
/  When the byte order on the memory is big-endian or address miss-aligned
/  word access results incorrect behavior, the _WORD_ACCESS must be set to 0.
/  If it is not the case, the value can also be set to 1 to improve the
/  performance and code efficiency. */


/* End of configuration options. Do not change followings without care.     */
/*--------------------------------------------------------------------------*/



#if _FS_FAT32
#define	CLUST	DWORD
#else
#define	CLUST	WORD
#endif


/* File system object structure */

typedef struct {
	BYTE	fs_type;	/* FAT sub type */
	BYTE	flag;		/* File status flags */
	BYTE	csize;		/* Number of sectors per cluster */
	BYTE	pad1;
	WORD	n_rootdir;	/* Number of root directory entries (0 on FAT32) */
	CLUST	n_fatent;	/* Number of FAT entries (= number of clusters + 2) */
	DWORD	fatbase;	/* FAT start sector */
	DWORD	dirbase;	/* Root directory start sector (Cluster# on FAT32) */
	DWORD	database;	/* Data start sector */
	DWORD	fptr;		/* File R/W pointer */
	DWORD	fsize;		/* File size */
	CLUST	org_clust;	/* File start cluster */
	CLUST	curr_clust;	/* File current cluster */
	DWORD	dsect;		/* File current data sector */
} FATFS;



/* Directory object structure */

typedef struct {
	WORD	index;		/* Current read/write index number */
	BYTE*	fn;			/* Pointer to the SFN (in/out) {file[8],ext[3],status[1]} */
	CLUST	sclust;		/* Table start cluster (0:Static table) */
	CLUST	clust;		/* Current cluster */
	DWORD	sect;		/* Current sector */
} DIR;



/* File status structure */

typedef struct {
	DWORD	fsize;		/* File size */
	WORD	fdate;		/* Last modified date */
	WORD	ftime;		/* Last modified time */
	BYTE	fattrib;	/* Attribute */
	char	fname[13];	/* File name */
} FILINFO;



/* File function return code (FRESULT) */

typedef enum {
	FR_OK = 0,			/* 0 */
	FR_DISK_ERR,		/* 1 */
	FR_NOT_READY,		/* 2 */
	FR_NO_FILE,			/* 3 */
	FR_NO_PATH,			/* 4 */
	FR_NOT_OPENED,		/* 5 */
	FR_NOT_ENABLED,		/* 6 */
	FR_NO_FILESYSTEM	/* 7 */
} FRESULT;



/*--------------------------------------------------------------*/
/* Petit FatFs module application interface                     */

FRESULT pf_mount (FATFS*)
__attribute__((section(".library"), used));						/* Mount/Unmount a logical drive */
FRESULT pf_open (const char*)
__attribute__((section(".library"), used));					/* Open a file */
FRESULT pf_read (void*, WORD, WORD*)
__attribute__((section(".library"), used));			/* Read data from the open file */
FRESULT pf_write (const void*, WORD, WORD*)
__attribute__((section(".library"), used));	/* Write data to the open file */
FRESULT pf_lseek (DWORD)
__attribute__((section(".library"), used));						/* Move file pointer of the open file */
FRESULT pf_opendir (DIR*, const char*)
__attribute__((section(".library"), used));			/* Open a directory */
FRESULT pf_readdir (DIR*, FILINFO*)
__attribute__((section(".library"), used));			/* Read a directory item from the open directory */



/*--------------------------------------------------------------*/
/* Flags and offset address                                     */

/* File status flag (FATFS.flag) */

#define	FA_OPENED	0x01
#define	FA_WPRT		0x02
#define	FA__WIP		0x40


/* FAT sub type (FATFS.fs_type) */

#define FS_FAT12	1
#define FS_FAT16	2
#define FS_FAT32	3


/* File attribute bits for directory entry */

#define	AM_RDO	0x01	/* Read only */
#define	AM_HID	0x02	/* Hidden */
#define	AM_SYS	0x04	/* System */
#define	AM_VOL	0x08	/* Volume label */
#define AM_LFN	0x0F	/* LFN entry */
#define AM_DIR	0x10	/* Directory */
#define AM_ARC	0x20	/* Archive */
#define AM_MASK	0x3F	/* Mask of defined bits */


/*--------------------------------*/
/* Multi-byte word access macros  */

#if _WORD_ACCESS == 1	/* Enable word access to the FAT structure */
#define	LD_WORD(ptr)		(WORD)(*(WORD*)(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(*(DWORD*)(BYTE*)(ptr))
#define	ST_WORD(ptr,val)	*(WORD*)(BYTE*)(ptr)=(WORD)(val)
#define	ST_DWORD(ptr,val)	*(DWORD*)(BYTE*)(ptr)=(DWORD)(val)
#else					/* Use byte-by-byte access to the FAT structure */
#define	LD_WORD(ptr)		(WORD)(((WORD)*((BYTE*)(ptr)+1)<<8)|(WORD)*(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(((DWORD)*((BYTE*)(ptr)+3)<<24)|((DWORD)*((BYTE*)(ptr)+2)<<16)|((WORD)*((BYTE*)(ptr)+1)<<8)|*(BYTE*)(ptr))
#define	ST_WORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8)
#define	ST_DWORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8); *((BYTE*)(ptr)+2)=(BYTE)((DWORD)(val)>>16); *((BYTE*)(ptr)+3)=(BYTE)((DWORD)(val)>>24)
#endif


#endif /* _FATFS */
/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: lc-addrlabels.h,v 1.4 2006/06/03 11:29:43 adam Exp $
 */

/**
 * \addtogroup lc
 * @{
 */

/**
 * \file
 * Implementation of local continuations based on the "Labels as
 * values" feature of gcc
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 * This implementation of local continuations is based on a special
 * feature of the GCC C compiler called "labels as values". This
 * feature allows assigning pointers with the address of the code
 * corresponding to a particular C label.
 *
 * For more information, see the GCC documentation:
 * http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
 *
 */

#ifndef __LC_ADDRLABELS_H__
#define __LC_ADDRLABELS_H__

/** \hideinitializer */
typedef void * lc_t;

#define LC_INIT(s) s = NULL

#define LC_RESUME(s)				\
  do {						\
    if(s != NULL) {				\
      goto *s;					\
    }						\
  } while(0)

#define LC_CONCAT2(s1, s2) s1##s2
#define LC_CONCAT(s1, s2) LC_CONCAT2(s1, s2)

#define LC_SET(s)				\
  do {						\
    LC_CONCAT(LC_LABEL, __LINE__):   	        \
    (s) = &&LC_CONCAT(LC_LABEL, __LINE__);	\
  } while(0)

#define LC_END(s)

#endif /* __LC_ADDRLABELS_H__ */
/** @} */
/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: lc-switch.h,v 1.4 2006/06/03 11:29:43 adam Exp $
 */

/**
 * \addtogroup lc
 * @{
 */

/**
 * \file
 * Implementation of local continuations based on switch() statment
 * \author Adam Dunkels <adam@sics.se>
 *
 * This implementation of local continuations uses the C switch()
 * statement to resume execution of a function somewhere inside the
 * function's body. The implementation is based on the fact that
 * switch() statements are able to jump directly into the bodies of
 * control structures such as if() or while() statmenets.
 *
 * This implementation borrows heavily from Simon Tatham's coroutines
 * implementation in C:
 * http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
 */

#ifndef __LC_SWITCH_H__
#define __LC_SWITCH_H__

/* WARNING! lc implementation using switch() does not work if an
   LC_SET() is done within another switch() statement! */

/** \hideinitializer */
typedef unsigned short lc_t;

#define LC_INIT(s) s = 0;

#define LC_RESUME(s) switch(s) { case 0:

#define LC_SET(s) s = __LINE__; case __LINE__:

#define LC_END(s) }

#endif /* __LC_SWITCH_H__ */

/** @} */
/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the protothreads library.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: lc.h,v 1.2 2005/02/24 10:36:59 adam Exp $
 */

/**
 * \addtogroup pt
 * @{
 */

/**
 * \defgroup lc Local continuations
 * @{
 *
 * Local continuations form the basis for implementing protothreads. A
 * local continuation can be <i>set</i> in a specific function to
 * capture the state of the function. After a local continuation has
 * been set can be <i>resumed</i> in order to restore the state of the
 * function at the point where the local continuation was set.
 *
 *
 */

/**
 * \file lc.h
 * Local continuations
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifdef DOXYGEN
/**
 * Initialize a local continuation.
 *
 * This operation initializes the local continuation, thereby
 * unsetting any previously set continuation state.
 *
 * \hideinitializer
 */
#define LC_INIT(lc)

/**
 * Set a local continuation.
 *
 * The set operation saves the state of the function at the point
 * where the operation is executed. As far as the set operation is
 * concerned, the state of the function does <b>not</b> include the
 * call-stack or local (automatic) variables, but only the program
 * counter and such CPU registers that needs to be saved.
 *
 * \hideinitializer
 */
#define LC_SET(lc)

/**
 * Resume a local continuation.
 *
 * The resume operation resumes a previously set local continuation, thus
 * restoring the state in which the function was when the local
 * continuation was set. If the local continuation has not been
 * previously set, the resume operation does nothing.
 *
 * \hideinitializer
 */
#define LC_RESUME(lc)

/**
 * Mark the end of local continuation usage.
 *
 * The end operation signifies that local continuations should not be
 * used any more in the function. This operation is not needed for
 * most implementations of local continuation, but is required by a
 * few implementations.
 *
 * \hideinitializer 
 */
#define LC_END(lc)

/**
 * \var typedef lc_t;
 *
 * The local continuation type.
 *
 * \hideinitializer
 */
#endif /* DOXYGEN */

#ifndef __LC_H__
#define __LC_H__


#ifdef LC_INCLUDE
#include LC_INCLUDE
#else
#include "lc-switch.h"
#endif /* LC_INCLUDE */

#endif /* __LC_H__ */

/** @} */
/** @} */
/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the protothreads library.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: pt-sem.h,v 1.2 2005/02/24 10:36:59 adam Exp $
 */

/**
 * \addtogroup pt
 * @{
 */

/**
 * \defgroup ptsem Protothread semaphores
 * @{
 *
 * This module implements counting semaphores on top of
 * protothreads. Semaphores are a synchronization primitive that
 * provide two operations: "wait" and "signal". The "wait" operation
 * checks the semaphore counter and blocks the thread if the counter
 * is zero. The "signal" operation increases the semaphore counter but
 * does not block. If another thread has blocked waiting for the
 * semaphore that is signalled, the blocked thread will become
 * runnable again.
 *
 * Semaphores can be used to implement other, more structured,
 * synchronization primitives such as monitors and message
 * queues/bounded buffers (see below).
 *
 * The following example shows how the producer-consumer problem, also
 * known as the bounded buffer problem, can be solved using
 * protothreads and semaphores. Notes on the program follow after the
 * example.
 *
 \code
#include "pt-sem.h"

#define NUM_ITEMS 32
#define BUFSIZE 8

static struct pt_sem mutex, full, empty;

PT_THREAD(producer(struct pt *pt))
{
  static int produced;
  
  PT_BEGIN(pt);
  
  for(produced = 0; produced < NUM_ITEMS; ++produced) {
  
    PT_SEM_WAIT(pt, &full);
    
    PT_SEM_WAIT(pt, &mutex);
    add_to_buffer(produce_item());    
    PT_SEM_SIGNAL(pt, &mutex);
    
    PT_SEM_SIGNAL(pt, &empty);
  }

  PT_END(pt);
}

PT_THREAD(consumer(struct pt *pt))
{
  static int consumed;
  
  PT_BEGIN(pt);

  for(consumed = 0; consumed < NUM_ITEMS; ++consumed) {
    
    PT_SEM_WAIT(pt, &empty);
    
    PT_SEM_WAIT(pt, &mutex);    
    consume_item(get_from_buffer());    
    PT_SEM_SIGNAL(pt, &mutex);
    
    PT_SEM_SIGNAL(pt, &full);
  }

  PT_END(pt);
}

PT_THREAD(driver_thread(struct pt *pt))
{
  static struct pt pt_producer, pt_consumer;

  PT_BEGIN(pt);
  
  PT_SEM_INIT(&empty, 0);
  PT_SEM_INIT(&full, BUFSIZE);
  PT_SEM_INIT(&mutex, 1);

  PT_INIT(&pt_producer);
  PT_INIT(&pt_consumer);

  PT_WAIT_THREAD(pt, producer(&pt_producer) &
		     consumer(&pt_consumer));

  PT_END(pt);
}
 \endcode
 *
 * The program uses three protothreads: one protothread that
 * implements the consumer, one thread that implements the producer,
 * and one protothread that drives the two other protothreads. The
 * program uses three semaphores: "full", "empty" and "mutex". The
 * "mutex" semaphore is used to provide mutual exclusion for the
 * buffer, the "empty" semaphore is used to block the consumer is the
 * buffer is empty, and the "full" semaphore is used to block the
 * producer is the buffer is full.
 *
 * The "driver_thread" holds two protothread state variables,
 * "pt_producer" and "pt_consumer". It is important to note that both
 * these variables are declared as <i>static</i>. If the static
 * keyword is not used, both variables are stored on the stack. Since
 * protothreads do not store the stack, these variables may be
 * overwritten during a protothread wait operation. Similarly, both
 * the "consumer" and "producer" protothreads declare their local
 * variables as static, to avoid them being stored on the stack.
 * 
 *
 */
   
/**
 * \file
 * Couting semaphores implemented on protothreads
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __PT_SEM_H__
#define __PT_SEM_H__

#include "pt.h"

struct pt_sem {
  unsigned int count;
};

/**
 * Initialize a semaphore
 *
 * This macro initializes a semaphore with a value for the
 * counter. Internally, the semaphores use an "unsigned int" to
 * represent the counter, and therefore the "count" argument should be
 * within range of an unsigned int.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \param c (unsigned int) The initial count of the semaphore.
 * \hideinitializer
 */
#define PT_SEM_INIT(s, c) (s)->count = c

/**
 * Wait for a semaphore
 *
 * This macro carries out the "wait" operation on the semaphore. The
 * wait operation causes the protothread to block while the counter is
 * zero. When the counter reaches a value larger than zero, the
 * protothread will continue.
 *
 * \param pt (struct pt *) A pointer to the protothread (struct pt) in
 * which the operation is executed.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define PT_SEM_WAIT(pt, s)	\
  do {						\
    PT_WAIT_UNTIL(pt, (s)->count > 0);		\
    --(s)->count;				\
  } while(0)

/**
 * Signal a semaphore
 *
 * This macro carries out the "signal" operation on the semaphore. The
 * signal operation increments the counter inside the semaphore, which
 * eventually will cause waiting protothreads to continue executing.
 *
 * \param pt (struct pt *) A pointer to the protothread (struct pt) in
 * which the operation is executed.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define PT_SEM_SIGNAL(pt, s) ++(s)->count

#endif /* __PT_SEM_H__ */

/** @} */
/** @} */
   
/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: pt.h,v 1.7 2006/10/02 07:52:56 adam Exp $
 */

/**
 * \addtogroup pt
 * @{
 */

/**
 * \file
 * Protothreads implementation.
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __PT_H__
#define __PT_H__

#include "lc.h"

struct pt {
  lc_t lc;
};

#define PT_WAITING 0
#define PT_YIELDED 1
#define PT_EXITED  2
#define PT_ENDED   3

/**
 * \name Initialization
 * @{
 */

/**
 * Initialize a protothread.
 *
 * Initializes a protothread. Initialization must be done prior to
 * starting to execute the protothread.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \sa PT_SPAWN()
 *
 * \hideinitializer
 */
#define PT_INIT(pt)   LC_INIT((pt)->lc)

/** @} */

/**
 * \name Declaration and definition
 * @{
 */

/**
 * Declaration of a protothread.
 *
 * This macro is used to declare a protothread. All protothreads must
 * be declared with this macro.
 *
 * \param name_args The name and arguments of the C function
 * implementing the protothread.
 *
 * \hideinitializer
 */
#define PT_THREAD(name_args) char name_args

/**
 * Declare the start of a protothread inside the C function
 * implementing the protothread.
 *
 * This macro is used to declare the starting point of a
 * protothread. It should be placed at the start of the function in
 * which the protothread runs. All C statements above the PT_BEGIN()
 * invokation will be executed each time the protothread is scheduled.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_BEGIN(pt) { char PT_YIELD_FLAG = 1; LC_RESUME((pt)->lc)

/**
 * Declare the end of a protothread.
 *
 * This macro is used for declaring that a protothread ends. It must
 * always be used together with a matching PT_BEGIN() macro.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_END(pt) LC_END((pt)->lc); PT_YIELD_FLAG = 0; \
                   PT_INIT(pt); return PT_ENDED; }

/** @} */

/**
 * \name Blocked wait
 * @{
 */

/**
 * Block and wait until condition is true.
 *
 * This macro blocks the protothread until the specified condition is
 * true.
 *
 * \param pt A pointer to the protothread control structure.
 * \param condition The condition.
 *
 * \hideinitializer
 */
#define PT_WAIT_UNTIL(pt, condition)	        \
  do {						\
    LC_SET((pt)->lc);				\
    if(!(condition)) {				\
      return PT_WAITING;			\
    }						\
  } while(0)

/**
 * Block and wait while condition is true.
 *
 * This function blocks and waits while condition is true. See
 * PT_WAIT_UNTIL().
 *
 * \param pt A pointer to the protothread control structure.
 * \param cond The condition.
 *
 * \hideinitializer
 */
#define PT_WAIT_WHILE(pt, cond)  PT_WAIT_UNTIL((pt), !(cond))

/** @} */

/**
 * \name Hierarchical protothreads
 * @{
 */

/**
 * Block and wait until a child protothread completes.
 *
 * This macro schedules a child protothread. The current protothread
 * will block until the child protothread completes.
 *
 * \note The child protothread must be manually initialized with the
 * PT_INIT() function before this function is used.
 *
 * \param pt A pointer to the protothread control structure.
 * \param thread The child protothread with arguments
 *
 * \sa PT_SPAWN()
 *
 * \hideinitializer
 */
#define PT_WAIT_THREAD(pt, thread) PT_WAIT_WHILE((pt), PT_SCHEDULE(thread))

/**
 * Spawn a child protothread and wait until it exits.
 *
 * This macro spawns a child protothread and waits until it exits. The
 * macro can only be used within a protothread.
 *
 * \param pt A pointer to the protothread control structure.
 * \param child A pointer to the child protothread's control structure.
 * \param thread The child protothread with arguments
 *
 * \hideinitializer
 */
#define PT_SPAWN(pt, child, thread)		\
  do {						\
    PT_INIT((child));				\
    PT_WAIT_THREAD((pt), (thread));		\
  } while(0)

/** @} */

/**
 * \name Exiting and restarting
 * @{
 */

/**
 * Restart the protothread.
 *
 * This macro will block and cause the running protothread to restart
 * its execution at the place of the PT_BEGIN() call.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_RESTART(pt)				\
  do {						\
    PT_INIT(pt);				\
    return PT_WAITING;			\
  } while(0)

/**
 * Exit the protothread.
 *
 * This macro causes the protothread to exit. If the protothread was
 * spawned by another protothread, the parent protothread will become
 * unblocked and can continue to run.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_EXIT(pt)				\
  do {						\
    PT_INIT(pt);				\
    return PT_EXITED;			\
  } while(0)

/** @} */

/**
 * \name Calling a protothread
 * @{
 */

/**
 * Schedule a protothread.
 *
 * This function shedules a protothread. The return value of the
 * function is non-zero if the protothread is running or zero if the
 * protothread has exited.
 *
 * \param f The call to the C function implementing the protothread to
 * be scheduled
 *
 * \hideinitializer
 */
#define PT_SCHEDULE(f) ((f) < PT_EXITED)

/** @} */

/**
 * \name Yielding from a protothread
 * @{
 */

/**
 * Yield from the current protothread.
 *
 * This function will yield the protothread, thereby allowing other
 * processing to take place in the system.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_YIELD(pt)				\
  do {						\
    PT_YIELD_FLAG = 0;				\
    LC_SET((pt)->lc);				\
    if(PT_YIELD_FLAG == 0) {			\
      return PT_YIELDED;			\
    }						\
  } while(0)

/**
 * \brief      Yield from the protothread until a condition occurs.
 * \param pt   A pointer to the protothread control structure.
 * \param cond The condition.
 *
 *             This function will yield the protothread, until the
 *             specified condition evaluates to true.
 *
 *
 * \hideinitializer
 */
#define PT_YIELD_UNTIL(pt, cond)		\
  do {						\
    PT_YIELD_FLAG = 0;				\
    LC_SET((pt)->lc);				\
    if((PT_YIELD_FLAG == 0) || !(cond)) {	\
      return PT_YIELDED;			\
    }						\
  } while(0)

/** @} */

#endif /* __PT_H__ */

/** @} */
#ifndef SD_H
#define SD_H

#include <string.h>

#include "pfatfs/diskio.h"
#include "pfatfs/pff.h"
#include "spi.h"

#include "graphics.h"

enum {
  SD_INIT_SUCCESS = 0,
  SD_INIT_FAILURE,
  SD_INIT_FAIL_INIT,
  SD_INIT_FAIL_MOUNT,
};

uint8_t sd_init(void) __attribute__((section(".boot")));
FRESULT sd_scan_files (char* path) __attribute__((section(".boot")));
#endif
#ifndef _SPI_H
#define _SPI_H

#include <stdint.h>
#include <avr/io.h>
#include "HAL/board.h"


typedef enum {
  SPI_LSB_FIRST = 1,
  SPI_MSB_FIRST = 0
} spi_endianness_t;
typedef enum {
  SPI_BUSMODE_SLAVE = 0,
  SPI_BUSMODE_MASTER = 1,
} spi_bus_mode_t;
typedef enum {
  SPI_MODE_0 = 0,
  SPI_MODE_1 = 1,
  SPI_MODE_2 = 2,
  SPI_MODE_3 = 3,
} spi_trans_mode_t;
typedef enum {
  SPI_CLOCKDIV_4 = 0,
  SPI_CLOCKDIV_16 = 1,
  SPI_CLOCKDIV_64 = 2,
  SPI_CLOCKDIV_128 = 3,
} spi_clock_rate_t;
typedef enum  {
  SPI_DBLCLK_DISABLE = 0,
  SPI_DBLCLK_ENABLE = 1,
} spi_double_clock_t;

typedef
union {
  struct __attribute__ ((packed)) {
    spi_endianness_t endianness : 1;
    spi_bus_mode_t bus_mode : 1;
    spi_trans_mode_t trans_mode : 2;
    spi_clock_rate_t clock_rate : 2;
    spi_double_clock_t double_clock : 1;
  };
  uint8_t intRep;
} spi_setting_t;

void spi_init(spi_setting_t* settings);

uint8_t spi_send(uint8_t value);

#endif
#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>
volatile uint32_t global_tick;


void systick_init();
#endif
#ifndef TERMINAL_H
#define TERMINAL_H

#include "stdint.h"

#include "buffer.h"
#include "font.h"

#include <avr/pgmspace.h>

// todo: add function pointer to read and write characters to term (for FRAM)
typedef struct {
  uint8_t scroll_x;   // scroll windows top position (in rows)
  uint8_t rows;       // maximum number of character rows
  uint8_t width;      // maximum characters per row
  uint8_t view_rows;  // number of rows to render from scroll position
  uint8_t cursor_x;   // character cursor position in current row
  uint8_t cursor_y;   // current row of character cursor
  char* buffer;       // storage space for term buffer
} terminal_t;

terminal_t* term_redirected;

terminal_t term_init(uint8_t width, uint8_t height);

void term_putchar(terminal_t* term, char c);
void term_redirect_putchar(terminal_t* term);
void term_puts(terminal_t* term, const char* str);
void term_puts_P(terminal_t* term, PGM_P str);
void term_draw(terminal_t* term);
void term_set_cursor(terminal_t* term, uint8_t cur_x, uint8_t cur_y);
void term_clear(terminal_t* term);
#endif
#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include <stdio.h>

#include "config.h"

void flash_app(char* path) __attribute__((section(".boot")));

#endif
#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "lcd.h"  // for display size constants
#define SD_BUFFER_SIZE 256

#define FRAME_BUFFER_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT / 8)

#define FLASH_BUFFER_SIZE SPM_PAGESIZE
typedef union {
#ifdef GRAPHICS_USE_SRAM
  volatile uint8_t fb[FRAME_BUFFER_SIZE];
#endif
#ifdef GRAPHICS_USE_FRAM
  volatile uint8_t pagebuffer[DISPLAY_WIDTH];
#endif
  volatile uint8_t sd[SD_BUFFER_SIZE];
  volatile uint8_t flash_page[FLASH_BUFFER_SIZE];
} buffer_t;
volatile buffer_t buffer; // instantiate buffer in SRAM


// buffer location in FRAM
#define FRAM_FB_START   0x00
#define FRAM_FB_END     (FRAM_FB_START + FRAME_BUFFER_SIZE)

#ifdef GRAPHICS_USE_SRAM
  #define BUFFER_SET_BYTE(addr, b) (buffer.fb[(addr)] = (b))
  #define BUFFER_GET_BYTE(addr) (buffer.fb[(addr)])
#endif

#ifdef GRAPHICS_USE_FRAM
  #define BUFFER_SET_BYTE(addr, b) (fram_write_byte(FRAM_FB_START + (addr), (b)))
  #define BUFFER_GET_BYTE(addr) (fram_read_byte(FRAM_FB_START + (addr)))
#endif


#endif
#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include "HAL/board.h"

/* hardware abstractions */
#define BTN_DIR_MASK    (BTN_UP_PIN | BTN_DOWN_PIN | BTN_LEFT_PIN | BTN_RIGHT_PIN)
#define BTN_INPUT_MASK  (BTN_A_PIN | BTN_B_PIN)


#define BTN_FLAG_BITPOS 7
/* software-only representation - matches with hardware*/
typedef enum {
  BTN_A             = BTN_A_PIN,
  BTN_B             = BTN_B_PIN,
  BTN_UP            = BTN_UP_PIN,
  BTN_DOWN          = BTN_UP_PIN,
  BTN_LEFT          = BTN_LEFT_PIN,
  BTN_RIGHT         = BTN_RIGHT_PIN,
  BTN_FLAG_POLLING  = _BV(BTN_FLAG_BITPOS)
} button_t;

#define BTN_ALL_MASK (BTN_A | BTN_B | BTN_UP | BTN_DOWN | BTN_LEFT | BTN_RIGHT)
typedef uint8_t btn_state_t;


uint8_t buttons_isset(button_t button_mask);
void buttons_init(void);
void buttons_poll(void);
#endif
#ifndef CONFIG_H
#define CONFIG_H

#define APP_FILENAME "alice.txt"

#define APP_START_ADDR 0
#define APP_END_ADDR 8192

//#define GRAPHICS_USE_SRAM
#define GRAPHICS_USE_FRAM

#endif
#ifndef DEBUG_H
#define DEBUG_H

#define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2*!!(condition)]))

#endif
#ifndef _FONT_H
#define _FONT_H

/* typedef struct {
  const char first_ascii;
  const uint8_t num_glyphs;
  const uint8_t width_px;
  const uint8_t height_px;
  const uint8_t font_data[];
} font_t; */
#include <stdint.h>
/* defines global "font" variable */
//#include "fonts/font_5x7.h"
#include "fonts/font_BMplain.h"
const uint8_t* font_data;

#endif
#ifndef _FONT_5X7_H
#define _FONT_5X7_H

#include "../font.h"
#include <avr/pgmspace.h>
#include <stdint.h>

/*#define FONT_FIRST_ASCII  ' '   // first ASCII point
#define FONT_LAST_ASCII   '}'   // number of ASCII characters covered from point
#define FONT_GLYPH_WIDTH  5     // glyph width in px
#define FONT_GLYPH_HEIGHT 7     // glyph height in px
*/
#endif
#ifndef _FONT_BMPLAIN_H
#define _FONT_BMPLAIN_H

#include "../font.h"
#include <avr/pgmspace.h>
#include <stdint.h>

#define FONT_FIRST_ASCII  ' '   // first ASCII point
#define FONT_LAST_ASCII   '~'   // number of ASCII characters covered from point
#define FONT_GLYPH_WIDTH  6     // glyph width in px
#define FONT_GLYPH_HEIGHT 8     // glyph height in px

#endif
#ifndef FRAM_H
#define FRAM_H

#include <stdint.h>

void fram_init();

uint8_t fram_read_byte(uint16_t addr);
void fram_write_byte(uint16_t addr, uint8_t c);

void fram_read_n_bytes(uint16_t start_addr, uint16_t n, uint8_t* buff);
void fram_write_n_bytes(uint16_t start_addr, uint16_t n, uint8_t* buff);

void fram_clear_n_bytes(uint16_t start_addr, uint16_t n);

uint8_t fram_read_status();

#endif
#ifndef _GRAPHICS_H
#define _GRAPHICS_H

//#include "lcd.h"
#include "font.h"
#include "buffer.h"
#include "terminal.h"
#include "stdlib.h"
#include "lcd.h"
/*FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);
stdout = &uart_output;
stdin  = &uart_input;*/
#define TERM_WIDTH_PX   DISPLAY_WIDTH
#define TERM_HEIGHT_PX  DISPLAY_HEIGHT
#define TERM_ROWS       (TERM_HEIGHT_PX / FONT_HEIGHT)
#define TERM_COLS       (TERM_WIDTH_PX /  (FONT_WIDTH + 1))



void gfx_draw_point(uint8_t x, uint8_t y);
void gfx_draw_char(uint8_t x, uint8_t line, char c);
void gfx_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void gfx_putchar(char c);
void gfx_draw_term(terminal_t* term);
void gfx_draw_string(uint8_t x, uint8_t line, const char* str);

#endif
#ifndef ADC_H
#define ADC_H

#define BAT_ADC_PIN PA1
#define BAT_CONF_INPUT() do{DDRA &= ~_BV(BAT_ADC_PIN);} while(0)
#define
#endif
#ifndef BOARD_H
#define BOARD_H

#include "led_hardware.h"
#include "lcd_hardware.h"
#include "button_hardware.h"
#include "spi_hardware.h"
#include "timer_hardware.h"
#include "fram_hardware.h"
#include "sd_hardware.h"

#endif
#ifndef BUTTON_HARDWARE_H
#define BUTTON_HARDWARE_H

#define BTN_INPUT_PORT PORTD
#define BTN_INPUT_PORTIN PIND
#define BTN_INPUT_DDR DDRD

#define BTN_DIR_PORT PORTB
#define BTN_DIR_PORTIN PINB
#define BTN_DIR_DDR DDRB

#include <avr/io.h>

/* typesafe hardware pin mapping */
enum {
  BTN_A_PIN     = _BV(6),
  BTN_B_PIN     = _BV(5),
  BTN_UP_PIN    = _BV(1),
  BTN_DOWN_PIN  = _BV(2),
  BTN_LEFT_PIN  = _BV(0),
  BTN_RIGHT_PIN = _BV(3),
} button_pin;

#endif
#ifndef FRAM_HARDWARE_H
#define FRAM_HARDWARE_H

#define FRAM_PORT PORTB
#define FRAM_DDR  DDRB

#define FRAM_CS_PIN PB4

#define FRAM_SIZE_BYTES 2048

#define FRAM_PORT_INIT()          (FRAM_DDR |= _BV(FRAM_CS_PIN))
#define FRAM_CS_DEACTIVATE()      (FRAM_PORT |= _BV(FRAM_CS_PIN))
#define FRAM_CS_ACTIVATE()        (FRAM_PORT &= ~(_BV(FRAM_CS_PIN)))

// opcodes
#define FRAM_WRITE_ENABLE   (0b00000110)
#define FRAM_WRITE_DISABLE  (0b00000100)
#define FRAM_READ_STATUS    (0b00000101)
#define FRAM_WRITE_STATUS   (0b00000001)
#define FRAM_READ_MEMORY    (0b00000011)
#define FRAM_WRITE_MEMORY   (0b00000010)

// status register bits
#define FRAM_STATUS_WEL   _BV(1)
#define FRAM_STATUS_BP0   _BV(2)
#define FRAM_STATUS_BP1   _BV(3)
#define FRAM_STATUS_WPEN  _BV(7)


#define FRAM_MSB_MASK       (0b00011111)

#define FRAM_DUMMY_PACKET   0x00

#endif
#ifndef LCD_HARDWARE_H
#define LCD_HARDWARE_H


/* select appropriate LCD controller */
//#include "PCD8544.h"
#include "UC1701.h"

#endif
#ifndef LED_HARDWARE_H
#define LED_HARDWARE_H

#define USER_LED_PORT PORTC
#define USER_LED_DDR  DDRC
#define USER_LED_PIN  PC6

#define BACKLIGHT_LED_PORT  PORTD
#define BACKLIGHT_LED_DDR   DDRD
#define BACKLIGHT_LED_PIN   PD4

#endif
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
#ifndef SD_HARDWARE_H
#define SD_HARDWARE_H

#define SD_PORT PORTA
#define SD_DDR  DDRA

#define SD_CS_PIN PA0


#define SD_PORT_INIT()          (SD_DDR |= _BV(SD_CS_PIN))
#define SD_CS_DEACTIVATE()      (SD_PORT |= _BV(SD_CS_PIN))
#define SD_CS_ACTIVATE()        (SD_PORT &= ~(_BV(SD_CS_PIN)))

#endif
#ifndef SPI_HARDWARE_H
#define SPI_HARDWARE_H

#include <avr/io.h>


#define SPI_PORT  PORTB
#define SPI_PIN   PINB
#define SPI_DDR   DDRB

#define SPI_MOSI_PIN  PB5
#define SPI_MISO_PIN  PB6
#define SPI_SCK_PIN   PB7

#define SPI_LSBFIRST_MASK   0b00000001
#define SPI_MASTER_MASK     0b00000001
#define SPI_MODE_MASK       0b00000011
#define SPI_SPEED_MASK      0b00000011
#define SPI_DBLCLK_MASK     0b00000001

#define SPI_SCK_LOW()   (SPI_PORT &= ~(_BV(SPI_SCK_PIN)))
#define SPI_SCK_HIGH()  (SPI_PORT |= (_BV(SPI_SCK_PIN)))



#endif
#ifndef TIMER_HARDWARE_H
#define TIMER_HARDWARE_H

/* TCCR0 */


#define TIMER0_CLK_SHIFT    0x02
#define TIMER0_CLK_DIV_STOP 0x00
#define TIMER0_CLK_DIV_1    0x01
#define TIMER0_CLK_DIV_8    0x02
#define TIMER0_CLK_DIV_64   0x03
#define TIMER0_CLK_DIV_256  0x04
#define TIMER0_CLK_DIV_1024 0x05

/* TIMSK */
#define TIMER0_COMP_MATCH_INT 0x01
#define TIMER0_OVERFLOW_INT   0x00

/* TIFR */
#define TIMER0_OUT_COMP_FLAG  0x01
#define TIMER0_OVERFLOW_FLAG  0x01

/* SFIOR */
#define TIMER0_PRESCALE_RST   0x00

#endif
#ifndef UC1701_H
#define UC1701_H

#ifdef _LCD_DRIVER
#error LCD controller already selected. Can only have one controller in use.
#else
#define LCD_CONTROLLER UC1701
#endif

/* control registers */

#define UC1701_SL
#define UC1701_STATUS_BZ            _BV(7)
#define UC1701_STATUS_MX            _BV(6)
#define UC1701_STATUS_DE            _BV(5)
#define UC1701_STATUS_RST           _BV(4)

#define UC1701_SET_COL_ADDR_LSB     (0b00000000)
#define UC1701_SET_COL_ADDR_MSB     (0b00010000)
#define UC1701_SET_COL_MASK         (0b00001111)

#define UC1701_SET_POWER_CTRL       (0b00101000)
#define UC1701_SET_POWER_BOOST_ON   (0b00000001)
#define UC1701_SET_POWER_BOOST_OFF  (0b00000000)
#define UC1701_SET_POWER_REG_ON     (0b00000010)
#define UC1701_SET_POWER_REG_OFF    (0b00000000)
#define UC1701_SET_POWER_FOLL_ON    (0b00000100)
#define UC1701_SET_POWER_FOLL_OFF   (0b00000000)

#define UC1701_SET_SCROLL_LINE      (0b01000000)
#define UC1701_SET_SCROLL_MASK      (0b00111111)

#define UC1701_SET_PAGE_ADDR        (0b10110000)
#define UV1701_SET_PAGE_MASK        (0b00001111)

#define UC1701_SET_VLCD_RATIO       (0b00100000)
#define UC1701_SET_VLCD_DEFAULT     (0b00000111)
#define UC1701_SET_VLCD_MASK        (0b00000111)

/* two byte command */
/* default value: 32 */
#define UC1701_SET_EL_VOL_1         (0b10000001)
#define UC1701_SET_EL_VOL_2         (0b00000000)
#define UC1701_SET_EL_VOL_MASK      (0b00111111)

#define UC1701_SET_ALL_PX           (0b10100100)
#define UC1701_SET_ALL_ON           (0b00000001)
#define UC1701_SET_ALL_OFF          (0b00000000)

#define UC1701_SET_INV_DISP         (0b10100110)
#define UC1701_SET_INV_DISP_ON      (0b00000001)
#define UC1701_SET_INV_DISP_OFF     (0b00000000)

#define UC1701_SET_DISP_EN          (0b10101110)
#define UC1701_SET_DISP_EN_ON       (0b00000001)
#define UC1701_SET_DISP_EN_OFF      (0b00000000)

#define UC1701_SET_SEG_DIR          (0b10100000)
#define UC1701_SET_SEG_DIR_NORM     (0b00000000)
#define UC1701_SET_SEG_DIR_MIRROR   (0b00000001)

#define UC1701_SET_COM_DIR          (0b11000000)
#define UC1701_SET_COM_DIR_NORM     (0b00000000)
#define UC1701_SET_COM_DIR_MIRROR   (0b00001000)

#define UC1701_SYS_RESET            (0b11100010)

/* varies according to duty */
/*
Default: 0
DUTY | BR = 0 | BR = 1
----------------------
1/65*|   1/9  |  1/7
1/49 |   1/8  |  1/6
1/33 |   1/6  |  1/5
1/55 |   1/8  |  1/6
*/

#define UC1701_SET_BIAS_RATIO       (0b10100010)
#define UC1701_SET_BIAS_1_7         (0b00000001)
#define UC1701_SET_BIAS_1_9         (0b00000000)

#define UC1701_NOP                  (0b11100011)

#define UC1701_SET_CUR_MODE         (0b11100000)
#define UC1701_RESET_CUR_MODE       (0b11101110)

#define UC1701_SET_STAT_IND_OFF     (0b10101100)
/* two byte command, 2nd byte is don't-care */
#define UC1701_SET_STAT_IND_OFF_2   (0b10101101)

#define UC1701_SET_BOOST_1          (0b11111000)
#define UC1701_SET_BOOST_2          (0b00000000)

/* two byte command */

#define UC1701_SET_ADV_PROG_1       (0b11111010)
#define UC1701_SET_ADV_PROG_2       (0b00010000)
#define UC1701_ADV_PROG_WRAP_COL    (0b00000010)
#define UC1701_ADV_PROG_WRAP_ROW    (0b00000001)
#define UC1701_ADV_PROG_TEMPCO_0    (0b00000000)
#define UC1701_ADV_PROG_TEMPCO_1    (0b10000000)

/* compound command */
#define UC1701_SET_POWER_SAVE       (0b00000000)

#define UC1701_NUM_PAGES 8
#define UC1701_PAGE_BIT_SIZE 8

#define DISPLAY_WIDTH 102
#define DISPLAY_HEIGHT UC1701_NUM_PAGES * UC1701_PAGE_BIT_SIZE




#endif
#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "spi.h"
#include "HAL/board.h"
#include "buffer.h"

#define LCD_CONTRAST 16
/* standard interface that all LCD controllers must implement */
void lcd_init(void);
void lcd_fill(void);
void lcd_clear_buffer(void);
#endif
#ifndef LED_H
#define LED_H

#include "HAL/board.h"

#define USER_LED_INIT()   do{USER_LED_DDR  |=   _BV(USER_LED_PIN); USER_LED_PORT |= _BV(USER_LED_PIN);}while(0)
#define USER_LED_OFF()    do{USER_LED_PORT |=   _BV(USER_LED_PIN);}while(0)
#define USER_LED_ON()     do{USER_LED_PORT &=  ~_BV(USER_LED_PIN);}while(0)
#define USER_LED_TOGGLE() do{USER_LED_PORT ^=   _BV(USER_LED_PIN);}while(0)


#define BACKLIGHT_LED_INIT()    do{BACKLIGHT_LED_DDR  |=  _BV(BACKLIGHT_LED_PIN); BACKLIGHT_LED_PORT &= ~_BV(BACKLIGHT_LED_PIN);}while(0)
#define BACKLIGHT_LED_ON()      do{BACKLIGHT_LED_PORT |=  _BV(BACKLIGHT_LED_PIN);}while(0)
#define BACKLIGHT_LED_OFF()     do{BACKLIGHT_LED_PORT &= ~_BV(BACKLIGHT_LED_PIN);}while(0)
#define BACKLIGHT_LED_TOGGLE()  do{BACKLIGHT_LED_PORT ^=  _BV(BACKLIGHT_LED_PIN);}while(0)

#define BACKLIGHT_PWM_MODE      (_BV(WGM20) | _BV(WGM21))   // fast PWM
#define BACKLIGHT_PWM_OUTMODE   (_BV(COM21) | _BV(COM20))   // inverted output
#define BACKLIGHT_PWM_CLOCK     (_BV(CS20)) // F_CPU / 2
#define BACKLIGHT_PWM_LEVEL     OCR2
// initialise backlight and set to half brightness
#define BACKLIGHT_LED_PWM_INIT() do{TCCR2 |= (BACKLIGHT_PWM_MODE | BACKLIGHT_PWM_OUTMODE | BACKLIGHT_PWM_CLOCK); BACKLIGHT_PWM_LEVEL = 196;} while(0)

void led_init(void);
void led_user_on(void);
void led_user_off(void);
void led_user_toggle(void);
void led_backlight_on(void);
void led_backlight_off(void);
void led_backlight_on(void);
void led_backlight_level(uint8_t level);

#endif
/*-----------------------------------------------------------------------
/  PFF - Low level disk interface modlue include file    (C)ChaN, 2009
/-----------------------------------------------------------------------*/

#ifndef _DISKIO

#include "integer.h"


/* Status of Disk Functions */
typedef BYTE	DSTATUS;


/* Results of Disk Functions */
typedef enum {
	RES_OK = 0,		/* 0: Function succeeded */
	RES_ERROR,		/* 1: Disk error */
	RES_NOTRDY,		/* 2: Not ready */
	RES_PARERR		/* 3: Invalid parameter */
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */

DSTATUS disk_initialize (void)
__attribute__((section(".library"), used));
DRESULT disk_readp (BYTE*, DWORD, WORD, WORD)
__attribute__((section(".library"), used));
DRESULT disk_writep (const BYTE*, DWORD)
__attribute__((section(".library"), used));

#define STA_NOINIT		0x01	/* Drive not initialized */
#define STA_NODISK		0x02	/* No medium in the drive */

/* Card type flags (CardType) */
#define CT_MMC				0x01	/* MMC ver 3 */
#define CT_SD1				0x02	/* SD ver 1 */
#define CT_SD2				0x04	/* SD ver 2 */
#define CT_SDC				(CT_SD1|CT_SD2)	/* SD */
#define CT_BLOCK			0x08	/* Block addressing */

#define _DISKIO
#endif
/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _INTEGER
#define _INTEGER

#ifdef _WIN32	/* FatFs development platform */

#include <windows.h>
#include <tchar.h>

#else			/* Embedded platform */
#include <stdint.h>
/* These types must be 16-bit, 32-bit or larger integer */
typedef int				INT;
typedef unsigned int	UINT;

/* These types must be 8-bit integer */
typedef int8_t  CHAR;
typedef uint8_t	UCHAR;
typedef uint8_t	BYTE;

/* These types must be 16-bit integer */
typedef int16_t			SHORT;
typedef uint16_t	USHORT;
typedef uint16_t	WORD;
typedef uint16_t	WCHAR;

/* These types must be 32-bit integer */
typedef long			    LONG;
typedef unsigned long	ULONG;
typedef unsigned long	DWORD;

#endif

#endif
/*---------------------------------------------------------------------------/
/  Petit FatFs - FAT file system module include file  R0.02a   (C)ChaN, 2010
/----------------------------------------------------------------------------/
/ Petit FatFs module is an open source software to implement FAT file system to
/ small embedded systems. This is a free software and is opened for education,
/ research and commercial developments under license policy of following trems.
/
/  Copyright (C) 2010, ChaN, all right reserved.
/
/ * The Petit FatFs module is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial use UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.
/
/----------------------------------------------------------------------------*/

#include "integer.h"

/*---------------------------------------------------------------------------/
/ Petit FatFs Configuration Options
/
/ CAUTION! Do not forget to make clean the project after any changes to
/ the configuration options.
/
/----------------------------------------------------------------------------*/
#ifndef _FATFS
#define _FATFS

#define	_USE_READ	1	/* 1:Enable pf_read() */

#define	_USE_DIR	1	/* 1:Enable pf_opendir() and pf_readdir() */

#define	_USE_LSEEK	0	/* 1:Enable pf_lseek() */

#define	_USE_WRITE	0	/* 1:Enable pf_write() */

#define _FS_FAT12	0	/* 1:Enable FAT12 support */
#define _FS_FAT32	1	/* 1:Enable FAT32 support */


#define	_CODE_PAGE	1
/* Defines which code page is used for path name. Supported code pages are:
/  932, 936, 949, 950, 437, 720, 737, 775, 850, 852, 855, 857, 858, 862, 866,
/  874, 1250, 1251, 1252, 1253, 1254, 1255, 1257, 1258 and 1 (ASCII only).
/  SBCS code pages except for 1 requiers a case conversion table. This
/  might occupy 128 bytes on the RAM on some platforms, e.g. avr-gcc. */


#define _WORD_ACCESS	0
/* The _WORD_ACCESS option defines which access method is used to the word
/  data in the FAT structure.
/
/   0: Byte-by-byte access. Always compatible with all platforms.
/   1: Word access. Do not choose this unless following condition is met.
/
/  When the byte order on the memory is big-endian or address miss-aligned
/  word access results incorrect behavior, the _WORD_ACCESS must be set to 0.
/  If it is not the case, the value can also be set to 1 to improve the
/  performance and code efficiency. */


/* End of configuration options. Do not change followings without care.     */
/*--------------------------------------------------------------------------*/



#if _FS_FAT32
#define	CLUST	DWORD
#else
#define	CLUST	WORD
#endif


/* File system object structure */

typedef struct {
	BYTE	fs_type;	/* FAT sub type */
	BYTE	flag;		/* File status flags */
	BYTE	csize;		/* Number of sectors per cluster */
	BYTE	pad1;
	WORD	n_rootdir;	/* Number of root directory entries (0 on FAT32) */
	CLUST	n_fatent;	/* Number of FAT entries (= number of clusters + 2) */
	DWORD	fatbase;	/* FAT start sector */
	DWORD	dirbase;	/* Root directory start sector (Cluster# on FAT32) */
	DWORD	database;	/* Data start sector */
	DWORD	fptr;		/* File R/W pointer */
	DWORD	fsize;		/* File size */
	CLUST	org_clust;	/* File start cluster */
	CLUST	curr_clust;	/* File current cluster */
	DWORD	dsect;		/* File current data sector */
} FATFS;



/* Directory object structure */

typedef struct {
	WORD	index;		/* Current read/write index number */
	BYTE*	fn;			/* Pointer to the SFN (in/out) {file[8],ext[3],status[1]} */
	CLUST	sclust;		/* Table start cluster (0:Static table) */
	CLUST	clust;		/* Current cluster */
	DWORD	sect;		/* Current sector */
} DIR;



/* File status structure */

typedef struct {
	DWORD	fsize;		/* File size */
	WORD	fdate;		/* Last modified date */
	WORD	ftime;		/* Last modified time */
	BYTE	fattrib;	/* Attribute */
	char	fname[13];	/* File name */
} FILINFO;



/* File function return code (FRESULT) */

typedef enum {
	FR_OK = 0,			/* 0 */
	FR_DISK_ERR,		/* 1 */
	FR_NOT_READY,		/* 2 */
	FR_NO_FILE,			/* 3 */
	FR_NO_PATH,			/* 4 */
	FR_NOT_OPENED,		/* 5 */
	FR_NOT_ENABLED,		/* 6 */
	FR_NO_FILESYSTEM	/* 7 */
} FRESULT;



/*--------------------------------------------------------------*/
/* Petit FatFs module application interface                     */

FRESULT pf_mount (FATFS*)
__attribute__((section(".library"), used));						/* Mount/Unmount a logical drive */
FRESULT pf_open (const char*)
__attribute__((section(".library"), used));					/* Open a file */
FRESULT pf_read (void*, WORD, WORD*)
__attribute__((section(".library"), used));			/* Read data from the open file */
FRESULT pf_write (const void*, WORD, WORD*)
__attribute__((section(".library"), used));	/* Write data to the open file */
FRESULT pf_lseek (DWORD)
__attribute__((section(".library"), used));						/* Move file pointer of the open file */
FRESULT pf_opendir (DIR*, const char*)
__attribute__((section(".library"), used));			/* Open a directory */
FRESULT pf_readdir (DIR*, FILINFO*)
__attribute__((section(".library"), used));			/* Read a directory item from the open directory */



/*--------------------------------------------------------------*/
/* Flags and offset address                                     */

/* File status flag (FATFS.flag) */

#define	FA_OPENED	0x01
#define	FA_WPRT		0x02
#define	FA__WIP		0x40


/* FAT sub type (FATFS.fs_type) */

#define FS_FAT12	1
#define FS_FAT16	2
#define FS_FAT32	3


/* File attribute bits for directory entry */

#define	AM_RDO	0x01	/* Read only */
#define	AM_HID	0x02	/* Hidden */
#define	AM_SYS	0x04	/* System */
#define	AM_VOL	0x08	/* Volume label */
#define AM_LFN	0x0F	/* LFN entry */
#define AM_DIR	0x10	/* Directory */
#define AM_ARC	0x20	/* Archive */
#define AM_MASK	0x3F	/* Mask of defined bits */


/*--------------------------------*/
/* Multi-byte word access macros  */

#if _WORD_ACCESS == 1	/* Enable word access to the FAT structure */
#define	LD_WORD(ptr)		(WORD)(*(WORD*)(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(*(DWORD*)(BYTE*)(ptr))
#define	ST_WORD(ptr,val)	*(WORD*)(BYTE*)(ptr)=(WORD)(val)
#define	ST_DWORD(ptr,val)	*(DWORD*)(BYTE*)(ptr)=(DWORD)(val)
#else					/* Use byte-by-byte access to the FAT structure */
#define	LD_WORD(ptr)		(WORD)(((WORD)*((BYTE*)(ptr)+1)<<8)|(WORD)*(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(((DWORD)*((BYTE*)(ptr)+3)<<24)|((DWORD)*((BYTE*)(ptr)+2)<<16)|((WORD)*((BYTE*)(ptr)+1)<<8)|*(BYTE*)(ptr))
#define	ST_WORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8)
#define	ST_DWORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8); *((BYTE*)(ptr)+2)=(BYTE)((DWORD)(val)>>16); *((BYTE*)(ptr)+3)=(BYTE)((DWORD)(val)>>24)
#endif


#endif /* _FATFS */
/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: lc-addrlabels.h,v 1.4 2006/06/03 11:29:43 adam Exp $
 */

/**
 * \addtogroup lc
 * @{
 */

/**
 * \file
 * Implementation of local continuations based on the "Labels as
 * values" feature of gcc
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 * This implementation of local continuations is based on a special
 * feature of the GCC C compiler called "labels as values". This
 * feature allows assigning pointers with the address of the code
 * corresponding to a particular C label.
 *
 * For more information, see the GCC documentation:
 * http://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
 *
 */

#ifndef __LC_ADDRLABELS_H__
#define __LC_ADDRLABELS_H__

/** \hideinitializer */
typedef void * lc_t;

#define LC_INIT(s) s = NULL

#define LC_RESUME(s)				\
  do {						\
    if(s != NULL) {				\
      goto *s;					\
    }						\
  } while(0)

#define LC_CONCAT2(s1, s2) s1##s2
#define LC_CONCAT(s1, s2) LC_CONCAT2(s1, s2)

#define LC_SET(s)				\
  do {						\
    LC_CONCAT(LC_LABEL, __LINE__):   	        \
    (s) = &&LC_CONCAT(LC_LABEL, __LINE__);	\
  } while(0)

#define LC_END(s)

#endif /* __LC_ADDRLABELS_H__ */
/** @} */
/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: lc-switch.h,v 1.4 2006/06/03 11:29:43 adam Exp $
 */

/**
 * \addtogroup lc
 * @{
 */

/**
 * \file
 * Implementation of local continuations based on switch() statment
 * \author Adam Dunkels <adam@sics.se>
 *
 * This implementation of local continuations uses the C switch()
 * statement to resume execution of a function somewhere inside the
 * function's body. The implementation is based on the fact that
 * switch() statements are able to jump directly into the bodies of
 * control structures such as if() or while() statmenets.
 *
 * This implementation borrows heavily from Simon Tatham's coroutines
 * implementation in C:
 * http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
 */

#ifndef __LC_SWITCH_H__
#define __LC_SWITCH_H__

/* WARNING! lc implementation using switch() does not work if an
   LC_SET() is done within another switch() statement! */

/** \hideinitializer */
typedef unsigned short lc_t;

#define LC_INIT(s) s = 0;

#define LC_RESUME(s) switch(s) { case 0:

#define LC_SET(s) s = __LINE__; case __LINE__:

#define LC_END(s) }

#endif /* __LC_SWITCH_H__ */

/** @} */
/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the protothreads library.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: lc.h,v 1.2 2005/02/24 10:36:59 adam Exp $
 */

/**
 * \addtogroup pt
 * @{
 */

/**
 * \defgroup lc Local continuations
 * @{
 *
 * Local continuations form the basis for implementing protothreads. A
 * local continuation can be <i>set</i> in a specific function to
 * capture the state of the function. After a local continuation has
 * been set can be <i>resumed</i> in order to restore the state of the
 * function at the point where the local continuation was set.
 *
 *
 */

/**
 * \file lc.h
 * Local continuations
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifdef DOXYGEN
/**
 * Initialize a local continuation.
 *
 * This operation initializes the local continuation, thereby
 * unsetting any previously set continuation state.
 *
 * \hideinitializer
 */
#define LC_INIT(lc)

/**
 * Set a local continuation.
 *
 * The set operation saves the state of the function at the point
 * where the operation is executed. As far as the set operation is
 * concerned, the state of the function does <b>not</b> include the
 * call-stack or local (automatic) variables, but only the program
 * counter and such CPU registers that needs to be saved.
 *
 * \hideinitializer
 */
#define LC_SET(lc)

/**
 * Resume a local continuation.
 *
 * The resume operation resumes a previously set local continuation, thus
 * restoring the state in which the function was when the local
 * continuation was set. If the local continuation has not been
 * previously set, the resume operation does nothing.
 *
 * \hideinitializer
 */
#define LC_RESUME(lc)

/**
 * Mark the end of local continuation usage.
 *
 * The end operation signifies that local continuations should not be
 * used any more in the function. This operation is not needed for
 * most implementations of local continuation, but is required by a
 * few implementations.
 *
 * \hideinitializer 
 */
#define LC_END(lc)

/**
 * \var typedef lc_t;
 *
 * The local continuation type.
 *
 * \hideinitializer
 */
#endif /* DOXYGEN */

#ifndef __LC_H__
#define __LC_H__


#ifdef LC_INCLUDE
#include LC_INCLUDE
#else
#include "lc-switch.h"
#endif /* LC_INCLUDE */

#endif /* __LC_H__ */

/** @} */
/** @} */
/*
 * Copyright (c) 2004, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the protothreads library.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: pt-sem.h,v 1.2 2005/02/24 10:36:59 adam Exp $
 */

/**
 * \addtogroup pt
 * @{
 */

/**
 * \defgroup ptsem Protothread semaphores
 * @{
 *
 * This module implements counting semaphores on top of
 * protothreads. Semaphores are a synchronization primitive that
 * provide two operations: "wait" and "signal". The "wait" operation
 * checks the semaphore counter and blocks the thread if the counter
 * is zero. The "signal" operation increases the semaphore counter but
 * does not block. If another thread has blocked waiting for the
 * semaphore that is signalled, the blocked thread will become
 * runnable again.
 *
 * Semaphores can be used to implement other, more structured,
 * synchronization primitives such as monitors and message
 * queues/bounded buffers (see below).
 *
 * The following example shows how the producer-consumer problem, also
 * known as the bounded buffer problem, can be solved using
 * protothreads and semaphores. Notes on the program follow after the
 * example.
 *
 \code
#include "pt-sem.h"

#define NUM_ITEMS 32
#define BUFSIZE 8

static struct pt_sem mutex, full, empty;

PT_THREAD(producer(struct pt *pt))
{
  static int produced;
  
  PT_BEGIN(pt);
  
  for(produced = 0; produced < NUM_ITEMS; ++produced) {
  
    PT_SEM_WAIT(pt, &full);
    
    PT_SEM_WAIT(pt, &mutex);
    add_to_buffer(produce_item());    
    PT_SEM_SIGNAL(pt, &mutex);
    
    PT_SEM_SIGNAL(pt, &empty);
  }

  PT_END(pt);
}

PT_THREAD(consumer(struct pt *pt))
{
  static int consumed;
  
  PT_BEGIN(pt);

  for(consumed = 0; consumed < NUM_ITEMS; ++consumed) {
    
    PT_SEM_WAIT(pt, &empty);
    
    PT_SEM_WAIT(pt, &mutex);    
    consume_item(get_from_buffer());    
    PT_SEM_SIGNAL(pt, &mutex);
    
    PT_SEM_SIGNAL(pt, &full);
  }

  PT_END(pt);
}

PT_THREAD(driver_thread(struct pt *pt))
{
  static struct pt pt_producer, pt_consumer;

  PT_BEGIN(pt);
  
  PT_SEM_INIT(&empty, 0);
  PT_SEM_INIT(&full, BUFSIZE);
  PT_SEM_INIT(&mutex, 1);

  PT_INIT(&pt_producer);
  PT_INIT(&pt_consumer);

  PT_WAIT_THREAD(pt, producer(&pt_producer) &
		     consumer(&pt_consumer));

  PT_END(pt);
}
 \endcode
 *
 * The program uses three protothreads: one protothread that
 * implements the consumer, one thread that implements the producer,
 * and one protothread that drives the two other protothreads. The
 * program uses three semaphores: "full", "empty" and "mutex". The
 * "mutex" semaphore is used to provide mutual exclusion for the
 * buffer, the "empty" semaphore is used to block the consumer is the
 * buffer is empty, and the "full" semaphore is used to block the
 * producer is the buffer is full.
 *
 * The "driver_thread" holds two protothread state variables,
 * "pt_producer" and "pt_consumer". It is important to note that both
 * these variables are declared as <i>static</i>. If the static
 * keyword is not used, both variables are stored on the stack. Since
 * protothreads do not store the stack, these variables may be
 * overwritten during a protothread wait operation. Similarly, both
 * the "consumer" and "producer" protothreads declare their local
 * variables as static, to avoid them being stored on the stack.
 * 
 *
 */
   
/**
 * \file
 * Couting semaphores implemented on protothreads
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __PT_SEM_H__
#define __PT_SEM_H__

#include "pt.h"

struct pt_sem {
  unsigned int count;
};

/**
 * Initialize a semaphore
 *
 * This macro initializes a semaphore with a value for the
 * counter. Internally, the semaphores use an "unsigned int" to
 * represent the counter, and therefore the "count" argument should be
 * within range of an unsigned int.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \param c (unsigned int) The initial count of the semaphore.
 * \hideinitializer
 */
#define PT_SEM_INIT(s, c) (s)->count = c

/**
 * Wait for a semaphore
 *
 * This macro carries out the "wait" operation on the semaphore. The
 * wait operation causes the protothread to block while the counter is
 * zero. When the counter reaches a value larger than zero, the
 * protothread will continue.
 *
 * \param pt (struct pt *) A pointer to the protothread (struct pt) in
 * which the operation is executed.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define PT_SEM_WAIT(pt, s)	\
  do {						\
    PT_WAIT_UNTIL(pt, (s)->count > 0);		\
    --(s)->count;				\
  } while(0)

/**
 * Signal a semaphore
 *
 * This macro carries out the "signal" operation on the semaphore. The
 * signal operation increments the counter inside the semaphore, which
 * eventually will cause waiting protothreads to continue executing.
 *
 * \param pt (struct pt *) A pointer to the protothread (struct pt) in
 * which the operation is executed.
 *
 * \param s (struct pt_sem *) A pointer to the pt_sem struct
 * representing the semaphore
 *
 * \hideinitializer
 */
#define PT_SEM_SIGNAL(pt, s) ++(s)->count

#endif /* __PT_SEM_H__ */

/** @} */
/** @} */
   
/*
 * Copyright (c) 2004-2005, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the Contiki operating system.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: pt.h,v 1.7 2006/10/02 07:52:56 adam Exp $
 */

/**
 * \addtogroup pt
 * @{
 */

/**
 * \file
 * Protothreads implementation.
 * \author
 * Adam Dunkels <adam@sics.se>
 *
 */

#ifndef __PT_H__
#define __PT_H__

#include "lc.h"

struct pt {
  lc_t lc;
};

#define PT_WAITING 0
#define PT_YIELDED 1
#define PT_EXITED  2
#define PT_ENDED   3

/**
 * \name Initialization
 * @{
 */

/**
 * Initialize a protothread.
 *
 * Initializes a protothread. Initialization must be done prior to
 * starting to execute the protothread.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \sa PT_SPAWN()
 *
 * \hideinitializer
 */
#define PT_INIT(pt)   LC_INIT((pt)->lc)

/** @} */

/**
 * \name Declaration and definition
 * @{
 */

/**
 * Declaration of a protothread.
 *
 * This macro is used to declare a protothread. All protothreads must
 * be declared with this macro.
 *
 * \param name_args The name and arguments of the C function
 * implementing the protothread.
 *
 * \hideinitializer
 */
#define PT_THREAD(name_args) char name_args

/**
 * Declare the start of a protothread inside the C function
 * implementing the protothread.
 *
 * This macro is used to declare the starting point of a
 * protothread. It should be placed at the start of the function in
 * which the protothread runs. All C statements above the PT_BEGIN()
 * invokation will be executed each time the protothread is scheduled.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_BEGIN(pt) { char PT_YIELD_FLAG = 1; LC_RESUME((pt)->lc)

/**
 * Declare the end of a protothread.
 *
 * This macro is used for declaring that a protothread ends. It must
 * always be used together with a matching PT_BEGIN() macro.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_END(pt) LC_END((pt)->lc); PT_YIELD_FLAG = 0; \
                   PT_INIT(pt); return PT_ENDED; }

/** @} */

/**
 * \name Blocked wait
 * @{
 */

/**
 * Block and wait until condition is true.
 *
 * This macro blocks the protothread until the specified condition is
 * true.
 *
 * \param pt A pointer to the protothread control structure.
 * \param condition The condition.
 *
 * \hideinitializer
 */
#define PT_WAIT_UNTIL(pt, condition)	        \
  do {						\
    LC_SET((pt)->lc);				\
    if(!(condition)) {				\
      return PT_WAITING;			\
    }						\
  } while(0)

/**
 * Block and wait while condition is true.
 *
 * This function blocks and waits while condition is true. See
 * PT_WAIT_UNTIL().
 *
 * \param pt A pointer to the protothread control structure.
 * \param cond The condition.
 *
 * \hideinitializer
 */
#define PT_WAIT_WHILE(pt, cond)  PT_WAIT_UNTIL((pt), !(cond))

/** @} */

/**
 * \name Hierarchical protothreads
 * @{
 */

/**
 * Block and wait until a child protothread completes.
 *
 * This macro schedules a child protothread. The current protothread
 * will block until the child protothread completes.
 *
 * \note The child protothread must be manually initialized with the
 * PT_INIT() function before this function is used.
 *
 * \param pt A pointer to the protothread control structure.
 * \param thread The child protothread with arguments
 *
 * \sa PT_SPAWN()
 *
 * \hideinitializer
 */
#define PT_WAIT_THREAD(pt, thread) PT_WAIT_WHILE((pt), PT_SCHEDULE(thread))

/**
 * Spawn a child protothread and wait until it exits.
 *
 * This macro spawns a child protothread and waits until it exits. The
 * macro can only be used within a protothread.
 *
 * \param pt A pointer to the protothread control structure.
 * \param child A pointer to the child protothread's control structure.
 * \param thread The child protothread with arguments
 *
 * \hideinitializer
 */
#define PT_SPAWN(pt, child, thread)		\
  do {						\
    PT_INIT((child));				\
    PT_WAIT_THREAD((pt), (thread));		\
  } while(0)

/** @} */

/**
 * \name Exiting and restarting
 * @{
 */

/**
 * Restart the protothread.
 *
 * This macro will block and cause the running protothread to restart
 * its execution at the place of the PT_BEGIN() call.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_RESTART(pt)				\
  do {						\
    PT_INIT(pt);				\
    return PT_WAITING;			\
  } while(0)

/**
 * Exit the protothread.
 *
 * This macro causes the protothread to exit. If the protothread was
 * spawned by another protothread, the parent protothread will become
 * unblocked and can continue to run.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_EXIT(pt)				\
  do {						\
    PT_INIT(pt);				\
    return PT_EXITED;			\
  } while(0)

/** @} */

/**
 * \name Calling a protothread
 * @{
 */

/**
 * Schedule a protothread.
 *
 * This function shedules a protothread. The return value of the
 * function is non-zero if the protothread is running or zero if the
 * protothread has exited.
 *
 * \param f The call to the C function implementing the protothread to
 * be scheduled
 *
 * \hideinitializer
 */
#define PT_SCHEDULE(f) ((f) < PT_EXITED)

/** @} */

/**
 * \name Yielding from a protothread
 * @{
 */

/**
 * Yield from the current protothread.
 *
 * This function will yield the protothread, thereby allowing other
 * processing to take place in the system.
 *
 * \param pt A pointer to the protothread control structure.
 *
 * \hideinitializer
 */
#define PT_YIELD(pt)				\
  do {						\
    PT_YIELD_FLAG = 0;				\
    LC_SET((pt)->lc);				\
    if(PT_YIELD_FLAG == 0) {			\
      return PT_YIELDED;			\
    }						\
  } while(0)

/**
 * \brief      Yield from the protothread until a condition occurs.
 * \param pt   A pointer to the protothread control structure.
 * \param cond The condition.
 *
 *             This function will yield the protothread, until the
 *             specified condition evaluates to true.
 *
 *
 * \hideinitializer
 */
#define PT_YIELD_UNTIL(pt, cond)		\
  do {						\
    PT_YIELD_FLAG = 0;				\
    LC_SET((pt)->lc);				\
    if((PT_YIELD_FLAG == 0) || !(cond)) {	\
      return PT_YIELDED;			\
    }						\
  } while(0)

/** @} */

#endif /* __PT_H__ */

/** @} */
#ifndef SD_H
#define SD_H

#include <string.h>

#include "pfatfs/diskio.h"
#include "pfatfs/pff.h"
#include "spi.h"

#include "graphics.h"

enum {
  SD_INIT_SUCCESS = 0,
  SD_INIT_FAILURE,
  SD_INIT_FAIL_INIT,
  SD_INIT_FAIL_MOUNT,
};

uint8_t sd_init(void) __attribute__((section(".boot")));
FRESULT sd_scan_files (char* path) __attribute__((section(".boot")));
#endif
#ifndef _SPI_H
#define _SPI_H

#include <stdint.h>
#include <avr/io.h>
#include "HAL/board.h"


typedef enum {
  SPI_LSB_FIRST = 1,
  SPI_MSB_FIRST = 0
} spi_endianness_t;
typedef enum {
  SPI_BUSMODE_SLAVE = 0,
  SPI_BUSMODE_MASTER = 1,
} spi_bus_mode_t;
typedef enum {
  SPI_MODE_0 = 0,
  SPI_MODE_1 = 1,
  SPI_MODE_2 = 2,
  SPI_MODE_3 = 3,
} spi_trans_mode_t;
typedef enum {
  SPI_CLOCKDIV_4 = 0,
  SPI_CLOCKDIV_16 = 1,
  SPI_CLOCKDIV_64 = 2,
  SPI_CLOCKDIV_128 = 3,
} spi_clock_rate_t;
typedef enum  {
  SPI_DBLCLK_DISABLE = 0,
  SPI_DBLCLK_ENABLE = 1,
} spi_double_clock_t;

typedef
union {
  struct __attribute__ ((packed)) {
    spi_endianness_t endianness : 1;
    spi_bus_mode_t bus_mode : 1;
    spi_trans_mode_t trans_mode : 2;
    spi_clock_rate_t clock_rate : 2;
    spi_double_clock_t double_clock : 1;
  };
  uint8_t intRep;
} spi_setting_t;

void spi_init(spi_setting_t* settings);

uint8_t spi_send(uint8_t value);

#endif
#ifndef SYSTICK_H
#define SYSTICK_H
#include <stdint.h>
volatile uint32_t global_tick;


void systick_init();
#endif
#ifndef TERMINAL_H
#define TERMINAL_H

#include "stdint.h"

#include "buffer.h"
#include "font.h"

#include <avr/pgmspace.h>

// todo: add function pointer to read and write characters to term (for FRAM)
typedef struct {
  uint8_t scroll_x;   // scroll windows top position (in rows)
  uint8_t rows;       // maximum number of character rows
  uint8_t width;      // maximum characters per row
  uint8_t view_rows;  // number of rows to render from scroll position
  uint8_t cursor_x;   // character cursor position in current row
  uint8_t cursor_y;   // current row of character cursor
  char* buffer;       // storage space for term buffer
} terminal_t;

terminal_t* term_redirected;

terminal_t term_init(uint8_t width, uint8_t height);

void term_putchar(terminal_t* term, char c);
void term_redirect_putchar(terminal_t* term);
void term_puts(terminal_t* term, const char* str);
void term_puts_P(terminal_t* term, PGM_P str);
void term_draw(terminal_t* term);
void term_set_cursor(terminal_t* term, uint8_t cur_x, uint8_t cur_y);
void term_clear(terminal_t* term);
#endif
