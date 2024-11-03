#include "main_2.h"

int main(void){
	UINT8 l_Stt_u8 = 0;
	UINT8 l_ArrayFormat1_aa[] = "Input Format:\n";
	UINT8 l_ArrayFormat2_aa[] = "Date: Dxx.xx.xxxx\n";
	UINT8 l_ArrayFormat3_aa[] = "Time: Txx-xx-xx--\n";
	UINT8 l_ArrayFormat4_aa[] = "Alarm: Axx-xx-xx--\n";
	
	Setup_ClockCrystal_8MHZ(PREDIV_2, MULTI_36, DIVCORE_1, DIVBUS_2, DIVFLASH_4, DIVDIV2_2); /* Core_72, Bus_36, Flash_18, Div2_36 */
	Setup_LedAlarm();
	Setup_Button();
	Setup_LPSPI0(SCKDIV_2, PRESCALE_2, FRAMESIZE_16); /* Output 9MHZ */
	Setup_Led7D();
	Setup_LPUART1(SBR_36, OSR_26); /* Baurate ~38400 */
	Setup_Timer0Ch0(DIV2_36MHZ);
	
	g_Date_u8 = 1;
	g_Month_u8 = 1;
	g_Year_u16 = 1991;
	g_Hour_u8 = 18;
	g_Minute_u8 = 0;
	g_Seconds_u8 = 0;
	g_StatusTimeDate_u8 = 0;
	
	l_Stt_u8 = 0;
	while (l_ArrayFormat1_aa[l_Stt_u8]){
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} 
		LPUART1 -> LPUART_DATA = l_ArrayFormat1_aa[l_Stt_u8];
		l_Stt_u8++;
	}
	l_Stt_u8 = 0;
	while (l_ArrayFormat2_aa[l_Stt_u8]){
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} 
		LPUART1 -> LPUART_DATA = l_ArrayFormat2_aa[l_Stt_u8];
		l_Stt_u8++;
	}
	l_Stt_u8 = 0;
	while (l_ArrayFormat3_aa[l_Stt_u8]){
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){}
		LPUART1 -> LPUART_DATA = l_ArrayFormat3_aa[l_Stt_u8];
		l_Stt_u8++;
	}
	l_Stt_u8 = 0;
	while (l_ArrayFormat4_aa[l_Stt_u8]){
		while ( !((LPUART1 -> LPUART_STAT) & (1u << 23)) ){} 
		LPUART1 -> LPUART_DATA = l_ArrayFormat4_aa[l_Stt_u8];
		l_Stt_u8++;
	}
	
	
	while(1){
		Com_RunDateTime();
		Com_Alarm();
		if ((g_StatusTimeDate_u8 == 0) && (g_EnableSend_u8 == 0) && (g_Intensity_u8 != 0) ){
			Com_ControlLed7D( Com_GML7D(7, (g_Hour_u8/10)) );
			Com_ControlLed7D( Com_GML7D(6, (g_Hour_u8%10)) );
			Com_ControlLed7D( Com_GML7D(5, 11) );
			Com_ControlLed7D( Com_GML7D(4, (g_Minute_u8/10)) );
			Com_ControlLed7D( Com_GML7D(3, (g_Minute_u8%10)) );
			Com_ControlLed7D( Com_GML7D(2, 11) );
			Com_ControlLed7D( Com_GML7D(1, (g_Seconds_u8/10)) );
			Com_ControlLed7D( Com_GML7D(0, (g_Seconds_u8%10)) );
			g_EnableSend_u8++; /* send data per seconds */
		}
		else if ((g_StatusTimeDate_u8 == 1) && (g_EnableSend_u8 == 0) && (g_Intensity_u8 != 0) ){
			Com_ControlLed7D( Com_GML7D(7, (g_Date_u8/10)) );
			Com_ControlLed7D( Com_GML7D(6, (g_Date_u8%10)) | Com_GML7D(6, 10) );
			Com_ControlLed7D( Com_GML7D(5, (g_Month_u8/10)) );
			Com_ControlLed7D( Com_GML7D(4, (g_Month_u8%10)) | Com_GML7D(4, 10) );
			Com_ControlLed7D( Com_GML7D(3, (g_Year_u16/1000)) );
			Com_ControlLed7D( Com_GML7D(2, (g_Year_u16/100%10)) );
			Com_ControlLed7D( Com_GML7D(1, (UINT8)(g_Year_u16/10%10)) );
			Com_ControlLed7D( Com_GML7D(0, (UINT8)(g_Year_u16%10)) );
			g_EnableSend_u8++; /* send data per seconds */
		}
			
	}
	
}
