#ifndef __ABBA_USART_H
#define __ABBA_USART_H

#include "stm32f10x.h"
#include "abba_GPIO.h"
#include <stdio.h>

#define RX_Mode 	1
#define TX_Mode 	2
#define RX_TX_Mode	RX_Mode | TX_Mode
void abba_USART_Init(USART_TypeDef* USARTx,uint32_t USART_BaudRate,uint8_t USART_Mode);
void abba_USART_SendString(USART_TypeDef* USARTx,char *s);
void abba_USART_SendChar(USART_TypeDef* USARTx,char s);
void abba_USART_DMA_Init(USART_TypeDef* USARTx,uint8_t Send[],uint32_t SENDBUFF_SIZE,uint32_t DMA_Mode,uint32_t DMA_Priority);
#endif //__ABBA_USART_H
