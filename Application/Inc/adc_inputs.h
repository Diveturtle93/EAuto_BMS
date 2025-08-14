//----------------------------------------------------------------------
// Titel	:	adc_inputs.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	14.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
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
uint16_t readADC (uint8_t channel);
uint16_t ADC_STMTemperatur (void);
uint16_t ADC_PCBTemperatur (void);
uint16_t ADC_KL15 (void);
uint16_t ADC_KL30_Relais (void);
uint16_t ADC_Temp1 (void);
uint16_t ADC_Temp2 (void);
uint16_t ADC_Temp3 (void);
uint16_t ADC_Temp4 (void);
//----------------------------------------------------------------------

#endif /* INC_ADC_INPUTS_H_ */
//----------------------------------------------------------------------
