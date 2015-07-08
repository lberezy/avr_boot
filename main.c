/* Name: main.c
 * Author: <insert your name here>
 * Copyright: <insert your copyright message here>
 * License: <insert your license reference here>
 */

#include <avr/io.h>
#include <stdint.h>

#include <avr/signature.h>


int main(void)
{
  DDRD = 0xff;

  while(1) {
    PORTD ^= 0xff;
  }

  return 0;
}
