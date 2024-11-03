#include "stm32f10x.h"                  // Device header
#include "function_interrupt.h"
#include "function_user.h"
#include "function_init.h"

static volatile char g_SPI2SendStringData_aa[4] = {0x11, 0x12, 0x13, 0x14};
static volatile char i = 0;

int main()
{
	/* Initial State */
	INIT_Clock();
	INIT_GPIOLed();
	INIT_Timer2();
	INIT_USART1();	//using hercules program to communicate USART
	INIT_SPI1();
	INIT_SPI2();
	
	/* Send Test USART */
	if (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == 1){
			USART_SendData(USART1, 'S');
	}

	
	/*------------------------------ Run System --------------------------------*/
	while(1)
	{
		/* Blink led */
		USER_BlinkLed(500); //flash 500 ms
		
		/* USART */
		/* Send data */
		
		/* Test Receive Data */
		if (g_USART1ReceiveStringData_aa[0] == 'a'){
			USER_USARTSendData(USART1, 'A');	//confirm to receive true data
			
			/* Transmit SPI data */
			for (i=0; i<4; i++){
				while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == 0){}
				USER_SPI1SendData(g_SPI2SendStringData_aa[i]);
			}
//			USER_SPI2ReceiveData();	//not use because using interrupt -> check g_SPI2DataReceive_u8
			g_USART1ReceiveStringData_aa[0] = 'P';	// Reset transmitted condition to only send once time
		}
		else if (g_USART1ReceiveStringData_aa[0] == 'b'){
			USER_USARTSendData(USART1, 'B');	//confirm to receive true data
			
			/* Transmit SPI data */
			USER_SPI1SendData('a');
//			USER_SPI2ReceiveData();	//not use because using interrupt -> check g_SPI2DataReceive_u8
			g_USART1ReceiveStringData_aa[0] = 'P';	// Reset transmitted condition to only send once time
		}
		else{
			USER_USARTSendData(USART1, 'Q');
		}
	}
}
