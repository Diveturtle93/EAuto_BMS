//----------------------------------------------------------------------
// Titel	:	AD8403.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	27.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Shutdown Pin				= Low, Wiper wird an Terminal B angeschlossen
// Shutdown Pin				= High, Alle anderen Funktionen gegeben
// RS Pin					= Low, Alle Poti Register werden auf Wiper Center gesetzt
// RS Pin Pulse				= positiv Pulse, Alle Potis werden auf Wiper Center gesetzt
// RS Pin					= High, Alle anderen Funktionen gegeben
// CS, RS und Shutdown		= High, No Operation

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_AD8403_H_
#define INC_AD8403_H_
//----------------------------------------------------------------------

// Addressen
//----------------------------------------------------------------------
#define AD8403_MUX0						0b10010000							// Poti 1
#define AD8403_MUX1						0b10010010							// Poti 2
#define AD8403_MUX2						0b10010100							// Poti 3
#define AD8403_MUX3						0b10010110							// Poti 4
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void initAD8403(void);														// Initialisiere AD8403
void setPoti(uint8_t addresse, uint8_t Data);								// Poti mit Daten fuellen
void setAllPoti(uint8_t Data);												// Alle Potis mit gleichen Daten fuellen
void PotiOff(uint8_t addresse);												// Poti ausschalten
void AllPotiOff(void);														// Alle Potis ausschalten
void AllPotiMidscale(void);													// Alle Potis auf halbe Stellung
//----------------------------------------------------------------------

#endif /* INC_AD8403_H_ */
//----------------------------------------------------------------------
