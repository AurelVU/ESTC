#include "main.h"

#define SWITCH_DELAY 500000
#define PERIOD 8400
#define PRESCALER 10000
#define STEP 1000

static int pulseR;
static int pulseG;
static int pulseB;

void SwitchOffAllA() 
{
  GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
}

void SwitchOnA(uint16_t Pin) 
{
  GPIO_ResetBits(GPIOA, Pin);
}

void SwitchOffA(uint16_t Pin) 
{
  GPIO_SetBits(GPIOA, Pin);
}

void UpYarR() 
{
  if (pulseR + STEP <= 20000)
  {
    pulseR += STEP;
    TIM_SetCompare1(TIM1, pulseR);
  }
}
void UpYarG() 
{
  if (pulseG + STEP <= 20000)
  {
    pulseG += STEP;
    TIM_SetCompare2(TIM1, pulseG);
  }
}
void UpYarB() 
{
  if (pulseB + STEP <= 20000)
  {
    pulseB += STEP;
    TIM_SetCompare3(TIM1, pulseB);
  }
}
void DownYarR() 
{
  if (pulseR - STEP >= 0)
  {
    pulseR -= STEP;
    TIM_SetCompare1(TIM1, pulseR);
  }
}
void DownYarG() 
{
  if (pulseG  - STEP >= 0)
  {
    pulseG -= STEP;
    TIM_SetCompare2(TIM1, pulseG);
  }
}
void DownYarB() 
{
  if (pulseB - STEP >= 0)
  {
    pulseB -= STEP;
    TIM_SetCompare3(TIM1, pulseB);
  }
}

void EXTI0_IRQHandler (void) 
{
    

  if (EXTI_GetITStatus(EXTI_Line0)!= RESET)
  {
    DownYarR();
    DownYarG();
    DownYarB();
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

void EXTI1_IRQHandler (void) 
{
  if (EXTI_GetITStatus(EXTI_Line1)!= RESET)
  {
    UpYarR();
    UpYarG();
    UpYarB();
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

int IsSetButton(uint16_t Pin) 
{
  return !GPIO_ReadInputDataBit(GPIOE, Pin); 
}


void InitTim1() 
{
  TIM_TimeBaseInitTypeDef tim_struct2;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  tim_struct2.TIM_Period = 20000 - 1; //12000 - 1;
  tim_struct2.TIM_Prescaler = 168 - 1; //2 - 1;
  tim_struct2.TIM_ClockDivision = 0;

  tim_struct2.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &tim_struct2);
}

void InitA() 
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);


  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;


  //RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
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

void InitPrButt0() 
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

void InitPrButt1() 
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource1);

  EXTI_InitTypeDef EXTI_InitStruct;
  EXTI_InitStruct.EXTI_Line = EXTI_Line1;
  EXTI_InitStruct.EXTI_LineCmd = ENABLE;
  EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_Init(&EXTI_InitStruct);
}

void ConfPr0() 
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  //TIM_OCStructInit(&NVIC_InitStruct);
  
}
void ConfPr1() 
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
}

void InitCompForTim1() 
{
  TIM_OCInitTypeDef timer1 = {0};
  timer1.TIM_OCMode = TIM_OCMode_PWM2;
  timer1.TIM_OutputState = TIM_OutputState_Enable;
  pulseR = 0;
  pulseG = 0;
  pulseB = 0;
  timer1.TIM_Pulse = pulseR;
  TIM_OC1Init(TIM1, &timer1);
  timer1.TIM_Pulse = pulseG;
  TIM_OC2Init(TIM1, &timer1);
  timer1.TIM_Pulse = pulseB;
  TIM_OC3Init(TIM1, &timer1);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
}

int main(void)
{
  InitE();
  InitA();
  InitTim1();
  InitCompForTim1();
  InitPrButt0();
  InitPrButt1();
  ConfPr0();
  ConfPr1();

  TIM_Cmd(TIM1, ENABLE);
  TIM_CtrlPWMOutputs(TIM1, ENABLE);


  

  while(1) 
  {

  }
}
