#include "Alarm.h"
#include "LED.h"
#include "RTC.h"

void delay_s(unsigned int t);

void init_Alarm(void) {
   NVIC_EnableIRQ(RTC_Alarm_IRQn);
   EXTI->RTSR1 |= EXTI_RTSR1_RT18;
   EXTI->IMR1  |= EXTI_IMR1_IM18;
}

void set_alarm(uint32_t h, uint32_t m, uint32_t s) {
   uint32_t hour, minute, second;
   hour = ((h / 10) << 4) | (h % 10);
   minute = ((m / 10) << 4) | (m % 10);
   second = ((s / 10) << 4) | (s % 10);

   // Step 1: Disable the RTC reg write protection
   RTC->WPR = 0xCA;
   RTC->WPR = 0x53;
   
   // Step 2: Disable alarm A
   RTC->CR &= ~(0x33 << 7);
   
   while((RTC->ISR & 1) == 0) { ; }
   
   RTC->ALRMAR = 0x80000000 | (hour << 16) | (minute << 8) | second;

   RTC->CR |= 0x33 << 7;

   RTC->WPR = 0xFF;
}


static int digit = 0; 
int delay[] = {
   1, 1, 1, 1, 1, 1, 1, 3, 3, 1,
   3, 1, 3, 3, 3, 1, 1, 1, 1, 3,
   3, 1, 1, 1, 1, 3, 1, 1, 1, 3,
   3
};
void display_Hobbit(void) {
   if(!digit)
      Red_LED_Toggle();

   Green_LED_Toggle();
   if(digit < (sizeof(delay) / sizeof(delay[0])))
      delay_s(delay[digit++]);
   else {
      digit = 0;
      Red_LED_Toggle();
   }
   /*uint32_t i;
   // H
   for(i = 0; i < 4; ++i) {
      Green_LED_On();
      delay_ms(1000);
      Green_LED_Off();
      delay_ms(1000);
   }
   delay_ms(2000);
   
   // O
   for(i = 0; i < 3; ++i) {
      Green_LED_On();
      delay_ms(3000);
      Green_LED_Off();
      delay_ms(1000);
   }
   delay_ms(2000);

   // B
   Green_LED_On();
   delay_ms(3000);
   for(i = 0; i < 3; ++i) {
      Green_LED_Off();
      delay_ms(1000);
      Green_LED_On();
      delay_ms(1000);
   }
   Green_LED_Off();
   delay_ms(3000);

   // B
   Green_LED_On();
   delay_ms(3000);
   for(i = 0; i < 3; ++i) {
      Green_LED_Off();
      delay_ms(1000);
      Green_LED_On();
      delay_ms(1000);
   }
   Green_LED_Off();
   delay_ms(3000);

   // I
   for(i = 0; i < 2; ++i) {
      Green_LED_On();
      delay_ms(1000);
      Green_LED_Off();
      delay_ms(1000);
   }
   delay_ms(2000);

   // T
   Green_LED_On();
   delay_ms(3000);
   */
}

void RTC_Alarm_IRQHandler(void) {
   if (RTC->ISR & RTC_ISR_ALRAF) {
      RTC->ISR &= ~RTC_ISR_ALRAF;
      EXTI->PR1 |= EXTI_PR1_PIF18;
      
      display_Hobbit();
   }
   else if (RTC->ISR & RTC_ISR_ALRBF) {
      RTC->ISR &= ~RTC_ISR_ALRBF;
      EXTI->PR1 |= EXTI_PR1_PIF18;
   }
}

// rudimentary delay millisecond function 
void delay_s(unsigned int t) {
   uint32_t hour, minute, second;
      RTC_Read_Time(&hour, &minute, &second);
      second += t;
      if(second > 59) {
         second -= 60;
         ++minute;
      }
      if(minute > 59) {
         minute -= 60;
         ++hour;
      }
      if(hour > 23)
         hour -= 23;
      set_alarm(hour, minute, second);
}
