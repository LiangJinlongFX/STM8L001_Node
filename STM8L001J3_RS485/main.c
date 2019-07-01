#include "stm8l10x.h"
#include "stm8l10x_gpio.h"
#include "stm8l10x_clk.h"
#include "usart.h"
#include "delay.h"
#include "tsic506.h"

#define _IAR_

#ifdef      _COSMIC_
#define     ASM _asm
#endif
#ifdef      _IAR_
#define     ASM asm
#endif

/* This delay should be added just after reset to have access to SWIM pin
and to be able to reprogram the device after power on (otherwise the
device will be locked) */
#define STARTUP_SWIM_DELAY_5S     \
{                                 \
  ASM(" PUSHW X \n"               \
      " PUSH A \n"                \
      " LDW X, #0xFFFF \n"        \
      "loop1: LD A, #50 \n"       \
                                  \
      "loop2: DEC A \n"           \
      " JRNE loop2 \n"            \
                                  \
      " DECW X \n"                \
      " JRNE loop1 \n"            \
                                  \
      " POP A \n"                 \
      " POPW X " );               \
}

/* pin for testing */
#define TEST_PORT   GPIOA
#define TEST_PIN    GPIO_Pin_2

int main( void )
{ 
    /* -------------STM8L001 startup-------------- */
    /* delay for SWIM connection: ~5seconds */
    STARTUP_SWIM_DELAY_5S;

    /* initialize tested pin */
    GPIO_Init(TEST_PORT, TEST_PIN, GPIO_Mode_Out_PP_Low_Fast);
    
    Usart_Init();
    TSIC506_Init();
    TSIC506_ON();

    while (1)
    {
        #ifdef USART_SLAVE
        RS485_RX_ENABLE();
        Temperture_Val[0] = 0x80;
        Temperture_Val[1] = 0x81;
        delay_n20us(500);
        #else
        RS485_TX_ENABLE();
        Usart_SendData9(0xcc, 1);
        RS485_RX_ENABLE();
        delay_n20us(50000);
        RS485_TX_ENABLE();
        Usart_SendData9(0xca, 1);
        RS485_RX_ENABLE();
        delay_n20us(50000);
        #endif
        //toggle with tested pin
        //GPIO_ToggleBits(TEST_PORT, TEST_PIN);
    }
}
