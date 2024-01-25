//----------------------------------------------------------------------
// Titel	:	app_info.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jul 16, 2023
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "app_info.h"
#include "BatteriemanagementSystem.h"
//----------------------------------------------------------------------

void app_info(void)
{
  	// Teste serielle Schnittstelle
	#define START_STRING_UART		"!--- Batteriemanagement-System ---!\n"
	uartTransmit(START_STRING_UART, sizeof(START_STRING_UART));
	#define VERSION_STRING_UART		"Application Version: "
	uartTransmit(VERSION_STRING_UART, sizeof(VERSION_STRING_UART));
	uartTransmitNumber(MAJOR, 10);
	uartTransmit(".", 1);
	uartTransmitNumber(MINOR, 10);
	uartTransmit("\n", 1);

  	// Sammel Systeminformationen
  	collectSystemInfo();
	printResetSource(readResetSource());
}
