#ifndef MAIN_2_H
#define MAIN_2_H

/* Source */
#include "GPIO_Type.h"
#include "PCC_Type.h"
#include "INTERUPT_TYPE.h"
#include "LPIT_TYPE.h"
#include "LPSPI_TYPE.h"
#include "LPUART_TYPE.h"
#include "SCG_Type.h"
#include "PORT_Type.h"

#define PREDIV_2 1
#define MULTI_36 20
#define DIVCORE_1 0
#define DIVBUS_2 1
#define DIVFLASH_4 3
#define DIVDIV2_2 2

#define SCKDIV_2 0
#define PRESCALE_2 1
#define FRAMESIZE_16 15

#define SBR_36 36
#define OSR_26 25

#define DIV2_36MHZ (18000000-1)


typedef unsigned char UINT8;
typedef unsigned short UINT16;
typedef unsigned int UINT32;


/* Variable */
extern volatile UINT8 g_AdrL7D_aa[8]; /* digits 0->7 */
extern volatile UINT8 g_Intensity_u8;
extern volatile UINT8 g_MaL7D_aa[12]; /* 0->9, 10 is '.', 11 is '-' */
extern volatile UINT16 g_DisplayL7D_u16;

extern volatile UINT8 g_StatusTimeDate_u8;

extern volatile UINT8 g_NumberArrayGet_u8;
extern volatile UINT8 g_UARTDataRx_u8;
extern volatile UINT8 g_ArrayStringGet_aa[12]; /* Get maximum 10 chars ('Start char' + 10 data chars + 'End char') */

extern volatile UINT16 g_Year_u16;
extern volatile UINT8 g_Month_u8;
extern volatile UINT8 g_Date_u8;
extern volatile UINT8 g_Hour_u8;
extern volatile UINT8 g_Minute_u8;
extern volatile UINT8 g_Seconds_u8;
extern volatile UINT8 g_HourAlarm_u8;
extern volatile UINT8 g_MinuteAlarm_u8;
extern volatile UINT8 g_SecondsAlarm_u8;
extern volatile UINT8 g_EnableAlarm_u8;
extern volatile UINT8 g_OffAlarm10s_u8;

extern volatile UINT8 g_Timer0Ch0_u8;

extern volatile UINT8 g_EnableSend_u8;

/* Function */
void Setup_ClockCrystal_8MHZ(UINT8 PREDIV, UINT8 MULTI, UINT8 DIVCORE, UINT8 DIVBUS, UINT8 DIVFLASH, UINT8 PLLDIV2);
void Setup_LedAlarm(void);
void Setup_Button(void);
void Setup_LPSPI0(UINT8 SCKDIV, UINT8 PRESCALE, UINT8 FRAMESIZE);
void Setup_Led7D(void);
void Setup_LPUART1(UINT16 SBR, UINT8 OSR);
void Setup_Timer0Ch0(UINT32 PLL_DIV2);

UINT16 Com_GML7D(UINT8 l_AdrL7D_u8, UINT8 l_MaL7D_u8);
void Com_AdjustIntensity(void);
void Com_ControlLed7D(UINT16 l_DataSent_u16);
void Com_ProcessDataUART(void);
void Com_RunDateTime(void);
void Com_Alarm(void);

void PORTC_IRQHandler(void);
void LPUART1_RxTx_IRQHandler(void);
void LPIT0_Ch0_IRQHandler(void);



/* Function Interrupt */

#endif
