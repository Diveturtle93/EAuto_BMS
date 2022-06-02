//----------------------------------------------------------------------
// Titel	:	math.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	09.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

#include <stdio.h>

static int calculateMovingAverage(int oldValue, int newValue, int n);
static uint16_t getDifference(uint16_t a, uint16_t b);

// Gleitenden Mittelwert berechnen, sehr Speicher arm
//----------------------------------------------------------------------
static int calculateMovingAverage(int oldValue, int newValue, int n)
{
	return (oldValue + ((newValue - oldValue) / n));						// MovingAverage Calculation x_n  = x_{n-1} + ((x_n+x_{n-1})/n)
}
//----------------------------------------------------------------------

// Differenz Berechnen, Betrag
//----------------------------------------------------------------------
static uint16_t getDifference(uint16_t a, uint16_t b)
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
