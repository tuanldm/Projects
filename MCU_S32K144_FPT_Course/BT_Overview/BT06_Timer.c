#include "BT06_Timer.h"
#include "Setup_Port_S32K144.h"

/* Using Crystal create Core 80MHZ, Bus 40MHZ, Flash 26.67MHZ and conduct flash led to follow in per situation */

void BT06_Ex1(void){ /* TON 500ms, TOFF 500ms, Timer_CH0 mode 32 bits */
	volatile unsigned int f_RegisterTemp_u32;
	
	/* Set interrupt ID */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 16); /* ID 48 (Timer CH0) */
	
	/* wait LK = 0 to disable OSC Control Status Register */
	SCG -> SCG_SOSCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable OSC Control Status Register (Reset 0 for bit 0) */
	/* Don't need configure SCG_OSCCDIV Register (Not yet use) */
	/* After Disable OSC Control Status Register, then we can write data to SCG_SOSCCFG Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SOSCCFG Register */
	f_RegisterTemp_u32 |= (1u << 2); /* Set 1 for bit 2 to select trimming system (use for crystal) */
	f_RegisterTemp_u32 |= (2u << 4); /* Set 10 for bits 5->4 (Choose 8MHZ) */
	SCG -> SCG_SOSCCFG = f_RegisterTemp_u32; /* Configure source clock of OSC is 8MHZ */
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
	f_RegisterTemp_u32 |= (0u << 0); /* Reset bit 0 to Choose source Input PLL is System OSC */
	f_RegisterTemp_u32 |= (0u << 8); /* Set 000 for bits 10->8 to select Div_1 */
	f_RegisterTemp_u32 |= (4u << 16); /* Set 00100 for bits 20->16 to select Mul_20 */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ x 10 */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_RegisterTemp_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SPLL_DIV2 with Div_2 */
	SCG -> SCG_SPLLDIV = f_RegisterTemp_u32; /* PLL_DIV2 40MHZ */
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
	f_RegisterTemp_u32 |= (0u << 16); /* Because OSC provide 8MHZ x10 with PLL, so in oder to have 80MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 (BUS 40MHZ) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= (2u << 0); /* set 0010 for bits 3->0 to DIV 3 (Flash 26.67MHZ) */ 
	SCG -> SCG_RCCR = f_RegisterTemp_u32;
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Configure for Timer */
	/* Choose PCC_LPIT choose PLL_DIV2 */
	PCC -> PCC_LPIT &= ~(1u << 30); /* Disable Clock */
	PCC -> PCC_LPIT |= (6u << 24); /* Set 110 for bits 26->24 */
	PCC -> PCC_LPIT |= (1u << 30); /* Enable Clock */
	/* Configure Module Control Register (MCR) */
	LPIT -> LPIT_MCR |= (9u << 0); /* Set 1001 for bits 3->0 */
	
	/* Set Value for Timer 0 (value > 1) */
	LPIT -> LPIT_TVAL0 = 39999u; /* 1ms (DIV_2 = 40MHZ) */
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
	
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR ^= (1u << 15); /* Toggle status PIN15 of PORT_D */
		g_Timer0Ch0_u32 = 0;
		while (g_Timer0Ch0_u32 < 500){}
	}
}

/* ------------------------------------------------------------------------------------------------------- */
void BT06_Ex2(void){ /* TON 250ms, TOFF 750ms, Timer_CH1 mode 32 bits */
	volatile unsigned int f_RegisterTemp_u32;
	
	/* Set interrupt ID */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 17); /* ID 49 (Timer CH1) */
	
	/* wait LK = 0 to disable OSC Control Status Register */
	SCG -> SCG_SOSCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable OSC Control Status Register (Reset 0 for bit 0) */
	/* Don't need configure SCG_OSCCDIV Register (Not yet use) */
	/* After Disable OSC Control Status Register, then we can write data to SCG_SOSCCFG Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SOSCCFG Register */
	f_RegisterTemp_u32 |= (1u << 2); /* Set 1 for bit 2 to select trimming system (use for crystal) */
	f_RegisterTemp_u32 |= (2u << 4); /* Set 10 for bits 5->4 (Choose 8MHZ) */
	SCG -> SCG_SOSCCFG = f_RegisterTemp_u32; /* Configure source clock of OSC is 8MHZ */
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
	f_RegisterTemp_u32 |= (0u << 0); /* Reset bit 0 to Choose source Input PLL is System OSC */
	f_RegisterTemp_u32 |= (0u << 8); /* Set 000 for bits 10->8 to select Div_1 */
	f_RegisterTemp_u32 |= (4u << 16); /* Set 00100 for bits 20->16 to select Mul_20 */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ x 10 */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_RegisterTemp_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SPLL_DIV2 with Div_2 */
	SCG -> SCG_SPLLDIV = f_RegisterTemp_u32; /* PLL_DIV2 40MHZ */
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
	f_RegisterTemp_u32 |= (0u << 16); /* Because OSC provide 8MHZ x10 with PLL, so in oder to have 80MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 (BUS 40MHZ) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= (2u << 0); /* set 0010 for bits 3->0 to DIV 3 (Flash 26.67MHZ) */ 
	SCG -> SCG_RCCR = f_RegisterTemp_u32;
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Configure for Timer */
	/* Choose PCC_LPIT choose PLL_DIV2 */
	PCC -> PCC_LPIT &= ~(1u << 30); /* Disable Clock */
	PCC -> PCC_LPIT |= (6u << 24); /* Set 110 for bits 26->24 */
	PCC -> PCC_LPIT |= (1u << 30); /* Enable Clock */
	/* Configure Module Control Register (MCR) */
	LPIT -> LPIT_MCR |= (9u << 0); /* Set 1001 for bits 3->0 */
	
	/* Set Value for Timer 1 (value > 1) */
	LPIT -> LPIT_TVAL1 = 39999u; /* 1ms (DIV_2 = 40MHZ) */
	/* Configure Timer 0 Control Register (TCTRL1) */
	LPIT -> LPIT_TCTRL1 |= 0u;
	LPIT -> LPIT_TCTRL1 |= (0u << 24); /* Set 0000 for bits 27->24 to choose Trigger for Timer 1 */
	LPIT -> LPIT_TCTRL1 |= (1u << 23); /* Set 1 for bit 23 to choose Internal Source Trigger */
	LPIT -> LPIT_TCTRL1 |= (0u << 18); /* Set 0 for bit 18 to disable Reload value when get trigger signal (TROT) */
	LPIT -> LPIT_TCTRL1 |= (0u << 17); /* Set 0 for bit 17 to disable Timer Stop On Inetrrupt (TSOI) */ 
	LPIT -> LPIT_TCTRL1 |= (0u << 16); /* Set 0 for bit 16 to disable Timer Start On Trigger (TSOT) */ 
	LPIT -> LPIT_TCTRL1 |= (0u << 2); /* Set 00 for bits 3->2 to choose 32-bit Periodic Counter */ 
	LPIT -> LPIT_TCTRL1 |= (0u << 1); /* Set 0 for bit 1 to dont use Chain bit because just only use a timer channel */
	LPIT -> LPIT_TCTRL1 |= (1u << 0); /* Set 1 for bit 0 to enable Timer 1 */
	
	/* Configure Module Interrupt Enable Register (MIER) */
	LPIT -> LPIT_MIER |= (1u << 1); /* Set Enable Interrupt for Timer 1 ||| When occuring Interrupt -> Read Module Status Regiger (MSR) */
	/* Set Timer Enable Register (SETTEN) */
	LPIT -> LPIT_SETTEN |= (1u << 1); /* Set Enable for Timer 1 */
	
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Light status PIN15 of PORT_D */
		g_Timer0Ch1_u32 = 0;
		while (g_Timer0Ch1_u32 < 250){} /* Ligh 250ms */
		
		GPIOD -> GPIOD_PDOR |= (1u << 15); /* Off status PIN15 of PORT_D */
		g_Timer0Ch1_u32 = 0;
		while (g_Timer0Ch1_u32 < 750){} /* Off 750ms */
	}
}

/* ------------------------------------------------------------------------------------------------------- */
void BT06_Ex3(void){ /* TON 2000ms, TOFF 1500ms, Timer_CH2 mode 32 bits */
	volatile unsigned int f_RegisterTemp_u32;
	
	/* Set interrupt ID */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 18); /* ID 50 (Timer CH2) */
	
	/* wait LK = 0 to disable OSC Control Status Register */
	SCG -> SCG_SOSCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable OSC Control Status Register (Reset 0 for bit 0) */
	/* Don't need configure SCG_OSCCDIV Register (Not yet use) */
	/* After Disable OSC Control Status Register, then we can write data to SCG_SOSCCFG Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SOSCCFG Register */
	f_RegisterTemp_u32 |= (1u << 2); /* Set 1 for bit 2 to select trimming system (use for crystal) */
	f_RegisterTemp_u32 |= (2u << 4); /* Set 10 for bits 5->4 (Choose 8MHZ) */
	SCG -> SCG_SOSCCFG = f_RegisterTemp_u32; /* Configure source clock of OSC is 8MHZ */
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
	f_RegisterTemp_u32 |= (0u << 0); /* Reset bit 0 to Choose source Input PLL is System OSC */
	f_RegisterTemp_u32 |= (0u << 8); /* Set 000 for bits 10->8 to select Div_1 */
	f_RegisterTemp_u32 |= (4u << 16); /* Set 00100 for bits 20->16 to select Mul_20 */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ x 10 */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_RegisterTemp_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SPLL_DIV2 with Div_2 */
	SCG -> SCG_SPLLDIV = f_RegisterTemp_u32; /* PLL_DIV2 40MHZ */
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
	f_RegisterTemp_u32 |= (0u << 16); /* Because OSC provide 8MHZ x10 with PLL, so in oder to have 80MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 (BUS 40MHZ) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= (2u << 0); /* set 0010 for bits 3->0 to DIV 3 (Flash 26.67MHZ) */ 
	SCG -> SCG_RCCR = f_RegisterTemp_u32;
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Configure for Timer */
	/* Choose PCC_LPIT choose PLL_DIV2 */
	PCC -> PCC_LPIT &= ~(1u << 30); /* Disable Clock */
	PCC -> PCC_LPIT |= (6u << 24); /* Set 110 for bits 26->24 */
	PCC -> PCC_LPIT |= (1u << 30); /* Enable Clock */
	/* Configure Module Control Register (MCR) */
	LPIT -> LPIT_MCR |= (9u << 0); /* Set 1001 for bits 3->0 */
	
	/* Set Value for Timer 2 (value > 1) */
	LPIT -> LPIT_TVAL2 = 39999u; /* 1ms (DIV_2 = 40MHZ) */
	/* Configure Timer 0 Control Register (TCTRL2) */
	LPIT -> LPIT_TCTRL2 |= 0u;
	LPIT -> LPIT_TCTRL2 |= (0u << 24); /* Set 0000 for bits 27->24 to choose Trigger for Timer 2 */
	LPIT -> LPIT_TCTRL2 |= (1u << 23); /* Set 1 for bit 23 to choose Internal Source Trigger */
	LPIT -> LPIT_TCTRL2 |= (0u << 18); /* Set 0 for bit 18 to disable Reload value when get trigger signal (TROT) */
	LPIT -> LPIT_TCTRL2 |= (0u << 17); /* Set 0 for bit 17 to disable Timer Stop On Inetrrupt (TSOI) */ 
	LPIT -> LPIT_TCTRL2 |= (0u << 16); /* Set 0 for bit 16 to disable Timer Start On Trigger (TSOT) */ 
	LPIT -> LPIT_TCTRL2 |= (0u << 2); /* Set 00 for bits 3->2 to choose 32-bit Periodic Counter */ 
	LPIT -> LPIT_TCTRL2 |= (0u << 1); /* Set 0 for bit 1 to dont use Chain bit because just only use a timer channel */
	LPIT -> LPIT_TCTRL2 |= (1u << 0); /* Set 1 for bit 0 to enable Timer 2 */
	
	/* Configure Module Interrupt Enable Register (MIER) */
	LPIT -> LPIT_MIER |= (1u << 2); /* Set Enable Interrupt for Timer 2 ||| When occuring Interrupt -> Read Module Status Regiger (MSR) */
	/* Set Timer Enable Register (SETTEN) */
	LPIT -> LPIT_SETTEN |= (1u << 2); /* Set Enable for Timer 2 */
	
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Light status PIN15 of PORT_D */
		g_Timer0Ch2_u32 = 0;
		while (g_Timer0Ch2_u32 < 2000){} /* Ligh 2000ms */
		
		GPIOD -> GPIOD_PDOR |= (1u << 15); /* Off status PIN15 of PORT_D */
		g_Timer0Ch2_u32 = 0;
		while (g_Timer0Ch2_u32 < 1500){} /* Off 1500ms */
	}
}

/* ------------------------------------------------------------------------------------------------------- */
void BT06_Ex4(void){ /* TON 1500ms, TOFF 500ms, Timer_CH3 mode 32 bits */
	volatile unsigned int f_RegisterTemp_u32;
	
	/* Set interrupt ID */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 19); /* ID 51 (Timer CH3) */
	
	/* wait LK = 0 to disable OSC Control Status Register */
	SCG -> SCG_SOSCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable OSC Control Status Register (Reset 0 for bit 0) */
	/* Don't need configure SCG_OSCCDIV Register (Not yet use) */
	/* After Disable OSC Control Status Register, then we can write data to SCG_SOSCCFG Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SOSCCFG Register */
	f_RegisterTemp_u32 |= (1u << 2); /* Set 1 for bit 2 to select trimming system (use for crystal) */
	f_RegisterTemp_u32 |= (2u << 4); /* Set 10 for bits 5->4 (Choose 8MHZ) */
	SCG -> SCG_SOSCCFG = f_RegisterTemp_u32; /* Configure source clock of OSC is 8MHZ */
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
	f_RegisterTemp_u32 |= (0u << 0); /* Reset bit 0 to Choose source Input PLL is System OSC */
	f_RegisterTemp_u32 |= (0u << 8); /* Set 000 for bits 10->8 to select Div_1 */
	f_RegisterTemp_u32 |= (4u << 16); /* Set 00100 for bits 20->16 to select Mul_20 */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ x 10 */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_RegisterTemp_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SPLL_DIV2 with Div_2 */
	SCG -> SCG_SPLLDIV = f_RegisterTemp_u32; /* PLL_DIV2 40MHZ */
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
	f_RegisterTemp_u32 |= (0u << 16); /* Because OSC provide 8MHZ x10 with PLL, so in oder to have 80MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 (BUS 40MHZ) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= (2u << 0); /* set 0010 for bits 3->0 to DIV 3 (Flash 26.67MHZ) */ 
	SCG -> SCG_RCCR = f_RegisterTemp_u32;
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Configure for Timer */
	/* Choose PCC_LPIT choose PLL_DIV2 */
	PCC -> PCC_LPIT &= ~(1u << 30); /* Disable Clock */
	PCC -> PCC_LPIT |= (6u << 24); /* Set 110 for bits 26->24 */
	PCC -> PCC_LPIT |= (1u << 30); /* Enable Clock */
	/* Configure Module Control Register (MCR) */
	LPIT -> LPIT_MCR |= (9u << 0); /* Set 1001 for bits 3->0 */
	
	/* Set Value for Timer 3 (value > 1) */
	LPIT -> LPIT_TVAL3 = 39999u; /* 1ms (DIV_2 = 40MHZ) */
	/* Configure Timer 0 Control Register (TCTRL3) */
	LPIT -> LPIT_TCTRL3 |= 0u;
	LPIT -> LPIT_TCTRL3 |= (0u << 24); /* Set 0000 for bits 27->24 to choose Trigger for Timer 3 */
	LPIT -> LPIT_TCTRL3 |= (1u << 23); /* Set 1 for bit 23 to choose Internal Source Trigger */
	LPIT -> LPIT_TCTRL3 |= (0u << 18); /* Set 0 for bit 18 to disable Reload value when get trigger signal (TROT) */
	LPIT -> LPIT_TCTRL3 |= (0u << 17); /* Set 0 for bit 17 to disable Timer Stop On Inetrrupt (TSOI) */ 
	LPIT -> LPIT_TCTRL3 |= (0u << 16); /* Set 0 for bit 16 to disable Timer Start On Trigger (TSOT) */ 
	LPIT -> LPIT_TCTRL3 |= (0u << 2); /* Set 00 for bits 3->2 to choose 32-bit Periodic Counter */ 
	LPIT -> LPIT_TCTRL3 |= (0u << 1); /* Set 0 for bit 1 to dont use Chain bit because just only use a timer channel */
	LPIT -> LPIT_TCTRL3 |= (1u << 0); /* Set 1 for bit 0 to enable Timer 3 */
	
	/* Configure Module Interrupt Enable Register (MIER) */
	LPIT -> LPIT_MIER |= (1u << 3); /* Set Enable Interrupt for Timer 3 ||| When occuring Interrupt -> Read Module Status Regiger (MSR) */
	/* Set Timer Enable Register (SETTEN) */
	LPIT -> LPIT_SETTEN |= (1u << 3); /* Set Enable for Timer 3 */
	
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Light status PIN15 of PORT_D */
		g_Timer0Ch3_u32 = 0;
		while (g_Timer0Ch3_u32 < 1500){} /* Ligh 1500ms */
		
		GPIOD -> GPIOD_PDOR |= (1u << 15); /* Off status PIN15 of PORT_D */
		g_Timer0Ch3_u32 = 0;
		while (g_Timer0Ch3_u32 < 500){} /* Off 500ms */
	}
}

/* ------------------------------------------------------------------------------------------------------- */
void BT06_Ex5(void){ /* TON 1000ms, TOFF 1000ms, Timer_CH0 mode dual 16 bits */
	volatile unsigned int f_RegisterTemp_u32;
	
	/* Set interrupt ID */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 16); /* ID 48 (Timer CH0) */
	
	/* wait LK = 0 to disable OSC Control Status Register */
	SCG -> SCG_SOSCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable OSC Control Status Register (Reset 0 for bit 0) */
	/* Don't need configure SCG_OSCCDIV Register (Not yet use) */
	/* After Disable OSC Control Status Register, then we can write data to SCG_SOSCCFG Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SOSCCFG Register */
	f_RegisterTemp_u32 |= (1u << 2); /* Set 1 for bit 2 to select trimming system (use for crystal) */
	f_RegisterTemp_u32 |= (2u << 4); /* Set 10 for bits 5->4 (Choose 8MHZ) */
	SCG -> SCG_SOSCCFG = f_RegisterTemp_u32; /* Configure source clock of OSC is 8MHZ */
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
	f_RegisterTemp_u32 |= (0u << 0); /* Reset bit 0 to Choose source Input PLL is System OSC */
	f_RegisterTemp_u32 |= (0u << 8); /* Set 000 for bits 10->8 to select Div_1 */
	f_RegisterTemp_u32 |= (4u << 16); /* Set 00100 for bits 20->16 to select Mul_20 */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ x 10 */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_RegisterTemp_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SPLL_DIV2 with Div_2 */
	SCG -> SCG_SPLLDIV = f_RegisterTemp_u32; /* PLL_DIV2 40MHZ */
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
	f_RegisterTemp_u32 |= (0u << 16); /* Because OSC provide 8MHZ x10 with PLL, so in oder to have 80MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 (BUS 40MHZ) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= (2u << 0); /* set 0010 for bits 3->0 to DIV 3 (Flash 26.67MHZ) */ 
	SCG -> SCG_RCCR = f_RegisterTemp_u32;
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Configure for Timer */
	/* Choose PCC_LPIT choose PLL_DIV2 */
	PCC -> PCC_LPIT &= ~(1u << 30); /* Disable Clock */
	PCC -> PCC_LPIT |= (6u << 24); /* Set 110 for bits 26->24 */
	PCC -> PCC_LPIT |= (1u << 30); /* Enable Clock */
	/* Configure Module Control Register (MCR) */
	LPIT -> LPIT_MCR |= (9u << 0); /* Set 1001 for bits 3->0 */
	
	/* Set Value for Timer 0 (value > 1) */
	LPIT -> LPIT_TVAL0 = (39999u << 0); /* 1ms (DIV_2 = 40MHZ) */
	/* Configure Timer 0 Control Register (TCTRL0) */
	LPIT -> LPIT_TCTRL0 |= 0u;
	LPIT -> LPIT_TCTRL0 |= (0u << 24); /* Set 0000 for bits 27->24 to choose Trigger for Timer 0 */
	LPIT -> LPIT_TCTRL0 |= (1u << 23); /* Set 1 for bit 23 to choose Internal Source Trigger */
	LPIT -> LPIT_TCTRL0 |= (0u << 18); /* Set 0 for bit 18 to disable Reload value when get trigger signal (TROT) */
	LPIT -> LPIT_TCTRL0 |= (0u << 17); /* Set 0 for bit 17 to disable Timer Stop On Inetrrupt (TSOI) */ 
	LPIT -> LPIT_TCTRL0 |= (0u << 16); /* Set 0 for bit 16 to disable Timer Start On Trigger (TSOT) */ 
	LPIT -> LPIT_TCTRL0 |= (1u << 2); /* Set 01 for bits 3->2 to choose 16-bit Dual Periodic Counter */ 
	LPIT -> LPIT_TCTRL0 |= (0u << 1); /* Set 0 for bit 1 to dont use Chain bit because just only use a timer channel */
	LPIT -> LPIT_TCTRL0 |= (1u << 0); /* Set 1 for bit 0 to enable Timer 0 */
	
	/* Configure Module Interrupt Enable Register (MIER) */
	LPIT -> LPIT_MIER |= (1u << 0); /* Set Enable Interrupt for Timer 0 ||| When occuring Interrupt -> Read Module Status Regiger (MSR) */
	/* Set Timer Enable Register (SETTEN) */
	LPIT -> LPIT_SETTEN |= (1u << 0); /* Set Enable for Timer 0 */
	
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR ^= (1u << 15); /* Toggle status PIN15 of PORT_D */
		g_Timer0Ch0_u32 = 0;
		while (g_Timer0Ch0_u32 < 1000){}
	}
}

/* ------------------------------------------------------------------------------------------------------- */
void BT06_Ex6(void){ /* TON 3000ms, TOFF 3000ms, Timer_CH1 mode dual 32 bits (chain) */
	volatile unsigned int f_RegisterTemp_u32;
	
	/* Set interrupt ID */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 17); /* ID 49 (Timer CH1) */
	
	/* wait LK = 0 to disable OSC Control Status Register */
	SCG -> SCG_SOSCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable OSC Control Status Register (Reset 0 for bit 0) */
	/* Don't need configure SCG_OSCCDIV Register (Not yet use) */
	/* After Disable OSC Control Status Register, then we can write data to SCG_SOSCCFG Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SOSCCFG Register */
	f_RegisterTemp_u32 |= (1u << 2); /* Set 1 for bit 2 to select trimming system (use for crystal) */
	f_RegisterTemp_u32 |= (2u << 4); /* Set 10 for bits 5->4 (Choose 8MHZ) */
	SCG -> SCG_SOSCCFG = f_RegisterTemp_u32; /* Configure source clock of OSC is 8MHZ */
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
	f_RegisterTemp_u32 |= (0u << 0); /* Reset bit 0 to Choose source Input PLL is System OSC */
	f_RegisterTemp_u32 |= (0u << 8); /* Set 000 for bits 10->8 to select Div_1 */
	f_RegisterTemp_u32 |= (4u << 16); /* Set 00100 for bits 20->16 to select Mul_20 */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ x 10 */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_RegisterTemp_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SPLL_DIV2 with Div_2 */
	SCG -> SCG_SPLLDIV = f_RegisterTemp_u32; /* PLL_DIV2 40MHZ */
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
	f_RegisterTemp_u32 |= (0u << 16); /* Because OSC provide 8MHZ x10 with PLL, so in oder to have 80MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 (BUS 40MHZ) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= (2u << 0); /* set 0010 for bits 3->0 to DIV 3 (Flash 26.67MHZ) */ 
	SCG -> SCG_RCCR = f_RegisterTemp_u32;
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Configure for Timer */
	/* Choose PCC_LPIT choose PLL_DIV2 */
	PCC -> PCC_LPIT &= ~(1u << 30); /* Disable Clock */
	PCC -> PCC_LPIT |= (6u << 24); /* Set 110 for bits 26->24 */
	PCC -> PCC_LPIT |= (1u << 30); /* Enable Clock */
	/* Configure Module Control Register (MCR) */
	LPIT -> LPIT_MCR |= (9u << 0); /* Set 1001 for bits 3->0 */
	
	/* Set Value for Timer 1 (value > 1) */
	LPIT -> LPIT_TVAL1 = 19999u; /* 1ms (DIV_2 = 40MHZ) */
	LPIT -> LPIT_TVAL0 = 1u; /* TVALCHn x (TVALCHn-1 + 1) */
	/* Configure Timer 0 Control Register (TCTRL1) */
	LPIT -> LPIT_TCTRL1 |= 0u;
	LPIT -> LPIT_TCTRL1 |= (0u << 24); /* Set 0000 for bits 27->24 to choose Trigger for Timer 1 */
	LPIT -> LPIT_TCTRL1 |= (1u << 23); /* Set 1 for bit 23 to choose Internal Source Trigger */
	LPIT -> LPIT_TCTRL1 |= (0u << 18); /* Set 0 for bit 18 to disable Reload value when get trigger signal (TROT) */
	LPIT -> LPIT_TCTRL1 |= (0u << 17); /* Set 0 for bit 17 to disable Timer Stop On Inetrrupt (TSOI) */ 
	LPIT -> LPIT_TCTRL1 |= (0u << 16); /* Set 0 for bit 16 to disable Timer Start On Trigger (TSOT) */ 
	LPIT -> LPIT_TCTRL1 |= (0u << 2); /* Set 00 for bits 3->2 to choose 32-bit Periodic Counter */ 
	LPIT -> LPIT_TCTRL1 |= (1u << 1); /* Set 1 for bit 1 to use Chain bit because just only use a timer channel */
	LPIT -> LPIT_TCTRL1 |= (1u << 0); /* Set 1 for bit 0 to enable Timer 1 */
	LPIT -> LPIT_TCTRL0 |= 0u;
	LPIT -> LPIT_TCTRL0 |= (1u << 0); /* Set 1 for bit 0 to enable Timer 0 */
	
	/* Configure Module Interrupt Enable Register (MIER) */
	LPIT -> LPIT_MIER |= (1u << 1); /* Set Enable Interrupt for Timer 1 ||| When occuring Interrupt -> Read Module Status Regiger (MSR) */
	/* Set Timer Enable Register (SETTEN) */
	LPIT -> LPIT_SETTEN |= (1u << 1); /* Set Enable for Timer 1 */
	
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Light status PIN15 of PORT_D */
		g_Timer0Ch1_u32 = 0;
		while (g_Timer0Ch1_u32 < 3000){} /* Ligh 3000ms */
		
		GPIOD -> GPIOD_PDOR |= (1u << 15); /* Off status PIN15 of PORT_D */
		g_Timer0Ch1_u32 = 0;
		while (g_Timer0Ch1_u32 < 3000){} /* Off 3000ms */
	}
}

/* ------------------------------------------------------------------------------------------------------- */
void Test_UART(void){
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
	f_RegisterTemp_u32 |= (8u << 16); /* Set 01000 for bits 20->16 to select Mul_24 */
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
	PCC -> PCC_PORTC &= ~(1u << 30); /* Disable */
	PORTC -> PORTC_PCR6 = 0u;
	PORTC -> PORTC_PCR6 |= (2u << 8);
	PORTC -> PORTC_PCR7 = 0u;
	PORTC -> PORTC_PCR7 |= (2u << 8);
	PCC -> PCC_PORTC |= (1u << 30); /* Enable */
	
	/* Setup LPUART */
	PCC -> PCC_LPUART1 |= (6u << 24); /* Choose PLL */
	PCC -> PCC_LPUART1 |= (1u << 30);
		
	/* Setup Baudrate */
	LPUART1 -> LPUART_CTRL &= ~(1u << 19); /* Disable Tx */
	LPUART1 -> LPUART_CTRL &= ~(1u << 18); /* Disable Rx */
	f_RegisterTemp_u32 = 500u; /* Choose SBR = 5000 (just 13bits 12-0) */
	f_RegisterTemp_u32 |= (9u << 24); /* Choose OSR = 10 by set 01001 for bits 28-24 */
	/* Choose 1 stop bit by configure bit 13 is 0 */
	LPUART1 -> LPUART_BAUD = f_RegisterTemp_u32;
	
	/* Setup Frame ( StartBit + 8 bits data + ParityBit + StopBit ) */
	/* configure bit 0 is 0 to choose parity even */
	/* configure bit 4 is 0 to choose data have 8 bits */
	LPUART1 -> LPUART_CTRL |= (1u << 1); /* configure bit 1 is 1 to enable parity bit */
	
	/* Commonly, We use polling for Tx and Interrupt for Rx */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 1); /* ID_33 LPUART_1 */
	//INTERUPT_SETPEND ->  NVIC_ISER1 |= (1u << 1); /* ID_33 LPUART_1 */
	//LPUART1 -> LPUART_CTRL |= (1u << 23); /* Enable TIE (Interrupt for Tx) */
	LPUART1 -> LPUART_CTRL |= (1u << 19); /* Enable Tx Data */
	LPUART1 -> LPUART_CTRL |= (1u << 21); /* Enable RIE (Interrupt for Rx) */
	LPUART1 -> LPUART_CTRL |= (1u << 18); /* Enable Rx Data */
	
	/* Set up SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0u; /* 0 is Disable SysTick Timer to set up SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Bit 2 is choose clock source (0 external / 1 system ) */ 
	SYSTICK -> SYSTICK_LOAD = 47999u; /* Set 48000 HZ to flag (<=> 1 milisecond because SysTick max is 48MHZ) */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to reset VAL = 0 */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Bit 1 is interrupt (0 Disable / 1 Enable) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0);	/* Enable SysTick */
	
	/**/
	PCC -> PCC_PORTD |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTD -> PORTD_PCR16 |= (1u << 8); /* set GPIO for PortD_PCR16 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTD -> PORTD_PCR16 &= ~(1u << 1) ; /* disabled pull-up/down for PortD_PCR16 */
	
	GPIOD -> GPIOD_PDDR |= (1u << 16); /* set (1) Output for PCR_16 (if 0 is Input) */
	
	while(1){
		/* Tx */
		//LPUART1 -> LPUART_CTRL |= (1u << 19); /* Enable Tx Data */
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'h';
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} /* wait bit 23 = 1 (data emty) */
		LPUART1 -> LPUART_DATA = 'a';
		//LPUART1 -> LPUART_CTRL &= ~(1u << 19); /* Enable Tx Data */
		
		
		g_UARTDataRx_u8 = 0;
		while (g_UARTDataRx_u8 == 0){}
		/* Rx */
		//while ( !((LPUART1 -> LPUART_STAT) & (1u << 21)) ){} /* wait bit 21 = 1 (data full) */
		//f_RegisterTemp_u32 = (LPUART1 -> LPUART_DATA);	
		/* Process Data */
		//f_RegisterTemp_u32 = f_RegisterTemp_u32 << 25;
		//f_RegisterTemp_u32 = f_RegisterTemp_u32 >> 25;
		/*if (	g_UARTDataRx_u8 == 'a'){
			while (1){
				g_SysTickTimer_u32 = 0;
				while (g_SysTickTimer_u32 < 500){}
				GPIOD -> GPIOD_PDOR ^= (1u << 16); 
			}
		}*/
		GPIOD -> GPIOD_PDOR ^= (1u << 16); 
	}
}

void Test_SPI(void){
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
	f_RegisterTemp_u32 |= (20u << 16); /* Set 10100 for bits 20->16 to select Mul_36 */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ x 9 */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register (Not yet use) */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_RegisterTemp_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SPLL_DIV2 with Div_2 */
	SCG -> SCG_SPLLDIV = f_RegisterTemp_u32; /* 36 MHZ */
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
	f_RegisterTemp_u32 |= (0u << 16); /* Because OSC provide 8MHZ x 9 with PLL, so in oder to have 72MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 (we need 36MHZ) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= (3u << 0); /* set 0011 for bits 3->0 to DIV 4 */ 
	SCG -> SCG_RCCR = f_RegisterTemp_u32; /* CORE 72MHZ, BUS 36MHZ, FLASH 18MHZ */
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
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
	/* set 0 for bits 7->0 to choose SCKDIV = (0 + 2) "+2" is defaul auto add */
	f_RegisterTemp_u32 = 0u;
	/* CPOL = 0 and CPHA = 0 (bits 31 and 30) */
	f_RegisterTemp_u32 |= (1u << 27); /* 001 for bits 29->27 (PRESCALE) */ /* => 36 / (SCK * Prescale) = 9 MHZ (<10MHZ is ok) */
	f_RegisterTemp_u32 |= (2u << 24); /* 10 for bits 25->24 (PCS) */
	/* LSBF = 0 for MSB first (bit 24) */
	f_RegisterTemp_u32 |= 15u; /* bits 11->0 for FRAME_SIZE (auto +1) */
	LPSPI0 -> LPSPI_TCR = f_RegisterTemp_u32;
	
	f_RegisterTemp_u32 = 3u; /* Set Rx_water = 3 (bits 1->0) */ 
	f_RegisterTemp_u32 |= (3u << 16); /* Set Tx_water = 3 (bits 17->16) */ 
	LPSPI0 -> LPSPI_FCR = f_RegisterTemp_u32;
	
	LPSPI0 -> LPSPI_CR = 0u; /* Disable LPSPI_Module */
	LPSPI0 -> LPSPI_CR |= (1u << 3); /* Set 1 for bit 3 (DBGEN) */
	LPSPI0 -> LPSPI_CFGR1 |= (1u << 3); /* Set NoStall = 1 (bit 3) */
	LPSPI0 -> LPSPI_CFGR1 |= (1u << 0); /* Set 1 for bit 0 to choose device is Master */
	LPSPI0 -> LPSPI_CR |= (1u << 0); /* Enable LPSPI_Module (Bit 0 = 1) */
	
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xFCF1; /* Turn on ShutDown_Mode */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xFBF7; /* Set Scan_Limit is full led (8 led) */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xFAFF; /* Set Intensity is max light */
		
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xF16D; /* Display 2 for led 0 */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xF26D; /* Display 2 for led 1 */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xF36D; /* Display 2 for led 2 */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xF46D; /* Display 2 for led 3 */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xF56D; /* Display 2 for led 4 */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xF66D; /* Display 2 for led 5 */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xF76D; /* Display 2 for led 6 */
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xF86D; /* Display 2 for led 7 */
	
	while ( !((LPSPI0 -> LPSPI_SR) & (1u << 0)) ){} /* wait TDF = 1 to send data */
	LPSPI0 -> LPSPI_TDR = 0xFFF0; /* Display mode is normal */
		
	while(1){}
}
