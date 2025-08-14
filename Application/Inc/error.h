//----------------------------------------------------------------------
// Titel	:	Error.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef ERROR_H_
#define ERROR_H_
//----------------------------------------------------------------------

// Definiere Debug Symbol
//----------------------------------------------------------------------
#ifdef DEBUG
//#define DEBUG_HAL
//#define DEBUG_SWO
#endif
//----------------------------------------------------------------------

// Festlegen der Fehlercodes
//----------------------------------------------------------------------
#define ERROR_NONE								0							// Kein Fehler
#define ERROR_LTC6811_THERMAL					1							// LTC6811 Temperaturfehler
#define ERROR_LTC6811_TEST1						2							// LTC6811 Test 1 fehlerhaft
#define ERROR_LTC6811_TEST2						3							// LTC6811 Test 2 fehlerhaft
#define ERROR_LTC6811_DIAGN						4							// LTC6811 Diagnosebit fehlerhaft
#define ERROR_LTC6811_OPENWIRE					5							// LTC6811 OpenWire fehlerhaft
#define ERROR_LTC6811_OVERVOLT					6							// LTC6811 Ueberspannungsfehler
#define ERROR_LTC6811_UNDERVOLT					7							// LTC6811 Unterspannungsfehler
#define ERROR_LTC6811_INITIALTEST				8							// LTC6811 Initialtest fehlerhaft
#define ERROR_LTC6811_COMM_TIMEOUT				9							// LTC6811 Kommunikationsfehler
#define ERROR_SDC_BTB							10							// Kein BTB
#define ERROR_SDC_MOTOR							11							// Kein Motorsteuergeraet
#define ERROR_SDC_HVIL							12							// Keine HV-Stecker
#define ERROR_IMD								13							// IMD Fehler
#define ERROR_AMS								14							// AMS Fehler
#define ERROR_ADC								15							// ADC Fehler
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void hal_error (uint8_t status);											// Statusausgabe HAL Error auf UART
void software_error (uint8_t errorcode);									// Software Error auf UART, Haelt das Programm an
void software_error_debug (uint8_t errorcode);								// Software Error auf UART
void ITM_SendString (char *text);											// Debug Ausgabe auf SWO, String, nur DEBUG
void ITM_SendNumber (long number);											// Debug Ausgabe auf SWO, Nummer, nur DEBUG
void ITM_SendFloat (double number, int digits);								// Debug Ausgabe auf SWO, Float, nur DEBUG
//----------------------------------------------------------------------

#endif /* INC_ERROR_H_ */
//----------------------------------------------------------------------
