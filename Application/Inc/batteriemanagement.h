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

// ... definieren
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// ... definieren
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void bms_init(void);														// Initialisier BMS
void bms_cellspannungen(void);												// Lese alle Zellspannungen ein
void bms_celltemperaturen(void);											// Lese Zelltemperaturen ein
void bms_ltc_status(void);													// Lese IC Status ein
void bms_measure(void);														// Messe Zellspannungen und zwei Temperaturen
void bms_ok(void);															// Pruefe ob BMS OK ist
//----------------------------------------------------------------------

//----------------------------------------------------------------------
extern uint8_t CellVolt[LTC6811_DEVICES][12];								// Array fuer gemessene Zellspannungen
extern uint8_t CellTemp[LTC6811_DEVICES][12];								// Array fuer gemessene Zelltemperaturen
//----------------------------------------------------------------------

#endif /* INC_BATTERIEMANAGEMENT_H_ */
//----------------------------------------------------------------------
