#ifndef __TSIC506_H

#include "stm8l10x.h"
#include "stm8l10x_gpio.h"

#define TSIC506_VDD_PORT GPIOB
#define TSIC506_VDD_PIN  GPIO_Pin_6
#define TSIC506_DQ_PORT  GPIOB
#define TSIC506_DQ_PIN   GPIO_Pin_7

#define TSIC506_ON()  GPIO_SetBits(TSIC506_VDD_PORT, TSIC506_VDD_PIN)
#define TSIC506_OFF() GPIO_ResetBits(TSIC506_VDD_PORT, TSIC506_VDD_PIN)
#define DQ GPIO_ReadInputDataBit(TSIC506_DQ_PORT, TSIC506_DQ_PIN)

extern u8  Temperture_Val[2];
extern u8  Is_Flush;

void TSIC506_Init(void);
u16 TSIC506_GetTemp(u16 *temp_value16);
float Get_RealTemperature(u16 Temp_Val);


#endif /* __TSIC506_H */
