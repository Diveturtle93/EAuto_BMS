//----------------------------------------------------------------------
// Titel	:	Inputs.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	31.03.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_INPUTS_H_
#define INC_INPUTS_H_
//----------------------------------------------------------------------

// Eingangsstrukturen definieren
//----------------------------------------------------------------------
union system_input_tag {
	struct {
		uint8_t IMD_PWM_STATUS : 3;				// 0 - 2					// 0 = Kurzschluss gegen Masse, 0Hz
																			// 1 = Normalzustand, 10Hz
																			// 2 = bei Unterspannung, 20Hz
																			// 3 = Schnellstart-Messung, 30Hz
																			// 4 = Geraetefehler, 40Hz
																			// 5 = Anschlussfehler gegen Erde, 50Hz
																			// 6 = Kurzschluss gegen KL15, 0Hz
																			// 7 = IMD Error, Frequenz ausserhalb des gueltigen Bereiches
		uint8_t IMD_PWM : 1;					// 3
		uint8_t KL15 : 1;						// 5
		uint8_t Crash : 1;						// 6
		uint8_t Wakeup : 1;						// 7
	};

	uint8_t systeminput;						// 1 Byte
} system_in;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
union sdc_in_tag {
	struct {
		uint8_t IMD_OK_IN : 1;					// 0
		uint8_t HVIL : 1;						// 1
		uint8_t MotorSDC : 1;					// 2
		uint8_t BTB_SDC : 1;					// 3
		uint8_t PrechargeIn : 1;				// 4
		uint8_t  : 1;							// 5
		uint8_t  : 1;							// 6
		uint8_t  : 1;							// 7
	};

	uint8_t sdcinput;							// 1 Byte
} sdc_in;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
union komfort_in_tag {
	struct {
		uint8_t OVC : 1;						// 0
		uint8_t Button1 : 1;					// 1
		uint8_t Button2 : 1;					// 2
		uint8_t  : 1;							// 3
		uint8_t  : 1;							// 4
		uint8_t  : 1;							// 5
		uint8_t  : 1;							// 6
		uint8_t  : 1;							// 7
	};

	uint8_t komfortinput;						// 1 Byte
} komfort_in;
//----------------------------------------------------------------------

// Definiere Konstanten
//----------------------------------------------------------------------
#define SYSTEM_INPUT					0b00000111							// 8 Bit, 6 Systemeingaenge
#define KOMFORT_INPUT					0b00000000							// 8 Bit, 1 Komforteingaenge
#define SDC_INPUT						0b00000000							// 8 Bit, 5 SDC-Eingaenge
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void readall_inputs(void);													// Lese alle Eingaenge
void read_sdc(void);														// Lese alle Pins vom SDC
//void read_
//----------------------------------------------------------------------

#endif /* INC_INPUTS_H_ */
//----------------------------------------------------------------------
