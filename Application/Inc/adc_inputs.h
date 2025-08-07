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

// Konstanten definieren
//----------------------------------------------------------------------
//#define TEMP_SENSOR_AVG_SLOPE_MV_PER_CELSIUS			2.5f
//#define TEMP_SENSOR_VOLTAGE_MV_AT_25					760.0f
//#define ADC_REFERENCE_VOLTAGE_MV						3300.0f
//#define ADC_MAX_OUTPUT_VALUE							4095.0f
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
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
