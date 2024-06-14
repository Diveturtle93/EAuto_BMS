//----------------------------------------------------------------------
// Titel	:	CAN_config.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Aug 25, 2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	BatteriemanagementSystem
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------
#include "CAN_Bus.h"
#include "BatteriemanagementSystem.h"
//----------------------------------------------------------------------

// Konfiguriere CAN Nachrichten
//----------------------------------------------------------------------
void CAN_config(void)
{
	CAN_Output_PaketListe[0] = CAN_Nachricht(BMS_CAN_SAFETY, 6, 100, 17);		// main.c
	CAN_Output_PaketListe[1] = CAN_Nachricht(BMS_CAN_DIGITAL_OUT, 5, 200, 13);	// main.c
	CAN_Output_PaketListe[2] = CAN_Nachricht(BMS_CAN_DIGITAL_IN, 4, 200, 14);	// main.c
	CAN_Output_PaketListe[3] = CAN_Nachricht(BMS_CAN_ANALOG_IN, 8, 500, 7);		// main.c
	CAN_Output_PaketListe[4] = CAN_Nachricht(BMS_CAN_TEMPERATUR, 8, 500, 24);	// main.c
	CAN_Output_PaketListe[5] = CAN_Nachricht(BMS_CAN_STATUS, 4, 200, 5);		// main.c
	CAN_Output_PaketListe[6] = CAN_Nachricht(BMS_CAN_IMD, 5, 200, 12);			// main.c oder imd.c?
	CAN_Output_PaketListe[7] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 28);		// batteriemanagement.c
	CAN_Output_PaketListe[8] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 30);		// batteriemanagement.c
	CAN_Output_PaketListe[9] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 27);		// batteriemanagement.c
	CAN_Output_PaketListe[10] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 40);// batteriemanagement.c
	CAN_Output_PaketListe[11] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 57);// batteriemanagement.c
	CAN_Output_PaketListe[12] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 37);// batteriemanagement.c
	CAN_Output_PaketListe[13] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 20);// batteriemanagement.c
	CAN_Output_PaketListe[14] = CAN_Nachricht(BMS_CAN_STACKVOLTAGE, 4, 200, 73);// batteriemanagement.c
}
//----------------------------------------------------------------------
