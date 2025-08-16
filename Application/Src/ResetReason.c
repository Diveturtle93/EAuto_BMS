//----------------------------------------------------------------------
// Titel	:	ResetReason.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.05.2025
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	ResetReason
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "ResetReason.h"
#include "BasicUart.h"
//----------------------------------------------------------------------

// Collects Reset source Flag microcontroller
//----------------------------------------------------------------------
reset_reason readResetSource(void)
{
	reset_reason reset_flags = STARTUP;

	// Pruefe Reset Flag Internen Watchdog
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) == true)
	{
		reset_flags += IWDGRST1;
	}

	// Pruefe Reset Flag Window Watchdog
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) == true)
	{
		reset_flags += WWDGRST1;
	}

	// Pruefe Reset Flag Low Power Reset
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST) == true)
	{
		reset_flags += LPWRRST1;
	}
	
	// Pruefe Reset Flag Brown Out Reset
#ifdef STM32F7
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST) == true)
	{
		reset_flags += BORRST1;
	}
#endif

	// Pruefe Reset Flag Option Byte Loader Reset
#ifdef STM32G0
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_OBLRST) == true)
	{
		reset_flags += OBLRST1;
	}
#endif
	

	// Pruefe Reset Flag Power On Reset
#ifndef STM32G0
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST) == true)
#else
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_PWRRST) == true)
#endif
	{
		reset_flags += PORRST1;
	}

	// Pruefe Reset Flag Software Reset
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST) == true)
	{
		reset_flags += SFTRST1;
	}

	// Pruefe Reset Flag Pin-Reset
	if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST) == true)
	{
		reset_flags += PINRST1;
	}

	// Loesche alle Reset Flags
	__HAL_RCC_CLEAR_RESET_FLAGS();

	return reset_flags;
}
//----------------------------------------------------------------------

// Print reset source from microcontroller
//----------------------------------------------------------------------
void printResetSource(reset_reason reset_flags)
{
	if (reset_flags == STARTUP)												// Regulaerer Start
	{
		uartTransmit("Regular Start\n\n", 15);
	}
	else
	{
		if (reset_flags & IWDGRST1)											// Independent watchdog Reset
		{
			uartTransmit("Interner Watchdog Reset\n", 24);
		}

		if (reset_flags & WWDGRST1)											// Window watchdog Reset
		{
			uartTransmit("Window Watchdog Reset\n", 22);
		}

		if (reset_flags & LPWRRST1)											// Low Power Reset
		{
			uartTransmit("Low Power Reset\n", 16);
		}
	
#ifdef STM32F7
		if (reset_flags & BORRST1)											// Brown out Reset
		{
			uartTransmit("Brown Out Reset\n", 16);
		}
#endif

#ifdef STM32G0
		if (reset_flags & OBLRST1)											// Option Byte Loader Reset
		{
			uartTransmit("Option Byte Loader Reset\n", 25);
		}
#endif

		if (reset_flags & PORRST1)											// Power on Reset / Power down Reser
		{
			uartTransmit("Power On Reset\n", 15);
		}

		if (reset_flags & SFTRST1)											// Software Reset
		{
			uartTransmit("Software Reset\n", 15);
		}

		if (reset_flags & PINRST1)											// NRST pin
		{
			uartTransmit("PIN Reset\n", 10);
		}
	}
}
//----------------------------------------------------------------------
