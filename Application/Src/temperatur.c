//----------------------------------------------------------------------
// Titel	:	temperatur.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jan 12, 2024
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------
#include <math.h>
//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "temperatur.h"
#include "BatteriemanagementSystem.h"
//----------------------------------------------------------------------

// ADC-Wert in Temperatur umrechnen, NTC auf der PCB
//----------------------------------------------------------------------
float temperatur_PCB(uint16_t value)
{
	float resistor = 0.0, temperatur = 0.0;

	resistor = ((ADC_MAX_VALUE * ((PCB_RES1 * PCB_RES2) / (PCB_RES1 + PCB_RES2))) - ((ADC_MAX_VALUE - (float)value) * ((PCB_RES1 * PCB_RES2) / (PCB_RES1 + PCB_RES2)) / (ADC_MAX_VALUE - (float)value)));

	temperatur = (1 / ((1 / (PCB_TEMP0 + 273.15)) + (1 / PCB_B_VALUE * log(resistor / PCB_RES0))) - 273.15);

	return temperatur;
}
//----------------------------------------------------------------------

// ADC-Wert in Temperatur umrechnen, STM interner Temperatursensor
//----------------------------------------------------------------------
float temperatur_STM(uint16_t value)
{
	float temperatur = 0.0;
	temperatur = (float)((TEMP110 - TEMP30) / ((float)(*TEMP110_CAL_VALUE) - (float)(*TEMP30_CAL_VALUE)) * ((float)value - (float)(*TEMP30_CAL_VALUE)) + TEMP30);

	return temperatur;
}
//----------------------------------------------------------------------

// ADC-Wert in Temperatur umrechnen, Externe Temperatursensoren Temp1 - Temp4
//----------------------------------------------------------------------
float temperatur_Temp(uint16_t value)
{
	float resistor = 0.0, temperatur = 0.0;

	resistor = ((((ADC_MAX_VALUE * NTC_RES1) - ((ADC_MAX_VALUE - (float)value) * NTC_RES1) / (ADC_MAX_VALUE - (float)value)) * NTC_RES2) / (NTC_RES2 - ((ADC_MAX_VALUE * NTC_RES1) - ((ADC_MAX_VALUE - (float)value) * NTC_RES1) / (ADC_MAX_VALUE - (float)value))));

	temperatur = (1 / ((1 / (NTC_TEMP0 + 273.15)) + (1 / NTC_B_VALUE * log(resistor / NTC_RES0))) - 273.15);

	return temperatur;
}
//----------------------------------------------------------------------
