//----------------------------------------------------------------------
// Titel	:	stromsensor.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	15.08.2025
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Stromsensor IVT-Mod
// Quelle	:	
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_STROMSENSOR_H_
#define INC_STROMSENSOR_H_
//----------------------------------------------------------------------

// Inlude Dateien einfuegen
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define IVT_OVERCURRENT_TRESHOLD				1000						// Angabe in mA
#define IVT_OVERVOLTAGE1_TRESHOLD				15000						// Angabe in mV
#define IVT_UNDERVOLTAGE1_TRESHOLD				10000						// Angabe in mV
#define IVT_OVERVOLTAGE2_TRESHOLD				30000						// Angabe in mV
#define IVT_UNDERVOLTAGE2_TRESHOLD				20000						// Angabe in mV
#define IVT_OVERVOLTAGE3_TRESHOLD				30000						// Angabe in mV
#define IVT_UNDERVOLTAGE3_TRESHOLD				20000						// Angabe in mV
//----------------------------------------------------------------------

// Definiere CAN Strukturen
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t MessageID : 8;												// Byte 0
		uint8_t Counter : 4;												// Byte 1, Bit 0 - 3, Counter
		uint8_t OCS : 1;													// Byte 1, Bit 4, Overcurrent
		uint8_t channel_error : 1;											// Byte 1, Bit 5, Channel Error
		uint8_t measurement_error : 1;										// Byte 1, Bit 6, Measurment Error
		uint8_t system_error : 1;											// Byte 1, Bit 7, System Error
		int32_t result;														// Byte 2 - 5, Result
	};

	uint8_t data[6];														// 8 Byte
} stromsensor_ivtmod;
//----------------------------------------------------------------------

#endif /* INC_STROMSENSOR_H_ */
//----------------------------------------------------------------------
