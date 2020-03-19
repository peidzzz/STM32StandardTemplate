#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED0 PAout(8)   	//LED0
#define LED1 PDout(2)   	//LED1

void LED_Init(void); //初始化

#endif /* __LED_H */
