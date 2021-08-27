//----------------------------------------------------------------------
// Titel	:	LTC6811.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	25.09.2020
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
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
#include "ltc6811.h"
#include "SPI_resource.h"
//----------------------------------------------------------------------


// Pec Lookuptabelle definieren
//----------------------------------------------------------------------
const uint16_t pec15Table[256] = {
	0x0000,	0xC599,	0xCEAB,	0x0B32,	0xD8CF,	0x1D56,	0x1664,	0xD3FD,
	0xF407,	0x319E,	0x3AAC,	0xFF35,	0x2CC8,	0xE951,	0xE263,	0x27FA,
	0xAD97,	0x680E,	0x633C,	0xA6A5,	0x7558,	0xB0C1,	0xBBF3,	0x7E6A,
	0x5990,	0x9C09,	0x973B,	0x52A2,	0x815F,	0x44C6,	0x4FF4,	0x8A6D,
	0x5B2E,	0x9EB7,	0x9585,	0x501C,	0x83E1,	0x4678,	0x4D4A,	0x88D3,
	0xAF29,	0x6AB0,	0x6182,	0xA41B,	0x77E6,	0xB27F,	0xB94D,	0x7CD4,
	0xF6B9,	0x3320,	0x3812,	0xFD8B,	0x2E76,	0xEBEF,	0xE0DD,	0x2544,
	0x02BE,	0xC727,	0xCC15,	0x098C,	0xDA71,	0x1FE8,	0x14DA,	0xD143,
	0xF3C5,	0x365C,	0x3D6E,	0xF8F7,	0x2B0A,	0xEE93,	0xE5A1,	0x2038,
	0x07C2,	0xC25B,	0xC969,	0x0CF0,	0xDF0D,	0x1A94,	0x11A6,	0xD43F,
	0x5E52,	0x9BCB,	0x90F9,	0x5560,	0x869D,	0x4304,	0x4836,	0x8DAF,
	0xAA55,	0x6FCC,	0x64FE,	0xA167,	0x729A,	0xB703,	0xBC31,	0x79A8,
	0xA8EB,	0x6D72,	0x6640,	0xA3D9,	0x7024,	0xB5BD,	0xBE8F,	0x7B16,
	0x5CEC,	0x9975,	0x9247,	0x57DE,	0x8423,	0x41BA,	0x4A88,	0x8F11,
	0x057C,	0xC0E5,	0xCBD7,	0x0E4E,	0xDDB3,	0x182A,	0x1318,	0xD681,
	0xF17B,	0x34E2,	0x3FD0,	0xFA49,	0x29B4,	0xEC2D,	0xE71F,	0x2286,
	0xA213,	0x678A,	0x6CB8,	0xA921,	0x7ADC,	0xBF45,	0xB477,	0x71EE,
	0x5614,	0x938D,	0x98BF,	0x5D26,	0x8EDB,	0x4B42,	0x4070,	0x85E9,
	0x0F84,	0xCA1D,	0xC12F,	0x04B6,	0xD74B,	0x12D2,	0x19E0,	0xDC79,
	0xFB83,	0x3E1A,	0x3528,	0xF0B1,	0x234C,	0xE6D5,	0xEDE7,	0x287E,
	0xF93D,	0x3CA4,	0x3796,	0xF20F,	0x21F2,	0xE46B,	0xEF59,	0x2AC0,
	0x0D3A,	0xC8A3,	0xC391,	0x0608,	0xD5F5,	0x106C,	0x1B5E,	0xDEC7,
	0x54AA,	0x9133,	0x9A01,	0x5F98,	0x8C65,	0x49FC,	0x42CE,	0x8757,
	0xA0AD,	0x6534,	0x6E06,	0xAB9F,	0x7862,	0xBDFB,	0xB6C9,	0x7350,
	0x51D6,	0x944F,	0x9F7D,	0x5AE4,	0x8919,	0x4C80,	0x47B2,	0x822B,
	0xA5D1,	0x6048,	0x6B7A,	0xAEE3,	0x7D1E,	0xB887,	0xB3B5,	0x762C,
	0xFC41,	0x39D8,	0x32EA,	0xF773,	0x248E,	0xE117,	0xEA25,	0x2FBC,
	0x0846,	0xCDDF,	0xC6ED,	0x0374,	0xD089,	0x1510,	0x1E22,	0xDBBB,
	0x0AF8,	0xCF61,	0xC453,	0x01CA,	0xD237,	0x17AE,	0x1C9C,	0xD905,
	0xFEFF,	0x3B66,	0x3054,	0xF5CD,	0x2630,	0xE3A9,	0xE89B,	0x2D02,
	0xA76F,	0x62F6,	0x69C4,	0xAC5D,	0x7FA0,	0xBA39,	0xB10B,	0x7492,
	0x5368,	0x96F1,	0x9DC3,	0x585A,	0x8BA7,	0x4E3E,	0x450C,	0x8095
};
//----------------------------------------------------------------------

// Wakeup LTC6811
//----------------------------------------------------------------------
void wakeup_ltc6811(void)
{
	for(uint8_t i=0; i<LTC6811_DEVICES; i++)
	{
		LTC6811_CS_ENABLE();
		HAL_Delay(2);														//isoSPI braucht Zeit bis ready
		LTC6811_CS_DISABLE();
		HAL_Delay(2);
	}
}
//----------------------------------------------------------------------

// Broadcast Command
//----------------------------------------------------------------------
void ltc6811(uint16_t command)
{
	// PEC berechnen, Anhand Command
	uint16_t pec;
	uint8_t cmd[4];
	pec = peccommand(command);
	
	cmd[0] = ((command>>8) & 0x07);
	cmd[1] = (command & 0xFF);
	cmd[2] = ((pec>>8) & 0xFF);
	cmd[3] = (pec & 0xFE);

	// Command übertragen
	LTC6811_CS_ENABLE();
	HAL_SPI_Transmit(&hspi1, cmd, 4, HAL_MAX_DELAY);

	// Wenn Command = STCOMM ist dann müssen noch 72 Takte übertragen werden
	if (command == STCOMM)
	{
		// 72 = 9 * 8 Bit Daten
		for (uint8_t i = 0; i < 9; i++)
		{
			// Dummy-Byte �bertragen
			HAL_SPI_Transmit(&hspi1, (uint8_t*)0xFF, 1, HAL_MAX_DELAY);
		}
	}
	
	LTC6811_CS_DISABLE();
	// Ende der Übertragung
}
//----------------------------------------------------------------------

/*
// Broadcast Write Command
//----------------------------------------------------------------------
void ltc6811_write(uint16_t command, uint8_t* data)
{
	// PEC berechnen, für Data Funktion nur bei einem Device gegeben
	uint16_t pec_c, pec_d;
	pec_c = peccommand(command);
	pec_d = peclookup(6, data);
	
	// Command übertragen
	LTC6811_CS_ENABLE();
	
	// Command fuer zu beschreibendes Register senden
	spi_transmit((command>>8) & 0x07);
	spi_transmit(command & 0xFF);
	spi_transmit((pec_c>>8) & 0xFF);
	spi_transmit(pec_c & 0xFE);
	
	// Data senden
	for (uint8_t i = 0; i < 6; i++)
	{
		spi_transmit(data[i]);
	}
	spi_transmit((pec_d>>8) & 0xFF);
	spi_transmit(pec_d & 0xFE);
	
	LTC6811_CS_DISABLE();
	// Ende der Übertragung
}
//----------------------------------------------------------------------

// Broadcast Read Command
//----------------------------------------------------------------------
void ltc6811_read(uint16_t command, uint8_t* data)
{
	// PEC berechnen, Anhand Command
	uint16_t pec;
	pec = peccommand(command);
	
	// Command übertragen
	LTC6811_CS_ENABLE();
	
	// Command fuer zu lesendes Register senden
	spi_transmit((command>>8) & 0x07);
	spi_transmit(command & 0xFF);
	spi_transmit((pec>>8) & 0xFF);
	spi_transmit(pec & 0xFE);
	
	// Data empfangen
	for (uint8_t i = 0; i < (8 * LTC6811_DEVICES); i++)
	{
		// Dummy Byte senden
		data[i] = spi_transmit(0xFF);
	}
	
	LTC6811_CS_DISABLE();
	// Ende der Übertragung
}
//----------------------------------------------------------------------
 */

// Pec Command bauen
//----------------------------------------------------------------------
uint16_t peccommand(uint16_t command)
{
	uint8_t pec[2];															// pec = Zwischenspeicher 16-Bit Command in 2x 8-Bit Bytes
	
	pec[1] = (command & 0xFF);												// pec[1] = lower Command Byte
	pec[0] = ((command >> 8) & 0x07);										// pec[0] = upper Command Byte
	
	return peclookup(2, pec);
}
//----------------------------------------------------------------------

// Pec kalculieren (Datasheet ltc6811 Page 76, Datasheet ltc6811 Page 72)
//----------------------------------------------------------------------
uint16_t peclookup(uint8_t len,	uint8_t *data)								// len = Anzahl Byte, data = Daten fuer die Pec ausgewaehlt wird
{
	uint16_t remainder, addr;												// remainder = Zwischenspeicher Pec, addr = Zwischenspeicher Addresse
	remainder = 16;															// Initialisiere reminder mit 16 (0b0000000000010000)
	
	// Schleife fuer die Pec-Calculation
	for(uint8_t i = 0; i < len; i++)
	{
		// Kalkuliere Pec Anhand der Lookuptabelle
		addr = ((remainder >> 7) ^ data[i]) & 0xFF;							// Tabellenaddresse berechnen
		remainder = (remainder << 8) ^ pec15Table[addr];					// Pec berechnen
	}
	
	return (remainder << 1);												// Der Pec hat eine 0 als LSB, remainder muss um 1 nach links geshiftet werden
}
//----------------------------------------------------------------------

/*
//----------------------------------------------------------------------
uint16_t test[256];
// CRC Tabelle berechnen (Datasheet ltc6811 Page 76)
//----------------------------------------------------------------------
void init_crc(void)
{
	uint16_t test_crc = 0x4599;
	uint16_t remainder;
	for (int i = 0; i < 256; i++)
	{
		remainder = i << 7;
		for (int bit = 8; bit > 0; --bit)
		{
			if (remainder & 0x4000)
			{
				remainder = ((remainder << 1));
				remainder = (remainder ^ test_crc);
			}
			else
			{
				remainder = ((remainder << 1));
			}
		}
		test[i] = remainder&0xFFFF;
	}
}
//----------------------------------------------------------------------*/

/*
// LTC6811 Status auslesen und auswerten
//----------------------------------------------------------------------
uint8_t ltc6811_check(void)
{
	uint8_t tmp_data[50] = {0}, result = 0;
	uint16_t temp = 0;

	// Verzögerungszeit zum wecken des LTC6811
	wakeup_ltc6811();

	// Commands für Status senden  Test 1
	ltc6811(CVST | MD73 | ST1);
	HAL_Delay(300);
	ltc6811(AXST | MD73 | ST1);
	HAL_Delay(300);
	ltc6811(STATST | MD73 | ST1);
	HAL_Delay(300);

	// Register auslesen Test 1
	ltc6811_read(RDCVA, &tmp_data[0]);
	ltc6811_read(RDCVB, &tmp_data[6]);
	ltc6811_read(RDCVC, &tmp_data[12]);
	ltc6811_read(RDCVD, &tmp_data[18]);

	ltc6811_read(RDAUXA, &tmp_data[24]);
	ltc6811_read(RDAUXB, &tmp_data[30]);

	ltc6811_read(RDSTATA, &tmp_data[36]);
	ltc6811_read(RDSTATB, &tmp_data[42]);

	// Daten prüfen Test 1
	for (uint8_t i=0; i<22; i++)
	{
		temp = ((tmp_data[i*2+1]<<8)|tmp_data[i*2]);
		if (temp != 0x9555)
			result = 1;
	}

	// Commands für Status senden Test 2
	ltc6811(CVST | MD73 | ST2);
	HAL_Delay(300);
	ltc6811(AXST | MD73 | ST2);
	HAL_Delay(300);
	ltc6811(STATST | MD73 | ST2);
	HAL_Delay(300);

	// Register auslesen Test 2
	ltc6811_read(RDCVA, &tmp_data[0]);
	ltc6811_read(RDCVB, &tmp_data[6]);
	ltc6811_read(RDCVC, &tmp_data[12]);
	ltc6811_read(RDCVD, &tmp_data[18]);

	ltc6811_read(RDAUXA, &tmp_data[24]);
	ltc6811_read(RDAUXB, &tmp_data[30]);

	ltc6811_read(RDSTATA, &tmp_data[36]);
	ltc6811_read(RDSTATB, &tmp_data[42]);

	// Daten prüfen Test 2
	for (uint8_t i=0; i<22; i++)
	{
		temp = ((tmp_data[i*2+1]<<8)|tmp_data[i*2]);
		if (temp != 0x6AAA)
			result |= 2;
	}

	ltc6811(DIAGN);
	wakeup_ltc6811();
	ltc6811_read(RDSTATB, &tmp_data[0]);

	if (tmp_data[5] & (1<<1))
	{
		result |= 4;
	}

	/ * // Command für OpenWire PUP = 1
	ltc6811(ADOW | MD73 | PUP);

	// Register auslesen OpenWire
	ltc6811_read(RDCVA, &tmp_data[0]);
	ltc6811_read(RDCVB, &tmp_data[6]);
	ltc6811_read(RDCVC, &tmp_data[12]);
	ltc6811_read(RDCVD, &tmp_data[18]);

	// Command für OpenWire PUP = 0
	ltc6811(ADOW | MD73);

	// Register auslesen OpenWire
	ltc6811_read(RDCVA, &tmp_data[24]);
	ltc6811_read(RDCVB, &tmp_data[30]);
	ltc6811_read(RDCVC, &tmp_data[36]);
	ltc6811_read(RDCVD, &tmp_data[42]);* /

	return result;										// return result
}
//----------------------------------------------------------------------*/
