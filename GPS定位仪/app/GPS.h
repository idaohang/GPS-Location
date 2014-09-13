#ifndef __GPS_H
#define __GPS_H


#include "Sys.h"
typedef struct 
{
      char UTC[11];//UTC时间
      char status;//当前数据包的状态 可用于判断是否为有效数据
      char latitude[10];//纬度
      char lat;//南北纬
      char longitude[11];//经度
      char lon;//东西经
      u8 countUTC;//当前UTC数组长度
      u8 countlat;//同上(纬度)
      u8 countlon;//同上(经度)
}Datapack;
//初始化时记得 将数组长度个数全赋值为0  status为'V'
uint8_t GPRMC_Analyze(char temp,Datapack* pack);
//void Sendpack(Datapack* pack);
void Dispack(Datapack* pack);


#endif //__GPS_H

