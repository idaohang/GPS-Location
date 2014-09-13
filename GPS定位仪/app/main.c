#include "stm32f10x.h"
#include "abba_GPIO.h"
#include "abba_I2C.h"
#include "abba_USART.h"
#include "abba_ISR.h"
#include "abba_TIM.h"
#include "GPS.h"
#include "GSM.h"


Datapack Data;
uint8_t flag_1s = 0;
uint8_t Rec_flag = 0;
void Init()
{
	abba_USART_Init(USART1,9600,RX_TX_Mode);
	abba_USART_Init(USART2,9600,TX_Mode);
	//abba_GPIO_Init(GPIOB,GPIO_Pin_0,GPIO_Mode_Out_PP,1);
	//abba_PIT_Init(TIM7,1);
	NVIC_Configuration(NVIC_PriorityGroup_1,USART1_IRQn,0,1);
	//NVIC_Configuration(NVIC_PriorityGroup_1,USART2_IRQn,0,0);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7 , ENABLE);
	httpInit();
	Data.countlat = 0;
	Data.countlon = 0;
	Data.countUTC = 0;
}
int main(void)
{
	Init();
	while(1)
	{
		if(Rec_flag == 1)
		{
			if(Data.status=='A')
			{
			
				Send_PostMessage(&Data);
				Data.countlat = 0;
				Data.countlon = 0;
				Data.countUTC = 0;
				Data.status = 'V';
			}
			else
			{
				printf("¶¨Î»Ê§°Ü");
			}
			Rec_flag = 0;
			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		}
	}
}

