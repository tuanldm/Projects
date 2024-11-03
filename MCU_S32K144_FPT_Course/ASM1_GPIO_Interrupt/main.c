#include "GPIO_Type.h"
#include "INTERUPT_TYPE.h"
#include "PCC_Type.h"
#include "PORT_Type.h"
#include "SYSTICK_Type.h"

void SysTick_Handler(void);
void PORTA_IRQHandler(void);
void PORTB_IRQHandler(void);

/* Variable is used */
static volatile unsigned int g_ClockSysTick_u32 = 0;
static volatile unsigned char g_BT1_u8 = 0; /* 0: Stop (Dislay current light) //  1: period up light (Green -> Red -> Blue) */
static volatile unsigned char g_BT2_u8 = 0; /* 0: off  //  1: on */
static volatile unsigned char g_State_u8 = 3; /* 1 -> 2 -> 3 corresponding Blue -> Red -> Green */


int main(void){
	/* Setup Priority Interrupt */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 27); /* Set Interrupt for PORT_A */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 28); /* Set Interrupt for PORT_B */
	
	
	/* Enable Interrupt SystemTick Timer */
	SYSTICK -> SYSTICK_CTRL = 0; /* Disable SysTick */
	SYSTICK -> SYSTICK_LOAD = 47999u; /* Setup a period is 1ms */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value != 0 to Reset Current Clock SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Using source core clock */
	SYSTICK -> SYSTICK_CTRL |= (1u << 1); /* Enable Interrupt SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0); /* Enable SysTick Timer */
	
	/* Configue PIN_3 PORTA is Input using Interrupt */
	PCC -> PCC_PORTA |= (1u << 30); /* Enable Clock for PORT_A */
	PORTA -> PORTA_PCR3 |= (10u << 16); /* Set 1010 for bits 19->16 (Interrupt Edge-Falling) */
	PORTA -> PORTA_PCR3 |= (1u << 8); /* Set mux 001 for bits 10->8 (GPIO mode) */
	PORTA -> PORTA_PCR3 |= (1u << 1); /* Set Enable Internal Resistor */
	PORTA -> PORTA_PCR3 &= ~(1u << 0); /* Select Pull-down Internal Resistor */
	GPIOA -> GPIOA_PDDR &= ~(1u << 3); /* Set PIN_3 PORT_A is Input */
	
	/* Configue PIN_8 PORTB is Input using Interrupt */
	PCC -> PCC_PORTB |= (1u << 30); /* Enable Clock for PORT_B */
	PORTB -> PORTB_PCR8 |= (10u << 16); /* Set 1010 for bits 19->16 (Interrupt Edge-Falling) */
	PORTB -> PORTB_PCR8 |= (1u << 8); /* Set mux 001 for bits 10->8 (GPIO mode) */
	PORTB -> PORTB_PCR8 |= (1u << 1); /* Set Enable Internal Resistor */
	PORTB -> PORTB_PCR8 &= ~(1u << 0); /* Select Pull-down Internal Resistor */
	GPIOB -> GPIOB_PDDR &= ~(1u << 8); /* Set PIN_8 PORT_B is Input */
	
	/* Configue PIN_0 PORTD is Output */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable Clock for PORT_D */
	PORTD -> PORTD_PCR0 |= (1u << 8); /* Set mux 001 for bits 10->8 (GPIO mode) */
	PORTD -> PORTD_PCR0 &= ~(1u << 1); /* Set Disable Internal Resistor */
	GPIOD -> GPIOD_PDDR |= (1u << 0); /* Set PIN_0 PORT_D is Output */
	
	/* Configue PIN_15 PORTD is Output */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable Clock for PORT_D */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* Set mux 001 for bits 10->8 (GPIO mode) */
	PORTD -> PORTD_PCR15 &= ~(1u << 1); /* Set Disable Internal Resistor */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* Set PIN_15 PORT_D is Output */
	
	/* Configue PIN_16 PORTD is Output */
	PCC -> PCC_PORTD |= (1u << 30); /* Enable Clock for PORT_D */
	PORTD -> PORTD_PCR16 |= (1u << 8); /* Set mux 001 for bits 10->8 (GPIO mode) */
	PORTD -> PORTD_PCR16 &= ~(1u << 1); /* Set Disable Internal Resistor */
	GPIOD -> GPIOD_PDDR |= (1u << 16); /* Set PIN_16 PORT_D is Output */
	
	
	/* Step up Initial State */
	GPIOD -> GPIOD_PDOR |= (1u << 0); /* Light Blue Off */
	GPIOD -> GPIOD_PDOR |= (1u << 15); /* Light Red Off */
	GPIOD -> GPIOD_PDOR &= ~(1u << 16); /* Light Green Light */
	g_BT1_u8 = 0;
	g_BT2_u8 = 0;
	g_State_u8 = 3; /*Green On*/
	
	while(1){
		if (g_State_u8 == 1){ /* Blue On */
			GPIOD -> GPIOD_PDOR &= ~(1u << 0); /* Light Blue On 	*/
			GPIOD -> GPIOD_PDOR |= (1u << 15); /* Light Red Off 	*/
			GPIOD -> GPIOD_PDOR |= (1u << 16); /* Light Green Off */
		}
		else if (g_State_u8 == 2){ /* Red On */
			GPIOD -> GPIOD_PDOR |= (1u << 0); 	/* Light Blue Off  */
			GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Light Red On 	 */
			GPIOD -> GPIOD_PDOR |= (1u << 16); 	/* Light Green Off */
		}
		else if (g_State_u8 == 3){ /* Green On */
			GPIOD -> GPIOD_PDOR |= (1u << 0); 	/* Light Blue Off */
			GPIOD -> GPIOD_PDOR |= (1u << 15); 	/* Light Red Off 	*/
			GPIOD -> GPIOD_PDOR &= ~(1u << 16); /* Light Green On */
		}
		if (g_BT1_u8 != 0){ /* g_BT1_u8 = 1 then run with light period 500ms */
			/*Light within 500ms*/
			g_ClockSysTick_u32 = 0;
			while(g_ClockSysTick_u32 < 1000){
				if (g_BT1_u8 == 0)
					break;
			}
			
			/* Change State Light */
			if ((g_BT2_u8 == 0) && (g_BT1_u8 != 0)) /* g_BT2_u8 = 0 then Green->Red->Blue */
				g_State_u8--;
			else if ((g_BT2_u8 == 1) && (g_BT1_u8 != 0)) /* g_BT2_u8 = 1 then Blue->Red->Green */
				g_State_u8++;
			
			/* Limit g_State_u8 in zone 1->3 */
			if (g_State_u8 > 3)
				g_State_u8 = 1;
			if (g_State_u8 < 1)
				g_State_u8 = 3;
		}
	}
}

/* Function for Interrupt */
void SysTick_Handler(void){
	g_ClockSysTick_u32++;
}

void PORTA_IRQHandler(void){
	/* Interrupt for PIN_3 */
	if ((PORTA -> PORTA_PCR3) & (1u << 24)){
		(PORTA -> PORTA_PCR3) |= (1u << 24); /* w1c */
		
		g_BT1_u8 ^= (1u << 0);
	}
}

void PORTB_IRQHandler(void){
	/* Interrupt for PIN_8 */
	if ((PORTB -> PORTB_PCR8) & (1u << 24)){
		(PORTB -> PORTB_PCR8) |= (1u << 24); /* w1c */
		
		if (g_BT1_u8 != 0) /* BT1 is running then inverse g_BT2_u8 */
			g_BT2_u8 ^= (1u << 0);
		else{ /* BT1 is off then increase or decrease a unit (depend on current g_BT2_u8 status) */
			if (g_BT2_u8 == 0)
				g_State_u8--;
			else
				g_State_u8++;
			
			/* Limit g_State_u8 in zone 1->3 */
			if (g_State_u8 > 3)
				g_State_u8 = 1;
			if (g_State_u8 < 1)
				g_State_u8 = 3;
		}
	}
}
