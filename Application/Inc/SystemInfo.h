//----------------------------------------------------------------------
// Titel	:	SystemInfo.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	SystemInfo
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef SYSTEMINFO_H_
#define SYSTEMINFO_H_
//----------------------------------------------------------------------

// Build Daten definieren
//----------------------------------------------------------------------
#ifndef BUILD_DATE
#define BUILD_DATE			__DATE__										// Build Datum speichern wenn noch nicht definiert
#endif

#ifndef BUILD_TIME
#define BUILD_TIME			__TIME__										// Build Zeit speichern wenn noch nicht definiert
#endif
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void collectSystemInfo (void);												// Sammelt Systeminformationen, Schreibt diese auf Uart
void collectHardwareInfo (void);											// Sammle Hardware Informationen
void collectSoftwareInfo (void);											// Sammle Software Informationen
void collectMiddlewareInfo (void);											// Sammle Middleware Informationen
void collectGitcounts (void);												// Sammle Git Count Informationen
//----------------------------------------------------------------------

#endif /* INC_SYSTEMINFO_H_ */
//----------------------------------------------------------------------
