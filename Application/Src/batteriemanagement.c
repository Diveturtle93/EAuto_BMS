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

// Definiere Global Variablen
//----------------------------------------------------------------------
uint16_t mincellvoltage[LTC6811_DEVICES + 1] = {0};
uint16_t maxcellvoltage[LTC6811_DEVICES + 1] = {0};
uint32_t modulevoltage[LTC6811_DEVICES] = {0};
uint32_t stackvoltage = 0;
uint16_t mincelltemperature[LTC6811_DEVICES + 1] = {0};
uint16_t maxcelltemperature[LTC6811_DEVICES + 1] = {0};
uint16_t LTC6811_Tempstatus = 0;
uint16_t LTC6811_Temperature[LTC6811_DEVICES] = {0};
uint16_t PCB_Temperature[LTC6811_DEVICES] = {0};
uint16_t LTC6811_undervolt[LTC6811_DEVICES] = {0};
uint16_t LTC6811_overvolt[LTC6811_DEVICES] = {0};
uint16_t LTC6811_analogvolt[LTC6811_DEVICES] = {0};
uint16_t LTC6811_digitalvolt[LTC6811_DEVICES] = {0};
uint16_t LTC6811_soc[LTC6811_DEVICES] = {0};
uint8_t bms_tempcount = 0;
uint16_t Sec_Ref[LTC6811_DEVICES] = {0};
//----------------------------------------------------------------------

// Definiere Zellenarray
//----------------------------------------------------------------------
uint16_t cellvoltage[LTC6811_DEVICES][12] = {0};								// Array fuer gemessene Zellspannungen
uint16_t celltemperature[LTC6811_DEVICES][LTC1380_DEVICES * LTC1380_SENSORES] = {0};	// Array fuer gemessene Zelltemperaturen
uint16_t modulvoltage[LTC6811_DEVICES] = {0};									// Array fuer gemessene Modulspannung
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

			uartTransmitNumber(error, 10);
			uartTransmit("\n", 1);
			count++;
		}
		else
		{
			#define LTC6811_PASSED	"Selbsttest LTC6811 erfolgreich\n"
			uartTransmit(LTC6811_PASSED, sizeof(LTC6811_PASSED));				// Ausgabe bei Erfolgreichem Selbsttest
		}

		// TODO: Count wird nicht hochgezaehlt
		if (count >= 10)
		{
#ifdef DEBUG
			software_error_debug(ERROR_LTC6811_INITIALTEST);
			return;
#else
			software_error(ERROR_LTC6811_INITIALTEST);
#endif
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
	ltc6811(ADCVC | MD73 | CELLALL);											// Initial Command Zellen auslesen

	// Alle Zellen und Spannungen auslesen und abspeichern
	for (uint8_t i = 0; i < 8; i++)
	{
		bms_celltemperatur(i);													// Zellen messen und Arrays initialisieren
	}
}
//----------------------------------------------------------------------

// Lese alle Zellspannung ein
//----------------------------------------------------------------------
void bms_cellspannung(uint8_t cell)
{
	uint8_t data[32 * LTC6811_DEVICES];

	ltc6811(ADCVC | MD73 | cell);

	switch (cell)
	{
		case 1:
		case 2:
		case 3:
			ltc6811_read(RDCVA, &data[0]);
			ltc6811_read(RDCVC, &data[16 * LTC6811_DEVICES]);
			break;
		case 4:
		case 5:
		case 6:
			ltc6811_read(RDCVB, &data[8 * LTC6811_DEVICES]);
			ltc6811_read(RDCVD, &data[24 * LTC6811_DEVICES]);
			break;
		default:
			ltc6811_read(RDCVA, &data[0]);
			ltc6811_read(RDCVB, &data[8 * LTC6811_DEVICES]);
			ltc6811_read(RDCVC, &data[16 * LTC6811_DEVICES]);
			ltc6811_read(RDCVD, &data[24 * LTC6811_DEVICES]);
			break;
	}

	// TODO: sortiere Zellspannungen
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		for (uint8_t j = 0; j < 12; j++)
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
		}
	}
}
//----------------------------------------------------------------------

// Lese alle Zellspannungen ein
//----------------------------------------------------------------------
void bms_cellspannungen(void)
{
	uint8_t data[32 * LTC6811_DEVICES];

	ltc6811(ADCVC | MD73);

	ltc6811_read(RDCVA, &data[0]);
	ltc6811_read(RDCVB, &data[8 * LTC6811_DEVICES]);
	ltc6811_read(RDCVC, &data[16 * LTC6811_DEVICES]);
	ltc6811_read(RDCVD, &data[24 * LTC6811_DEVICES]);

	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		for (uint8_t j = 0; j < 12; j++)
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
		}
	}
}
//----------------------------------------------------------------------

// TODO: Lese Referenzspannung, GPIO3
// Lese Zelltemperatur ein
//----------------------------------------------------------------------
void bms_celltemperatur(uint8_t tempsensor)
{
	uint8_t data[8 * LTC6811_DEVICES];

	ltc1380_write(LTC1380_MUX0, tempsensor);
	ltc1380_write(LTC1380_MUX2, tempsensor);
	ltc6811(ADAX | MD73);
	
	ltc6811_read(RDAUXA, &data[0 * LTC6811_DEVICES]);

	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		for (uint8_t j = 0; j < 2; j++)
		{
			celltemperature[i][2*tempsensor + j] = ((data[i*8 + j*2 + 1] << 8) | data[i*8 + j*2]);	// LTC GPIO 0 und 1, Byte 0 bis 3 des Registers
		}

		PCB_Temperature[i] = ((data[i*8 + 4 + 1] << 8) | data[i*8 + 4]);		// LTC GPIO 2, Byte 4 und 5 des Registers
	}
}
//----------------------------------------------------------------------

// Lese Analogspannung an den GPIOs ein
//----------------------------------------------------------------------
void bms_readgpio(uint8_t gpio)
{
	uint8_t data[16 * LTC6811_DEVICES];

	ltc6811(ADAX | MD73 | gpio);

	ltc6811_read(RDAUXA, &data[0]);
	ltc6811_read(RDAUXB, &data[8 * LTC6811_DEVICES]);

	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		switch (gpio)
		{
			case 1:
			case 2:
				break;
			case 3:
				PCB_Temperature[i] = ((data[i*8 + 4 + 1] << 8) | data[i*8 + 4]);// LTC GPIO 2, Byte 4 und 5 des Registers
				break;
			case 4:
			case 5:
				break;
			case 6:
				Sec_Ref[i] = ((data[i*16 + 6 + 1] << 8) | data[i*16 + 6]);		// LTC Sec Referenzspannung einlesen, Byte 6 und 7 des Registers
				break;
			default:
				break;
		}
	}
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

		LTC6811_soc[i] = ((data[i*8 + 1] << 8) | data[i*8]);
		LTC6811_Temperature[i] = ((data[i*8 + 3] << 8) | data[i*8 + 2]);
		LTC6811_analogvolt[i] = ((data[i*8 + 5] << 8) | data[i*8 + 4]);
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
void bms_volt_temp(uint8_t tempsensor)
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
		}

		for (uint8_t j = 0; j < 2; j++)
		{
			celltemperature[i][2*tempsensor + j] = ((data[(LTC6811_DEVICES*4+i)*8 + j*2 + 1] << 8) | data[(LTC6811_DEVICES*4+i)*8 + j*2]);
		}
	}
}
//----------------------------------------------------------------------

// Messe alle Zellspannungen und zwei Temperaturen
//----------------------------------------------------------------------
void bms_volt_SOC(void)
{
	uint8_t data[40 * LTC6811_DEVICES];

	ltc6811(ADCVSC | MD73);

	ltc6811_read(RDCVA, &data[0]);
	ltc6811_read(RDCVB, &data[8 * LTC6811_DEVICES]);
	ltc6811_read(RDCVC, &data[16 * LTC6811_DEVICES]);
	ltc6811_read(RDCVD, &data[24 * LTC6811_DEVICES]);
	ltc6811_read(RDSTATA, &data[32 * LTC6811_DEVICES]);

	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		for (uint8_t j = 0; j < 12; j++)
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
		}

		LTC6811_soc[i] = ((data[(LTC6811_DEVICES*4+i)*8 + 1] << 8) | data[(LTC6811_DEVICES*4+i)*8]);
	}
}
//----------------------------------------------------------------------

// Fuehre BMS Operation durch
//----------------------------------------------------------------------
void bms_work(void)
{
	bms_volt_temp(bms_tempcount);
	bms_Vminmax();
	bms_Tminmax();
	bms_MSvoltage();
//	bms_ltc_status();

	bms_tempcount++;

	if (bms_tempcount == LTC1380_SENSORES)
	{
		bms_tempcount = 0;
	}

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
		CAN_Output_PaketListe[10+i].msg.buf[0] = celltemperature[0][0+i*4];
		CAN_Output_PaketListe[10+i].msg.buf[1] = (celltemperature[0][0+i*4]>>8);
		CAN_Output_PaketListe[10+i].msg.buf[2] = celltemperature[0][1+i*4];
		CAN_Output_PaketListe[10+i].msg.buf[3] = (celltemperature[0][1+i*4]>>8);
		CAN_Output_PaketListe[10+i].msg.buf[4] = celltemperature[0][2+i*4];
		CAN_Output_PaketListe[10+i].msg.buf[5] = (celltemperature[0][2+i*4]>>8);
		CAN_Output_PaketListe[10+i].msg.buf[6] = celltemperature[0][3+i*4];
		CAN_Output_PaketListe[10+i].msg.buf[7] = (celltemperature[0][3+i*4]>>8);
	}

	// Stackvoltage
	CAN_Output_PaketListe[14].msg.buf[0] = stackvoltage;
	CAN_Output_PaketListe[14].msg.buf[1] = (stackvoltage >> 8);
	CAN_Output_PaketListe[14].msg.buf[2] = (stackvoltage >> 16);
	CAN_Output_PaketListe[14].msg.buf[3] = (stackvoltage >> 24);

#ifdef DEBUG_BMS_WORK
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		for (uint8_t j = 0; j < 12; j++)
		{
			uartTransmitNumber(cellvoltage[i][j], 10);
			uartTransmit(", ", 2);
		}

		for (uint8_t j = 0; j < 16; j++)
		{
			uartTransmitNumber(celltemperature[i][j], 10);
			uartTransmit(", ", 2);
		}

		uartTransmitNumber(PCB_Temperature[i], 10);
	}
	uartTransmit("\n", 1);
#endif
}
//----------------------------------------------------------------------

// Pruefe ob BMS OK ist
//----------------------------------------------------------------------
void bms_ok(void)
{
	// TODO: BMS OK abfrage erstellen
}
//----------------------------------------------------------------------

// Minimal- / Maximalspannung ermitteln
//----------------------------------------------------------------------
void bms_Vminmax(void)
{
	mincellvoltage[LTC6811_DEVICES + 1] = 65535;
	maxcellvoltage[LTC6811_DEVICES + 1] = 0;

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
	mincelltemperature[LTC6811_DEVICES + 1] = 65535;
	maxcelltemperature[LTC6811_DEVICES + 1] = 0;

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
