#include "BT04_SysTickTimer.h"
#include "Setup_Port_S32K144.h"


void BT04_Ex1(void){ /* Flash Led PTD16 delay 500ms (not use interrupt of SysTick) */
	/* Set up */
	Setup_PortPin(PORTD, PIN_16, OUTPUT);
	
	while(1){
		Toggle_PortPin(PORTD, PIN_16);
		Delay_SysTick(500);
	}
}

void BT04_Ex2(void){ /* Flash Led PTD16 delay 500ms (use interrupt of SysTick) */
	/* Set up */
	Setup_PortPin(PORTD, PIN_16, OUTPUT);
	
	/* Set up SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0u; /* 0 is Disable SysTick Timer to set up SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Bit 2 is choose clock source (0 external / 1 system ) */ 
	SYSTICK -> SYSTICK_LOAD = 47999u; /* Set 48000 HZ to flag (<=> 1 milisecond because SysTick max is 48MHZ) */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to reset VAL = 0 */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Bit 1 is interrupt (0 Disable / 1 Enable) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0);	/* Enable SysTick */
	
	g_SysTickTimer_u32 = 500; /* Delay 500ms */
	while(1){
		g_SysTickTimer_u32 = 0;
		while (g_SysTickTimer_u32 < 500){}
		Toggle_PortPin(PORTD, PIN_16);
	}
}

void BT04_Ex3(void){ /* PTD16 ligh 2s, PTD16 off 1s (not use interrupt of SysTick) */
	/* Set up */
	Setup_PortPin(PORTD, PIN_16, OUTPUT);
	
	while(1){
		Set_PortPin(PORTD, PIN_16, HIGH);
		Delay_SysTick(1000);
		Set_PortPin(PORTD, PIN_16, LOW);
		Delay_SysTick(2000);
	}
}

void BT04_Ex4(void){ /* PTD16 ligh 2s, PTD16 off 1s (use interrupt of SysTick) */
	/* Set up */
	Setup_PortPin(PORTD, PIN_16, OUTPUT);
	
	/* Set up SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0u; /* 0 is Disable SysTick Timer to set up SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Bit 2 is choose clock source (0 external / 1 system ) */ 
	SYSTICK -> SYSTICK_LOAD = 47999u; /* Set 48000 HZ to flag (<=> 1 milisecond because SysTick max is 48MHZ) */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to reset VAL = 0 */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Bit 1 is interrupt (0 Disable / 1 Enable) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0);	/* Enable SysTick */
	
	while(1){
		g_SysTickTimer_u32 = 0;
		while (g_SysTickTimer_u32 < 2000){}
		Set_PortPin(PORTD, PIN_16, HIGH);
			
		g_SysTickTimer_u32 = 0;
		while (g_SysTickTimer_u32 < 1000){}
		Set_PortPin(PORTD, PIN_16, LOW);
	}
}

void BT04_Ex5(void){ /* Math real time of function for (i=0; i<250; i++) */
	volatile unsigned int f_NowDec_u32 = 0;
	volatile unsigned int f_NowCur1_u32 = 0;
	volatile unsigned int f_NowCur2_u32 = 0;
	volatile unsigned int f_NowCurTotal_u32 = 0;
	volatile unsigned int i = 0;
	
	f_NowCurTotal_u32 = 0;
	g_SysTickTimer_u32 = 0;
	
	/* Set up SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0u; /* 0 is Disable SysTick Timer to set up SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Bit 2 is choose clock source (0 external / 1 system ) */ 
	SYSTICK -> SYSTICK_LOAD = 16777215u; /* Set 2^24-1 HZ to flag (max) */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to reset VAL = 0 */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Bit 1 is interrupt (0 Disable / 1 Enable) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0);	/* Enable SysTick */
	f_NowCur1_u32 = (SYSTICK -> SYSTICK_VAL);
	for (i=0; i<250; i++){}
	f_NowCur2_u32 = (SYSTICK -> SYSTICK_VAL); 
	f_NowDec_u32 += g_SysTickTimer_u32; /* f_NowDec_u32 is period 2^24-1 */
	f_NowCurTotal_u32 = f_NowCur1_u32 - f_NowCur2_u32; /* measure: 0xFFFFFA - 0xFFF238 = 4017 <=> 4017/47999 = 0.089 milisecond */
	f_NowCurTotal_u32++; /* To avoid warning "not used" */
}

void ConfigureClockSoure_SlowIRC(void){ /* Configure SlowIRC use RUN, Core and Sys CLK is 4MHZ */
	volatile unsigned int f_TempSCG_u32;
	volatile unsigned int f_TempIRC_u32;
	
	/* wait LK = 0 to disable IRC Control Status Register */
	SCG -> SCG_SIRCCSR = 0u; /* Set 0 in Bit 23 to unclock Control Status Register (When LK bit 23 is 1, just can write this bit to 0) */
	SCG -> SCG_SIRCCSR = 0u; /* Disable IRC Control Status Register (Reset 0 for bit 0) */
	/* After Disable IRC Control Status Register, then we can write data to SCG_SIRCDIV Register (Not yet use) */
	f_TempIRC_u32 = 0; /* or read from SCG_SIRCDIV Register */
	f_TempIRC_u32 |= (2u << 0); /* set 010 for bits 2->0 to using SIRC_DIV1 with Div_2 (= BUS) to easy synchronized math */
	f_TempIRC_u32 |= (2u << 8); /* set 010 for bits 10->8 to using SIRC_DIV2 with Div_2 (= BUS) to easy synchronized math */
	SCG -> SCG_SIRCDIV = f_TempIRC_u32; /* SCG Register just only write once 32bits */
	/* After Disable IRC Control Status Register, then we can write data to SCG_SIRCCFG Register */
	SCG -> SCG_SIRCCFG = 1u; /* Configure source clock of Slow_IRC is 8MHZ */
	/* Return to Enable IRC Control Status Register */
	f_TempIRC_u32 = 5u;
	f_TempIRC_u32 |= (1u << 23);
	SCG -> SCG_SIRCCSR = f_TempIRC_u32;
	while (((SCG -> SCG_SIRCCSR) & (1u << 24)) == 0){} /* Wait Slow_IRC valid */
	
	/* Setup for RUN Mode */
	/* Choose SCG */
	f_TempSCG_u32 = 0; /* or read from SCG_RCCR Register */
	f_TempSCG_u32 |= (2u << 24); /* set 0010 for bits 27->24 for choosing Slow_IRC */
	/* CORE and System (MAX = 80MHZ for RUN Mode) */
	f_TempSCG_u32 |= (1u << 16); /* Because SlowIRC provide 8MHZ, so in oder to have 4MHZ, we use DIVCORE 2 (0001 for bits 19->16) */
	/* BUS in RUN Mode has MAX = 48MHZ (BUS<=CORE and DIV of Interger with CORE and Maximum 48MHZ) */
	f_TempSCG_u32 |= (1u << 4); /* set 0001 for bits 7->4 to DIV 2 */
	/* FLASH in RUN Mode has MAX = 26,67 MHZ (FLASH<=CORE and DIV of Interger with CORE and Maximum 26.67MHZ) */
	f_TempSCG_u32 |= (1u << 0); /* set 0001 for bits 3->0 to DIV 2 */ 
	/* Write f_TempSCG_u32 to SCG_RCCR */
	SCG -> SCG_RCCR = f_TempSCG_u32; /* SCG Register just only write once 32bits */
	while ((SCG -> SCG_CSR) != (SCG -> SCG_RCCR)){} /* Wait system is ready */
	
	/* Setup SysTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0; /* Disable SysTick Timer */
	SYSTICK -> SYSTICK_LOAD = 4000u; /* ~1ms because core clock is configured 8MHZ above */
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
