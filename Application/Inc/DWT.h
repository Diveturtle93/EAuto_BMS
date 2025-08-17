//----------------------------------------------------------------------
// Titel	:	DWT.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	12.06.2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Data Watchpoint Trigger
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_DWT_H_
#define INC_DWT_H_
//----------------------------------------------------------------------

// Include-Dateien einfuegen
//----------------------------------------------------------------------
#include <stdint.h>
//----------------------------------------------------------------------

// Define Debug Symbols
//----------------------------------------------------------------------
#ifdef DEBUG
//	#define DEBUG_DWT
#endif
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void DWT_Init(void);														// DWT Zaehler initialisieren
void DWT_Enable(void);														// DWT Zaehler aktivieren
void DWT_CycCounterEn(void);												// DWT Zaehler einschalten
void DWT_CycCounterDis(void);												// DWT Zaehler ausschalten
uint32_t DWT_CycCounterRead(void);											// DWT Zaehler auslesen
void DWT_CycCounterClear(void);												// DWT Zaehler loeschen
//----------------------------------------------------------------------

#endif /* INC_DWT_H_ */
//----------------------------------------------------------------------
