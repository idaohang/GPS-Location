#include "key.h"



u8 status = 1;

void keyinit(void)
{
  GPIOB->DDR &=~(1<<3);
  GPIOB->CR1 |= 1<<3;
  GPIOB->CR2 &=~(1<<3);
  GPIOB->DDR &=~(1<<5);
  GPIOB->CR1 |= 1<<5;
  GPIOB->CR2 &=~(1<<5);
  GPIOB->DDR &=~(1<<7);
  GPIOB->CR1 |= 1<<7;
  GPIOB->CR2 &=~(1<<7);

}


static void Timeadd(time *temp)
{
  if(status == 1)
  {
    if(++temp->min>=60)
    {
      temp->min = 0;
    }
  }
  else if(status == 2)
  {
    if(++temp->hour>=24)
    {
      temp->hour = 0;
    }
  }
  else if(status == 3)
  {
    if(++temp->day>=32)
    {
      temp->day = 1;
    }
  }
  else if(status == 4 )
  {
    if(++temp->mouth>=13)
    {
      temp->mouth = 1;
    }
  }
  else if(status >= 5)
  {
    temp->year++;
  }
}
static void Statusdisplay(void)
{
  if(status == 1)
  {
    setCharsOLED("min  ",60,2);
  }
  else if(status ==2)
  {
    setCharsOLED("hour ",60,2);
  }
  else if(status == 3)
  {
    setCharsOLED("day  ",60,2);
  }
  else if(status == 4)
  {
    setCharsOLED("mouth",60,2);
  }
  else if(status == 5)
  {
    setCharsOLED("year ",60,2);
  }
}
void show(time* temp)
{
  Dis_fnum(temp->year,11,1);
  setCharsOLED("-",22,1);
  Dis_fnum(temp->mouth,28,1);
  if(temp->mouth>9)
  {
    setCharsOLED("-",40,1);
    Dis_fnum(temp->day,46,1);
  }
  else 
  {
    setCharsOLED("-",35,1);
    Dis_fnum(temp->day,41,1);
  }
  
  Dis_fnum(temp->hour,11,2);
  if(temp->hour>9)
  {
     setCharsOLED("-",22,2);
     Dis_fnum(temp->min,28,2);
  }
  else
  {
     setCharsOLED("-",18,2);
    Dis_fnum(temp->min,24,2);
  }
}
static int truetime(time* temp)
{
  if(temp->mouth == 2)
  {
    if(temp->year % 4 == 0 && ( temp->year % 100 != 0 || temp->year % 400 == 0))
    {
      if(temp->day>29)
      {
	return 0;
      }
    }
    else 
    {
      if(temp->day>28)
      {
	return 0;
      }
      
    }
  }
  else if (temp->mouth==1 || temp->mouth==3 || temp->mouth==5 || temp->mouth==7 || temp->mouth==8 || temp->mouth==10 || temp->mouth==12)
  {
    if(temp->day>31)
    {
      return 0;
    }
  }
  else 
  {
    if(temp->day>30)
    {
      return 0;
    }
  }
  return 1;
}
time Menu()
{
  time Time;
  Time.year=14;
  Time.mouth=9;
  Time.day=8;
  Time.hour=1;
  Time.min=10;
  Time.sec=50;
  Statusdisplay();
  show(&Time);
  while(1)
  {
    if(addkey==0)
    {
      delay_ms(100);
      if(addkey==0)
      {
	Timeadd(&Time);
	clear_OLED();
	Statusdisplay();
	show(&Time);
      }
    }
    else if(changekey==0)
    {
      delay_ms(100);
      if(changekey==0)
      {
	if(++status>=6)
	{
	  status = 1; 
	}
	Statusdisplay();
      }
    }
    else if(surekey==0)
    {
      delay_ms(100);
      if(surekey==0)
      {
	if(truetime(&Time))
	{
	   DSWrite(&Time);
	   return Time;  
	}
      }
    }
  }
}


u8 readkey()
{
  if(surekey==0)
  {
    delay_ms(100);
    if(surekey==0)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
}