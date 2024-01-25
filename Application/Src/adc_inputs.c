//----------------------------------------------------------------------
// Titel	:	adc_inputs.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	14.08.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Motorsteuergeraet
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "adc.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "adc_inputs.h"
#include "BatteriemanagementSystem.h"
//----------------------------------------------------------------------

// STM32 Temperatur einlesen
//----------------------------------------------------------------------
uint16_t ADC_STMTemperatur (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;								// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// PCB Temperatur einlesen
//----------------------------------------------------------------------
uint16_t ADC_PCBTemperatur (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_7;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Spannung KL15 einlesen
//----------------------------------------------------------------------
uint16_t ADC_KL15 (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_7;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Spannung KL30 fuer Relais einlesen
//----------------------------------------------------------------------
uint16_t ADC_KL30_Relais (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_7;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Temperatur 1 einlesen
//----------------------------------------------------------------------
uint16_t ADC_Temp1 (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_3;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Temperatur 2 einlesen
//----------------------------------------------------------------------
uint16_t ADC_Temp2 (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_4;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Temperatur 3 einlesen
//----------------------------------------------------------------------
uint16_t ADC_Temp3 (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_5;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------

// Temperatur 4 einlesen
//----------------------------------------------------------------------
uint16_t ADC_Temp4 (void)
{
	// Temporaere Variable anlegen
	uint16_t ADC_Data = 0;

	// ADC1 konfigurieren
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = ADC_CHANNEL_6;										// ADC Kanal einstellen
	sConfig.Rank = 1;														// Rang einstellen
	sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;							// ADC Sampletime einstellen
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)					// Wenn Config nicht Ok ist
	{
		Error_Handler();													// Fehler HAL ausgeben
	}

	// ADC Starten, Wert einlesen und ADC Stoppen
	HAL_ADC_Start(&hadc1);													// ADC starten
	if(HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)					// Wenn ADC funktioniert
	{
		// ADC Wert holen
		ADC_Data = HAL_ADC_GetValue(&hadc1);
	}
	else																	// Falls ADC nicht funktioniert
	{
		// Software Error ausgeben
		software_error(ERROR_ADC);
	}
	HAL_ADC_Stop(&hadc1);													// ADC stoppen

	//ADC Wert zurueck geben
	return ADC_Data;
}
//----------------------------------------------------------------------
