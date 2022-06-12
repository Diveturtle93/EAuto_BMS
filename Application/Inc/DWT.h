//----------------------------------------------------------------------
// Titel	:	DWT.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jun 12, 2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
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

// ... definieren
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void DWT_Enable(void);														// DWT Zaehler aktivieren
void DWT_CycCounterEn(void);												// DWT Zaehler einschalten
void DWT_CycCounterDis(void);												// DWT Zaehler ausschalten
uint32_t DWT_CycCounterRead(void);											// DWT Zaehler auslesen
void DWT_CycCounterClear(void);												// DWT Zaehler loeschen
//----------------------------------------------------------------------

#endif /* INC_DWT_H_ */
//----------------------------------------------------------------------
