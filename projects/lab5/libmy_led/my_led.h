#ifndef MY_LED_H
#define MY_LED_H

#include <stm32f4xx.h>
#include <math.h>

#define SWITCH_DELAY 500000
#define PERIOD 8400
#define PRESCALER 10000
#define STEP 1000


void SwitchOffAllA(void);//!<Выключить все лампочки на линии A
void SwitchOffAllD(void);//!<Выключить все лампочки на линии D
void SwitchOnA(uint16_t Pin);//!<Включить лампочку на линии A
void SwitchOffA(uint16_t Pin);//!<Выключить лампочку на линии A
void SwitchOffD(uint16_t Pin);//!<Выключить лампочку на линии D
void SwitchOnD(uint16_t Pin);//!<Включить лампочку на линии D
void TIM2_IRQHandler(void);//!<Прерывание таймера Tim2
void Wait(void);//!<Ожидание
void UpYarR(void);//!<Поднять яркость красного светодиода
void UpYarG(void);//!<Поднять яркость зеленого светодиода
void UpYarB(void);//!<Поднять яркость синего светодиода
void DownYarR(void);//!<Убавить яркость красного светодиода
void DownYarG(void);//!<Убавить яркость зеленого светодиода
void DownYarB(void);//!<Убавить яркость синего светодиода
void EXTI0_IRQHandler (void);//!< Прерывание для первой кнопки
void EXTI1_IRQHandler (void);//!< Прерывание для второй кнопки
int IsSetButton(uint16_t Pin);//!< Проверка, нажата ли кнопка
void InitTim2(void);//!< Инициализация таймера Tim2 
void InitTim1(void);//!< Инициализация таймера Tim1
void InitD(void);//!< Инициализация линии D
void InitBaseA(void);//!< Базовая инициализация линии A
void InitA(void);//!< Инициализация линии A
void InitE(void);//!< Инициализация линии E
void InitPrTim2(void);//!< Инициализация прерываний по таймеру Tim2
void InitPrButt0(void);//!< Инициализация прерываний для первой кнопки
void InitPrButt1(void);//!< Инициализация прерываний для второй кнопки
void ConfPr0(void);//!< Прерывания для первой кнопки
void ConfPr1(void);//!< Прерывания для второй кнопки
void InitCompForTim1(void);//!< Инициализация компеира для таймера Tim1
void setColorRGB(uint8_t R, uint8_t G, uint8_t B);//!< Установка цвета в формате RGB
void setColorHEX(uint32_t color);//!< Установка цвета в формате HEX
void InitAll(void);//!< Инициализация всего

#endif