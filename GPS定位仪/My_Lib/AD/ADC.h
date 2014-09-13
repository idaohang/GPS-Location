#ifndef _ADC_H
#define _ADC_H

#include "Sys.h"

#define Channel_2       0x02
#define Channel_3       0x03
#define Channel_4       0x04
#define Channel_5       0x05
#define Channel_6       0x06


/***************************
AD IO¿Úºê¶¨Òå
***************************/
#define ADC_GPIO        GPIOC
#define ADC_PIN         (1<<4)


void ADC_Init(u8 Channel);
u16 ADC_Data(void);
void ADC_IOConfig(void);


#endif
