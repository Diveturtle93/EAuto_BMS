//----------------------------------------------------------------------
// Titel	:	imd.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	29.08.2021
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
#include "imd.h"
#include "BasicUart.h"
#include "inputs.h"
#include "outputs.h"
//----------------------------------------------------------------------

// IMD Status einlesen
//----------------------------------------------------------------------
void imd_status(void)
{
	// Einlesen von IMD Ok Pin
	sdc_in.IMD_OK_IN = HAL_GPIO_ReadPin(IMD_OK_IN_GPIO_Port, IMD_OK_IN_Pin);		// IMD OK einlesen

	// Abfrage ob IMD Ok ist
	if(sdc_in.IMD_OK_IN == 1)
	{
		// Ausgabe IMD OK kommend BMS
		system_out.ImdOK = 1;
		HAL_GPIO_WritePin(IMD_OK_OUT_GPIO_Port, IMD_OK_OUT_Pin, system_out.ImdOK);	// IMD Status von BMS ausgeben
	}

	// IMD ist nicht OK
	if (sdc_in.IMD_OK_IN != 1)
	{
#ifdef DEBUG_IMD
		// Ausgabe Frequenz
		uartTransmit("Frequenz: \t", 11);
		uartTransmitNumber(imd.Frequency, 10);
		uartTransmit("\n", 1);

		// Ausgabe DutyCycle
		uartTransmit("DutyCycle: \t", 12);
		uartTransmitNumber(imd.DutyCycle, 10);
		uartTransmit("\n", 1);
#endif

		// IMD PWM abfragen
		switch (imd.Frequency)
		{
			case 0:																	// Case 0 Hz
				// PWM Pin einlesen
				system_in.IMD_PWM = HAL_GPIO_ReadPin(IMD_PWM_GPIO_Port, IMD_PWM_Pin);

				// Wenn IMD 1 ist
				if (system_in.IMD_PWM == 1)
				{
					// IMD Status speichern
					system_in.IMD_PWM_STATUS = IMD_KURZSCHLUSS_KL15;				// Kurzschluss von HV nach Pluspol
					imd.PWM_STATUS = IMD_KURZSCHLUSS_KL15;							// Kurzschluss von HV nach Pluspol
				}
				// Wenn IMD 0 ist
				else
				{
					// IMD Status speichern
					system_in.IMD_PWM_STATUS = IMD_KURZSCHLUSS_GND;					// Kurzschluss von HV nach Masse
					imd.PWM_STATUS = IMD_KURZSCHLUSS_GND;							// Kurzschluss von HV nach Masse
				}
				break;

			case 10:																// Case 10 Hz
				// IMD Status speichern
				system_in.IMD_PWM_STATUS = IMD_NORMAL;								// IMD funktioniert normal
				imd.PWM_STATUS = IMD_NORMAL;										// IMD funktioniert normal

				// DutyCycle abfragen
				if (imd.DutyCycle > 5 && imd.DutyCycle < 95)						// IMD PWM
				{
					// Widerstand berechnen
					imd.Resistanc = 90 * 1200 / (imd.DutyCycle - 5) - 1200;			// Angabe in kOhm

#ifdef DEBUG_IMD
					// Ausgabe Widerstandswert
					uartTransmitNumber(imd.Resistanc, 10);
#endif
				}
				// Falls DutyCycle nicht im Wertebereich ist
				else																// IMD Invalid
				{
					// IMD Status speichern
					system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;						// Fehlerausgabe
					imd.PWM_STATUS = IMD_FREQ_ERROR;								// Fehlerausgabe
				}
				break;

			case 20:																// Case 20 Hz
				// DutyCycle abfragen
				if (imd.DutyCycle > 5 && imd.DutyCycle < 95)						// IMD PWM
				{
					// Widerstand berechnen
					imd.Resistanc = 90 * 1200 / (imd.DutyCycle - 5) - 1200;			// Angabe in kOhm

#ifdef DEBUG_IMD
					// Ausgabe Widerstandswert
					uartTransmitNumber(imd.Resistanc, 10);
#endif
				}
				// Falls DutyCycle nicht im Wertebereich ist
				else																// IMD Invalid
				{
					// IMD Status speichern
					system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;						// Fehlerausgabe
					imd.PWM_STATUS = IMD_FREQ_ERROR;								// Fehlerausgabe
				}
				break;

			case 30:																// Case 30 Hz
				// IMD Status speichern
				system_in.IMD_PWM_STATUS = IMD_SCHNELLSTART;						// Schnellstartmessung
				imd.PWM_STATUS = IMD_SCHNELLSTART;									// Schnellstartmessung

				// DutyCycle abfragen
				if (imd.DutyCycle > 5 && imd.DutyCycle < 11)						// IMD Gut
				{

				}
				else if (imd.DutyCycle > 89 && imd.DutyCycle < 95)					// IMD Schlecht
				{

				}
				// Falls DutyCycle nicht im Wertebereich ist
				else																// IMD Invalid
				{
					// IMD Status speichern
					system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;						// Fehlerausgabe
					imd.PWM_STATUS = IMD_FREQ_ERROR;								// Fehlerausgabe
				}
				break;

			case 40:																// Case 40 Hz
				// IMD Status speichern
				system_in.IMD_PWM_STATUS = IMD_GERAETEFEHLER;						// Geraetefehler
				imd.PWM_STATUS = IMD_GERAETEFEHLER;									// Geraetefehler

				// DutyCyle abfragen
				if (imd.DutyCycle > 47 && imd.DutyCycle < 53)						// IMD PWM
				{

				}
				// Falls DutyCycle nicht im Wertebereich ist
				else																// IMD Invalid
				{
					// IMD Status speichern
					system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;						// Fehlerausgabe
					imd.PWM_STATUS = IMD_FREQ_ERROR;								// Fehlerausgabe
				}
				break;

			case 50:																// Case 50 Hz
				// IMD Status speichern
				system_in.IMD_PWM_STATUS = IMD_ANSCHLUSSFEHLER_ERDE;				// Anschluss an Erde festgestellt
				imd.PWM_STATUS = IMD_ANSCHLUSSFEHLER_ERDE;							// Anschluss an Erde festgestellt

				// DutyCycle abfragen
				if (imd.DutyCycle > 47 && imd.DutyCycle < 53)						// IMD PWM
				{

				}
				// Fall DutyCycle nicht im Wertebereich ist
				else																// IMD Invalid
				{
					// IMD Status speichern
					system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;						// Fehlerausgabe
					imd.PWM_STATUS = IMD_FREQ_ERROR;								// Fehlerausgabe
				}
				break;

			default:																// Case Default Fehler
				// IMD Status speichern
				system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;							// Fehlerausgabe
				imd.PWM_STATUS = IMD_FREQ_ERROR;									// Fehlerausgabe
				break;
		}
	}
	else
	{
		switch (imd.Frequency)
		{
			case 10:																// Case 10 Hz
				// IMD Status speichern
				system_in.IMD_PWM_STATUS = IMD_NORMAL;								// IMD funktioniert normal
				imd.PWM_STATUS = IMD_NORMAL;										// IMD funktioniert normal

				// DutyCycle abfragen
				if (imd.DutyCycle > 5 && imd.DutyCycle < 95)						// IMD PWM
				{
					// Widerstand berechnen
					imd.Resistanc = 90 * 1200 / (imd.DutyCycle - 5) - 1200;			// Angabe in kOhm

#ifdef DEBUG_IMD
					// Ausgabe Widerstandswert
					uartTransmitNumber(imd.Resistanc, 10);
#endif
				}
				// Falls DutyCycle nicht im Wertebereich ist
				else																// IMD Invalid
				{
					// IMD Status speichern
					system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;						// Fehlerausgabe
					imd.PWM_STATUS = IMD_FREQ_ERROR;								// Fehlerausgabe
				}
				break;

			case 20:
				// IMD Status speichern
				system_in.IMD_PWM_STATUS = IMD_UNTERSPANNUNG;						// Unterspannung an HV erkannt
				imd.PWM_STATUS = IMD_UNTERSPANNUNG;									// Unterspannung an HV erkannt

				// DutyCycle abfragen
				if (imd.DutyCycle > 5 && imd.DutyCycle < 95)						// IMD PWM
				{
					// Widerstand berechnen
					imd.Resistanc = 90 * 1200 / (imd.DutyCycle - 5) - 1200;			// Angabe in kOhm

#ifdef DEBUG_IMD
					// Ausgabe Widerstandswert
					uartTransmitNumber(imd.Resistanc, 10);
#endif
				}
				// Falls DutyCycle nicht im Wertebereich ist
				else																// IMD Invalid
				{
					// IMD Status speichern
					system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;						// Fehlerausgabe
					imd.PWM_STATUS = IMD_FREQ_ERROR;								// Fehlerausgabe
				}
				break;

			default:																// Case Default Fehler
				// IMD Status speichern
				system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;							// Fehlerausgabe
				imd.PWM_STATUS = IMD_FREQ_ERROR;									// Fehlerausgabe
				break;
		}

		// Ausgabe IMD nicht OK kommend BMS
		system_out.ImdOK = 0;
		HAL_GPIO_WritePin(IMD_OK_OUT_GPIO_Port, IMD_OK_OUT_Pin, system_out.ImdOK);	// IMD Status von BMS ausgeben
	}
}
//----------------------------------------------------------------------
