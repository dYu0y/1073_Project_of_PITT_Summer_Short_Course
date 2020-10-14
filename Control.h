#ifndef __STM32L476G_DISCOVERY_CONTROL_H
#define __STM32L476G_DISCOVERY_CONTROL_H

#include <stdint.h>

extern int32_t hate_clock;

void event_Up(void);
void event_Down(void);
void event_Left(void);
void event_Right(void);
void event_Center(void);

#endif /* __STM32L476G_DISCOVERY_JOYCONTROL_H */
