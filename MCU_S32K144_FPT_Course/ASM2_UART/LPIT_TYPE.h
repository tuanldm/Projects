/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 23/10/07 - 20:33:23
**
**     Abstract:
**         Peripheral Access Layer for S32K144
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#ifndef LPIT_TYPE_H_  /* Check if memory map has not been already included */
#define LPIT_TYPE_H_  

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */


/* LPIT */
typedef struct {
  volatile const unsigned int LPIT_VERID;
  volatile const unsigned int LPIT_PARAM;
  volatile unsigned int       LPIT_MCR;
  volatile unsigned int       LPIT_MSR;
  volatile unsigned int       LPIT_MIER;
  volatile unsigned int       LPIT_SETTEN;
  volatile unsigned int       LPIT_CLRTEN;
  unsigned int                dummy_00[1];
  volatile unsigned int       LPIT_TVAL0;
  volatile const unsigned int LPIT_CVAL0;
  volatile unsigned int       LPIT_TCTRL0;
  unsigned int                dummy_01[1];
  volatile unsigned int       LPIT_TVAL1;
  volatile const unsigned int LPIT_CVAL1;
  volatile unsigned int       LPIT_TCTRL1;
  unsigned int                dummy_02[1];
  volatile unsigned int       LPIT_TVAL2;
  volatile const unsigned int LPIT_CVAL2;
  volatile unsigned int       LPIT_TCTRL2;
  unsigned int                dummy_03[1];
  volatile unsigned int       LPIT_TVAL3;
  volatile const unsigned int LPIT_CVAL3;
  volatile unsigned int       LPIT_TCTRL3;
} LPIT_Type;

#define LPIT_BASE_ADDRS (0x40037000) /* Base Address */
#define LPIT ((LPIT_Type*)LPIT_BASE_ADDRS)

#endif  /* #if !defined(LPIT_TYPE_H_) */

