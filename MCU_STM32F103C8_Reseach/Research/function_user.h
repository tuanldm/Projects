#ifndef FUNCTION_USER
#define FUNCTION_USER

#include "stm32f10x.h"
#include "function_interrupt.h"

void USER_Delay(unsigned int l_Delay_u32);	//miliseconds
void USER_BlinkLed(unsigned int l_Delay_u32);
void USER_USARTSendData(USART_TypeDef* USARTx, char l_Char_u8);	//send data usart
void USER_SPI1SendData(char l_Char_u8);	//send data spi
void USER_SPI2ReceiveData(void);	//receive data spi 2

#endif