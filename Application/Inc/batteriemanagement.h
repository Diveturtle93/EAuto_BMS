//----------------------------------------------------------------------
// Titel	:	batteriemanagement.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jun 23, 2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_BATTERIEMANAGEMENT_H_
#define INC_BATTERIEMANAGEMENT_H_
//----------------------------------------------------------------------

// Inlude Dateien einfuegen
//----------------------------------------------------------------------
#include "ltc6811.h"
#include "ltc1380.h"
//----------------------------------------------------------------------

// ... definieren
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void bms_init(void);														// Initialisier BMS
void bms_cellspannungen(uint16_t command);									// Lese alle Zellspannungen ein
void bms_celltemperaturen(uint16_t command);								// Lese Zelltemperaturen ein
void bms_ltc_status();														// Lese IC Status ein
void bms_measure(uint8_t tempsensor);										// Messe Zellspannungen und zwei Temperaturen
void bms_ok(void);															// Pruefe ob BMS OK ist
void bms_Vminmax(void);														// Minimal- und Maximalspannung ermitteln
void bms_Tminmax(void);														// Minimal- und Maximaltemperatur ermitteln
void bms_MSvoltage(void);													// Module- / Stackspannung berechnen
//----------------------------------------------------------------------

//----------------------------------------------------------------------
extern uint16_t cellvoltage[LTC6811_DEVICES][12];							// Array fuer gemessene Zellspannungen
extern uint16_t celltemperature[LTC6811_DEVICES][LTC1380_DEVICES * LTC1380_SENSORES];// Array fuer gemessene Zelltemperaturen
//----------------------------------------------------------------------

#endif /* INC_BATTERIEMANAGEMENT_H_ */
//----------------------------------------------------------------------
