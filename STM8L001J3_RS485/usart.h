#ifndef _USART_H
#define _USART_H

#include "stm8l10x.h"
#include "stm8l10x_usart.h"

#define Node_ID 0x80
#define USART_SLAVE

#define RS485_TX_ENABLE() GPIO_SetBits(GPIOC, GPIO_Pin_0)
#define RS485_RX_ENABLE() GPIO_ResetBits(GPIOC, GPIO_Pin_0)

void Usart_Init(void);
void Usart_SendString(char* string);
void Usart_SendData9(u8 Data, u8 DA);

#endif