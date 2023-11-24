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

// Programmversion definieren
//----------------------------------------------------------------------
#define MAJOR 0																// Batteriemanagement Major Version Number
#define MINOR 1																// Batteriemanagement Minor Version Number
//----------------------------------------------------------------------

// Include Project Header
//----------------------------------------------------------------------
#include "BasicUart.h"
#include "AD8403.h"
#include "adc_inputs.h"
#include "app_info.h"
#include "CAN_Bus.h"
#include "error.h"
#include "imd.h"
#include "inputs.h"
#include "LTC1380.h"
#include "LTC6811.h"
#include "millis.h"
#include "my_math.h"
#include "outputs.h"
#include "SPI_resource.h"
#include "statemaschine.h"
#include "SystemInfo.h"
//----------------------------------------------------------------------

// Definiere Revision of Batteriemanagement HW PCB
//----------------------------------------------------------------------
//#if REVISION == 255
//#error "Revision ist nicht definiert"
//#elif REVISION == 1
//#warning "PCB Revision 1.0 definert"
//#elif REVISION == 2
//#warning "PCB Revision 1.1 definert"
//#endif
//----------------------------------------------------------------------

// Tischaufbau
//----------------------------------------------------------------------
#define TISCHAUFBAU									1						// 0 = Auto, 1 = Tischaufbau

//----------------------------------------------------------------------
#if TISCHAUFBAU == 1
#warning "Programm ist fuer Tischaufbau kompiliert!!"
#elif
#warning "Programm ist fuer Auto kompiliert!!"
#endif
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// TODO:

//----------------------------------------------------------------------

// CAN-IDs definieren
//----------------------------------------------------------------------
// Batteriemanagement-System neu
//----------------------------------------------------------------------
#define BMS_CAN_SAFETY								0x138					// Shutdown Circuit Batteriemanagement, Sicherheitsrelevante Daten
#define BMS_CAN_DIGITAL_OUT							0x237					// Digitale Ausgaenge Batteriemanagement, Alle digitalen Ausgaenge
#define BMS_CAN_DIGITAL_IN							0x238					// Digitale Eingaenge Batteriemanagement, Alle digitalen Eingaenge
#define BMS_CAN_ANALOG_IN							0x239					// Analogwerte Batteriemanagement, Spannung Relais, PCB
#define BMS_CAN_TEMPERATUR							0x538					// Temperatur Batteriemanagement, Temperatursensor 1 bis 4
#define BMS_CAN_STATUS								0x560					// Status BMS
#define BMS_CAN_IMD									0x565					// Status IMD
#define BMS_CAN_Zellen11							0x640					// Batterie-Zellen 1-4 Modul 1
#define BMS_CAN_Zellen12							0x641					// Batterie-Zellen 5-8 Modul 1
#define BMS_CAN_Zellen13							0x642					// Batterie-Zellen 9-12 Modul 1
#define BMS_CAN_Zellen21							0x643					// Batterie-Zellen 1-4 Modul 2
#define BMS_CAN_Zellen22							0x644					// Batterie-Zellen 5-8 Modul 2
#define BMS_CAN_Zellen23							0x645					// Batterie-Zellen 9-12 Modul 2
#define BMS_CAN_Temperatur11						0x740					// Batterie-Temperatur 1-4 Modul 1
#define BMS_CAN_Temperatur12						0x741					// Batterie-Temperatur 5-8 Modul 1
#define BMS_CAN_Temperatur13						0x742					// Batterie-Temperatur 9-12 Modul 1
#define BMS_CAN_Temperatur21						0x743					// Batterie-Temperatur 1-4 Modul 2
#define BMS_CAN_Temperatur22						0x744					// Batterie-Temperatur 5-8 Modul 2
#define BMS_CAN_Temperatur23						0x745					// Batterie-Temperatur 9-12 Modul 2
//----------------------------------------------------------------------
// Motorsteuergeraet neu
//----------------------------------------------------------------------
#define MOTOR_CAN_STATUS							0x505					// Motorsteuergeraet Status
#define MOTOR_CAN_DIGITAL_OUT						0x581					// Digitale Ausgaenge Motorsteuergeraet, Alle digitalen Ausgaenge
#define MOTOR_CAN_DIGITAL_IN						0x582					// Digitale Eingaenge Motorsteuergeraet, Alle digitalen Eingaenge
#define MOTOR_CAN_ANALOG_IN							0x583					// Analogwerte Motorsteuergeraet, Gaspedal, Bremsdruck, Info, Return, KlimaFlap, KL15
#define MOTOR_CAN_TEMPERATUR						0x584					// Temperatur Motorsteuergeraet, PCB, Bremsdrucktemperatur, Kuehlwassertemperatur
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
#define xy_CAN										0x011					// Einmalig gesendet wenn Schlüssel auf Stufe 2
//----------------------------------------------------------------------

//
//----------------------------------------------------------------------
#define CAN_TIMEOUT									3000					// Zeit bis CAN Timeout auftritt
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

	uint8_t status;									// 1 Byte
} BMS_states;
//----------------------------------------------------------------------

#endif /* INC_BATTERIEMANAGEMENTSYSTEM_H_ */
//----------------------------------------------------------------------
