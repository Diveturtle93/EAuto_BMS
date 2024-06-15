//----------------------------------------------------------------------
// Titel	:	Error.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------
#include "string.h"
#include "stdlib.h"
//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
#include "usart.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "BasicUart.h"
//----------------------------------------------------------------------

// Uart2 Transmit Funktion
//----------------------------------------------------------------------
void uartTransmit(const char *str, const size_t size)
{
	// Sende String mit Laenge "Size", "Size" muss bekannt sein
#ifdef SHELL
	HAL_UART_Transmit(&huart2, (uint8_t *)str, size, 1000);
#endif
}
//----------------------------------------------------------------------

// Uart2 Transmit Nummer Funktion
//----------------------------------------------------------------------
void uartTransmitNumber(const uint32_t number, const uint32_t base)
{
	char str[11];

	// Zahl umrechnen
	utoa(number, str, base);												// Zahl umrechnen anhand der Basis "base"
#ifdef SHELL
	HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), 1000);			// Sende Zahlen
#endif
}
//----------------------------------------------------------------------

// Uart2 Transmit String Funktion
//----------------------------------------------------------------------
void uartTransmitString(const char *str)
{
#ifdef SHELL
	HAL_UART_Transmit(&huart2, (uint8_t *)str, sizeof(str), 1000);
#endif
}
//----------------------------------------------------------------------
