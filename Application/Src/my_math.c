//----------------------------------------------------------------------
// Titel	:	math.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	09.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "my_math.h"
//----------------------------------------------------------------------

// Gleitenden Mittelwert berechnen, sehr Speicher arm
//----------------------------------------------------------------------
int32_t calculateMovingAverage(uint16_t oldValue, uint16_t newValue, uint16_t n)
{
	return (oldValue + ((newValue - oldValue) / n));						// MovingAverage Calculation x_n  = x_{n-1} + ((x_n+x_{n-1})/n)
}
//----------------------------------------------------------------------

// Differenz Berechnen, Betrag
//----------------------------------------------------------------------
uint16_t getDifference(uint16_t a, uint16_t b)
{
	// A ist groesser B
	if (a > b)
	{
		// B von A abziehen
		return (a - b);
	}
	// B ist groesser A
	else if (a < b)
	{
		// A von B abziehen
		return (b - a);
	}
	// A ist gleich B
	else
	{
		// Differenz ist 0
		return 0;
	}
}
//----------------------------------------------------------------------
