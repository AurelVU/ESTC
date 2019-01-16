#ifndef MY_LED_H
#define MY_LED_H
/// \file my_led.h 
/// Библиотека для работа с цветом светодиода.

#include <stm32f4xx.h>
#include <math.h>

#define SWITCH_DELAY 500000
#define PERIOD 8400
#define PRESCALER 10000
#define STEP 1000

/// \brief Выключить все лампочки на линии A.
void SwitchOffAllA(void);
/// \brief Выключить все лампочки на линии D.
void SwitchOffAllD(void);
/// \brief Включить лампочку на линии A.
void SwitchOnA(uint16_t Pin);
/// \brief Выключить лампочку на линии A.
void SwitchOffA(uint16_t Pin);
/// \brief Выключить лампочку на линии D.
void SwitchOffD(uint16_t Pin);
/// \brief Включить лампочку на линии D.
void SwitchOnD(uint16_t Pin);
/// \brief Прерывание таймера Tim2.
void TIM2_IRQHandler(void);
/// \brief Ожидание.
void Wait(void);
/// \brief Поднять яркость красного светодиода.
void UpYarR(void);
/// \brief Поднять яркость зеленого светодиода.
void UpYarG(void);
/// \brief Поднять яркость синего светодиода.
void UpYarB(void);
/// \brief Убавить яркость красного светодиода.
void DownYarR(void);
/// \brief Убавить яркость зеленого светодиода.
void DownYarG(void);
/// \brief Убавить яркость синего светодиода.
void DownYarB(void);
/// \brief Прерывание для первой кнопки.
void EXTI0_IRQHandler (void);
/// \brief Прерывание для второй кнопки.
void EXTI1_IRQHandler (void);
/// \brief Проверка, нажата ли кнопка.
int IsSetButton(uint16_t Pin);
/// \brief Инициализация таймера Tim2.
void InitTim2(void);
/// \brief Инициализация таймера Tim1.
void InitTim1(void);
/// \brief Инициализация линии D.
void InitD(void);
/// \brief Базовая инициализация линии A.
void InitBaseA(void);
/// \brief Инициализация линии A.
void InitA(void);
/// \brief Инициализация линии E.
void InitE(void);
/// \brief Инициализация прерываний по таймеру Tim2.
void InitPrTim2(void);
/// \brief Инициализация прерываний для первой кнопки.
void InitPrButt0(void);
/// \brief Инициализация прерываний для второй кнопки.
void InitPrButt1(void);
/// \brief Прерывания для первой кнопки.
void ConfPr0(void);
/// \brief Прерывания для второй кнопки.
void ConfPr1(void);
/// \brief Инициализация компеира для таймера Tim1.
void InitCompForTim1(void);
/// \brief Установка цвета в формате RGB.
void setColorRGB(uint8_t R, uint8_t G, uint8_t B);
/// \brief Установка цвета в формате HEX.
void setColorHEX(uint32_t color);
/// \brief Инициализация всего.
void InitAll(void);

#endif 