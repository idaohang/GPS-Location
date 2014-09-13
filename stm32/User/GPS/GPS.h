#ifndef __GPS_H
#define __GPS_H


#include "stm32f10x.h"
#include "abba_USART.h"
//#include "GSM.h"
typedef struct 
{
	char UTC[11];//UTC时间
	char status;//当前数据包的状态 可用于判断是否为有效数据
	char latitude[10];//纬度
	char lat;//南北纬
	char longitude[11];//经度
	char lon;//东西经
	uint8_t countUTC;//当前UTC数组长度
	uint8_t countlat;//同上(纬度)
	uint8_t countlon;//同上(经度)
}Datapack;
//初始化时记得 将数组长度个数全赋值为0  status为'V'
uint8_t GPRMC_Analyze(char temp,Datapack* pack);
void Sendpack(Datapack* pack);


#endif //__GPS_H

