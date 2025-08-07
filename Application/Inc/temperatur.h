//----------------------------------------------------------------------
// Titel	:	temperatur.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jan 12, 2024
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_TEMPERATUR_H_
#define INC_TEMPERATUR_H_
//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
#define ADC_MAX_VALUE									4095.0f				// Maximale ADC-Schritte
//----------------------------------------------------------------------

// Konstanten fuer PCB NTC definieren, NTCS0603E3472FHT
//----------------------------------------------------------------------
#define PCB_RES0										4700.0f				// R0 @25°C von NTC
#define PCB_RES1										10000.0f			// Vorwiderstand 1 der Parallelschaltung
#define PCB_RES2										10000.0f			// Vorwiderstand 2 der Parallelschaltung
#define PCB_TEMP0										25.0f				// T0 des NTCs
#define PCB_B_VALUE										3830.0f				// B-Wert des NTCs
//----------------------------------------------------------------------

// Konstanten fuer STM Temperatursensor definieren
//----------------------------------------------------------------------
#define TEMP110_CAL_VALUE								((uint16_t*)((uint32_t)0x1FF0F44E))	// Register fuer Calibrierwert des STM bei 110°C
#define TEMP30_CAL_VALUE								((uint16_t*)((uint32_t)0x1FF0F44C))	// Register fuer Calibrierwert des STM bei 30°C
#define TEMP110											110.0f				// Temperatur fuer oberen Calibrierwert
#define TEMP30											30.0f				// Temperatur fuer unteren Calibrierwert
//----------------------------------------------------------------------

// Konstanten fuer externen NTC definieren, NTCLE100E3103HT1
//----------------------------------------------------------------------
#define NTC_RES0										10000.0f			// R0 @25°C von NTC
#define NTC_RES1										10000.0f			// Vorwiderstand
#define NTC_RES2										100000.0f			// Parallelwiderstand zum NTC
#define NTC_TEMP0										25.0f				// T0 des NTCs
#define NTC_B_VALUE										3977.0f				// B-Wert des NTCs
//----------------------------------------------------------------------

// Konstanten fuer PCB NTC definieren, NTCS0603E3472FHT
//----------------------------------------------------------------------
#define PCB_SLAVE_RES0									4700.0f				// R0 @25°C von NTC
#define PCB_SLAVE_RES1									10000.0f			// Vorwiderstand
#define PCB_SLAVE_TEMP0									25.0f				// T0 des NTCs
#define PCB_SLAVE_B_VALUE								3830.0f				// B-Wert des NTCs
#define PCB_SLAVE_REFVOLT								5.3f				// Referenzspannung am LTC6811
//----------------------------------------------------------------------

// Konstanten fuer PCB NTC definieren, NTCS0603E3472FHT
//----------------------------------------------------------------------
#define PCB_CELL_RES0									4700.0f				// R0 @25°C von NTC
#define PCB_CELL_RES1									3300.0f				// Vorwiderstand
#define PCB_CELL_RES2									100000.0f			// Parallelwiderstand zum NTC
#define PCB_CELL_TEMP0									25.0f				// T0 des NTCs
#define PCB_CELL_B_VALUE								3830.0f				// B-Wert des NTCs
#define PCB_CELL_REFVOLT								5.3f				// Referenzspannung am LTC6811
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
float temperatur_PCB (uint16_t value);										// PCB Temperatur BMS-Master
float temperatur_STM (uint16_t value);										// STM32 internal Temperatur
float temperatur_Temp (uint16_t value);										// Temperatursensor BMS-Master
float temperatur_PCB_Slave (uint16_t value);								// PCB Temperatur BMS-Slave
float temperatur_Cell_Temp (uint16_t value);								// Zelltemperatur BMS
//----------------------------------------------------------------------

#endif /* INC_TEMPERATUR_H_ */
//----------------------------------------------------------------------
