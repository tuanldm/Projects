#ifndef BT06_H
#define BT06_H

#include "GPIO_Type.h"
#include "PCC_Type.h"
#include "PORT_Type.h"
#include "LPIT_TYPE.h"
#include "LPUART_TYPE.h"
#include "LPSPI_TYPE.h"

/* Using Crystal create Core 80MHZ, Bus 40MHZ, Flash 26.67MHZ and conduct flash led to follow in per situation */
void BT06_Ex1(void)__attribute__ ((noreturn)); /* TON 500ms, TOFF 500ms, Timer_CH0 mode 32 bits */
void BT06_Ex2(void)__attribute__ ((noreturn)); /* TON 250ms, TOFF 750ms, Timer_CH1 mode 32 bits */
void BT06_Ex3(void)__attribute__ ((noreturn)); /* TON 2000ms, TOFF 1500ms, Timer_CH2 mode 32 bits */
void BT06_Ex4(void)__attribute__ ((noreturn)); /* TON 1500ms, TOFF 500ms, Timer_CH3 mode 32 bits */
void BT06_Ex5(void)__attribute__ ((noreturn)); /* TON 1000ms, TOFF 1000ms, Timer_CH0 mode dual 16 bits */
void BT06_Ex6(void)__attribute__ ((noreturn)); /* TON 3000ms, TOFF 3000ms, Timer_CH1 mode dual 32 bits (chain) */

void Test_UART(void)__attribute__ ((noreturn));
void Test_SPI(void)__attribute__ ((noreturn));

#endif /* BT06_H */
