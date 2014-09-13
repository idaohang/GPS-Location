#ifndef _OLED_H_
#define _OLED_H_

#include "sys.h"
void Init_OLED(void);
void clear_OLED(void);
void setCharsOLED(u8 *disbuf,u8 x,u8 y);
void Dis_fnum(float num,u8 x,u8 y);
void drpic(u8 *pic);
void setCharOLED(char c);
void addrOLED(u16 column,u16 page);
void WriteIIC_Dat(u8 IIC_Data);


#endif