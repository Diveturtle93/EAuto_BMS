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
#include "main.h"
#include "ltc6811.h"
#include "ltc1380.h"
//----------------------------------------------------------------------

// Definiere Debug Symbols
//----------------------------------------------------------------------
#ifdef DEBUG
//	#define DEBUG_BMS
//	#define DEBUG_BMS_OK
	#define DEBUG_BMS_WORK
#endif
//----------------------------------------------------------------------

// Pruefen ob zuviele LTC6811_DEVICES gesetzt sind
//----------------------------------------------------------------------
#if LTC6811_DEVICES > 8
	#error "Zuviele LTC6811 Devices definiert."
#endif
//----------------------------------------------------------------------

// BMS Errors definieren
//----------------------------------------------------------------------
#define BMSError								false
#define BMSWarning								false
#define BMSNoError								true
//----------------------------------------------------------------------
// Zellen haben Unterspannung
//----------------------------------------------------------------------
#define Cell1Undervoltage						0
#define Cell2Undervoltage						1
#define Cell3Undervoltage						2
#define Cell4Undervoltage						3
#define Cell5Undervoltage						4
#define Cell6Undervoltage						5
#define Cell7Undervoltage						6
#define Cell8Undervoltage						7
#define Cell9Undervoltage						8
#define Cell10Undervoltage						9
#define Cell11Undervoltage						10
#define Cell12Undervoltage						11
//----------------------------------------------------------------------
// Zellen haben Ueberspannung
//----------------------------------------------------------------------
#define Cell1Overvoltage						12
#define Cell2Overvoltage						13
#define Cell3Overvoltage						14
#define Cell4Overvoltage						15
#define Cell5Overvoltage						16
#define Cell6Overvoltage						17
#define Cell7Overvoltage						18
#define Cell8Overvoltage						19
#define Cell9Overvoltage						20
#define Cell10Overvoltage						21
#define Cell11Overvoltage						22
#define Cell12Overvoltage						23
//----------------------------------------------------------------------
// Zellen haben Untertemperatur
//----------------------------------------------------------------------
#define Cell1Undertemperatur					24
#define Cell2Undertemperatur					25
#define Cell3Undertemperatur					26
#define Cell4Undertemperatur					27
#define Cell5Undertemperatur					28
#define Cell6Undertemperatur					29
#define Cell7Undertemperatur					30
#define Cell8Undertemperatur					31
#define Cell9Undertemperatur					32
#define Cell10Undertemperatur					33
#define Cell11Undertemperatur					34
#define Cell12Undertemperatur					35
#define Cell13Undertemperatur					36
#define Cell14Undertemperatur					37
#define Cell15Undertemperatur					38
#define Cell16Undertemperatur					39
//----------------------------------------------------------------------
// Zellen haben Uebertemperatur
//----------------------------------------------------------------------
#define Cell1Overtemperatur						40
#define Cell2Overtemperatur						41
#define Cell3Overtemperatur						42
#define Cell4Overtemperatur						43
#define Cell5Overtemperatur						44
#define Cell6Overtemperatur						45
#define Cell7Overtemperatur						46
#define Cell8Overtemperatur						47
#define Cell9Overtemperatur						48
#define Cell10Overtemperatur					49
#define Cell11Overtemperatur					50
#define Cell12Overtemperatur					51
#define Cell13Overtemperatur					52
#define Cell14Overtemperatur					53
#define Cell15Overtemperatur					54
#define Cell16Overtemperatur					55
//----------------------------------------------------------------------
#define BMS_LTC_Temperatur						56
#define BMS_SlavePCBError						57
#define BMS_PlausibilityError					58
#define BMS_MeasurementOutRange					59
#define BMS_ReadTimeOut							60
//----------------------------------------------------------------------

//----------------------------------------------------------------------
#define BMS_ERROR_TRESHOLD						5
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
bool bms_init (void);														// Initialisier BMS
void bms_cellspannung (uint8_t cell);										// Lese einen Zellblock ein
void bms_cellspannungen (void);												// Lese alle Zellspannungen ein
void bms_celltemperatur (uint8_t tempsensor);								// Lese Zelltemperatur ein
void bms_celltemperaturen (void);											// Lese alle Zelltemperaturen ein
void bms_readgpio (uint8_t gpio);											// Lese GPIO des LTC ein
void bms_ltc_status (void);													// Lese IC Status ein
void bms_volt_temp (uint8_t tempsensor);									// Messe Zellspannungen und zwei Temperaturen
void bms_volt_SOC (void);													// Messe Zellspannungen und Sum of Cells
void bms_work (void);														// Fuehre BMS Operation durch
bool bms_ok (void);															// Pruefe ob BMS OK ist
void bms_Vminmax (void);													// Minimal- und Maximalspannung ermitteln
void bms_Tminmax (void);													// Minimal- und Maximaltemperatur ermitteln
void bms_MSvoltage (void);													// Module- / Stackspannung berechnen
//----------------------------------------------------------------------

//// Definiere globale Arrays fuer Zellspannung und -temperatur
////----------------------------------------------------------------------
//extern uint16_t cellvoltage[LTC6811_DEVICES][LTC6811_CELLS];				// Array fuer gemessene Zellspannungen
//extern uint16_t celltemperature[LTC6811_DEVICES][LTC1380_DEVICES * LTC1380_SENSORES];// Array fuer gemessene Zelltemperaturen
////----------------------------------------------------------------------

#endif /* INC_BATTERIEMANAGEMENT_H_ */
//----------------------------------------------------------------------
