//----------------------------------------------------------------------
// Titel	:	BasicUart.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_BASICUART_H_
#define INC_BASICUART_H_
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------
#include <stdint.h>
#include <stdio.h>
//----------------------------------------------------------------------

// Definiere Debug Symbols
//----------------------------------------------------------------------
#ifdef DEBUG
	#define SHELL
#endif
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void uartTransmit (const char *str, const size_t size);
void uartTransmitString (const char *str);
void uartTransmitNumber (const uint32_t number, const uint32_t base);
//----------------------------------------------------------------------

#endif /* INC_BASICUART_H_ */
//----------------------------------------------------------------------
