#include "OLED.h"
#include "font.h"


//SCL  B4   SDA  B6

void Init_OLED(void);
void fill_picture(u8 fill_Data);
void IIC_Start(void);
void IIC_Stop(void);
void WriteIIC_Cmd(u8 IIC_Command);
void WriteIIC_Dat(u8 IIC_Data);
void WriteIIC_Byt(u8 IIC_Byte);


void Init_OLED(void)    //1-8 1-128
{
    GPIOB->DDR   |=  (5<<4);
    GPIOB->CR1   |=  (5<<4);
    delay_ms(100);
    WriteIIC_Cmd(0xAE);   //display off
    WriteIIC_Cmd(0x20);	//Set Memory Addressing Mode                                                                                0010 0000
    WriteIIC_Cmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid      0001 0000
    WriteIIC_Cmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7                                                       1011 0000
    WriteIIC_Cmd(0xc0);	//Set COM Output Scan Direction                                                                             1100 1000  

    WriteIIC_Cmd(0x00);//---set low column address
    WriteIIC_Cmd(0x10);//---set high column address
    WriteIIC_Cmd(0x40);//--set start line address
    WriteIIC_Cmd(0x81);//--set contrast control register
    WriteIIC_Cmd(0x7f);
    WriteIIC_Cmd(0xa0);//--set segment re-map 0 to 127    1010 0001
    WriteIIC_Cmd(0xa6);//--set normal display             1010 0110 
    WriteIIC_Cmd(0xa8);//--set multiplex ratio(1 to 64)   1010 1000
    WriteIIC_Cmd(0x3F);//
    WriteIIC_Cmd(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    WriteIIC_Cmd(0xd3);//-set display offset
    WriteIIC_Cmd(0x00);//-not offset
    WriteIIC_Cmd(0xd5);//--set display clock divide ratio/oscillator frequency
    WriteIIC_Cmd(0xf0);//--set divide ratio
    WriteIIC_Cmd(0xd9);//--set pre-charge period
    WriteIIC_Cmd(0x22); //
    WriteIIC_Cmd(0xda);//--set com pins hardware configuration
    WriteIIC_Cmd(0x12);
    WriteIIC_Cmd(0xdb);//--set vcomh
    WriteIIC_Cmd(0x20);//0x20,0.77xVcc
    WriteIIC_Cmd(0x8d);//--set DC-DC enable
    WriteIIC_Cmd(0x14);//
    WriteIIC_Cmd(0xaf);//--turn on oled panel 
}


void IIC_Start(void)
{
   PBO(4,1);	
   PBO(6,1);
   PBO(6,0);
   PBO(4,0);
}

void IIC_Stop(void)
{
   PBO(4,0);
   PBO(6,0);
   PBO(4,1);
   PBO(6,1);
}

void WriteIIC_Byt(u8 IIC_Byte)
{
    u8 i;
    for(i=0;i<8;i++)		
    {
        if(IIC_Byte & 0x80)		//1?0?
          PBO(6,1);
        else
          PBO(6,0);
        PBO(4,1);
        PBO(4,0);
        IIC_Byte<<=1;			//loop
    }
    PBO(6,1);
    PBO(4,1);
    PBO(4,0);
}

void WriteIIC_Cmd(u8 IIC_Command)
{
   IIC_Start();
   WriteIIC_Byt(0x78);            //Slave address,SA0=0
   WriteIIC_Byt(0x00);			//write command
   WriteIIC_Byt(IIC_Command); 
   IIC_Stop();
}

void WriteIIC_Dat(u8 IIC_Data)
{
   IIC_Start();
   WriteIIC_Byt(0x78);			
   WriteIIC_Byt(0x40);			//write data
   WriteIIC_Byt(IIC_Data);
   IIC_Stop();
}

void addrOLED(u16 column,u16 page)
{
    column=column-0x01;
    WriteIIC_Cmd(0xb0+page-1);   /*设置页地址*/
    WriteIIC_Cmd(0x10+(column>>4&0x0f));	/*设置列地址的高4位*/
    WriteIIC_Cmd(column&0x0f);	/*设置列地址的低4位*/	
}


void clear_OLED(void)
{
    u8 m,n;
    for(m=1;m<9;m++)
    {
        WriteIIC_Cmd(0xb0+m);		//page0-page1
        WriteIIC_Cmd(0x00);		//low column start address
        WriteIIC_Cmd(0x10);		//high column start address
        for(n=0;n<128;n++)
        {
                WriteIIC_Dat(0x00);
        }
    }
}

void setCharOLED(char c)
{
  u16 i=0;
  for (i=0;i<5;i++)
  {
    WriteIIC_Dat((u8)ASCII8[c-0x20][i]);
  }
}
void setCharsOLED(u8 *disbuf,u8 x,u8 y)
{
    addrOLED(x+1,y);
    while(*disbuf!='\0')
    {
            setCharOLED(*disbuf);
            *(disbuf++);
    }
}


void Dis_fnum(float num,u8 x,u8 y)
{
    u32 byt;
    u8 temp;
    addrOLED(x+1,y);
    if(num<0)
    {
            num=-num;
            setCharOLED('-');
            x+=8;
    }
    byt=(int)num;
    num*=1000;
    if(byt>10000||byt==10000)
    {	
            setCharOLED(byt/10000+0x30);
            x+=8;
    }
    if(byt>1000||byt==1000)
    {	
            setCharOLED(byt%10000/1000+0x30);
            x+=8;
    }
    if(byt>100||byt==100)
    {	
            setCharOLED(byt%1000/100+0x30);
            x+=8;
    }
    if(byt>10||byt==10)
    {	
            setCharOLED(byt%100/10+0x30);
            x+=8;
    }
    if(byt>0||byt==0)
    {	
            setCharOLED(byt%10+0x30);
            x+=8;
    }
    byt=(u32)num-byt*1000;	
    if(byt)
    {
            setCharOLED('.');
            x+=8;
            do
            {
                    temp=byt/100;
                    byt-=temp*100;
                    byt*=10;
                    setCharOLED(temp+0x30);
                    x+=8;
            }while(byt>10);
    }
}


void drpic(u8 *pic)
{
  u8 x,y;
  u16 i=0;
  for(y=0;y<6;y++)
    {
      WriteIIC_Cmd(0xb0+y);
      WriteIIC_Cmd(0x00);
      WriteIIC_Cmd(0x10);
      for(x=0;x<128;x++)
        {
          WriteIIC_Dat(pic[i++]);
        }
    }
}

