#include "function_interrupt.h"

volatile uint32_t g_Timer2_u32 = 0;
volatile uint8_t g_USART1ReceiveStringData_aa[30];
volatile uint8_t g_SPI2DataReceive_u8 = 0;
volatile uint8_t g_SPI2ReceiveStringData_aa[30];

static volatile uint8_t g_USART1Stt_u8 = 0;
static volatile uint16_t g_USART1StatusTime_u16 = 500;
static volatile uint8_t g_SPI2Stt_u8 = 0;
static volatile uint16_t g_SPI2StatusTime_u16 = 500;



void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == 1){
		/* Clear Interrupt flag */
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		
		
		/* Active */
		/* Timer */
		g_Timer2_u32++;
		
		/* Process receive string data from USART1 */
		if (g_USART1StatusTime_u16 > 100){
			g_USART1StatusTime_u16--;
		}
		else if ((g_USART1StatusTime_u16 <= 100) && (g_USART1StatusTime_u16 > 10)){	
			while (g_USART1Stt_u8 < 30){	//Reset Abundant Data
				g_USART1ReceiveStringData_aa[g_USART1Stt_u8] = '\0';
				g_USART1Stt_u8++;
			}
			g_USART1Stt_u8 = 0;
			g_USART1StatusTime_u16 = 0;
		}
		
		/* Process receive string data from SPI2 */
		if (g_SPI2StatusTime_u16 > 100){
			g_SPI2StatusTime_u16--;
		}
		else if ((g_SPI2StatusTime_u16 <= 100) && (g_SPI2StatusTime_u16 > 10)){	
			while (g_SPI2Stt_u8 < 30){	//Reset Abundant Data
				g_SPI2ReceiveStringData_aa[g_SPI2Stt_u8] = '\0';
				g_SPI2Stt_u8++;
			}
			g_SPI2Stt_u8 = 0;
			g_SPI2StatusTime_u16 = 0;
		}
	}
}

void USART1_IRQHandler(void){
	if (USART_GetITStatus(USART1,	USART_IT_RXNE) == 1){
		/* Clear Interrupt flag */
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		
		/* Active */
		g_USART1StatusTime_u16 = 500;	//Time CountDown to determine string chars
		if (g_USART1Stt_u8 < 30){	//only receive 30 chars
			g_USART1ReceiveStringData_aa[g_USART1Stt_u8] = USART_ReceiveData(USART1);
			g_USART1Stt_u8++;
		}
	}
}

void SPI2_IRQHandler(void){
	if (SPI_I2S_GetITStatus(SPI2, SPI_I2S_IT_RXNE) == 1){
		/* Clear Interrupt flag */
		SPI_I2S_ClearITPendingBit(SPI2, SPI_I2S_IT_RXNE);
		
		/* Active */
		g_SPI2StatusTime_u16 = 500;	//Time CountDown to determine string chars
		if (g_SPI2Stt_u8 < 30){	//only receive 30 chars
			g_SPI2DataReceive_u8 = SPI_I2S_ReceiveData(SPI2);		
			g_SPI2ReceiveStringData_aa[g_SPI2Stt_u8] = g_SPI2DataReceive_u8;
			g_SPI2Stt_u8++;
		}
	}
}
