//----------------------------------------------------------------------
// Titel	:	SPI_resource.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	27.09.2020
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------


#ifndef SPI_RESOURCE_H_
#define SPI_RESOURCE_H_

#include "main.h"


// Definiere Chip-Select Leitung
//----------------------------------------------------------------------
#define CS_ENABLE() (HAL_GPIO_WritePin(ISOSPI_CS_GPIO_Port, ISOSPI_CS_Pin, GPIO_PIN_RESET))		// Chip-Select enable
#define CS_DISABLE() (HAL_GPIO_WritePin(ISOSPI_CS_GPIO_Port, ISOSPI_CS_Pin, GPIO_PIN_SET))		// Chip-Select disable
//----------------------------------------------------------------------

#endif
