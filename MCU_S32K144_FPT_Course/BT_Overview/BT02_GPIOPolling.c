#include "BT02_GPIOPolling.h"
#include "Setup_Port_S32K144.h"

void BT02_Ex1(void){ /* Toggle led PTD16 */
	volatile unsigned int i = 0;
	
	PCC -> PCC_PORTD |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTD -> PORTD_PCR16 |= (1u << 8); /* set GPIO for PortD_PCR16 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTD -> PORTD_PCR16 &= ~(1u << 1) ; /* disabled pull-up/down for PortD_PCR16 */
	
	GPIOD -> GPIOD_PDDR |= (1u << 16); /* set (1) Output for PCR_16 (if 0 is Input) */
	
	while (1){
		/* Set/Rest bit 0 */
		for (i=0; i<500000; i++){ /* Same as delay */
		}
		GPIOD -> GPIOD_PDOR ^= (1u << 16); /* Reserve pin 16 of Port D */
	}
}


void BT02_Ex2(void){ /* Press PTC12 then PTD15 light, Release PTC12 then PTD15 off */
	volatile unsigned int f_RegisterTemp_u32;
		
	/* Set INPUT for PTC12 */
	PCC -> PCC_PORTC |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTC -> PORTC_PCR12 |= (1u << 8); /* set GPIO for PortC_PCR12 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTC -> PORTC_PCR12 &= ~(1u << 1) ; /* disabled pull-up/down for PortD_PCR12 */
	GPIOC -> GPIOC_PDDR &= ~(1u << 12); /* set (0) Input for PCR_12 (if 1 is Output) */
	
	/* Set OUTPUT for PTD15 */
	PCC -> PCC_PORTD |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTD -> PORTD_PCR15 |= (1u << 8); /* set GPIO for PortD_PCR15 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTD -> PORTD_PCR15 &= ~(1u << 1) ; /* disabled pull-up/down for PortD_PCR15 */
	GPIOD -> GPIOD_PDDR |= (1u << 15); /* set (1) Output for PCR_15 (if 0 is Input) */
	
	/* Run */
	while (1){
		/* check status of bit 12 of GPIOC_PDIR */
		f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
		f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 12) % 2;
		
		if (f_RegisterTemp_u32 == 1) {
			GPIOD -> GPIOD_PDOR &= ~(1u << 15); /* Reset pin 15 of Port D */
		}
		else {
			GPIOD -> GPIOD_PDOR |= (1u << 15); /* Set pin 15 of Port D */
		}
	}
}

void BT02_Ex3(void){ /* Press PTC12 then PTD0 light, Press PTC13 then PTD0 off */
	volatile unsigned int f_RegisterTemp_u32;
	
	/* Set INPUT for PTC12 */
	PCC -> PCC_PORTC |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTC -> PORTC_PCR12 |= (1u << 8); /* set GPIO for PortC_PCR12 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTC -> PORTC_PCR12 &= ~(1u << 1) ; /* disabled pull-up/down for PortC_PCR12 */
	GPIOC -> GPIOC_PDDR &= ~(1u << 12); /* set (0) Input for PCR_12 (if 1 is Output) */
	
	/* Set INPUT for PTC13 */
	PCC -> PCC_PORTC |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTC -> PORTC_PCR13 |= (1u << 8); /* set GPIO for PortC_PCR12 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTC -> PORTC_PCR13 &= ~(1u << 1) ; /* disabled pull-up/down for PortC_PCR13 */
	GPIOC -> GPIOC_PDDR &= ~(1u << 13); /* set (0) Input for PCR_13 (if 1 is Output) */
	
	/* Set OUTPUT for PTD0 */
	PCC -> PCC_PORTD |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTD -> PORTD_PCR0 |= (1u << 8); /* set GPIO for PortD_PCR0 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTD -> PORTD_PCR0 &= ~(1u << 1) ; /* disabled pull-up/down for PortD_PCR0 */
	GPIOD -> GPIOD_PDDR |= (1u << 0); /* set (1) Output for PCR_0 (if 0 is Input) */
	
	
	while(1){
		/* check status of bit 12 of GPIOC_PDIR */
		f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
		f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 12) % 2;
		if (f_RegisterTemp_u32 == 1) {
			GPIOD -> GPIOD_PDOR &= ~(1u << 0); /* Reset pin 0 of Port D */
		}
		
		/* check status of bit 13 of GPIOC_PDIR */
		f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
		f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 13) % 2;
		if (f_RegisterTemp_u32 == 1) {
			GPIOD -> GPIOD_PDOR |= (1u << 0); /* Set pin 0 of Port D */
		}
	}
}

void BT02_Ex4(void){ /* PTC12 control Led PTD16 (press to toggle status) */ 
	volatile unsigned int f_RegisterTemp_u32;
	volatile unsigned char f_Status_u8 = 0;
		
	/* Set INPUT for PTC12 */
	PCC -> PCC_PORTC |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTC -> PORTC_PCR12 |= (1u << 8); /* set GPIO for PortC_PCR12 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTC -> PORTC_PCR12 &= ~(1u << 1) ; /* disabled pull-up/down for PortD_PCR12 */
	GPIOC -> GPIOC_PDDR &= ~(1u << 12); /* set (0) Input for PCR_12 (if 1 is Output) */
	
	/* Set OUTPUT for PTD16 */
	PCC -> PCC_PORTD |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTD -> PORTD_PCR16 |= (1u << 8); /* set GPIO for PortD_PCR16 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTD -> PORTD_PCR16 &= ~(1u << 1) ; /* disabled pull-up/down for PortD_PCR16 */
	GPIOD -> GPIOD_PDDR |= (1u << 16); /* set (1) Output for PCR_16 (if 0 is Input) */
	
	while(1){
		/* check status of bit 12 of GPIOC_PDIR */
		f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
		f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 12) % 2;
		
		while (f_RegisterTemp_u32 == 1) {
			f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
			f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 12) % 2;
			if (f_RegisterTemp_u32 == 0){
				f_Status_u8 = ~f_Status_u8;
				break;
			}
		}
		
		if(f_Status_u8 == 0){
			GPIOD -> GPIOD_PDOR |= (1u << 16); /* Set pin 16 of Port D */
		}
		else{
			GPIOD -> GPIOD_PDOR &= ~(1u << 16); /* Reset pin 16 of Port D */
		}
	}
}

void BT02_Ex5(void){ /* PTC12 make PTD16 flash about 5HZ, PTC13 make PTD16 always light */
	volatile unsigned int f_RegisterTemp_u32;
	volatile unsigned int i = 0;
	volatile unsigned char f_Status_u8 = 0;
	
	/* Set INPUT for PTC12 */
	PCC -> PCC_PORTC |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTC -> PORTC_PCR12 |= (1u << 8); /* set GPIO for PortC_PCR12 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTC -> PORTC_PCR12 &= ~(1u << 1) ; /* disabled pull-up/down for PortC_PCR12 */
	GPIOC -> GPIOC_PDDR &= ~(1u << 12); /* set (0) Input for PCR_12 (if 1 is Output) */
	
	/* Set INPUT for PTC13 */
	PCC -> PCC_PORTC |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTC -> PORTC_PCR13 |= (1u << 8); /* set GPIO for PortC_PCR12 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTC -> PORTC_PCR13 &= ~(1u << 1) ; /* disabled pull-up/down for PortC_PCR13 */
	GPIOC -> GPIOC_PDDR &= ~(1u << 13); /* set (0) Input for PCR_13 (if 1 is Output) */
	
	/* Set OUTPUT for PTD0 */
	PCC -> PCC_PORTD |= (1u << 30); /* set clock control (bit 30 = 1) */
	PORTD -> PORTD_PCR16 |= (1u << 8); /* set GPIO for PortD_PCR0 in bit 8-9-10 (MUX 001 is set for GPIO) */
	PORTD -> PORTD_PCR16 &= ~(1u << 1) ; /* disabled pull-up/down for PortD_PCR0 */
	GPIOD -> GPIOD_PDDR |= (1u << 16); /* set (1) Output for PCR_0 (if 0 is Input) */
	
	while(1){
		/* check status of bit 12 of GPIOC_PDIR */
		f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
		f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 12) % 2;
		while (f_RegisterTemp_u32 == 1) {
			f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
			f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 12) % 2;
			if (f_RegisterTemp_u32 == 0){
				f_Status_u8 = 1;
				break;
			}
		}
		
		f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
		f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 13) % 2;
		while (f_RegisterTemp_u32 == 1) {
			f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
			f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 13) % 2;
			if (f_RegisterTemp_u32 == 0){
				f_Status_u8 = 0;
				break;
			}
		}
		
		if (f_Status_u8 == 0){
			GPIOD -> GPIOD_PDOR &= ~(1u << 16); /* Reset pin 16 of Port D */
		}
		else{
			for(i=0; i<1000000; i++){
				f_RegisterTemp_u32 = (GPIOC -> GPIOC_PDIR);
				f_RegisterTemp_u32 = (f_RegisterTemp_u32 >> 12) % 2;
				if (f_RegisterTemp_u32 == 1){
					f_Status_u8 = 1;
					break;
				}
			}
			GPIOD -> GPIOD_PDOR ^= (1u << 16); /* Toggle pin 16 of Port D */
		}
	}
}
