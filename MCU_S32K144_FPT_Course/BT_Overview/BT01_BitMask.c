#include "BT01_BitMask.h"

void BT01_Ex3(void){
	PCC -> PCC_PORTA = 0x1234;
	PORTB -> PORTB_PCR10 = 0x5555;
	GPIOC -> GPIOC_PDOR = 0xAAAA;
}
