//----------------------------------------------------------------------
// Titel	:	batteriemanagement.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jun 23, 2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
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
#include "batteriemanagement.h"
#include "BatteriemanagementSystem.h"
//----------------------------------------------------------------------

// Definiere
//----------------------------------------------------------------------
uint32_t stackvoltage = 0;													// Variable fuer Gesamtspannung
uint16_t LTC6811_undervolt[LTC6811_DEVICES] = {0};							// Array zum Speichern welche Zelle Unterspannung hat
uint16_t LTC6811_overvolt[LTC6811_DEVICES] = {0};							// Array zum Speichern welche Zelle Ueberspannung hat
uint16_t LTC6811_analogvolt[LTC6811_DEVICES] = {0};							// Array zum Speichern der Analogspannung pro Modul
uint16_t LTC6811_digitalvolt[LTC6811_DEVICES] = {0};						// Array zum Speichern der Digitalspannung pro Modul
uint16_t LTC6811_secref[LTC6811_DEVICES] = {0};								// Array zum Speichern der Sekundaerspannung pro Modul
uint16_t LTC6811_soc[LTC6811_DEVICES] = {0};								// Array zum Speichern der SOC pro Modul
uint8_t bms_tempcount = 0;													// Temperatursensor Zaehler
uint8_t bms_warning[LTC6811_DEVICES + 1] = {0};								// Array zum Speichern der Warnungen pro Modul
uint64_t bms_error[LTC6811_DEVICES + 1] = {0};								// Array zum Speichern der Fehler pro Modul
bool bms_readerror = false;													// Variable ob Fehler vorhanden beim auslesen
uint8_t bms_readerror_count = 0;											// Variable fuer Fehlerzaehler beim auslesen
//----------------------------------------------------------------------

// Definiere Zellenarray Spannungen
//----------------------------------------------------------------------
uint16_t cellvoltage[LTC6811_DEVICES][LTC6811_CELLS] = {0};					// Array fuer gemessene Zellspannungen
uint32_t modulvoltage[LTC6811_DEVICES] = {0};								// Array fuer gemessene Modulspannung
uint16_t mincellvoltage[LTC6811_DEVICES + 1] = {0};							// Array fuer Minimalspannungen
uint16_t maxcellvoltage[LTC6811_DEVICES + 1] = {0};							// Array fuer Maximalspannungen
//----------------------------------------------------------------------

// Definiere Zellenarray Temperaturen
//----------------------------------------------------------------------
uint16_t celltemperature[LTC6811_DEVICES][LTC1380_DEVICES * LTC1380_SENSORES] = {0};	// Array fuer gemessene Zelltemperaturen
uint16_t mincelltemperature[LTC6811_DEVICES + 1] = {0};						// Array fuer Minimaltemperaturen
uint16_t maxcelltemperature[LTC6811_DEVICES + 1] = {0};						// Array fuer Maximaltemperaturen
uint16_t LTC6811_ThermalShutdown = 0;										// LTC Thermal Shutdown
uint16_t LTC6811_Temperature[LTC6811_DEVICES] = {0};						// Array fuer LTC Devices Temperatur
uint16_t PCB_Temperature[LTC6811_DEVICES] = {0};							// Array fuer PCB Temperatur
//----------------------------------------------------------------------

// BMS initialisieren
//----------------------------------------------------------------------
bool bms_init (void)
{
	// Variablen definieren
	uint8_t error = 0, count = 0;

  	// IsoSPI einschalten, Isolierte Spannungsversorgung IsoSPI und HV-Precharge Messung einschalten
  	ISOSPI_ENABLE();

  	// Warten fuer eine kurze Zeit
  	HAL_Delay(20);

	// Alle Register zuruecksetzen
	ltc6811(CLRCELL);
	ltc6811(CLRSTAT);
	ltc6811(CLRAUX);
	ltc6811(CLRSCTRL);

	// Ausgabe auf Seriller Schnittstelle
	uartTransmit("\n", 1);

	#define TEST_LTC6811	"Starte Batteriemanagement-System\n"
	uartTransmit(TEST_LTC6811, sizeof(TEST_LTC6811));

	// LTC Check durchfuehren, bei Fehler wird der Check max. 10 mal wiederholt
	// Danach wird ein Fehler ausgegeben
	// TODO: Bei Fehler nicht in Endlosschleife gehen. Ggf. Slaves neustarten. Status muss auf CAN-Bus vorhanden sein
	do
	{
		if ((error = ltc6811_check()) != 0)									// LTC6811 Selftest durchfuehren
		{
			#define LTC6811_FAILED	"Selbsttest LTC6811 fehlerhaft\n"
			uartTransmit(LTC6811_FAILED, sizeof(LTC6811_FAILED));			// Ausgabe bei Fehlerhaftem Selbsttest

			uartTransmitNumber(error, 10);
			uartTransmit("\n", 1);
			count++;
		}
		else
		{
			#define LTC6811_PASSED	"Selbsttest LTC6811 erfolgreich\n"
			uartTransmit(LTC6811_PASSED, sizeof(LTC6811_PASSED));			// Ausgabe bei Erfolgreichem Selbsttest
			break;
		}

		// Wenn Fehler zum 10ten mal auftritt dann Fehler ausgeben
		if (count >= 10)
		{
#ifdef DEBUG
			software_error_debug(ERROR_LTC6811_INITIALTEST);
#else
			software_error(ERROR_LTC6811_INITIALTEST);
#endif
			return false;
		}
	}
	while ((error != 0) && (count <= 10));

	// LTC6811 initialisieren
	ltc6811_init();

	// Alle Register zuruecksetzen
	ltc6811(CLRCELL);
	ltc6811(CLRSTAT);
	ltc6811(CLRAUX);

	// Erster ADC Vorgang ist ungueltig
	ltc6811(ADCVC | MD73);													// Initial Command Zellen auslesen

	// Fuehre Zellmessungen durch
	bms_cellspannungen();
	// Alle Zellen und Spannungen auslesen und abspeichern
	for (uint8_t i = 0; i < 8; i++)
	{
		bms_celltemperatur(i);												// Zellen messen und Arrays initialisieren
	}

	// Fuhre Statusfunktion aus
	bms_ltc_status();

	return true;
}
//----------------------------------------------------------------------

// Lese alle Zellspannung ein
//----------------------------------------------------------------------
void bms_cellspannung (uint8_t cell)
{
	// Variablen definieren
	uint8_t data[32 * LTC6811_DEVICES];

	// Starte Zellmessung
	ltc6811(ADCVC | MD73 | cell);

	// Daten einlesen, Auswahl Zelle
	switch (cell)
	{
		// Zelle 1 - 3 und 7 - 9
		case 1:
		case 2:
		case 3:
			ltc6811_read(RDCVA, &data[0]);
			ltc6811_read(RDCVC, &data[16 * LTC6811_DEVICES]);
			break;
		// Zell 4 - 6 und  10 - 12
		case 4:
		case 5:
		case 6:
			ltc6811_read(RDCVB, &data[8 * LTC6811_DEVICES]);
			ltc6811_read(RDCVD, &data[24 * LTC6811_DEVICES]);
			break;
		default:
			break;
	}

	// TODO: sortiere Zellspannungen
	// Daten sortieren fuer alle Zellen
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		/*for (uint8_t j = 0; j < 12; j++)
		{
			switch (j)
			{
				case 0:
				case 1:
				case 2:
					cellvoltage[i][j] = ((data[i*8 + j*2 + 1] << 8) | data[i*8 + j*2]);
					break;
				case 3:
				case 4:
				case 5:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES+i)*8 + (j-3)*2 + 1] << 8) | data[(LTC6811_DEVICES+i)*8+ (j-3)*2]);
					break;
				case 6:
				case 7:
				case 8:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES*2+i)*8 + (j-6)*2 + 1] << 8) | data[(LTC6811_DEVICES*2+i)*8 + (j-6)*2]);
					break;
				case 9:
				case 10:
				case 11:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES*3+i)*8 + (j-9)*2 + 1] << 8) | data[(LTC6811_DEVICES*3+i)*8 + (j-9)*2]);
					break;
			}
		}*/

		// Daten sortieren fuer gewaehlte Zellen
		switch (cell)
		{
			case 1:
			case 2:
			case 3:
			{
				cellvoltage[i][cell-1] = ((data[i*8 + (cell-1)*2 + 1] << 8) | data[i*8 + (cell-1)*2]);
				cellvoltage[i][cell-1+6] = ((data[(LTC6811_DEVICES*2+i)*8 + ((cell-1)-6)*2 + 1] << 8) | data[(LTC6811_DEVICES*2+i)*8 + ((cell-1)-6)*2]);
				break;
			}
			case 4:
			case 5:
			case 6:
			{
				cellvoltage[i][cell-1] = ((data[(LTC6811_DEVICES+i)*8 + ((cell-1)-3)*2 + 1] << 8) | data[(LTC6811_DEVICES+i)*8 + ((cell-1)-3)*2]);
				cellvoltage[i][cell-1+6] = ((data[(LTC6811_DEVICES*3+i)*8 + ((cell-1)-9)*2 + 1] << 8) | data[(LTC6811_DEVICES*3+i)*8 + ((cell-1)-9)*2]);
				break;
			}
			default:
				return;
				break;
		}
	}
}
//----------------------------------------------------------------------

// Lese alle Zellspannungen ein
//----------------------------------------------------------------------
void bms_cellspannungen (void)
{
	// Variablen definieren
	uint8_t data[32 * LTC6811_DEVICES];

	// Starte Zellmessung
	ltc6811(ADCVC | MD73);

	// Daten einlesen
	ltc6811_read(RDCVA, &data[0]);
	ltc6811_read(RDCVB, &data[8 * LTC6811_DEVICES]);
	ltc6811_read(RDCVC, &data[16 * LTC6811_DEVICES]);
	ltc6811_read(RDCVD, &data[24 * LTC6811_DEVICES]);

	// Daten bearbeiten, pro Modul
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Daten fuer Zelle bearbeiten
		for (uint8_t j = 0; j < LTC6811_CELLS; j++)
		{
			switch (j)
			{
				// Zelle 1 - 3
				case 0:
				case 1:
				case 2:
					cellvoltage[i][j] = ((data[i*8 + j*2 + 1] << 8) | data[i*8 + j*2]);
					break;
				// Zelle 4 - 6
				case 3:
				case 4:
				case 5:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES+i)*8 + (j-3)*2 + 1] << 8) | data[(LTC6811_DEVICES+i)*8+ (j-3)*2]);
					break;
				// Zelle 7 - 9
				case 6:
				case 7:
				case 8:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES*2+i)*8 + (j-6)*2 + 1] << 8) | data[(LTC6811_DEVICES*2+i)*8 + (j-6)*2]);
					break;
				// Zelle 10 - 12
				case 9:
				case 10:
				case 11:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES*3+i)*8 + (j-9)*2 + 1] << 8) | data[(LTC6811_DEVICES*3+i)*8 + (j-9)*2]);
					break;
			}
		}
	}
}
//----------------------------------------------------------------------

// TODO: Lese Referenzspannung, GPIO3
// Lese Zelltemperatur ein
//----------------------------------------------------------------------
void bms_celltemperatur (uint8_t tempsensor)
{
	// Variablen definieren
	uint8_t data[8 * LTC6811_DEVICES];

	// Analogmultiplexer einstellen und Messung starten
	ltc1380_write(LTC1380_MUX0, tempsensor);								// Adresse und Kanal auf Multiplexer setzen
	ltc1380_write(LTC1380_MUX2, tempsensor);								// Adresse und Kanal auf Multiplexer setzen
	ltc6811(ADCVAX | MD73);													// Messung fuer GPIOs starten
	
	// Daten einlesen
	ltc6811_read(RDAUXA, &data[0]);

	// Daten bearbeiten, pro Modul
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Pro GPIO, Max 2
		for (uint8_t j = 0; j < LTC1380_DEVICES; j++)
		{
			// GPIO 1 und 2
			celltemperature[i][tempsensor + j*8] = ((data[i*8 + j*2 + 1] << 8) | data[i*8 + j*2]);	// LTC GPIO 1 und 2, Byte 0 bis 3 des Registers
		}

		// GPIO 3
		PCB_Temperature[i] = ((data[i*8 + 4 + 1] << 8) | data[i*8 + 4]);	// LTC GPIO 3, Byte 4 und 5 des Registers
	}
}
//----------------------------------------------------------------------

// Lese Analogspannung an den GPIOs ein
//----------------------------------------------------------------------
void bms_readgpio (uint8_t gpio)
{
	// Variablen definieren
	uint8_t data[16 * LTC6811_DEVICES];

	// Starte GPIO Messung
	ltc6811(ADAX | MD73 | gpio);

	// Daten einlesen
	ltc6811_read(RDAUXA, &data[0]);
	ltc6811_read(RDAUXB, &data[8 * LTC6811_DEVICES]);

	// Daten bearbeiten, pro Modul
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// GPIO waehlen
		switch (gpio)
		{
			// GPIO 1 und 2
			case 1:
			case 2:
				break;
			// GPIO 3
			case 3:
				PCB_Temperature[i] = ((data[i*8 + 4 + 1] << 8) | data[i*8 + 4]);// LTC GPIO 3, Byte 4 und 5 des Registers
				break;
			// GPIO 4 und 5
			case 4:
			case 5:
				break;
			// Sekundaerspannung
			case 6:
				LTC6811_secref[i] = ((data[i*8 + 8*LTC6811_DEVICES + 4 + 1] << 8) | data[i*8 + 8*LTC6811_DEVICES + 4]);	// LTC Sec Referenzspannung einlesen, Byte 6 und 7 des Registers
				break;
			default:
				break;
		}
	}
}
//----------------------------------------------------------------------

// Lese LTC Status ein
//----------------------------------------------------------------------
void bms_ltc_status (void)
{
	// Variablen definieren
	uint8_t data[16 * LTC6811_DEVICES];

	// Starte Status Messung
	ltc6811(ADSTAT | MD73);

	// Daten einlesen
	ltc6811_read(RDSTATA, &data[0]);
	ltc6811_read(RDSTATB, &data[8 * LTC6811_DEVICES]);

	// Daten bearbeiten, pro Modul
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Variablen zuruecksetzen
		LTC6811_undervolt[i] = 0;
		LTC6811_overvolt[i] = 0;

		// Statusdaten abspeichern
		LTC6811_soc[i] = ((data[i*8 + 1] << 8) | data[i*8]);
		LTC6811_Temperature[i] = ((data[i*8 + 3] << 8) | data[i*8 + 2]);
		LTC6811_analogvolt[i] = ((data[i*8 + 5] << 8) | data[i*8 + 4]);
		LTC6811_digitalvolt[i] = ((data[i*8 + 8*LTC6811_DEVICES + 1] << 8) | data[i*8 + 8*LTC6811_DEVICES]);

		// Unter- / Ueberspannungswerte sortieren
		for (uint8_t j = 0; j < 3; j++)
		{
			for (uint8_t k = 0; k <= 3; k++)
			{
				LTC6811_undervolt[i] |= (((data[i*8 + 8*LTC6811_DEVICES + 2+j] >> (k*2)) & 1) << (j*4 + k));
				LTC6811_overvolt[i] |= (((data[i*8 + 8*LTC6811_DEVICES + 2+j] >> (k*2 + 1)) & 1) << (j*4 + k));
			}
		}

		// Statusbit Thermalshutdown verarbeiten
		if (data[i*8 + 8*LTC6811_DEVICES + 5] & 0x01)
		{
			LTC6811_ThermalShutdown |= (1 << i);
		}
		else
		{
			LTC6811_ThermalShutdown &= ~(1 << i);
		}
	}
}
//----------------------------------------------------------------------

// Messe alle Zellspannungen und zwei Temperaturen
//----------------------------------------------------------------------
void bms_volt_temp (uint8_t tempsensor)
{
	// Variablen definieren
	uint8_t data[40 * LTC6811_DEVICES];

	// Analogmultiplexer einstellen und Messung starten
	ltc1380_write(LTC1380_MUX0, tempsensor);								// Adresse und Kanal auf Multiplexer setzen
	ltc1380_write(LTC1380_MUX2, tempsensor);								// Adresse und Kanal auf Multiplexer setzen
	ltc6811(ADAX | MD73);													// Messung fuer GPIOs starten

	// Daten einlesen
	ltc6811_read(RDCVA, &data[0]);
	ltc6811_read(RDCVB, &data[8 * LTC6811_DEVICES]);
	ltc6811_read(RDCVC, &data[16 * LTC6811_DEVICES]);
	ltc6811_read(RDCVD, &data[24 * LTC6811_DEVICES]);
	ltc6811_read(RDAUXA, &data[32 * LTC6811_DEVICES]);

	// Daten bearbeiten, pro Modul
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Daten fuer Zellen bearbeiten
		for (uint8_t j = 0; j < LTC6811_CELLS; j++)
		{
			switch (j)
			{
				// Zelle 1 - 3
				case 0:
				case 1:
				case 2:
					cellvoltage[i][j] = ((data[i*8 + j*2 + 1] << 8) | data[i*8 + j*2]);
					break;
				// Zelle 4 - 6
				case 3:
				case 4:
				case 5:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES+i)*8 + (j-3)*2 + 1] << 8) | data[(LTC6811_DEVICES+i)*8+ (j-3)*2]);
					break;
				// Zelle 7 - 9
				case 6:
				case 7:
				case 8:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES*2+i)*8 + (j-6)*2 + 1] << 8) | data[(LTC6811_DEVICES*2+i)*8 + (j-6)*2]);
					break;
				// Zelle 10 - 12
				case 9:
				case 10:
				case 11:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES*3+i)*8 + (j-9)*2 + 1] << 8) | data[(LTC6811_DEVICES*3+i)*8 + (j-9)*2]);
					break;
				default:
					break;
			}
		}

		// Daten fuer Temperaturen bearbeiten, max 2
		for (uint8_t j = 0; j < LTC1380_DEVICES; j++)
		{
			celltemperature[i][tempsensor + j*8] = ((data[(LTC6811_DEVICES*4+i)*8 + j*2 + 1] << 8) | data[(LTC6811_DEVICES*4+i)*8 + j*2]);
		}
	}
}
//----------------------------------------------------------------------

// Messe alle Zellspannungen und zwei Temperaturen
//----------------------------------------------------------------------
void bms_volt_SOC (void)
{
	// Variablen definieren
	uint8_t data[40 * LTC6811_DEVICES];

	// Starte Zellmessung und SOC
	ltc6811(ADCVSC | MD73);

	// Daten einlesen
	ltc6811_read(RDCVA, &data[0]);
	ltc6811_read(RDCVB, &data[8 * LTC6811_DEVICES]);
	ltc6811_read(RDCVC, &data[16 * LTC6811_DEVICES]);
	ltc6811_read(RDCVD, &data[24 * LTC6811_DEVICES]);
	ltc6811_read(RDSTATA, &data[32 * LTC6811_DEVICES]);

	// Daten bearbeiten, pro Modul
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Daten fuer Zellen bearbeiten
		for (uint8_t j = 0; j < LTC6811_CELLS; j++)
		{
			switch (j)
			{
				// Zelle 1 - 3
				case 0:
				case 1:
				case 2:
					cellvoltage[i][j] = ((data[i*8 + j*2 + 1] << 8) | data[i*8 + j*2]);
					break;
				// Zelle 4 - 6
				case 3:
				case 4:
				case 5:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES+i)*8 + (j-3)*2 + 1] << 8) | data[(LTC6811_DEVICES+i)*8+ (j-3)*2]);
					break;
				// Zelle 7 - 9
				case 6:
				case 7:
				case 8:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES*2+i)*8 + (j-6)*2 + 1] << 8) | data[(LTC6811_DEVICES*2+i)*8 + (j-6)*2]);
					break;
				// Zelle 10 - 12
				case 9:
				case 10:
				case 11:
					cellvoltage[i][j] = ((data[(LTC6811_DEVICES*3+i)*8 + (j-9)*2 + 1] << 8) | data[(LTC6811_DEVICES*3+i)*8 + (j-9)*2]);
					break;
				default:
					break;
			}
		}

		// Daten fuer SOC bearbeiten
		LTC6811_soc[i] = ((data[(LTC6811_DEVICES*4+i)*8 + 1] << 8) | data[(LTC6811_DEVICES*4+i)*8]);
	}
}
//----------------------------------------------------------------------

// Fuehre BMS Operation durch
//----------------------------------------------------------------------
void bms_work (void)
{
	// Wenn BMS maximalen Temperatursensor erreicht hat, einmal aufrufen
	if (bms_tempcount == LTC1380_SENSORES)
	{
		bms_tempcount = 0;													// Temperatur Zaehler zuruecksetzen
		bms_celltemperatur(bms_tempcount);									// Temperatur einlesen
		bms_readgpio(SECREF);												// Sekundaerspannung einlesen
		bms_ltc_status();													// LTC Status abfragen

#ifdef DEBUG_BMS_WORK
		uartTransmitNumber(bms_ok(), 10);
		uartTransmit(", ", 2);
#endif

	}
	// Solange wie BMS maximalen Temperatursensor nicht erreicht hat, aufrufen
	else
	{
		bms_volt_temp(bms_tempcount);										// Spannung und Temperatur einlesen
		bms_tempcount++;													// Temperatur Zaehler hochzaehlen
	}

	// Min- und Maxwerte ermitteln
	bms_Vminmax();															// Min- / Maxspannung pro Modul und Gesammt
	bms_Tminmax();															// Min- / Maxtemperatur pro Modul und Gesamt
	bms_MSvoltage();														// Modul- / Stackspannung

	// Zellwerte in CAN-Nachrichten abspeichern
	// xxx: Aufruf hier? Oder wo anders?
	// Spannungen
	for (uint8_t i = 0; i < 3; i++)
	{
		CAN_Output_PaketListe[7+i].msg.buf[0] = cellvoltage[0][0+i*4];
		CAN_Output_PaketListe[7+i].msg.buf[1] = (cellvoltage[0][0+i*4]>>8);
		CAN_Output_PaketListe[7+i].msg.buf[2] = cellvoltage[0][1+i*4];
		CAN_Output_PaketListe[7+i].msg.buf[3] = (cellvoltage[0][1+i*4]>>8);
		CAN_Output_PaketListe[7+i].msg.buf[4] = cellvoltage[0][2+i*4];
		CAN_Output_PaketListe[7+i].msg.buf[5] = (cellvoltage[0][2+i*4]>>8);
		CAN_Output_PaketListe[7+i].msg.buf[6] = cellvoltage[0][3+i*4];
		CAN_Output_PaketListe[7+i].msg.buf[7] = (cellvoltage[0][3+i*4]>>8);
	}

	// Temperaturen
	for (uint8_t i = 0; i < 4; i++)
	{
		CAN_Output_PaketListe[31+i].msg.buf[0] = celltemperature[0][0+i*4];
		CAN_Output_PaketListe[31+i].msg.buf[1] = (celltemperature[0][0+i*4]>>8);
		CAN_Output_PaketListe[31+i].msg.buf[2] = celltemperature[0][1+i*4];
		CAN_Output_PaketListe[31+i].msg.buf[3] = (celltemperature[0][1+i*4]>>8);
		CAN_Output_PaketListe[31+i].msg.buf[4] = celltemperature[0][2+i*4];
		CAN_Output_PaketListe[31+i].msg.buf[5] = (celltemperature[0][2+i*4]>>8);
		CAN_Output_PaketListe[31+i].msg.buf[6] = celltemperature[0][3+i*4];
		CAN_Output_PaketListe[31+i].msg.buf[7] = (celltemperature[0][3+i*4]>>8);
	}

	// Stackvoltage
	CAN_Output_PaketListe[63].msg.buf[0] = stackvoltage;
	CAN_Output_PaketListe[63].msg.buf[1] = (stackvoltage >> 8);
	CAN_Output_PaketListe[63].msg.buf[2] = (stackvoltage >> 16);
	CAN_Output_PaketListe[63].msg.buf[3] = (stackvoltage >> 24);

#ifdef DEBUG_BMS_WORK
	if (bms_tempcount == 0)
	{
		for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
		{
			for (uint8_t j = 0; j < LTC6811_CELLS; j++)
			{
				uartTransmitNumber(cellvoltage[i][j], 10);
				uartTransmit(", ", 2);
			}

			for (uint8_t j = 0; j < (LTC1380_DEVICES * LTC1380_SENSORES); j++)
			{
				uartTransmitNumber(celltemperature[i][j], 10);
				uartTransmit(", ", 2);
			}

			uartTransmitNumber(PCB_Temperature[i], 10);
			uartTransmit(", ", 2);
			uartTransmitNumber(LTC6811_Temperature[i], 10);
			uartTransmit(", ", 2);
			uartTransmitNumber(LTC6811_analogvolt[i], 10);
			uartTransmit(", ", 2);
			uartTransmitNumber(LTC6811_digitalvolt[i], 10);
			uartTransmit(", ", 2);
			uartTransmitNumber(LTC6811_secref[i], 10);
			uartTransmit(", ", 2);
			uartTransmitNumber(LTC6811_soc[i], 10);
			uartTransmit("\n", 1);
		}

		// Wenn mehrere Module angeschlossen sind, zusaetzlichen Zeilenumbruch ausgeben
		if (LTC6811_DEVICES > 1)
		{
			uartTransmit("\n", 1);
		}
	}
#endif
}
//----------------------------------------------------------------------

// Pruefe ob BMS OK ist
//----------------------------------------------------------------------
bool bms_ok (void)
{
	// TODO: BMS OK abfrage erstellen
	/*for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// BMS Error zuruecksetzen
		bms_error[i] = 0;
		// BMS Warnung zuruecksetzen
		bms_warning[i] = 0;
	}*/

	// Unterspannung
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		if (LTC6811_undervolt[i] > 0)
		{
			bms_error[i] |= LTC6811_undervolt[i];							// Offset 0, Bits in Fehlerspeicher schreiben
		}
		else
		{
			bms_error[i] &= 0x07FFFFFFFFFFF000;								// Bit 0 - 11 maskieren wenn kein Unterspannungsfehler
		}
	}

	// Ueberspannung
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		if (LTC6811_overvolt[i] > 0)
		{
			bms_error[i] |= (LTC6811_overvolt[i] << 12);					// Offset 12, Bits in Fehlerspeicher schreiben
		}
		else
		{
			bms_error[i] &= 0x07FFFFFFFF000FFF;								// Bit 12 - 23 maskieren wenn kein Ueberspannungsfehler
		}
	}

	// Untertemperatur
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		for (uint8_t j = 0; j < (LTC1380_DEVICES * LTC1380_SENSORES); j++)
		{
			if ((celltemperature[i][j] >= LTC6811_UTEMP) && (celltemperature[i][j] < 53000))
			{
				bms_error[i] |= (1 << (24+j));								// Offset 24, Bits in Fehlerspeicher schreiben
			}
			else
			{
				bms_error[i] &= ~(1 << (24+j));								// Bit 24 - 39 maskieren wenn kein Untertemperaturfehler
			}
		}
	}

	// Uebertemperatur
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		for (uint8_t j = 0; j < (LTC1380_DEVICES * LTC1380_SENSORES); j++)
		{
			if (celltemperature[i][j] < LTC6811_OTEMP)
			{
				bms_error[i] |= (1 << (40+j));								// Offset 40, Bits in Fehlerspeicher schreiben
			}
			else
			{
				bms_error[i] &= ~(1 << (40+j));								// Bit 40 - 55 maskieren wenn kein Ubeertemperaturfehler
			}
		}
	}

	// LTC Chip Temperatur
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		if ((LTC6811_Temperature[i] >= LTC6811_DEVUTEMP) && (LTC6811_Temperature[i] < LTC6811_DEVOTEMP))
		{
			// 1ULL fuer Konvertierung von 8bit in 64Bit
			bms_error[i] &= ~(1ULL << BMS_LTC_Temperatur);					// LTC Temperaturfehler zuruecksetzen
		}
		else
		{
			// 1ULL fuer Konvertierung von 8bit in 64Bit
			bms_error[i] |= (1ULL << BMS_LTC_Temperatur);					// LTC Temperaturfehler setzen
		}
	}

	// LTC PCB Temperatur
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		if ((PCB_Temperature[i] <= LTC6811_PCB_UTEMP) && (PCB_Temperature[i] > LTC6811_PCB_OTEMP))
		{
			// 1ULL fuer Konvertierung von 8bit in 64Bit
			bms_error[i] &= ~(1ULL << BMS_SlavePCBError);					// LTC PCB Temperaturfehler zuruecksetzen
		}
		else
		{
			// 1ULL fuer Konvertierung von 8bit in 64Bit
			bms_error[i] |= (1ULL << BMS_SlavePCBError);					// LTC PCB Temperaturfehler setzen
		}
	}

	// Plausibilitaetsfehler
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		if ((LTC6811_undervolt[i] && LTC6811_overvolt[i]) > 0)
		{
			// 1ULL fuer Konvertierung von 8bit in 64Bit
			bms_error[i] |= (1ULL << BMS_PlausibilityError);				// LTC Plausibilitaetsfehler setzen
		}
		else
		{
			// 1ULL fuer Konvertierung von 8bit in 64Bit
			bms_error[i] &= ~(1ULL << BMS_PlausibilityError);				// LTC Plausibilitaetsfehler zuruecksetzen
		}
	}

	// Second Referenzspannung am LTC pruefen
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Spannung ausserhalb der Grenzen
		if ((LTC6811_secref[i] >= SEC_UVOLT) && (LTC6811_secref[i] < SEC_OVOLT))
		{
			bms_warning[i] &= ~(1 << 0);
		}
		else
		{
			bms_warning[i] |= (1 << 0);
		}
	}

	// Analogspannung am LTC pruefen
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Spannung ausserhalb der Grenzen
		if ((LTC6811_analogvolt[i] >= ANALOG_UVOLT) && (LTC6811_analogvolt[i] < ANALOG_OVOLT))
		{
			bms_warning[i] &= ~(1 << 1);
		}
		else
		{
			bms_warning[i] |= (1 << 1);
		}
	}

	// Digitalspannung am LTC pruefen
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Spannung ausserhalb der Grenzen
		if ((LTC6811_digitalvolt[i] >= DIGITAL_UVOLT) && (LTC6811_digitalvolt[i] < DIGITAL_OVOLT))
		{
			bms_warning[i] &= ~(1 << 2);
		}
		else
		{
			bms_warning[i] |= (1 << 2);
		}
	}

	// Modulfehler und -warnung auswerten und speichern
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Fehler in Modul
		if (bms_error[i] != 0)
		{
			bms_error[LTC6811_DEVICES] |= (1 << i);
		}
		else
		{
			bms_error[LTC6811_DEVICES] &= ~(1 << i);
		}

		// Warnung in Modul
		if (bms_warning[i] != 0)
		{
			bms_warning[LTC6811_DEVICES] |= (1 << i);
		}
		else
		{
			bms_warning[LTC6811_DEVICES] &= ~(1 << i);
		}
	}

#ifdef DEBUG_BMS_OK
	uartTransmitNumber(bms_error[0], 10);
	uartTransmit(", ", 2);
	uartTransmitNumber(bms_warning[0], 10);
	uartTransmit("\n", 1);
#endif

	// Auswertung ob in BMS ein Fehler oder Warnung vorhanden, Rueckgabe False / True
	if (bms_error[LTC6811_DEVICES] != 0)
	{
		return BMSError;													// Wenn Fehler vorhanden
	}
	else if (bms_warning[LTC6811_DEVICES] != 0)
	{
		return BMSWarning;													// Wenn Warnung vorhanden
	}
	else
	{
		return BMSNoError;													// Wenn kein Fehler vorhanden
	}
}
//----------------------------------------------------------------------

// Minimal- / Maximalspannung ermitteln
//----------------------------------------------------------------------
void bms_Vminmax (void)
{
	// Min- / Maxspannung aller Zellen
	mincellvoltage[LTC6811_DEVICES] = 65535;
	maxcellvoltage[LTC6811_DEVICES] = 0;

	// Min- / Maxspannung pro Modul
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Zelle: Min- / Maxwerte auf default setzen
		mincellvoltage[i] = 65535;
		maxcellvoltage[i] = 0;

		// Daten bearbeiten, pro Zelle
		for (uint8_t j = 0; j < LTC6811_CELLS; j++)
		{
			if (cellvoltage[i][j] < mincellvoltage[i])
			{
				mincellvoltage[i] = cellvoltage[i][j];
			}

			if (cellvoltage[i][j] > maxcellvoltage[i])
			{
				maxcellvoltage[i] = cellvoltage[i][j];
			}
		}

		if (mincellvoltage[i] < mincellvoltage[LTC6811_DEVICES])
		{
			mincellvoltage[LTC6811_DEVICES] = mincellvoltage[i];
		}

		if (maxcellvoltage[i] > maxcellvoltage[LTC6811_DEVICES])
		{
			maxcellvoltage[LTC6811_DEVICES] = maxcellvoltage[i];
		}
	}
}
//----------------------------------------------------------------------

// Minimal- / Maximaltemperatur ermitteln
//----------------------------------------------------------------------
void bms_Tminmax (void)
{
	// Min- / Maxtemperatur aller Zellen
	mincelltemperature[LTC6811_DEVICES] = 65535;
	maxcelltemperature[LTC6811_DEVICES] = 0;

	// Min- / Maxtemperatur pro Modul
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Zelle: Min- / Maxwerte auf default setzen
		mincelltemperature[i] = 65535;
		maxcelltemperature[i] = 0;

		// Daten bearbeiten, pro Temperatursensor
		for (uint8_t j = 0; j < (LTC1380_DEVICES * LTC1380_SENSORES); j++)
		{
			if (celltemperature[i][j] < mincelltemperature[i])
			{
				mincelltemperature[i] = celltemperature[i][j];
			}

			if (celltemperature[i][j] > maxcelltemperature[i])
			{
				maxcelltemperature[i] = celltemperature[i][j];
			}
		}

		if (mincelltemperature[i] < mincelltemperature[LTC6811_DEVICES])
		{
			mincelltemperature[LTC6811_DEVICES] = mincelltemperature[i];
		}

		if (maxcelltemperature[i] > maxcelltemperature[LTC6811_DEVICES])
		{
			maxcelltemperature[LTC6811_DEVICES] = maxcelltemperature[i];
		}
	}
}
//----------------------------------------------------------------------

// Modul- / Stackspannung ermitteln
//----------------------------------------------------------------------
void bms_MSvoltage (void)
{
	// Gesamtspannung zuruecksetzen
	stackvoltage = 0;

	// Modulspannungen ermitteln
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Modulspannung zuruecksetzen
		modulvoltage[i] = 0;

		// Daten bearbeiten
		for (uint8_t j = 0; j < LTC6811_CELLS; j++)
		{
			modulvoltage[i] += cellvoltage[i][j];
		}

		// Gesamtspannung bearbeiten
		stackvoltage += modulvoltage[i];
	}
}
//----------------------------------------------------------------------
