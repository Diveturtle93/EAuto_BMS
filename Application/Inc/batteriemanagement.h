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

// BMS Errors definieren
//----------------------------------------------------------------------
#define Module_OK								0
// Zellen haben Unterspannung
//----------------------------------------------------------------------
#define Cell1Undervoltage						1
#define Cell2Undervoltage						2
#define Cell3Undervoltage						3
#define Cell4Undervoltage						4
#define Cell5Undervoltage						5
#define Cell6Undervoltage						6
#define Cell7Undervoltage						7
#define Cell8Undervoltage						8
#define Cell9Undervoltage						9
#define Cell10Undervoltage						10
#define Cell11Undervoltage						11
#define Cell12Undervoltage						12
// Zellen haben Ueberspannung
//----------------------------------------------------------------------
#define Cell1Overvoltage						13
#define Cell2Overvoltage						14
#define Cell3Overvoltage						15
#define Cell4Overvoltage						16
#define Cell5Overvoltage						17
#define Cell6Overvoltage						18
#define Cell7Overvoltage						19
#define Cell8Overvoltage						20
#define Cell9Overvoltage						21
#define Cell10Overvoltage						22
#define Cell11Overvoltage						23
#define Cell12Overvoltage						24
//----------------------------------------------------------------------
// Zellen haben Untertemperatur
//----------------------------------------------------------------------
#define Cell1Undertemperatur					25
#define Cell2Undertemperatur					26
#define Cell3Undertemperatur					27
#define Cell4Undertemperatur					28
#define Cell5Undertemperatur					29
#define Cell6Undertemperatur					30
#define Cell7Undertemperatur					31
#define Cell8Undertemperatur					32
#define Cell9Undertemperatur					33
#define Cell10Undertemperatur					34
#define Cell11Undertemperatur					35
#define Cell12Undertemperatur					36
// Zellen haben Uebertemperatur
//----------------------------------------------------------------------
#define Cell1Overtemperatur						37
#define Cell2Overtemperatur						38
#define Cell3Overtemperatur						39
#define Cell4Overtemperatur						40
#define Cell5Overtemperatur						41
#define Cell6Overtemperatur						42
#define Cell7Overtemperatur						43
#define Cell8Overtemperatur						44
#define Cell9Overtemperatur						45
#define Cell10Overtemperatur					46
#define Cell11vertemperatur						47
#define Cell12vertemperatur						48
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void bms_init(void);														// Initialisier BMS
void bms_cellspannung(uint8_t cell);										// Lese einen Zellblock ein
void bms_cellspannungen(void);												// Lese alle Zellspannungen ein
void bms_celltemperatur(uint8_t tempsensor);								// Lese Zelltemperatur ein
void bms_celltemperaturen(void);											// Lesse alle Zelltemperaturen ein
void bms_ltc_status(void);													// Lese IC Status ein
void bms_volt_temp(uint8_t tempsensor);										// Messe Zellspannungen und zwei Temperaturen
void bms_volt_SOC(void);													// Messe Zellspannungen und Sum of Cells
void bms_work(void);														// Fuehre BMS Operation durch
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
