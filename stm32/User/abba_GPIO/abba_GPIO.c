#include "abba_GPIO.h"

/*
**************************************************
GPIO初始化函数
参数1:端口外设号A-E
参数2:引脚号Pin0-Pin16
参数3:引脚工作模式
		_AIN			模拟输入
		_IN_FLOATING	浮空输入
		_IPD			下拉输入
		_IPU			上拉输入
		_Out_OD			开漏输出
		_Out_PP			推挽输出
		_AF_OD			复用开漏输出
		_AF_PP			复用推挽输出
参数5:端口初始化值
备注:引脚工作速度默认50Mhz
**************************************************
*/

void abba_GPIO_Init(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode,uint8_t GPIO_Init_val)
{
	GPIO_InitTypeDef GPIO_temp;
	if(GPIOx == GPIOA)//开启对应端口时钟
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if(GPIOx == GPIOB)
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if(GPIOx == GPIOC)
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE);
	}
	else if(GPIOx == GPIOD)
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);
	}
	else if(GPIOx == GPIOE)
	{
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE);
	}
	GPIO_temp.GPIO_Pin  = GPIO_Pin;//设置引脚
	GPIO_temp.GPIO_Mode = GPIO_Mode;//设置工作模式
	GPIO_temp.GPIO_Speed = GPIO_Speed_50MHz;//设置工作速度
	
	GPIO_Init(GPIOx,&GPIO_temp);//调用官方库初始化
	abba_GPIO_WriteBit(GPIOx,GPIO_Pin,GPIO_Init_val);//初始化写入
}

/*
**************************************************
GPIO端口数据写入
参数1:端口外设号A-E
参数2:引脚号Pin0-Pin16
参数3:端口写入值
e.g.  :BSRR低16位地址写1置高电平,高16位地址写一置低电平
**************************************************
*/
void abba_GPIO_WriteBit(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin,uint8_t GPIO_Init_val)
{
	if(GPIO_Init_val==1)
	{
		GPIO_Init_val = 0;
	}
	else 
	{
		GPIO_Init_val = 1;
	}
	GPIOx->BSRR=GPIO_Pin<<(GPIO_Init_val*16);//设置初始化值
}


/*
**************************************************
GPIO端口电平翻转
参数1:端口外设号A-E
参数2:引脚号Pin0-Pin16
**************************************************
*/
void abba_GPIO_Toggle(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	GPIOx->ODR ^= GPIO_Pin;
}


/*
**************************************************
GPIO端口电平读取
参数1:端口外设号A-E
参数2:引脚号Pin0-Pin16
返回值:电平高低
**************************************************
*/
uint8_t abba_GPIO_ReadBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	uint8_t bitstatus = 0x00;
	if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
	{
		bitstatus = (uint8_t)Bit_SET;
	}	
	else
	{
		bitstatus = (uint8_t)Bit_RESET;
	}
	return bitstatus;
}



/*********************************************END OF FILE**********************/
