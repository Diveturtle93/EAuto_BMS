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

	resistor = ((ADC_Max_Value * ((resistor1 * resistor2) / (resistor1 + resistor2))) - ((ADC_Max_Value - (float)value) * ((resistor1 * resistor2) / (resistor1 + resistor2)) / (ADC_Max_Value - (float)value)));

	temperatur = (1 / ((1 / (temperatur0 + 273.15)) + (1 / B_Value * log(resistor / resistor0))) - 273.15);

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
