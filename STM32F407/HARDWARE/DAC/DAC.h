#ifndef __DAC_H
#define __DAC_H

#include "sys.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dac.h"

void sin_Generation(u16 Fre,u16 Vol);
void TIM6_Configuration(u16 Fre);
void GPIO_Configuration(void);
void DAC_DMA_Configuration(void);
void TIM4_PWM_Init(u32 arr,u32 psc);

#endif
