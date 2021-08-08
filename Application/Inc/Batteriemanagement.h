//----------------------------------------------------------------------
// Titel	:	Batteriemanagement.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	08.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Audi_BMS
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_BATTERIEMANAGEMENT_H_
#define INC_BATTERIEMANAGEMENT_H_
//----------------------------------------------------------------------

// CAN-IDs definieren
//----------------------------------------------------------------------
// Batteriemanagement-System
#define BMS_CAN_SAFETY								0x140					// Shutdown Circuit Motorsteuergeraet, Sicherheitsrelevante Daten
#define BMS_CAN_DIGITAL_OUT							0x240					// Digitale Ausgaenge Motorsteuergeraet, Alle digitalen Ausgaenge
#define BMS_CAN_DIGITAL_IN							0x241					// Digitale Eingaenge Motorsteuergeraet, Alle digitalen Eingaenge
#define BMS_CAN_ANALOG_IN							0x242					// Analogwerte Motorsteuergerat, Gaspedal, Bremsdruck, Info, Return, KlimaFlap, KL15
#define BMS_CAN_TEMPERATUR_PCB						0x540					// Temperatur Motorsteuergeraet, PCB, Bremsdrucktemperatur, Kuehlwassertemperatur
//----------------------------------------------------------------------
// CAN-IDs auf dem BUS Fahrzeug intern
//----------------------------------------------------------------------
#define LENKWINKEL_CAN								0x0C2					// CAN ID Lenkwinkelsensor
#define BEMSE1_CAN									0x1A0
#define BEMSE2_CAN									0x4A0
#define BEMSE3_CAN									0x4A8
#define BEMSE4_CAN									0x5A0
#define KOMBI1_CAN									0x320
#define KOMBI2_CAN									0x420
#define KOMBI3_CAN									0x520
#define KLIMA_CAN									0x5E0
#define xxx_CAN										0x3D0
#define xx_CAN										0x5DE					// Immer aktive, außer im Sleep
#define x_CAN										0x010					// Einmalig gesendet wenn Schlüssel auf Stufe 2
#define xy_CAN										0x011					// EInmalig gesendet wenn Schlüssel auf Stufe 2
//----------------------------------------------------------------------

#endif /* INC_BATTERIEMANAGEMENT_H_ */
//----------------------------------------------------------------------
