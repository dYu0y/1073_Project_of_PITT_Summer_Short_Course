#include "Control.h"
#include "RTC.h"
#include "SysTimer.h"

extern int32_t hate_clock = -1;
static int32_t sel = 0;
static uint32_t hour = 0, minute = 0, second = 0;

extern char strTime[12];

// RTC_Read_Time
// RTC_Set_Time

inline static void set_time(uint32_t hour, uint32_t minute, uint32_t second) {
   RTC_Init(((hour / 10) << 4) | (hour % 10), ((minute / 10) << 4) | (minute % 10), ((second / 10) << 4) | (second % 10));
}

void event_Up() {
   switch(sel) {
      case 0:
         if(++hour >= 24)
            hour = 0;
         break;
      case 1:
         if(++minute >= 60)
            minute = 0;
         break;
      case 2:
         if(++second >= 60)
            second = 0;
         break;
   }
   if (hate_clock) {
      sprintf(strTime, "%.2d:%.2d:%.2d", hour, minute, second);
      LCD_DisplayString((uint8_t *)strTime);
   }
}

void event_Down() {
   switch(sel) {
      case 0:
         if(hour-- == 0)
            hour = 23;
         break;
      case 1:
         if(minute-- == 0)
            minute = 59;
         break;
      case 2:
         if(second-- == 0)
            second = 59;
         break;
   }
   if(hate_clock) {
      sprintf(strTime, "%.2d:%.2d:%.2d", hour, minute, second);
      LCD_DisplayString((uint8_t *)strTime);
   }
}

void event_Left() {
   if(--sel < 0)
      sel = 2;
}

void event_Right() {
   if(++sel > 2)
      sel = 0;
}

void event_Center() {
   if(hate_clock == -1) {
      set_time(hour, minute, second);
      SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
      hate_clock = 0;
   }
   else if(hate_clock == 0) {
      SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
      hour = minute = second = 0;
      sprintf(strTime, "%.2d:%.2d:%.2d", hour, minute, second);
      LCD_DisplayString((uint8_t *)strTime);
      sel = 2;
      hate_clock = 1;
   }
   else {
      uint32_t h, m, s;
      RTC_Read_Time(&h, &m, &s);
      second += s;
      if(second > 59) {
         second -= 60;
         ++minute;
      }
      minute += m;
      if(minute > 59) {
         minute -= 60;
         ++hour;
      }
      hour += h;
      if(hour > 23)
         hour -= 24;
      set_alarm(hour, minute, second);
      SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; 
      hate_clock = 0;
   }
}
