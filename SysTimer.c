#include "SysTimer.h"
#include "LCD.h"
#include "RTC.h"
#include "LED.h"

extern char strTime[12];
extern char strDate[12];
uint32_t msTicks;


//******************************************************************************************
// SysTick Interrupt Handler
//******************************************************************************************
void SysTick_Handler(void){
	uint32_t hour = 0, min = 0, sec = 0;
	msTicks++;
	
	//Assignment4:
	if(msTicks >= 250)
	{
		msTicks = 0;
		//call RTC
		RTC_Read_Time(&hour, &min, &sec);
		sprintf(strTime, "%.2d:%.2d:%.2d", hour, min, sec);
		LCD_DisplayString((uint8_t *)strTime);
	}
}

//******************************************************************************************
// Initialize SysTick	
//******************************************************************************************	
void SysTick_Init(void){
	// The RCC feeds the Cortex System Timer (SysTick) external clock with the AHB clock
	// (HCLK) divided by 8. The SysTick can work either with this clock or with the Cortex clock
	// (HCLK), configurable in the SysTick Control and Status Register.
	
	//  SysTick Control and Status Register
	SysTick->CTRL = 0;										// Disable SysTick IRQ and SysTick Counter
	
	//Assignment3:
	SysTick->LOAD = 80000000/1000 - 1;    // 1ms, Default clock
	
	// SysTick Current Value Register
	SysTick->VAL = 0;

	NVIC_SetPriority(SysTick_IRQn, 1);		// Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);					// Enable EXTI0_1 interrupt in NVIC

	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does not assert the SysTick exception request
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
	
	// Select processor clock
	// 1 = processor clock;  0 = external clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;		
	
	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  
}
