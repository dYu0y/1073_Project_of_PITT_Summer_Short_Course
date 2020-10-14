#ifndef __STM32L476G_DISCOVERY_ALARM_H
#define __STM32L476G_DISCOVERY_ALARM_H

#include <stdint.h>
#include "stm32l476xx.h"

void init_Alarm(void);
void set_alarm(uint32_t h, uint32_t m, uint32_t s);

#endif /* __STM32L476G_DISCOVERY_ALARM_H */
