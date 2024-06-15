//----------------------------------------------------------------------
// Titel	:	SPI_resource.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	27.09.2020
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef SPI_RESOURCE_H_
#define SPI_RESOURCE_H_
//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Definiere ISO-SPI Enable Leitung, LTC6811
//----------------------------------------------------------------------
#define ISOSPI_ENABLE() (HAL_GPIO_WritePin(ISOSPI_EN_GPIO_Port, ISOSPI_EN_Pin, GPIO_PIN_SET))		// Iso SPI enable
#define ISOSPI_DISABLE() (HAL_GPIO_WritePin(ISOSPI_EN_GPIO_Port, ISOSPI_EN_Pin, GPIO_PIN_RESET))	// Iso SPI disable
//----------------------------------------------------------------------

// Definiere Chip-Select Leitung, AD8403
//----------------------------------------------------------------------
#define AD8403_CS_ENABLE() (HAL_GPIO_WritePin(POTI_CS_GPIO_Port, POTI_CS_Pin, GPIO_PIN_RESET))			// Chip-Select Leitung enable
#define AD8403_CS_DISABLE() (HAL_GPIO_WritePin(POTI_CS_GPIO_Port, POTI_CS_Pin, GPIO_PIN_SET))			// Chip-Select Leitung disable
//----------------------------------------------------------------------

// Definiere RS Leitung, AD8403
//----------------------------------------------------------------------
#define AD8403_RS_ENABLE() (HAL_GPIO_WritePin(POTI_RS_GPIO_Port, POTI_RS_Pin, GPIO_PIN_SET))			// Reset-Select Leitung enable
#define AD8403_RS_DISABLE() (HAL_GPIO_WritePin(POTI_RS_GPIO_Port, POTI_RS_Pin, GPIO_PIN_RESET))			// Reset-Select Leitung disable
//----------------------------------------------------------------------

// Definiere Shutdown Leitung, AD8403
//----------------------------------------------------------------------
#define AD8403_SHDN_ENABLE() (HAL_GPIO_WritePin(POTI_SHDN_GPIO_Port, POTI_SHDN_Pin, GPIO_PIN_SET))		// Shutdown Leitung enable
#define AD8403_SHDN_DISABLE() (HAL_GPIO_WritePin(POTI_SHDN_GPIO_Port, POTI_SHDN_Pin, GPIO_PIN_RESET))	// Shutdown Leitung disable
//----------------------------------------------------------------------

#endif /* INC_SPI_RESOURCE_H_ */
//----------------------------------------------------------------------
