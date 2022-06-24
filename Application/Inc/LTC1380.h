//----------------------------------------------------------------------
// Titel	:	LTC1380.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	25.09.2020
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef LTC1380_H
#define LTC1380_H
//----------------------------------------------------------------------

// Include-Dateien einfuegen
//----------------------------------------------------------------------
#include "inttypes.h"
//----------------------------------------------------------------------

// Define Debug Symbols
//----------------------------------------------------------------------
//#define DEBUG_LTC1380
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define LTC1380_DEVICES		2												// Anzahl der ICs pro LTC6811
#define LTC1380_SENSORES	8												// Anzahl der Sensoren pro IC
//----------------------------------------------------------------------

// Addressen
//----------------------------------------------------------------------
#define LTC1380_MUX0 		0b10010000										// Adresse fue IC 1
#define LTC1380_MUX1		0b10010010										// Adresse fue IC 2
#define LTC1380_MUX2		0b10010100										// Adresse fue IC 3
#define LTC1380_MUX3		0b10010110										// Adresse fue IC 4
//----------------------------------------------------------------------

// Channel Auswahl
//----------------------------------------------------------------------
#define TEMPERATUR0			0												// Kanal 1 am IC
#define TEMPERATUR1			1												// Kanal 2 am IC
#define TEMPERATUR2			2												// Kanal 3 am IC
#define TEMPERATUR3			3												// Kanal 4 am IC
#define TEMPERATUR4			4												// Kanal 5 am IC
#define TEMPERATUR5			5												// Kanal 6 am IC
#define TEMPERATUR6			6												// Kanal 7 am IC
#define TEMPERATUR7			7												// Kanal 8 am IC
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void ltc1380_write(uint8_t Address, uint8_t Channel);						// Kanal eines ICs auswaehlen
void ltc1380_off(uint8_t Address);											// Alle Kanaele eines ICs ausschalten
void ltc1380_alloff(void);													// Alle Kanaele aller ICs ausschalten
//----------------------------------------------------------------------

#endif /* INC_LTC1380_H_ */
//----------------------------------------------------------------------
