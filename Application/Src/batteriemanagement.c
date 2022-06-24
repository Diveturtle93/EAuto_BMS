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
uint16_t modulevoltage[LTC6811_DEVICES];
uint32_t stackvoltage;
uint16_t mincelltemperature[LTC6811_DEVICES + 1];
uint16_t maxcelltemperature[LTC6811_DEVICES + 1];
uint16_t LTC6811_Tempstatus = 0;
uint16_t LTC6811_Tempertures[LTC6811_DEVICES];
uint16_t LTC6811_undervolt[LTC6811_DEVICES];
uint16_t LTC6811_overvolt[LTC6811_DEVICES];
uint16_t LTC6811_analogvolt[LTC6811_DEVICES];
uint16_t LTC6811_digitalvolt[LTC6811_DEVICES];
uint16_t LTC6811_soc[LTC6811_DEVICES];
//----------------------------------------------------------------------

// Definiere Zellenarray
//----------------------------------------------------------------------
uint8_t CellVoltage[LTC6811_DEVICES][12];									// Array fuer gemessene Zellspannungen
uint8_t CellTemperature[LTC6811_DEVICES][12];								// Array fuer gemessene Zelltemperaturen
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
	ltc6811(ADCVAX | MD73 | CELLALL);										// Initial Command Zellen auslesen
}
//----------------------------------------------------------------------

// Lese Zellspannungen ein
//----------------------------------------------------------------------
void bms_cellspannungen(void)
{

}
//----------------------------------------------------------------------

// Lese Zelltemperaturen ein
//----------------------------------------------------------------------
void bms_celltemperaturen(void)
{

}
//----------------------------------------------------------------------

// Lese LTC Status ein
//----------------------------------------------------------------------
void bms_ltc_status(void)
{
	uint8_t data[8*2*LTC1380_DEVICES];

	ltc6811(ADSTAT | MD73 | STATALL);

	for (uint8_t i = 0; i <= LTC6811_DEVICES; i++)
	{
		LTC6811_soc[i] = ((data[1] << 8) | data[0]);
		LTC6811_Tempertures[i] = ((data[3] << 8) | data[2]);
		LTC6811_analogvolt[i] = ((data[5] << 8) | data[5]);
		LTC6811_digitalvolt[i] = ((data[7] << 8) | data[6]);

		for (uint8_t j = 0; j <= 3; j++)
		{
			for (uint8_t k = 0; k <= 4; k++)
			{
				LTC6811_undervolt[i] = (data[8 + j] >> (k * 2));
				LTC6811_overvolt[i] = (data[8 + j] >> (k * 2 + 1));
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
void bms_measure(void)
{

}

// Pruefe ob BMS OK ist
//----------------------------------------------------------------------
void bms_ok(void)
{

}
