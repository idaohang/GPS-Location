#ifndef  _USART_H
#define  _USART_H

#include "Sys.h"

//定义UART的TX、RX引脚
#define  TXPort  GPIOA
#define  TXPin   (1 << 4) 
#define  RXPort  GPIOA
#define  RXPin   (1 << 5)

#define  TX3Port  GPIOD
#define  TX3Pin   (1 << 5) 
#define  RX3Port  GPIOD
#define  RX3Pin   (1 << 6)

#define SYS_Clk 11059200l

void UART_Init(u32 baud);
void UART_SendChar(unsigned char ch);
void UART_IOConfig(void);
u8 UART_GetChar(void);
void UART3_SendChar(unsigned char ch);
u8 UART3_GetChar(void);
void sendChars(u8 *disbuf);

#endif