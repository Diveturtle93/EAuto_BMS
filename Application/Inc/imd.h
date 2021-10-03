//----------------------------------------------------------------------
// Titel	:	imd.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	29.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_IMD_H_
#define INC_IMD_H_
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define IMD_KURZSCHLUSS_GND					0								// 0 = Kurzschluss gegen Masse, 0Hz
#define IMD_NORMAL							1								// 1 = Normalzustand, 10Hz
#define IMD_UNTERSPANNUNG					2								// 2 = bei Unterspannung, 20Hz
#define IMD_SCHNELLSTART					3								// 3 = Schnellstart-Messung, 30Hz
#define IMD_GERAETEFEHLER					4								// 4 = Geraetefehler, 40Hz
#define IMD_ANSCHLUSSFEHLER_ERDE			5								// 5 = Anschlussfehler gegen Erde, 50Hz
#define IMD_KURZSCHLUSS_KL15				6								// 6 = Kurzschluss gegen KL15, 0Hz
#define IMD_FREQ_ERROR						7								// 7 = IMD Error, Frequenz ausserhalb des gueltigen Bereiches
//----------------------------------------------------------------------

// ... definieren
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------

//----------------------------------------------------------------------

#endif /* INC_IMD_H_ */
//----------------------------------------------------------------------
