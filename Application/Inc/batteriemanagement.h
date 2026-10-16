//----------------------------------------------------------------------
// Titel	:	batteriemanagement.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	23.07.2022
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
// Quelle	:
//----------------------------------------------------------------------

// Sicherheitssymbol
//----------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_BATTERIEMANAGEMENT_H_
#define INC_BATTERIEMANAGEMENT_H_
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include-Dateien
//----------------------------------------------------------------------
#include "ltc6811.h"
#include "ltc1380.h"
//----------------------------------------------------------------------

// Definiere Debug-Symbole
//----------------------------------------------------------------------
#ifdef DEBUG
//	#define DEBUG_BMS
//	#define DEBUG_BMS_OK
	#define DEBUG_BMS_WORK
//	#define DEBUG_BATTERIEMANAGEMENT
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
#define BMS_ERROR								false
#define BMS_WARNING								false
#define BMS_NOERROR								true
//----------------------------------------------------------------------
// Zellen haben Unterspannung
//----------------------------------------------------------------------
#define CELL1UNDERVOLTAGE						0
#define CELL2UNDERVOLTAGE						1
#define CELL3UNDERVOLTAGE						2
#define CELL4UNDERVOLTAGE						3
#define CELL5UNDERVOLTAGE						4
#define CELL6UNDERVOLTAGE						5
#define CELL7UNDERVOLTAGE						6
#define CELL8UNDERVOLTAGE						7
#define CELL9UNDERVOLTAGE						8
#define CELL10UNDERVOLTAGE						9
#define CELL11UNDERVOLTAGE						10
#define CELL12UNDERVOLTAGE						11
//----------------------------------------------------------------------
// Zellen haben Ueberspannung
//----------------------------------------------------------------------
#define CELL1OVERVOLTAGE						12
#define CELL2OVERVOLTAGE						13
#define CELL3OVERVOLTAGE						14
#define CELL4OVERVOLTAGE						15
#define CELL5OVERVOLTAGE						16
#define CELL6OVERVOLTAGE						17
#define CELL7OVERVOLTAGE						18
#define CELL8OVERVOLTAGE						19
#define CELL9OVERVOLTAGE						20
#define CELL10OVERVOLTAGE						21
#define CELL11OVERVOLTAGE						22
#define CELL12OVERVOLTAGE						23
//----------------------------------------------------------------------
// Zellen haben Untertemperatur
//----------------------------------------------------------------------
#define CELL1UNDERTEMPERATUR					24
#define CELL2UNDERTEMPERATUR					25
#define CELL3UNDERTEMPERATUR					26
#define CELL4UNDERTEMPERATUR					27
#define CELL5UNDERTEMPERATUR					28
#define CELL6UNDERTEMPERATUR					29
#define CELL7UNDERTEMPERATUR					30
#define CELL8UNDERTEMPERATUR					31
#define CELL9UNDERTEMPERATUR					32
#define CELL10UNDERTEMPERATUR					33
#define CELL11UNDERTEMPERATUR					34
#define CELL12UNDERTEMPERATUR					35
#define CELL13UNDERTEMPERATUR					36
#define CELL14UNDERTEMPERATUR					37
#define CELL15UNDERTEMPERATUR					38
#define CELL16UNDERTEMPERATUR					39
//----------------------------------------------------------------------
// Zellen haben Uebertemperatur
//----------------------------------------------------------------------
#define CELL1OVERTEMPERATUR						40
#define CELL2OVERTEMPERATUR						41
#define CELL3OVERTEMPERATUR						42
#define CELL4OVERTEMPERATUR						43
#define CELL5OVERTEMPERATUR						44
#define CELL6OVERTEMPERATUR						45
#define CELL7OVERTEMPERATUR						46
#define CELL8OVERTEMPERATUR						47
#define CELL9OVERTEMPERATUR						48
#define CELL10OVERTEMPERATUR					49
#define CELL11OVERTEMPERATUR					50
#define CELL12OVERTEMPERATUR					51
#define CELL13OVERTEMPERATUR					52
#define CELL14OVERTEMPERATUR					53
#define CELL15OVERTEMPERATUR					54
#define CELL16OVERTEMPERATUR					55
//----------------------------------------------------------------------
#define BMS_LTC_TEMPERATUR						56
#define BMS_SLAVE_PCB_ERROR						57
#define BMS_PLAUSIBILITY_ERROR					58
#define BMS_MEASUREMENT_OUTOF_RANGE				59
#define BMS_READ_TIMEOUT						60
//----------------------------------------------------------------------

//----------------------------------------------------------------------
#define BMS_ERROR_TRESHOLD						5
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
bool bms_init (void);														// Initialisier BMS
void bms_cellspannung (uint8_t CELL);										// Lese einen Zellblock ein
void bms_cellspannungen (void);												// Lese alle Zellspannungen ein
void bms_celltemperatur (uint8_t tempsensor);								// Lese Zelltemperatur ein
void bms_celltemperaturen (void);											// Lese alle Zelltemperaturen ein
void bms_readgpio (uint8_t gpio);											// Lese GPIO des LTC ein
void bms_ltc_status (void);													// Lese IC Status ein
void bms_volt_temp (uint8_t tempsensor);									// Messe Zellspannungen und zwei Temperaturen
void bms_volt_SOC (void);													// Messe Zellspannungen und Sum of CELLs
void bms_work (void);														// Fuehre BMS Operation durch
bool bms_ok (void);															// Pruefe ob BMS OK ist
void bms_Vminmax (void);													// Minimal- und Maximalspannung ermitteln
void bms_Tminmax (void);													// Minimal- und Maximaltemperatur ermitteln
void bms_MSvoltage (void);													// Module- / Stackspannung berechnen
//----------------------------------------------------------------------

// Definiere globale Arrays fuer Zellspannung und -temperatur
//----------------------------------------------------------------------
// extern uint16_t CELLvoltage[LTC6811_DEVICES][LTC6811_CELLS];				// Array fuer gemessene Zellspannungen
// extern uint16_t CELLtemperature[LTC6811_DEVICES][LTC1380_DEVICES * LTC1380_SENSORES];// Array fuer gemessene Zelltemperaturen
//----------------------------------------------------------------------

#endif /* INC_BATTERIEMANAGEMENT_H_ */
//----------------------------------------------------------------------
