//----------------------------------------------------------------------
// Titel	:	SystemInfo.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	16.01.2021
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	SystemInfo
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include-Dateien
//----------------------------------------------------------------------
#include "main.h"
#include "git.h"
#include "SystemInfo.h"
#include "BasicUart.h"
//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
//#include "cmsis_os.h"														//Collect Information from RTOS CMSIS LAYER
//#include "task.h"															//Collect Information from RTOS
//----------------------------------------------------------------------


// Collects hardware information from microcontroller and prints it
//----------------------------------------------------------------------
void collectHardwareInfo (void)
{
	#define STRING_STM_DEVICE_ID			"\nSTM32 Device ID:\t\t"
	#define STRING_STM_REVISION				"\nSTM32 Revision ID:\t\t"
	#define STRING_STM_FREQ					"\nSTM32 CPU-Freq:\t\t\t"
	#define STRING_STM_UUID					"\nSTM32 UUID:\t\t\t"

	uartTransmit(STRING_STM_DEVICE_ID, sizeof(STRING_STM_DEVICE_ID));
	uartTransmitNumber(HAL_GetDEVID(), 10);									// Mikrocontroller Typ

	uartTransmit(STRING_STM_REVISION, sizeof(STRING_STM_REVISION));

	switch(HAL_GetREVID())													// Mikrocontroller Revision
	{
		case 0x1001:
			uartTransmit("Z", 1);
			break;
		case 0x1003:
			uartTransmit("Y", 1);
			break;
		case 0x2001:
			uartTransmit("X", 1);
			break;
		default:
			uartTransmitNumber(HAL_GetREVID(), 10);
			break;
	}


	uartTransmit(STRING_STM_FREQ, sizeof(STRING_STM_FREQ));
	{
		uint32_t frequency = HAL_RCC_GetSysClockFreq();						// Systemfrequenz ausgeben
		frequency = frequency / 1000000;

		uartTransmitNumber(frequency, 10);
	}

	uartTransmit(" MHz", 4);


	uartTransmit("\n", 1);
	uartTransmit(STRING_STM_UUID, sizeof(STRING_STM_UUID));
	uartTransmitNumber(HAL_GetUIDw0(), 16);									// UID0 ausgeben

	uartTransmit(" ", 1);
	uartTransmitNumber(HAL_GetUIDw1(), 16);									// UID1 ausgeben

	uartTransmit(" ", 1);
	uartTransmitNumber(HAL_GetUIDw2(), 16);									// UID2 ausgeben

	uartTransmit("\n", 1);
}
//----------------------------------------------------------------------

// Collects Version information from Middleware and prints it
//----------------------------------------------------------------------
void collectMiddlewareInfo (void)
{
	#define STRING_CORTEX_CMSIS_VERSION		"\nCortex CMSIS Version:\t\t"
	#define STRING_STM_CMSIS_VERSION		"\nSTM32F7 CMSIS Version:\t\t"
	#define STRING_HAL_VERSION				"\nHAL Version:\t\t\t"
	#define STRING_RTOS_CMSIS_VERSION		"\nRTOS CMSIS Version:\t\t"
	#define STRING_RTOS_VERSION				"\nRTOS Version:\t\t\t"

	uartTransmit(STRING_CORTEX_CMSIS_VERSION, sizeof(STRING_CORTEX_CMSIS_VERSION));
	uartTransmitNumber(__CM_CMSIS_VERSION_MAIN, 10);						// Cortex CMSIS Version anzeigen, Main Version
	uartTransmit(".", 1);
	uartTransmitNumber(__CM_CMSIS_VERSION_SUB, 10);							// Cortex CMSIS Version anzeigen, Sub Version

	uartTransmit(STRING_STM_CMSIS_VERSION, sizeof(STRING_STM_CMSIS_VERSION));

#ifdef STM32F1
	uartTransmitNumber(__STM32F1_CMSIS_VERSION_MAIN, 10);					// CMSIS Version anzeigen, Main Version
	uartTransmit(".", 1);
	uartTransmitNumber(__STM32F1_CMSIS_VERSION_SUB1, 10);					// CMSIS Version anzeigen, Sub1 Version
	uartTransmit(".", 1);
	uartTransmitNumber(__STM32F1_CMSIS_VERSION_SUB2, 10);					// CMSIS Version anzeigen, Sub2 Version
	uartTransmit(".", 1);
	uartTransmitNumber(__STM32F1_CMSIS_VERSION_RC, 10);						// CMSIS Version anzeigen, Release candidate
#endif

#ifdef STM32F7
	uartTransmitNumber(__STM32F7_CMSIS_VERSION_MAIN, 10);					// CMSIS Version anzeigen, Main Version
	uartTransmit(".", 1);
	uartTransmitNumber(__STM32F7_CMSIS_VERSION_SUB1, 10);					// CMSIS Version anzeigen, Sub1 Version
	uartTransmit(".", 1);
	uartTransmitNumber(__STM32F7_CMSIS_VERSION_SUB2, 10);					// CMSIS Version anzeigen, Sub2 Version
#endif

#ifdef STM32G0
	uartTransmitNumber(__STM32G0_CMSIS_VERSION_MAIN, 10);					// CMSIS Version anzeigen, Main Version
	uartTransmit(".", 1);
	uartTransmitNumber(__STM32G0_CMSIS_VERSION_SUB1, 10);					// CMSIS Version anzeigen, Sub1 Version
	uartTransmit(".", 1);
	uartTransmitNumber(__STM32G0_CMSIS_VERSION_SUB2, 10);					// CMSIS Version anzeigen, Sub2 Version
	uartTransmit(".", 1);
	uartTransmitNumber(__STM32G0_CMSIS_VERSION_RC, 10);						// CMSIS Version anzeigen, Release candidate
#endif

	uartTransmit(STRING_HAL_VERSION, sizeof(STRING_HAL_VERSION));			// Hal Version anzeigen
	uartTransmitNumber((uint32_t)((HAL_GetHalVersion() >> 24) & 0xFF), 10);

	uartTransmit(".", 1);													// Hal Version anzeigen
	uartTransmitNumber((uint32_t)((HAL_GetHalVersion() >> 16) & 0xFF), 10);

	uartTransmit(".", 1);													// Hal Version anzeigen
	uartTransmitNumber((uint32_t)((HAL_GetHalVersion() >> 8) & 0xFF), 10);

	uartTransmit(".", 1);													// Hal Version anzeigen
	uartTransmitNumber((uint32_t)(HAL_GetHalVersion() & 0xFF), 10);

#ifdef INC_TASK_H
	uartTransmit(STRING_RTOS_CMSIS_VERSION, sizeof(STRING_RTOS_CMSIS_VERSION));
	uartTransmitNumber((osCMSIS >> 16), 10);								// FreeRTOS CMSIS Version anzeigen

	uartTransmit(".", 1);
	uartTransmitNumber((osCMSIS & 0xFFFF), 10);								// FreeRTOS CMSIS Version anzeigen


	uartTransmit(STRING_RTOS_VERSION , sizeof(STRING_RTOS_VERSION));
	uartTransmitNumber(tskKERNEL_VERSION_MAJOR, 10);						// FreeRTOS Kernel Version anzeigen

	uartTransmit(".", 1);
	uartTransmitNumber(tskKERNEL_VERSION_MINOR, 10);						// FreeRTOS Kernel Version anzeigen

	uartTransmit(".", 1);
	uartTransmitNumber(tskKERNEL_VERSION_BUILD, 10);						// FreeRTOS Kernel Version anzeigen
#endif

	uartTransmit("\n", 1);
}
//----------------------------------------------------------------------

// Collects Software information and prints it
//----------------------------------------------------------------------
void collectSoftwareInfo (void)
{
	#define STRING_BUILD_DATE				"\nBuild Date:\t\t\t"
	#define STRING_BUILD_TIME				"\nBuild Time:\t\t\t"
	#define STRING_GIT_BUILD_DATE			"\nGit Build Date:\t\t\t"
	#define STRING_GIT_BUILD_TIME			"\nGit Build Time:\t\t\t"
	#define STRING_GIT_COMMIT				"\nGit Commit:\t\t\t"
	#define STRING_GIT_BRANCH				"\nGit Branch:\t\t\t"
	#define STRING_GIT_HASH					"\nGit Hash:\t\t\t"
	#define STRING_GIT_TAGS					"\nGit Branch Tags:\t\t"
	#define STRING_GIT_LAST_TAG				"\nGit letzter Tags:\t\t"
	#define STRING_GIT_TAG_COMMIT			"\nGit Tags commit:\t\t"
	#define STRING_GIT_TAG_DIRTY			"\nGit Dirty commit:\t\t"

	uartTransmit(STRING_BUILD_DATE, sizeof(STRING_BUILD_DATE));
	uartTransmit(BUILD_DATE, sizeof(BUILD_DATE));							// Kompilierdatum anzeigen

	uartTransmit(STRING_BUILD_TIME, sizeof(STRING_BUILD_TIME));
	uartTransmit(BUILD_TIME, sizeof(BUILD_TIME));							// Kompilierzeit anzeigen

	uartTransmit("\n", 1);													// Leerzeile einfuegen

	uartTransmit(STRING_GIT_BUILD_DATE, sizeof(STRING_GIT_BUILD_DATE));
	uartTransmit(GIT_BUILD_DATE, sizeof(GIT_BUILD_DATE));					// Git Kompilierdatum anzeigen von git.h

	uartTransmit(STRING_GIT_BUILD_TIME, sizeof(STRING_GIT_BUILD_TIME));
	uartTransmit(GIT_BUILD_TIME, sizeof(GIT_BUILD_TIME));					// GIt Kompilierzeit anzeigen von git.h

	uartTransmit("\n", 1);													// Leerzeile einfuegen

	uartTransmit(STRING_GIT_COMMIT, sizeof(STRING_GIT_COMMIT));
	uartTransmit(GIT_COMMIT, sizeof(GIT_COMMIT));							// Git Commit anzeigen

	uartTransmit(STRING_GIT_BRANCH, sizeof(STRING_GIT_BRANCH));
	uartTransmit(GIT_BRANCH, sizeof(GIT_BRANCH));							// Git Branch anzeigen

	uartTransmit(STRING_GIT_HASH, sizeof(STRING_GIT_HASH));
	uartTransmit(GIT_HASH, sizeof(GIT_HASH));								// Git Hash anzeigen

	uartTransmit("\n", 1);													// Leerzeile einfuegen

	uartTransmit(STRING_GIT_TAGS, sizeof(STRING_GIT_TAGS));
	uartTransmit(GIT_TAGS, sizeof(GIT_TAGS));								// Git alle Tags des Branch anzeigen

	uartTransmit(STRING_GIT_LAST_TAG, sizeof(STRING_GIT_LAST_TAG));
	uartTransmit(GIT_LAST_TAG, sizeof(GIT_LAST_TAG));						// Git letzten Tags anzeigen

	uartTransmit(STRING_GIT_TAG_COMMIT, sizeof(STRING_GIT_TAG_COMMIT));
	uartTransmit(GIT_TAG_COMMIT, sizeof(GIT_TAG_COMMIT));					// Git Tags Commit anzeigen

	uartTransmit(STRING_GIT_TAG_DIRTY, sizeof(STRING_GIT_TAG_DIRTY));
	uartTransmit(GIT_TAG_DIRTY, sizeof(GIT_TAG_DIRTY));						// Git Dirty Commit anzeigen

	uartTransmit("\n", 1);													// Leerzeile einfuegen
}
//----------------------------------------------------------------------

// Collects Git count information and prints it
//----------------------------------------------------------------------
void collectGitcounts (void)
{
	#define STRING_GIT_TAG_DIRTY_COUNT		"\nGit Dirty count:\t\t"
	#define STRING_GIT_OVERALL_COMMIT_COUNT	"\nGit Overall count:\t\t"
	#define STRING_GIT_BRANCH_COMMIT_COUNT	"\nGit Branch commit count:\t"
	#define STRING_GIT_ACTIVE_BRANCHES		"\nGit active Branches:\t\t"
	#define STRING_GIT_TAG_COUNT			"\nGit Tags count:\t\t\t"

	uartTransmit(STRING_GIT_TAG_DIRTY_COUNT, sizeof(STRING_GIT_TAG_DIRTY_COUNT));
	uartTransmit(GIT_TAG_DIRTY_COUNT, sizeof(GIT_TAG_DIRTY_COUNT));			// Git zaehle Dirty commits nach letztem Tags und Anzahl anzeigen

	uartTransmit(STRING_GIT_OVERALL_COMMIT_COUNT, sizeof(STRING_GIT_OVERALL_COMMIT_COUNT));
	uartTransmit(GIT_OVERALL_COMMIT_COUNT, sizeof(GIT_OVERALL_COMMIT_COUNT));// Git alle Commits zaehlen und Anzahl anzeigen

	uartTransmit(STRING_GIT_BRANCH_COMMIT_COUNT, sizeof(STRING_GIT_BRANCH_COMMIT_COUNT));
	uartTransmit(GIT_BRANCH_COMMIT_COUNT, sizeof(GIT_BRANCH_COMMIT_COUNT));	// Git Branch Commits zaehken und Anzahl anzeigen

	uartTransmit(STRING_GIT_ACTIVE_BRANCHES, sizeof(STRING_GIT_ACTIVE_BRANCHES));
	uartTransmit(GIT_ACTIVE_BRANCHES, sizeof(GIT_ACTIVE_BRANCHES));			// Git aktive Branches zaehlen und Anzahl anzeigen

	uartTransmit(STRING_GIT_TAG_COUNT, sizeof(STRING_GIT_TAG_COUNT));
	uartTransmit(GIT_TAG_COUNT, sizeof(GIT_TAG_COUNT));						// Git Tags zaehlen und Anzahl anzeigen
}
//----------------------------------------------------------------------

// Collects Information from microcontroller and send to UART
//----------------------------------------------------------------------
void collectSystemInfo(void)
{
	#define STRING_HARDWARE_TITEL			"\n\t --Hardware--\n"
	#define STRING_MIDDLEWARE_TITEL			"\n\t --Middleware--\n"
	#define STRING_SOFTWARE_TITEL			"\n\t --Software--\n"
	#define STRING_GIT_COUNTS				"\n\t --Git counts--\n"

	uartTransmit(STRING_HARDWARE_TITEL, sizeof(STRING_HARDWARE_TITEL));
	collectHardwareInfo();													// Sammelt Hardware Informationen und gibt diese ueber Uart aus

	uartTransmit(STRING_SOFTWARE_TITEL, sizeof(STRING_SOFTWARE_TITEL));
	collectSoftwareInfo();													// Sammelt Software Informationen und gibt diese ueber Uart aus

	uartTransmit(STRING_MIDDLEWARE_TITEL, sizeof(STRING_MIDDLEWARE_TITEL));
	collectMiddlewareInfo();												// Sammelt Middleware Informationen und gibt diese ueber Uart aus

	uartTransmit(STRING_GIT_COUNTS, sizeof(STRING_GIT_COUNTS));
	collectGitcounts();														// Sammelt Git count Informationen und gibt diese ueber Uart aus

	uartTransmit("\n\n\n", 3);
}
//----------------------------------------------------------------------
