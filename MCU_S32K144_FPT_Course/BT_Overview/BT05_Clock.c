#include "BT05_Clock.h"
#include "Setup_Port_S32K144.h"


void BT05_Ex1(void){ /* Use Crystal 8MHZ create CORE Clock 80MHZ, BUS Clock 40MHZ */
	volatile unsigned int f_TempSCG_u32;
	volatile unsigned int f_TempPLL_u32;
	volatile unsigned int f_TempOSC_u32;
	
	/* wait LK = 0 to disable OSC Control Status Register */
	SCG -> SCG_SOSCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable OSC Control Status Register (Reset 0 for bit 0) */
	/* After Disable OSC Control Status Register, then we can write data to SCG_OSCCDIV Register (Not yet use) */
	f_TempOSC_u32 = 0; /* or read from SCG_SOSCDIV Register */
	f_TempOSC_u32 |= (2u << 0); /* set 010 for bits 2->0 to using SOSC_DIV2 with Div_2 (= BUS) to easy synchronized math */
	f_TempOSC_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SOSC_DIV1 with Div_2 (= BUS) to easy synchronized math */
	SCG -> SCG_SOSCDIV = f_TempOSC_u32; /* SCG Register just only write once 32bits */
	/* After Disable OSC Control Status Register, then we can write data to SCG_SOSCCFG Register */
	f_TempOSC_u32 = 0; /* or read from SCG_SOSCCFG Register */
	f_TempOSC_u32 |= (1u << 2); /* Set 1 for bit 2 to select trimming system (use for crystal) */
	f_TempOSC_u32 |= (2u << 4); /* Set 10 for bits 5->4 (Choose 8MHZ) */
	SCG -> SCG_SOSCCFG = f_TempOSC_u32; /* Configure source clock of OSC is 8MHZ */
	/* Return to Enable OSC Control Status Register */
	f_TempOSC_u32 = 1u;
	f_TempOSC_u32 |= (1u << 23);
	SCG -> SCG_SOSCCSR = f_TempOSC_u32;
	while ( !((SCG -> SCG_SOSCCSR) & (1u << 24)) ){} /* Wait OSC valid */
	
	/* wait LK = 0 to disable PLL Control Status Register */
	SCG -> SCG_SPLLCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SPLLCSR = 0u; /* Disable PLL Control Status Register (Reset 0 for bit 0) */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLDIV Register (Not yet use) */
	f_TempPLL_u32 = 0; /* or read from SCG_SPLLDIV Register */
	f_TempPLL_u32 |= (2u << 0); /* set 010 for bits 2->0 to using SPLL_DIV1 with Div_2 (= BUS) to easy synchronized math */
	f_TempPLL_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SPLL_DIV2 with Div_2 (= BUS) to easy synchronized math */
	SCG -> SCG_SPLLDIV = f_TempPLL_u32; /* SCG Register just only write once 32bits */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLCFG Register */
	f_TempPLL_u32 = 0; /* or read from SCG_SPLLCFG Register */
	f_TempPLL_u32 &= ~(1u << 0); /* Reset bit 0 to Choose source Input PLL is System OSC */
	f_TempPLL_u32 &= ~(1u << 8); /* Set 000 for bits 10->8 to select Div_1 */
	f_TempPLL_u32 |= (4u << 16); /* Set 00100 for bits 20->16 to select Mul_20 */
	SCG -> SCG_SPLLCFG = f_TempPLL_u32; /* Configure source clock of OSC 8MHZ x 10 */
	/* Return to Enable PLL Control Status Register */
	f_TempPLL_u32 = 1u;
	f_TempPLL_u32 |= (1u << 23);
	SCG -> SCG_SPLLCSR = f_TempPLL_u32;
	while ( !((SCG -> SCG_SPLLCSR) & (1u << 24)) ){} /* Wait PLL valid */
	
	/* Setup for RUN Mode */
	/* Choose SCG */
	f_TempSCG_u32 = 0; /* or read from SCG_RCCR Register */
	f_TempSCG_u32 |= (6u << 24); /* set 0110 for bits 27->24 for choosing System_PLL */
	/* CORE and System (MAX = 80MHZ for RUN Mode) */
	f_TempSCG_u32 &= ~(1u << 16); /* Because OSC provide 8MHZ x10 with PLL, so in oder to have 80MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_TempSCG_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 (we need 40MHZ) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_TempSCG_u32 |= (3u << 0); /* set 0011 for bits 3->0 to DIV 4 */ 
	/* Write f_TempSCG_u32 to SCG_RCCR */
	SCG -> SCG_RCCR = f_TempSCG_u32; /* SCG Register just only write once 32bits */
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Setup SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0; /* Disable SysTick Timer */
	SYSTICK -> SYSTICK_LOAD = 79999u; /* ~1ms because core clock is configured 80MHZ above */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to Reset current value */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Choose Clock Soure is Core Clock (Internal) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Using Interrupt for SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0); /* Enable SysTick Timer */
	
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR ^= (1u << 15); /* Toggle status PIN15 of PORT_D */
		g_SysTickTimer_u32 = 0;
		while (g_SysTickTimer_u32 < 500){}
	}
}

void BT05_Ex2(void){ /* Use Crystal 8MHZ create CORE Clock 8MHZ, BUS Clock 4MHZ */
	unsigned int f_RegisterTemp_u32;
	
	/* Configure Clock */
	/* Disable SOSCCSR */
	SCG -> SCG_SOSCCSR = 0u; /* Disable SCG_SOSCCSR (Set 0 for bit 23 LK to write) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable SCG_SOSCCSR (Set 0 for bit 0 Enable to configure) */
	/* Dont need configure SOSCDIV because not yet use */
	/* Configure SOSCCFG */
	f_RegisterTemp_u32 = 0u;
	f_RegisterTemp_u32 |= (1u << 2); /* Choose Crystal */
	f_RegisterTemp_u32 |= (2u << 4); /* Choose range 4-8MHZ */
	SCG -> SCG_SOSCCFG = f_RegisterTemp_u32;
	/* Enable SOSCCSR again */
	f_RegisterTemp_u32 = 1u;
	f_RegisterTemp_u32 |= (1u << 23);
	SCG -> SCG_SOSCCSR = f_RegisterTemp_u32;
	while ( !((SCG -> SCG_SOSCCSR) & (1u << 24)) ){}
	
	/* Configure RUN mode */
	f_RegisterTemp_u32 = 0u;
	f_RegisterTemp_u32 |= (1u << 24); /* Choose OSC */
	f_RegisterTemp_u32 |= (0u << 16); /* Core Div 1 (8MHZ) */
	f_RegisterTemp_u32 |= (1u << 4); /* Bus Div 2 (4MHZ) */
	f_RegisterTemp_u32 |= (1u << 0); /* Flash Div 2 (4MHZ) */
	SCG -> SCG_RCCR = f_RegisterTemp_u32;
	while ((SCG -> SCG_RCCR) != (SCG -> SCG_CSR)){}
	
	/* Setup SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0; /* Disable SysTick Timer */
	SYSTICK -> SYSTICK_LOAD = 7999u; /* ~1ms because core clock is configured 8MHZ above */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to Reset current value */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Choose Clock Soure is Core Clock (Internal) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Using Interrupt for SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0); /* Enable SysTick Timer */
		
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR ^= (1u << 15); /* Toggle status PIN15 of PORT_D */
		g_SysTickTimer_u32 = 0;
		while (g_SysTickTimer_u32 < 500){}
	}
}

void BT05_Ex3(void){ /* Use FIRC 48MHZ create CORE Clock 24MHZ */
	unsigned int f_RegisterTemp_u32;
	
	/* Because default is FIRC 48MHZ RUN_mode -> just configure FIRC_CORE_BUS_FLASH */
	/* Configure RUN_Mode */
	f_RegisterTemp_u32 = 0u;
	f_RegisterTemp_u32 |= (3u << 24); /* Choose FIRC */
	f_RegisterTemp_u32 |= (1u << 16); /* Core Div 2 (24MHZ) */
	f_RegisterTemp_u32 |= (0u << 4); /* Bus Div 1 (24MHZ) */
	f_RegisterTemp_u32 |= (1u << 0); /* Flash Div 2 (12MHZ) */
	SCG -> SCG_RCCR = f_RegisterTemp_u32;
	while ((SCG -> SCG_RCCR) != (SCG -> SCG_CSR)){}
	
	/* Setup SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0; /* Disable SysTick Timer */
	SYSTICK -> SYSTICK_LOAD = 23999u; /* ~1ms because core clock is configured 8MHZ above */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to Reset current value */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Choose Clock Soure is Core Clock (Internal) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Using Interrupt for SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0); /* Enable SysTick Timer */
		
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR ^= (1u << 15); /* Toggle status PIN15 of PORT_D */
		g_SysTickTimer_u32 = 0;
		while (g_SysTickTimer_u32 < 500){}
	}
}

void BT05_Ex4(void){ /* Use Crystal 8MHZ create CORE Clock 48MHZ, BUS Clock 16MHZ */
	unsigned int f_RegisterTemp_u32;
	
	/* wait LK = 0 to disable OSC Control Status Register */
	SCG -> SCG_SOSCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SOSCCSR = 0u; /* Disable OSC Control Status Register (Reset 0 for bit 0) */
	/* Dont need configure SCG_OSCCDIV Register (Not yet use) */
	/* After Disable OSC Control Status Register, then we can write data to SCG_SOSCCFG Register */
	f_RegisterTemp_u32 = 0u; /* or read from SCG_SOSCCFG Register */
	f_RegisterTemp_u32 |= (1u << 2); /* Set 1 for bit 2 to select trimming system (use for crystal) */
	f_RegisterTemp_u32 |= (2u << 4); /* Set 10 for bits 5->4 (Choose 4-8MHZ) */
	SCG -> SCG_SOSCCFG = f_RegisterTemp_u32; /* Configure source clock of OSC is 8MHZ */
	/* Return to Enable OSC Control Status Register */
	f_RegisterTemp_u32 = 1u;
	f_RegisterTemp_u32 |= (1u << 23);
	SCG -> SCG_SOSCCSR = f_RegisterTemp_u32;
	while ( !((SCG -> SCG_SOSCCSR) & (1u << 24)) ){} /* Wait OSC valid */
	
	/* wait LK = 0 to disable PLL Control Status Register */
	SCG -> SCG_SPLLCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SPLLCSR = 0u; /* Disable PLL Control Status Register (Reset 0 for bit 0) */
	/* Dont need configure SCG_SPLLDIV Register (Not yet use) */
	/* After Disable PLL Control Status Register, then we can write data to SCG_SPLLCFG Register */
	f_RegisterTemp_u32 = 0; /* or read from SCG_SPLLCFG Register */
	f_RegisterTemp_u32 &= ~(1u << 0); /* Reset bit 0 to Choose source Input PLL is System OSC */
	f_RegisterTemp_u32 |= (1u << 8); /* Set 001 for bits 10->8 to select Div_2 */
	f_RegisterTemp_u32 |= (8u << 16); /* Set 01000 for bits 20->16 to select Mul_24 */
	SCG -> SCG_SPLLCFG = f_RegisterTemp_u32; /* Configure source clock of OSC 8MHZ / 2 * 24 / 2 (48MHZ) */
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
	f_RegisterTemp_u32 |= (0u << 16); /* 0000 for bits 19->16 (Core Div 1) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_RegisterTemp_u32 |= (2u << 4); /* set 0010 for bits 7->4 (Bus Div 3) */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_RegisterTemp_u32 |= (3u << 0); /* set 0011 for bits 3->0 (Flash Div 4) */ 
	/* Write f_TempSCG_u32 to SCG_RCCR */
	SCG -> SCG_RCCR = f_RegisterTemp_u32; /* SCG Register just only write once 32bits */
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Setup SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0; /* Disable SysTick Timer */
	SYSTICK -> SYSTICK_LOAD = 47999u; /* ~1ms because core clock is configured 80MHZ above */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to Reset current value */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Choose Clock Soure is Core Clock (Internal) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Using Interrupt for SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0); /* Enable SysTick Timer */
	
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR ^= (1u << 15); /* Toggle status PIN15 of PORT_D */
		g_SysTickTimer_u32 = 0;
		while (g_SysTickTimer_u32 < 500){}
	}
}

void BT05_Ex5(void){ /* Use SIRC 8MHZ create CORE Clock 8MHZ */
	volatile unsigned int f_TempSCG_u32;
	volatile unsigned int f_TempIRC_u32;
	
	/* wait LK = 0 to disable IRC Control Status Register */
	SCG -> SCG_SIRCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SIRCCSR = 0u; /* Disable IRC Control Status Register (Reset 0 for bit 0) */
	/* Dont need configure SCG_SIRCDIV Register (Not yet use) */
	/* After Disable IRC Control Status Register, then we can write data to SCG_SIRCCFG Register */
	SCG -> SCG_SIRCCFG = 1u; /* Configure source clock of Slow_IRC is 8MHZ */
	/* Return to Enable IRC Control Status Register */
	f_TempIRC_u32 = 1u;
	f_TempIRC_u32 |= (1u << 23);
	SCG -> SCG_SIRCCSR = f_TempIRC_u32;
	while (((SCG -> SCG_SIRCCSR) & (1u << 24)) == 0){} /* Wait Slow_IRC valid */
	
	/* Setup for RUN Mode */
	/* Choose SCG */
	f_TempSCG_u32 = 0; /* or read from SCG_RCCR Register */
	f_TempSCG_u32 |= (2u << 24); /* set 0010 for bits 27->24 for choosing Slow_IRC */
	/* CORE and System (MAX = 80MHZ for RUN Mode) */
	f_TempSCG_u32 |= (1u << 16); /* Because SlowIRC provide 8MHZ, so in oder to have 8MHZ, we use DIVCORE 1 (0000 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_TempSCG_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_TempSCG_u32 |= (1u << 0); /* set 0001 for bits 3->0 to DIV 2 */ 
	/* Write f_TempSCG_u32 to SCG_RCCR */
	SCG -> SCG_RCCR = f_TempSCG_u32; /* SCG Register just only write once 32bits */
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Setup SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0; /* Disable SysTick Timer */
	SYSTICK -> SYSTICK_LOAD = 7999u; /* ~1ms because core clock is configured 8MHZ above */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to Reset current value */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Choose Clock Soure is Core Clock (Internal) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Using Interrupt for SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0); /* Enable SysTick Timer */
	
	/* Setup Output for PORT_D */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set 001 for bits 10->8 to choose mode GPIO for PIN_15 of PORT_D */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Disable Pullup/down */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 of PORTD is Output */
	
	/* Initial Status */
	GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Start up PIN_15 PORT_D is Light */
	
	while(1){
		GPIOD -> GPIOD_PDOR ^= (1u << 15); /* Toggle status PIN15 of PORT_D */
		g_SysTickTimer_u32 = 0;
		while (g_SysTickTimer_u32 < 1000){}
	}
}

void Test_Timer(void){
	volatile unsigned int f_Temp_u32;
	/* Set interrupt ID */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 16); /* ID 48 */
	
	/* Configure for IRC_Slow */
	/* Disable SCG_SIRCCSR */
	SCG -> SCG_SIRCCSR = 0u; /* Set 0 for bit 23 LK to interract with SCG_SIRCCSR */
	SCG -> SCG_SIRCCSR = 0u; /* Set 0 for bit 0 to Disable SCG_SIRCCSR */
	/* After Disable SCG_SIRCCSR, Interracting with SCG_SIRCDIV */
	f_Temp_u32 = 0;
	f_Temp_u32 |= (2u << 8); /* Configure 010 for bits 10->8 (choose DIV 2) */
	SCG -> SCG_SIRCDIV = f_Temp_u32;
	/* After Disable SCG_SIRCCSR, Interracting with SCG_SIRCCFG */
	SCG -> SCG_SIRCCFG = 1u; /* Set 1 for bit 0 (Choose 8MHZ) */
	/* Enable SCG_SIRCCSR return */
	SCG -> SCG_SIRCCSR = 1u; /* Set 1 for bit 0 to Enable SCG_SIRCCSR */
	f_Temp_u32 = SCG -> SCG_SIRCCSR;
	f_Temp_u32 |= (1u << 23); /* Set 1 for bit 23 LK to lock SCG_SIRCCSR */
	SCG -> SCG_SIRCCSR = f_Temp_u32;
	while (!((SCG -> SCG_SIRCCSR) & (1u << 24))){} /* Wait SCG -> SCG_SIRCCSR register valid */
	
	/* Configure IRC_SLOW for RUN Mode */
	f_Temp_u32 = 0;
	f_Temp_u32 |= (2u << 24); /* Choose IRC_Slow */
	f_Temp_u32 |= (1u << 4); /* Set DIV 2 for BUS */
	f_Temp_u32 |= (1u << 0); /* Set DIV 2 for FLASH */
	SCG -> SCG_RCCR = f_Temp_u32;
	while ((SCG -> SCG_RCCR) != (SCG -> SCG_CSR)) /* Wait */
	
	/* Configure for Timer */
	/* Choose PCC_LPIT choose SIRC_DIV2 */
	PCC -> PCC_LPIT &= ~(1u << 30); /* Disable Clock */
	PCC -> PCC_LPIT |= (2u << 24); /* Set 010 for bits 26->24 */
	PCC -> PCC_LPIT |= (1u << 30); /* Enable Clock */
	/* Configure Module Control Register (MCR) */
	LPIT -> LPIT_MCR |= (9u << 0); /* Set 1001 for bits 3->0 */
	
	/* Set Value for Timer 0 (value > 1) */
	LPIT -> LPIT_TVAL0 = 3999u; /* 1ms (DIV_2 = 4MHZ) */
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
	LPIT -> LPIT_SETTEN |= (1u <<0); /* Set Enable for Time 0 */
	
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

