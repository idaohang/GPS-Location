#include "EXIT.h"

/***********************
函数功能：外部中断初始化
输入参数：无
输出参数：无
备    注：PA2
***********************/
void EXTI_Init(void)
{
    EXIT_GPIO->DDR &=~EXIT_PIN;//输入模式
    EXIT_GPIO->CR1 |= EXIT_PIN;//上拉输入
    EXIT_GPIO->CR2 |= EXIT_PIN;//使能外部中断
     
    EXTI->CR1  |= BIT(1);//PA下降沿触发  
    
    asm("rim");    //开总中断
}


#pragma   vector = EXTI0_PA_vector
__interrupt  void  EXTI0_PA_IRQHandler(void)
{
    asm("sim");    //关总中断
      //PA2中断
    if(!(GPIOA->IDR&0X04))
    {    
          LED_ON();
    }
    
    asm("rim");    //开总中断
}


#pragma vector = TIM4_Updata_vector
__interrupt void TIM4_Updata_IRQHandler(void)
{
    sim();//关总中断

    
    TIM4->SR1 &=~BIT(0);//清标志位
    rim();//开总中断
}

