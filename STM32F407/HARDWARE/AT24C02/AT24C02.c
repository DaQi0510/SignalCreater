#include "AT24C02.h"
#include "delay.h"

/********** IIC���ų�ʼ��*****************/
/*-------------|----------------
	        PD12<->SCL
					PD13<->SDA
  -------------|----------------*/
void AT24C02_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOBʱ��
  //GPIOD12,D13��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��
	AT24C02_SCL=1;
	AT24C02_SDA=1;
}
void AT24C02_Init(void)
{
	AT24C02_GPIO_Init();
}
//�����豸��Ϣ
void SetDeviceInformation(u8 *Information,u8 Length)    
{
	u8 i;
	u8 j;
	for(i=0;i<Length;i++)
	{
		AT24C02_WriteOneByte(i,Information[i]);
		for(j=0;j<100;j++);
	}
}

//��AT24C02ָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24C02_ReadOneByte(u8 ReadAddr)
{
	u8 RxData;
	AT24C02_IIC_Start();
	AT24C02_Send_Byte(0xA0);
	AT24C02_IIC_Wait_Ack();
	AT24C02_Send_Byte(ReadAddr);   //���͵�ַ
	AT24C02_IIC_Wait_Ack();
	AT24C02_IIC_Start();
	AT24C02_Send_Byte(0xA1);      //����ָ��
	AT24C02_IIC_Wait_Ack();
	RxData=AT24C02_Read_Byte(0);
	AT24C02_IIC_Stop();
	return RxData;	
}

//��AT24C02ָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24C02_WriteOneByte(u8 WriteAddr,u8 DataToWrite)
{
	u32 i;
	AT24C02_IIC_Start();
	AT24C02_Send_Byte(0xA0);
  AT24C02_IIC_Wait_Ack();
	AT24C02_Send_Byte(WriteAddr);   //���͵�ַ
	AT24C02_IIC_Wait_Ack();
	AT24C02_Send_Byte(DataToWrite);
	AT24C02_IIC_Wait_Ack();
	AT24C02_IIC_Stop();	
	for(i=0;i<1000000;i++);
}

//��AT24C02�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24C02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24C02_Read(u8 ReadAddr,u8 *pBuffer,u8 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24C02_ReadOneByte(ReadAddr++);
		NumToRead--;
	}
}

//��AT24C02�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24C02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24C02_Write(u8 WriteAddr,u8 *pBuffer,u8 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24C02_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}

//IIC��ʼ�ź�
void AT24C02_IIC_Start(void)
{
	u8 i;
	AT24C02_SDA_OUT();
	AT24C02_SDA=1;
	AT24C02_SCL=1;
	for(i=0;i<50;i++);
	AT24C02_SDA=0;
	for(i=0;i<50;i++);
	AT24C02_SCL=0;
}

//IIC�����ź�
void AT24C02_IIC_Stop(void)
{
	u8 i;
	AT24C02_SDA_OUT();
	AT24C02_SDA=0;
	AT24C02_SCL=0;
  for(i=0;i<50;i++);
	AT24C02_SCL=1;
	AT24C02_SDA=1;
  for(i=0;i<50;i++);
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 AT24C02_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0,i=0;
	AT24C02_SDA_IN();
	AT24C02_SDA=1;
	for(i=0;i<20;i++); 
	AT24C02_SCL=1;
	for(i=0;i<20;i++); 	 
	while(AT24C02_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			AT24C02_IIC_Stop();
			return 1;
		}
	}
	AT24C02_SCL=0;//ʱ�����0 	   
	return 0;  
}

//����ACKӦ��
void AT24C02_IIC_Ack(void)
{
	u8 i;
	AT24C02_SCL=0;
	AT24C02_SDA_OUT();
	AT24C02_SDA=0;
	for(i=0;i<20;i++); 
	AT24C02_SCL=1;
	for(i=0;i<20;i++); 
	AT24C02_SCL=0;
}

//������ACKӦ��		    
void AT24C02_IIC_NAck(void)
{
	u8 i;
	AT24C02_SCL=0;
	AT24C02_SDA_OUT();
	for(i=0;i<20;i++); 
	AT24C02_SCL=1;
	for(i=0;i<20;i++); 
	AT24C02_SCL=0;
}

//AT24C02����һ���ֽ�
void AT24C02_Send_Byte(u8 TxData)
{                        
  u8 t,i;   
	AT24C02_SDA_OUT(); 	    
  AT24C02_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
  for(t=0;t<8;t++)
  {              
    AT24C02_SDA=(TxData&0x80)>>7;
    TxData<<=1; 
    for(i=0;i<20;i++); 	   
		AT24C02_SCL=1;
		for(i=0;i<20;i++); 	 
		AT24C02_SCL=0;	
		for(i=0;i<20;i++); 
   }	 
} 

//AT24C02��ȡһ���ֽ�
u8 AT24C02_Read_Byte(u8 Ack)
{
	u8 i,j,RxData;
	AT24C02_SDA_IN();
	for(i=0;i<8;i++)
	{
		AT24C02_SCL=0;	
		for(j=0;j<20;j++); 
		AT24C02_SCL=1;
		RxData<<=1;
		RxData+=AT24C02_READ_SDA;	
		for(j=0;j<20;j++);
	}
	if(Ack)
		AT24C02_IIC_Ack();
	else
		AT24C02_IIC_NAck();	
	return RxData;
}
