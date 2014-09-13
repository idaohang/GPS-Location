#ifndef __ABBA_ISR_H
#define	__ABBA_ISR_H

#include <stdio.h>
#include "stm32f10x.h"
#include "GPS.h"


void NVIC_Configuration(uint32_t NVIC_PriorityGroup,uint8_t IRQn_Channel,uint8_t IRQChannelPreemptionPriority,uint8_t IRQChannelSubPriority);
void abba_EXIT_Init(uint8_t GPIO_PortSource,uint8_t GPIO_PinSource,EXTIMode_TypeDef EXTI_Mode,EXTITrigger_TypeDef EXTI_Trigger);


#endif //__ABBA_ISR_H

