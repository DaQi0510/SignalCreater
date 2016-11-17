#ifndef __LCD_H
#define __LCD_H

#include "stm32f4xx_gpio.h"
#include "delay.h"

#define SET_LCD_DC GPIO_SetBits(GPIOA,GPIO_Pin_6)     //  PF0  片选
#define CLR_LCD_DC GPIO_ResetBits(GPIOA,GPIO_Pin_6)

#define SET_LCD_RST GPIO_SetBits(GPIOA,GPIO_Pin_7)    //  PF1  复位
#define CLR_LCD_RST GPIO_ResetBits(GPIOA,GPIO_Pin_7)

#define SET_LCD_SDA GPIO_SetBits(GPIOC,GPIO_Pin_4)     //  PF2  数据位
#define CLR_LCD_SDA GPIO_ResetBits(GPIOC,GPIO_Pin_4)

#define SET_LCD_SCL GPIO_SetBits(GPIOC,GPIO_Pin_5)     //  PF3  数据位
#define CLR_LCD_SCL GPIO_ResetBits(GPIOC,GPIO_Pin_5)

 void LCD_Init(void);
 void LCD_P6x8Str(u8 x,u8 y,u8 ch[]);
 void LCD_ShowNum(u8 x,u8 y, unsigned int num);
 void LCD_Show_M(u8 y,unsigned long int num);
 void LCD_Display(void);
 void LCD_ShowADNum(u8 Value);
 void LCD_ShowSqua_Fre(u16 Value);
 void LCD_ShowSine_Fre(u16 Value);
 void LCD_ShowSine_Amp(u16 Value);
 void LCD_ShowSwitch_Flag(u8 Value);
 
#endif

