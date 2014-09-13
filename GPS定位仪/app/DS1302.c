#include "ds1302.h"

void ds_rdinit(void);
void ds_wrinit(void);


void DSWriteDat(u8 addr, u8 d)
{
  u8 i;
  RST_SET;	
  delay_us(5);
  //写入目标地址：addr
  addr = addr & 0xFE;     //最低位置零
  for (i = 0; i < 8; i ++) 
  { 
          if (addr & 0x01) 
          {
              IO_SET;
          }
          else 
          {
              IO_CLR;
          }
          delay_us(5);
          SCK_SET;
          delay_us(5);
          SCK_CLR;
          addr = addr >> 1;
  }
  delay_us(5);
  //写入数据：d
  for (i = 0; i < 8; i ++) 
  {
          if (d & 0x01) 
          {
                  IO_SET;
          }
          else 
          {
                  IO_CLR;
          }
          delay_us(5);
          SCK_SET;
          delay_us(5);
          SCK_CLR;
          d = d >> 1;
  }
  delay_us(5);
  RST_CLR;	//停止DS1302总线
  delay_us(5);
}
/*------------------------------------------------
从DS1302读出一字节数据
------------------------------------------------*/

u8 DSReadDat(u8 addr) 
{
    u8 i;
    u8 temp;
    RST_SET;	
    delay_us(5);
    //写入目标地址：addr
    addr = addr | 0x01;//最低位置高
    for (i = 0; i < 8; i ++) 
    {
            if (addr & 0x01) 
            {
                    IO_SET;
            }
            else 
            {
                    IO_CLR;
            }
            delay_us(5);
            SCK_SET;
            delay_us(5);
            SCK_CLR;
            addr = addr >> 1;
    }
    delay_us(5);
    //输出数据：temp
    ds_rdinit();
    for (i = 0; i < 8; i ++) 
    {
            temp = temp >> 1;
            if (IO_R) 
            {
                    temp |= 0x80;
            }
            else 
            {
                    temp &= 0x7F;
            }
            delay_us(5);
            SCK_SET;
            delay_us(5);
            SCK_CLR;
    }
    delay_us(5);
    ds_wrinit();
    RST_CLR;	//停止DS1302总线
    delay_us(5);
    return temp;
}

/*------------------------------------------------
向DS1302写入时钟数据
------------------------------------------------*/
void DSWrite(time *buf) 
{
    buf->year=buf->year%10+(u16)(buf->year/10)*16;
    buf->mouth=buf->mouth%10+(u8)(buf->mouth/10)*16;
    buf->day=buf->day%10+(u8)(buf->day/10)*16;
    buf->hour=buf->hour%10+(u8)(buf->hour/10)*16;
    buf->min=buf->min%10+(u8)(buf->min/10)*16;
    buf->sec=buf->sec%10+(u8)(buf->sec/10)*16;

    DSWriteDat(ds1302_control_add,0x00);			//关闭写保护 
    DSWriteDat(ds1302_sec_add,0x80);				//暂停 
    //DSWriteDat(ds1302_charger_add,0xa9);			//涓流充电 
    DSWriteDat(ds1302_year_add,buf->year);		//年 
    DSWriteDat(ds1302_month_add,buf->mouth);	//月 
    DSWriteDat(ds1302_date_add,buf->day);		//日 
    //DSWriteDat(ds1302_day_add,timebuf[7]);		//周 
    DSWriteDat(ds1302_hr_add,buf->hour);		//时 
    DSWriteDat(ds1302_min_add,buf->min);		//分
    DSWriteDat(ds1302_sec_add,buf->sec);		//秒
    //DSWriteDat(ds1302_day_add,timebuf[7]);		//周 
    DSWriteDat(ds1302_control_add,0x80);			//打开写保护 
}

/*------------------------------------------------
从DS1302读出时钟数据
------------------------------------------------*/
void DSRead(time *buf)  
{ 
  delay_ms(10);buf->year=DSReadDat(ds1302_year_add);		//年 
  delay_ms(10);buf->mouth=DSReadDat(ds1302_month_add);		//月 
  delay_ms(10);buf->day=DSReadDat(ds1302_date_add);		//日 
  delay_ms(10);buf->hour=DSReadDat(ds1302_hr_add);		//时 
  delay_ms(10);buf->min=DSReadDat(ds1302_min_add);		//分 
  delay_ms(10);buf->sec=(DSReadDat(ds1302_sec_add))&0x7F;//秒 
  //time_buf[6]=DSReadDat(ds1302_day_add);		//周 
  
  buf->year=buf -> year%16 +(u16)(buf->year/16)*10;
  buf->mouth=buf-> mouth%16+(u8)(buf->mouth/16)*10;
  buf->day=buf  -> day%16  +(u8)(buf->day/16)*10;
  buf->hour=buf -> hour%16 +(u8)(buf->hour/16)*10;
  buf->min=buf  -> min%16  +(u8)(buf->min/16)*10;
  buf->sec=buf  -> sec%16  +(u8)(buf->sec/16)*10;
}

void ds_rdinit(void)
{
   GPIOB->DDR &= ~(1<<1);//输入模式
   GPIOB->CR1 |=  (1<<1);//上拉输入
   GPIOB->CR2 &=~(1<<1);
}
void ds_wrinit(void)
{
  GPIOB->DDR  |=  (1<<1);
  GPIOB->CR1  |=  (1<<1);
}
/*------------------------------------------------
DS1302初始化
------------------------------------------------*/
void Ds1302_Init(void)
{
  GPIOB->DDR  |=  (5<<0);
  GPIOB->CR1  |=  (5<<0);
  ds_wrinit();
  RST_CLR;			//RST脚置低
  delay_us(5);
  SCK_CLR;			//SCK脚置低
  delay_us(5);
  DSWriteDat(ds1302_sec_add,0x00);				 
}
