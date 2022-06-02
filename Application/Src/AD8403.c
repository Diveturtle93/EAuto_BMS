//----------------------------------------------------------------------
// Titel	:	AD8403.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	27.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "spi.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "AD8403.h"
#include "SPI_resource.h"
//----------------------------------------------------------------------

// Initialisiere AD8403
//----------------------------------------------------------------------
void initAD8403(void)
{
	// Setze AD8403 Shutdown Pin
	AD8403_SHDN_ENABLE();

	// Verzoegerung fuer einen Reset des AD8403
	HAL_Delay(20);

	// Deaktiviere Chip Select
	AD8403_CS_DISABLE();

	// Setze AD8403 RS Pin
	AD8403_RS_ENABLE();
}
//----------------------------------------------------------------------

// Setze Potentiometer Wert
//----------------------------------------------------------------------
void setPoti(uint8_t addresse, uint8_t Data)
{
	// Variable definieren
	uint8_t tmp[2] = {0};

	// Speicher mit Adresse und Data fuellen
	tmp[0] = addresse;
	tmp[1] = Data;

	// Aktiviere Chip Select
	AD8403_CS_ENABLE();

	// Command fuer AD8403 senden
	HAL_SPI_Transmit(&hspi1, tmp, 2, HAL_MAX_DELAY);

	// Deaktiviere Chip Select
	AD8403_CS_DISABLE();
}
//----------------------------------------------------------------------

// Setze alle Potis mit den selben Werten
//----------------------------------------------------------------------
void setAllPoti(uint8_t Data)
{
	// Setze jedes Poti einzeln
	setPoti(AD8403_MUX0, Data);												// Setze Poti 1
	setPoti(AD8403_MUX1, Data);												// Setze Poti 2
	setPoti(AD8403_MUX2, Data);												// Setze Poti 3
	setPoti(AD8403_MUX3, Data);												// Setze Poti 4
}
//----------------------------------------------------------------------

// Schalte Poti aus
//----------------------------------------------------------------------
void PotiOff(uint8_t addresse)
{
	// Setze ausgewaehltes Poti auf Terminal B
	setPoti(addresse, 255);													// Setze Poti auf 255, Auswahl ueber Addresse
}
//----------------------------------------------------------------------

// Schalte alle Potis aus
//----------------------------------------------------------------------
void AllPotiOff(void)
{
	// Schalte Wiper auf Terminal B, Open circuit Terminal A
	AD8403_SHDN_DISABLE();													// Setze SHDN auf Low
}
//----------------------------------------------------------------------

// Schalte alle Potis an
//----------------------------------------------------------------------
void AllPotiOn(void)
{
	// Schalte Wiper auf Wert im Register
	AD8403_SHDN_ENABLE();													// Setze SHDN auf High
}
//----------------------------------------------------------------------

// Schalte alle Potis auf halbe Stellung, Midscale
//----------------------------------------------------------------------
void AllPotiMidscale(void)
{
	// Schalte Wiper mittlere Stellung, halb A, halb B
	AD8403_RS_DISABLE();													// Setze RS auf Low

	// Verzoegerung um den Pin wieder auf High zu setzen
	HAL_Delay(20);

	// Setze AD8403 Shutdown Pin
	AD8403_RS_ENABLE();														// Setze RS auf High
}
//----------------------------------------------------------------------
