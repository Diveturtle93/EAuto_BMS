//----------------------------------------------------------------------
// Titel	:	LTC1380.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	25.09.2020
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "ltc1380.h"
#include "ltc6811.h"
//----------------------------------------------------------------------

// Channel auswaehlen
//----------------------------------------------------------------------
void ltc1380_write(uint8_t Address, uint8_t Channel)
{
	// Definiere Array fuer Channel auswaehlen
	uint8_t off[6] = {0x69, 0x08, 0x00, 0x89, 0x7F, 0xF9};					// Daten-Bytes fuer LTC6811 mit Daten fuer LTC1380
	
	// Addresse und Channel waehlen
	off[1] |= ((Address & 0x0F) << 4);										// Address in Array uebertragen
	off[3] |= ((Channel & 0x0F) << 4);										// Channel in Array uebertragen
	
	// LTC6811 beschreiben und ueber I2C uebertragen
	ltc6811_write(WRCOMM, off);												// Daten in LTC6811 schreiben
	ltc6811(STCOMM);														// Daten von LTC6811 an LTC1380 senden
}
//----------------------------------------------------------------------

// All Channel off
//----------------------------------------------------------------------
void ltc1380_off(uint8_t Address)
{
	// Definiere Array fuer alle Kanaele aus
	uint8_t off[6] = {0x69, 0x08, 0x00, 0x09, 0x7F, 0xF9};					// Daten-Bytes fuer LTC6811 mit Daten fuer LTC1380
	
	// Addresse waehlen
	off[1] |= ((Address & 0x0F) << 4);										// Address in Array uebertragen
	
	// LTC6811 beschreiben und ueber I2C uebertragen
	ltc6811_write(WRCOMM, off);												// Daten in LTC6811 schreiben
	ltc6811(STCOMM);														// Daten von LTC6811 an LTC1380 senden
}
//----------------------------------------------------------------------


// All Multiplexer off
//----------------------------------------------------------------------
void ltc1380_alloff(void)
{
	// Definiere Array fuer alle Multiplexer aus
	uint8_t off[6] = {0x69, 0x08, 0x00, 0x09, 0x7F, 0xF9};					// Daten-Bytes fuer LTC6811 mit Daten fuer LTC1380
	
	// Schleife um Daten an LTC6811 zu uebertragen
	for (uint8_t i = 0; i<LTC1380_DEVICES; i++)
	{
		// Addresse waehlen
		off[1] |= (((i+1) & 0x0F) << 4);									// Address in Array uebertragen
		
		// LTC6811 beschreiben und ueber I2C uebertragen
		ltc6811_write(WRCOMM, off);											// Daten in LTC6811 schreiben
		ltc6811(STCOMM);													// Daten von LTC6811 an LTC1380 senden
	}
}
//----------------------------------------------------------------------
