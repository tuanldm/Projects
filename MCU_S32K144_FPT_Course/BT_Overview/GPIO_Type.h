/*
** ###################################################################
**     Processor:           S32K144
**     Compiler:            Keil ARM C/C++ Compiler
**     Version:             rev. 1.0, 23/09/19 - 14:38:52
**
**     Abstract:
**         Peripheral Access Layer for S32K144
**
** ###################################################################
*/

/* Prevention from multiple including the same memory map */
#ifndef GPIO_TYPE_H_  /* Check if memory map has not been already included */
#define GPIO_TYPE_H_  

/* ----------------------------------------------------------------------------
   -- Peripheral Access Layer
   ---------------------------------------------------------------------------- */


/* GPIOA */
typedef struct {
  volatile unsigned int       GPIOA_PDOR;
  volatile unsigned int       GPIOA_PSOR;
  volatile unsigned int       GPIOA_PCOR;
  volatile unsigned int       GPIOA_PTOR;
  volatile const unsigned int GPIOA_PDIR;
  volatile unsigned int       GPIOA_PDDR;
  volatile unsigned int       GPIOA_PIDR;
} GPIOA_Type;

#define GPIOA_BASE_ADDRS (0x400FF000) /* Base Address */
#define GPIOA ((GPIOA_Type*)GPIOA_BASE_ADDRS)


/* GPIOB */
typedef struct {
  volatile unsigned int       GPIOB_PDOR;
  volatile unsigned int       GPIOB_PSOR;
  volatile unsigned int       GPIOB_PCOR;
  volatile unsigned int       GPIOB_PTOR;
  volatile const unsigned int GPIOB_PDIR;
  volatile unsigned int       GPIOB_PDDR;
  volatile unsigned int       GPIOB_PIDR;
} GPIOB_Type;

#define GPIOB_BASE_ADDRS (0x400FF040) /* Base Address */
#define GPIOB ((GPIOB_Type*)GPIOB_BASE_ADDRS)


/* GPIOC */
typedef struct {
  volatile unsigned int       GPIOC_PDOR;
  volatile unsigned int       GPIOC_PSOR;
  volatile unsigned int       GPIOC_PCOR;
  volatile unsigned int       GPIOC_PTOR;
  volatile const unsigned int GPIOC_PDIR;
  volatile unsigned int       GPIOC_PDDR;
  volatile unsigned int       GPIOC_PIDR;
} GPIOC_Type;

#define GPIOC_BASE_ADDRS (0x400FF080) /* Base Address */
#define GPIOC ((GPIOC_Type*)GPIOC_BASE_ADDRS)


/* GPIOD */
typedef struct {
  volatile unsigned int       GPIOD_PDOR;
  volatile unsigned int       GPIOD_PSOR;
  volatile unsigned int       GPIOD_PCOR;
  volatile unsigned int       GPIOD_PTOR;
  volatile const unsigned int GPIOD_PDIR;
  volatile unsigned int       GPIOD_PDDR;
  volatile unsigned int       GPIOD_PIDR;
} GPIOD_Type;

#define GPIOD_BASE_ADDRS (0x400FF0C0) /* Base Address */
#define GPIOD ((GPIOD_Type*)GPIOD_BASE_ADDRS)


/* GPIOE */
typedef struct {
  volatile unsigned int       GPIOE_PDOR;
  volatile unsigned int       GPIOE_PSOR;
  volatile unsigned int       GPIOE_PCOR;
  volatile unsigned int       GPIOE_PTOR;
  volatile const unsigned int GPIOE_PDIR;
  volatile unsigned int       GPIOE_PDDR;
  volatile unsigned int       GPIOE_PIDR;
} GPIOE_Type;

#define GPIOE_BASE_ADDRS (0x400FF100) /* Base Address */
#define GPIOE ((GPIOE_Type*)GPIOE_BASE_ADDRS)

#endif  /* #if !defined(GPIO_TYPE_H_) */

