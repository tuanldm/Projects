#ifndef MAIN_H
#define MAIN_H

#include "PCC_Type.h"
#include "LPIT_TYPE.h"
#include "LPUART_TYPE.h"
#include "INTERUPT_TYPE.h"
#include "GPIO_Type.h"
#include "PORT_Type.h"

extern volatile unsigned char g_UARTDataRx_u8;
extern volatile unsigned char g_NumberArrayGet_u8;
extern volatile unsigned char g_ArrayStringGet_aa[22]; /* Get maximum 22 chars (uint32 + uint32 =) */
extern volatile unsigned char g_ArrayStringSend_aa[10]; /* UInterger type max have 10 nums */

void LPUART1_RxTx_IRQHandler(void); /* Interrupt for LPUART_1 */
void ProcessData(void);


#endif
