#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "RTC.h"
#include "LCD.h"
#include "SysTimer.h"
#include "JoyControl.h"

char strTime[12] = {0};
char strDate[12] = {0};

int main(void){

   System_Clock_Init(); // Switch System Clock = 80 MHz
   LED_Init();
  
   LCD_Initialization();
   
   SysTick_Init();
   
   init_JOY();

   init_Alarm();
   // You can call RTC_Set_Time() and RTC_Read_Time()
   // The values of Hour, Minute, Second are in BCD format

   LCD_DisplayString("00:00:00");

   while(1) {
      
   }
}

