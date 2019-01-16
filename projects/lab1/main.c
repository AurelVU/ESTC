#include "main.h"

#define SWITCH_DELAY 5000000
#define PERIOD 8400
#define PRESCALER 10000
#define STEP 100



void SwitchOffAllA() 
{
  GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
}

void SwitchOffAllD() 
{
  GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void SwitchOnA(uint16_t Pin) 
{
  GPIO_ResetBits(GPIOA, Pin);
}

void SwitchOffA(uint16_t Pin) 
{
  GPIO_SetBits(GPIOA, Pin);
}


void SwitchOffD(uint16_t Pin) 
{
  GPIO_ResetBits(GPIOD, Pin);
}

void SwitchOnD(uint16_t Pin) 
{
  GPIO_SetBits(GPIOD, Pin);
}

void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    static int flag = 1;

    if (flag)
      SwitchOnD(GPIO_Pin_12); 
    else
      SwitchOffD(GPIO_Pin_12);    
    flag = !flag;
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  } 
}


void Wait() 
{
  int i;
  for (i = 0; i < SWITCH_DELAY; i++);
}
int IsSetButton(uint16_t Pin) 
{
  return !GPIO_ReadInputDataBit(GPIOE, Pin); 
}

void InitD() 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void InitBaseA() 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void InitE() 
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
}


int main(void)
{
  InitD();  
  InitE();
  InitBaseA();
  
  SwitchOffAllA();
  SwitchOffAllD();
  int step = 0;

  int k = 1;
  int swich1 = 1;
  
  while(1) 
  {
    if (IsSetButton(GPIO_Pin_0)) 
    {
      swich1 =  1 - swich1;     
    }
    if (IsSetButton(GPIO_Pin_1)) 
    {
      if (k == 1)
        k = -1;
      else 
        k = 1;
    } 
     
      if (step % 3 == 0) 
      {
        SwitchOnA(GPIO_Pin_8);
        SwitchOnD(GPIO_Pin_15);
      } else if (step % 3 == 1) 
      {
        SwitchOnA(GPIO_Pin_9);
        SwitchOnD(GPIO_Pin_14);
      } else if (step % 3 == 2)
      {
        SwitchOnA(GPIO_Pin_10);
        SwitchOnD(GPIO_Pin_13);
      }
    
      step += k;
      if (step == 0 && k < 0)
        step = 1000;
      else if (step == 999 && k > 0)
        step = 3;
    
      Wait();
      
    
    SwitchOffAllA();
    SwitchOffAllD();
  }
}
