/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 02/01/03 - 01:00:01
**
**     Abstract:
**         Peripheral Access Layer for S32K144
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#ifndef LPSPI_TYPE_H_  /* Check if memory map has not been already included */
#define LPSPI_TYPE_H_  

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */


/* LPSPI0 */
typedef struct {
  volatile const unsigned int LPSPI_VERID;
  volatile const unsigned int LPSPI_PARAM;
  unsigned int                dummy_00[2];
  volatile unsigned int       LPSPI_CR;
  volatile unsigned int       LPSPI_SR;
  volatile unsigned int       LPSPI_IER;
  volatile unsigned int       LPSPI_DER;
  volatile unsigned int       LPSPI_CFGR0;
  volatile unsigned int       LPSPI_CFGR1;
  unsigned int                dummy_01[2];
  volatile unsigned int       LPSPI_DMR0;
  volatile unsigned int       LPSPI_DMR1;
  unsigned int                dummy_02[2];
  volatile unsigned int       LPSPI_CCR;
  unsigned int                dummy_03[5];
  volatile unsigned int       LPSPI_FCR;
  volatile const unsigned int LPSPI_FSR;
  volatile unsigned int       LPSPI_TCR;
  volatile unsigned int       LPSPI_TDR;
  unsigned int                dummy_04[2];
  volatile const unsigned int LPSPI_RSR;
  volatile const unsigned int LPSPI_RDR;
} LPSPI0_Type;

#define LPSPI0_BASE_ADDRS (0x4002C000) /* Base Address */
#define LPSPI0 ((LPSPI0_Type*)LPSPI0_BASE_ADDRS)


/* LPSPI1 */
typedef struct {
  volatile const unsigned int LPSPI_VERID;
  volatile const unsigned int LPSPI_PARAM;
  unsigned int                dummy_00[2];
  volatile unsigned int       LPSPI_CR;
  volatile unsigned int       LPSPI_SR;
  volatile unsigned int       LPSPI_IER;
  volatile unsigned int       LPSPI_DER;
  volatile unsigned int       LPSPI_CFGR0;
  volatile unsigned int       LPSPI_CFGR1;
  unsigned int                dummy_01[2];
  volatile unsigned int       LPSPI_DMR0;
  volatile unsigned int       LPSPI_DMR1;
  unsigned int                dummy_02[2];
  volatile unsigned int       LPSPI_CCR;
  unsigned int                dummy_03[5];
  volatile unsigned int       LPSPI_FCR;
  volatile const unsigned int LPSPI_FSR;
  volatile unsigned int       LPSPI_TCR;
  volatile unsigned int       LPSPI_TDR;
  unsigned int                dummy_04[2];
  volatile const unsigned int LPSPI_RSR;
  volatile const unsigned int LPSPI_RDR;
} LPSPI1_Type;

#define LPSPI1_BASE_ADDRS (0x4002D000) /* Base Address */
#define LPSPI1 ((LPSPI1_Type*)LPSPI1_BASE_ADDRS)


/* LPSPI2 */
typedef struct {
  volatile const unsigned int LPSPI_VERID;
  volatile const unsigned int LPSPI_PARAM;
  unsigned int                dummy_00[2];
  volatile unsigned int       LPSPI_CR;
  volatile unsigned int       LPSPI_SR;
  volatile unsigned int       LPSPI_IER;
  volatile unsigned int       LPSPI_DER;
  volatile unsigned int       LPSPI_CFGR0;
  volatile unsigned int       LPSPI_CFGR1;
  unsigned int                dummy_01[2];
  volatile unsigned int       LPSPI_DMR0;
  volatile unsigned int       LPSPI_DMR1;
  unsigned int                dummy_02[2];
  volatile unsigned int       LPSPI_CCR;
  unsigned int                dummy_03[5];
  volatile unsigned int       LPSPI_FCR;
  volatile const unsigned int LPSPI_FSR;
  volatile unsigned int       LPSPI_TCR;
  volatile unsigned int       LPSPI_TDR;
  unsigned int                dummy_04[2];
  volatile const unsigned int LPSPI_RSR;
  volatile const unsigned int LPSPI_RDR;
} LPSPI2_Type;

#define LPSPI2_BASE_ADDRS (0x4002E000) /* Base Address */
#define LPSPI2 ((LPSPI2_Type*)LPSPI2_BASE_ADDRS)

#endif  /* #if !defined(LPSPI_TYPE_H_) */

