//----------------------------------------------------------------------
// Titel	:	LTC1380.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	25.09.2020
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------


#ifndef LTC1380_H
#define LTC1380_H

#include "inttypes.h"


// Konstanten definieren
//----------------------------------------------------------------------
#define LTC1380_DEVICES		2						// Anzahl der ICs
//----------------------------------------------------------------------

// Addressen
//----------------------------------------------------------------------
#define LTC1380_MUX0 0b10010000
#define LTC1380_MUX1 0b10010010
#define LTC1380_MUX2 0b10010100
#define LTC1380_MUX3 0b10010110
//----------------------------------------------------------------------

// Channel Auswahl
//----------------------------------------------------------------------
#define TEMPERATUR0			0
#define TEMPERATUR1			1
#define TEMPERATUR2			2
#define TEMPERATUR3			3
#define TEMPERATUR4			4
#define TEMPERATUR5			5
#define TEMPERATUR6			6
#define TEMPERATUR7			7
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void ltc1380_write(uint8_t Address, uint8_t Channel);
void ltc1380_off(uint8_t Address);
void ltc1380_alloff(void);
//----------------------------------------------------------------------

#endif
