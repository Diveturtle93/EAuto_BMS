//----------------------------------------------------------------------
// Titel	:	Error.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "error.h"
#include "BasicUart.h"
//----------------------------------------------------------------------

// Hal Error auswerten und ausgeben
//----------------------------------------------------------------------
void hal_error(uint8_t status)
{
#ifdef DEBUG
	if (status == HAL_OK) {													// HAL OK
		uartTransmit("HAL OK\n", 7);
	}
	else if (status == HAL_ERROR) {											// HAL Error
		uartTransmit("HAL ERROR\n", 10);
	}
	else if (status == HAL_BUSY) {											// HAL Beschaeftigt
		uartTransmit("HAL BUSY\n", 9);
	}
	else if (status == HAL_TIMEOUT) {										// HAL Timeout
		uartTransmit("HAL TIMEOUT\n", 12);
	}
#endif
}
//----------------------------------------------------------------------

// Diagnose Funktion falls ein Fehler auftritt
//----------------------------------------------------------------------
void software_error(uint8_t errorcode)
{
	__disable_irq();														// Interrupts deaktivieren
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);		// Fehler LED einschalten
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);	// Gruene LED ausschalten

#ifdef DEBUG																// Serielle Kommunukation nur waehrend Debugging
#define SOFTERRORMESSAGE			"\nError Handler ausgeloest\n"			// Ausgabe das Fehler aufgetreten ist
	uartTransmit(SOFTERRORMESSAGE,sizeof(SOFTERRORMESSAGE));

#define ERRORCODE					"Error Code:\t"							// Ausgabe des Fehlers anhand von Fehlercode
	uartTransmit(ERRORCODE,sizeof(ERRORCODE));
	uartTransmitNumber(errorcode, 10);										// Fehlercode ausgeben
#endif
	while (1)																// Endlosschleife
	{
	}
}
//----------------------------------------------------------------------
