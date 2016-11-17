#ifndef __GPIO_Init_H
#define __GPIO_Init_H

#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_exti.h"

#define AD1  PAout(3)      
#define AD2  PAout(2) 
#define AD3  PAout(1)      
#define AD4  PAout(0) 
#define AD5  PCout(3)      
#define AD6  PCout(2) 
#define AD7  PCout(1)      
#define AD8  PCout(0) 

#define AD9  PFout(8)


#define B1  PDin(15) 
#define B2  PDin(14)
#define B3  PGin(6) 
#define B4  PGin(7)

void Gpio_Init(void);
void Delays(void);    //��ʱ����
void SetAD(u8 SetNum);    //���ģ��ת��

#endif

