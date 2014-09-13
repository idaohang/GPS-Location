#ifndef __GSM_H
#define __GSM_H

#include "stm32f10x.h"
#include "abba_USART.h"
#include "GPS.h"
#include <stdio.h>
#include <string.h>

void Send_PostMessage(Datapack* pack);
void httpInit(void);
#endif //__GSM_H

