#include "tsic506.h"
#include "delay.h"
#include "stdio.h"

u8 Temperture_Val[2];
u8 Is_Flush=1;

/*
 * ��ʼ��TSIC506����
 */
void TSIC506_Init() {
  //��ʼ���Դ������
  GPIO_Init(TSIC506_VDD_PORT, TSIC506_VDD_PIN, GPIO_Mode_Out_PP_Low_Fast);
  //��ʼ���������Q����
  GPIO_Init(TSIC506_DQ_PORT, TSIC506_DQ_PIN, GPIO_Mode_In_PU_No_IT);
}

u16 TSIC506_GetTemp(u16 *temp_value16) {
  u16 temp_val1 = 0;
  u16 temp_val2 = 0;
  u8 i;
  u16 temperature;
  u8 parity;
  
  TSIC506_ON();         //оƬ���
  delay_n20us(8);       //�ӕr120us���ȴ�����
  
  //first byte
  //�ȴ��_ʼ��̖
  while(DQ);
  while(DQ == 0);
  
  //���½��ض�ȡ8λ����+1λ��żУ��λ
  for(i=0;i<9;i++) {
    while(DQ);    //�ȴ��½���
    delay_60us();
    if(DQ) {
      temp_val1 |= 1 << (8-i); //ȡһ��λ���Ӹ�λ��ʼ��
    } else {
      while(DQ == 0);  //�ȴ����Q������
    }
  }
  
  //second byte
  //�ȴ��_ʼ��̖
  while(DQ);
  while(DQ == 0);
  
  //���½��ض�ȡ8λ����+1λ��żУ��λ
  for(i=0;i<9;i++) {
    while(DQ);    //�ȴ��½���
    delay_60us();
    if(DQ) {
      temp_val2 |= 1 << (8-i); //ȡһ��λ���Ӹ�λ��ʼ��
    } else {
      while(DQ == 0);  //�ȴ����Q������
    }
  }
  
  TSIC506_OFF();         //оƬ���
    
  //check parity for byte 1
  parity = 0;
  for(i = 0; i < 9; i++) {
    if(temp_val1 & (1<<i)) {
      parity++;
    }
  }
  if(parity % 2)
    return 0;
  
  //check parity for byte 2
  parity = 0;
  for(i = 0; i < 9; i++) {
    if(temp_val2 & (1<<i)) {
      parity++;
    }
  }
  if(parity % 2)
    return 0;
  
  
  //delete parity bit
  temp_val1 >>= 1;
  temp_val2 >>= 1;
  
  temperature = (temp_val1 << 8 ) | temp_val2;
  *temp_value16 = temperature;
  
  return 1; //parity is OK
  
}

float Get_RealTemperature(u16 Temp_Val) {
  
  float Temp_float;
  
  Temp_float = ((float)Temp_Val/2047*70) - 10;
  
  return Temp_float;
}
