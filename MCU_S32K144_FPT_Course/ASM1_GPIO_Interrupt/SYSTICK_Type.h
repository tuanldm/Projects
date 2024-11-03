/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 23/09/26 - 06:50:36
**
**     Abstract:
**         Peripheral Access Layer for S32K144
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#ifndef SYSTICK_TYPE_H_  /* Check if memory map has not been already included */
#define SYSTICK_TYPE_H_  

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */


/* SYSTICK */
typedef struct {
  volatile unsigned int SYSTICK_CTRL;
  volatile unsigned int SYSTICK_LOAD;
  volatile unsigned int SYSTICK_VAL;
  volatile unsigned int SYSTICK_CALIB;
} SYSTICK_Type;

#define SYSTICK_BASE_ADDRS (0xE000E010) /* Base Address */
#define SYSTICK ((SYSTICK_Type*)SYSTICK_BASE_ADDRS)

#endif  /* #if !defined(SYSTICK_TYPE_H_) */
