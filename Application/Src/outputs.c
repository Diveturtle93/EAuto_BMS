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
#include "BatteriemanagementSystem.h"
//----------------------------------------------------------------------

// Variablen einbinden
//----------------------------------------------------------------------
system_out_tag system_out;																			// Variable fuer Systemausgaenge definieren
highcurrent_out_tag highcurrent_out;																// Variable fuer Highcurrentausgaenge definieren
leuchten_out_tag leuchten_out;																		// Variable fuer Leuchtenausgaenge definieren
komfort_out_tag komfort_out;																		// Variable fuer Komfortausgaenge definieren
//----------------------------------------------------------------------

// Initialisiere alle Ausgangsstrukturen auf default Werte
//----------------------------------------------------------------------
void init_outputs (void)
{
	// Schreibe alle Variablen auf Null
	system_out.systemoutput = SYSTEM_OUTPUT;														// Alle System Ausgaenge auf null setzen
	highcurrent_out.high_out = HIGH_OUTPUT;															// Alle Hochstrom Ausgaenge auf null setzen
	leuchten_out.ledoutput = LED_OUTPUT;															// Alle Leuchten Ausgaenge auf null setzen
	komfort_out.komfortoutput = KOMFORT_OUTPUT;														// Alle Komfort Ausgaenge auf null setzen
}
//----------------------------------------------------------------------

// Schreibe alle Ausgaenge auf default Werte
//----------------------------------------------------------------------
void writeall_outputs (void)
{
	// Schreibe System Ausgaenge
	HAL_GPIO_WritePin(AMS_LIMIT_GPIO_Port, AMS_LIMIT_Pin, system_out.AmsLimit);						// Batteriemanagement-System Strom limitiert
	HAL_GPIO_WritePin(IMD_OK_OUT_GPIO_Port, IMD_OK_OUT_Pin, system_out.ImdOK);						// Isolationswaechter OK
	HAL_GPIO_WritePin(AMS_OK_GPIO_Port, AMS_OK_Pin, system_out.AmsOK);								// Batteriemanagement-System OK
	HAL_GPIO_WritePin(FREIGABE_GPIO_Port, FREIGABE_Pin, system_out.Freigabe);						// Freigabe, Run, Fahren möglich
	HAL_GPIO_WritePin(RECUPERATION_GPIO_Port, RECUPERATION_Pin, system_out.Recuperation);			// Rekuperation aktivieren
	HAL_GPIO_WritePin(HV_P_GPIO_Port, HV_P_Pin, system_out.HV_P);									// Ausgang HV-Schuetz Plus
	HAL_GPIO_WritePin(HV_N_GPIO_Port, HV_N_Pin, system_out.HV_N);									// Ausgang HV-Schuetz Minus
	HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, system_out.PowerOn);						// Selbsthaltung DCDC-Wandler Motorsteuergeraet

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
	HAL_GPIO_WritePin(AKKU_LED_GPIO_Port, AKKU_LED_Pin, leuchten_out.AkkuErrorLed);					// Akku LED Kombiinstrument
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);							// Rote LED Platine
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);					// Gruene LED Platine
	HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, leuchten_out.BlueLed);						// Blaue LED Platine

	// Schreibe Komfortausgaenge
	HAL_GPIO_WritePin(TRIGGER_CURRENT_GPIO_Port, TRIGGER_CURRENT_Pin, komfort_out.TriggerOut);		// Stromsensor Triggern, mehr Infos
//	HAL_GPIO_WritePin(ISOSPI_EN_GPIO_Port, ISOSPI_EN_Pin, komfort_out.IsoSPI_EN);					// IsoSPI einschalten
}
//----------------------------------------------------------------------

// Schreibe alle LED-Ausgaenge auf default Werte
//----------------------------------------------------------------------
void writeled_outputs (void)
{
	leuchten_out.ledoutput = 0;

	// Schreibe Leuchtdioden Ausgaenge
	HAL_GPIO_WritePin(INLET_RED_GPIO_Port, INLET_RED_Pin, leuchten_out.InletRed);					// Red Inlet LED
	HAL_GPIO_WritePin(INLET_GREEN_GPIO_Port, INLET_GREEN_Pin, leuchten_out.InletGreen);				// Green Inlet LED
	HAL_GPIO_WritePin(AKKU_LED_GPIO_Port, AKKU_LED_Pin, leuchten_out.AkkuErrorLed);					// Akku LED Kombiinstrument
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);							// Rote LED Platine
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);					// Gruene LED Platine
	HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, leuchten_out.BlueLed);						// Blaue LED Platine
}
//----------------------------------------------------------------------

// Teste Platinen LEDs
//----------------------------------------------------------------------
void testPCB_Leds (void)
{
	// Leds Testen
    HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_SET);								// Blaue LED Platine setzen
    HAL_Delay(LED_TEST_TIME);
    HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_RESET);							// Blaue LED Platine zuruecksetzen
    HAL_Delay(LED_TEST_TIME);
    HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_SET);							// Gruene LED Platine setzen
    HAL_Delay(LED_TEST_TIME);
    HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, GPIO_PIN_RESET);							// Gruene LED Platine zuruecksetzen
    HAL_Delay(LED_TEST_TIME);
    HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_SET);								// Rote LED Platine setzen
    HAL_Delay(LED_TEST_TIME);
    HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, GPIO_PIN_RESET);								// Rote LED Platine zuruecksetzen
    HAL_Delay(LED_TEST_TIME);
}
//----------------------------------------------------------------------

// Teste alle externen LEDs, Inlet
//----------------------------------------------------------------------
void testInletLeds (void)
{
	// Leds Testen
	HAL_GPIO_WritePin(INLET_RED_GPIO_Port, INLET_RED_Pin, GPIO_PIN_SET);							// Red Inlet LED setzen
	HAL_Delay(LED_TEST_TIME);
	HAL_GPIO_WritePin(INLET_RED_GPIO_Port, INLET_RED_Pin, GPIO_PIN_RESET);							// Red Inlet LED zuruecksetzen
	HAL_Delay(LED_TEST_TIME);
	HAL_GPIO_WritePin(INLET_GREEN_GPIO_Port, INLET_GREEN_Pin, GPIO_PIN_SET);						// Green Inlet LED setzen
	HAL_Delay(LED_TEST_TIME);
	HAL_GPIO_WritePin(INLET_GREEN_GPIO_Port, INLET_GREEN_Pin, GPIO_PIN_RESET);						// Green Inlet LED zuruecksetzen
	HAL_Delay(LED_TEST_TIME);
}
//----------------------------------------------------------------------

// Teste Cockpit LEDs
void testCockpitLeds (void)
{
	HAL_GPIO_WritePin(AKKU_LED_GPIO_Port, AKKU_LED_Pin, GPIO_PIN_SET);								// Akku LED Kombiinstrument setzen, Ladekontrollleuchte an
	HAL_Delay(LED_TEST_TIME);
	HAL_GPIO_WritePin(AKKU_LED_GPIO_Port, AKKU_LED_Pin, GPIO_PIN_RESET);							// Akku LED Kombiinstrument zuruecksetzen, Ladekontrollleuchte aus
	HAL_Delay(LED_TEST_TIME);
}

// Ladekontroll LED setzen
//----------------------------------------------------------------------
void setLadekontrolle (void)
{
	// Status Ladekontrolle setzen
	leuchten_out.AkkuErrorLed = 1;

	// Ladekontrolle im Cockpit setzen
	HAL_GPIO_WritePin(AKKU_LED_GPIO_Port, AKKU_LED_Pin, leuchten_out.AkkuErrorLed);					// Akku LED Kombiinstrument setzen
}
//----------------------------------------------------------------------

// Ladekontroll LED zuruecksetzen
//----------------------------------------------------------------------
void resetLadekontrolle (void)
{
	// Status Ladekontrolle zuruecksetzen
	leuchten_out.AkkuErrorLed = 0;

	// Ladekontrolle im Cockpit zuruecksetzen
	HAL_GPIO_WritePin(AKKU_LED_GPIO_Port, AKKU_LED_Pin, leuchten_out.AkkuErrorLed);					// Akku LED Kombiinstrument zuruecksetzen
}
//----------------------------------------------------------------------

// Selbsterhaltung einschalten
//----------------------------------------------------------------------
void setPowerOn (void)
{
	// Status PowerOn setzen
	system_out.PowerOn = 1;

	// Selbsterhaltung einschalten
	HAL_GPIO_WritePin(POWER_ON_GPIO_Port, POWER_ON_Pin, system_out.PowerOn);						// BMS bleibt aktiv bei auschalten von KL15
}
//----------------------------------------------------------------------
