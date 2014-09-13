
#ifndef __DS1302_H__
#define __DS1302_H__
#include "Sys.h"   

/*sbit SCK=D2;		
sbit SDA=D3;		
sbit RST=D4;*/
//复位脚
#define RST_CLR	PBO(0,0)//电平置低
#define RST_SET	PBO(0,1)//电平置高


//双向数据
#define IO_CLR	PBO(1,0)//电平置低
#define IO_SET	PBO(1,1)//电平置高
#define IO_R	PB(1)  //电平读取


//时钟信号
#define SCK_CLR	PBO(2,0)//时钟信号
#define SCK_SET	PBO(2,1)//电平置高


#define ds1302_sec_add			0x80		//秒数据地址
#define ds1302_min_add			0x82		//分数据地址
#define ds1302_hr_add			0x84		//时数据地址
#define ds1302_date_add			0x86		//日数据地址
#define ds1302_month_add		0x88		//月数据地址
#define ds1302_day_add			0x8a		//星期数据地址
#define ds1302_year_add			0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

typedef struct 
{
  u16 year;
  u8 mouth;
  u8 day;
  u8 hour;
  u8 min;
  u8 sec;
}time;

void DSWrite(time *buf); 
void DSRead(time *buf);  
void Ds1302_Init(void);

#endif
