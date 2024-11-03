#include "main.h"

volatile unsigned char g_UARTDataRx_u8 = 0;
volatile unsigned char g_NumberArrayGet_u8 = 0;
volatile unsigned char g_ArrayStringGet_aa[22]; /* Get maximum 22 chars (uint32 + uint32 =) */
volatile unsigned char g_ArrayStringSend_aa[10]; /* UInterger type max have 10 nums */

int main(void){
	unsigned int f_RegisterTemp_u32;
	
	/* wait LK = 0 to disable OSC Control Status Register */
	SCG -> SCG_SOSCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable OSC Control Status Register (Reset 0 for bit 0) */
	/* After Disable OSC Control Status Register, then we can write data to SCG_SOSCCFG Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SOSCCFG Register */
	f_RegisterTemp_u32 |= (1u << 2); /* Set 1 for bit 2 to select trimming system (use for crystal) */
	f_RegisterTemp_u32 |= (2u << 4); /* Set 10 for bits 5->4 (Choose 8MHZ) */
	SCG -> SCG_SOSCCFG = f_RegisterTemp_u32; /* Configure source clock of OSC is 8MHZ */
	/* Don't need use SCG_OSCCDIV Register */
	/* Return to Enable OSC Control Status Register */
	f_RegisterTemp_u32 = 1u;
	f_RegisterTemp_u32 |= (1u << 23);
	SCG -> SCG_SOSCCSR = f_RegisterTemp_u32;
	while ( !((SCG -> SCG_SOSCCSR) & (1u << 24)) ){} /* Wait OSC valid */
	
	/* wait LK = 0 to disable PLL Control Status Register */
	SCG -> SCG_SPLLCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SPLLCSR = 0u; /* Disable PLL Control Status Register (Reset 0 for bit 0) */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLCFG Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLCFG Register */
	f_RegisterTemp_u32 &= ~(1u << 0); /* Reset bit 0 to Choose source Input PLL is System OSC */
	f_RegisterTemp_u32 |= (1u << 8); /* Set 001 for bits 10->8 to select Div_2 */
	f_RegisterTemp_u32 |= (8u << 16); /* Set 00100 for bits 20->16 to select Mul_24 */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ x 6 */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register (Not yet use) */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_RegisterTemp_u32 |= (1u << 8); /* set 001 for bits 10->8 to using SPLL_DIV2 with Div_1 */
	SCG -> SCG_SPLLDIV = f_RegisterTemp_u32; /* Configure SCG_SPLLDIV_2 doesn't div */
	/* Return to Enable PLL Control Status Register */
	f_RegisterTemp_u32 = 1u;
	f_RegisterTemp_u32 |= (1u << 23);
	SCG -> SCG_SPLLCSR = f_RegisterTemp_u32;
	while ( !((SCG -> SCG_SPLLCSR) & (1u << 24)) ){} /* Wait PLL valid */
	
	/* Setup for RUN Mode */
	/* Choose SCG */
	f_RegisterTemp_u32 = 0; /* or read from SCG_RCCR Register */
	f_RegisterTemp_u32 |= (6u << 24); /* set 0110 for bits 27->24 for choosing System_PLL */
	/* CORE and System (MAX = 80MHZ for RUN Mode) */
	f_RegisterTemp_u32 |= (0u << 16); /* Because OSC provide 8MHZ x6 with PLL, so in oder to have 48MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= (0u << 4); /* set 0001 for bits 7->4 to DIV 1 (we need 48MHZ) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= (3u << 0); /* set 0011 for bits 3->0 to DIV 4 */ 
	SCG -> SCG_RCCR = f_RegisterTemp_u32; /* CORE 48MHZ, BUS 48MHZ, FLASH 12MHZ */
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Setup Tx/Rx pin */
	PCC -> PCC_PORTC |= (1u << 30); /**/
	PORTC -> PORTC_PCR6 = 0u;
	PORTC -> PORTC_PCR6 |= (2u << 8);
	PORTC -> PORTC_PCR7 = 0u;
	PORTC -> PORTC_PCR7 |= (2u << 8);
	
	/* Setup LPUART */
	PCC -> PCC_LPUART1 |= (6u << 24); /* Choose PLL */
	PCC -> PCC_LPUART1 |= (1u << 30);
		
	/* Setup Baudrate */
	LPUART1 -> LPUART_CTRL &= ~(1u << 19); /* Disable Tx */
	LPUART1 -> LPUART_CTRL &= ~(1u << 18); /* Disable Rx */
	f_RegisterTemp_u32 = 250u; /* Choose SBR = 250 (just 13bits 12-0) */
	f_RegisterTemp_u32 |= (9u << 24); /* Choose OSR = 10 by set 01001 for bits 28-24 */
	/* Choose 1 stop bit by configure bit 13 is 0 */
	LPUART1 -> LPUART_BAUD = f_RegisterTemp_u32; /* 19200 baud */
	
	/* Setup Frame ( StartBit + 8 bits data + ParityBit + StopBit ) */
	LPUART1 -> LPUART_CTRL |= (1u << 0); /* configure bit 0 is 1 to choose parity odd */
	/* configure bit 4 is 0 to choose data have 8 bits */
	LPUART1 -> LPUART_CTRL |= (1u << 1); /* configure bit 1 is 1 to enable parity bit */
	
	/* Commonly, We use polling for Tx and Interrupt for Rx */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 1); /* ID_33 LPUART_1 */
	//LPUART1 -> LPUART_CTRL |= (1u << 23); /* Enable TIE (Interrupt for Tx) */
	LPUART1 -> LPUART_CTRL |= (1u << 19); /* Enable Tx Data */
	LPUART1 -> LPUART_CTRL |= (1u << 21); /* Enable RIE (Interrupt for Rx) */
	LPUART1 -> LPUART_CTRL |= (1u << 18); /* Enable Rx Data */
	
	while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
	LPUART1 -> LPUART_DATA = 'h';
		
	while(1){}
}

void LPUART1_RxTx_IRQHandler(void){ /* Commonly, We use polling for Tx and Interrupt for Rx */
	unsigned int f_RegisterTemp_u32;
	
	/* Rx */
	if ( ((LPUART1 -> LPUART_STAT) & (1u << 21)) ){ /* if bit 21 = 1 (data full) */
		f_RegisterTemp_u32 = (LPUART1 -> LPUART_DATA);	
		f_RegisterTemp_u32 = f_RegisterTemp_u32 << 25; /* just using 7 bits, so shift 32-7=25 */
		f_RegisterTemp_u32 = f_RegisterTemp_u32 >> 25;
		g_UARTDataRx_u8 = (unsigned char)f_RegisterTemp_u32;
		g_ArrayStringGet_aa[g_NumberArrayGet_u8] = g_UARTDataRx_u8;
		g_NumberArrayGet_u8++;
		if ((g_ArrayStringGet_aa[g_NumberArrayGet_u8-1] == '=') || (g_NumberArrayGet_u8 > 21)){ /* >21 is limit get 22 chars (uint + uint =) */
			for (unsigned char i=g_NumberArrayGet_u8; i<22; i++){ /* clear the redundant chars behind '=' of the previous function */
				g_ArrayStringGet_aa[i] = '\0'; 
			}
			ProcessData();
			g_NumberArrayGet_u8 = 0;
		}
	}
}

void ProcessData(void){
	unsigned int f_Num1_u32 = 0;
	unsigned int f_Num2_u32 = 0;
	unsigned int f_Num3_u32 = 0;
	unsigned char f_NumsArray_u8 = 0;
	unsigned char f_NumsArrayTemp_u8 = 0;
	unsigned char f_Detect_u8 = 0;
	
	/* check valid of string get */
	f_Detect_u8 = 0;
	f_NumsArray_u8 = 0;
	while (g_ArrayStringGet_aa[f_NumsArray_u8] != '\0'){
		if ((g_ArrayStringGet_aa[f_NumsArray_u8] < 48) || (g_ArrayStringGet_aa[f_NumsArray_u8] > 57)){
			if ( (g_ArrayStringGet_aa[f_NumsArray_u8] != '+') && (g_ArrayStringGet_aa[f_NumsArray_u8] != '=') ){
				f_Detect_u8 = 1;
				goto DETECT;
			}
		}
		f_NumsArray_u8++;
	}
	/* check num_1 < 10 chars */
	f_NumsArray_u8 = 0;
	while (g_ArrayStringGet_aa[f_NumsArray_u8] != '+'){
		if (f_NumsArray_u8 >= 10){
			f_Detect_u8 = 1;
			goto DETECT;
		}
		f_NumsArray_u8++;
	}
	/* check num_2 < 10 chars */
	f_NumsArray_u8++; /* pass '+' */
	f_NumsArrayTemp_u8 = f_NumsArray_u8; /* save as template value of stt */
	while (g_ArrayStringGet_aa[f_NumsArray_u8] != '='){
		if (f_NumsArray_u8 >= (f_NumsArrayTemp_u8 + 10)){ /* template value of stt + 10 (num_2 have 10 chars (uint)) */
			f_Detect_u8 = 1;
			goto DETECT;
		}
		f_NumsArray_u8++;
	}
	DETECT:
	
	/* process data */
	if (f_Detect_u8 == 0){ /* if all data valid */
		/* get the first number */
		f_NumsArray_u8 = 0;
		f_Num1_u32 = 0;
		while (g_ArrayStringGet_aa[f_NumsArray_u8] != '+'){
			f_Num1_u32 = f_Num1_u32*10 + (g_ArrayStringGet_aa[f_NumsArray_u8] - 48);
			f_NumsArray_u8++;
		}
		/* get the second number */
		f_NumsArray_u8++; /* pass '+' */
		f_Num2_u32 = 0;
		while (g_ArrayStringGet_aa[f_NumsArray_u8] != '='){
			f_Num2_u32 = f_Num2_u32*10 + (g_ArrayStringGet_aa[f_NumsArray_u8] - 48);
			f_NumsArray_u8++;
		}
		/* result add math */
		f_Num3_u32 = f_Num1_u32 + f_Num2_u32;
		
		/* convert uint to char */
		f_NumsArray_u8 = 0;
		for (unsigned char i=0; i<10; i++){
			g_ArrayStringSend_aa[i] = '\0';
		}
		while (f_Num3_u32 > 0){ /* Save Data into g_ArrayStringSend (but data is inverted, ex: 123 will save 321 into g_ArrayStringSend) */
			g_ArrayStringSend_aa[f_NumsArray_u8] = (unsigned char)((f_Num3_u32%10) + 48);
			f_NumsArray_u8++;
			f_Num3_u32 /= 10;
		}
		for (unsigned char i=f_NumsArray_u8; i>0; i--){
			while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
			LPUART1 -> LPUART_DATA = g_ArrayStringSend_aa[i-1];
		}
	}
	else{
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'W';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'r';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'o';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'n';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'g';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = ' ';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'f';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'o';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'r';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'm';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'a';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 't';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = '\r';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = '\n';
	}
}
