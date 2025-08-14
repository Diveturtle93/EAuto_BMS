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
void CAN_config (void)
{
	CAN_Output_PaketListe[0] = CAN_Nachricht(BMS_CAN_SAFETY, 6, 100, 55);			// main.c
	CAN_Output_PaketListe[1] = CAN_Nachricht(BMS_CAN_DIGITAL_OUT, 5, 200, 75);		// main.c
	CAN_Output_PaketListe[2] = CAN_Nachricht(BMS_CAN_DIGITAL_IN, 4, 200, 74);		// main.c
	CAN_Output_PaketListe[3] = CAN_Nachricht(BMS_CAN_ANALOG_IN, 8, 500, 67);		// main.c
	CAN_Output_PaketListe[4] = CAN_Nachricht(BMS_CAN_TEMPERATUR, 8, 500, 84);		// main.c
	CAN_Output_PaketListe[5] = CAN_Nachricht(BMS_CAN_STATUS, 4, 200, 95);			// main.c
	CAN_Output_PaketListe[6] = CAN_Nachricht(BMS_CAN_IMD, 5, 200, 62);				// main.c oder imd.c?
	CAN_Output_PaketListe[7] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 1);			// batteriemanagement.c
	CAN_Output_PaketListe[8] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 2);			// batteriemanagement.c
	CAN_Output_PaketListe[9] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 3);			// batteriemanagement.c
	CAN_Output_PaketListe[10] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 4);			// batteriemanagement.c
	CAN_Output_PaketListe[11] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 5);			// batteriemanagement.c
	CAN_Output_PaketListe[12] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 6);			// batteriemanagement.c
	CAN_Output_PaketListe[13] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 7);			// batteriemanagement.c
	CAN_Output_PaketListe[14] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 8);			// batteriemanagement.c
	CAN_Output_PaketListe[15] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 9);			// batteriemanagement.c
	CAN_Output_PaketListe[16] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 10);		// batteriemanagement.c
	CAN_Output_PaketListe[17] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 11);		// batteriemanagement.c
	CAN_Output_PaketListe[18] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 12);		// batteriemanagement.c
	CAN_Output_PaketListe[19] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 13);		// batteriemanagement.c
	CAN_Output_PaketListe[20] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 14);		// batteriemanagement.c
	CAN_Output_PaketListe[21] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 15);		// batteriemanagement.c
	CAN_Output_PaketListe[22] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 16);		// batteriemanagement.c
	CAN_Output_PaketListe[23] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 17);		// batteriemanagement.c
	CAN_Output_PaketListe[24] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 18);		// batteriemanagement.c
	CAN_Output_PaketListe[25] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 19);		// batteriemanagement.c
	CAN_Output_PaketListe[26] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 20);		// batteriemanagement.c
	CAN_Output_PaketListe[27] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 21);		// batteriemanagement.c
	CAN_Output_PaketListe[28] = CAN_Nachricht(BMS_CAN_ZELLEN11, 8, 200, 22);		// batteriemanagement.c
	CAN_Output_PaketListe[29] = CAN_Nachricht(BMS_CAN_ZELLEN12, 8, 200, 23);		// batteriemanagement.c
	CAN_Output_PaketListe[30] = CAN_Nachricht(BMS_CAN_ZELLEN13, 8, 200, 24);		// batteriemanagement.c
	CAN_Output_PaketListe[31] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 25);	// batteriemanagement.c
	CAN_Output_PaketListe[32] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 26);	// batteriemanagement.c
	CAN_Output_PaketListe[33] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 27);	// batteriemanagement.c
	CAN_Output_PaketListe[34] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 28);	// batteriemanagement.c
	CAN_Output_PaketListe[35] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 29);	// batteriemanagement.c
	CAN_Output_PaketListe[36] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 30);	// batteriemanagement.c
	CAN_Output_PaketListe[37] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 31);	// batteriemanagement.c
	CAN_Output_PaketListe[38] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 32);	// batteriemanagement.c
	CAN_Output_PaketListe[39] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 33);	// batteriemanagement.c
	CAN_Output_PaketListe[40] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 34);	// batteriemanagement.c
	CAN_Output_PaketListe[41] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 35);	// batteriemanagement.c
	CAN_Output_PaketListe[42] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 36);	// batteriemanagement.c
	CAN_Output_PaketListe[43] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 37);	// batteriemanagement.c
	CAN_Output_PaketListe[44] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 38);	// batteriemanagement.c
	CAN_Output_PaketListe[45] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 39);	// batteriemanagement.c
	CAN_Output_PaketListe[46] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 40);	// batteriemanagement.c
	CAN_Output_PaketListe[47] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 41);	// batteriemanagement.c
	CAN_Output_PaketListe[48] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 42);	// batteriemanagement.c
	CAN_Output_PaketListe[49] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 43);	// batteriemanagement.c
	CAN_Output_PaketListe[50] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 44);	// batteriemanagement.c
	CAN_Output_PaketListe[51] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 45);	// batteriemanagement.c
	CAN_Output_PaketListe[52] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 46);	// batteriemanagement.c
	CAN_Output_PaketListe[53] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 47);	// batteriemanagement.c
	CAN_Output_PaketListe[54] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 48);	// batteriemanagement.c
	CAN_Output_PaketListe[55] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 49);	// batteriemanagement.c
	CAN_Output_PaketListe[56] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 50);	// batteriemanagement.c
	CAN_Output_PaketListe[57] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 51);	// batteriemanagement.c
	CAN_Output_PaketListe[58] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 52);	// batteriemanagement.c
	CAN_Output_PaketListe[59] = CAN_Nachricht(BMS_CAN_TEMPERATUR11, 8, 200, 53);	// batteriemanagement.c
	CAN_Output_PaketListe[60] = CAN_Nachricht(BMS_CAN_TEMPERATUR12, 8, 200, 54);	// batteriemanagement.c
	CAN_Output_PaketListe[61] = CAN_Nachricht(BMS_CAN_TEMPERATUR13, 8, 200, 55);	// batteriemanagement.c
	CAN_Output_PaketListe[62] = CAN_Nachricht(BMS_CAN_TEMPERATUR14, 8, 200, 56);	// batteriemanagement.c
	CAN_Output_PaketListe[63] = CAN_Nachricht(BMS_CAN_STACKVOLTAGE, 4, 200, 73);	// batteriemanagement.c
}
//----------------------------------------------------------------------
