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
#define ERROR_NONE								0
#define ERROR_LTC6811_THERMAL					1
#define ERROR_LTC6811_TEST1						2
#define ERROR_LTC6811_TEST2						3
#define ERROR_LTC6811_DIAGN						4
#define ERROR_LTC6811_OPENWIRE					5
#define ERROR_LTC6811_OVERVOLT					6
#define ERROR_LTC6811_UNDERVOLT					7
#define ERROR_LTC6811_INITIALTEST				8
#define ERROR_SDC_BTB							10
#define ERROR_SDC_MOTOR							11
#define ERROR_SDC_HVIL							12
#define ERROR_IMD								13
#define ERROR_AMS								14
#define ERROR_ADC								15
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
