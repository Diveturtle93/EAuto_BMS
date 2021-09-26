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

// Bruecke an A Kurzgeschlossen, Bruecke an B offen
// Digitaler Wert			Widerstand am Poti	, Errechneter Widerstand
// Poti = 0					=> 347 Ohm
// Poti = 35				=> 309 Ohm			, 312
// Poti = 56				=> 298 Ohm			, 291
// Poti = 98				=> 259 Ohm			, 249
// Poti = 128				=> 228 Ohm			, 219
// Poti = 156				=> 196 Ohm			, 191
// Poti = 197				=> 148 Ohm			, 150
// Poti = 213				=> 128 Ohm			, 134
// Poti = 237				=> 95 Ohm			, 110
// Poti = 255				=> 65 Ohm			, 92

// Bruecke an B Kurzgeschlossen, Bruecke an A offen
// Digitaler Wert			Widerstand am Poti	, Errechneter Widerstand
// Poti = 0					=> 65 Ohm			, 92
// Poti = 35				=> 95 Ohm			, 110
// Poti = 56				=> 128 Ohm			, 134
// Poti = 98				=> 148 Ohm			, 150
// Poti = 128				=> 196 Ohm			, 191
// Poti = 156				=> 228 Ohm			, 219
// Poti = 197				=> 259 Ohm			, 249
// Poti = 213				=> 298 Ohm			, 291
// Poti = 237				=> 309 Ohm			, 312
// Poti = 255				=> 347 Ohm

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_AD8403_H_
#define INC_AD8403_H_
//----------------------------------------------------------------------

// Addressen
//----------------------------------------------------------------------
#define AD8403_MUX0						0b00								// Poti 1
#define AD8403_MUX1						0b01								// Poti 2
#define AD8403_MUX2						0b10								// Poti 3
#define AD8403_MUX3						0b11								// Poti 4
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void initAD8403(void);														// Initialisiere AD8403
void setPoti(uint8_t addresse, uint8_t Data);								// Poti mit Daten fuellen
void setAllPoti(uint8_t Data);												// Alle Potis mit gleichen Daten fuellen
void PotiOff(uint8_t addresse);												// Poti ausschalten
void AllPotiOff(void);														// Alle Potis ausschalten
void AllPotiOn(void);														// Alle Potis einschalten
void AllPotiMidscale(void);													// Alle Potis auf halbe Stellung
//----------------------------------------------------------------------

#endif /* INC_AD8403_H_ */
//----------------------------------------------------------------------
