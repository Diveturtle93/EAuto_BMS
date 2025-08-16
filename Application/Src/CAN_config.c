//----------------------------------------------------------------------
// Titel	:	CAN_config.c
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	25.08.2022
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	CAN-Bus
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
void CAN_config (void)
{
	CAN_Output_PaketListe[0] = CAN_Nachricht(BMS_CAN_SAFETY, 6, 100, 55, 0);		// main.c
	CAN_Output_PaketListe[1] = CAN_Nachricht(BMS_CAN_DIGITAL_OUT, 5, 200, 75, 255);	// main.c
	CAN_Output_PaketListe[2] = CAN_Nachricht(BMS_CAN_DIGITAL_IN, 4, 200, 74, 255);	// main.c
	CAN_Output_PaketListe[3] = CAN_Nachricht(BMS_CAN_ANALOG_IN, 8, 500, 67, 255);	// main.c
	CAN_Output_PaketListe[4] = CAN_Nachricht(BMS_CAN_TEMPERATUR, 8, 500, 84, 255);	// main.c
	CAN_Output_PaketListe[5] = CAN_Nachricht(BMS_CAN_STATUS, 4, 200, 95, 255);		// main.c
	CAN_Output_PaketListe[6] = CAN_Nachricht(BMS_CAN_IMD, 5, 200, 62, 255);			// main.c oder imd.c?
	CAN_Output_PaketListe[7] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 1, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[8] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 2, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[9] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 3, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[10] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 4, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[11] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 5, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[12] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 6, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[13] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 7, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[14] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 8, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[15] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 9, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[16] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 10, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[17] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 11, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[18] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 12, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[19] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 13, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[20] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 14, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[21] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 15, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[22] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 16, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[23] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 17, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[24] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 18, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[25] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 19, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[26] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 20, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[27] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 21, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[28] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 22, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[29] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 23, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[30] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 24, 0);		// batteriemanagement.c
	CAN_Output_PaketListe[31] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 25, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[32] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 26, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[33] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 27, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[34] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 28, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[35] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 29, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[36] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 30, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[37] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 31, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[38] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 32, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[39] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 33, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[40] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 34, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[41] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 35, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[42] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 36, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[43] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 37, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[44] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 38, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[45] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 39, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[46] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 40, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[47] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 41, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[48] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 42, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[49] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 43, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[50] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 44, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[51] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 45, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[52] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 46, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[53] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 47, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[54] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 48, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[55] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 49, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[56] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 50, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[57] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 51, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[58] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 52, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[59] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 53, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[60] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 54, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[61] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 55, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[62] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 56, 0);	// batteriemanagement.c
	CAN_Output_PaketListe[63] = CAN_Nachricht(BMS_CAN_STACKVOLTAGE, 4, 200, 73, 0);	// batteriemanagement.c
}
//----------------------------------------------------------------------
