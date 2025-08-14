//----------------------------------------------------------------------
// Titel	:	statemaschine.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	11.08.2025
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Statemaschine
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_STATEMASCHINE_H_
#define INC_STATEMASCHINE_H_
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define BMSTIME										300000					// Standby Zeit nach ausschalten KL15, 5min
#define ERROR_RESET									300000					// Zeit 5min bis Error Zurueckgesetzt werden kann
#define WARNING_RESET								30000					// Zeit 30s bis Warning Zurueckgesetzt werden kann
//----------------------------------------------------------------------

// Definiere Statemaschine Typedefines
//----------------------------------------------------------------------
typedef enum
{
	Start,																	// 0 Starte Batteriemanagement
	Ready,																	// 1 Batteriemanagement gestartet
	KL15,																	// 2 KL15 aktiv
	Anlassen,																// 3 Anlasser betaetigt
	Precharge,																// 4 Precharge Fahrzeug
	ReadyToDrive,															// 5 Batteriemanagement bereit fuer Fahrmodus
	Drive,																	// 6 Fahrzeug im Fahrmodus
	Standby,																// 7 Auto wird abgeschaltet, Zeitverzoegerung bis Batteriemanagement ausgeht
	Ausschalten,															// 8 Batteriemanagement ausschalten
	Laden,																	// 9 Lademodus
	StateNormal = 0x10,														// 16 Normalzustand
	StateWarning = 0x20,													// 32 Warnung
	StateError = 0x40,														// 64 Fehler
	CriticalError = 0x80,													// 128 Critischer Fehler
} states;
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t State : 4;													// State der Statemaschine
		uint8_t Normal : 1;													// Statemaschine Normal
		uint8_t Warning : 1;												// Statemaschine Warning
		uint8_t Error : 1;													// Statemaschine Error
		uint8_t CriticalError : 1;											// Statemaschine kritischer Error
	};

	uint8_t Status;									// 1 Byte
} Statemaschine;
//----------------------------------------------------------------------

// Definiere globale Variablen
//----------------------------------------------------------------------
extern Statemaschine BMSstate;												// Variable fuer BMS-Statemaschine definieren
extern uint32_t longError;													// Variable fuer Langzeit-Fehler, um Fehler eine bestimmte Zeit noch anzuzeigen, auch wenn nicht mehr vorhanden
extern uint32_t longWarning;												// Variable fuer Langzeit-Warnung, um Warnung eine bestimmte Zeit noch anzuzeigen, auch wenn nicht mehr vorhanden
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void setState (uint8_t state);												// State setzen
void setStatus (uint8_t status);											// Status setzen
//----------------------------------------------------------------------

#endif /* INC_STATEMASCHINE_H_ */
//----------------------------------------------------------------------
