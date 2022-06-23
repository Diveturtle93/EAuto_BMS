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
#include "error.h"
#include "my_math.h"
#include "BasicUart.h"
#include "millis.h"
//----------------------------------------------------------------------

// Definiere Zellenarray
//----------------------------------------------------------------------
ltc6811_configuration_tag ltc6811_Conf;										// LTC6811 Configurations Register
uint8_t CellVoltage[LTC6811_DEVICES][12];									// Array fuer gemessene Zellspannungen
uint8_t CellTemperature[LTC6811_DEVICES][12];								// Array fuer gemessene Zelltemperaturen
//----------------------------------------------------------------------

// Definiere Globale Variable
//----------------------------------------------------------------------
static LTC6811_State Ltc6811State;											// Statusvariable Statemaschine
uint32_t timeLtc6811State;													// Time Variable fuer State
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

// Setze Statemaschine von LTC6811
//----------------------------------------------------------------------
void set_ltc6811_state(LTC6811_State newState)
{
	Ltc6811State = newState;												// Neuen Status setzen
	timeLtc6811State = millis();											// Zeit speichern

#ifdef DEBUG_LTC6811
	ITM_SendString("LTC6811: ");

	ITM_SendString(" Neuer State: ");

	switch (Ltc6811State)
	{
		case LTCStandby:
			ITM_SendString("Standby\n");
			break;

		case LTCMeasure:
			ITM_SendString("Measure\n");
			break;

		case LTCRefup:
			ITM_SendString("Refup\n");
			break;

		case LTCSetRefup:
			ITM_SendString("SetRefup\n");
			break;

		case LTCWakeup:
			ITM_SendString("Wakeup\n");
			break;

		case LTCExtendedBalancing:
			ITM_SendString("Extended Balancing\n");
			break;

		case LTCSleep:
			ITM_SendString("Sleep\n");
			break;

		default:
			ITM_SendString("#RED#FEHLER\n");
			break;
	}
#endif
}
//----------------------------------------------------------------------

// Statemaschine von LTC6811
//----------------------------------------------------------------------
void ltc6811_statemaschine(void)
{
	// Messzeit feststellen, Messzeit immer fuer alle Zellen + GPIOs (Das ist eine Abschaetzung zur sicheren Seite)
	uint32_t measurementDuration; // in us
	uint16_t samplingMode = MD73;

	switch (Ltc6811State)
	{
		case LTCSleep:
			break;

		case LTCStandby:
			if (timeLtc6811State + 1800 < millis())							// ms
			{
				// 1.8s ist in diesem Zustand vergangen, Watchdog koennte ausgeloest haben (t_sleep)
				set_ltc6811_state(LTCSleep);
				break;
			}

			if (ltc6811_Conf.REFON == 1)
			{
				set_ltc6811_state(LTCRefup);
			}
			break;

		case LTCRefup:
			if (ltc6811_Conf.REFON == 1)
			{
				if (timeLtc6811State + 1800 < millis())						// ms
				{
					// 1.8s ist in diesem Zustand vergangen, Watchdog koennte ausgeloest haben (t_sleep)
					set_ltc6811_state(LTCSleep);
				}
			}
			else
			{
				set_ltc6811_state(LTCStandby);
			}
			break;

		case LTCMeasure:
			if (ltc6811_Conf.ADCOPT == 0)
			{
				switch (samplingMode)
				{
					case MD2714:
						//measurementDuration = 1503;							// us
						measurementDuration = 2;							// ms
						break;

					case MD73:
						//measurementDuration = 3133;							// us
						measurementDuration = 4;							// ms
						break;

					case MD262:
						//measurementDuration = 268442;						// us
						measurementDuration = 269;							// ms
						break;

					case MD1422:
						//measurementDuration = 17096;						// us
						measurementDuration = 17;							// ms
						break;

					default:
						//measurementDuration = 300000;						// us Dummy Wert
						measurementDuration = 300;							// ms
						break;
				}
			}
			else if (ltc6811_Conf.ADCOPT == 1)
			{
				switch (samplingMode)
				{
					case MD2714:
						//measurementDuration = 1736;							// us
						measurementDuration = 2;							// ms
						break;

					case MD73:
						//measurementDuration = 4064;							// us
						measurementDuration = 4;							// ms
						break;

					case MD262:
						//measurementDuration = 9648;							// us
						measurementDuration = 10;							// ms
						break;

					case MD1422:
						//measurementDuration = 5925;							// us
						measurementDuration = 6;							// ms
						break;

					default:
						//measurementDuration = 300000;						// us Dummy Wert
						measurementDuration = 300;							// ms
						break;
				}
			}
			else
			{

			}

			// Wenn die Referenz zuerst eingeschaltet werden muss, dauert die Messung 5ms (t_Refup) laenger
			measurementDuration = measurementDuration + 5;					// ms

			if (timeLtc6811State + measurementDuration < millis())			// ms
			{
				// Messung ist beendet
				if (ltc6811_Conf.REFON == 1)
				{
					set_ltc6811_state(LTCRefup);
				}
				else
				{
					set_ltc6811_state(LTCStandby);
				}
			}

			break;

		case LTCWakeup:
			// 500us (t_Wakeup) warten bis Chip aufgewacht ist
			if (timeLtc6811State + 1 < millis())							// ms
			{
				set_ltc6811_state(LTCStandby);
			}
			break;

		case LTCSetRefup:
			// 5ms (t_Refup) warten bis Referenz eingeschaltet ist
			if (timeLtc6811State + 5 < millis())							// ms
			{
				set_ltc6811_state(LTCRefup);
			}
			break;

		default:
			break;
	}
}
//----------------------------------------------------------------------

// Bekomme aktuellen State LTC6811
//----------------------------------------------------------------------
LTC6811_State get_ltc6811_state(void)
{
	// Statemaschine abfragen
	ltc6811_statemaschine();

	// Aktuellen State ausgeben
	return Ltc6811State;
}
//----------------------------------------------------------------------

// Broadcast Command
//----------------------------------------------------------------------
void ltc6811(uint16_t command)
{
	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Aufruf von Transcreceive LTC6811.\n");
#endif

	// PEC berechnen, Anhand Command
	uint16_t pec;															// pec = Zwischenspeicher 16-Bit Command
	uint8_t cmd[4];															// Zwischenspeicher Command + Pec CRC
	pec = peccommand(command);												// CRC berechnen

	// Command in cmd abspeichern
	cmd[0] = ((command >> 8) & 0x07);
	cmd[1] = (command & 0xFF);
	cmd[2] = ((pec >> 8) & 0xFF);
	cmd[3] = (pec & 0xFE);

	if (get_ltc6811_state() == LTCStandby)
	{
		set_ltc6811_state(LTCSetRefup);
		while (get_ltc6811_state() == LTCSetRefup);
	}

	// Befehl ueber IsoSPI senden
	IsoSPI_cmd(&cmd[0]);													// Sende Befehl

	// Setze Statemaschine auf Messen
	if ((command & ADAX) || (command & ADCVC) || (command & ADCVAX) || (command & ADSTAT))
	{
		set_ltc6811_state(LTCMeasure);
	}

	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Command wurde gesendet.\n");
	ITM_SendString("Folgendes wurde gesendet:");

	// Sende Command auf UART
	for (uint8_t i = 0; i < 4; i++)
	{
		ITM_SendChar(' ');
		ITM_SendNumber(cmd[i]);
	}
	ITM_SendChar('\n');
#endif
}
//----------------------------------------------------------------------

// Broadcast Write Command
//----------------------------------------------------------------------
void ltc6811_write(uint16_t command, uint8_t* data)
{
	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Aufruf von Transceive LTC6811.\n"); // 31
#endif

	// PEC berechnen, fuer Data Funktion nur bei einem Device gegeben
	uint16_t pec_c, pec_d;													// pec_c = Zwischenspeicher 16-Bit Command, pec_d = Zwischenspeicher 16-Bit Data
	uint8_t cmd[4];															// Zwischenspeicher Command + Pec CRC
	uint8_t tmp_data[8 * LTC6811_DEVICES];									// Zwischenspeicher Daten + Pec CRC
	pec_c = peccommand(command);											// Pec Command berechnen

	// Command in cmd abspeichern
	cmd[0] = ((command  >> 8) & 0x07);
	cmd[1] = (command & 0xFF);
	cmd[2] = ((pec_c >> 8) & 0xFF);
	cmd[3] = (pec_c & 0xFE);

	// Daten in tmp_data abspeichern zum Senden
	for (uint8_t j = 0; j < LTC6811_DEVICES; j++)
	{
		// Schleife um Daten fuer einen IC abzuspeichern
		for (uint8_t i = 0; i < 6; i++)
		{
			tmp_data[j*8+i] = data[j*6+i];
		}

		// Pec berechnen pro IC einmal
		pec_d = peclookup(6, &tmp_data[j*8]);								// Pec Daten berechnen

		// Pec abspeichern fuer einen IC
		tmp_data[6] = ((pec_d >> 8) & 0xFF);
		tmp_data[7] = (pec_d & 0xFE);
	}

	// Befehl ueber IsoSPI senden
	IsoSPI_transmit(&cmd[0], &tmp_data[0]);									// Sende Daten

	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Command wurde gesendet.\n");
	ITM_SendString("Folgendes wurde gesendet:");

	// Sende Command auf UART
	for (uint8_t i = 0; i < 4; i++)
	{
		ITM_SendChar(' ');
		ITM_SendNumber(cmd[i]);
	}
	ITM_SendChar('\n');

	ITM_SendString("Daten wurde gesendet.\n");
	ITM_SendString("Folgendes wurde gesendet:");

	// Sende Daten auf UART
	for (uint8_t i = 0; i < 8; i++)
	{
		ITM_SendChar(' ');
		ITM_SendNumber(data[i]);
	}
	ITM_SendChar('\n');
#endif
}
//----------------------------------------------------------------------

// Broadcast Read Command
//----------------------------------------------------------------------
uint8_t ltc6811_read(uint16_t command, uint8_t* data)
{
	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Aufruf von Receive LTC6811.\n");
#endif

	// PEC berechnen, Anhand Command
	uint16_t pec;															// pec = Zwischenspeicher 16-Bit Command
#ifdef DEBUG_LTC6811
	uint16_t tmp;															// Zwischenspeicher fuer Pruefung CRC
#endif
	uint8_t cmd[4];															// Zwischenspeicher Command + Pec CRC
	pec = peccommand(command);

	// Command in cmd abspeichern
	cmd[0] = ((command >> 8) & 0x07);
	cmd[1] = (command & 0xFF);
	cmd[2] = ((pec >> 8) & 0xFF);
	cmd[3] = (pec & 0xFE);

	while (get_ltc6811_state() == LTCMeasure);								// Warten solange bis LTC fertig mit Messen ist

	// Befehl ueber IsoSPI senden
	IsoSPI_read(&cmd[0], &data[0]);											// Sende Daten

	// Pec zuruecksetzen
	pec = 0;

	// Pec pruefen
	for (uint8_t i = 0; i < LTC6811_DEVICES; i++)
	{
		// Variante 1, Pec berechnen und pruefen, ob richtiger Pec mitgesendet wurde
#ifdef DEBUG_LTC6811
		tmp = ((data[i + 6] << 8) + data[i + 7]);
		pec = peclookup(6, &data[i*8]);
		if (pec != tmp)
		{
			uartTransmit("Pec Error1: ", 11);
			uartTransmitNumber(i + 1, 10);
			uartTransmit(" ", 1);
			uartTransmitNumber(tmp, 16);
			uartTransmit(" ", 1);
			uartTransmitNumber(pec, 16);
			uartTransmit("\n", 1);
		}
#endif

		// Pec zuruecksetzen
		pec = 0;

		// Variante 2, Daten inklusive Pec mit durch Peccheck pruefen, ob Ergebnis gleich 0 ist
		pec = peccheck(8, &data[i*8]);

#ifdef DEBUG_LTC6811
		if (pec != 0)
		{
			uartTransmit("Pec Error2: ", 11);
			uartTransmitNumber(i + 1, 10);
			uartTransmit(" ", 1);
			uartTransmitNumber(tmp, 16);
			uartTransmit(" ", 1);
			uartTransmitNumber(pec, 16);
			uartTransmit("\n", 1);
		}
#endif
	}

	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Command wurde empfangen.\n");
	ITM_SendString("Folgendes wurde empfangen:");

	// Sende Command auf UART
	for (uint8_t i = 0; i < 4; i++)
	{
		ITM_SendChar(' ');
		ITM_SendNumber(cmd[i]);
	}
	ITM_SendChar('\n');

	ITM_SendString("Daten wurde empfangen.\n");
	ITM_SendString("Folgendes wurde empfangen:");

	// Sende Daten auf UART
	for (uint8_t i = 0; i < 8; i++)
	{
		ITM_SendChar(' ');
		ITM_SendNumber(data[i]);
	}
	ITM_SendChar('\n');
#endif

	return 0;
}
//----------------------------------------------------------------------

// Pec Command bauen
//----------------------------------------------------------------------
uint16_t peccommand(uint16_t command)
{
	// Variable definieren
	uint8_t pec[2];															// pec = Zwischenspeicher 16-Bit Command in 2x 8-Bit Bytes
	
	// 16 Bit Command in 8 Bit Array uebertragen
	pec[1] = (command & 0xFF);												// pec[1] = lower Command Byte
	pec[0] = ((command >> 8) & 0x07);										// pec[0] = upper Command Byte
	
	// Pec zurueckgeben
	return peclookup(2, pec);
}
//----------------------------------------------------------------------

// Pec kalculieren (Datasheet ltc6811 Page 76, Datasheet ltc6811 Page 72)
//----------------------------------------------------------------------
uint16_t peclookup(uint8_t len,	uint8_t *data)								// len = Anzahl Byte, data = Daten fuer die Pec ausgewaehlt wird
{
	// Variable definieren
	uint16_t remainder, addr;												// remainder = Zwischenspeicher Pec, addr = Zwischenspeicher Addresse
	remainder = 16;															// Initialisiere reminder mit 16 (0b0000000000010000)
	
	// Schleife fuer die Pec-Calculation
	for(uint8_t i = 0; i < len; i++)
	{
		// Kalkuliere Pec Anhand der Lookuptabelle
		addr = ((remainder >> 7) ^ data[i]) & 0xFF;							// Tabellenaddresse berechnen
		remainder = (remainder << 8) ^ pec15Table[addr];					// Pec berechnen
//		uartTransmitNumber(data[i], 16);
//		uartTransmit("\n", 1);
	}
	
	// Pec zurueckgeben
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

// Validiere Pec von Daten
//----------------------------------------------------------------------
uint8_t peccheck(uint8_t len, uint8_t *data)
{
	// Variable definieren
	uint16_t pec = peclookup(len, data);

	// Wenn Ergebnis 0, ist Pec OK
	if (pec == 0)
	{
		return 0;
	}
	// Wenn Ergebnis 1, ist Pec nicht OK
	else
	{
		return 1;
	}
}
//----------------------------------------------------------------------

// Initialisiere LTC6811, Schreibe Config in Konfigurationsregister
//----------------------------------------------------------------------
void ltc6811_init(void)
{
	// Setze Konfiguration
	ltc6811_Conf.ADCOPT = 0;												// Setze ADC Mode option, 0 = default
	ltc6811_Conf.REFON = 0;													// Setze Referenzspannung, 0 = default, 0 = Shutdown after Conversion, 1 = Shutdown after Watchdog timeout
	ltc6811_Conf.LTC_GPIO1 = 1;												// Setze GPIO Pulldown, 1 = default, 0 = On, 1 = Off
	ltc6811_Conf.LTC_GPIO2 = 1;												// Setze GPIO Pulldown, 1 = default, 0 = On, 1 = Off
	ltc6811_Conf.LTC_GPIO3 = 1;												// Setze GPIO Pulldown, 1 = default, 0 = On, 1 = Off
	ltc6811_Conf.LTC_GPIO4 = 1;												// Setze GPIO Pulldown, 1 = default, 0 = On, 1 = Off
	ltc6811_Conf.LTC_GPIO5 = 1;												// Setze GPIO Pulldown, 1 = default, 0 = On, 1 = Off

	// Setze Vergleichsspannungen
	ltc6811_Conf.VUV = LTC6811_UVOLT;										// Setze Vergleichsspannung fuer Unterspannung
	ltc6811_Conf.VOV = LTC6811_OVOLT;										// Setze Vergleichsspannung fuer Ueberspannung

	// Balancing
	ltc6811_Conf.DCC1 = 0;													// Balancing von Zelle 1 ausschalten
	ltc6811_Conf.DCC2 = 0;													// Balancing von Zelle 2 ausschalten
	ltc6811_Conf.DCC3 = 0;													// Balancing von Zelle 3 ausschalten
	ltc6811_Conf.DCC4 = 0;													// Balancing von Zelle 4 ausschalten
	ltc6811_Conf.DCC5 = 0;													// Balancing von Zelle 5 ausschalten
	ltc6811_Conf.DCC6 = 0;													// Balancing von Zelle 6 ausschalten
	ltc6811_Conf.DCC7 = 0;													// Balancing von Zelle 7 ausschalten
	ltc6811_Conf.DCC8 = 0;													// Balancing von Zelle 8 ausschalten
	ltc6811_Conf.DCC9 = 0;													// Balancing von Zelle 9 ausschalten
	ltc6811_Conf.DCC10 = 0;													// Balancing von Zelle 10 ausschalten
	ltc6811_Conf.DCC11 = 0;													// Balancing von Zelle 11 ausschalten
	ltc6811_Conf.DCC12 = 0;													// Balancing von Zelle 12 ausschalten
	ltc6811_Conf.DCTO = 0;													// Balancing Timer zuruecksetzen

	// Schreibe Konfiguration in Register am LTC6811
	//ltc6811_write(WRCFG, &ltc6811_Conf.ltc6811_configuration[0]);
}
//----------------------------------------------------------------------

// LTC6811 Status auslesen und auswerten
//----------------------------------------------------------------------
uint8_t ltc6811_check(void)
{
	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Aufruf von Check LTC6811.\n");
#endif

	// Variablen definieren
	uint8_t tmp_data[64] = {0}, error = 0;									// Speicher Registerwerte, Fehlerspeicher

	// Alle Register zuruecksetzen
	ltc6811(CLRCELL);														// Register Zellspannung auf default setzen
	ltc6811(CLRAUX);														// Register GPIO-Spannung auf default setzen
	ltc6811(CLRSTAT);														// Register Interne Messungen auf default setzen

	// Lese Register Status B aus
	ltc6811_read(RDSTATB, &tmp_data[0]);

	// Thermal Shutdown pruefen
	if (tmp_data[5] & !(1 << 0))
	{
		error |= (1 << 0);													// Thermal Shutdown nicht Ok

#ifdef DEBUG_LTC6811
		ITM_SendString("Thermal Shutdown");
		ITM_SendChar('\n');
#endif
	}

	// Selbsttest 1 Digitale Filter
	if (ltc6811_test(ST1 | MD73) == 1)
	{
		error |= (1 << 1);													// Selbsttest 1 nicht bestanden

#ifdef DEBUG_LTC6811
		ITM_SendString("Selbsttest 1 Fehler");
		ITM_SendChar('\n');
#endif
	}
	HAL_Delay(300);

	// Selbsttest 2 Digitale Filter
	if (ltc6811_test(ST2 | MD73) == 1)
	{
		error |= (1 << 2);													// Selbsttest 2 nicht bestanden

#ifdef DEBUG_LTC6811
		ITM_SendString("Selbsttest 2 Fehler");
		ITM_SendChar('\n');
#endif
	}
	HAL_Delay(300);

	// Selbsttest Multiplexer
	if (ltc6811_diagn() == 1)
	{
		error |= (1 << 3);													// Multiplexertest nicht bestanden

#ifdef DEBUG_LTC6811
		ITM_SendString("Multiplexer Fehler");
		ITM_SendChar('\n');
#endif
	}
	HAL_Delay(300);

	// Open Wire Check durchfuehren
	if (ltc6811_openwire() == 1)
	{
		error |= (1 << 4);													// Open-Wire Test nicht bestanden

#ifdef DEBUG_LTC6811
		ITM_SendString("Openwire Fehler");
		ITM_SendChar('\n');
#endif
	}

	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Error Code:\t");
	ITM_SendNumber(error);
	ITM_SendChar('\n');
#endif

	// Fehlercode zurueckgeben
	return error;															// Fehler 0 = alles Ok, Fehler > 0 = Selbsttest fehlerhaft
}
//----------------------------------------------------------------------

// Selbsttest Digitale Filter (Datasheet ltc6811 Page 28)
//----------------------------------------------------------------------
uint8_t ltc6811_test(uint16_t command)
{
	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Aufruf von Test LTC6811.\n");
#endif

	// Variablen definieren
	uint8_t tmp_data[64] = {0};												// Speicher Registerwerte
	uint16_t tmp = 0, test_pattern = 0;										// Zwischenspeicher, Kontrollvariable Selbsttest

	// Commands fuer Status senden  Test 1
	ltc6811(CVST | command);												// Digitalfilter Check Zellspannungen
	HAL_Delay(300);															// 300ms zwischen den Selbsttests warten
	ltc6811(AUXST | command);												// Digitalfilter Check GPIO-Spannungen
	HAL_Delay(300);															// 300ms zwischen den Selbsttests warten
	ltc6811(STATST | command);												// Digitalfilter Check Interne Messungen
	HAL_Delay(300);															// 300ms zwischen den Selbsttests warten

	// Register auslesen Test 1
	// Spannungsregister
	ltc6811_read(RDCVA, &tmp_data[0]);										// Lese Register CVA zurueck
	ltc6811_read(RDCVB, &tmp_data[8]);										// Lese Register CVB zurueck
	ltc6811_read(RDCVC, &tmp_data[16]);										// Lese Register CVC zurueck
	ltc6811_read(RDCVD, &tmp_data[24]);										// Lese Register CVD zurueck

	// GPIO-Register
	ltc6811_read(RDAUXA, &tmp_data[32]);									// Lese Register AUXA zurueck
	ltc6811_read(RDAUXB, &tmp_data[40]);									// Lese Register AUXB zurueck

	// Statusregister
	ltc6811_read(RDSTATA, &tmp_data[48]);									// Lese Register STATA zurueck
	ltc6811_read(RDSTATB, &tmp_data[56]);									// Lese Register STATB zurueck

	// Lookup fuer Selbstest digitaler Filter
	// Kontrollvariable heraussuchen
	if (command & MD2714)													// Wenn Sampling Frequenz = MD2714
	{
		// Wenn ADCOPT gesetzt
		if (ltc6811_Conf.ADCOPT == 1)
		{
			// Wenn Selbsttest 1 gewaehlt
			if (command == ST1)
			{
				test_pattern = 0x9553;										// Registerwert bei 14kHz
			}
			// Wenn Selbsttest 2 gewaehlt
			else if (command == ST2)
			{
				test_pattern = 0x6AAC;										// Registerwert bei 14kHz
			}
			// Bei fehlerhaften Einstellungen
			else
			{
				test_pattern = 0;											// Registerwert = 0 damit Fehler ausloest
			}
		}
		else																// Wenn ADCOPT nicht gesetzt
		{
			// Wenn Selbsttest 1 gewaehlt
			if (command & ST1)
			{
				test_pattern = 0x9565;										// Registerwert bei 27kHz
			}
			// Wenn Selbsttest 2 gewaehlt
			else if (command & ST2)
			{
				test_pattern = 0x6A9A;										// Registerwert bei 27kHz
			}
			// Bei fehlerhaften Einstellungen
			else
			{
				test_pattern = 0;											// Registerwert = 0 damit Fehler ausloest
			}
		}
	}
	else
	{
		// Wenn Selbsttest 1 gewaehlt
		if (command & ST1)
		{
			test_pattern = 0x9555;											// Registerwert bei allen anderen Sampling Frequenzen
		}
		// Wenn Selbsttest 2 gewaehlt
		else if (command & ST2)
		{
			test_pattern = 0x6AAA;											// Registerwert bei allen anderen Sampling Frequenzen
		}
		// Bei fehlerhaften Einstellungen
		else
		{
			test_pattern = 0;												// Registerwert = 0 damit Fehler ausloest
		}
	}

	// Daten pruefen Test 1
	for (uint8_t i=0; i<22; i++)
	{
		// Auswaehlen welches Register im Array steht
		switch (i)
		{
			// Register CVA
			case 0:
			case 1:
			case 2:
				tmp = ((tmp_data[i*2+1]<<8)|tmp_data[i*2]);					// Register CVA umwandeln
				break;
			// Register CVB
			case 3:
			case 4:
			case 5:
				tmp = ((tmp_data[i*2+3] << 8)|tmp_data[i*2+2]);				// Register CVB umwandeln
				break;
			// Register CVC
			case 6:
			case 7:
			case 8:
				tmp = ((tmp_data[(i+2)*2+1] << 8)|tmp_data[(i+2)*2]);		// Register CVC umwandeln
				break;
			// Register CVD
			case 9:
			case 10:
			case 11:
				tmp = ((tmp_data[(i+2)*2+3] << 8)|tmp_data[(i+2)*2+2]);		// Register CVD umwandeln
				break;
			// Register AUXA
			case 12:
			case 13:
			case 14:
				tmp = ((tmp_data[(i+4)*2+1] << 8)|tmp_data[(i+4)*2]);		// Register AUXA umwandeln
				break;
			// Register AUXB
			case 15:
			case 16:
			case 17:
				tmp = ((tmp_data[(i+4)*2+3] << 8)|tmp_data[(i+4)*2+2]);		// Register AUXB umwandeln
				break;
			// Register STATA
			case 18:
			case 29:
			case 20:
				tmp = ((tmp_data[(i+6)*2+1] << 8)|tmp_data[(i+6)*2]);		// Register STATA umwandeln
				break;
			// Register STATB
			case 21:
				tmp = ((tmp_data[(i+6)*2+3] << 8)|tmp_data[(i+6)*2+2]);		// Register STATB umwandeln
				break;
			// Kein Register
			default:
				break;
		}

		// Vergleiche Registerwert mit Vorgabewert aus Datenblatt
		if (tmp != test_pattern)
		{
#ifdef DEBUG_LTC6811
			ITM_SendString("Test failed: ");
			ITM_SendNumber(i);
			ITM_SendChar('\n');
#endif
			return 1;														// Selbsttest 1 nicht OK
		}
	}
#ifdef DEBUG_LTC6811
	ITM_SendString("Test passed\n");
#endif
	return 0;																// Selbsttest 1 OK
}
//----------------------------------------------------------------------

// Selbstdiagnose Multiplexer (Datasheet ltc6811 Page 27)
//----------------------------------------------------------------------
uint8_t ltc6811_diagn(void)
{
	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Aufruf von Diagnostic LTC6811.\n");
#endif

	// Variablen definieren
	uint8_t tmp_data[8] = {0};												// Speicher Registerwerte

	// Command senden
	ltc6811(DIAGN);															// Multiplexer Check

	// Verzoegerungszeit 10ms, DIAG Befehl braucht ca. 400µs bis 4ms
	HAL_Delay(10);

	// Lese Register
	ltc6811_read(RDSTATB, &tmp_data[0]);									// Lese Status B Register fuer Multiplexer Check

	// Multiplexer pruefen
	if (tmp_data[5] & (1 << 1))
	{
		return 1;															// Multiplexertest nicht OK
	}

	return 0;																// Multiplexertest OK
}
//----------------------------------------------------------------------

// LTC6811 Openwire check
//----------------------------------------------------------------------
uint8_t ltc6811_openwire(void)
{
	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Aufruf von Openwire LTC6811.\n");
#endif

	// Arrays definieren
	uint8_t pulldown[32] = {0}, pullup[32] = {0};							// Speicher Registerwerte
	uint16_t cell[1] = {0}, openwire[13] = {0};								// Speicher Zelle, Openwire vergleic Threshold

	// Pullup Current, drei Durchgaenge
	for (uint8_t i = 0; i < 2; i++)
	{

		// Commands fuer Openwire Test
		ltc6811(ADOW | MD262 | PUP);										// Pullup Current
		HAL_Delay(300);
	}

	// Register auslesen OpenWire
	ltc6811_read(RDCVA, &pullup[0]);
	ltc6811_read(RDCVB, &pullup[8]);
	ltc6811_read(RDCVC, &pullup[16]);
	ltc6811_read(RDCVD, &pullup[24]);

	// Pulldown Current, drei Durchgaenge
	for (uint8_t i = 0; i < 2; i++)
	{

		// Commands fuer Openwire Test
		ltc6811(ADOW | MD262 | PUP);											// Pulldown Current
		HAL_Delay(300);
	}

	// Register auslesen OpenWire
	ltc6811_read(RDCVA, &pulldown[0]);
	ltc6811_read(RDCVB, &pulldown[8]);
	ltc6811_read(RDCVC, &pulldown[16]);
	ltc6811_read(RDCVD, &pulldown[24]);

	// Schleife zum umformatieren der Daten
	for (uint8_t i = 0; i < 13; i++)
	{
		// Auswahl welche Leitung
		switch (i)
		{
			// Leitungen Zelle 1/2 bis 3/4
			case 0:
				openwire[i] = ((pulldown[1] << 8) + pulldown[0]);
				break;
			case 1:
			case 2:
				openwire[i] = getDifference(((pullup[i*2+1] << 8) + pullup[i*2]), ((pulldown[i*2+1] << 8) + pulldown[i*2]));
				break;
			// Leitungen Zelle 4/5 bis 6/7
			case 3:
			case 4:
			case 5:
				openwire[i] = getDifference(((pullup[i*2+3] << 8) + pullup[i*2+2]), ((pulldown[i*2+3] << 8) + pulldown[i*2+2]));
				break;
			// Leitungen Zelle 7/8 bis 9/10
			case 6:
			case 7:
			case 8:
				openwire[i] = getDifference(((pullup[i*2+5] << 8) + pullup[i*2+4]), ((pulldown[i*2+5] << 8) + pulldown[i*2+4]));
				break;
			// Leitungen Zelle 10/11 und 11/12
			case 9:
			case 10:
			case 11:
				openwire[i] = getDifference(((pullup[i*2+7] << 8) + pullup[i*2+6]), ((pulldown[i*2+7] << 8) + pulldown[i*2+6]));
				break;
			case 12:
				openwire[i] = ((pullup[29] << 8) + pullup[28]);
				break;
			default:
				break;
		}
	}

	// Schleife zum Pruefen der Daten
	for (uint8_t i = 1; i < 12; i++)
	{
		// Vergleiche Messdaten mit Threshold
		if (openwire[i] > OPENWIRE_THRESHOLD)
		{
			cell[0] |= (1 << i);											// Wenn Threshold ueberschritten, Offene Leitung
		}
	}

	// Offene Leitung erste Zelle messen
	if (openwire[0] == 0)
	{
		cell[0] |= (1 << 0);												// Unterste Leitung Offen
	}

	// Offene Leitung letzte Zelle messen
	if (openwire[12] == 0)
	{
		cell[0] |= (1 << 12);												// Oberste Leitung offen
	}

	// Wenn offene Leitung vorhanden
	if (cell[0] != 0)
	{
		return 1;															// Open Wire nicht OK
	}

	return 0;																// Open Wire OK
}
//----------------------------------------------------------------------

// LTC6811 Polling Daten
//----------------------------------------------------------------------
uint16_t ltc6811_poll(void)
{
	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Aufruf von Polling LTC6811.\n");
#endif

	// PEC berechnen, Anhand Command
	uint16_t counter = 0, pec;												// Counter fuer Timeout, pec = Zwischenspeicher 16-Bit Command
	uint8_t finished = 0, current_time = 0;									// Finish fuer Uebertragung abgeschlossen, Zeit aus HAL_SPI_Receive
	uint8_t cmd[4];															// Zwischenspeicher Command + Pec CRC
	pec = peccommand(PLADC);

	// Verzoegerungszeit zum wecken des IsoSPI
	IsoSPI_wakeup();

	// Command in cmd abspeichern
	cmd[0] = ((PLADC >> 8) & 0x07);
	cmd[1] = (PLADC & 0xFF);
	cmd[2] = ((pec >> 8) & 0xFF);
	cmd[3] = (pec & 0xFE);

	// ISOCS einschalten
	ISOCS_ENABLE();

	// Command uebertragen
	HAL_SPI_Transmit(&hspi4, cmd, 4, 100);

	// Warten das alle LTC6811 fertig mit der Conversation sind
	while ((counter < 20000) && (finished == 0))
	{
		current_time = HAL_SPI_Receive(&hspi4, (uint8_t*) 0xFF, 1, 100);

		if (current_time > 0)
		{
			finished = 1;
		}
		else
		{
			counter++;
		}
	}

	// ISOCS ausschalten
	ISOCS_DISABLE();
	// Ende der Uebertragung

	// Debug Nachricht
#ifdef DEBUG_LTC6811
	ITM_SendString("Counter Wert auslesen:\t");
	ITM_SendNumber(counter);
	ITM_SendChar('\n');
#endif

	return(counter);
}
//----------------------------------------------------------------------
