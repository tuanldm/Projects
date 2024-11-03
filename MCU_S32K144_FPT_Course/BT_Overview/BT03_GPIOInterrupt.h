#ifndef BT03_H
#define BT03_H

#include "GPIO_Type.h"
#include "PCC_Type.h"
#include "PORT_Type.h"

extern unsigned char g_StatusBT03Ex2_u8;
extern unsigned char g_StatusBT03Ex3_u8;
extern unsigned char g_StatusBT03Ex4_u8;
extern unsigned char g_StatusBT03Ex5_u8;

void BT03_Ex2(void)__attribute__ ((noreturn)); /* Press PTC12 then PTD15 light, Release PTC12 then PTD15 off */
void BT03_Ex3(void)__attribute__ ((noreturn)); /* Press PTC12 then PTD0 light, Press PTC13 then PTD0 off */
void BT03_Ex4(void)__attribute__ ((noreturn)); /* PTC12 control Led PTD16 (press to toggle status) */ 
void BT03_Ex5(void)__attribute__ ((noreturn)); /* PTC12 make PTD16 flash about 5HZ, PTC13 make PTD16 always light */
void test_priority(void)__attribute__ ((noreturn));

#endif /* BT03_H */
