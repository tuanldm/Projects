#ifndef FUNCTION_INTERRUPT
#define FUNCTION_INTERRUPT

#include "stm32f10x.h"

extern volatile uint32_t g_Timer2_u32;
extern volatile uint8_t g_USART1ReceiveStringData_aa[30];
extern volatile uint8_t g_SPI2DataReceive_u8;
extern volatile uint8_t g_SPI2ReceiveStringData_aa[30];

void TIM2_IRQHandler(void);
void USART1_IRQHandler(void);
void SPI2_IRQHandler(void);

#endif