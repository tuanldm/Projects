#include <stdio.h>
#include <ctime>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;

/* global variable */
char g_ListTemp_aa[500][200]; /* Row : Text */
char g_EndLine_aa[10] = "EOF,,,,,\n"; /* Endline of text */
char g_ListOut_aa[500][200]; /* Row : Text */
char g_UInt32ToChar_aa[3]; /* max 00-99 */
char g_TimeNow_aa[20] = "00/00/00 - 00:00:00";
uint16 g_RowOut_u16 = 0;

/* Compare length and char 2 Strings */
int Com_CompareStrings(char l_Str1_aa[10], char l_Str2_aa[10]); 

/* Check Key */
int Com_CompareKey(char l_Compare_aa[5]);

/* Convert text in hex type to Interger */
int Com_ConvertCharHexToInt(char l_Input_aa[10]);

/* Convert Unsigned Interger to Chars --- Return amount of Numbers */
void Com_ConvertUInt32ToChar(uint32 l_Input_u32);

/* Get Time Now */
void Com_GetTimeNow();

/* Process MSN -> Return a count of Line which MSN using */
void Com_ProcessMSN(char l_CSV_aa[500][6][50], uint16 l_RowCSV_u16, char l_Template_aa[200][200], uint16 l_RowTemplate_u16, char l_ListMSN_aa[300][200], uint16 l_LineMSN_aa[3]);

/* Process ListOut */
void Com_ProcessListOut(char l_Template_aa[200][200], uint16 l_RowTemplate_u16, char l_ListMSN_aa[300][200], uint16 l_LineMSN_aa[3]);

/* Arrange and save the data of g_ListTemp_aa[][] in l_ListCSV_aa[][][] */
void Com_SaveListCSV(char l_ListStore_aa[500][6][50], uint16 l_Row_u16);

/* Save the data of g_ListTemp_aa[][] in l_ListTemplate_aa[][] */
void Com_SaveListTemplate(char l_ListStore_aa[200][200], uint16 l_Row_u16);

/* Get data from file and save in Temp_Variable (text) */
void Get_InfoToTemp(char l_Link_aa[200], uint16* l_Row_u16);

/* Get link */
void Get_InputLink(char l_LinkFile_aa[200]);

/* Export Data to File */
void Export_DataToFile(char l_Link_aa[200]);

int main(){
	/* Variable of Menu */
	uint8 l_SwitchCaseMain_u8 = 0;
	uint8 l_SwitchCaseVice_u8 = 0;
	uint8 l_CheckLinkCSV_u8 = 0;
	uint8 l_CheckLinkTemplate_u8 = 0;
	uint8 l_CheckLinkOut_u8 = 0;
	
	/* Variable of CSV_File */
	char l_LinkCSV_aa[200];
	char l_ListCSV_aa[500][6][50]; /* Row : Column : Text */
	uint16 l_RowCSV_u16 = 0; /* count of Row_CSV is returned */
	
	/* Variable of Template_File */
	char l_LinkTemplate_aa[200];
	char l_ListTemplate_aa[200][200]; /* Row : Text */
	uint16 l_RowTemplate_u16 = 0; /* count of Row_Template is returned */
	
	/* Variable of Process Data to Out */
	char l_ListMSN_aa[300][200]; /* max 300 row : max 200 char per row */
	uint16 l_LineMSN_aa[3]; /* LineStart : LineEnd : LineUse */
	
	/* Variable of Export data to File */
	char l_LinkOut_aa[200];
	
	/* Menu */
	l_SwitchCaseMain_u8 = 0;
	while (l_SwitchCaseMain_u8 != 3){
		printf("Input command:\n\t1. Input Link\n\t2. Generate File.h\n\t3. Exit\n");
		scanf("%d", &l_SwitchCaseMain_u8);
		getchar();
		switch(l_SwitchCaseMain_u8){
			case 1:{
				l_SwitchCaseVice_u8 = 0;
				while (l_SwitchCaseVice_u8 != 4){
					printf("Input command:\n\t1. Input Link_Input_CSV\n\t2. Input Link_Input_Template\n\t3. Input Link_Output\n\t4. Back to main menu\n");
					scanf("%d", &l_SwitchCaseVice_u8);
					getchar();
					if (l_SwitchCaseVice_u8 == 1){
						Get_InputLink(l_LinkCSV_aa);
					}
					else if (l_SwitchCaseVice_u8 == 2){
						Get_InputLink(l_LinkTemplate_aa);
					}
					else if (l_SwitchCaseVice_u8 == 3){
						Get_InputLink(l_LinkOut_aa);
					}
					else if (l_SwitchCaseVice_u8 == 4){
						break;
					}
					else{
						printf("Chose Fail - chose 4 for exit\n");
					}
				}
				break;
			}
			case 2:{
				/* Check Link */
				if (l_LinkCSV_aa[0]){ /* link <> NULL (first char) */
					l_CheckLinkCSV_u8 = 1;
				}
				if (l_LinkTemplate_aa[0]){ /* link <> NULL (first char) */
					l_CheckLinkTemplate_u8 = 1;
				}
				if (l_LinkOut_aa[0]){ /* link <> NULL (first char) */
					l_CheckLinkOut_u8 = 1;
				}
				if ( (l_CheckLinkCSV_u8==1) && (l_CheckLinkTemplate_u8==1) && (l_CheckLinkOut_u8==1) ){
					/* Get and process data of CSV_file */
					Get_InfoToTemp(l_LinkCSV_aa, &l_RowCSV_u16);
					Com_SaveListCSV(l_ListCSV_aa, l_RowCSV_u16);
					
					/* Save data of Template_File in l_LinkTemplate_aa[][] */
					Get_InfoToTemp(l_LinkTemplate_aa, &l_RowTemplate_u16);
					Com_SaveListTemplate(l_ListTemplate_aa, l_RowTemplate_u16);
					
					/* Process Data to Out */
					Com_ProcessMSN(l_ListCSV_aa, l_RowCSV_u16, l_ListTemplate_aa, l_RowTemplate_u16, l_ListMSN_aa, l_LineMSN_aa);
					Com_ProcessListOut(l_ListTemplate_aa, l_RowTemplate_u16, l_ListMSN_aa, l_LineMSN_aa);
					
					/* Export data to File Out */
					Export_DataToFile(l_LinkOut_aa);
					
					/* Clear data to reuse */
					for (uint16 i=0; i<500; i++){
						for (uint16 j=0; j<200; j++){
							g_ListTemp_aa[i][j] = '\0';
							g_ListOut_aa[i][j] = '\0';
							if (i < 1){
								if (j < 3){
									l_LineMSN_aa[j] = '\0';
									g_UInt32ToChar_aa[j] = '\0';
								}
								if (j < 200){
									l_LinkCSV_aa[j] = '\0';
									l_LinkTemplate_aa[j] = '\0';
									l_LinkOut_aa[j] = '\0';
								}
								
							}
							if (i < 200){
								l_ListTemplate_aa[i][j] = '\0';
							}
							if (i < 300){
								l_ListMSN_aa[i][j] = '\0';
							}
						}
					}
					for (uint16 i=0; i<500; i++){
						for (uint16 j=0; j<6; j++){
							for (uint16 k=0; k<50; k++){
								l_ListCSV_aa[i][j][k] = '\0';
							}
						}
					}
					g_RowOut_u16 = 0;
					l_RowCSV_u16 = 0; /* count of Row_CSV is returned */
					l_RowTemplate_u16 = 0; /* count of Row_Template is returned */
				}
				else{
					if (l_CheckLinkCSV_u8=='\0'){
						printf("Link CSV is emty\n");
					}
					if (l_CheckLinkTemplate_u8=='\0'){
						printf("Link Template is emty\n");
					}
					if (l_CheckLinkOut_u8=='\0'){
						printf("Link Out is emty\n");
					}
				}
				break;
			}
			case 3:{
				printf("-----Exit-----\n");
				break;
			}
			default:{
				printf("Chose Fail, please chose menu again\n");
				break;
			}
		}
	}
	
	return 0;
}

/* Compare length and char 2 Strings */
int Com_CompareStrings(char l_Str1_aa[10], char l_Str2_aa[10]) {
    uint16 f_I_u16 = 0;
    while (l_Str1_aa[f_I_u16] && l_Str2_aa[f_I_u16]) { /* check if both 2 strings still have char or not */
        if (l_Str1_aa[f_I_u16] < l_Str2_aa[f_I_u16]) return -1;
        if (l_Str1_aa[f_I_u16] > l_Str2_aa[f_I_u16]) return 1;
        f_I_u16++;
    }
    if (l_Str1_aa[f_I_u16]) return 1; /* Str1 has char, but Str2 is not (all of chars before is same) */
    if (l_Str2_aa[f_I_u16]) return -1; /* Str2 has char, but Str1 is not (all of chars before is same) */
    return 0; /* Str1 is same Str2 altogether (all of chars before is same) */
}

/* Convert text in hex type to Interger */
int Com_ConvertCharHexToInt(char l_Input_aa[11]){
	char const f_HexModel_aa[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
	
	char f_ArrayTemp_aa[8]; /*hex in 32bit have 8 char maximum*/
	uint16 f_N_u16 = 0;
	uint16 f_M_u16 = 0;
	uint32 f_IntTemp_u32 = 0;
	uint32 f_IntReturn_u32 = 0;
	
	for (int i=0; i<8; i++){
		f_ArrayTemp_aa[i] = '\0';
	}
	
	while (l_Input_aa[f_N_u16] != '@'){
		if (l_Input_aa[f_N_u16] == 'x'){
			f_M_u16 = 0;
			while (l_Input_aa[f_N_u16+1] && (l_Input_aa[f_N_u16+1] != '@')){
				f_ArrayTemp_aa[f_M_u16] = l_Input_aa[f_N_u16+1];
				f_M_u16++;
				f_N_u16++;
			}
			break;
		}
		f_N_u16++;
	}
	
	f_N_u16 = 0;
	while (f_ArrayTemp_aa[f_N_u16]){
		f_M_u16 = 0;
		f_IntTemp_u32 = 0;
		while ( (f_ArrayTemp_aa[f_N_u16] != f_HexModel_aa[f_M_u16]) && (f_M_u16<=15) ){
			f_IntTemp_u32++;
			f_M_u16++;
		}
		f_IntReturn_u32 = (f_IntReturn_u32<<4);
		f_IntReturn_u32 |= f_IntTemp_u32;
		f_N_u16++;
	}
	
	return f_IntReturn_u32;
}

/* Convert Unsigned Interger to Chars*/
void Com_ConvertUInt32ToChar(uint32 l_Input_u32){
	uint8 f_Temp_u8 = 2;
	
	/* setup 	g_UInt32ToChar_aa[3] = "000" */
	for (int i=0; i<3; i++){
		g_UInt32ToChar_aa[i] = '0';
	}
	f_Temp_u8 = 2;
	
	while ((l_Input_u32 > 0) && (f_Temp_u8>=0)){
		g_UInt32ToChar_aa[f_Temp_u8] = (l_Input_u32%10) + 48;
		l_Input_u32 /= 10;
		f_Temp_u8--;
	}
}

/* Check Key */
int Com_CompareKey(char l_Compare_aa[5]){
	char f_Start_aa[] = "<[-->";
	char f_End_aa[] = "<--]>";
	char f_Now_aa[] = "<NOW>";
	char f_Msn_aa[] = "<MSN>";
	char f_BaseAdress_aa[] = "<B_A>";
	char f_Reg_aa[] = "<REG>";
	char f_Stt_aa[] = "<STT>";
	/*char f_Num_aa[] = "<NUM>";*/
	
	if (Com_CompareStrings(l_Compare_aa, f_Start_aa) == 0){
		return 1;
	}
	else if ((Com_CompareStrings(l_Compare_aa, f_End_aa) == 0)){
		return 2;
	}
	else if ((Com_CompareStrings(l_Compare_aa, f_Now_aa) == 0)){
		return 3;
	}
	else if ((Com_CompareStrings(l_Compare_aa, f_Msn_aa) == 0)){
		return 4;
	}
	else if ((Com_CompareStrings(l_Compare_aa, f_BaseAdress_aa) == 0)){
		return 5;
	}
	else if ((Com_CompareStrings(l_Compare_aa, f_Reg_aa) == 0)){
		return 6;
	}
	else if ((Com_CompareStrings(l_Compare_aa, f_Stt_aa) == 0)){
		return 7;
	}
	/*else if ((Com_CompareStrings(l_Compare_aa, f_Num_aa) == 0)){
		return 8;
	}*/
	return 0;
}

/* Get Time Now */
void Com_GetTimeNow(){
	uint32 f_Year_u32 = 0;
	uint32 f_Mon_u32 = 0;
	uint32 f_Day_u32 = 0;
	uint32 f_Hour_u32 = 0;
	uint32 f_Min_u32 = 0;
	uint32 f_Sec_u32 = 0;
	time_t timeNow = time(NULL);
	tm *f_T_ptr = localtime(&timeNow);
	
	f_Year_u32 = ((f_T_ptr->tm_year)+1900) % 100;
	f_Mon_u32 = (f_T_ptr->tm_mon)+1;
	f_Day_u32 = f_T_ptr->tm_mday;
	f_Hour_u32 = f_T_ptr->tm_hour;
	f_Min_u32 = f_T_ptr->tm_min;
	f_Sec_u32 = f_T_ptr->tm_sec;
	
	Com_ConvertUInt32ToChar(f_Year_u32);
	for (uint8 i=0; i<2; i++){
		g_TimeNow_aa[i] = g_UInt32ToChar_aa[i];
	}
	g_TimeNow_aa[2] = '/';
	Com_ConvertUInt32ToChar(f_Mon_u32);
	for (uint8 i=0; i<2; i++){
		g_TimeNow_aa[i+3] = g_UInt32ToChar_aa[i];
	}
	g_TimeNow_aa[5] = '/';
	Com_ConvertUInt32ToChar(f_Day_u32);
	for (uint8 i=0; i<2; i++){
		g_TimeNow_aa[i+6] = g_UInt32ToChar_aa[i];
	}
	g_TimeNow_aa[8] = ' ';
	g_TimeNow_aa[9] = '-';
	g_TimeNow_aa[10] = ' ';
	Com_ConvertUInt32ToChar(f_Hour_u32);
	for (uint8 i=0; i<2; i++){
		g_TimeNow_aa[i+11] = g_UInt32ToChar_aa[i];
	}
	g_TimeNow_aa[13] = ':';
	Com_ConvertUInt32ToChar(f_Min_u32);
	for (uint8 i=0; i<2; i++){
		g_TimeNow_aa[i+14] = g_UInt32ToChar_aa[i];
	}
	g_TimeNow_aa[16] = ':';
	Com_ConvertUInt32ToChar(f_Sec_u32);
	for (uint8 i=0; i<2; i++){
		g_TimeNow_aa[i+17] = g_UInt32ToChar_aa[i];
	}
	g_TimeNow_aa[19] = '\n';
}

/* Process MSN -> Return a count of Line which MSN using */
void Com_ProcessMSN(char l_CSV_aa[500][6][50], uint16 l_RowCSV_u16, char l_Template_aa[200][200], uint16 l_RowTemplate_u16, char l_ListMSN_aa[300][200], uint16 l_LineMSN_aa[3]){
	uint16 f_N_u16 = 0;
	uint16 f_M_u16 = 0;
	uint16 f_LoopMsn_u16 = 0;
	uint16 f_CSVChar_u16 = 0;
	uint16 f_TemplateLineUse_u16 = 0;
	uint16 f_TemplateChar_u16 = 0;
	uint16 f_OutChar_u16 = 0;
	
	uint32 f_OffsetPre_u32 = 0;
	uint32 f_OffsetNow_u32 = 0;
	uint8 f_ModeStruct_u8 = 0;
	
	char f_CheckKey_aa[] = "12345";
	char f_DummyStt_aa[] = {48, 48}; /* int 48->57 ~ char 0->9 int /// maximum numbers of perpherial is 100 (00->99) */
	char f_DummyCh_c = 48;
	char f_DummyDv_c = 48;
	
	uint16 f_PeripheralCheck_aa[30][2]; /* Peripheral position (Row) : a mount of Peripheral Register */
	
	/* Reset l_MSN_aa[300][200] */
	for (uint16 i=0; i<300; i++){
		for (uint16 j=0; j<200; j++){
			l_ListMSN_aa[i][j] = '\0';
		}
	}
	
	/* Reset for f_PeripheralCheck_aa[30][2] */
	for (uint16 i=0; i<30; i++){
		for (uint16 j=0; j<2; j++){
			f_PeripheralCheck_aa[i][j] = '\0';
		}
	}
	
	/* determine looping and save position and amount of MSN */
	f_N_u16 = 0;
	f_LoopMsn_u16 = 0;
	for (uint16 i=1; i<l_RowCSV_u16; i++){ /* First Row is Topic, not use */
		if (l_CSV_aa[i][1][0] != '@'){
			f_PeripheralCheck_aa[f_N_u16][0] = i;
			f_M_u16 = 0;
			for (uint16 j=i+1; j<l_RowCSV_u16; j++){
				if (l_CSV_aa[j][0][0] != '@'){
					break;
				}
				f_M_u16++;
			}
			f_PeripheralCheck_aa[f_N_u16][1] = f_M_u16 + 1; /* +1 Because in Peripheral Row have also a Register */
			f_N_u16++;
			f_LoopMsn_u16++; /* Loop of MSN */
		}
	}
	for (uint16 i=0; i<30; i++){
		for (uint16 j=0; j<2; j++){
			printf("i-j (%d - %d): %d\n",i, j, f_PeripheralCheck_aa[i][j]);
		}
	}
	printf("f_LoopMsn_u16: %d\n", f_LoopMsn_u16);
	
	/* Processing: Remove to <[--> to determine LineStart and LineEnd of the replacing content in template */
	f_CSVChar_u16 = 0;
	f_TemplateChar_u16 = 0;
	f_OutChar_u16 = 0;
	for (uint16 i=0; i<l_RowTemplate_u16; i++){
		f_CSVChar_u16 = 0;
		f_TemplateChar_u16 = 0;
		f_OutChar_u16 = 0;
		while (l_Template_aa[i][f_TemplateChar_u16]){
			if (l_Template_aa[i][f_TemplateChar_u16] == '<'){
				for (uint16 check=0; check<5; check++){
					f_CheckKey_aa[check] = l_Template_aa[i][f_TemplateChar_u16+check];
				}
				if (Com_CompareKey(f_CheckKey_aa) == 1){
					l_LineMSN_aa[0] = i-1;
				}
				if (Com_CompareKey(f_CheckKey_aa) == 2){
					l_LineMSN_aa[1] = i+1;
					break;
				}
			}
			f_TemplateChar_u16++;
		}
	}
	
	/* Replace content _ include 2 part: 
				part 1 is replacing content of template 
				part 2 is creating register and dummy */
	l_LineMSN_aa[2] = 0; /* oversee Line which l_ListMSN_aa using */
	for (uint16 loop=0; loop<f_LoopMsn_u16; loop++){
		f_DummyCh_c = 48;
		f_DummyDv_c = 48;
		for (uint16 i=(l_LineMSN_aa[0]+2); i<=(l_LineMSN_aa[1]-2); i++){
			if (i == (l_LineMSN_aa[0]+2+2)){
				f_ModeStruct_u8 = 1;
				goto indexStruct;
			}
			else {
				f_ModeStruct_u8 = 0;
			}
			f_CSVChar_u16 = 0;
			f_TemplateChar_u16 = 0;
			f_OutChar_u16 = 0;
			while (l_Template_aa[i][f_TemplateChar_u16]){
				if (l_Template_aa[i][f_TemplateChar_u16] == '<'){
					for (uint16 check=0; check<5; check++){
						f_CheckKey_aa[check] = l_Template_aa[i][f_TemplateChar_u16+check];
					}
					if (Com_CompareKey(f_CheckKey_aa) == 4){
						while (l_CSV_aa[(f_PeripheralCheck_aa[loop][0])][1][f_CSVChar_u16] != '@'){ 
							l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16] = l_CSV_aa[(f_PeripheralCheck_aa[loop][0])][1][f_CSVChar_u16];
							f_OutChar_u16++;
							f_CSVChar_u16++;
							goto indexKey1;
						}
						f_CSVChar_u16 = 0; 
						f_TemplateChar_u16 += 5; /* Remove 5 char CheckKey "<MSN>" */
					}
					if (Com_CompareKey(f_CheckKey_aa) == 5){
						while (l_CSV_aa[(f_PeripheralCheck_aa[loop][0])][0][f_CSVChar_u16] != '@'){ 
							l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16] = l_CSV_aa[(f_PeripheralCheck_aa[loop][0])][0][f_CSVChar_u16];
							f_OutChar_u16++;
							f_CSVChar_u16++;
							goto indexKey1;
						}
						f_CSVChar_u16 = 0;
						f_TemplateChar_u16 += 5; /* Remove 5 char CheckKey "<B_A>" */
					}
				}
				l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16] = l_Template_aa[i][f_TemplateChar_u16];
				f_OutChar_u16++;
				f_TemplateChar_u16++;
				indexKey1:;
			}
			l_LineMSN_aa[2]++;
			indexStruct:;
			if (f_ModeStruct_u8 != 0){
				f_OffsetPre_u32 = 0;
				f_OffsetNow_u32 = 0;
				for (uint32 nums=f_PeripheralCheck_aa[loop][0]; nums < (f_PeripheralCheck_aa[loop][0]+f_PeripheralCheck_aa[loop][1]); nums++){
					f_OffsetPre_u32 = f_OffsetNow_u32;
					f_OffsetNow_u32 = Com_ConvertCharHexToInt(l_CSV_aa[nums][2]);
					
					if ( (((f_OffsetNow_u32-f_OffsetPre_u32)>0)&&(nums==f_PeripheralCheck_aa[loop][0])) || (((f_OffsetNow_u32-f_OffsetPre_u32>4))&&(nums>f_PeripheralCheck_aa[loop][0])) ){
						f_CSVChar_u16 = 0;
						f_TemplateChar_u16 = 0;
						f_OutChar_u16 = 0;
						while (l_Template_aa[l_LineMSN_aa[0]+2+4][f_TemplateChar_u16]){
							if (l_Template_aa[l_LineMSN_aa[0]+2+4][f_TemplateChar_u16] == '<'){
								for (uint16 check=0; check<5; check++){
									f_CheckKey_aa[check] = l_Template_aa[l_LineMSN_aa[0]+2+4][f_TemplateChar_u16+check];
								}
								if (Com_CompareKey(f_CheckKey_aa) == 7){
									l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16] = f_DummyCh_c;
									l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+1] = f_DummyDv_c;
									f_DummyDv_c++;
									if (f_DummyDv_c > 57){
										f_DummyDv_c = 48;
										f_DummyCh_c++;
										if (f_DummyCh_c > 57){
											f_DummyCh_c = 48;
											printf(" Dummy Maximum \n");
										}
									}
									f_TemplateChar_u16 += 5; /* Remove 5 char CheckKey "<STT>" */
									l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+2] = '[';
									if (nums==f_PeripheralCheck_aa[loop][0]){ /* if first Offset is not 0x00 */
										Com_ConvertUInt32ToChar((f_OffsetNow_u32-f_OffsetPre_u32)/4);
									}
									else{
										Com_ConvertUInt32ToChar((f_OffsetNow_u32-f_OffsetPre_u32-4)/4);
									}
									if (g_UInt32ToChar_aa[0] == '0'){ /* delete the abadon 0 number */
										if (g_UInt32ToChar_aa[1] == '0'){ /* delete the abadon 0 number */
											f_OutChar_u16 -= 2;
											l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+5] = g_UInt32ToChar_aa[2];
										}
										else{
											f_OutChar_u16--;
											l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+4] = g_UInt32ToChar_aa[1];
											l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+5] = g_UInt32ToChar_aa[2];
										}
									}
									else{
										l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+3] = g_UInt32ToChar_aa[0];
										l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+4] = g_UInt32ToChar_aa[1];
										l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+5] = g_UInt32ToChar_aa[2];
									}
									l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+6] = ']';
									l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+7] = ';';
									l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16+8] = '\n';
									l_LineMSN_aa[2]++;
									
									goto indexKey2;
								}
							}
							l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16] = l_Template_aa[l_LineMSN_aa[0]+2+4][f_TemplateChar_u16];
							f_OutChar_u16++;
							f_TemplateChar_u16++;
						}
						
					}
					else if ( ((f_OffsetNow_u32-f_OffsetPre_u32==0)&&(nums==f_PeripheralCheck_aa[loop][0])) || ((f_OffsetNow_u32-f_OffsetPre_u32==4)&&(nums>f_PeripheralCheck_aa[loop][0])) ){
						indexKey2:; /* dummy and a line Register  */
						f_CSVChar_u16 = 0;
						f_TemplateChar_u16 = 0;
						f_OutChar_u16 = 0;
						if (l_CSV_aa[nums][5][0] == '1'){ /* '1' is RO */
							while (l_Template_aa[l_LineMSN_aa[0]+2+2][f_TemplateChar_u16]){
								if (l_Template_aa[l_LineMSN_aa[0]+2+2][f_TemplateChar_u16] == '<'){
									for (uint16 check=0; check<5; check++){
										f_CheckKey_aa[check] = l_Template_aa[l_LineMSN_aa[0]+2+2][f_TemplateChar_u16+check];
									}
									if (Com_CompareKey(f_CheckKey_aa) == 6){
										while (l_CSV_aa[nums][3][f_CSVChar_u16] != '@'){ 
											l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16] = l_CSV_aa[nums][3][f_CSVChar_u16];
											f_OutChar_u16++;
											f_CSVChar_u16++;
											goto indexKey3;
										}
										f_CSVChar_u16 = 0; 
										f_TemplateChar_u16 += 5; /* Remove 5 char CheckKey "<REG>" */
									}
								}
								l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16] = l_Template_aa[l_LineMSN_aa[0]+2+2][f_TemplateChar_u16];
								f_OutChar_u16++;
								f_TemplateChar_u16++;
								indexKey3:;
							}
						}
						if (l_CSV_aa[nums][5][0] == '2'){ /* '2' is Others */
							while (l_Template_aa[l_LineMSN_aa[0]+2+3][f_TemplateChar_u16]){
								if (l_Template_aa[l_LineMSN_aa[0]+2+3][f_TemplateChar_u16] == '<'){
									for (uint16 check=0; check<5; check++){
										f_CheckKey_aa[check] = l_Template_aa[l_LineMSN_aa[0]+2+3][f_TemplateChar_u16+check];
									}
									if (Com_CompareKey(f_CheckKey_aa) == 6){
										while (l_CSV_aa[nums][3][f_CSVChar_u16] != '@'){ 
											l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16] = l_CSV_aa[nums][3][f_CSVChar_u16];
											f_OutChar_u16++;
											f_CSVChar_u16++;
											goto indexKey4;
										}
										f_CSVChar_u16 = 0; 
										f_TemplateChar_u16 += 5; /* Remove 5 char CheckKey "<REG>" */
									}
								}
								l_ListMSN_aa[l_LineMSN_aa[2]][f_OutChar_u16] = l_Template_aa[l_LineMSN_aa[0]+2+3][f_TemplateChar_u16];
								f_OutChar_u16++;
								f_TemplateChar_u16++;
								indexKey4:;
							}
						}
						l_LineMSN_aa[2]++;
					}
				}
				i = l_LineMSN_aa[0]+2+2+2; /* Write continue after "........." in template */
			}
			
		}
		l_ListMSN_aa[l_LineMSN_aa[2]][0] = '\n'; /* Increase a line to nice */
		l_LineMSN_aa[2]++; /* Increase a line to nice */
	}
	
	printf("------ListOut_Check-----\n");
	int n=0;
	for (int i=0; i<l_LineMSN_aa[2]; i++){
		printf("Line %d: ", i);
		int n=0;
		while (l_ListMSN_aa[i][n] != '\0'){
			printf("%c", l_ListMSN_aa[i][n]);
			n++;
		}
	}
	printf("\n");
	printf("LineStart: %d\n", l_LineMSN_aa[0]);
	printf("LineEnd: %d\n", l_LineMSN_aa[1]);
	printf("LineUse: %d\n", l_LineMSN_aa[2]);
}

/* Process ListOut */
void Com_ProcessListOut(char l_Template_aa[200][200], uint16 l_RowTemplate_u16, char l_ListMSN_aa[300][200], uint16 l_LineMSN_aa[3]){
	uint16 f_N_u16 = 0;
	uint16 f_M_u16 = 0;
	uint16 f_CSVChar_u16 = 0;
	uint16 f_TemplateLineUse_u16 = 0;
	uint16 f_TemplateChar_u16 = 0;
	uint16 f_OutLineUse_u16 = 0;
	uint16 f_OutChar_u16 = 0;
		
	char f_CheckKey_aa[5];
	
	/* the start of l_Template_aa */
	f_CSVChar_u16 = 0;
	f_TemplateChar_u16 = 0;
	f_OutChar_u16 = 0;
	f_OutLineUse_u16 = 0;
	for (uint16 i=0; i<l_LineMSN_aa[0]; i++){
		f_CSVChar_u16 = 0;
		f_TemplateChar_u16 = 0;
		f_OutChar_u16 = 0;
		while (l_Template_aa[i][f_TemplateChar_u16]){
			if (l_Template_aa[i][f_TemplateChar_u16] == '<'){
				for (int check=0; check<5; check++){
					f_CheckKey_aa[check] = l_Template_aa[i][f_TemplateChar_u16+check];
				}
				if (Com_CompareKey(f_CheckKey_aa) == 3){
					Com_GetTimeNow();
					for (uint8 t=0; t<19; t++){
						g_ListOut_aa[i][f_OutChar_u16] = g_TimeNow_aa[t];
						f_OutChar_u16++;
					}
					g_ListOut_aa[i][f_OutChar_u16] = '\n';
					break;
				}
			}
			g_ListOut_aa[i][f_OutChar_u16] = l_Template_aa[i][f_TemplateChar_u16];
			f_OutChar_u16++;
			f_TemplateChar_u16++;
		}
	}
	
	/* combine l_ListMSN_aa */
	g_ListOut_aa[l_LineMSN_aa[0]][0] = '\n'; /* create space line to nice */
	g_ListOut_aa[l_LineMSN_aa[0]+1][0] = '\n'; /* create space line to nice */
	f_N_u16 = 0;
	for (uint16 i=(l_LineMSN_aa[0]+2); i<(l_LineMSN_aa[0]+l_LineMSN_aa[2]+2); i++){
		f_M_u16 = 0;
		f_OutChar_u16 = 0;
		while (l_ListMSN_aa[f_N_u16][f_M_u16]){
			g_ListOut_aa[i][f_OutChar_u16] = l_ListMSN_aa[f_N_u16][f_M_u16];
			f_M_u16++;
			f_OutChar_u16++;
		}
		f_N_u16++;
	}
	
	/* combine the end of l_Template_aa */
	f_N_u16 = 0;
	for (uint16 i=l_LineMSN_aa[1]; i<(l_RowTemplate_u16-1); i++){ /* -1 because remove EOF,,,,,, */
		f_M_u16 = 0;
		f_OutChar_u16 = 0;
		while (l_Template_aa[i][f_M_u16]){
			g_ListOut_aa[(l_LineMSN_aa[0] + l_LineMSN_aa[2] + f_N_u16)][f_OutChar_u16] = l_Template_aa[i][f_M_u16];
			f_M_u16++;
			f_OutChar_u16++;
		}
		f_N_u16++;
	}
	g_RowOut_u16 = l_LineMSN_aa[0] + l_LineMSN_aa[2] + f_N_u16;
	
	printf("------ListOut_Check-----\n");
	int n=0;
	for (uint16 i=0; i<g_RowOut_u16; i++){
		printf("Line %d: ", i);
		int n=0;
		while (g_ListOut_aa[i][n] != '\0'){
			printf("%c", g_ListOut_aa[i][n]);
			n++;
		}
	}
	printf("\n");
}

/* Arrange and save the data of g_ListTemp_aa[][] in l_ListCSV_aa[][][] */
void Com_SaveListCSV(char l_ListStore_aa[500][6][50], uint16 l_Row_u16){
	uint16 f_N_u16 = 0;
	uint16 f_M_u16 = 0;
	uint16 f_O_u16 = 0;
	
	char f_Access_aa[] = "12";
	char f_RO_aa[] = "RO"; /* 1 */
	char f_RW_aa[] = "RW"; /* 2 */
	char f_WO_aa[] = "WO"; /* 3 */
	
	/* set up emty for l_ListStore_aa[500][6][50] */
	for (int i=0; i<500; i++){
		for (int j=0; j<6; j++){
			for (int k=0; k<50; k++){
				l_ListStore_aa[i][j][k] = '\0';
			}
		}
	}
	
	/* Arrange the data get by g_ListTemp_aa[][] */
	for (int i=0; i<l_Row_u16; i++){ 
		uint16 f_N_u16 = 0; /* f_N_u16 is char in a line of g_ListTemp_aa[][] */
		uint16 f_M_u16 = 0; /* f_M_u16 is char in a box of l_ListStore_aa[][][] */
		uint16 f_O_u16 = 0; /* f_O_u16 on behalf of column */
		while (g_ListTemp_aa[i][f_N_u16] != '\n'){ /* ex: string ", ,ab,cd " is save as "@"; " @"; "ab@";  "cd @" */
			if (g_ListTemp_aa[i][f_N_u16] == ','){
				l_ListStore_aa[i][f_O_u16][f_M_u16] = '@';
				f_M_u16 = 0;
				f_O_u16++; 
			}
			else{
				l_ListStore_aa[i][f_O_u16][f_M_u16] = g_ListTemp_aa[i][f_N_u16];
				f_M_u16++;
			}
			f_N_u16++;
		}
		l_ListStore_aa[i][f_O_u16][f_M_u16] = '@'; /* end char is '\n' replaced by '@' */
	}
	
	
	for (int i=1; i<l_Row_u16; i++){
		f_Access_aa[0] = l_ListStore_aa[i][5][0];
		f_Access_aa[1] = l_ListStore_aa[i][5][1];
		if (Com_CompareStrings(f_Access_aa, f_RO_aa) == 0){
			l_ListStore_aa[i][5][0] = '1';
			l_ListStore_aa[i][5][1] = '@';
		}
		else{
			l_ListStore_aa[i][5][0] = '2';
			l_ListStore_aa[i][5][1] = '@';
		}
		/*
		if (Com_CompareStrings(f_Access_aa, f_RW_aa) == 0){
			l_ListStore_aa[i][5][0] = '2';
			l_ListStore_aa[i][5][1] = '@';
		}
		if (Com_CompareStrings(f_Access_aa, f_WO_aa) == 0){
			l_ListStore_aa[i][5][0] = '3';
			l_ListStore_aa[i][5][1] = '@';
		}
		*/
	}
	
	/* printf check list_store */
	for (int i=0; i<l_Row_u16; i++){
		for (int j=0; j<6; j++){
			printf("i-j (%d-%d): ", i, j);
			for (int k=0; k<500; k++){
				printf("%c", l_ListStore_aa[i][j][k]);
				if (l_ListStore_aa[i][j][k] == '@'){
					break;
				}
			}
			printf("\n");
		}
	}
}

/* Save the data of g_ListTemp_aa[][] in l_ListTemplate_aa[][] */
void Com_SaveListTemplate(char l_ListStore_aa[200][200], uint16 l_Row_u16){
	uint16 f_N_u16 = 0;
	
	/* set up emty for l_ListStore_aa[200][200] */
	for (int i=0; i<200; i++){
		for (int j=0; j<200; j++){
			l_ListStore_aa[i][j] = '\0';
		}	
	}
	
	/* copy data from g_ListTemp_aa[][] to l_ListStore_aa[][] */
	for (int i=0; i<l_Row_u16; i++){
		f_N_u16 = 0;
		printf("line %d: ", i);
		while (g_ListTemp_aa[i][f_N_u16]){
			l_ListStore_aa[i][f_N_u16] = g_ListTemp_aa[i][f_N_u16];
			printf("%c", l_ListStore_aa[i][f_N_u16]);
			f_N_u16++;
		}
	}
}

/* Get data from file and save in Temp_Variable (text) */
void Get_InfoToTemp(char l_Link_aa[200], uint16* l_Row_u16){
	FILE* f_File_ptr;
	char f_Str_aa[200];

	uint16 f_N_u16 = 0; /* oversee char in line */
	
	/* set up emty for g_ListTemp_aa[200][200] */
	for (int i=0; i<500; i++){
		for (int j=0; j<200; j++){
			g_ListTemp_aa[i][j] = '\0';
		}	
	}
	
	/* set up emty for temp_array in function */
	for (int i=0; i<200; i++){
		f_Str_aa[i] = '\0';
	}
	
	/*---------Read and process data of file--------------------------------	
	  open file ("r" is read mode)
	  "csv" is "excel" file read in "open with notepad" mode */
	f_File_ptr = fopen(l_Link_aa, "r"); 
	
	/* Check to Interact fail or succesful (Pointer is not NULL opening succesful file) */
	if (f_File_ptr == NULL){
		printf("Fail !!\n-----------------\n");
	}
	printf("Interact file succesful\n-----------------\n");
	
	/* save string as g_ListTemp_aa[200][200] de tien tuong tac */
	*l_Row_u16 = 0;
	while (Com_CompareStrings(f_Str_aa, g_EndLine_aa) != 0){
		fgets(f_Str_aa, 200, f_File_ptr); /* 200 is maximum char in a line (we want to that) */
		printf("line %d ", *l_Row_u16);
		printf("String is get: %s\n", f_Str_aa);
		f_N_u16 = 0;
		while (f_Str_aa[f_N_u16] != '\0'){ 
			g_ListTemp_aa[*l_Row_u16][f_N_u16] = f_Str_aa[f_N_u16];
			f_N_u16++;
		}
		(*l_Row_u16)++; 	
	}
	
	printf("row: %d\n\n", *l_Row_u16); 
	
	/* close file */
	fclose(f_File_ptr);
}

/* Get link */
void Get_InputLink(char l_LinkFile_aa[200]){
	uint8 f_Nums_u8 = 0;
	
	/* Reset l_LinkFile_aa */
	for (uint8 i=0; i<200; i++){
		l_LinkFile_aa[i] = '\0';
	}
	printf("Input Link_String: \n");
	gets(l_LinkFile_aa);
	
	printf("String is get:  %s\nPlease enter to continue!\n", l_LinkFile_aa);
	getchar();//de khong bi nhay chuoi
}

/* Export Data to File */
void Export_DataToFile(char l_Link_aa[200]){
	FILE* f_File_ptr;
	
	/*---------Read and process data of file--------------------------------	
	  open file ("w" is write mode)
	  "csv" is "excel" file read in "open with notepad" mode */
	f_File_ptr = fopen(l_Link_aa, "w");
	if (f_File_ptr == NULL){
		printf("Fail !!\n-----------------\n");
	}
	printf("Interact file succesful\n-----------------\n");

	/* Export data to file */
	for (uint16 i=0; i<g_RowOut_u16; i++){
		fputs(g_ListOut_aa[i], f_File_ptr);
	}
	
	/* close file */
	fclose(f_File_ptr);
}

