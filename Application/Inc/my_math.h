//----------------------------------------------------------------------
// Titel	:	my_math.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	30.01.2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_MATH_H_
#define INC_MATH_H_
//----------------------------------------------------------------------

// Include-Dateien einfuegen
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Define Debug Symbols
//----------------------------------------------------------------------
#define DEBUG_MATH
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
static uint16_t calculateMovingAverage(uint16_t oldValue, uint16_t newValue, uint16_t n);		// Gleitenden Mittelwert berechnen
static uint16_t getDifference(uint16_t a, uint16_t b);						// Differenzberechnung

// Gleitenden Mittelwert berechnen, sehr Speicher arm
//----------------------------------------------------------------------
static uint16_t calculateMovingAverage(uint16_t oldValue, uint16_t newValue, uint16_t n)
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
//----------------------------------------------------------------------

#endif /* INC_MATH_H_ */
//----------------------------------------------------------------------
