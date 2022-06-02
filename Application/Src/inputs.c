//----------------------------------------------------------------------
// Titel	:	Inputs.c
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
#include "inputs.h"
//----------------------------------------------------------------------

// Variablen einbinden
//----------------------------------------------------------------------
system_input_tag system_in;													// Variable fuer Systemeingaenge definieren
sdc_in_tag sdc_in;															// Variable fuer SDC-Eingaenge definieren
komfort_in_tag komfort_in;													// Variable fuer Komforteingaenge definieren
//----------------------------------------------------------------------

// Lese alle Eingaenge
//----------------------------------------------------------------------
void readall_inputs(void)
{
	// Systemeingaenge einlesen
	system_in.IMD_PWM = HAL_GPIO_ReadPin(IMD_PWM_GPIO_Port, IMD_PWM_Pin);						// Eingang IMD PWM
	system_in.KL15 = HAL_GPIO_ReadPin(KL15_GPIO_Port, KL15_Pin);								// Eingang Auto an
	system_in.Button1 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);						// Zusatzeingang Taster 1
	system_in.Button2 = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);						// Zusatzeingang Taster 2
	system_in.Crash = HAL_GPIO_ReadPin(CRASH_GPIO_Port, CRASH_Pin);								// Crash Eingang
	system_in.Wakeup = HAL_GPIO_ReadPin(HW_WAKE_GPIO_Port, HW_WAKE_Pin);						// Eingang Hardware Wakeup

	// SDC-Eingaenge einlesen
	sdc_in.IMD_OK_IN = HAL_GPIO_ReadPin(IMD_OK_IN_GPIO_Port, IMD_OK_IN_Pin);					// IMD OK, Akku
	sdc_in.HVIL = HAL_GPIO_ReadPin(SENSE_SDC_HVIL_GPIO_Port, SENSE_SDC_HVIL_Pin);				// Shutdown-Circuit HVIL, OK
	sdc_in.MotorSDC = HAL_GPIO_ReadPin(SENSE_SDC_MOTOR_GPIO_Port, SENSE_SDC_MOTOR_Pin);			// Shutdown-Circuit Akku, OK
	sdc_in.BTB_SDC = HAL_GPIO_ReadPin(SENSE_SDC_BTB_GPIO_Port, SENSE_SDC_BTB_Pin);				// Shutdown-Circuit Bamocar, OK
	sdc_in.PrechargeIn = HAL_GPIO_ReadPin(PRECHARGE_IN_GPIO_Port, PRECHARGE_IN_Pin);			// Eingang Precharge abgeschlossen

	// Komforteingaenge einlesen
	komfort_in.OVC = HAL_GPIO_ReadPin(OVC_SENSE_GPIO_Port, OVC_SENSE_Pin);						// Eingang Overcurrent erkannt
}
//----------------------------------------------------------------------
