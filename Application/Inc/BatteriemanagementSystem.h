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
#include "batteriemanagement.h"
#include "CAN_Bus.h"
#include "DWT.h"
#include "error.h"
#include "HardFault.h"
#include "imd.h"
#include "inputs.h"
#include "LTC1380.h"
#include "LTC6811.h"
#include "millis.h"
#include "my_math.h"
#include "outputs.h"
#include "ResetReason.h"
#include "SPI_resource.h"
#include "statemaschine.h"
#include "stromsensor.h"
#include "SystemInfo.h"
#include "temperatur.h"
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

// Definiere Debug Symbols
//----------------------------------------------------------------------
#ifdef DEBUG
//	#define DEBUG_ZYKLUS
#endif
//----------------------------------------------------------------------

// Tischaufbau
//----------------------------------------------------------------------
#define TISCHAUFBAU									1						// 0 = Auto, 1 = Tischaufbau
//----------------------------------------------------------------------

// Motorsteuergeraet vorhanden
//----------------------------------------------------------------------
#define MOTOR_AVAILABLE								0						// 0 = Nicht vorhanden, 1 = vorhanden
#define IMD_AVAILABLE								0						// 0 = Nicht vorhanden, 1 = vorhanden
#define BAMOCAR_AVAILABLE							0						// 0 = Nicht vorhanden, 1 = vorhanden
#define STROM_HV_AVAILABLE							1						// 0 = Nicht vorhanden, 1 = vorhanden
#define STROM_LV_AVAILABLE							0						// 0 = Nicht vorhanden, 1 = vorhanden
#define KOMBIINSTRUMENT_AVAILABLE					0						// 0 = Nicht vorhanden, 1 = vorhanden
//----------------------------------------------------------------------


//----------------------------------------------------------------------
#if TISCHAUFBAU == 1
	#warning "Programm ist fuer Tischaufbau kompiliert!!"
#else
	#warning "Programm ist fuer Auto kompiliert!!"
#endif
//----------------------------------------------------------------------

// Definiere Konstante fuer vorderen und hinteren Akkukasten
//----------------------------------------------------------------------
#define BMS_VORNE									1						// 0 = Nicht vorne, 1 = vorne
#define BMS_HINTEN									0						// 0 = Nicht hinten, 1 = hinten
//----------------------------------------------------------------------
#if (BMS_VORNE == 1 && BMS_HINTEN == 1)
	#error "BMS kann nicht fuer hinten und vornde gleichzeitig kompiliert werden!!!"
#endif
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
#define BMS_CAN_ZELLEN11							0x640					// Batterie-Zellen 1-4 Modul 1
#define BMS_CAN_ZELLEN12							0x641					// Batterie-Zellen 5-8 Modul 1
#define BMS_CAN_ZELLEN13							0x642					// Batterie-Zellen 9-12 Modul 1
#define BMS_CAN_ZELLEN21							0x643					// Batterie-Zellen 1-4 Modul 2
#define BMS_CAN_ZELLEN22							0x644					// Batterie-Zellen 5-8 Modul 2
#define BMS_CAN_ZELLEN23							0x645					// Batterie-Zellen 9-12 Modul 2
#define BMS_CAN_ZELLEN31							0x646					// Batterie-Zellen 1-4 Modul 3
#define BMS_CAN_ZELLEN32							0x647					// Batterie-Zellen 5-8 Modul 3
#define BMS_CAN_ZELLEN33							0x648					// Batterie-Zellen 9-12 Modul 3
#define BMS_CAN_ZELLEN41							0x649					// Batterie-Zellen 1-4 Modul 4
#define BMS_CAN_ZELLEN42							0x650					// Batterie-Zellen 5-8 Modul 4
#define BMS_CAN_ZELLEN43							0x651					// Batterie-Zellen 9-12 Modul 4
#define BMS_CAN_ZELLEN51							0x652					// Batterie-Zellen 1-4 Modul 5
#define BMS_CAN_ZELLEN52							0x653					// Batterie-Zellen 5-8 Modul 5
#define BMS_CAN_ZELLEN53							0x654					// Batterie-Zellen 9-12 Modul 5
#define BMS_CAN_ZELLEN61							0x655					// Batterie-Zellen 1-4 Modul 6
#define BMS_CAN_ZELLEN62							0x656					// Batterie-Zellen 5-8 Modul 6
#define BMS_CAN_ZELLEN63							0x657					// Batterie-Zellen 9-12 Modul 6
#define BMS_CAN_ZELLEN71							0x658					// Batterie-Zellen 1-4 Modul 7
#define BMS_CAN_ZELLEN72							0x659					// Batterie-Zellen 5-8 Modul 7
#define BMS_CAN_ZELLEN73							0x660					// Batterie-Zellen 9-12 Modul 7
#define BMS_CAN_ZELLEN81							0x661					// Batterie-Zellen 1-4 Modul 8
#define BMS_CAN_ZELLEN82							0x662					// Batterie-Zellen 5-8 Modul 8
#define BMS_CAN_ZELLEN83							0x663					// Batterie-Zellen 9-12 Modul 8
#define BMS_CAN_TEMPERATUR11						0x740					// Batterie-Temperatur 1-4 Modul 1
#define BMS_CAN_TEMPERATUR12						0x741					// Batterie-Temperatur 5-8 Modul 1
#define BMS_CAN_TEMPERATUR13						0x742					// Batterie-Temperatur 9-12 Modul 1
#define BMS_CAN_TEMPERATUR14						0x743					// Batterie-Temperatur 13-16 Modul 1
#define BMS_CAN_TEMPERATUR21						0x744					// Batterie-Temperatur 1-4 Modul 2
#define BMS_CAN_TEMPERATUR22						0x745					// Batterie-Temperatur 5-8 Modul 2
#define BMS_CAN_TEMPERATUR23						0x746					// Batterie-Temperatur 9-12 Modul 2
#define BMS_CAN_TEMPERATUR24						0x747					// Batterie-Temperatur 13-16 Modul 2
#define BMS_CAN_TEMPERATUR31						0x748					// Batterie-Temperatur 1-4 Modul 3
#define BMS_CAN_TEMPERATUR32						0x749					// Batterie-Temperatur 5-8 Modul 3
#define BMS_CAN_TEMPERATUR33						0x750					// Batterie-Temperatur 9-12 Modul 3
#define BMS_CAN_TEMPERATUR34						0x751					// Batterie-Temperatur 13-16 Modul 3
#define BMS_CAN_TEMPERATUR41						0x752					// Batterie-Temperatur 1-4 Modul 4
#define BMS_CAN_TEMPERATUR42						0x753					// Batterie-Temperatur 5-8 Modul 4
#define BMS_CAN_TEMPERATUR43						0x754					// Batterie-Temperatur 9-12 Modul 4
#define BMS_CAN_TEMPERATUR44						0x755					// Batterie-Temperatur 13-16 Modul 4
#define BMS_CAN_TEMPERATUR51						0x756					// Batterie-Temperatur 1-4 Modul 5
#define BMS_CAN_TEMPERATUR52						0x757					// Batterie-Temperatur 5-8 Modul 5
#define BMS_CAN_TEMPERATUR53						0x758					// Batterie-Temperatur 9-12 Modul 5
#define BMS_CAN_TEMPERATUR54						0x759					// Batterie-Temperatur 13-16 Modul 5
#define BMS_CAN_TEMPERATUR61						0x760					// Batterie-Temperatur 1-4 Modul 6
#define BMS_CAN_TEMPERATUR62						0x761					// Batterie-Temperatur 5-8 Modul 6
#define BMS_CAN_TEMPERATUR63						0x762					// Batterie-Temperatur 9-12 Modul 6
#define BMS_CAN_TEMPERATUR64						0x763					// Batterie-Temperatur 13-16 Modul 6
#define BMS_CAN_TEMPERATUR71						0x764					// Batterie-Temperatur 1-4 Modul 7
#define BMS_CAN_TEMPERATUR72						0x765					// Batterie-Temperatur 5-8 Modul 7
#define BMS_CAN_TEMPERATUR73						0x766					// Batterie-Temperatur 9-12 Modul 7
#define BMS_CAN_TEMPERATUR74						0x767					// Batterie-Temperatur 13-16 Modul 7
#define BMS_CAN_TEMPERATUR81						0x768					// Batterie-Temperatur 1-4 Modul 8
#define BMS_CAN_TEMPERATUR82						0x769					// Batterie-Temperatur 5-8 Modul 8
#define BMS_CAN_TEMPERATUR83						0x770					// Batterie-Temperatur 9-12 Modul 8
#define BMS_CAN_TEMPERATUR84						0x771					// Batterie-Temperatur 13-16 Modul 8
#define BMS_CAN_INT_TEMPERATUR1						0x772					// Temperatur LTC6811 ICs 1 - 4
#define BMS_CAN_INT_TEMPERATUR2						0x773					// Temperatur LTC6811 ICs 5 - 8
#define BMS_CAN_INT_TEMPERATUR3						0x774					// Temperatur Passiv Discharge 1 - 4
#define BMS_CAN_INT_TEMPERATUR4						0x775					// Temperatur Passiv Discharge 5 - 8
#define BMS_CAN_STACKVOLTAGE						0x776					// Gesamtspannung BMS berechnet
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
// Bamocar
//----------------------------------------------------------------------
#define BAMOCAR_CAN_RX								0x181					// Bamocar Empfangs ID
#define BAMOCAR_CAN_TX								0x210					// Bamocar Sende ID
//----------------------------------------------------------------------
// Stromsensor HV-Kreis
//----------------------------------------------------------------------
#define STROM_HV_COMMAND_RX							0x411					// Befehl an Stromsensor senden
#define STROM_HV_COMMAND_TX							0x511					// Befehl von Stromsensor empfanden
#define STROM_HV_CAN_I								0x521					// Aktueller Stromverbrauch
#define STROM_HV_CAN_U1								0x522					// Aktuelle Spannung U1
#define STROM_HV_CAN_U2								0x523					// Aktuelle Spannung U2
#define STROM_HV_CAN_U3								0x524					// Aktuelle Spannung U3
#define STROM_HV_CAN_T								0x525					// Aktuelle Temperatur
#define STROM_HV_CAN_W								0x526					// Power (U1 x I)
#define STROM_HV_CAN_AS								0x527					// Gesamtstromverbrauch
#define STROM_HV_CAN_WH								0x528					// Gesamtenergie (U1 x I)
//----------------------------------------------------------------------
// Stromsensor LV-Kreis
//----------------------------------------------------------------------
//#define STROM_LV_COMMAND_RX							0x412					// Befehl an Stromsensor senden
//#define STROM_LV_COMMAND_TX							0x512					// Befehl von Stromsensor empfanden
//#define STROM_LV_CAN_I								0x531					// Aktueller Stromverbrauch
//#define STROM_LV_CAN_U1								0x532					// Aktuelle Spannung U1
//#define STROM_LV_CAN_U2								0x533					// Aktuelle Spannung U2
//#define STROM_LV_CAN_U3								0x534					// Aktuelle Spannung U3
//#define STROM_LV_CAN_T								0x535					// Aktuelle Temperatur
//#define STROM_LV_CAN_W								0x536					// Power (U1 x I)
//#define STROM_LV_CAN_AS								0x537					// Gesamtstromverbrauch
//#define STROM_LV_CAN_WH								0x538					// Gesamtenergie (U1 x I)
//----------------------------------------------------------------------

// Zeit Konstanten festlegen
//----------------------------------------------------------------------
#define CAN_TIMEOUT									10000					// Zeit 10s bis CAN Timeout auftritt
#define HVRELAISTIME								5000					// Zeit 5s bis HV-Relais ausgeschaltet wird nach wegnahme Freigabe
#define BMS_WORK_TIME								100						// Zeitintervall fuer BMS-Abfrage
//----------------------------------------------------------------------

#endif /* INC_BATTERIEMANAGEMENTSYSTEM_H_ */
//----------------------------------------------------------------------
