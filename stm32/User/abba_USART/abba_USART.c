#include "abba_USART.h"
#include <string.h>
#include <stdio.h>
/*
**************************************************
USART初始化函数
参数1:串口号USART1-USART2
参数2:串口波特率
参数3:配置模式
		TX_mode		只发送模式
		RX_mode		只接收模式
		TX_RX_mode	发送和接收模式
		(注:接收方式皆为中断接收 初始化时注意中断优先级 中断配置文件中有全局变量RecChar接收一个字节的信息)
备注:目前只配置了USART1及USART2切只配置了最基本功能:8位收发,无校验,无流控,1位停止位
**************************************************
*/
void abba_USART_Init(USART_TypeDef* USARTx,uint32_t USART_BaudRate,uint8_t USART_Mode)
{
	USART_InitTypeDef USART_temp;
		
	if((USART_Mode&RX_Mode)==RX_Mode)
	{
		if(USARTx == USART1)
		{		
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);//开启IO复用几USART1的引脚时钟
			abba_GPIO_Init(GPIOA,GPIO_Pin_10,GPIO_Mode_IPU,0);
		}
		else if(USARTx == USART2)
		{
			abba_GPIO_Init(GPIOA,GPIO_Pin_3,GPIO_Mode_IPU,0);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE); //(注:USART2挂在RCC_APB2时钟上)
		}
		USART_temp.USART_Mode |= USART_Mode_Rx;
		USART_ITConfig(USARTx,USART_IT_RXNE,ENABLE);//使能USART接收中断
	}
	if((USART_Mode&TX_Mode) == TX_Mode)
	{
		if(USARTx == USART1)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
			abba_GPIO_Init(GPIOA,GPIO_Pin_9,GPIO_Mode_AF_PP,0);
		}
		else if(USARTx == USART2)
		{
			abba_GPIO_Init(GPIOA,GPIO_Pin_2,GPIO_Mode_AF_PP,0);
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);
		}
		USART_temp.USART_Mode |= USART_Mode_Tx;
	}

	USART_temp.USART_BaudRate = USART_BaudRate;
	USART_temp.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_temp.USART_WordLength = USART_WordLength_8b;
	USART_temp.USART_StopBits = USART_StopBits_1;
	USART_temp.USART_Parity = USART_Parity_No;
	USART_Init(USARTx,&USART_temp);
	USART_Cmd(USARTx, ENABLE);
}
/*
**************************************************
USART_DMA发送模式初始化函数
参数1:串口号USART1-USART2
参数2:发送的数据地址
参数3:发送数据的长度
参数4:发送模式
		_Normal 单次发送模式
		_Circular 反复发送模式
参数5:DMA优先级
		_VeryHigh
		_High
		_Medium
		_Low
		(注意这里的优先级指的是同一DMA下的优先级,USART1-USART3都在DMA1)
备注:由于对DMA的不熟悉暂时没写DMA采集模式,这里模式发送数据单位为一个字节
使用方法:当采用初始化后调用 USART_DMACmd(USARTx, USART_DMAReq_Tx, ENABLE);函数触发DMA发送
**************************************************
*/
void abba_USART_DMA_Init(USART_TypeDef* USARTx,uint8_t Send[],uint32_t SENDBUFF_SIZE,uint32_t DMA_Mode,uint32_t DMA_Priority)
{
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);		   
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)Send;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;	
	DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
	DMA_InitStructure.DMA_Mode = DMA_Mode;//DMA_Mode_Circular;	 
	DMA_InitStructure.DMA_Priority = DMA_Priority;  
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	if(USARTx == USART1)
	{
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(USART1) + 0x04;
		DMA_Init(DMA1_Channel4, &DMA_InitStructure); 	   
		DMA_Cmd (DMA1_Channel4,ENABLE);		
	}
	else if(USARTx == USART2)
	{
		DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(USART2) + 0x04;
		DMA_Init(DMA1_Channel7, &DMA_InitStructure); 	   
		DMA_Cmd (DMA1_Channel7,ENABLE);
	}
}
/*
**************************************************
USART发送字符串函数
参数1:串口号USART1-USART2
参数2:需发送的字符串
**************************************************
*/
void abba_USART_SendString(USART_TypeDef* USARTx,char *s)
{
	while(*s != '\0')
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
		USARTx->DR = (*s & (uint16_t)0x01FF);
		s++;
	}
	
}

/*
**************************************************
USART发送单字符字符函数
参数1:串口号USART1-USART2
参数2:需发送的字符
**************************************************
*/

void abba_USART_SendChar(USART_TypeDef* USARTx,char s)
{
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	USARTx->DR = (s & (uint16_t)0x01FF);
}


int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	
		return (ch);
}


/*********************************************END OF FILE**********************/
