#ifndef __SYS_H_
#define __SYS_H_


#include "stdio.h"
#include "stm8s.h"
#include "mytype.h"

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define uc8 const unsigned char


#include "led.h"
#include "USART.h"
#include "delay.h"
//#include "ADC.h"
//#include "Time.h"
#include "OLED.h"
#include "ds1302.h"
#include "GPS.h"
#include "GSM.h"

#define   UART3_RX_vector          0x17

#define PAO(n,x) (x==1)?(GPIOA->ODR|=(1<<n)):(GPIOA->ODR&=~BIT(n))
#define PBO(n,x) (x==1)?(GPIOB->ODR|=(1<<n)):(GPIOB->ODR&=~BIT(n))
#define PCO(n,x) (x==1)?(GPIOC->ODR|=(1<<n)):(GPIOC->ODR&=~BIT(n))
#define PDO(n,x) (x==1)?(GPIOD->ODR|=(1<<n)):(GPIOD->ODR&=~BIT(n))
#define PEO(n,x) (x==1)?(GPIOE->ODR|=(1<<n)):(GPIOE->ODR&=~BIT(n))
#define PFO(n,x) (x==1)?(GPIOF->ODR|=(1<<n)):(GPIOF->ODR&=~BIT(n))

#define PA(n) ((GPIOA->IDR>>n)&0x01)
#define PB(n) ((GPIOB->IDR>>n)&0x01)
#define PC(n) ((GPIOC->IDR>>n)&0x01)
#define PD(n) ((GPIOD->IDR>>n)&0x01)
#define PF(n) ((GPIOF->IDR>>n)&0x01)

void CLK_init(u8 ch);
void Sys_init(void);

#endif