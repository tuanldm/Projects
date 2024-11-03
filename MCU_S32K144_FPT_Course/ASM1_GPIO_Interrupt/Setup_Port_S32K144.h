/* Introduce */
#ifndef SETUP_PORT_S32K144_H
#define SETUP_PORT_S32K144_H

#include "GPIO_Type.h"
#include "PCC_Type.h"
#include "PORT_Type.h"
#include "INTERUPT_TYPE.h"
#include "SYSTICK_Type.h"

#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1
#define	PIN_0 0
#define	PIN_1 1
#define	PIN_2 2
#define	PIN_3 3
#define	PIN_4 4
#define	PIN_5 5
#define	PIN_7 7
#define	PIN_8 8
#define	PIN_9 9
#define	PIN_10 10
#define	PIN_11 11
#define	PIN_12 12
#define	PIN_13 13
#define	PIN_14 14
#define	PIN_15 15
#define	PIN_16 16
#define	PIN_17 17


void PORTC_IRQHandler(void); /* Interrupt port C */
void SysTick_Handler(void); /* Interrupt SysTick Timer */
void Delay_SysTick(unsigned int milisecond); /* SysTick Timer without Interrupt */

void Setup_PortPin(void* PORTx, unsigned char PIN, unsigned char MODE); /* set up INPUT/OUTPUT for a Pin */
void Set_PortPin(void* PORTx, unsigned char PIN, unsigned char LEVEL); /* set HIGH/LOW for a Pin mode Output */
void Toggle_PortPin(void* PORTx, unsigned char PIN); /* Inverse Value for Output PortPin */
char Get_PortPin(void* PORTx, unsigned char PIN); /* Get status of Pin mode Input */


#endif /* SETUP_PORT_S32K144_H */
