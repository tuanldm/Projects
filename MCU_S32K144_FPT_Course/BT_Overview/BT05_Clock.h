#ifndef BT05_H
#define BT05_H

#include "GPIO_Type.h"
#include "PCC_Type.h"
#include "PORT_Type.h"
#include "LPIT_TYPE.h"

/* Flash Led PTD16 delay 500ms follow in per situation */
void BT05_Ex1(void)__attribute__ ((noreturn)); /* Use Crystal 8MHZ create CORE Clock 80MHZ, BUS Clock 40MHZ */
void BT05_Ex2(void)__attribute__ ((noreturn)); /* Use Crystal 8MHZ create CORE Clock 8MHZ, BUS Clock 4MHZ */
void BT05_Ex3(void)__attribute__ ((noreturn)); /* Use FIRC 48MHZ create CORE Clock 24MHZ */
void BT05_Ex4(void)__attribute__ ((noreturn)); /* Use Crystal 8MHZ create CORE Clock 48MHZ, BUS Clock 16MHZ */
void BT05_Ex5(void)__attribute__ ((noreturn)); /* Use SIRC 8MHZ create CORE Clock 8MHZ */

void Test_Timer(void)__attribute__ ((noreturn));

#endif /* BT05_H */
