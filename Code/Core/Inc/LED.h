#ifndef __STM32L476G_DISCOVERY_LED_H
#define __STM32L476G_DISCOVERY_LED_H

#include "stm32l476xx.h"

void LED_Init(void);

void Red_LED_Off(void);
void Red_LED_On(void);
void Red_LED_Toggle(void);

void Green_LED_On(void);
void Green_LED_Off(void);
void Green_LED_Toggle(void);

void LED_Off_State(void);
void LED_Green_State(void);
void LED_Yellow_State(void);
void LED_Red_State(void);

#endif /* __STM32L476G_DISCOVERY_LED_H */
