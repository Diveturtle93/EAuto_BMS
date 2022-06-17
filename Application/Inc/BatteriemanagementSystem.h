//----------------------------------------------------------------------
// Titel	:	BatteriemanagementSystem.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	29.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_BATTERIEMANAGEMENTSYSTEM_H_
#define INC_BATTERIEMANAGEMENTSYSTEM_H_
//----------------------------------------------------------------------

// CAN-IDs definieren
//----------------------------------------------------------------------
// Batteriemanagement-System neu
//----------------------------------------------------------------------
#define BMS_CAN_SAFETY								0x138					// Shutdown Circuit Batteriemanagement-System, Sicherheitsrelevante Daten
#define BMS_CAN_DIGITAL_OUT							0x237					// Digitale Ausgaenge Batteriemanagement-System, Alle digitalen Ausgaenge
#define BMS_CAN_DIGITAL_IN							0x238					// Digitale Eingaenge Batteriemanagement-System, Alle digitalen Eingaenge
#define BMS_CAN_ANALOG_IN							0x239					// Analogwerte Batteriemanagement-System, KL30 Relais, PCB
#define BMS_CAN_TEMPERATUR							0x538					// Temperature Batteriemanagement-System, Temperaturen Heizung 4x
#define BMS_CAN_ZELLEN11							0x610					// Batterie-Zellen 1-4 Modul 1
#define BMS_CAN_ZELLEN12							0x611					// Batterie-Zellen 5-8 Modul 1
#define BMS_CAN_ZELLEN13							0x612					// Batterie-Zellen 9-12 Modul 1
#define BMS_CAN_ZELLEN21							0x613					// Batterie-Zellen 1-4 Modul 2
#define BMS_CAN_ZELLEN22							0x614					// Batterie-Zellen 5-8 Modul 2
#define BMS_CAN_ZELLEN23							0x615					// Batterie-Zellen 9-12 Modul 2
#define BMS_CAN_ZELLEN31							0x616					// Batterie-Zellen 1-4 Modul 3
#define BMS_CAN_ZELLEN32							0x617					// Batterie-Zellen 5-8 Modul 3
#define BMS_CAN_ZELLEN33							0x618					// Batterie-Zellen 9-12 Modul 3
#define BMS_CAN_ZELLEN41							0x619					// Batterie-Zellen 1-4 Modul 4
#define BMS_CAN_ZELLEN42							0x620					// Batterie-Zellen 5-8 Modul 4
#define BMS_CAN_ZELLEN43							0x621					// Batterie-Zellen 9-12 Modul 4
#define BMS_CAN_ZELLEN51							0x622					// Batterie-Zellen 1-4 Modul 5
#define BMS_CAN_ZELLEN52							0x623					// Batterie-Zellen 5-8 Modul 5
#define BMS_CAN_ZELLEN53							0x624					// Batterie-Zellen 9-12 Modul 5
#define BMS_CAN_ZELLEN61							0x625					// Batterie-Zellen 1-4 Modul 6
#define BMS_CAN_ZELLEN62							0x626					// Batterie-Zellen 5-8 Modul 6
#define BMS_CAN_ZELLEN63							0x627					// Batterie-Zellen 9-12 Modul 6
#define BMS_CAN_ZELLEN71							0x628					// Batterie-Zellen 1-4 Modul 7
#define BMS_CAN_ZELLEN72							0x629					// Batterie-Zellen 5-8 Modul 7
#define BMS_CAN_ZELLEN73							0x630					// Batterie-Zellen 9-12 Modul 7
#define BMS_CAN_ZELLEN81							0x631					// Batterie-Zellen 1-4 Modul 8
#define BMS_CAN_ZELLEN82							0x632					// Batterie-Zellen 5-8 Modul 8
#define BMS_CAN_ZELLEN83							0x633					// Batterie-Zellen 9-12 Modul 8
#define BMS_CAN_TEMPERATUR11						0x640					// Batterie-Temperatur 1-4 Modul 1
#define BMS_CAN_TEMPERATUR12						0x641					// Batterie-Temperatur 5-8 Modul 1
#define BMS_CAN_TEMPERATUR13						0x642					// Batterie-Temperatur 9-12 Modul 1
#define BMS_CAN_TEMPERATUR14						0x643					// Batterie-Temperatur 13-16 Modul 1
#define BMS_CAN_TEMPERATUR21						0x644					// Batterie-Temperatur 1-4 Modul 2
#define BMS_CAN_TEMPERATUR22						0x645					// Batterie-Temperatur 5-8 Modul 2
#define BMS_CAN_TEMPERATUR23						0x646					// Batterie-Temperatur 9-12 Modul 2
#define BMS_CAN_TEMPERATUR24						0x647					// Batterie-Temperatur 13-16 Modul 2
#define BMS_CAN_TEMPERATUR31						0x648					// Batterie-Temperatur 1-4 Modul 3
#define BMS_CAN_TEMPERATUR32						0x649					// Batterie-Temperatur 5-8 Modul 3
#define BMS_CAN_TEMPERATUR33						0x650					// Batterie-Temperatur 9-12 Modul 3
#define BMS_CAN_TEMPERATUR34						0x651					// Batterie-Temperatur 13-16 Modul 3
#define BMS_CAN_TEMPERATUR41						0x652					// Batterie-Temperatur 1-4 Modul 4
#define BMS_CAN_TEMPERATUR42						0x653					// Batterie-Temperatur 5-8 Modul 4
#define BMS_CAN_TEMPERATUR43						0x654					// Batterie-Temperatur 9-12 Modul 4
#define BMS_CAN_TEMPERATUR44						0x655					// Batterie-Temperatur 13-16 Modul 4
#define BMS_CAN_TEMPERATUR51						0x656					// Batterie-Temperatur 1-4 Modul 5
#define BMS_CAN_TEMPERATUR52						0x657					// Batterie-Temperatur 5-8 Modul 5
#define BMS_CAN_TEMPERATUR53						0x658					// Batterie-Temperatur 9-12 Modul 5
#define BMS_CAN_TEMPERATUR54						0x659					// Batterie-Temperatur 13-16 Modul 5
#define BMS_CAN_TEMPERATUR61						0x660					// Batterie-Temperatur 1-4 Modul 6
#define BMS_CAN_TEMPERATUR62						0x661					// Batterie-Temperatur 5-8 Modul 6
#define BMS_CAN_TEMPERATUR63						0x662					// Batterie-Temperatur 9-12 Modul 6
#define BMS_CAN_TEMPERATUR64						0x663					// Batterie-Temperatur 13-16 Modul 6
#define BMS_CAN_TEMPERATUR71						0x664					// Batterie-Temperatur 1-4 Modul 7
#define BMS_CAN_TEMPERATUR72						0x665					// Batterie-Temperatur 5-8 Modul 7
#define BMS_CAN_TEMPERATUR73						0x666					// Batterie-Temperatur 9-12 Modul 7
#define BMS_CAN_TEMPERATUR74						0x667					// Batterie-Temperatur 13-16 Modul 7
#define BMS_CAN_TEMPERATUR81						0x668					// Batterie-Temperatur 1-4 Modul 8
#define BMS_CAN_TEMPERATUR82						0x669					// Batterie-Temperatur 5-8 Modul 8
#define BMS_CAN_TEMPERATUR83						0x670					// Batterie-Temperatur 9-12 Modul 8
#define BMS_CAN_TEMPERATUR84						0x671					// Batterie-Temperatur 13-16 Modul 8
//----------------------------------------------------------------------
// Motorsteuergeraet neu
//----------------------------------------------------------------------
#define MOTOR_CAN_SAFETY							0x139					// Shutdown Circuit Motorsteuergeraet, Sicherheitsrelevante Daten
#define MOTOR_CAN_DIGITAL_OUT						0x240					// Digitale Ausgaenge Motorsteuergeraet, Alle digitalen Ausgaenge
#define MOTOR_CAN_DIGITAL_IN						0x241					// Digitale Eingaenge Motorsteuergeraet, Alle digitalen Eingaenge
#define MOTOR_CAN_ANALOG_IN							0x242					// Analogwerte Motorsteuergerat, Gaspedal, Bremsdruck, Info, Return, KlimaFlap, KL15
#define MOTOR_CAN_TEMPERATUR						0x539					// TEMPERATUR Motorsteuergeraet, PCB, Bremsdrucktemperatur, Kuehlwassertemperatur
//----------------------------------------------------------------------
// Motorsteuergeraet alt
//----------------------------------------------------------------------
#define MOTOR_CAN_DREHZAHL							0x280					// Motorsteuergeraet ID MotorSTG1
#define MOTOR_CAN_MOTOR2							0x288					// Motorsteuergeraet ID MotorSTG2
#define MOTOR_CAN_GASPEDAL							0x380					// Motorsteuergeraet ID MotorSTG3
#define MOTOR_CAN_GRA								0x388					// Motorsteuergeraet ID MotorSTG4
#define MOTOR_CAN_LEUCHTEN							0x480					// Motorsteuergeraet ID MotorSTG5
#define MOTOR_CAN_GAS								0x488					// Motorsteuergeraet ID MotorSTG6
#define MOTOR_CAN_FLEXIA							0x580					// Motorsteuergeraet ID MotorFlexia
//----------------------------------------------------------------------
// CAN-IDs auf dem BUS
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

// Definiere Statemaschine Typedefines
//----------------------------------------------------------------------
// Definiere Batteriemanagement-System States
//----------------------------------------------------------------------
typedef enum BMSState_tag
{
	BMSStart,																// Batteriemanagement wird gestartet
	BMSSleep,																// Batteriemanagement liegt im schlafen
	BMSStandby,																// Batteriemanagement ist im Standby
	BMSGetReady,															// Precharge wird vorbereitet
	BMSPrecharge,															// Akkukasten wird vorgeladen
	BMSActive,																// Akkukasten ist Bereit und Aktiv
	BMSFreigabe,															// Freigabe zur Leistungsentnahme
	BMSDisable,																// Akkukasten vorbereiten zum abschalten
	BMSDischarge,															// Akkukasten abschalten
	BMSCharge,																// Akkukasten Laden
} BMSState;
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------

//----------------------------------------------------------------------

#endif /* INC_BATTERIEMANAGEMENTSYSTEM_H_ */
//----------------------------------------------------------------------
