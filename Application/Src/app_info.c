//----------------------------------------------------------------------
// Titel	:	app_info.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.07.2023
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	App Info
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

// Application Informationen sammeln
//----------------------------------------------------------------------
void app_info (void)
{
	// Teste serielle Schnittstelle
	#define START_STRING_UART		"!--- Batteriemanagement-System ---!\n"
	uartTransmit(START_STRING_UART, sizeof(START_STRING_UART));

	// Version der Software auf Uart ausgeben
	#define VERSION_STRING_UART		"Application Version: "
	uartTransmit(VERSION_STRING_UART, sizeof(VERSION_STRING_UART));
	uartTransmitNumber(BATTERIEMANAGEMENTSYSTEM_MAJOR, 10);
	uartTransmit(".", 1);
	uartTransmitNumber(BATTERIEMANAGEMENTSYSTEM_MINOR, 10);
	uartTransmit(".", 1);
	uartTransmitNumber(BATTERIEMANAGEMENTSYSTEM_PATCH, 10);
	uartTransmit(".", 1);
	uartTransmitNumber(BATTERIEMANAGEMENTSYSTEM_DEV, 10);
	uartTransmit("\n", 1);

  	// Sammelt Systeminformationen
  	collectSystemInfo();
	printResetSource(readResetSource());
}
//----------------------------------------------------------------------