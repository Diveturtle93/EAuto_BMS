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
#define BMS_CAN_ANALOG_IN							0x538					// Analog Eingaenge Batteriemanagement-System, PCB, Temperaturen, KL30-Relais
#define BMS_CAN_ERROR								0x640					// Error BMS
#define BMS_CAN_Zellen11							0x641					// Batterie-Zellen 1-4 Modul 1
#define BMS_CAN_Zellen12							0x642					// Batterie-Zellen 5-8 Modul 1
#define BMS_CAN_Zellen13							0x643					// Batterie-Zellen 9-12 Modul 1
#define BMS_CAN_Zellen21							0x644					// Batterie-Zellen 1-4 Modul 2
#define BMS_CAN_Zellen22							0x645					// Batterie-Zellen 5-8 Modul 2
#define BMS_CAN_Zellen23							0x646					// Batterie-Zellen 9-12 Modul 2
#define BMS_CAN_Temperatur11						0x741					// Batterie-Temperatur 1-4 Modul 1
#define BMS_CAN_Temperatur12						0x742					// Batterie-Temperatur 5-8 Modul 1
#define BMS_CAN_Temperatur13						0x743					// Batterie-Temperatur 9-12 Modul 1
#define BMS_CAN_Temperatur21						0x744					// Batterie-Temperatur 1-4 Modul 2
#define BMS_CAN_Temperatur22						0x745					// Batterie-Temperatur 5-8 Modul 2
#define BMS_CAN_Temperatur23						0x746					// Batterie-Temperatur 9-12 Modul 2

//----------------------------------------------------------------------
// Motorsteuergeraet neu
//----------------------------------------------------------------------
#define MOTOR_CAN_SAFETY							0x139					// Shutdown Circuit Motorsteuergeraet, Sicherheitsrelevante Daten
#define MOTOR_CAN_DIGITAL_OUT						0x240					// Digitale Ausgaenge Motorsteuergeraet, Alle digitalen Ausgaenge
#define MOTOR_CAN_DIGITAL_IN						0x241					// Digitale Eingaenge Motorsteuergeraet, Alle digitalen Eingaenge
#define MOTOR_CAN_ANALOG_IN							0x242					// Analogwerte Motorsteuergerat, Gaspedal, Bremsdruck, Info, Return, KlimaFlap, KL15
#define MOTOR_CAN_TEMPERATUR						0x539					// Temperatur Motorsteuergeraet, PCB, Bremsdrucktemperatur, Kuehlwassertemperatur
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

// Funktionen definieren
//----------------------------------------------------------------------

//----------------------------------------------------------------------

#endif /* INC_BATTERIEMANAGEMENTSYSTEM_H_ */
//----------------------------------------------------------------------
