#include "JoyControl.h"
#include "LED.h"
#include "Control.h"

void init_JOY() {
   RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;  // Enable clock of Port A

   GPIOA->MODER &= ~3UL; // Set PA.0 as digital input
   GPIOA->MODER &= ~(3UL << 2); // Set PA.1 as digital input
   GPIOA->MODER &= ~(3UL << 4); // Set PA.2 as digital input
   GPIOA->MODER &= ~(3UL << 6); // Set PA.3 as digital input
   GPIOA->MODER &= ~(3UL << 10); // Set PA.5 as digital input

   //GPIOA->MODER &= 0xFFFFF3

   GPIOA->PUPDR &= ~3UL; // No pull-up, no pull-down
   GPIOA->PUPDR &= ~(3UL << 2); // No pull-up, no pull-down
   GPIOA->PUPDR |= 2UL << 2; // No pull-up, no pull-down
   GPIOA->PUPDR &= ~(3UL << 4); // No pull-up, no pull-down
   GPIOA->PUPDR |= 2UL << 4; // No pull-up, no pull-down
   GPIOA->PUPDR &= ~(3UL << 6); // No pull-up, no pull-down
   GPIOA->PUPDR |= 2UL << 6; // No pull-up, no pull-down
   GPIOA->PUPDR &= ~(3UL << 10); // No pull-up, no pull-down
   GPIOA->PUPDR |= 2UL << 10; // No pull-up, no pull-down





   NVIC_EnableIRQ(EXTI0_IRQn); // Enable Interrupt
   NVIC_EnableIRQ(EXTI1_IRQn); // Enable Interrupt
   NVIC_EnableIRQ(EXTI2_IRQn); // Enable Interrupt
   NVIC_EnableIRQ(EXTI3_IRQn); // Enable Interrupt
   NVIC_EnableIRQ(EXTI9_5_IRQn); // Enable Interrupt

   // Connect External Line to the GPI
   RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
   SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0; 
   SYSCFG->EXTICR[0] |=  SYSCFG_EXTICR1_EXTI0_PA; 

   SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1; 
   SYSCFG->EXTICR[0] |=  SYSCFG_EXTICR1_EXTI1_PA;

   SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2; 
   SYSCFG->EXTICR[0] |=  SYSCFG_EXTICR1_EXTI2_PA; 

   SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI3; 
   SYSCFG->EXTICR[0] |=  SYSCFG_EXTICR1_EXTI3_PA;

   SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI5; 
   SYSCFG->EXTICR[1] |=  SYSCFG_EXTICR2_EXTI5_PA;



   // Rising trigger selection
   // 0 = trigger disabled, 1 = trigger enabled
   EXTI->RTSR1 |= EXTI_RTSR1_RT0;
   EXTI->RTSR1 |= EXTI_RTSR1_RT1;
   EXTI->RTSR1 |= EXTI_RTSR1_RT2;
   EXTI->RTSR1 |= EXTI_RTSR1_RT3;
   EXTI->RTSR1 |= EXTI_RTSR1_RT5;

   // Interrupt Mask Register
   // 0 = marked, 1 = not masked (enabled)
   EXTI->IMR1  |= EXTI_IMR1_IM0;     
   EXTI->IMR1  |= EXTI_IMR1_IM1;
   EXTI->IMR1  |= EXTI_IMR1_IM2;
   EXTI->IMR1  |= EXTI_IMR1_IM3;
   EXTI->IMR1  |= EXTI_IMR1_IM5;
}

void EXTI0_IRQHandler(void) {  
   if ((EXTI->PR1 & EXTI_PR1_PIF0) != 0) {
      event_Center();
      EXTI->PR1 |= EXTI_PR1_PIF0;
   }
}

void EXTI1_IRQHandler(void) {  
   if ((EXTI->PR1 & EXTI_PR1_PIF1) != 0) {
      event_Left();
      EXTI->PR1 |= EXTI_PR1_PIF1;
   }
}

void EXTI2_IRQHandler(void) {  
   if ((EXTI->PR1 & EXTI_PR1_PIF2) != 0) {
      event_Right();
      EXTI->PR1 |= EXTI_PR1_PIF2;
   }
}

void EXTI3_IRQHandler(void) {  
   if ((EXTI->PR1 & EXTI_PR1_PIF3) != 0) {
      event_Up();
      EXTI->PR1 |= EXTI_PR1_PIF3;
   }
}

void EXTI9_5_IRQHandler(void) {  
   if ((EXTI->PR1 & EXTI_PR1_PIF5) != 0) {
      event_Down();
      EXTI->PR1 |= EXTI_PR1_PIF5;
   }
}
