#include "DAC.h"
#include "math.h"

#define DAC_DHR12R1_ADDRESS     0x40007408

extern volatile u16 tableSize;
volatile u16 sinTable[1024];

void sin_Generation(u16 Fre,u16 Vol)
{
	u32 Voltage;
	u16 n;
	if(Vol>490)
		Vol =490;
	Voltage= Vol*4090/500;
	if(Fre>150)
		tableSize=512;
	else
		tableSize=1024;
//	for(n=0;n<tableSize;n++)
//	{
//		sinTable[n] = (sin(2*PI*n/tableSize)+1)*Voltage+50;	
//	}	

	if(Voltage>40)
	{
		for(n=0;n<tableSize/2;n++)
		{
			sinTable[n] =n*2*Voltage/tableSize+80;	
		}
		for(n=tableSize/2;n<tableSize;n++)
		{
			sinTable[n] =Voltage-(2*n+2-tableSize)*Voltage/tableSize+80;	
		}
	}
	if((Voltage<=40)&&(Voltage>=10))
	{
		for(n=0;n<tableSize/2;n++)
		{
			sinTable[n] =n*2*Voltage/tableSize+150;	
		}
		for(n=tableSize/2;n<tableSize;n++)
		{
			sinTable[n] =Voltage-(2*n+2-tableSize)*Voltage/tableSize+150;	
		}
	}
	if(Voltage==0)
	{
		for(n=0;n<tableSize/2;n++)
		{
			sinTable[n] =n*2*Voltage/tableSize+300;	
		}
		for(n=tableSize/2;n<tableSize;n++)
		{
			sinTable[n] =Voltage-(2*n+2-tableSize)*Voltage/tableSize+300;	
		}
	}
	
}

void TIM6_Configuration(u16 Fre)
{

		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);	
		TIM_PrescalerConfig(TIM6,1, TIM_PSCReloadMode_Update);
		TIM_SetAutoreload(TIM6, Fre);
		TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
		TIM_Cmd(TIM6, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void DAC_DMA_Configuration(void)
{
	DAC_InitTypeDef  DAC_InitStructure;	

	DMA_InitTypeDef DMA_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DMA_DeInit(DMA1_Stream5);
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;  
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&sinTable;
	DMA_InitStructure.DMA_BufferSize = tableSize;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);    
	
	DMA_Cmd(DMA1_Stream5, ENABLE);
	
	DAC_Cmd(DAC_Channel_1, ENABLE);
	
	DAC_DMACmd(DAC_Channel_1, ENABLE);
} 

void Sine_Set(u16 Fre,u16 Vol)
{
	u16 FreNum;
	sin_Generation(Fre,Vol);
	FreNum=42000000/tableSize/Fre-1;
	TIM6_Configuration(FreNum);
	DAC_DMA_Configuration();
}

void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM4ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4); //GPIOB8����Ϊ��ʱ��4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM4 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM4��CCR3�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM14
	TIM_SetCompare3(TIM4,(arr+1)/2-1);
 
										  
}  





