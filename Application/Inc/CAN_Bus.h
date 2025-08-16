//----------------------------------------------------------------------
// Titel	:	CAN_Bus.h
//----------------------------------------------------------------------
// Sprache	:	C
// Datum	:	Jun 28, 2023
// Version	:	1.0
// Autor	:	Diveturtle93
// Projekt	:	CAN-Bus
//----------------------------------------------------------------------

// Dateiheader definieren
//----------------------------------------------------------------------
#ifndef INC_CAN_BUS_H_
#define INC_CAN_BUS_H_
//----------------------------------------------------------------------

// Einfuegen der standard Include-Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Einfuegen der STM Include-Dateien
//----------------------------------------------------------------------
#include "can.h"
#include "main.h"
//----------------------------------------------------------------------

// Einfuegen der eigenen Include Dateien
//----------------------------------------------------------------------

//----------------------------------------------------------------------

// Konstanten definieren
//----------------------------------------------------------------------
// Anzahl der CAN Output Pakete defineren
//----------------------------------------------------------------------
#define ANZAHL_OUTPUT_PAKETE						64						// Anzahl Sende Nachrichten
//----------------------------------------------------------------------

// Typedefine fuer Buffer size
//----------------------------------------------------------------------
typedef enum																// TypeDef fuer Empfangsbuffer groesse
{																			// Tabellenform
	RX_SIZE_2 = (uint16_t)2,
	RX_SIZE_4 = (uint16_t)4,
	RX_SIZE_8 = (uint16_t)8,
	RX_SIZE_16 = (uint16_t)16,
	RX_SIZE_32 = (uint16_t)32,
	RX_SIZE_64 = (uint16_t)64,
	RX_SIZE_128 = (uint16_t)128,
	RX_SIZE_256 = (uint16_t)256,
	RX_SIZE_512 = (uint16_t)512,
	RX_SIZE_1024 = (uint16_t)1024,
} RXQUEUE_TABLE;
//----------------------------------------------------------------------
typedef enum																// TypeDef fuer Sendebuffer groesse
{																			// Tabellenform
	TX_SIZE_2 = (uint16_t)2,
	TX_SIZE_4 = (uint16_t)4,
	TX_SIZE_8 = (uint16_t)8,
	TX_SIZE_16 = (uint16_t)16,
	TX_SIZE_32 = (uint16_t)32,
	TX_SIZE_64 = (uint16_t)64,
	TX_SIZE_128 = (uint16_t)128,
	TX_SIZE_256 = (uint16_t)256,
	TX_SIZE_512 = (uint16_t)512,
	TX_SIZE_1024 = (uint16_t)1024,
} TXQUEUE_TABLE;
//----------------------------------------------------------------------
// Typedefine fuer CAN-Message
//----------------------------------------------------------------------
typedef struct
{
	uint32_t id;															// CAN Identifier
	uint16_t timestamp;														// Zeit wann die Nachricht angekommen ist
	uint8_t idhit;															// Filter der die Nachricht erkannt hat
	struct
	{
		uint8_t extended:1;													// Erweiterte ID (29 Bit)
		uint8_t remote:1;													// Remote Sendeanforderung
		uint8_t overrun:1;													// Nachrichten ueberlauf
		uint8_t reserved:5;													// Flags haben alle 1 Bit, Deshalb sind 5 Bit reserviert
	} flags;
	uint8_t len;															// Nachrichtenlaenge
	uint8_t buf[8];															// Datenbuffer
	int8_t mb;																// Identifier welche Mailbox benutzt werden soll
	uint8_t bus;															// Identifier welche Bus benutzt werden soll
	bool seq;																// Sequentiale Rahmen
} CAN_message_t;
//----------------------------------------------------------------------
// Typedefine fuer Rigbuffer
//----------------------------------------------------------------------
typedef struct
{
	volatile uint16_t head;													// Kopf des Ringbusses
	volatile uint16_t tail;													// Schwanz des Ringbusses
	uint16_t size;															// Groesse des Ringbusses
	volatile CAN_message_t *buffer;											// Nachrichtenbuffer
} RingbufferTypeDef;
//----------------------------------------------------------------------
// Typedefine fuer CAN-Paket
//----------------------------------------------------------------------
typedef struct
{
	CAN_message_t msg;														// CAN-Nachricht
	uint16_t sendeintervall;												// Intervall, wie oft die Nachricht gesendet wird (in ms)
	uint32_t sendetime;														// Startzeit, ab wann die Nachricht gesendet wird
	uint8_t sendpossible;													// Senden der Nachricht moeglich, 0 = nicht moeglich, 255 = unendlich, Zahl anzahl der Sendevorgaenge
} CAN_PaketTypeDef;
//----------------------------------------------------------------------

// Arrays definieren
//----------------------------------------------------------------------
extern CAN_PaketTypeDef CAN_Output_PaketListe[ANZAHL_OUTPUT_PAKETE];
//----------------------------------------------------------------------

// Funktionen definieren
//----------------------------------------------------------------------
void CANinit (RXQUEUE_TABLE rxSize, TXQUEUE_TABLE txSize);					// CAN-Bus und Ringpuffer initialisieren
bool CANwrite (CAN_message_t *CAN_tx_msg, bool MB);							// CAN-Nachricht schreiben
uint8_t CAN_available (void);												// Abfrage, ob CAN-Nachricht im Ringpuffer vorhanden
bool CANread (CAN_message_t *CAN_rx_msg);									// CAN-Nachricht lesen
void CANwork (void);														// CAN-Bus durchlaufen
void CAN_config (void);														// CAN-Bus konfigurieren
void clearCAN (void);														// Daten aus CAN-NAchrichten zuruecksetzen
bool isInitialized (void);													// Abfrage, ob Ringpuffer initialisiert
void initializeBuffer (void);												// Empfangs und Sendepuffer initialisieren
void initRingBuffer (RingbufferTypeDef *ring, volatile CAN_message_t *buffer, uint32_t size);	// Ringpuffer initialisieren
bool addToRingBuffer (RingbufferTypeDef *ring, CAN_message_t *msg);			// Nachricht zu Ringpuffer hinzufuegen
bool removeFromRingBuffer (RingbufferTypeDef *ring, CAN_message_t *msg);	// Nachricht von Ringpuffer loeschen
bool isRingBufferEmpty (RingbufferTypeDef *ring);							// Abfrage, ob Ringpuffer leer ist
CAN_PaketTypeDef CAN_Nachricht (uint16_t id, uint8_t length, uint16_t sendeintervall, uint32_t sendetime, uint8_t sendpossible);	// CAN-Paket in CAN-Paketliste schreiben
//----------------------------------------------------------------------

#endif /* INC_CAN_BUS_H_ */
//----------------------------------------------------------------------
