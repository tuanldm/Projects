#ifndef BT02_H
#define BT02_H

#include "GPIO_Type.h"
#include "PCC_Type.h"
#include "PORT_Type.h"

void BT02_Ex1(void)__attribute__ ((noreturn)); /* Toggle led PTD16 */
void BT02_Ex2(void)__attribute__ ((noreturn)); /* Press PTC12 then PTD15 light, Release PTC12 then PTD15 off */
void BT02_Ex3(void)__attribute__ ((noreturn)); /* Press PTC12 then PTD0 light, Press PTC13 then PTD0 off */
void BT02_Ex4(void)__attribute__ ((noreturn)); /* PTC12 control Led PTD16 (press to toggle status) */ 
void BT02_Ex5(void)__attribute__ ((noreturn)); /* PTC12 make PTD16 flash about 5HZ, PTC13 make PTD16 always light */

#endif /* BT02_H */
