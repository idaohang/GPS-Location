#ifndef __ABBA_GPIO_H
#define	__ABBA_GPIO_H


#include "stm32f10x.h"

void abba_GPIO_Init(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,uint8_t GPIO_Init_val);
void abba_GPIO_WriteBit(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint8_t GPIO_Init_val);
void abba_GPIO_Toggle(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);
uint8_t abba_GPIO_ReadBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif //__ABBA_GPIO_H

