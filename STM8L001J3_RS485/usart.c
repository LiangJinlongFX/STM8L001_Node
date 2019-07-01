#include "usart.h"
#include "stm8l10x.h"

/*
 * 初始化串口外设
 * - BaudRate = 9600 baud  
 * - Word Length = 9 Bits
 * - One Stop Bit
 * - No parity
 * - Receive and Transmit enabled
 */
void Usart_Init() {
    
  /*Set the USART RX and USART TX at high level*/
  GPIO_ExternalPullUpConfig(GPIOC,GPIO_Pin_3|GPIO_Pin_4, ENABLE);
  /* initialize RS485 CTR */
  GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_Out_PP_High_Fast);
  // initialize UART Clock
  CLK_PeripheralClockConfig(CLK_Peripheral_USART, ENABLE);
  /* initialize UART */
  USART_Init(9600,
             USART_WordLength_9D,
             USART_StopBits_1,
             USART_Parity_No,
             (USART_Mode_TypeDef)(USART_Mode_Rx | USART_Mode_Tx));
  
  /* Enable the USART Receive interrupt: this interrupt is generated when the
     USART receive data register is not empty */
  USART_ITConfig(USART_IT_RXNE, ENABLE);

#ifdef USART_SLAVE

  /* Set the USART Address */
  USART_SetAddress(0x0A);

  /* Select the USART WakeUp Method */
  USART_WakeUpConfig(USART_WakeUp_AddressMark);

  /* Enable the USART mute mode*/
  USART_ReceiverWakeUpCmd(ENABLE);
  
#endif
  
  /* Enable the USART */
  USART_Cmd(ENABLE);
  
  /* Enable general interrupts */
  enableInterrupts();
}

/*
 * 串口发送字符串 
 */
void Usart_SendString(char* string) {
  
  while(*string != '\0') {
    USART_SendData8(*string++);
  }
}

/*
 * 串口发送9位数据
 * @params DA  0:发送数据字节  1:发送地址字节
 */
void Usart_SendData9(u8 Data, u8 DA) {
  
  u16 temp=0;
  temp = (u16)Data;
  if(DA) {
    temp |= 0x100;
  }
  USART_SendData9(temp);
  /* Wait while USART TXE = 0 */
  while (USART_GetFlagStatus(USART_FLAG_TC) == RESET);
}
