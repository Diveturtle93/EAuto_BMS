//----------------------------------------------------------------------
// Titel	:	LTC6811.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	25.09.2020
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef LTC6811_H
#define LTC6811_H
//----------------------------------------------------------------------

// Include-Dateien einfuegen
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Definiere Debug Symbols
//----------------------------------------------------------------------
#ifdef DEBUG
//	#define DEBUG_ISOSPI
//	#define DEBUG_LTC6811
//	#define DEBUG_LTC6811_PEC
#endif
//----------------------------------------------------------------------

// Definiere Statemaschine Typedefines
//----------------------------------------------------------------------
// Definiere IsoSpi States
//----------------------------------------------------------------------
typedef enum IsoSpiState_tag {
	IsoIdle,																// Kommunikation unterbrochen
	IsoReady,																// Kommunikation kann durchgefuehrt werden
	IsoActive,																// Kommunikation wird durchgefuehrt
	IsoGetReady,															// Kommunikation wird vorbereitet
	IsoSleep,																// Kommunikation abgeschaltet
} IsoSpi_State;
//----------------------------------------------------------------------
// Definiere LTC6811 States
//----------------------------------------------------------------------
typedef enum LTC6811State_tag {
	LTCStandby,																// IC im Standby, Referenzspannung inaktiv, Beide Timer laufen
	LTCMeasure,																// Messung am ADC wird durchgefuehrt
	LTCRefup,																// Referenzspannung aktiv
	LTCSetRefup,															// Referenzspannung wird vorbereitet
	LTCWakeup,																// IC wird geweckt
	LTCExtendedBalancing,													// Balancing aktiv, Watchdog Timer ausgeschaltet, Entladetimer läuft
	LTCSleep																// IC im Sleep, keine Aktion, Beide Timer ausgeschaltet
} LTC6811_State;
//----------------------------------------------------------------------

// Allgemeine Einstellungen
//----------------------------------------------------------------------
#define LTC6811_DEVICES				1										// Anzahl Chips im Daisy-Chain
#define LTC6811_CELLS				12										// Anzahl Zellen pro Chip
#define LTC6811_UVOLT				2000									// Unterspannung einer Zelle		3.2 = 2000 * 16 * 100µV, Spannung = VUV * 16 * 100µV, VUV muss im Register stehen
#define LTC6811_OVOLT				2625									// Ueberspannung einer Zelle		4.2 = 2625 * 16 * 100µV, Spannung = VOV * 16 * 100µV, VOV muss im Register stehen
#define LTC6811_SOC					25200									// Summe der Zellspannungen an einem LTC6811	50.4 = 25200 * 20 * 100µV, Spannung = SC * 20 * 100µV, SC muss im Register stehen
#define LTC6811_UTEMP				45200									// Untertemperatur einer Zelle, 0°C
#define LTC6811_OTEMP				13070									// Uebertemperatur einer Zelle, 65°C
#define LTC6811_PCB_UTEMP			33000									// Untertemperatur der PCB, 0°C
#define LTC6811_PCB_OTEMP			5760									// Uebertemperatur der PCB, 65°C
#define LTC6811_DEVUTEMP			20475									// Untertemperatur des Chips, 0°C	ITMP * 100µV / 7500µV/°C - 273°C, 20475µV * 100µV / 7500µV/°C - 273°C = 0
#define LTC6811_DEVOTEMP			25350									// Uebertemperatur des Chips, 65°C	ITMP * 100µV / 7500µV/°C - 273°C, 25350µV * 100µV / 7500µV/°C - 273°C = 65
#define OPENWIRE_THRESHOLD			4000									// Openwire Threshold
#define LTC6811_TIMEOUT				1800									// Timeout fuer Watchdog, 1.8s
#define SEC_UVOLT					29850									// Second Referenzvoltage Untergrenze
#define SEC_OVOLT					30150									// Second Referenzvoltage Obergrenze
#define ANALOG_UVOLT				45000									// Analogvoltage Untergrenze
#define ANALOG_OVOLT				55000									// Analogvoltage Obergrenze
#define DIGITAL_UVOLT				27000									// Digitalvoltage Untergrenze
#define DIGITAL_OVOLT				36000									// Digitalvoltage Obergrenze
//----------------------------------------------------------------------

// Command Codes definieren (Datasheet ltc6811 Page 49, Table 34)
//----------------------------------------------------------------------
// Configuration Register
//----------------------------------------------------------------------
#define WRCFG						0b00000000001							// Write Configuration
#define RDCFG						0b00000000010							// Read Configuration
#define WRCFGA						0b00000000001							// Write Configuration A, only LTC6812 / LTC6813
#define RDCFGA						0b00000000010							// Read Configuration A, only LTC6812 / LTC6813
#define WRCFGB						0b00000100100							// Write Configuration B, only LTC6812 / LTC6813
#define RDCFGB						0b00000100110							// Read Configuration B, only LTC6812 / LTC6813
//----------------------------------------------------------------------

// Cell Voltage Register
//----------------------------------------------------------------------
#define RDCVA						0b00000000100							// Read Cell 1 - 3
#define RDCVB						0b00000000110							// Read Cell 4 - 6
#define RDCVC						0b00000001000							// Read Cell 7 - 9
#define RDCVD						0b00000001010							// Read Cell 10 - 12
#define RDCVE						0b00000001001							// Read Cell 13 - 15, only LTC6812 / LTC6813
#define RDCVF						0b00000001011							// Read Cell 16 - 18, only LTC6812 / LTC6813
//----------------------------------------------------------------------

// Auxilliary Register
//----------------------------------------------------------------------
#define RDAUXA						0b00000001100							// Read Auxilliary Register Group A
#define RDAUXB						0b00000001110							// Read Auxilliary Register Group B
#define RDAUXC						0b00000001101							// Read Auxilliary Register Group C, only LTC6812 / LTC6813
#define RDAUXD						0b00000001111							// Read Auxilliary Register Group D, only LTC6812 / LTC6813
//----------------------------------------------------------------------

// Status Register
//----------------------------------------------------------------------
#define RDSTATA						0b00000010000							// Read Status Register Group A
#define RDSTATB						0b00000010010							// Read Status Register Group B
//----------------------------------------------------------------------

// Start Commands															// ADCOPT = 0	, ADCOPT = 1
//----------------------------------------------------------------------
#define MD1422						0b00000000000							// 422 Hz		, 1 kHz
#define MD2714						0b00010000000							// 27 kHz		, 14 kHz
#define MD73						0b00100000000							// 7 kHz		, 3 kHz
#define MD262						0b00110000000							// 26 Hz		, 2 kHz
//----------------------------------------------------------------------
#define ST1							0b00000100000							// Selftest 1
#define ST2							0b00001000000							// Selftest 2
//----------------------------------------------------------------------
#define DCP							0b00000010000							// Discharge Permitted
//----------------------------------------------------------------------

#define ADCVC						0b01001100000							// Start ADC Cell Conversion
//----------------------------------------------------------------------
#define CELLALL						0b00000000000							// Read All Cells
#define CELL17						0b00000000001							// Read Cell 1 & 7
#define CELL28						0b00000000010							// Read Cell 2 & 8
#define CELL39						0b00000000011							// Read Cell 3 & 9
#define CELL410						0b00000000100							// Read Cell 4 & 10
#define CELL511						0b00000000101							// Read Cell 5 & 11
#define CELL612						0b00000000110							// Read Cell 6 & 12
//----------------------------------------------------------------------

#define ADOW						0b01000101000							// Start ADC Open Wire Conversion
//----------------------------------------------------------------------
#define PUP							0b00001000000							// Pull-up Current
//----------------------------------------------------------------------

//----------------------------------------------------------------------
#define CVST						0b01000000111							// Start Self-Test Cell Conversion

#define ADOL						0b01000000001							// Start overlapping measurement of cell 7
//----------------------------------------------------------------------

#define ADAX						0b10001100000							// Start GPIO ADC Conversion
#define ADAXD						0b10000000000							// Start GPIO ADC Conversion with redundancy check
//----------------------------------------------------------------------
#define GPIOALL						0b00000000000							// Read All GPIO & Reference
#define GPIO1						0b00000000001							// Read GPIO 1
#define GPIO2						0b00000000010							// Read GPIO 2
#define GPIO3						0b00000000011							// Read GPIO 3
#define GPIO4						0b00000000100							// Read GPIO 4
#define GPIO5						0b00000000101							// Read GPIO 5
#define SECREF						0b00000000110							// Read Reference
//----------------------------------------------------------------------

#define AUXST						0b10000000111							// Start Self-Test GPIO Conversion

#define ADSTAT						0b10001101000							// Start Status ADC Conversion
#define ADSTATD						0b10000001000							// Start Status ADC Conversion with redundancy check
//----------------------------------------------------------------------
#define STATALL						0b00000000000							// Read All Status
#define STATSOC						0b00000000001							// Read SOC Status
#define STATITMP					0b00000000010							// Read ITMP Status
#define STATVA						0b00000000011							// Read VA Status
#define STATVD						0b00000000100							// Read VD Status
//----------------------------------------------------------------------

//----------------------------------------------------------------------
#define STATST						0b10000001111							// Start Self-Test Status ADC Conversion

#define ADCVAX						0b10001101111							// Start Combined Cell, GPIO1 & GPIO 2 Conversion
#define ADCVSC						0b10001100111							// Start Combined Cell, SC Conversion
//----------------------------------------------------------------------

// S Controll Commands
//----------------------------------------------------------------------
#define WRSCTRL						0b00000010100							// Write S Control Register
#define RDSCTRL						0b00000010110							// Read S Control Register
#define WRPWM						0b00000100000							// Write PWM Register Group
#define WRPSB						0b00000011100							// Write PWM and S Control Register
#define RDPWM						0b00000100010							// Read PWM Register Group
#define RDPSB						0b00000011110							// Read PWM and S Control Register B
#define STSCTRL						0b00000011001							// Starte S Control Pulsing
//----------------------------------------------------------------------

// Clear Commands
//----------------------------------------------------------------------
#define CLRCELL						0b11100010001							// Clear Cell Voltage Register Group
#define CLRAUX						0b11100010010							// Clear Auxilliary Register Group
#define CLRSTAT						0b11100010011							// Clear Status Register Group
#define CLRSCTRL					0b00000011000							// Clear S Control Register
//----------------------------------------------------------------------

// ADC Conversion Status und Diagnose Status
//----------------------------------------------------------------------
#define PLADC						0b11100010100							// Poll ADC Conversion Status Register
#define DIAGN						0b11100010101							// Diagnose Mux and Poll Register
//----------------------------------------------------------------------

// Communication Register
//----------------------------------------------------------------------
#define WRCOMM						0b11100100001							// Write Communication Register Group
#define RDCOMM						0b11100100010							// Read Communication Register Group
#define STCOMM						0b11100100011							// Start Communication I2C / SPI
//----------------------------------------------------------------------

// Definiere Chip-Select Leitung
//----------------------------------------------------------------------
#define ISOCS_ENABLE() (HAL_GPIO_WritePin(ISOSPI_CS_GPIO_Port, ISOSPI_CS_Pin, GPIO_PIN_RESET))		// Chip-Select enable
#define ISOCS_DISABLE() (HAL_GPIO_WritePin(ISOSPI_CS_GPIO_Port, ISOSPI_CS_Pin, GPIO_PIN_SET))		// Chip-Select disable
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
// IsoSPI Funktionen
//----------------------------------------------------------------------
void set_IsoSpiState (IsoSpi_State newState);								// Setze neuen State von IsoSPI
void IsoSPI_statemaschine (void);											// Auswertung State von IsoSPI
IsoSpi_State get_IsoSpiState (void);											// Bekomme aktuellen State von IsoSPI
void IsoSPI_wakeup (void);													// Aufwachfunktion fuer IsoSPI
void IsoSPI_cmd (uint8_t* command);											// Sende Command ueber IsoSPI
void IsoSPI_transmit (uint8_t* command, uint8_t* data);						// Sende Daten ueber IsoSPI
void IsoSPI_read (uint8_t* command, uint8_t* data);							// Lese Daten ueber IsoSPI
//----------------------------------------------------------------------
// LTC Funktionen
//----------------------------------------------------------------------
void set_ltc6811_state (LTC6811_State newState);							// Setze neuen Stat von LTC6811
void ltc6811_statemaschine (void);											// Auswertung State von LTC6811
LTC6811_State get_ltc6811_state (void);										// Bekomme aktuellen State von LTC6811
void ltc6811 (uint16_t command);											// LTC6811 Commando
void ltc6811_write (uint16_t command, uint8_t *data);						// Schreibfunktion LTC6811
bool ltc6811_read (uint16_t command, uint8_t *data);						// Lesefunktion LTC6811
uint16_t peccommand (uint16_t command);										// CRC Berechnung Command, 16 Bit
uint16_t peclookup (uint8_t len,	uint8_t *data);							// CRC Berechnung Daten Array, 8 Bit
bool peccheck (uint8_t len, uint8_t *data);									// CRC Validieren und pruefen
void ltc6811_init (void);													// Initialisiere LTC6811, Konfigurierung
uint8_t ltc6811_check (void);												// Diagnose LTC6811, fuehrt alle Tests durch
bool ltc6811_test (uint16_t command);										// Diagnose Selbsttest Test 1 und 2
bool ltc6811_thermal (void);												// Diagnose Thermal Shutdown
bool ltc6811_diagn (void);													// Diagnose Multiplexer
bool ltc6811_openwire (void);												// Leitungscheck offene Leitung
uint16_t ltc6811_poll (void);												// Poll Data nach Conversion
uint16_t ltc6811_timeout (void);											// Rueckgabe welches Module timeout hat
bool ltc6811_validate_balance (void);										// Validieren der Balancer Mosfets
//----------------------------------------------------------------------
//void init_crc(void);														// Wird benoetigt um Pec-Tabelle zu berechnen
//----------------------------------------------------------------------

// Definiere Zellenarray
//----------------------------------------------------------------------
typedef union __ltc6811_configuration_tag {
	struct {
		uint8_t ADCOPT : 1;													// ADC Mode Option
		uint8_t SWTRD : 1;													// SWT Pin
		uint8_t REFON : 1;													// Reference voltage shutdown
		uint8_t LTC_GPIO1 : 1;												// GPIO 1
		uint8_t LTC_GPIO2 : 1;												// GPIO 2
		uint8_t LTC_GPIO3 : 1;												// GPIO 3
		uint8_t LTC_GPIO4 : 1;												// GPIO 4
		uint8_t LTC_GPIO5 : 1;												// GPIO 5
		uint32_t VUV : 12;													// Undervoltage Treshold
		uint32_t VOV : 12;													// Overvoltage Treshold
		uint8_t DCC1 : 1;													// Zelle 1 Balancing
		uint8_t DCC2 : 1;													// Zelle 2 Balancing
		uint8_t DCC3 : 1;													// Zelle 3 Balancing
		uint8_t DCC4 : 1;													// Zelle 4 Balancing
		uint8_t DCC5 : 1;													// Zelle 5 Balancing
		uint8_t DCC6 : 1;													// Zelle 6 Balancing
		uint8_t DCC7 : 1;													// Zelle 7 Balancing
		uint8_t DCC8 : 1;													// Zelle 8 Balancing
		uint8_t DCC9 : 1;													// Zelle 9 Balancing
		uint8_t DCC10 : 1;													// Zelle 10 Balancing
		uint8_t DCC11 : 1;													// Zelle 11 Balancing
		uint8_t DCC12 : 1;													// Zelle 12 Balancing
		uint8_t DCTO : 4;													// Timeout fuer Balancing
	};

	uint8_t configuration[6];												// Array fuer COnfiguration Register
} ltc6811_configuration_tag;
//----------------------------------------------------------------------

//----------------------------------------------------------------------
extern ltc6811_configuration_tag ltc6811_Conf;								// LTC6811 Configurations Register
//----------------------------------------------------------------------

#endif /* INC_LTC6811_H_ */
//----------------------------------------------------------------------
