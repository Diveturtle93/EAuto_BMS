//----------------------------------------------------------------------
// Titel	:	HardFault.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.05.2025
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Hardfault
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_HARDFAULT_H_
#define INC_HARDFAULT_H_
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#ifdef STM32F767xx
	#include "stm32f7xx_hal.h"
#endif

#ifdef STM32F105xx
	#include "stm32f1xx_hal.h"
#endif
//----------------------------------------------------------------------

// Definiere Debug Symbols
//----------------------------------------------------------------------
// Bit masking
//----------------------------------------------------------------------
#define CHECK_BIT(REG, POS) ((REG) & (1u << (POS)))
//----------------------------------------------------------------------

// Hard Fault Status Register
//----------------------------------------------------------------------
#define FORCED              ((uint8_t)30u)
#define VECTTBL             ((uint8_t)1u)
//----------------------------------------------------------------------

// MemManage Fault Status Register (MMFSR; 0-7 bits in CFSR)
//----------------------------------------------------------------------
#define MMARVALID           ((uint8_t)7u)
#define MLSPERR             ((uint8_t)5u)   /**< Only on ARM Cortex-M4F. */
#define MSTKERR             ((uint8_t)4u)
#define MUNSTKERR           ((uint8_t)3u)
#define DACCVIOL            ((uint8_t)1u)
#define IACCVIOL            ((uint8_t)0u)
//----------------------------------------------------------------------

// Bus Fault Status Register (BFSR; 8-15 bits in CFSR)
//----------------------------------------------------------------------
#define BFARVALID           ((uint8_t)15u)
#define LSPERR              ((uint8_t)13u)  /**< Only on ARM Cortex-M4F. */
#define STKERR              ((uint8_t)12u)
#define UNSTKERR            ((uint8_t)11u)
#define IMPRECISERR         ((uint8_t)10u)
#define PRECISERR           ((uint8_t)9u)
#define IBUSERR             ((uint8_t)8u)
//----------------------------------------------------------------------

// Usage Fault Status Register (BFSR; 16-25 bits in CFSR)
//----------------------------------------------------------------------
#define DIVBYZERO           ((uint8_t)25u)  /**< Has to be enabled in CCR. */
#define UNALIGNED           ((uint8_t)24u)  /**< Has to be enabled in CCR. */
#define NOCP                ((uint8_t)19u)
#define INVPC               ((uint8_t)18u)
#define INVSTATE            ((uint8_t)17u)
#define UNDEFINSTR          ((uint8_t)16u)
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void HardFault_Handler (void);
//----------------------------------------------------------------------

#endif /* INC_HARDFAULT_H_ */
//----------------------------------------------------------------------
