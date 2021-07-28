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

#include "ltc1380.h"
#include "ltc6811.h"


// Channel auswählen
//----------------------------------------------------------------------
void ltc1380_write(uint8_t Address, uint8_t Channel)
{
	uint8_t off[6] = {0x69, 0x08, 0x00, 0x89, 0x7F, 0xF9};					// Daten-Bytes für LTC6811 mit Daten für LTC1380
	
	off[1] |= ((Address & 0x0F) << 4);										// Address in Array übertragen
	off[3] |= ((Channel & 0x0F) << 4);										// Channel in Array übertragen
	
	ltc6811_write(WRCOMM, off);												// Daten in LTC6811 schreiben
	ltc6811(STCOMM);														// Daten von LTC6811 an LTC1380 senden
}
//----------------------------------------------------------------------

// All Channel off
//----------------------------------------------------------------------
void ltc1380_off(uint8_t Address)
{
	uint8_t off[6] = {0x69, 0x08, 0x00, 0x09, 0x7F, 0xF9};					// Daten-Bytes für LTC6811 mit Daten für LTC1380
	
	off[1] |= ((Address & 0x0F) << 4);										// Address in Array übertragen
	
	ltc6811_write(WRCOMM, off);												// Daten in LTC6811 schreiben
	ltc6811(STCOMM);														// Daten von LTC6811 an LTC1380 senden
}
//----------------------------------------------------------------------


// All Multiplexer off
//----------------------------------------------------------------------
void ltc1380_alloff(void)
{
	uint8_t off[6] = {0x69, 0x08, 0x00, 0x09, 0x7F, 0xF9};					// Daten-Bytes für LTC6811 mit Daten für LTC1380
	
	for (uint8_t i = 0; i<LTC1380_DEVICES; i++)
	{
		off[1] |= (((i+1) & 0x0F) << 4);									// Address in Array übertragen
		
		ltc6811_write(WRCOMM, off);											// Daten in LTC6811 schreiben
		ltc6811(STCOMM);													// Daten von LTC6811 an LTC1380 senden
	}
}
//----------------------------------------------------------------------
