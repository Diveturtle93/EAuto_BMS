//----------------------------------------------------------------------
// Titel	:	adc_inputs.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	14.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	ADC Inputs
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_ADC_INPUTS_H_
#define INC_ADC_INPUTS_H_
//----------------------------------------------------------------------

// Define Debug Symbols
//----------------------------------------------------------------------
#define DEBUG_ADC_INPUTS
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
uint16_t readADC (uint8_t channel);											// Beliebigen Kanal einlesen
uint16_t ADC_STMTemperatur (void);											// STM Temperatursensor einlesen
uint16_t ADC_PCBTemperatur (void);											// PCB Temperatursensor einlesen
uint16_t ADC_KL15 (void);													// Spannung KL15 einlesen
uint16_t ADC_KL30_Relais (void);											// Spannung KL30, vor HV-Relais einlesen
uint16_t ADC_Temp1 (void);													// Temperatursensor 1 einlesen
uint16_t ADC_Temp2 (void);													// Temperatursensor 2 einlesen
uint16_t ADC_Temp3 (void);													// Temperatursensor 3 einlesen
uint16_t ADC_Temp4 (void);													// Temperatursensor 4 einlesen
//----------------------------------------------------------------------

#endif /* INC_ADC_INPUTS_H_ */
//----------------------------------------------------------------------
