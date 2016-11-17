#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "delay.h" 
#include "GPIO_Init.h"
#include "AT24C02.h"
#include "lcd.h"
#include "AD9851.h"
#include "X9C503.h"
#include "DAC.h"

volatile u8 ADNum;
volatile u16 Squa_Fre;
volatile u16 Sine_Fre;
volatile u16 Sine_Amp;
volatile u8 Switch_Flag;  //标记开关状态
volatile u8 Switch_Flag1;
volatile u8 Switch_Flag2;

volatile u8 ADNumt;
volatile u16 Squa_Fret;
volatile u16 Sine_Fret;
volatile u16 Sine_Ampt;
volatile u8 Switch_Flagt;

volatile u16 tableSize;
volatile u16 FreqNum;
volatile u16 VoltageValue;   //0-5000

void StartInit(void);
void CheckFlag(void);
volatile u16 FreqNuma;
int main(void)
{
	u8 i;
	u16 k;
	delay_init(168);
	Gpio_Init();
	GPIO_Configuration(); 
	AT24C02_Init();
	LCD_Init();
	StartInit();
	Switch_Flagt=3;
//	ADNum=100;
//	Squa_Fre=100;
//	Sine_Fret=100;																																																																																																											
//  Sine_Amp=100;

	while(1)
	{
		//AD转换
		CheckFlag();
		if(Switch_Flag!=Switch_Flagt)    //开关状态变化，执行相关动作
		{
			if(Switch_Flag==1)    
			{
				Sine_Fret=Sine_Fre;
				sin_Generation(Sine_Fret,Sine_Amp);	
				FreqNum=42000000/Sine_Fret/tableSize-1;
				TIM6_Configuration(FreqNum);
				DAC_DMA_Configuration(); 
				delay_ms(70);
				AD9 =0;
				ADNumt=ADNum;
				SetAD(ADNumt);
				delay_ms(10);
			}
			if(Switch_Flag==0)
			{
				Sine_Fret=Sine_Fre;
				sin_Generation(Sine_Fret,0);	
				FreqNum=42000000/Sine_Fret/tableSize-1;
				TIM6_Configuration(FreqNum);
				DAC_DMA_Configuration(); 
				AD9 =1;
				SetAD(0);
				delay_ms(10);
			}
			Switch_Flagt=Switch_Flag;
			LCD_ShowSwitch_Flag(Switch_Flag);
		}
		if((ADNumt!=ADNum)&&(Switch_Flagt==1))//AD数值变化，并且开关闭合，执行相关动作
		{
			ADNumt=ADNum;
			SetAD(ADNumt);
			delay_ms(10);
		}
		
		//方波频率设置
		if(Squa_Fret!=Squa_Fre)
		{
			Squa_Fret=Squa_Fre;
			FreqNuma=84000/Squa_Fret-1;
			TIM4_PWM_Init(FreqNuma,0);
			delay_ms(10);
		}
		//正弦波频率设置
		if((Sine_Fret!=Sine_Fre)&&(Switch_Flagt==1))
		{
			Sine_Fret=Sine_Fre;
      sin_Generation(Sine_Fret,Sine_Amp);	
	    FreqNum=42000000/Sine_Fret/tableSize-1;
	    TIM6_Configuration(FreqNum);
	    DAC_DMA_Configuration(); 
			delay_ms(10);
		}
		
		//正弦波幅值设置
		if((Sine_Ampt!=Sine_Amp)&&(Switch_Flagt==1))
		{
			Sine_Ampt=Sine_Amp;
			sin_Generation(Sine_Fret,Sine_Ampt);	
	    FreqNum=42000000/Sine_Fret/tableSize-1;
	    TIM6_Configuration(FreqNum);
	    DAC_DMA_Configuration(); 
			delay_ms(10);
		}
	}
}
void StartInit(void)
{
	LCD_Display();
	//AD设置部分
	ADNum = AT24C02_ReadOneByte(0x00);
	SetAD(ADNum);
	ADNumt=ADNum;
	LCD_ShowADNum(ADNum);
	//开关状态监测
	if(PDin(0)==0)    //开关闭合
	{
		Switch_Flag =1;
//		AD9=0;
//		ADNumt=ADNum;
//		SetAD(ADNumt);
	}
	else            //开关打开
	{
		Switch_Flag =0;
//		AD9=1;
//		ADNumt=ADNum;
//		SetAD(0);
	}
	LCD_ShowSwitch_Flag(Switch_Flag);
	//方波频率设置部分
	Squa_Fre =AT24C02_ReadOneByte(0x01);
	Squa_Fre<<=8;
	Squa_Fre +=AT24C02_ReadOneByte(0x02);
	LCD_ShowSqua_Fre(Squa_Fre);
	Squa_Fret=Squa_Fre;
	FreqNuma=84000/Squa_Fret-1;
  TIM4_PWM_Init(FreqNuma,0);
	//正弦波频率设置部分
	Sine_Fre =AT24C02_ReadOneByte(0x03);
	Sine_Fre<<=8;
	Sine_Fre +=AT24C02_ReadOneByte(0x04);
	LCD_ShowSine_Fre(Sine_Fre);
	Sine_Fret=Sine_Fre;
	
	//正弦波幅值设置部分
	Sine_Amp =AT24C02_ReadOneByte(0x05);
	Sine_Amp<<=8;
	Sine_Amp +=AT24C02_ReadOneByte(0x06);
	LCD_ShowSine_Amp(Sine_Amp);
	
	if(Sine_Amp<50)
		Sine_Ampt=50;
//	sin_Generation(Sine_Fre,Sine_Ampt);	
//	FreqNum=42000000/Sine_Fre/tableSize-1;
//	TIM6_Configuration(FreqNum);
//	DAC_DMA_Configuration();
	delay_ms(20);
}
void CheckFlag(void)
{
	if(PDin(0)==0)
		Switch_Flag1=1;
	else
		Switch_Flag1=0;
	if(PDin(1)==0)
		Switch_Flag2=1;
	else
		Switch_Flag2=0;
	if((PDin(0)==0)||(PDin(1)==0))   //低电平，开关闭合
	{
		Switch_Flag=1;
	}
	else 
	{
		Switch_Flag=0;
	}
	delay_ms(10);
}
