#include "main_2.h"


volatile UINT8 g_AdrL7D_aa[8] = {0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8}; /* Digits 0->7 */
volatile UINT8 g_Intensity_u8 = 15;
volatile UINT8 g_MaL7D_aa[12] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x80, 0x01}; /* 0->9, 10 is '.', 11 is '-' */
volatile UINT16 g_DisplayL7D_u16 = 0;

volatile UINT8 g_StatusTimeDate_u8 = 0;

volatile UINT8 g_NumberArrayGet_u8;
volatile UINT8 g_UARTDataRx_u8;
volatile UINT8 g_ArrayStringGet_aa[12]; /* Get maximum 10 chars ('Start char' + 10 data chars + 'End char') */

volatile UINT16 g_Year_u16 = 1999;
volatile UINT8 g_Month_u8 = 4;
volatile UINT8 g_Date_u8 = 15;
volatile UINT8 g_Hour_u8 = 22;
volatile UINT8 g_Minute_u8 = 1;
volatile UINT8 g_Seconds_u8 = 6;
volatile UINT8 g_HourAlarm_u8 = 0;
volatile UINT8 g_MinuteAlarm_u8 = 0;
volatile UINT8 g_SecondsAlarm_u8 = 0;
volatile UINT8 g_EnableAlarm_u8 = 0;
volatile UINT8 g_OffAlarm10s_u8 = 0;

volatile UINT8 g_Timer0Ch0_u8 = 0;
volatile UINT8 g_EnableSend_u8 = 0;



/*-------------------------------------------------------------------------------------------*/
void Setup_ClockCrystal_8MHZ(UINT8 PREDIV, UINT8 MULTI, UINT8 DIVCORE, UINT8 DIVBUS, UINT8 DIVFLASH, UINT8 PLLDIV2){ /* Clock */
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
	f_RegisterTemp_u32 |= ((UINT32)PREDIV << 8); /* PreDiv */
	f_RegisterTemp_u32 |= ((UINT32)MULTI << 16); /* Multi */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ x Multi / PreDiv */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_RegisterTemp_u32 |= ((UINT32)PLLDIV2 << 8); /* SPLL_DIV2 */
	SCG -> SCG_SPLLDIV = f_RegisterTemp_u32;
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
	f_RegisterTemp_u32 |= ((UINT32)DIVCORE << 16); /* DIVCORE (bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= ((UINT32)DIVBUS << 4); /* DIVBUS (bits 7->4) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= ((UINT32)DIVFLASH << 0); /* DIVFLASH  (bits 3->0) */ 
	SCG -> SCG_RCCR = f_RegisterTemp_u32; /* CORE, BUS, FLASH */
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
}

/*----------------------------------------------------------------------------------------*/
void Setup_LedAlarm(void){ /* Alarm Led */
	PCC -> PCC_PORTD |= (1u << 30); /* disable clock control (bit 30 = 1) */
	PORTD -> PORTD_PCR16 |= (1u << 8); /* Choose GPIO Mode for PORTx_PCRy */
	PORTD -> PORTD_PCR16 &= ~(1u << 1) ; /* Disabled pull-up/down for PORTx_PCRy */
	GPIOD -> GPIOD_PDDR |= (1u << 16); /* Set mode Output for PIN_16 */
	GPIOD -> GPIOD_PDOR |= (1u << 16); /* Initial LED Green Off */
}

/*--------------------------------------------------------------------------------------------*/
void Setup_Button(void){ /* Button (Port C) */
	PCC -> PCC_PORTC |= (1u << 30); /* disable clock control (bit 30 = 1) */
	
	PORTC -> PORTC_PCR12 |= (1u << 8); /* Choose GPIO Mode for PORTx_PCRy */
	PORTC -> PORTC_PCR12 &= ~(1u << 1); /* Disabled pull-up/down for PORTx_PCRy */
	GPIOC -> GPIOC_PDDR &= ~(1u << 12); /* Set mode Input for PIN_12 */
	
	PORTC -> PORTC_PCR13 |= (1u << 8); /* Choose GPIO Mode for PORTx_PCRy */
	PORTC -> PORTC_PCR13 &= ~(1u << 1); /* Disabled pull-up/down for PORTx_PCRy */
	GPIOC -> GPIOC_PDDR &= ~(1u << 13); /* Set mode Input for PIN_13 */
	
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 29); /*set 1 for bit 30 of NVIC_ISER1 */
	PORTC -> PORTC_PCR12 |= (10u << 16); /* set 1100 for bits 16->19 (Falling-Edge) */
	PORTC -> PORTC_PCR13 |= (10u << 16); /* set 1100 for bits 16->19 (Falling-Edge) */
}

/*-------------------------------------------------------------------------------------------*/
void Setup_LPSPI0(UINT8 SCKDIV, UINT8 PRESCALE, UINT8 FRAMESIZE){
	volatile UINT32 f_RegisterTemp_u32;
	/* Setup Tx/Rx pin */
	PCC -> PCC_PORTE |= (1u << 30); /* Enable */
	PORTE -> PORTE_PCR0 = 0u;
	PORTE -> PORTE_PCR0 |= (2u << 8); /* SCK */
	PORTE -> PORTE_PCR1 = 0u;
	PORTE -> PORTE_PCR1 |= (2u << 8); /* MISO */
	PORTE -> PORTE_PCR2 = 0u;
	PORTE -> PORTE_PCR2 |= (2u << 8); /* MOSI */
	PORTE -> PORTE_PCR6 = 0u;
	PORTE -> PORTE_PCR6 |= (2u << 8); /* Control Slave 2 (PCS_2) */
	
	PCC -> PCC_LPSPI0 = 0u;
	PCC -> PCC_LPSPI0 |= (6u << 24); /* Choose DIV2_PLL */
	PCC -> PCC_LPSPI0 |= (1u << 30); /* Enable */
	
	/**/
	LPSPI0 -> LPSPI_CCR = (UINT32)SCKDIV; /* bits 7->0 to choose SCKDIV = (0 + 2) "+2" is defaul auto add */
	f_RegisterTemp_u32 = 0u;
	/* CPOL = 0 and CPHA = 0 (bits 31 and 30) */
	f_RegisterTemp_u32 |= ((UINT32)PRESCALE << 27); /* 001 for bits 29->27 (PRESCALE) */ /* => 36 / (SCKDIV * Prescale) = 9 MHZ (<10MHZ is ok) */
	f_RegisterTemp_u32 |= (2u << 24); /* 10 for bits 25->24 (PCS) */
	/* LSBF = 0 for MSB first (bit 24) */
	f_RegisterTemp_u32 |= (UINT32)FRAMESIZE; /* bits 11->0 for FRAME_SIZE (auto +1) */
	LPSPI0 -> LPSPI_TCR = f_RegisterTemp_u32;
	
	LPSPI0 -> LPSPI_FCR = 0u; /* Set Tx/Rx_water = 1 (Tx bits 1->0 = 00) (Rx bits 17->16 = 00) */ 
	
	LPSPI0 -> LPSPI_CR = 0u; /* Disable LPSPI_Module */
	LPSPI0 -> LPSPI_CR |= (1u << 3); /* Set 1 for bit 3 (DBGEN) */
	LPSPI0 -> LPSPI_CFGR1 |= (1u << 3); /* Set NoStall = 1 (bit 3) */
	LPSPI0 -> LPSPI_CFGR1 |= (1u << 0); /* Set 1 for bit 0 to choose device is Master */
	LPSPI0 -> LPSPI_CR |= (1u << 0); /* Enable LPSPI_Module (Bit 0 = 1) */
}

/*-------------------------------------------------------------------------------------------*/
void Setup_Led7D(void){ /* Initial Led 7D */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xFCF1; /* Turn on ShutDown_Mode */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xFBF7; /* Set Scan_Limit is full led (8 led) */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xFAFF; /* Set Intensity is max light */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xFFF0; /* Display mode is normal */
}

/*-------------------------------------------------------------------------------------------*/
void Setup_LPUART1(UINT16 SBR, UINT8 OSR){
	volatile UINT32 f_RegisterTemp_u32;
	/* Setup Tx/Rx pin */
	PCC -> PCC_PORTC |= (1u << 30); /* Enable */
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
	f_RegisterTemp_u32 = (UINT32)SBR; /* Choose SBR (just 13bits 12-0) */
	f_RegisterTemp_u32 |= ((UINT32)OSR << 24); /* Choose OSR = 10 by set 01001 for bits 28-24 */
	/* Choose 1 stop bit by configure bit 13 is 0 */
	LPUART1 -> LPUART_BAUD = f_RegisterTemp_u32;
	
	/* Setup Frame ( StartBit + 8 bits data + ParityBit + StopBit ) */
	LPUART1 -> LPUART_CTRL |= (1u << 4); /* set 1 for bit 4 to choose 9 bits (8 bits data + ParityBit) */
	LPUART1 -> LPUART_CTRL |= (0u << 0);/* configure bit 0 is 0 to choose parity even */
	/* configure bit 4 is 0 to choose data have 8 bits */
	LPUART1 -> LPUART_CTRL |= (1u << 1); /* configure bit 1 is 1 to enable parity bit */
	
	/* Commonly, We use polling for Tx and Interrupt for Rx */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 1); /* ID_33 LPUART_1 */
	//INTERUPT_SETPEND ->  NVIC_ISER1 |= (1u << 1); /* ID_33 LPUART_1 */
	//LPUART1 -> LPUART_CTRL |= (1u << 23); /* Enable TIE (Interrupt for Tx) */
	LPUART1 -> LPUART_CTRL |= (1u << 19); /* Enable Tx Data */
	LPUART1 -> LPUART_CTRL |= (1u << 21); /* Enable RIE (Interrupt for Rx) */
	LPUART1 -> LPUART_CTRL |= (1u << 18); /* Enable Rx Data */
}

/*--------------------------------------------------------------------------------------------*/
void Setup_Timer0Ch0(UINT32 PLL_DIV2){
	/* Configure for Timer */
	/* Set interrupt ID */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 16); /* ID 48 (Timer CH0) */
	
	/* Choose PCC_LPIT choose PLL_DIV2 */
	PCC -> PCC_LPIT &= ~(1u << 30); /* Disable Clock */
	PCC -> PCC_LPIT |= (6u << 24); /* Set 110 for bits 26->24 */
	PCC -> PCC_LPIT |= (1u << 30); /* Enable Clock */
	/* Configure Module Control Register (MCR) */
	LPIT -> LPIT_MCR |= (9u << 0); /* Set 1001 for bits 3->0 */
	
	/* Set Value for Timer 0 (value > 1) */
	LPIT -> LPIT_TVAL0 = (UINT32)PLL_DIV2; /* 500ms (DIV_2 = 36MHZ) */
	/* Configure Timer 0 Control Register (TCTRL0) */
	LPIT -> LPIT_TCTRL0 |= 0u;
	LPIT -> LPIT_TCTRL0 |= (0u << 24); /* Set 0000 for bits 27->24 to choose Trigger for Timer 0 */
	LPIT -> LPIT_TCTRL0 |= (1u << 23); /* Set 1 for bit 23 to choose Internal Source Trigger */
	LPIT -> LPIT_TCTRL0 |= (0u << 18); /* Set 0 for bit 18 to disable Reload value when get trigger signal (TROT) */
	LPIT -> LPIT_TCTRL0 |= (0u << 17); /* Set 0 for bit 17 to disable Timer Stop On Inetrrupt (TSOI) */ 
	LPIT -> LPIT_TCTRL0 |= (0u << 16); /* Set 0 for bit 16 to disable Timer Start On Trigger (TSOT) */ 
	LPIT -> LPIT_TCTRL0 |= (0u << 2); /* Set 00 for bits 3->2 to choose 32-bit Periodic Counter */ 
	LPIT -> LPIT_TCTRL0 |= (0u << 1); /* Set 0 for bit 1 to dont use Chain bit because just only use a timer channel */
	LPIT -> LPIT_TCTRL0 |= (1u << 0); /* Set 1 for bit 0 to enable Timer 0 */
	
	/* Configure Module Interrupt Enable Register (MIER) */
	LPIT -> LPIT_MIER |= (1u << 0); /* Set Enable Interrupt for Timer 0 ||| When occuring Interrupt -> Read Module Status Regiger (MSR) */
	/* Set Timer Enable Register (SETTEN) */
	LPIT -> LPIT_SETTEN |= (1u << 0); /* Set Enable for Timer 0 */
}
	
/*-------------------------------------------------------------------------------------------*/
UINT16 Com_GML7D(UINT8 l_AdrL7D_u8, UINT8 l_MaL7D_u8){ /* Display Led 7D */
	g_DisplayL7D_u16 = 0u;
	if ((l_MaL7D_u8 < 12) && (l_AdrL7D_u8 < 8)){
		g_DisplayL7D_u16 = (UINT16)(((UINT16)g_AdrL7D_aa[l_AdrL7D_u8] << 8) | (UINT16)g_MaL7D_aa[l_MaL7D_u8]) ;
	}
	return g_DisplayL7D_u16;
}

/*-------------------------------------------------------------------------------------------*/
void Com_AdjustIntensity(void){ /* Calibrate Intensity of Led 7D */
	UINT16 f_Temp_u16 = 0xFA00; /* FA is address of Intensity in L7D */
	f_Temp_u16 |= (UINT16)g_Intensity_u8; 
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = f_Temp_u16; /* Set Intensity */
}

/*---------------------------------------------------------------------------------*/
void Com_ControlLed7D(UINT16 l_DataSent_u16){
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = l_DataSent_u16; /* Control Led 7D */
}

/*-------------------------------------------------------------------------------------*/
void Com_ProcessDataUART(void){
	UINT8 f_CountD_u8 = 0;
	UINT8 f_CountT_u8 = 0;
	UINT8 f_CountA_u8 = 0;
	UINT8 f_CountE_u8 = 0;
	UINT8 f_Detect_u8 = 0;
	
	/* check valid of string get: Dxx.xx.xxxxE / Txx-xx-xx--E */
	f_Detect_u8 = 0;
	/* check Start char and End char */
	if ( ((g_ArrayStringGet_aa[0] != 'D') && (g_ArrayStringGet_aa[0] != 'T') && (g_ArrayStringGet_aa[0] != 'A')) || (g_ArrayStringGet_aa[11] != 'E') ){
		f_Detect_u8 = 1;
		goto DETECT;
	}
	/* Check amount of Start/End char */
	for(UINT8 i=0; i<12; i++){
		if (g_ArrayStringGet_aa[i] == 'D')
			f_CountD_u8++;
		else if (g_ArrayStringGet_aa[i] == 'T')
			f_CountT_u8++;
		else if (g_ArrayStringGet_aa[i] == 'A')
			f_CountA_u8++;
		else if (g_ArrayStringGet_aa[i] == 'E')
			f_CountE_u8++;
		
		if ((f_CountE_u8 > 1) || (f_CountD_u8 > 1) || (f_CountT_u8 > 1) || (f_CountA_u8 > 1)){
			f_Detect_u8 = 1;
			goto DETECT;
		}
		if ((f_CountD_u8 > 0) && (f_CountT_u8 > 0) && (f_CountA_u8 > 0)){ /* Only a the type Start char */
			f_Detect_u8 = 1;
			goto DETECT;
		}
	}
	/* Check valid chars of data */
	for (UINT8 i=1; i<11; i++){
		if ((i == 3) || (i == 6)){
			continue;
		}
		if ((g_ArrayStringGet_aa[i] < 48) || (g_ArrayStringGet_aa[i] > 57)){
			if (((g_ArrayStringGet_aa[0] == 'T') || (g_ArrayStringGet_aa[0] == 'A')) && (i > 8) && (g_ArrayStringGet_aa[i] == '-')){
				continue;
			}
			f_Detect_u8 = 1;
			goto DETECT;
		}
	}
	if (g_ArrayStringGet_aa[0] == 'D'){ /* Check valid chars of Date */
		if ((g_ArrayStringGet_aa[3] != '.') || (g_ArrayStringGet_aa[6] != '.')){
			f_Detect_u8 = 1;
			goto DETECT;
		}
	}
	else if ((g_ArrayStringGet_aa[0] == 'T') || (g_ArrayStringGet_aa[0] == 'A')){ /* Check valid chars of Time */
		if ((g_ArrayStringGet_aa[3] != '-') || (g_ArrayStringGet_aa[6] != '-')){
			f_Detect_u8 = 1;
			goto DETECT;
		}
	}
	
	DETECT:
	
	/* process data */
	if (f_Detect_u8 == 0){ /* if all data valid */
		/* get the first number */
		if (g_ArrayStringGet_aa[0] == 'D'){
			g_Date_u8 = (g_ArrayStringGet_aa[1] - 48) * 10; /* Ch */
			g_Date_u8 += (g_ArrayStringGet_aa[2] - 48); /* Dv */
			g_Month_u8 = (g_ArrayStringGet_aa[4] - 48) * 10; /* Ch */
			g_Month_u8 += (g_ArrayStringGet_aa[5] - 48); /* Dv */
			g_Year_u16 = (g_ArrayStringGet_aa[7] - 48) * 1000; /* Ng */
			g_Year_u16 += ((g_ArrayStringGet_aa[8] - 48) * 100); /* Tr */
			g_Year_u16 += ((g_ArrayStringGet_aa[9] - 48) * 10); /* Ch */
			g_Year_u16 += (g_ArrayStringGet_aa[10] - 48); /* Dv */
			/*
				Follow Gregorius Calendar - the standard calendar is used almost of the world
				It specify that amount of years (% 4 == 0) and (% 100 != 0) is leap year
			*/
			if ((g_Date_u8 == 0) || (g_Month_u8 == 0) || (g_Month_u8 > 12)){
				goto ERROR;
			}
			if (g_Month_u8 == 2){
				if ( (g_Year_u16%4 == 0) && (g_Year_u16%100 != 0) ){ /* Leap year */
					if (g_Date_u8 > 29){
						goto ERROR;
					}
				}
				else { /* Normal year */
					if ( g_Date_u8 > 28 ){
						goto ERROR;
					}
				}
			}
			else if ( (g_Month_u8==4) || (g_Month_u8==6) || (g_Month_u8==9) || (g_Month_u8==11) ){
				if ( g_Date_u8 > 30 ){
					goto ERROR;
				}
			}
			else {
				if ( g_Date_u8 > 31 ){
					goto ERROR;
				}
			}
		}
		else if (g_ArrayStringGet_aa[0] == 'T'){
			g_Hour_u8 = (g_ArrayStringGet_aa[1] - 48) * 10; /* Ch */
			g_Hour_u8 += (g_ArrayStringGet_aa[2] - 48); /* Dv */
			g_Minute_u8 = (g_ArrayStringGet_aa[4] - 48) * 10; /* Ch */
			g_Minute_u8 += (g_ArrayStringGet_aa[5] - 48); /* Dv */
			g_Seconds_u8 = (g_ArrayStringGet_aa[7] - 48) * 10; /* Ch */
			g_Seconds_u8 += (g_ArrayStringGet_aa[8] - 48); /* Dv */
			if ( (g_Hour_u8 > 23) || (g_Minute_u8 > 59) || (g_Seconds_u8 > 59) ){
				g_Hour_u8 = 1;
				g_Minute_u8 = 1;
				g_Seconds_u8 = 1;
				goto ERROR;
			}
		}
		else if (g_ArrayStringGet_aa[0] == 'A'){
			g_HourAlarm_u8 = (g_ArrayStringGet_aa[1] - 48) * 10; /* Ch */
			g_HourAlarm_u8 += (g_ArrayStringGet_aa[2] - 48); /* Dv */
			g_MinuteAlarm_u8 = (g_ArrayStringGet_aa[4] - 48) * 10; /* Ch */
			g_MinuteAlarm_u8 += (g_ArrayStringGet_aa[5] - 48); /* Dv */
			g_SecondsAlarm_u8 = (g_ArrayStringGet_aa[7] - 48) * 10; /* Ch */
			g_SecondsAlarm_u8 += (g_ArrayStringGet_aa[8] - 48); /* Dv */
			if ( (g_HourAlarm_u8 > 23) || (g_MinuteAlarm_u8 > 59) || (g_SecondsAlarm_u8 > 59) ){
				g_HourAlarm_u8 = 33;
				g_MinuteAlarm_u8 = 66;
				g_SecondsAlarm_u8 = 99;
				goto ERROR;
			}
		}
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = ' ';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'G';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'e';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 't';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = ' ';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'S';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'u';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'c';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'c';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'e';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 's';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 's';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = '\n';
	}
	else{
		ERROR:
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
		LPUART1 -> LPUART_DATA = '\n';
	}
}

/*--------------------------------------------------------------------------------*/
void Com_RunDateTime(void){
	/* Reset Seconds */
	if (g_Seconds_u8 > 59){
		g_Minute_u8++;
		g_Seconds_u8 = 0;
	}
	
	/* Reset Minute */
	if (g_Minute_u8 > 59){
		g_Hour_u8++;
		g_Minute_u8 = 0;
	}
	
	/* Reset Hour */
	if (g_Hour_u8 > 23){
		g_Date_u8++;
		g_Hour_u8 = 0;
	}
	
	/* Reset Date */
	if (g_Month_u8 == 2){
		if ( (g_Year_u16%4 == 0) && (g_Year_u16%100 != 0) ){ /* Leap year */
			if (g_Date_u8 > 29){
				g_Month_u8++;
				g_Date_u8 = 1;
			}
		}
		else { /* Normal year */
			if ( g_Date_u8 > 28 ){
				g_Month_u8++;
				g_Date_u8 = 1;
			}
		}
	}
	else if ( (g_Month_u8==4) || (g_Month_u8==6) || (g_Month_u8==9) || (g_Month_u8==11) ){
		if ( g_Date_u8 > 30 ){
			g_Month_u8++;
			g_Date_u8 = 1;
		}
	}
	else {
		if ( g_Date_u8 > 31 ){
			g_Month_u8++;
			g_Date_u8 = 1;
		}
	}
	
	/* Reset Month */
	if ( (g_Month_u8 > 12) || (g_Month_u8 == 0) ){
		g_Year_u16++;
		g_Month_u8 = 1;
	}
	
	/* Reset Year */
	if ( g_Year_u16 > 9999 )
		g_Year_u16 = 0;
}

/*----------------------------------------------------------------------------------*/
void Com_Alarm(void){
	if ((g_Hour_u8 == g_HourAlarm_u8) && (g_Minute_u8 == g_MinuteAlarm_u8) && (g_Seconds_u8 == g_SecondsAlarm_u8))
		g_EnableAlarm_u8 = 1;
}

/*---------------------------------------------------------------------------------*/
void PORTC_IRQHandler(void){ /* Interrupt Port C (Button) */
	if ((PORTC -> PORTC_PCR12) & (1u << 24)){ /* Choose Mode Display Time/Date */
		/* clear interupt bit */
		PORTC -> PORTC_PCR12 |= (1u << 24); /* write 1 to clear (always have this step)*/
		
		/* Action */
		g_StatusTimeDate_u8 ^= 1u;
		g_EnableAlarm_u8 = 0; /* Off Alarm */
	}
	
	if ((PORTC -> PORTC_PCR13) & (1u << 24)){
		/* clear interupt bit */
		PORTC -> PORTC_PCR13 |= (1u << 24); /* write 1 to clear (always have this step)*/
		
		/* Action */
		g_EnableAlarm_u8 = 0; /* Off Alarm */
		if (g_Intensity_u8 > 13){
			g_Intensity_u8 -= 4;
			Com_AdjustIntensity();
		}
		else if (g_Intensity_u8 > 9){
			g_Intensity_u8 -= 4;
			Com_AdjustIntensity();
		}
		else if (g_Intensity_u8 > 5){
			g_Intensity_u8 -= 4;
			Com_AdjustIntensity();
		}
		else if (g_Intensity_u8 > 1){
			g_Intensity_u8 = 0;
			Com_ControlLed7D(0xF100);
			Com_ControlLed7D(0xF200);
			Com_ControlLed7D(0xF300);
			Com_ControlLed7D(0xF400);
			Com_ControlLed7D(0xF500);
			Com_ControlLed7D(0xF600);
			Com_ControlLed7D(0xF700);
			Com_ControlLed7D(0xF800);
		}
		else if (g_Intensity_u8 < 1){
			g_Intensity_u8 = 15;
			Com_AdjustIntensity();
		}
	}
}

/*---------------------------------------------------------------------------------*/
void LPUART1_RxTx_IRQHandler(void){ /* Commonly, We use polling for Tx and Interrupt for Rx */
	unsigned int f_RegisterTemp_u32;
	
	/* Rx */
	if ( ((LPUART1 -> LPUART_STAT) & (1u << 21)) ){ /* if bit 21 = 1 (data full) */
		f_RegisterTemp_u32 = (LPUART1 -> LPUART_DATA);	
		f_RegisterTemp_u32 = f_RegisterTemp_u32 << 24; /* using 8 bits, so shift 32-8=24 */
		f_RegisterTemp_u32 = f_RegisterTemp_u32 >> 24;
		g_UARTDataRx_u8 = (UINT8)f_RegisterTemp_u32;
		g_ArrayStringGet_aa[g_NumberArrayGet_u8] = g_UARTDataRx_u8;
		g_NumberArrayGet_u8++;
		if ((g_ArrayStringGet_aa[g_NumberArrayGet_u8-1] == 'E') || (g_NumberArrayGet_u8 >= 12)){ /* limit get 12 chars */
			for (UINT8 i=g_NumberArrayGet_u8; i<12; i++){ /* clear the redundant chars behind '=' of the previous function */
				g_ArrayStringGet_aa[i] = '\0'; 
			}
			Com_ProcessDataUART();
			g_NumberArrayGet_u8 = 0;
		}
	}
}

/*-------------------------------------------------------------------------------*/
void LPIT0_Ch0_IRQHandler(void){
	LPIT -> LPIT_MSR |= (1u << 0); /* w1c (i dont know if reset it auto  flag as flag of Systimer ? ) */
	g_Timer0Ch0_u8++;
	if (g_EnableAlarm_u8 == 1){
		GPIOD -> GPIOD_PDOR ^= ( 1u << 16 );
		g_OffAlarm10s_u8++;
		if (g_OffAlarm10s_u8 >= 20){ /* Flash max 10s */
			g_OffAlarm10s_u8 = 0;
			g_EnableAlarm_u8 = 0;
		}
	}
	if(g_Timer0Ch0_u8 >= 2){
		g_Seconds_u8++;
		g_Timer0Ch0_u8 = 0;
		g_EnableSend_u8 = 0;
	}
}
