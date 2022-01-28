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

// Eingangsstrukturen definieren
//----------------------------------------------------------------------
union imd_tag {
	struct {
		uint8_t PWM_STATUS : 3;					// 0 - 2					// 0 = Kurzschluss gegen Masse, 0Hz
																			// 1 = Normalzustand, 10Hz
																			// 2 = bei Unterspannung, 20Hz
																			// 3 = Schnellstart-Messung, 30Hz
																			// 4 = Geraetefehler, 40Hz
																			// 5 = Anschlussfehler gegen Erde, 50Hz
																			// 6 = Kurzschluss gegen KL15, 0Hz
																			// 7 = IMD Error, Frequenz ausserhalb des gueltigen Bereiches
		uint8_t Frequency : 6;					// Frequenz abspeichern
		uint8_t DutyCycle : 7;					// Duty-Cycle abspeichern
		uint32_t Resistanc : 18;				// Widerstand abspeichern
	};

	uint8_t status[5];							// 5 Byte
} imd;
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
void imd_status(void);														// IMD OK einlesen
//----------------------------------------------------------------------

#endif /* INC_IMD_H_ */
//----------------------------------------------------------------------
