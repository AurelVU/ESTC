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
void SwitchOffAllD(void);
void SwitchOnA(uint16_t Pin);
void SwitchOffA(uint16_t Pin);
void SwitchOffD(uint16_t Pin);
void SwitchOnD(uint16_t Pin);
void TIM2_IRQHandler(void);
void Wait(void);
int IsSetButton(uint16_t Pin);
void InitD(void);
void InitBaseA(void);
void InitE(void);


#endif  /* LEDS_AND_BUTTON_H */
