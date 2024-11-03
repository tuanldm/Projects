/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 23/09/19 - 14:41:51
**
**     Abstract:
**         Peripheral Access Layer for S32K144
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#ifndef PORT_TYPE_H_  /* Check if memory map has not been already included */
#define PORT_TYPE_H_  

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */


/* PORTA */
typedef struct {
  volatile unsigned int       PORTA_PCR0;
  volatile unsigned int       PORTA_PCR1;
  volatile unsigned int       PORTA_PCR2;
  volatile unsigned int       PORTA_PCR3;
  volatile unsigned int       PORTA_PCR4;
  volatile unsigned int       PORTA_PCR5;
  volatile unsigned int       PORTA_PCR6;
  volatile unsigned int       PORTA_PCR7;
  volatile unsigned int       PORTA_PCR8;
  volatile unsigned int       PORTA_PCR9;
  volatile unsigned int       PORTA_PCR10;
  volatile unsigned int       PORTA_PCR11;
  volatile unsigned int       PORTA_PCR12;
  volatile unsigned int       PORTA_PCR13;
  volatile unsigned int       PORTA_PCR14;
  volatile unsigned int       PORTA_PCR15;
  volatile unsigned int       PORTA_PCR16;
  volatile unsigned int       PORTA_PCR17;
  unsigned int                dummy_00[14];
  volatile unsigned int       PORTA_GPCLR;
  volatile unsigned int       PORTA_GPCHR;
  volatile unsigned int       PORTA_GICLR;
  volatile unsigned int       PORTA_GICHR;
  unsigned int                dummy_01[4];
  volatile unsigned int       PORTA_ISFR;
  unsigned int                dummy_02[7];
  volatile unsigned int       PORTA_DFER;
  volatile unsigned int       PORTA_DFCR;
  volatile unsigned int       PORTA_DFWR;
} PORTA_Type;

#define PORTA_BASE_ADDRS (0x40049000) /* Base Address */
#define PORTA ((PORTA_Type*)PORTA_BASE_ADDRS)


/* PORTB */
typedef struct {
  volatile unsigned int       PORTB_PCR0;
  volatile unsigned int       PORTB_PCR1;
  volatile unsigned int       PORTB_PCR2;
  volatile unsigned int       PORTB_PCR3;
  volatile unsigned int       PORTB_PCR4;
  volatile unsigned int       PORTB_PCR5;
  volatile unsigned int       PORTB_PCR6;
  volatile unsigned int       PORTB_PCR7;
  volatile unsigned int       PORTB_PCR8;
  volatile unsigned int       PORTB_PCR9;
  volatile unsigned int       PORTB_PCR10;
  volatile unsigned int       PORTB_PCR11;
  volatile unsigned int       PORTB_PCR12;
  volatile unsigned int       PORTB_PCR13;
  volatile unsigned int       PORTB_PCR14;
  volatile unsigned int       PORTB_PCR15;
  volatile unsigned int       PORTB_PCR16;
  volatile unsigned int       PORTB_PCR17;
  unsigned int                dummy_00[14];
  volatile unsigned int       PORTB_GPCLR;
  volatile unsigned int       PORTB_GPCHR;
  volatile unsigned int       PORTB_GICLR;
  volatile unsigned int       PORTB_GICHR;
  unsigned int                dummy_01[4];
  volatile unsigned int       PORTB_ISFR;
  unsigned int                dummy_02[7];
  volatile unsigned int       PORTB_DFER;
  volatile unsigned int       PORTB_DFCR;
  volatile unsigned int       PORTB_DFWR;
} PORTB_Type;

#define PORTB_BASE_ADDRS (0x4004A000) /* Base Address */
#define PORTB ((PORTB_Type*)PORTB_BASE_ADDRS)


/* PORTC */
typedef struct {
  volatile unsigned int       PORTC_PCR0;
  volatile unsigned int       PORTC_PCR1;
  volatile unsigned int       PORTC_PCR2;
  volatile unsigned int       PORTC_PCR3;
  volatile unsigned int       PORTC_PCR4;
  volatile unsigned int       PORTC_PCR5;
  volatile unsigned int       PORTC_PCR6;
  volatile unsigned int       PORTC_PCR7;
  volatile unsigned int       PORTC_PCR8;
  volatile unsigned int       PORTC_PCR9;
  volatile unsigned int       PORTC_PCR10;
  volatile unsigned int       PORTC_PCR11;
  volatile unsigned int       PORTC_PCR12;
  volatile unsigned int       PORTC_PCR13;
  volatile unsigned int       PORTC_PCR14;
  volatile unsigned int       PORTC_PCR15;
  volatile unsigned int       PORTC_PCR16;
  volatile unsigned int       PORTC_PCR17;
  unsigned int                dummy_00[14];
  volatile unsigned int       PORTC_GPCLR;
  volatile unsigned int       PORTC_GPCHR;
  volatile unsigned int       PORTC_GICLR;
  volatile unsigned int       PORTC_GICHR;
  unsigned int                dummy_01[4];
  volatile unsigned int       PORTC_ISFR;
  unsigned int                dummy_02[7];
  volatile unsigned int       PORTC_DFER;
  volatile unsigned int       PORTC_DFCR;
  volatile unsigned int       PORTC_DFWR;
} PORTC_Type;

#define PORTC_BASE_ADDRS (0x4004B000) /* Base Address */
#define PORTC ((PORTC_Type*)PORTC_BASE_ADDRS)


/* PORTD */
typedef struct {
  volatile unsigned int       PORTD_PCR0;
  volatile unsigned int       PORTD_PCR1;
  volatile unsigned int       PORTD_PCR2;
  volatile unsigned int       PORTD_PCR3;
  volatile unsigned int       PORTD_PCR4;
  volatile unsigned int       PORTD_PCR5;
  volatile unsigned int       PORTD_PCR6;
  volatile unsigned int       PORTD_PCR7;
  volatile unsigned int       PORTD_PCR8;
  volatile unsigned int       PORTD_PCR9;
  volatile unsigned int       PORTD_PCR10;
  volatile unsigned int       PORTD_PCR11;
  volatile unsigned int       PORTD_PCR12;
  volatile unsigned int       PORTD_PCR13;
  volatile unsigned int       PORTD_PCR14;
  volatile unsigned int       PORTD_PCR15;
  volatile unsigned int       PORTD_PCR16;
  volatile unsigned int       PORTD_PCR17;
  unsigned int                dummy_00[14];
  volatile unsigned int       PORTD_GPCLR;
  volatile unsigned int       PORTD_GPCHR;
  volatile unsigned int       PORTD_GICLR;
  volatile unsigned int       PORTD_GICHR;
  unsigned int                dummy_01[4];
  volatile unsigned int       PORTD_ISFR;
  unsigned int                dummy_02[7];
  volatile unsigned int       PORTD_DFER;
  volatile unsigned int       PORTD_DFCR;
  volatile unsigned int       PORTD_DFWR;
} PORTD_Type;

#define PORTD_BASE_ADDRS (0x4004C000) /* Base Address */
#define PORTD ((PORTD_Type*)PORTD_BASE_ADDRS)


/* PORTE */
typedef struct {
  volatile unsigned int       PORTE_PCR0;
  volatile unsigned int       PORTE_PCR1;
  volatile unsigned int       PORTE_PCR2;
  volatile unsigned int       PORTE_PCR3;
  volatile unsigned int       PORTE_PCR4;
  volatile unsigned int       PORTE_PCR5;
  volatile unsigned int       PORTE_PCR6;
  volatile unsigned int       PORTE_PCR7;
  volatile unsigned int       PORTE_PCR8;
  volatile unsigned int       PORTE_PCR9;
  volatile unsigned int       PORTE_PCR10;
  volatile unsigned int       PORTE_PCR11;
  volatile unsigned int       PORTE_PCR12;
  volatile unsigned int       PORTE_PCR13;
  volatile unsigned int       PORTE_PCR14;
  volatile unsigned int       PORTE_PCR15;
  volatile unsigned int       PORTE_PCR16;
  unsigned int                dummy_00[15];
  volatile unsigned int       PORTE_GPCLR;
  volatile unsigned int       PORTE_GPCHR;
  volatile unsigned int       PORTE_GICLR;
  volatile unsigned int       PORTE_GICHR;
  unsigned int                dummy_01[4];
  volatile unsigned int       PORTE_ISFR;
  unsigned int                dummy_02[7];
  volatile unsigned int       PORTE_DFER;
  volatile unsigned int       PORTE_DFCR;
  volatile unsigned int       PORTE_DFWR;
} PORTE_Type;

#define PORTE_BASE_ADDRS (0x4004D000) /* Base Address */
#define PORTE ((PORTE_Type*)PORTE_BASE_ADDRS)

#endif  /* #if !defined(PORT_TYPE_H_) */

