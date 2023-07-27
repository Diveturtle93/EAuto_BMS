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
#include "BasicUart.h"
#include "error.h"
#include "batteriemanagement.h"
#include "LTC6811.h"
#include "LTC1380.h"
#include "outputs.h"
//----------------------------------------------------------------------

// Definiere Global Variablen
//----------------------------------------------------------------------
uint16_t mincellvoltage[LTC6811_DEVICES + 1];
uint16_t maxcellvoltage[LTC6811_DEVICES + 1];
uint32_t modulevoltage[LTC6811_DEVICES];
uint32_t stackvoltage;
uint16_t mincelltemperature[LTC6811_DEVICES + 1];
uint16_t maxcelltemperature[LTC6811_DEVICES + 1];
uint16_t LTC6811_Tempstatus = 0;
uint16_t LTC6811_Temperatures[LTC6811_DEVICES];
uint16_t LTC6811_undervolt[LTC6811_DEVICES] = {0};
uint16_t LTC6811_overvolt[LTC6811_DEVICES] = {0};
uint16_t LTC6811_analogvolt[LTC6811_DEVICES];
uint16_t LTC6811_digitalvolt[LTC6811_DEVICES];
uint16_t LTC6811_soc[LTC6811_DEVICES];
uint8_t bms_tempcount = 0;
//----------------------------------------------------------------------

// Definiere Zellenarray
//----------------------------------------------------------------------
uint16_t cellvoltage[LTC6811_DEVICES][12];										// Array fuer gemessene Zellspannungen
uint16_t celltemperature[LTC6811_DEVICES][LTC1380_DEVICES * LTC1380_SENSORES];	// Array fuer gemessene Zelltemperaturen
//----------------------------------------------------------------------

// BMS initialisieren
//----------------------------------------------------------------------
void bms_init(void)
{
	uint8_t error, count = 0;

  	// IsoSPI einschalten, Isolierte Spannungsversorgung IsoSPI und HV-Precharge Messung einschalten
  	ISOSPI_ENABLE();

  	// Warten fuer eine kurze Zeit
  	HAL_Delay(20);

	uartTransmit("\n", 1);

	#define TEST_LTC6811	"Starte Batteriemanagement-System\n"
	uartTransmit(TEST_LTC6811, sizeof(TEST_LTC6811));

	do
	{
		if ((error = ltc6811_check()) != 0)										// LTC6804 Selftest durchfuehren
		{
			#define LTC6811_FAILED	"Selbsttest LTC6811 fehlerhaft\n"
			uartTransmit(LTC6811_FAILED, sizeof(LTC6811_FAILED));				// Ausgabe bei Fehlerhaftem Selbsttest
			leuchten_out.RedLed = 1;											// Variable setzen
			HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);// Ausgabe auf LEDs

			uartTransmitNumber(error, 10);
			uartTransmit("\n", 1);
		}
		else
		{
			#define LTC6811_PASSED	"Selbsttest LTC6811 erfolgreich\n"
			uartTransmit(LTC6811_PASSED, sizeof(LTC6811_PASSED));				// Ausgabe bei Erfolgreichem Selbsttest
		}

		if (count >= 10)
		{
			software_error(ERROR_LTC6811_INITIALTEST);
		}
	}
	while (error != 0);

	// LTC6811 initialisieren
	ltc6811_init();

	// Alle Register zuruecksetzen
	ltc6811(CLRCELL);
	ltc6811(CLRSTAT);
	ltc6811(CLRAUX);

	// Erster ADC Vorgang ist ungueltig
	ltc6811(ADCVC | MD73 | CELLALL);										// Initial Command Zellen auslesen

	// Alle Zellen und Spannungen auslesen und abspeichern
	for (uint8_t i = 0; i < 8; i++)
	{
		bms_measure(i);														// Zellen messen und Arrays initialisieren
	}
}
//----------------------------------------------------------------------

// Lese Zellspannungen ein
//----------------------------------------------------------------------
void bms_cellspannungen(uint16_t command)
{

}
//----------------------------------------------------------------------

// Lese Zelltemperaturen ein
//----------------------------------------------------------------------
void bms_celltemperaturen(uint16_t command)
{

}
//----------------------------------------------------------------------

// Lese LTC Status ein
//----------------------------------------------------------------------
void bms_ltc_status(void)
{
	uint8_t data[16 * LTC1380_DEVICES];

	ltc6811(ADSTAT | MD73);
	ltc6811_read(RDSTATA, &data[0]);
	ltc6811_read(RDSTATB, &data[8 * LTC6811_DEVICES]);


	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		LTC6811_undervolt[i] = 0;
		LTC6811_overvolt[i] = 0;

		LTC6811_soc[i] = ((data[i*16 + 1] << 8) | data[i*16]);
		LTC6811_Temperatures[i] = ((data[i*16 + 3] << 8) | data[i*16 + 2]);
		LTC6811_analogvolt[i] = ((data[i*16 + 5] << 8) | data[i*16 + 5]);
		LTC6811_digitalvolt[i] = ((data[i*16 + 9] << 8) | data[i*16 + 8]);

		for (uint8_t j = 0; j < 3; j++)
		{
			for (uint8_t k = 0; k <= 3; k++)
			{
				LTC6811_undervolt[i] |= (((data[i*16 + 10+j] >> (k*2)) & 1) << (j*4 + k));
				LTC6811_overvolt[i] |= (((data[i*16 + 10+j] >> (k*2 + 1)) & 1) << (j*4 + k));
			}
		}

		if (data[11] & 0x01)
		{
			LTC6811_Tempstatus |= (1 << i);
		}
		else
		{
			LTC6811_Tempstatus &= ~(1 << i);
		}
	}
}
//----------------------------------------------------------------------

// Messe alle Zellspannungen und zwei Temperaturen
//----------------------------------------------------------------------
void bms_measure(uint8_t tempsensor)
{
	uint8_t data[40 * LTC6811_DEVICES];

	ltc1380_write(LTC1380_MUX0, tempsensor);
	ltc1380_write(LTC1380_MUX2, tempsensor);
	ltc6811(ADCVAX | MD73);

	ltc6811_read(RDCVA, &data[0]);
	ltc6811_read(RDCVB, &data[8 * LTC6811_DEVICES]);
	ltc6811_read(RDCVC, &data[16 * LTC6811_DEVICES]);
	ltc6811_read(RDCVD, &data[24 * LTC6811_DEVICES]);
	ltc6811_read(RDAUXA, &data[32 * LTC6811_DEVICES]);

	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		for (uint8_t j = 0; j < 12; j++)
		{
			switch (j)
			{
				case 0:
				case 1:
				case 2:
					cellvoltage[i][j] = ((data[i*12 + j*2 + 1] << 8) | data[i*12 + j*2]);
					break;
				case 3:
				case 4:
				case 5:
					cellvoltage[i][j] = ((data[i*12 + j*2 + 3] << 8) | data[i*12 + j*2 + 2]);
					break;
				case 6:
				case 7:
				case 8:
					cellvoltage[i][j] = ((data[i*12 + j*2 + 5] << 8) | data[i*12 + j*2 + 4]);
					break;
				case 9:
				case 10:
				case 11:
					cellvoltage[i][j] = ((data[i*12 + j*2 + 7] << 8) | data[i*12 + j*2 + 6]);
					break;
			}
		}

		for (uint8_t j = 0; j < 2; j++)
		{
			celltemperature[i][2*tempsensor + j] = ((data[i*12 + 32 + j*2 + 1] << 8) | data[i*12 + 32 + j*2]);
		}
	}
}
// Pruefe ob BMS OK ist
//----------------------------------------------------------------------
void bms_ok(void)
{
	bms_measure(bms_tempcount);
	bms_Vminmax();
	bms_Tminmax();
	bms_MSvoltage();
//	bms_ltc_status();

	bms_tempcount++;

	if (bms_tempcount == 8)
	{
		bms_tempcount = 0;
	}
}

// Minimal- / Maximalspannung ermitteln
//----------------------------------------------------------------------
void bms_Vminmax(void)
{
	mincellvoltage[LTC6811_DEVICES] = 65535;
	maxcellvoltage[LTC6811_DEVICES] = 0;

	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		mincellvoltage[i] = 65535;
		maxcellvoltage[i] = 0;

		for (uint8_t j = 0; j < 12; j++)
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
void bms_Tminmax(void)
{
	mincelltemperature[LTC6811_DEVICES] = 65535;
	maxcelltemperature[LTC6811_DEVICES] = 0;

	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		mincelltemperature[i] = 65535;
		maxcelltemperature[i] = 0;

		for (uint8_t j = 0; j < 12; j++)
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
void bms_MSvoltage(void)
{
	stackvoltage = 0;

	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		modulevoltage[i] = 0;

		for (uint8_t j = 0; j < 12; j++)
		{
			modulevoltage[i] += cellvoltage[i][j];
		}

		stackvoltage += modulevoltage[i];
	}
}
//----------------------------------------------------------------------
