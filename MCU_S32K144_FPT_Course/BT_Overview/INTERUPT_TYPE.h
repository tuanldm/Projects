/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 23/09/28 - 18:57:16
**
**     Abstract:
**         Peripheral Access Layer for S32K144
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#ifndef INTERUPT_TYPE_H_  /* Check if memory map has not been already included */
#define INTERUPT_TYPE_H_  

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */


/* INTERUPT_SET */
typedef struct {
  volatile unsigned int       NVIC_ISER0;
  volatile unsigned int       NVIC_ISER1;
  volatile unsigned int       NVIC_ISER2;
  volatile unsigned int       NVIC_ISER3;
  volatile unsigned int       NVIC_ISER4;
  volatile unsigned int       NVIC_ISER5;
  volatile unsigned int       NVIC_ISER6;
  volatile unsigned int       NVIC_ISER7;
} INTERUPT_SET_Type;

#define INTERUPT_SET_BASE_ADDRS (0xE000E100) /* Base Address */
#define INTERUPT_SET ((INTERUPT_SET_Type*)INTERUPT_SET_BASE_ADDRS)


/* INTERUPT_CLEAR */
typedef struct {
  volatile unsigned int       NVIC_ICER0;
  volatile unsigned int       NVIC_ICER1;
  volatile unsigned int       NVIC_ICER2;
  volatile unsigned int       NVIC_ICER3;
  volatile unsigned int       NVIC_ICER4;
  volatile unsigned int       NVIC_ICER5;
  volatile unsigned int       NVIC_ICER6;
  volatile unsigned int       NVIC_ICER7;
} INTERUPT_CLEAR_Type;

#define INTERUPT_CLEAR_BASE_ADDRS (0xE000E180) /* Base Address */
#define INTERUPT_CLEAR ((INTERUPT_CLEAR_Type*)INTERUPT_CLEAR_BASE_ADDRS)


/* INTERUPT_SETPEND */
typedef struct {
  volatile unsigned int       NVIC_ISER0;
  volatile unsigned int       NVIC_ISER1;
  volatile unsigned int       NVIC_ISER2;
  volatile unsigned int       NVIC_ISER3;
  volatile unsigned int       NVIC_ISER4;
  volatile unsigned int       NVIC_ISER5;
  volatile unsigned int       NVIC_ISER6;
  volatile unsigned int       NVIC_ISER7;
} INTERUPT_SETPEND_Type;

#define INTERUPT_SETPEND_BASE_ADDRS (0xE000E200) /* Base Address */
#define INTERUPT_SETPEND ((INTERUPT_SETPEND_Type*)INTERUPT_SETPEND_BASE_ADDRS)


/* INTERUPT_CLEARPEND */
typedef struct {
  volatile unsigned int       NVIC_ISPR0;
  volatile unsigned int       NVIC_ISPR1;
  volatile unsigned int       NVIC_ISPR2;
  volatile unsigned int       NVIC_ISPR3;
  volatile unsigned int       NVIC_ISPR4;
  volatile unsigned int       NVIC_ISPR5;
  volatile unsigned int       NVIC_ISPR6;
  volatile unsigned int       NVIC_ISPR7;
} INTERUPT_CLEARPEND_Type;

#define INTERUPT_CLEARPEND_BASE_ADDRS (0xE000E280) /* Base Address */
#define INTERUPT_CLEARPEND ((INTERUPT_CLEARPEND_Type*)INTERUPT_CLEARPEND_BASE_ADDRS)


/* INTERUPT_ACTIVE */
typedef struct {
  volatile unsigned int       NVIC_ICPR0;
  volatile unsigned int       NVIC_ICPR1;
  volatile unsigned int       NVIC_ICPR2;
  volatile unsigned int       NVIC_ICPR3;
  volatile unsigned int       NVIC_ICPR4;
  volatile unsigned int       NVIC_ICPR5;
  volatile unsigned int       NVIC_ICPR6;
  volatile unsigned int       NVIC_ICPR7;
} INTERUPT_ACTIVE_Type;

#define INTERUPT_ACTIVE_BASE_ADDRS (0xE000E300) /* Base Address */
#define INTERUPT_ACTIVE ((INTERUPT_ACTIVE_Type*)INTERUPT_ACTIVE_BASE_ADDRS)


/* INTERUPT_PRIORITY */
typedef struct {
  volatile unsigned int       NVIC_IPR0;
  volatile unsigned int       NVIC_IPR1;
  volatile unsigned int       NVIC_IPR2;
  volatile unsigned int       NVIC_IPR3;
  volatile unsigned int       NVIC_IPR4;
  volatile unsigned int       NVIC_IPR5;
  volatile unsigned int       NVIC_IPR6;
  volatile unsigned int       NVIC_IPR7;
  volatile unsigned int       NVIC_IPR8;
  volatile unsigned int       NVIC_IPR9;
  volatile unsigned int       NVIC_IPR10;
  volatile unsigned int       NVIC_IPR11;
  volatile unsigned int       NVIC_IPR12;
  volatile unsigned int       NVIC_IPR13;
  volatile unsigned int       NVIC_IPR14;
  volatile unsigned int       NVIC_IPR15;
  volatile unsigned int       NVIC_IPR16;
  volatile unsigned int       NVIC_IPR17;
  volatile unsigned int       NVIC_IPR18;
  volatile unsigned int       NVIC_IPR19;
  volatile unsigned int       NVIC_IPR20;
  volatile unsigned int       NVIC_IPR21;
  volatile unsigned int       NVIC_IPR22;
  volatile unsigned int       NVIC_IPR23;
  volatile unsigned int       NVIC_IPR24;
  volatile unsigned int       NVIC_IPR25;
  volatile unsigned int       NVIC_IPR26;
  volatile unsigned int       NVIC_IPR27;
  volatile unsigned int       NVIC_IPR28;
  volatile unsigned int       NVIC_IPR29;
  volatile unsigned int       NVIC_IPR30;
  volatile unsigned int       NVIC_IPR31;
  volatile unsigned int       NVIC_IPR32;
  volatile unsigned int       NVIC_IPR33;
  volatile unsigned int       NVIC_IPR34;
  volatile unsigned int       NVIC_IPR35;
  volatile unsigned int       NVIC_IPR36;
  volatile unsigned int       NVIC_IPR37;
  volatile unsigned int       NVIC_IPR38;
  volatile unsigned int       NVIC_IPR39;
  volatile unsigned int       NVIC_IPR40;
  volatile unsigned int       NVIC_IPR41;
  volatile unsigned int       NVIC_IPR42;
  volatile unsigned int       NVIC_IPR43;
  volatile unsigned int       NVIC_IPR44;
  volatile unsigned int       NVIC_IPR45;
  volatile unsigned int       NVIC_IPR46;
  volatile unsigned int       NVIC_IPR47;
  volatile unsigned int       NVIC_IPR48;
  volatile unsigned int       NVIC_IPR49;
  volatile unsigned int       NVIC_IPR50;
  volatile unsigned int       NVIC_IPR51;
  volatile unsigned int       NVIC_IPR52;
  volatile unsigned int       NVIC_IPR53;
  volatile unsigned int       NVIC_IPR54;
  volatile unsigned int       NVIC_IPR55;
  volatile unsigned int       NVIC_IPR56;
  volatile unsigned int       NVIC_IPR57;
  volatile unsigned int       NVIC_IPR58;
  volatile unsigned int       NVIC_IPR59;
} INTERUPT_PRIORITY_Type;

#define INTERUPT_PRIORITY_BASE_ADDRS (0xE000E400) /* Base Address */
#define INTERUPT_PRIORITY ((INTERUPT_PRIORITY_Type*)INTERUPT_PRIORITY_BASE_ADDRS)


/* INTERUPT_TRIGGER */
typedef struct {
  volatile unsigned int       STIR;
} INTERUPT_TRIGGER_Type;

#define INTERUPT_TRIGGER_BASE_ADDRS (0xE000EF00) /* Base Address */
#define INTERUPT_TRIGGER ((INTERUPT_TRIGGER_Type*)INTERUPT_TRIGGER_BASE_ADDRS)

#endif  /* #if !defined(INTERUPT_TYPE_H_) */

