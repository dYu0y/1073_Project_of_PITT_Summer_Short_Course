#ifndef __STM32L476G_DISCOVERY_JOYCONTROL_H
#define __STM32L476G_DISCOVERY_JOYCONTROL_H

#include "stm32l476xx.h"

void init_JOY(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI9_5_IRQHandler(void);

#endif /* __STM32L476G_DISCOVERY_JOYCONTROL_H */
