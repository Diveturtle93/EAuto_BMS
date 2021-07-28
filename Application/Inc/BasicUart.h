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

// Funktionen definieren
//----------------------------------------------------------------------
void uartTransmit(const char *str, const size_t size);
void uartTransmitNumber(const uint32_t number, const uint32_t base);
void uartReInitBasicPolling(void);
//----------------------------------------------------------------------

#endif /* INC_BASICUART_H_ */
//----------------------------------------------------------------------
