#include "Setup_Port_S32K144.h"

/* Setup Port_Pin */
void Setup_PortPin(void* PORTx, unsigned char PIN, unsigned char MODE){ /* set up INPUT/OUTPUT for a Pin */
	if (PORTx == PORTA){
		PCC -> PCC_PORTA |= (1u << 30); /* set clock control (bit 30 = 1) */
		if (PIN <= 17){
			*(((unsigned int*)PORTA_BASE_ADDRS) + PIN) |= (1u << 8); /* set GPIO for PortA_PCRx in bit 8-9-10 (MUX 001 is set for GPIO) */
			*(((unsigned int*)PORTA_BASE_ADDRS) + PIN) &= ~(1u << 1) ; /* disabled pull-up/down for PortA_PCRx */
			if(MODE == INPUT){
				GPIOA -> GPIOA_PDDR &= ~(1u << PIN); /* set (0) Input for PCR_x (if 1 is Output) */ 
			}
			else if (MODE == OUTPUT){
				GPIOA -> GPIOA_PDDR |= (1u << PIN); /* set (1) Output for PCR_x (if 0 is Input) */ 
			}
		}
	}
	else if (PORTx == PORTB){
		PCC -> PCC_PORTB |= (1u << 30); /* set clock control (bit 30 = 1) */
		if (PIN <= 17){
			*(((unsigned int*)PORTB_BASE_ADDRS) + PIN) |= (1u << 8); /* set GPIO for PortB_PCRx in bit 8-9-10 (MUX 001 is set for GPIO) */
			*(((unsigned int*)PORTB_BASE_ADDRS) + PIN) &= ~(1u << 1) ; /* disabled pull-up/down for PortB_PCRx */
			if(MODE == INPUT){
				GPIOB -> GPIOB_PDDR &= ~(1u << PIN); /* set (0) Input for PCR_x (if 1 is Output) */ 
			}
			else if (MODE == OUTPUT){
				GPIOB -> GPIOB_PDDR |= (1u << PIN); /* set (1) Output for PCR_x (if 0 is Input) */ 
			}
		}
	}
	else if (PORTx == PORTC){
		PCC -> PCC_PORTC |= (1u << 30); /* set clock control (bit 30 = 1) */
		if (PIN <= 17){
			*(((unsigned int*)PORTC_BASE_ADDRS) + PIN) |= (1u << 8); /* set GPIO for PortC_PCRx in bit 8-9-10 (MUX 001 is set for GPIO) */
			*(((unsigned int*)PORTC_BASE_ADDRS) + PIN) &= ~(1u << 1) ; /* disabled pull-up/down for PortC_PCRx */
			if(MODE == INPUT){
				GPIOC -> GPIOC_PDDR &= ~(1u << PIN); /* set (0) Input for PCR_x (if 1 is Output) */ 
			}
			else if (MODE == OUTPUT){
				GPIOC -> GPIOC_PDDR |= (1u << PIN); /* set (1) Output for PCR_x (if 0 is Input) */ 
			}
		}
	}
	else if (PORTx == PORTD){
		PCC -> PCC_PORTD |= (1u << 30); /* set clock control (bit 30 = 1) */
		if (PIN <= 17){
			*(((unsigned int*)PORTD_BASE_ADDRS) + PIN) |= (1u << 8); /* set GPIO for PortD_PCRx in bit 8-9-10 (MUX 001 is set for GPIO) */
			*(((unsigned int*)PORTD_BASE_ADDRS) + PIN) &= ~(1u << 1) ; /* disabled pull-up/down for PortD_PCRx */
			if(MODE == INPUT){
				GPIOD -> GPIOD_PDDR &= ~(1u << PIN); /* set (0) Input for PCR_x (if 1 is Output) */ 
			}
			else if (MODE == OUTPUT){
				GPIOD -> GPIOD_PDDR |= (1u << PIN); /* set (1) Output for PCR_x (if 0 is Input) */ 
			}
		}
	}
	else if (PORTx == PORTE){
		PCC -> PCC_PORTE |= (1u << 30); /* set clock control (bit 30 = 1) */
		if (PIN <= 16){
			*(((unsigned int*)PORTE_BASE_ADDRS) + PIN) |= (1u << 8); /* set GPIO for PortE_PCRx in bit 8-9-10 (MUX 001 is set for GPIO) */
			*(((unsigned int*)PORTE_BASE_ADDRS) + PIN) &= ~(1u << 1) ; /* disabled pull-up/down for PortE_PCRx */
			if(MODE == INPUT){
				GPIOE -> GPIOE_PDDR &= ~(1u << PIN); /* set (0) Input for PCR_x (if 1 is Output) */ 
			}
			else if (MODE == OUTPUT){
				GPIOE -> GPIOE_PDDR |= (1u << PIN); /* set (1) Output for PCR_x (if 0 is Input) */ 
			}
		}
	}
}

/* Set Value for Output PortPin */
void Set_PortPin(void* PORTx, unsigned char PIN, unsigned char LEVEL){ /* set HIGH/LOW for a Pin mode Output */
	if (PORTx == PORTA){
		if (PIN < 18){
			if (LEVEL == LOW) 
				GPIOA -> GPIOA_PDOR &= ~(1u << PIN);
			else 
				GPIOA -> GPIOA_PDOR |= (1u << PIN);
		}
	}
	else if (PORTx == PORTB){
		if (PIN < 18){
			if (LEVEL == LOW) 
				GPIOB -> GPIOB_PDOR &= ~(1u << PIN);
			else 
				GPIOB -> GPIOB_PDOR |= (1u << PIN);
		}
	}
	else if (PORTx == PORTC){
		if (PIN < 18){
			if (LEVEL == LOW) 
				GPIOC -> GPIOC_PDOR &= ~(1u << PIN);
			else 
				GPIOC -> GPIOC_PDOR |= (1u << PIN);
		}
	}
	else if (PORTx == PORTD){
		if (PIN < 18){
			if (LEVEL == LOW) 
				GPIOD -> GPIOD_PDOR &= ~(1u << PIN);
			else 
				GPIOD -> GPIOD_PDOR |= (1u << PIN);
		}
	}
	else if (PORTx == PORTE){
		if (PIN < 17){
			if (LEVEL == LOW) 
				GPIOE -> GPIOE_PDOR &= ~(1u << PIN);
			else 
				GPIOE -> GPIOE_PDOR |= (1u << PIN);
		}
	}
}

/* Inverse Value for Output PortPin */
void Toggle_PortPin(void* PORTx, unsigned char PIN){ /* Inverse Value for Output PortPin */
	if (PORTx == PORTA){
		if (PIN < 18){
			GPIOA -> GPIOA_PDOR ^= (1u << PIN);
		}
	}
	else if (PORTx == PORTB){
		if (PIN < 18){
			GPIOB -> GPIOB_PDOR ^= (1u << PIN);
		}
	}
	else if (PORTx == PORTC){
		if (PIN < 18){
			GPIOC -> GPIOC_PDOR ^= (1u << PIN);
		}
	}
	else if (PORTx == PORTD){
		if (PIN < 18){
			GPIOD -> GPIOD_PDOR ^= (1u << PIN);
		}
	}
	else if (PORTx == PORTE){
		if (PIN < 17){
			GPIOE -> GPIOE_PDOR ^= (1u << PIN);
		}
	}
}

/* Get Value for Input PortPin */
char Get_PortPin(void* PORTx, unsigned char PIN){ /* Get status of Pin mode Input */
	if (PORTx == PORTA){
		if (PIN < 18){
			if ((GPIOA -> GPIOA_PDIR) & (1u << PIN))
				return 1;
			else
				return 0;
		}
	}
	else if (PORTx == PORTB){
		if (PIN < 18){
			if ((GPIOB -> GPIOB_PDIR) & (1u << PIN))
				return 1;
			else
				return 0;
		}
	}
	else if (PORTx == PORTC){
		if (PIN < 18){
			if ((GPIOC -> GPIOC_PDIR) & (1u << PIN))
				return 1;
			else
				return 0;
		}
	}
	else if (PORTx == PORTD){
		if (PIN < 18){
			if ((GPIOD -> GPIOD_PDIR) & (1u << PIN))
				return 1;
			else
				return 0;
		}
	}
	else if (PORTx == PORTE){
		if (PIN < 17){
			if ((GPIOE -> GPIOE_PDIR) & (1u << PIN))
				return 1;
			else
				return 0;
		}
	}
	return 0;
}

/* Delay_SysTick without Interrupt */
void Delay_SysTick(unsigned int milisecond){ /* Delay_SysTick without Interrupt */
	volatile unsigned int f_CheckDelay_u32 = 0;
	
	SYSTICK -> SYSTICK_CTRL = 0u; /* 0 is Disable SysTick Timer to set up SysTick */
	SYSTICK -> SYSTICK_CTRL |= (1u << 2); /* Bit 2 is choose clock source (0 external / 1 system ) */ 
	SYSTICK -> SYSTICK_LOAD = 47999u; /* Set 48000 HZ to flag (<=> 1 milisecond because SysTick max is 48MHZ) */
	SYSTICK -> SYSTICK_VAL = 1u; /* write any value to reset VAL = 0 */
	SYSTICK -> SYSTICK_CTRL &= ~(1u << 1); /* Bit 1 is interrupt (0 Disable / 1 Enable) */
	SYSTICK -> SYSTICK_CTRL |= (1u << 0);	/* Enable SysTick */
	
	while (f_CheckDelay_u32 < milisecond){
		while (!((SYSTICK -> SYSTICK_CTRL) & (1u << 16))){} /* check bit 16, triggered when complete a cycle-time */	
		f_CheckDelay_u32++; /* when f_CheckDelay_u32++ is 1 milisecond */
		SYSTICK -> SYSTICK_CTRL &= ~(1u << 16);
	}
	
	SYSTICK -> SYSTICK_CTRL = 0u; /* 0 is Disable SysTick Timer to end Delay process */
}
