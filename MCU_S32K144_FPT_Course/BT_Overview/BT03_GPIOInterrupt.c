#include "BT03_GPIOInterrupt.h"
#include "Setup_Port_S32K144.h"

unsigned char g_StatusBT03Ex2_u8 = 0; /* Control Ex2 */
unsigned char g_StatusBT03Ex3_u8 = 0; /* Control Ex3 */
unsigned char g_StatusBT03Ex4_u8 = 0; /* Control Ex4 */
unsigned char g_StatusBT03Ex5_u8 = 0; /* Control Ex5 */

void BT03_Ex2(void){ /* Press PTC12 then PTD15 light, Release PTC12 then PTD15 off */
	/* set up */
	Setup_PortPin(PORTC, PIN_12, INPUT);
	Setup_PortPin(PORTD, PIN_15, OUTPUT);
	g_StatusBT03Ex2_u8 = 0;
	
	/* Set Enable Interupt for PortC have ID 61 */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 29); /*set 1 for bit 30 of NVIC_ISER1 */
	PORTC -> PORTC_PCR12 |= (3u << 18); /* set 1100 for bits 16->19 (1 logic interupt) */
	
	while(1){
		if (g_StatusBT03Ex2_u8 == 0)
			Set_PortPin(PORTD, PIN_15, HIGH);
		else
			Set_PortPin(PORTD, PIN_15, LOW);
		g_StatusBT03Ex2_u8 = 0;
	}
}

void BT03_Ex3(void){ /* Press PTC12 then PTD0 light, Press PTC13 then PTD0 off */
	/* set up */
	Setup_PortPin(PORTC, PIN_12, INPUT);
	Setup_PortPin(PORTC, PIN_13, INPUT);
	Setup_PortPin(PORTD, PIN_0, OUTPUT);
	
	/* Set Enable Interupt for PortC have ID 61 */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 29); /*set 1 for bit 30 of NVIC_ISER1 */
	PORTC -> PORTC_PCR12 |= (10u << 16); /* set 1010 for bits 16->19 (falling-edge interupt) */
	PORTC -> PORTC_PCR13 |= (10u << 16); /* set 1010 for bits 16->19 (falling-edge interupt) */
	
	while(1){
		if (g_StatusBT03Ex3_u8)
			Set_PortPin(PORTD, PIN_0, LOW);
		else
			Set_PortPin(PORTD, PIN_0, HIGH);
	}
}

void BT03_Ex4(void){ /* PTC12 control Led PTD15 (press to toggle status) */ 
	/* set up */
	Setup_PortPin(PORTC, PIN_12, INPUT);
	Setup_PortPin(PORTD, PIN_15, OUTPUT);
	
	/* Set Enable Interupt for PortC have ID 61 */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 29); /*set 1 for bit 30 of NVIC_ISER1 */
	PORTC -> PORTC_PCR12 |= (10u << 16); /* set 1010 for bits 16->19 (falling-edge interupt) */
	
	while(1){
		if(g_StatusBT03Ex4_u8){
			Toggle_PortPin(PORTD, PIN_15);
			g_StatusBT03Ex4_u8 = 0;
		}
	}
}

void BT03_Ex5(void){ /* PTC12 make PTD16 flash about 5HZ, PTC13 make PTD16 always light */
	/* set up */
	Setup_PortPin(PORTC, PIN_12, INPUT);
	Setup_PortPin(PORTC, PIN_13, INPUT);
	Setup_PortPin(PORTD, PIN_16, OUTPUT);
	g_StatusBT03Ex5_u8 = 0;
	
	/* Set Enable Interupt for PortC have ID 61 */
	INTERUPT_SET -> NVIC_ISER1 |= (1u << 29); /*set 1 for bit 30 of NVIC_ISER1 */
	PORTC -> PORTC_PCR12 |= (10u << 16); /* set 1010 for bits 16->19 (falling-edge interupt) */
	PORTC -> PORTC_PCR13 |= (10u << 16); /* set 1010 for bits 16->19 (falling-edge interupt) */
	
	while(1){
		if (g_StatusBT03Ex5_u8 == 1){
			Delay_SysTick(5000);
			Toggle_PortPin(PORTD, PIN_16);
		}
		else if (g_StatusBT03Ex5_u8 == 2){
			Set_PortPin(PORTD, PIN_16, LOW);
		}
	}
}

void test_priority(void){
	volatile unsigned int x;
	
	Setup_PortPin(PORTC, PIN_12, INPUT);
	Setup_PortPin(PORTD, PIN_16, INPUT);
	
	INTERUPT_PRIORITY -> NVIC_IPR15 |= (1 << 12); /* Set PORT_C has piority 1 */
	INTERUPT_PRIORITY -> NVIC_IPR15 |= (5 << 20); /* Set PORT_D has piority 5 */
	PORTC -> PORTC_PCR12 |= (10u << 16); /* set 1010 for bits 16->19 (falling-edge interupt) */
	PORTD -> PORTD_PCR12 |= (10u << 16); /* set 1010 for bits 16->19 (falling-edge interupt) */
	
	x = (INTERUPT_PRIORITY -> NVIC_IPR15);
	x++;
	x--;
	
	while(1){
		x = (INTERUPT_PRIORITY -> NVIC_IPR15);
	}
}
