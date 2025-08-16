//----------------------------------------------------------------------
// Titel	:	statemaschine.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	11.08.2025
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Statemaschine
// Quelle	:	
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
#include "statemaschine.h"
#include "BatteriemanagementSystem.h"
//----------------------------------------------------------------------

// Variablen einbinden
//----------------------------------------------------------------------
Statemaschine BMSstate = {{Start, true, false, false, false}};
static uint32_t timeError = 0, timeWarning = 0;
uint32_t longError = 0, longWarning = 0;
//----------------------------------------------------------------------

// Setze neuen State der Statemaschine
//----------------------------------------------------------------------
void setState(uint8_t State)
{
	// State auswaehlen
	switch (State)
	{
		case Ready:
		{
			// State setzen
			BMSstate.State = Ready;
			uartTransmit("Ready\n", 6);

			break;
		}
		case KL15:
		{
			// State setzen
			BMSstate.State = KL15;
			uartTransmit("KL15\n", 5);

			break;
		}
		case Anlassen:
		{
			// State setzen
			BMSstate.State = Anlassen;
			uartTransmit("Anlassen\n", 9);

			break;
		}
		case Precharge:
		{
			// State setzen
			BMSstate.State = Precharge;
			uartTransmit("Precharge\n", 10);

			break;
		}
		case ReadyToDrive:
		{
			// State setzen
			BMSstate.State = ReadyToDrive;
			uartTransmit("ReadyToDrive\n", 13);

			break;
		}
		case Drive:
		{
			// State setzen
			BMSstate.State = Drive;
			uartTransmit("Drive\n", 6);

			break;
		}
		case Laden:
		{
			// State setzen
			BMSstate.State = Laden;
			uartTransmit("Laden\n", 6);

			break;
		}
		case Standby:
		{
			// State setzen
			BMSstate.State = Standby;
			uartTransmit("Standby\n", 8);

			break;
		}
		case Ausschalten:
		{
			// State setzen
			BMSstate.State = Ausschalten;
			uartTransmit("Ausschalten\n", 12);

			break;
		}
		default:
		{
			break;
		}
	}
}
//----------------------------------------------------------------------

// Setze Fehler Status der Statemaschine
//----------------------------------------------------------------------
void setStatus(uint8_t Status)
{
	// Fehler Status setzen
	switch (Status & 0xF0)
	{
		case StateNormal:
		{
			// Wenn Fehler Status Warnung
			if (BMSstate.Status & StateWarning)
			{
				// Wenn letzte Warnung schon laenger als 30s nicht mehr aufgetreten
				if (millis() > (timeWarning + WARNING_RESET))
				{
					// Status zuruecksetzen
					BMSstate.Status = (Status | BMSstate.State);

					// Fehlervariablen zuruecksetzen
					longWarning = 0;
					longError = 0;
				}

				break;
			}
		}
		case StateWarning:
		{
			// Zeit abspeichern
			timeWarning = millis();

			// Wenn Fehler Status Error
			if (BMSstate.Status & StateError)
			{
				// Wenn letzter Error schon laenger als 5min nicht mehr aufgetreten
				if (millis() > (timeError + ERROR_RESET))
				{
					// Status zuruecksetzen
					BMSstate.Status = (StateWarning | BMSstate.State);
				}

				break;
			}
		}
		case StateError:
		{
			// Zeit abspeichern
			timeError = millis();

			// Wenn Fehler Status kritischer Fehler
			if (BMSstate.Status & CriticalError)
			{
				// Status setzen ueberspringen
				break;
			}
		}
		case CriticalError:
		{
			// Status setzen
			BMSstate.Status = (Status | BMSstate.State);
			break;
		}
		default:
		{
			// Status setzen
			BMSstate.Status = (CriticalError | BMSstate.State);

			// Fehlerausgabe wenn Status nicht korrekt
			uartTransmit("BMS Kritischer Fehler Statemaschine\n!", 36);
			break;
		}
	}
}
//----------------------------------------------------------------------
