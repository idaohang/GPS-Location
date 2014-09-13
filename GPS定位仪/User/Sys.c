#include "Sys.h"

void Sys_init(void)
{
    CLK_init(1);//系统时钟初始化  
    UART_Init(9600);
    Init_OLED();
    delay_ms(1000);
    Ds1302_Init();
}
void CLK_init(u8 ch)
{
   //时钟配置为内部RC，16M
   if(ch==0)
     CLK->CKDIVR &=~(BIT(4)|BIT(3));
   else
   {
     CLK->ECKR = 0X01;   //允许外部高速振荡器工作
     while((CLK->ECKR & 0x02) == 0x00);  //等待外部高速振荡器准备好    
     CLK->SWCR |= 0x02; // SWEN <- 1
     CLK->SWR = 0xB4;
     while(CLK->SWCR & 0x08==0);
     CLK->SWCR &= 0xFD; // 清除切换标志
   }
}

    
