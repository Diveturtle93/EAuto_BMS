//----------------------------------------------------------------------
// Titel	:	stromsensor.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	15.08.2025
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Stromsensor IVT-Mod
// Quelle	:	
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "stromsensor.h"
#include "BatteriemanagementSystem.h"
//----------------------------------------------------------------------

// Globale Variablen definieren
//----------------------------------------------------------------------
uint8_t count = 0;
uint8_t incoming_CAN[8] = {0};
//----------------------------------------------------------------------

// Send Trigger, Hardware Trigger
//----------------------------------------------------------------------
void ivtTrigger (void)
{
	// TODO: Signal nach 200ms wieder abschalten
	komfort_out.TriggerOut = true;											// Signal muss 200ms anliegen
}
//----------------------------------------------------------------------

// Konfiguriere Result
//----------------------------------------------------------------------
bool ivtResultConfig (void)
{
	// CAN Message zuruecksetzen
	for (uint8_t i = 0; i < 8; i++)
	{
		CAN_Output_PaketListe[8].msg.buf[i] = 0;
	}

	// Auswaehlen Nachrichten status
	switch (count)
	{
		// Starte Konfiguration
		// Stoppe Stromsensor
		case 0:
		{
			// CAN Nachricht fuer Stop definieren, einmal senden
			CAN_Output_PaketListe[8].msg.buf[0] = 0x34;						// Set Mode
			CAN_Output_PaketListe[8].msg.buf[1] = 0;						// Runmode Stop
			CAN_Output_PaketListe[8].msg.buf[2] = 1;						// Startup Mode Run

			// Nachricht senden
			CANwrite(&CAN_Output_PaketListe[8].msg, false);

			// Zaehler hochzaehlen
			count++;
			break;
		}
		// Antwort abwarten
		case 1:
		{
			// Abfrage ob ankommende Nachricht von Stromsensor auf B4 ist
			if (incoming_CAN[0] == 0xB4)
			{
				// Zaehler hochzaehlen
				count++;
			}
			break;
		}
		// Senden der Konfiguration
		case 2:
		{
			// CAN Nachricht fuer Set Config definieren, einmal senden
			CAN_Output_PaketListe[8].msg.buf[0] = 0x21;						// Set Config Result U1
			CAN_Output_PaketListe[8].msg.buf[1] = 2;						// Cyclic Transmission
			CAN_Output_PaketListe[8].msg.buf[2] = 0;						// Upper Byte, Zeitintervall
			CAN_Output_PaketListe[8].msg.buf[3] = 0x64;						// Lower Byte, 100ms Zeitintervall

			// Nachricht senden
			CANwrite(&CAN_Output_PaketListe[8].msg, false);

			// Zaehler hochzaehlen
			count++;
			break;
		}
		// Antwort abwarten und vergleichen
		case 3:
		{
			if (incoming_CAN[0] == 0xA1)
			{
				if (incoming_CAN[1] == 2)
				{
					if (incoming_CAN[2] == 0)
					{
						if (incoming_CAN[3] == 0x64)
						{
							count++;
						}
						else
						{

						}
					}
					else
					{

					}
				}
				else
				{

				}
			}
			break;
		}
		// Daten speichern
		case 4:
		{
			// CAN Nachricht zum Speichern der Daten, einmal senden
			CAN_Output_PaketListe[8].msg.buf[0] = 0x32;						// Store Data

			// Nachricht senden
			CANwrite(&CAN_Output_PaketListe[8].msg, false);

			// Zaehler hochzaehlen
			count++;
			break;
		}
		// Antwort abwarten
		case 5:
		{
			if (incoming_CAN[0] == 0xB2)
			{
				count++;
			}
			break;
		}
		/// Starte Stromsensor
		case 6:
		{
			// CAN Nachricht fuer Start definieren, einmal senden
			CAN_Output_PaketListe[8].msg.buf[0] = 0x34;						// Set Mode
			CAN_Output_PaketListe[8].msg.buf[1] = 1;						// Runmode Start
			CAN_Output_PaketListe[8].msg.buf[2] = 1;						// Startup Mode Run

			// Nachricht senden
			CANwrite(&CAN_Output_PaketListe[8].msg, false);

			// Zaehler hochzaehlen
			count = 0;

			// Vollstaendig abgearbeitet
			return true;
			break;
		}

		default:
			break;
	}

	// Solange nicht vollstaendig abgearbeitet
	return false;
}
//----------------------------------------------------------------------

// Sortiere Konfiguration von Stromsensor
//----------------------------------------------------------------------
void ivtSort (uint8_t* data)
{
	// incoming CAN buffer zuruecksetzen
	for (uint8_t i = 0; i < 8; i++)
	{
		incoming_CAN[i] = 0;
	}

	// Daten auswaehlen
	switch (data[0])
	{
		// Antwort auf Speichern
		case 0xB2:
		{
			incoming_CAN[0] = data[0];
			break;
		}

		// Antwort auf Set Mode
		case 0xB4:
		{
			incoming_CAN[0] = data[0];
			incoming_CAN[1] = data[1];
			incoming_CAN[2] = data[2];
			break;
		}

		// Antwort auf Set Config Result
		case 0xA0:
		case 0xA1:
		case 0xA2:
		case 0xA3:
		case 0xA4:
		case 0xA5:
		case 0xA6:
		case 0xA7:
		{
			incoming_CAN[0] = data[0];
			incoming_CAN[1] = data[1];
			incoming_CAN[2] = data[2];
			incoming_CAN[3] = data[3];
			break;
		}

		default:
			break;
	}
}
//----------------------------------------------------------------------
