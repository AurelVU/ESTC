#ifndef LEDS_AND_BUTTON_H
#define LEDS_AND_BUTTON_H

#include <stm32f4xx.h>

/* #if defined (USE_STM324xG_EVAL) */
/*   #include "stm324xg_eval.h" */

/* #elif defined (USE_STM32F4DISC_EVAL) */
/*   #include "stm32f4disc_eval.h" */

/* #else */
/*  #error "Please select first the Evaluation board used in your application (in Project Options)" */
/* #endif */

#include <math.h>

 void SwitchOffAllA(void);
 void SwitchOnA(uint16_t Pin);
 void SwitchOffA(uint16_t Pin);
 void UpYarR(void);
 void UpYarG(void);
 void UpYarB(void);
 void DownYarR(void);
 void DownYarG(void);
 void DownYarB(void);
 void EXTI0_IRQHandler (void);
 void EXTI1_IRQHandler (void);
 int IsSetButton(uint16_t Pin);
 void InitTim1(void);
 void InitA(void);
 void InitE(void);
 void InitPrButt0(void);
 void InitPrButt1(void);
 void ConfPr0(void);
 void ConfPr1(void);
 void InitCompForTim1(void);

#endif  /* LEDS_AND_BUTTON_H */
