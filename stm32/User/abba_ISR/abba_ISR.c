#include "abba_ISR.h"
char RecChar1,RecChar2;
extern Datapack Data;
extern uint8_t Rec_flag;
/*
**************************************************
嵌套中断配置初始化
参数1:优先级组别
		NVIC_PriorityGroup_0 	抢占优先级0 次优先级4(位)
		NVIC_PriorityGroup_1	抢占优先级1 次优先级3(位)
		NVIC_PriorityGroup_2	抢占优先级2 次优先级2(位)
		NVIC_PriorityGroup_3	抢占优先级3 次优先级1(位)
		NVIC_PriorityGroup_4	抢占优先级4 次优先级0(位)
参数2:中断标号 头文件"stm32f10x.h"中标号的定义
参数3:抢占优先级,根据参数一所设置的位数限定最大值0-15
参数4:次优先级,根据参数一所设置的位数限定最大值0-15
**************************************************
*/
void NVIC_Configuration(uint32_t NVIC_PriorityGroup,uint8_t IRQn_Channel,uint8_t IRQChannelPreemptionPriority,uint8_t IRQChannelSubPriority)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup);
  
  NVIC_InitStructure.NVIC_IRQChannel = IRQn_Channel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = IRQChannelPreemptionPriority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = IRQChannelSubPriority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*
**************************************************
外部中断初始化
参数1:GPIO中断源组别  	GPIO_PortSourceGPIOA-G       
参数2:中断线路    		GPIO_PinSource0-15 
参数3:外部中断模式
			EXTI_Mode_Event 		事件请求
			EXTI_Mode_Interrupte	中断请求
参数4:触发方式
			EXTI_Trigger_Falling			下降沿触发
			EXTI_Trigger_Rising				上升沿触发
			EXTI_Trigger_Rising_Falling		上升沿或下降沿触发
**************************************************
*/
void abba_EXIT_Init(uint8_t GPIO_PortSource,uint8_t GPIO_PinSource,EXTIMode_TypeDef EXTI_Mode,EXTITrigger_TypeDef EXTI_Trigger)
{
	uint32_t EXTI_Line;
	uint8_t i,GPIO_Pin_temp = GPIO_PinSource0;
	EXTI_InitTypeDef EXTI_temp;

	GPIO_EXTILineConfig(GPIO_PortSource, GPIO_PinSource);
	EXTI_Line = EXTI_Line0;
	for(i=0;i<16;i++)
	{
		if(GPIO_PinSource == GPIO_Pin_temp)
		{
			break;
		}
		GPIO_Pin_temp++;
		EXTI_Line += EXTI_Line;
	}
	
	EXTI_temp.EXTI_Line = EXTI_Line;
	EXTI_temp.EXTI_Mode = EXTI_Mode;
	EXTI_temp.EXTI_Trigger = EXTI_Trigger;
	EXTI_temp.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_temp);
	
											
	
}


/*
**************************************************
中断向量定义在文件 "startup_stm32f10x_hd.s" 均可找到
**************************************************
*/

/*
**************************************************
外部中断函数管理
EXTI0_IRQHandler - EXTI15_10_IRQHandler
中断函数完成后,视情况而定清楚标志位
void EXTI_ClearFlag(u32 EXTI_Line));
EXTI->PR = EXTI_Line;
**************************************************
*/

void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI1_IRQHandler(void)
{
}
void EXTI2_IRQHandler(void)
{
}
void EXTI3_IRQHandler(void)
{
}
void EXTI4_IRQHandler(void)
{
}
void EXTI9_5IRQHandler(void)
{
}

void EXTI15_10_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line13);
}


void USART1_IRQHandler()
{
	RecChar1 = USART_ReceiveData(USART1);
	Rec_flag = GPRMC_Analyze(RecChar1,&Data);
}

void USART2_IRQHandler()
{
	RecChar2 = USART_ReceiveData(USART2);
	USART_SendData(USART1,RecChar2);
}
extern uint8_t flag_1s;



void TIM2_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM2 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM3_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM3 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM3 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM4_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM4 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM4 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM5_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM5 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM5 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM6_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM6 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM6 , TIM_FLAG_Update);  		 
	}		 	
}

void TIM7_IRQHandler(void)
{
	static uint16_t time = 0;
	if ( TIM_GetITStatus(TIM7 , TIM_IT_Update) != RESET ) 
	{	
		if(++time>1000)
		{
			flag_1s = 1;
			time = 0;
		}
		TIM_ClearITPendingBit(TIM7 , TIM_FLAG_Update);  		 
	}		 	
}



/*********************************************END OF FILE**********************/
