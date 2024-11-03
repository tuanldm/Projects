/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 02/01/01 - 02:01:03
**
**     Abstract:
**         Peripheral Access Layer for S32K144
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#ifndef LPUART_TYPE_H_  /* Check if memory map has not been already included */
#define LPUART_TYPE_H_  

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */


/* LPUART0 */
typedef struct {
  volatile const unsigned int LPUART_VERID;
  volatile const unsigned int LPUART_PARAM;
  volatile unsigned int       LPUART_GLOBAL;
  volatile unsigned int       LPUART_PINCFG;
  volatile unsigned int       LPUART_BAUD;
  volatile unsigned int       LPUART_STAT;
  volatile unsigned int       LPUART_CTRL;
  volatile unsigned int       LPUART_DATA;
  volatile unsigned int       LPUART_MATCH;
  volatile unsigned int       LPUART_MODIR;
  volatile unsigned int       LPUART_FIFO;
  volatile unsigned int       LPUART_WATER;
} LPUART0_Type;

#define LPUART0_BASE_ADDRS (0x4006A000) /* Base Address */
#define LPUART0 ((LPUART0_Type*)LPUART0_BASE_ADDRS)


/* LPUART1 */
typedef struct {
  volatile const unsigned int LPUART_VERID;
  volatile const unsigned int LPUART_PARAM;
  volatile unsigned int       LPUART_GLOBAL;
  volatile unsigned int       LPUART_PINCFG;
  volatile unsigned int       LPUART_BAUD;
  volatile unsigned int       LPUART_STAT;
  volatile unsigned int       LPUART_CTRL;
  volatile unsigned int       LPUART_DATA;
  volatile unsigned int       LPUART_MATCH;
  volatile unsigned int       LPUART_MODIR;
  volatile unsigned int       LPUART_FIFO;
  volatile unsigned int       LPUART_WATER;
} LPUART1_Type;

#define LPUART1_BASE_ADDRS (0x4006B000) /* Base Address */
#define LPUART1 ((LPUART1_Type*)LPUART1_BASE_ADDRS)


/* LPUART2 */
typedef struct {
  volatile const unsigned int LPUART_VERID;
  volatile const unsigned int LPUART_PARAM;
  volatile unsigned int       LPUART_GLOBAL;
  volatile unsigned int       LPUART_PINCFG;
  volatile unsigned int       LPUART_BAUD;
  volatile unsigned int       LPUART_STAT;
  volatile unsigned int       LPUART_CTRL;
  volatile unsigned int       LPUART_DATA;
  volatile unsigned int       LPUART_MATCH;
  volatile unsigned int       LPUART_MODIR;
  volatile unsigned int       LPUART_FIFO;
  volatile unsigned int       LPUART_WATER;
} LPUART2_Type;

#define LPUART2_BASE_ADDRS (0x4006C000) /* Base Address */
#define LPUART2 ((LPUART2_Type*)LPUART2_BASE_ADDRS)

#endif  /* #if !defined(LPUART_TYPE_H_) */

