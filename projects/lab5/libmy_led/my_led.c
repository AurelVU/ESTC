#include "my_led.h"


static int swich = 0;
static int pulseR;
static int pulseG;
static int pulseB;

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

void setColorRGB(uint8_t R, uint8_t G, uint8_t B) 
{
    TIM_SetCompare1(TIM1, (R / 256.0) * 20000);
    TIM_SetCompare2(TIM1, (G / 256.0) * 20000);
    TIM_SetCompare3(TIM1, (B / 256.0) * 20000);
}

void setColorHEX(uint32_t color) 
{
    uint8_t R = (uint8_t)(color >> 16);
    uint8_t G = (uint8_t)(color >> 8);
    uint8_t B = (uint8_t)color;
    TIM_SetCompare1(TIM1, (R / 256.0) * 20000);
    TIM_SetCompare2(TIM1, (G / 256.0) * 20000);
    TIM_SetCompare3(TIM1, (B / 256.0) * 20000);
}

void InitAll(void)
{
    InitD();  
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
}