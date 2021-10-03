//----------------------------------------------------------------------
// Titel	:	SystemInfo.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	Batteriemanagement-System
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef SYSTEMINFO_H_
#define SYSTEMINFO_H_
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------
#include <inttypes.h>
//----------------------------------------------------------------------

// Reset Reasons definieren
//----------------------------------------------------------------------
typedef enum {
	STARTUP = 0x00,
	IWDG1 = 0x01,
	WWDG1 = 0x02,
	CPURST1 = 0x04,
	BORST1 = 0x08,
	PORST1 = 0x10,
	SFTRST1 = 0x20,
	PINRST1 = 0x40,
	RMVF1 = 0x80,
} reset_reason;
//----------------------------------------------------------------------

// Build Daten definieren
//----------------------------------------------------------------------
#ifndef BUILD_DATE
#define BUILD_DATE			__DATE__									// Build Datum speichern wenn noch nicht definiert
#endif

#ifndef BUILD_TIME
#define BUILD_TIME			__TIME__									// Build Zeit speichern wenn noch nicht definiert
#endif
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void collectSystemInfo(void);											// Sammelt Systeminformationen, Schreibt diese auf Uart
reset_reason readResetSource(void);										// Wertet Systemreset aus
void printResetSource(reset_reason reset_flags);						// Schreibt Systemreset auf Uart
void collectHardwareInfo(void);											// Sammle Hardware Informationen
void collectSoftwareInfo(void);											// Sammle Software Informationen
void collectMiddlewareInfo(void);										// Sammle Middleware Informationen
void collectGitcounts(void);											// Sammle Git Count Informationen
//----------------------------------------------------------------------

#endif /* INC_SYSTEMINFO_H_ */
//----------------------------------------------------------------------
