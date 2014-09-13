#include "PWM.h"

/**********************************
函数功能：PWM初始化
输入参数：无
输出参数：无
备    注：定时器2通道3 输出脚为PA3
**********************************/
void PWM_Init(void)
{    
    TIM2-> PSCR |= 4;//预分频器
    TIM2-> ARRH = 0x03;//装载计数值高位 
    TIM2-> ARRL = 0xE7;////装载计数值低位

    
    TIM2-> CCMR1 |= BIT(6)|BIT(5)|BIT(3);
    TIM2-> CCR1H = 0x01;//比较值高位，通道3的设置，其它通道需要修改 
    TIM2-> CCR1L = 0xF4;//比较值低位，通道3的设置，其它通道需要修改  
    TIM2-> CCER1 |= BIT(0);//输出使能,通道3的设置，其它通道需要修改
    //TIM2-> CR1 |= BIT(0);//计数器使能
    
    TIM2-> CCMR2 |= BIT(6)|BIT(5)|BIT(3);//pwm模式1、预装载使能，通道3的设置，其它通道需要修改 
    TIM2-> CCR2H = 0x01;//比较值高位，通道3的设置，其它通道需要修改 
    TIM2-> CCR2L = 0xF4;//比较值低位，通道3的设置，其它通道需要修改  
    TIM2-> CCER1 |= BIT(4);//输出使能,通道3的设置，其它通道需要修改  
    //TIM2-> CR1 |= BIT(0);//计数器使能
    
    TIM2-> CCMR3 |= BIT(6)|BIT(5)|BIT(3);
    TIM2-> CCR3H = 0x01;//比较值高位，通道3的设置，其它通道需要修改 
    TIM2-> CCR3L = 0xF4;//比较值低位，通道3的设置，其它通道需要修改  
    TIM2-> CCER2 |= BIT(0);//输出使能,通道3的设置，其它通道需要修改
      
    TIM2-> CR1 |= BIT(0);//计数器使能
}

void PwmR(u16 x)
{
   x=255-x;
   x=x*4;
   TIM2-> CCR1H = (x>>8);//比较值高位，通道3的设置，其它通道需要修改 
   TIM2-> CCR1L = (x&0xff);
}
void PwmG(u16 x)
{
   x=255-x;
   x=x*4;
   TIM2-> CCR2H = (x>>8);//比较值高位，通道3的设置，其它通道需要修改 
   TIM2-> CCR2L = (x&0xff);
}
void PwmB(u16 x)
{
   x=255-x;
   x=x*4;
   TIM2-> CCR3H = (x>>8);//比较值高位，通道3的设置，其它通道需要修改 
   TIM2-> CCR3L = (x&0xff);
}
void SetColor(u32 color)
{
    PwmB(color>>16&0xff);
    PwmG(color>>8&0xff);
    PwmR(color&0xff);
}

