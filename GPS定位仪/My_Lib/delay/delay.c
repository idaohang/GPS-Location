#include"delay.h"

/***********************
函数功能：us延时
输入参数：无
输出参数：无
备    注：粗略延时
***********************/
void delay_us(u16 time)
{ 
  while(time--)  
  {;;}
}

/***********************
函数功能：ms延时
输入参数：无
输出参数：无
备    注：粗略延时
***********************/
void delay_ms(u16 time)
{
    u16 i;
    while(time--)  
      for(i=1900;i>0;i--);
}
