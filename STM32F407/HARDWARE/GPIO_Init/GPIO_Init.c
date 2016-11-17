#include "GPIO_Init.h"
#include "lcd.h"
#include "AT24C02.h"
extern volatile u8 ADNum;
extern volatile u16 Squa_Fre;
extern volatile u16 Sine_Fre;
extern volatile u16 Sine_Amp;
extern volatile u8 Switch_Flag1;
extern volatile u8 Switch_Flag2;
extern volatile u8 Switch_Flag;
void Gpio_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;	

	//液晶显示部分
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO	

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO	
	
	//模数转换部分
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化GPIO	
	
	//模数转换旋钮、方波频率调节旋钮、正弦波频率调节旋钮、正弦波幅值调节旋钮
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOA时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//RST对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化GPIO
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOA时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;//RST对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOA时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//RST对应IO口
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource3);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource4);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOG, EXTI_PinSource5);
	
		/* 配置EXTI_Line0 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升、下降均沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE5
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置	
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;//LINE0
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; //上升、下降沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE5
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置	
	
	/* 配置EXTI_Line2 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2;//LINE5
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE5
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置	
	
	/* 配置EXTI_Line3 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;//LINE5
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE5
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置	
	
	/* 配置EXTI_Line4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line4;//LINE5
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE5
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置	
	
	/* 配置EXTI_Line5 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line5;//LINE5
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE5
	EXTI_Init(&EXTI_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断10
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置	
	
	
}
//外部中断处理函数,开关接口
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		Delays();
		if(PDin(0)==0)   //低电平，开关闭合
		{
			Switch_Flag1=1;
		}
		else 
		{
			Switch_Flag1=0;
		}
		if((Switch_Flag1==1)||(Switch_Flag2==1))
			Switch_Flag=1;
		else
			Switch_Flag=0;
//		LCD_ShowSwitch_Flag(Switch_Flag);
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}
//外部中断处理函数,开关接口
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		Delays();
		if(PDin(1)==0)   //低电平，开关闭合
		{
			Switch_Flag2=1;
		}
		else 
		{
			Switch_Flag2=0;
		}
		if((Switch_Flag1==1)||(Switch_Flag2==1))
			Switch_Flag=1;
		else
			Switch_Flag=0;
//		LCD_ShowSwitch_Flag(Switch_Flag);
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}
//外部中断处理函数,模数转换
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2) != RESET)
	{
		Delays();
		if(B1==1)
		{
			if(ADNum>=255)
				ADNum=255;
			else
			 ADNum ++;
		}
		else
		{
			if(ADNum<=0)
				ADNum=0;
			else
				ADNum --;
		}
		AT24C02_WriteOneByte(0x00,ADNum);
		LCD_ShowADNum(ADNum);
		EXTI_ClearITPendingBit(EXTI_Line2);
	}
}
//外部中断处理函数,方波频率
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET)
	{
		Delays();
		if(B2==1)
		{
			if(Squa_Fre>=1200)
				Squa_Fre=1200;
			else
			 Squa_Fre +=10;
		}
		else
		{
			if(Squa_Fre<=20)
				Squa_Fre=20;
			else
				Squa_Fre -=10;
		}
		AT24C02_WriteOneByte(0x01,Squa_Fre/256);
		AT24C02_WriteOneByte(0x02,Squa_Fre%256);
		LCD_ShowSqua_Fre(Squa_Fre);
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}
//外部中断处理函数,正弦波频率
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET)
	{
		Delays();
		if(B3==1)
		{
			if(Sine_Fre>=300)
				Sine_Fre=300;
			else
			  Sine_Fre+=10;
		}
		else
		{
			if(Sine_Fre<=10)
				Sine_Fre=10;
			else
				Sine_Fre -=10;
		}
		AT24C02_WriteOneByte(0x03,Sine_Fre/256);
		AT24C02_WriteOneByte(0x04,Sine_Fre%256);
		LCD_ShowSine_Fre(Sine_Fre);
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

//外部中断处理函数,正弦波幅值
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		Delays();
		if(B4==1)
		{
			if(Sine_Amp>=500)
				Sine_Amp=500;
			else
			  Sine_Amp+=10;
		}
		else
		{
			if(Sine_Amp<=0)
				Sine_Amp=0;
			else
			 Sine_Amp -=10;
		}
		AT24C02_WriteOneByte(0x05,Sine_Amp/256);
		AT24C02_WriteOneByte(0x06,Sine_Amp%256);
		LCD_ShowSine_Amp(Sine_Amp);
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}
void Delays(void)    //延时消抖
{
	u8 i,j;
	for(i=0;i<50;i++)
		for(j=0;j<20;j++);
}
void SetAD(u8 SetNum)  //完成模数转换
{
	if(SetNum&1<<0)
		AD1=1;     //对应输出高电平
	else
		AD1=0;
	if(SetNum&1<<1)
		AD2=1;     //对应输出高电平
	else
		AD2=0;
	if(SetNum&1<<2)
		AD3=1;     //对应输出高电平
	else
		AD3=0;
	if(SetNum&1<<3)
		AD4=1;     //对应输出高电平
	else
		AD4=0;
	if(SetNum&1<<4)
		AD5=1;     //对应输出高电平
	else
		AD5=0;
	if(SetNum&1<<5)
		AD6=1;     //对应输出高电平
	else
		AD6=0;
	if(SetNum&1<<6)
		AD7=1;     //对应输出高电平
	else
		AD7=0;
	if(SetNum&1<<7)
		AD8=1;     //对应输出高电平
	else
		AD8=0;
}
