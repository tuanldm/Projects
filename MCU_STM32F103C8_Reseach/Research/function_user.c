#include "function_user.h"


void USER_Delay(unsigned int l_Delay_u32){	//miliseconds
	g_Timer2_u32 = 0;
	while (g_Timer2_u32 < l_Delay_u32){}
}

void USER_BlinkLed(unsigned int l_Delay_u32){
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	USER_Delay(l_Delay_u32);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	USER_Delay(l_Delay_u32);
}

void USER_USARTSendData(USART_TypeDef* USARTx, char l_Char_u8){
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == 0){}
	USART_SendData(USARTx, l_Char_u8);
}

void USER_SPI1SendData(char l_Char_u8){
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0){}
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);	//NSS low to choose Slave No.
	USER_Delay(100);
	SPI_I2S_SendData(SPI1, l_Char_u8);
	USER_Delay(100);
	GPIO_SetBits(GPIOA, GPIO_Pin_4);	//NSS high to disable Slave No.
}

//void USER_SPI2ReceiveData(void){
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == 0){}
//	g_SPI2DataReceive_u8 = SPI_I2S_ReceiveData(SPI2);
//}
