//----------------------------------------------------------------------
// Titel	:	Outputs.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	31.03.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
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
#include "outputs.h"
//----------------------------------------------------------------------

// Initialisiere alle Ausgangsstrukturen auf default Werte
//----------------------------------------------------------------------
void init_outputs(void)
{
	// Schreibe alle Variablen auf Standart setzen
	system_out.systemoutput = SYSTEM_OUTPUT;														// Alle System Ausgaenge auf null setzen
	highcurrent_out.high_out = HIGH_OUTPUT;															// Alle Hochstrom Ausgaenge auf null setzen
	leuchten_out.ledoutput = LED_OUTPUT;															// Alle Leuchten Ausgaenge auf null setzen
	komfort_out.komfortoutput = KOMFORT_OUTPUT;														// Alle Komfort Ausgaenge auf null setzen

	// Alle Ausgaenge setzen
	writeall_outputs();																				// Auf default setzen
}
//----------------------------------------------------------------------

// Schreibe alle Ausgaenge auf default Werte
//----------------------------------------------------------------------
void writeall_outputs(void)
{
	// Schreibe System Ausgaenge
	HAL_GPIO_WritePin(AMS_LIMIT_GPIO_Port, AMS_LIMIT_Pin, system_out.AmsLimit);						// Batteriemanagement-System Strom limitiert
	HAL_GPIO_WritePin(IMD_OK_OUT_GPIO_Port, IMD_OK_OUT_Pin, system_out.ImdOK);						// Isolationswaechter OK
	HAL_GPIO_WritePin(AMS_OK_GPIO_Port, AMS_OK_Pin, system_out.AmsOK);								// Batteriemanagement-System OK
	HAL_GPIO_WritePin(FREIGABE_GPIO_Port, FREIGABE_Pin, system_out.Freigabe);						// Freigabe, Run, Fahren möglich
	HAL_GPIO_WritePin(RECUPERATION_GPIO_Port, RECUPERATION_Pin, system_out.Recuperation);			// Rekuperation aktivieren
	HAL_GPIO_WritePin(HV_P_GPIO_Port, HV_P_Pin, system_out.HV_P);									// Ausgang HV-Schuetz Plus
	HAL_GPIO_WritePin(HV_N_GPIO_Port, HV_N_Pin, system_out.HV_N);									// Ausgang HV-Schuetz Minus
	HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, system_out.Power_On);						// Selbsthaltung DCDC-Wandler Motorsteuergeraet

	// Schreibe Hochstromfaehige Ausgaenge
	HAL_GPIO_WritePin(DIGITAL1_GPIO_Port, DIGITAL1_Pin, highcurrent_out.Digital1);					// Digitaler Ausgang 1
	HAL_GPIO_WritePin(DIGITAL2_GPIO_Port, DIGITAL2_Pin, highcurrent_out.Digital2);					// Digitaler Ausgang 2
	HAL_GPIO_WritePin(PRECHARGE_OUT_GPIO_Port, PRECHARGE_OUT_Pin, highcurrent_out.PrechargeOut);	// Ausgang Precharge starten
	HAL_GPIO_WritePin(HV_M_GPIO_Port, HV_M_Pin, highcurrent_out.HV_M);								// Ausgang HV-Schuetz Mitte
	HAL_GPIO_WritePin(HV_Charger_GPIO_Port, HV_Charger_Pin, highcurrent_out.HV_CHG);				// Ausgang HV-Schuetz Ladegeraet
	HAL_GPIO_WritePin(HEATER1_GPIO_Port, HEATER1_Pin, highcurrent_out.Heater1);						// Ausgang Heizung 1
	HAL_GPIO_WritePin(HEATER2_GPIO_Port, HEATER2_Pin, highcurrent_out.Heater2);						// Ausgang Heizung 2

	// Schreibe Leuchtdioden Ausgaenge
	HAL_GPIO_WritePin(INLET_RED_GPIO_Port, INLET_RED_Pin, leuchten_out.InletRed);					// Red Inlet LED
	HAL_GPIO_WritePin(INLET_GREEN_GPIO_Port, INLET_GREEN_Pin, leuchten_out.InletGreen);				// Green Inlet LED
	HAL_GPIO_WritePin(AKKU_LED_GPIO_Port, AKKU_LED_Pin, leuchten_out.AkkuLed);						// Akku LED Kombiinstrument
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);							// Rote LED Platine
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);					// Gruene LED Platine
	HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, leuchten_out.BlueLed);						// Blaue LED Platine

	// SChreibe Komfortausgaenge
	HAL_GPIO_WritePin(TRIGGER_CURRENT_GPIO_Port, TRIGGER_CURRENT_Pin, komfort_out.TriggerOut);		// Stromsensor Triggern, mehr Infos
}
//----------------------------------------------------------------------

// Selbsterhalten einschalten / DCDC-Wandler einschalten
//----------------------------------------------------------------------
void power_on(void)
{
	system_out.Power_On = 1;																		// Power On Variable setzen
	HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, system_out.Power_On);						// Selbsthaltung DCDC-Wandler Motorsteuergeraet
}
//----------------------------------------------------------------------
