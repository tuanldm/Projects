#ifndef BT04_H
#define BT04_H

#include "GPIO_Type.h"
#include "PCC_Type.h"
#include "PORT_Type.h"

void BT04_Ex1(void)__attribute__ ((noreturn)); /* Flash Led PTD16 delay 500ms (not use interrupt of SysTick) */
void BT04_Ex2(void)__attribute__ ((noreturn)); /* Flash Led PTD16 delay 500ms (use interrupt of SysTick) */
void BT04_Ex3(void)__attribute__ ((noreturn)); /* PTD16 ligh 2s, PTD16 off 1s (not use interrupt of SysTick) */
void BT04_Ex4(void)__attribute__ ((noreturn)); /* PTD16 ligh 2s, PTD16 off 1s (use interrupt of SysTick) */
void BT04_Ex5(void); /* Math real time of function for (i=0; i<250; i++) */

void ConfigureClockSoure_SlowIRC(void)__attribute__ ((noreturn)); /* Test Configure SlowIRC use RUN, Core and Sys CLK is 4MHZ */

#endif /* BT04_H */
