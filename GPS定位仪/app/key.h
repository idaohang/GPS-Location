#ifndef __KEY_H
#define __KEY_H

#include "Sys.h"
#include <stdio.h>
#include <string.h>
#include "DS1302.h"
#include "OLED.h"

#define addkey PB(3)
#define changekey PB(5)
#define surekey PB(7)

void keyinit(void);
time Menu(void);
u8 readkey();


#endif// __KEY_H
