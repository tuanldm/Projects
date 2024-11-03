#include "BT01_BitMask.h"
#include "BT02_GPIOPolling.h"
#include "BT03_GPIOInterrupt.h"
#include "BT04_SysTickTimer.h"
#include "BT05_Clock.h"
#include "BT06_Timer.h"
#include "Setup_Port_S32K144.h"

#define	BT01_3 0
#define	BT02_1 1
#define	BT02_2 2
#define	BT02_3 3
#define	BT02_4 4
#define	BT02_5 5
#define	BT03_2 6
#define	BT03_3 7
#define	BT03_4 8
#define BT03_5 9
#define BT04_1 10
#define BT04_2 11
#define BT04_3 12
#define BT04_4 13
#define BT04_5 14
#define BT05_1 15
#define BT05_2 16
#define BT05_3 17
#define BT05_4 18
#define BT05_5 19
#define BT06_1 20
#define BT06_2 21
#define BT06_3 22
#define BT06_4 23
#define BT06_5 24
#define BT06_6 25
#define BT_TEST 999

#define EXE_Q BT_TEST

volatile unsigned int g_SysTickTimer_u32 = 0;
volatile unsigned int g_Timer0Ch0_u32 = 0;
volatile unsigned int g_Timer0Ch1_u32 = 0;
volatile unsigned int g_Timer0Ch2_u32 = 0;
volatile unsigned int g_Timer0Ch3_u32 = 0;
volatile unsigned char g_UARTDataRx_u8 = 0;
volatile unsigned char g_UARTDataTx_u8 = 0;

volatile unsigned char g_NumberArrayGet_u8 = 0;
volatile unsigned char g_ArrayStringGet_aa[22];


int main(void){
	
	#if (EXE_Q == BT01_3)
		BT01_Ex3();
	#elif (EXE_Q == BT02_1)
		BT02_Ex1();
	#elif (EXE_Q == BT02_2)
		BT02_Ex2();
	#elif (EXE_Q == BT02_3)
		BT02_Ex3();
	#elif (EXE_Q == BT02_4)
		BT02_Ex4();
	#elif (EXE_Q == BT02_5)
		BT02_Ex5();
	#elif (EXE_Q == BT03_2)
		BT03_Ex2();
	#elif (EXE_Q == BT03_3)
		BT03_Ex3();
	#elif (EXE_Q == BT03_4)
		BT03_Ex4();
	#elif (EXE_Q == BT03_5)
		BT03_Ex5();
	#elif (EXE_Q == BT04_1)
		BT04_Ex1();
	#elif (EXE_Q == BT04_2)
		BT04_Ex2();
	#elif (EXE_Q == BT04_3)
		BT04_Ex3();
	#elif (EXE_Q == BT04_4)
		BT04_Ex4();
	#elif (EXE_Q == BT04_5)
		BT04_Ex5();
	#elif (EXE_Q == BT05_1)
		BT05_Ex1();
	#elif (EXE_Q == BT05_2)
		BT05_Ex2();
	#elif (EXE_Q == BT05_3)
		BT05_Ex3();
	#elif (EXE_Q == BT05_4)
		BT05_Ex4();
	#elif (EXE_Q == BT05_5)
		BT05_Ex5();	
	#elif (EXE_Q == BT06_1)
		BT06_Ex1();
	#elif (EXE_Q == BT06_2)
		BT06_Ex2();
	#elif (EXE_Q == BT06_3)
		BT06_Ex3();
	#elif (EXE_Q == BT06_4)
		BT06_Ex4();
	#elif (EXE_Q == BT06_5)
		BT06_Ex5();
	#elif (EXE_Q == BT06_6)
		BT06_Ex6();
	#else
		/*test_priority(); */
		/*ConfigureClockSoure_SlowIRC();*/
		/*Test_Timer();*/
		/*Test_UART();*/
		Test_SPI();
		
	#endif /* choose function */
}

/* Interrupt Function */
void PORTC_IRQHandler(void){
	if ((PORTC -> PORTC_PCR12) & (1u << 24)){
		/* clear interupt bit */
		PORTC -> PORTC_PCR12 |= (1u << 24); /* write 1 to clear (always have this step)*/
		
		/* Action */
		g_StatusBT03Ex2_u8 = 1; /* BT03_Ex2 */
		g_StatusBT03Ex3_u8 = 1; /* BT03_Ex3 */	
		g_StatusBT03Ex4_u8 = 1; /* BT03_Ex4 */
		g_StatusBT03Ex5_u8 = 1; /* BT03_Ex5 */
	}
	
	if ((PORTC -> PORTC_PCR13) & (1u << 24)){
		/* clear interupt bit */
		PORTC -> PORTC_PCR13 |= (1u << 24); /* write 1 to clear (always have this step)*/
		
		/* Action */
		g_StatusBT03Ex3_u8 = 0; /* BT03_Ex3 */
		g_StatusBT03Ex5_u8 = 2; /* BT03_Ex5 */
	}
}

void SysTick_Handler(void){
	g_SysTickTimer_u32++;
}

void LPIT0_Ch0_IRQHandler(void){
	LPIT -> LPIT_MSR |= (1u << 0); /* w1c (i dont know if reset it auto  flag as flag of Systimer ? ) */
	g_Timer0Ch0_u32++;
}

void LPIT0_Ch1_IRQHandler(void){
	LPIT -> LPIT_MSR |= (1u << 1); /* w1c (i dont know if reset it auto  flag as flag of Systimer ? ) */
	g_Timer0Ch1_u32++;
}

void LPIT0_Ch2_IRQHandler(void){
	LPIT -> LPIT_MSR |= (1u << 2); /* w1c (i dont know if reset it auto  flag as flag of Systimer ? ) */
	g_Timer0Ch2_u32++;
}

void LPIT0_Ch3_IRQHandler(void){
	LPIT -> LPIT_MSR |= (1u << 3); /* w1c (i dont know if reset it auto  flag as flag of Systimer ? ) */
	g_Timer0Ch3_u32++;
}

void LPUART1_RxTx_IRQHandler(void){ /* Commonly, We use polling for Tx and Interrupt for Rx */
	unsigned int f_RegisterTemp_u32;
	/* Tx */
	//g_UARTDataTx_u8 = 'h';
	//if ( ((LPUART1 -> LPUART_STAT) & (1u << 23)) ){ /* wait bit 23 = 1 (data emty) */
	//	LPUART1 -> LPUART_DATA = g_UARTDataTx_u8;
	//}
	
	/* Rx */
	if ( ((LPUART1 -> LPUART_STAT) & (1u << 21)) ){ /* if bit 21 = 1 (data full) (if we use both Tx and Rx then using "if" ) */
		f_RegisterTemp_u32 = (LPUART1 -> LPUART_DATA);	
		f_RegisterTemp_u32 = f_RegisterTemp_u32 << 25; /* just using 7 bits, so shift 32-7=25 */
		f_RegisterTemp_u32 = f_RegisterTemp_u32 >> 25;
		g_UARTDataRx_u8 = (unsigned char)f_RegisterTemp_u32;
		g_ArrayStringGet_aa[g_NumberArrayGet_u8] = g_UARTDataRx_u8;
		g_NumberArrayGet_u8++;
		
		
		if (g_NumberArrayGet_u8 == 3){
			GPIOD -> GPIOD_PDOR ^= (1u << 16); 
		}
		/*if ((g_UARTDataRx_u8 == 92) || (g_NumberArrayGet_u8 > 21)){ 
			for (unsigned char i=g_NumberArrayGet_u8; i<22; i++){
				g_ArrayStringGet_aa[i] = '\0'; 
			}
			g_NumberArrayGet_u8 = 0;
		}
		else{
			g_ArrayStringGet_aa[g_NumberArrayGet_u8] = g_UARTDataRx_u8;
			g_NumberArrayGet_u8++;
		}*/
	}
}

