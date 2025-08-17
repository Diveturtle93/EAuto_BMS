//----------------------------------------------------------------------
// Titel	:	DWT.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	12.06.2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Data Watchpoint Trigger
//----------------------------------------------------------------------


// Beispiel:
/*
	uint32_t DWT_count = 0, DWT_count1 = 0, DWT_count2 = 0, test = 0;

	// Data Watchpoint Trigger initialisieren
	DWT_Init();

	// Data Watchpoint Trigger auslesen und abspeichern
	DWT_count = DWT_CycCounterRead();
	test = DWT_count;

	uartTransmitNumber(test, 10);
  	uartTransmit("\n", 1);
  	DWT_CycCounterDis();													// Zaehler deaktivieren
*/

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "DWT.h"
//----------------------------------------------------------------------

// DWT-Einheit aktivieren
//----------------------------------------------------------------------
void DWT_Init(void)
{
	ITM -> LAR = 0xC5ACCE55;
//	ITM -> TCR |= ITM_TCR_DWTENA_Msk;
	DWT_Enable();
//	ITM -> LAR = 0xC5ACCE55;
	DWT_CycCounterClear();
	DWT_CycCounterEn();
}
//----------------------------------------------------------------------

// DWT-Einheit aktivieren
//----------------------------------------------------------------------
void DWT_Enable(void)
{
	CoreDebug -> DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;						// 0x01000000
}
//----------------------------------------------------------------------

// DWT-Einheit deaktivieren
//----------------------------------------------------------------------
void DWT_Disable(void)
{
	CoreDebug -> DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk;						// ~0x01000000
}
//----------------------------------------------------------------------

//Schalte DWT ein
//----------------------------------------------------------------------
void DWT_CycCounterEn()
{
	DWT -> CTRL |= DWT_CTRL_CYCCNTENA_Msk;									// 0x00000001
}
//----------------------------------------------------------------------

// Schalte DWT aus
//----------------------------------------------------------------------
void DWT_CycCounterDis(void)
{
	DWT -> CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;									// ~0x00000001
}
//----------------------------------------------------------------------

// Lese DWT Zaehlerstand
//----------------------------------------------------------------------
uint32_t DWT_CycCounterRead(void)
{
	return DWT -> CYCCNT;
}
//----------------------------------------------------------------------

// Loesche DWT Zaehlerstand
//----------------------------------------------------------------------
void DWT_CycCounterClear(void)
{
	DWT -> CYCCNT = 0;
}
//----------------------------------------------------------------------
