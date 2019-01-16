#include "main.h"

#define SWITCH_DELAY 500000
#define PERIOD 8400
#define PRESCALER 10000
#define STEP 100

static int step = 0;
static int k = 1;

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
    static int flag = 0;

    if (flag)
    {
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
      flag = !flag;
    }
    else
    {
      if (step % 3 == 0) 
      {
        SwitchOffA(GPIO_Pin_8);
        SwitchOffD(GPIO_Pin_15);
      } else if (step % 3 == 1) 
      {
        SwitchOffA(GPIO_Pin_9);
        SwitchOffD(GPIO_Pin_14);
      } else if (step % 3 == 2)
      {
        SwitchOffA(GPIO_Pin_10);
        SwitchOffD(GPIO_Pin_13);
      }
      step += k;  
      flag = !flag;
    }  
    
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
  } 
}




void EXTI0_IRQHandler (void) 
{
  if (EXTI_GetITStatus(EXTI_Line0)!= RESET)
  {
    if (k == 1)
      k = -1;
    else 
      k = 1;
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}




void InitTim2() 
{
  TIM_TimeBaseInitTypeDef tim_struct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  tim_struct.TIM_Period = PERIOD - 1;
  tim_struct.TIM_Prescaler = PRESCALER - 1;
  tim_struct.TIM_ClockDivision = 0;

  tim_struct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &tim_struct);
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

void InitPrTim2()
{
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  NVIC_InitTypeDef nvic_struct;
  nvic_struct.NVIC_IRQChannel = TIM2_IRQn;
  nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;
  nvic_struct.NVIC_IRQChannelSubPriority = 1;
  nvic_struct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic_struct);
}

void InitPrButt() 
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource0);

  EXTI_InitTypeDef EXTI_InitStruct;
  EXTI_InitStruct.EXTI_Line = EXTI_Line0;
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;
  EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStruct);
}

void ConfPr() 
{
  NVIC_InitTypeDef NVIC_InitStruct = {0};
  //TIM_OCStructInit(&NVIC_InitStruct);
  NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStruct);
}


int main(void)
{
  InitD();
  InitBaseA();
  InitE();  
  InitTim2();
  InitPrTim2();
  InitPrButt();
  ConfPr();
  
  SwitchOffAllA();
  SwitchOffAllD();
  
  
  TIM_Cmd(TIM2, ENABLE);
  while(1) 
  {

  }
}
