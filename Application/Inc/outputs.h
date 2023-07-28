//----------------------------------------------------------------------
// Titel	:	Outputs.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	31.03.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_OUTPUTS_H_
#define INC_OUTPUTS_H_
//----------------------------------------------------------------------

// Strukturen definieren
//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t AmsLimit : 1;					// 0
		uint8_t ImdOK : 1;						// 1
		uint8_t AmsOK : 1;						// 2
		uint8_t Freigabe : 1;					// 3
		uint8_t Recuperation : 1;				// 4
		uint8_t HV_P : 1;						// 5
		uint8_t HV_N : 1;						// 6
		uint8_t Power_On : 1;					// 7
	};

	uint8_t systemoutput;						// Byte
} system_out_tag;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t Digital1 : 1;					// 0
		uint8_t Digital2 : 1;					// 1
		uint8_t PrechargeOut : 1;				// 2
		uint8_t HV_M : 1;						// 3
		uint8_t HV_CHG : 1;						// 4
		uint8_t  : 1;							// 5
		uint8_t Heater1 : 1;					// 6
		uint8_t Heater2 : 1;					// 7
	};

	uint8_t high_out;							// Byte
} highcurrent_out_tag;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t InletRed : 1;					// 0
		uint8_t InletGreen : 1;					// 1
		uint8_t AkkuErrorLed : 1;				// 2
		uint8_t  : 1;							// 3
		uint8_t  : 1;							// 4
		uint8_t RedLed : 1;						// 5
		uint8_t GreenLed : 1;					// 6
		uint8_t BlueLed : 1;					// 7
	};

	uint8_t ledoutput;							// 1 Byte
} leuchten_out_tag;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
typedef union
{
	struct
	{
		uint8_t TriggerOut : 1;					// 0
		uint8_t IsoSPI_EN : 1;					// 1
		uint8_t IsoHV_EN : 1;					// 2
		uint8_t  : 1;							// 3
		uint8_t  : 1;							// 4
		uint8_t  : 1;							// 5
		uint8_t  : 1;							// 6
		uint8_t  : 1;							// 7
	};

	uint8_t komfortoutput;						// 1 Byte
} komfort_out_tag;
//----------------------------------------------------------------------

// Definiere Konstanten
//----------------------------------------------------------------------
#define SYSTEM_OUTPUT				0b00000000								// 8 Bit, 8 Systemausgaenge
#define HIGH_OUTPUT					0b00000000								// 8 Bit, 7 Hochstromfaehige Ausgaenge
#define LED_OUTPUT					0b11100111								// 8 Bit, 6 Leuchtdioden
#define KOMFORT_OUTPUT				0b00000000								// 8 Bit, 1 Komfortausgaenge
//----------------------------------------------------------------------

// Definiere globale Variablen
//----------------------------------------------------------------------
extern system_out_tag system_out;											// Variable fuer Systemausgaenge definieren
extern highcurrent_out_tag highcurrent_out;									// Variable fuer Highcurrentausgaenge definieren
extern leuchten_out_tag leuchten_out;										// Variable fuer Leuchtenausgaenge definieren
extern komfort_out_tag komfort_out;											// Variable fuer Komfortausgaenge definieren
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void init_outputs(void);													// Initialisiere Ausgaenge
void writeall_outputs(void);												// Schreibe alle Ausgaenge
void writeled_outputs(void);												// Schreibe alle LED-Ausgaenge
void testPCB_Leds(void);													// Teste PCB LEDs fuer je 1s
void testLeds(void);														// Teste LEDs fuer je 1s
void setLadekontrolle(void);												// Ladekontrolle setzen
void resetLadekontrolle(void);												// Ladekontrolle zuruecksetzen
//----------------------------------------------------------------------

#endif /* INC_OUTPUTS_H_ */
//----------------------------------------------------------------------
