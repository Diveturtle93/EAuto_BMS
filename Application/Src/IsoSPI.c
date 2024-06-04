//----------------------------------------------------------------------
// Titel	:	IsoSPI.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	03.06.2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "spi.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "LTC6811.h"
#include "millis.h"
//----------------------------------------------------------------------

// Definiere Globale Variable
//----------------------------------------------------------------------
static IsoSpi_State IsoSpiState;											// Statusvariable Statemaschine
uint32_t timeIsoSpiState;													// Time Variable fuer State
//----------------------------------------------------------------------

// Setze Statemaschine IsoSPI
//----------------------------------------------------------------------
void set_IsoSpiState(IsoSpi_State newState)
{
	IsoSpiState = newState;													// Neuen Status setzen
	timeIsoSpiState = millis();												// Zeit speichern

#ifdef DEBUG_ISOSPI
	ITM_SendString("IsoSPI: ");

	ITM_SendString(" Neuer State: ");

	switch (IsoSpiState)
	{
		case IsoIdle:
			ITM_SendString("Idle\n");
			break;

		case IsoActive:
			ITM_SendString("Active\n");
			break;

		case IsoReady:
			ITM_SendString("Ready\n");
			break;

		case IsoGetReady:
			ITM_SendString("GetReady\n");
			break;

		case IsoSleep:
			ITM_SendString("Sleep\n");
			break;

		default:
			ITM_SendString("#RED#FEHLER\n");
			break;
	}
#endif
}
//----------------------------------------------------------------------

// Setze Statemaschine ISOSpi
//----------------------------------------------------------------------
void IsoSPI_statemaschine(void)
{
	switch (IsoSpiState)
	{
		case IsoIdle:
			break;

		case IsoGetReady:
			if (millis() > (timeIsoSpiState + 1))
			{
				IsoSpiState = IsoReady;
			}
			break;

		case IsoReady:
			if (millis() > (timeIsoSpiState + 4))
			{
				IsoSpiState = IsoIdle;
			}
			break;

		case IsoActive:
			break;

		case IsoSleep:
			break;

		default:
			break;
	}
}
//----------------------------------------------------------------------

// Bekomme aktuellen State ISOSpi
//----------------------------------------------------------------------
IsoSpi_State get_IsoSpiState(void)
{
	// Statemaschine abfragen
	IsoSPI_statemaschine();

	// Aktuellen State ausgeben
	return IsoSpiState;
}
//----------------------------------------------------------------------

// Wakeup LTC6811 idle
//----------------------------------------------------------------------
void IsoSPI_wakeup(void)
{
	// Debug Nachricht
#ifdef DEBUG_ISOSPI
	ITM_SendString("IsoSPI wird geweckt.\n");
#endif

	// Wenn Statemaschine Idle ist, dann IsoSPI wecken
	if (get_IsoSpiState() == IsoIdle)
	{
		for(uint8_t i = 0; i < LTC6811_DEVICES; i++)							// Wiederholen fuer Anzahl Slaves
		{
			// ISOCS einschalten
			ISOCS_ENABLE();														// Chip-Select einschalten

			// Dummy Paket senden
			HAL_SPI_Transmit(&hspi4, (uint8_t*) 0xAA, 1, 100);					// Chip wecken, isoSPI braucht Zeit bis ready

			// ISOCS ausschalten
			ISOCS_DISABLE();													// Chip-Select ausschalten
		}

		// Setze Statemaschine auf GetReady
		set_IsoSpiState(IsoGetReady);

		// Warten das bis Ready
		while(get_IsoSpiState() == IsoGetReady);
	}
}
//----------------------------------------------------------------------

// Sende Command
//----------------------------------------------------------------------
void IsoSPI_cmd(uint8_t* command)
{
	// Debug Nachricht
#ifdef DEBUG_ISOSPI
	ITM_SendString("Aufruf von IsoSPI_cmd\n");
#endif

	// Verzoegerungszeit zum wecken des LTC6811
	IsoSPI_wakeup();

	// ISOCS einschalten
	ISOCS_ENABLE();

	// Setze State auf Aktiv
	set_IsoSpiState(IsoActive);

	// Command uebertragen
	HAL_SPI_Transmit(&hspi4, command, 4, 100);

	// Wenn Command = STCOMM ist dann muessen noch 72 Takte uebertragen werden
	if (((command[0] << 8) | command[1]) == STCOMM)
	{
		// 72 = 9 * 8 Bit Daten
		for (uint8_t i = 0; i < 9; i++)
		{
			// Dummy-Byte uebertragen
			HAL_SPI_Transmit(&hspi4, (uint8_t*) 0xAA, 1, HAL_MAX_DELAY);
		}
	}

	// ISOCS ausschalten
	ISOCS_DISABLE();
	// Ende der Uebertragung

	// Setze State auf Ready
	set_IsoSpiState(IsoReady);

	// Debug Nachricht
#ifdef DEBUG_ISOSPI
	ITM_SendString("Command wurde gesendet.\n");
	ITM_SendString("Folgendes wurde gesendet:");

	// Sende Command auf UART
	for (uint8_t i = 0; i < 4; i++)
	{
		ITM_SendChar(' ');
		ITM_SendNumber(command[i]);
	}
	ITM_SendChar('\n');
#endif
}
//----------------------------------------------------------------------

// Sende Daten
//----------------------------------------------------------------------
void IsoSPI_transmit(uint8_t* command, uint8_t* data)
{
	// Debug Nachricht
#ifdef DEBUG_ISOSPI
	ITM_SendString("Aufruf von IsoSPI Datentransmit\n");
#endif

	// Verzoegerungszeit zum wecken des IsoSPI
	IsoSPI_wakeup();

	// ISOCS einschalten
	ISOCS_ENABLE();

	// Setze State auf Aktiv
	set_IsoSpiState(IsoActive);

	// Command uebertragen
	HAL_SPI_Transmit(&hspi4, command, 4, 100);

	// Data senden
	HAL_SPI_Transmit(&hspi4, data, (8 * LTC6811_DEVICES), 100);

	// ISOCS ausschalten
	ISOCS_DISABLE();
	// Ende der Uebertragung

	// Setze Statemaschine auf Ready;
	set_IsoSpiState(IsoReady);

	// Debug Nachricht
#ifdef DEBUG_ISOSPI
	ITM_SendString("Command wurde gesendet.\n");
	ITM_SendString("Folgendes wurde gesendet:");

	// Sende Command auf UART
	for (uint8_t i = 0; i < 4; i++)
	{
		ITM_SendChar(' ');
		ITM_SendNumber(command[i]);
	}
	ITM_SendChar('\n');
#endif
}
//----------------------------------------------------------------------

// Lese Daten
//----------------------------------------------------------------------
void IsoSPI_read(uint8_t* command, uint8_t* data)
{
	// Debug Nachricht
#ifdef DEBUG_ISOSPI
	ITM_SendString("Aufruf von Receive LTC6811.\n");
#endif

	// Verzoegerungszeit zum wecken des IsoSPI
	IsoSPI_wakeup();

	// ISOCS einschalten
	ISOCS_ENABLE();

	// Setze State auf Aktiv
	set_IsoSpiState(IsoActive);

	// Command uebertragen
	HAL_SPI_Transmit(&hspi4, command, 4, 100);

	// Data empfangen
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Dummy Byte senden
		HAL_SPI_Receive(&hspi4, &data[i*8], 8, 100);
	}

	// ISOCS ausschalten
	ISOCS_DISABLE();
	// Ende der Uebertragung

	// Setze Statemaschine auf Ready;
	set_IsoSpiState(IsoReady);

	// Debug Nachricht
#ifdef DEBUG_ISOSPI
	ITM_SendString("Command wurde empfangen.\n");
	ITM_SendString("Folgendes wurde empfangen:");

	// Sende Command auf UART
	for (uint8_t i = 0; i < 4; i++)
	{
		ITM_SendChar(' ');
		ITM_SendNumber(command[i]);
	}
	ITM_SendChar('\n');

	ITM_SendString("Daten wurde empfangen.\n");
	ITM_SendString("Folgendes wurde empfangen:");

	// Sende Daten auf UART
	for (uint8_t i = 0; i < (8 * LTC6811_DEVICES); i++)
	{
		ITM_SendChar(' ');
		ITM_SendNumber(data[i]);
	}
	ITM_SendChar('\n');
#endif
}
//----------------------------------------------------------------------
