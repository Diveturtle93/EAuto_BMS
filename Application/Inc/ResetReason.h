//----------------------------------------------------------------------
// Titel	:	ResetReason.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.05.2025
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	ResetReason
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_RESETREASON_H_
#define INC_RESETREASON_H_
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Definiere TypeDefines
//----------------------------------------------------------------------

// Reset Reasons definieren
//----------------------------------------------------------------------
typedef enum
{
	STARTUP = 0x00,															// Normal Startup
	IWDGRST1 = 0x01,														// Reset durch Independent Watchdog
	WWDGRST1 = 0x02,														// Reset durch Window Watchdog
	LPWRRST1 = 0x04,														// Reset durch CPU
	BORRST1 = 0x08,															// Reset durch Brown-Out
	OBLRST1 = 0x08,															// Reset durch Option Byte Loader
	PORRST1 = 0x10,															// Reset durch Power Down, Power On
	SFTRST1 = 0x20,															// Reset durch Software
	PINRST1 = 0x40,															// Reset durch Reset-Pin
} reset_reason;
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void printResetSource (reset_reason reset_flags);							// Schreibt Systemreset auf Uart
reset_reason readResetSource (void);										// Wertet Systemreset aus
//----------------------------------------------------------------------


#endif /* INC_RESETREASON_H_ */
//----------------------------------------------------------------------
