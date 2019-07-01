#include "stm8l10x.h"
#include "delay.h"

void delay_20us(void) {
  u8 i=2;
  while(i--);
}


void delay_n20us(u16 us) {
  while(us--) {
    delay_20us();
    nop();
    nop();
    nop();
  }
}

void delay_60us() {
  u8 i=10;
  while(i--);
}