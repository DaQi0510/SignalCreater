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

#define Key_Out1   PFout(6)
#define Key_Out21  PFout(9)
#define Key_Out22  PFout(7)
#define Key_Out23  PFout(8)


#define B1  PDin(15) 
#define B2  PDin(14)
#define B3  PGin(6) 
#define B4  PGin(7)

void Gpio_Init(void);
void Delays(void);    //延时消抖
void SetAD(u8 SetNum);    //完成模数转换

#endif

