# CAN Bus – EAuto BMS
 
Für die Programmierung am Mikrocontroller und zur Kommunikation mit dem Fahrzeug
stehen auf der Platine zwei CAN-Busse zur Verfügung. Diese laufen auf unterschiedlichen
Baudraten und sind für verschiedene Einsatzzwecke vorgesehen.
 
---
 
Am Mikrocontroller sind nur zwei Registerbänke für die CAN-Interfaces vorhanden. Da
CAN1 und CAN2 am Mikrocontroller die Registerbank teilen, werden diese für die niedriger
priorisierten CAN-Busse genutzt. Im Fahrzeug sind das der Komfort- und Infotainment-CAN.
 
Der Antriebs-CAN erhält eine höhere Priorisierung und bekommt deshalb den CAN-Bus,
welcher eine eigene Registerbank hat (CAN3). Dieser ist für die Kommunikation aller
sicherheitsrelevanten Daten zuständig. Hier werden Informationen vom Motorcontroller,
Batteriemanagement, ABS, Lenkwinkelsensor, Ladegerät, DCDC-Wandler und Motorsteuergerät
übertragen. Alle Informationen laufen im Motorsteuergerät zusammen und werden dort
verarbeitet.
 
Des Weiteren werden die Informationen auch im Kombiinstrument genutzt und angezeigt.
Dieses zeigt die Drehzahl, die Geschwindigkeit, den Tankfüllstand / Akkustand und die
Motortemperatur an.
 
---
 
Auf dem Komfort-CAN sind weitere Informationen vom Fahrzeug. Diese sind zum jetzigen
Zeitpunkt nicht relevant und werden derzeit in der Programmierung nicht berücksichtigt.
 
---
 
## Liste aller CAN-IDs
 
Die nachfolgenden CAN-IDs sind auf dem Antriebs-CAN aktuell messbar.
 
| CAN-Bus | CAN-ID | Sender             | Empfänger          | Timing [ms] | DLC   |
|:--------|:------:|:-------------------|:-------------------|:-----------:|:-----:|
| CAN3    | 0x0C2  | Lenkwinkelsensor   | …                  | 10          | 8     |
| CAN3    | 0x181  | Bamocar            | Motorsteuergerät   | 100         | 3 – 6 |
| CAN3    | 0x1A0  | Bremse             | …                  | 7           | 8     |
| CAN3    | 0x201  | Motorsteuergerät   | Bamocar            | 100         | 3 – 6 |
| CAN3    | 0x237  | Batteriemanagement | …                  | 200         | 5     |
| CAN3    | 0x238  | Batteriemanagement | …                  | 200         | 4     |
| CAN3    | 0x239  | Batteriemanagement | …                  | 500         | 8     |
| CAN3    | 0x280  | Motorsteuergerät   | Kombiinstrument    | 20          | 8     |
| CAN3    | 0x288  | Motorsteuergerät   | …                  | 20          | 8     |
| CAN3    | 0x2A0  | Bremse             | …                  | …           | …     |
| CAN3    | 0x320  | Kombiinstrument    | …                  | 20          | 8     |
| CAN3    | 0x380  | Motorsteuergerät   | …                  | 20          | 8     |
| CAN3    | 0x388  | Motorsteuergerät   | …                  | 20          | 3     |
| CAN3    | 0x3D0  | …                  | …                  | 20          | 2     |
| CAN3    | 0x411  | Batteriemanagement | HV Stromsensor     | xxx         | 8     |
| CAN3    | 0x420  | Kombiinstrument    | …                  | 200         | 8     |
| CAN3    | 0x480  | Motorsteuergerät   | …                  | 20          | 8     |
| CAN3    | 0x488  | Motorsteuergerät   | …                  | 20          | 8     |
| CAN3    | 0x4A0  | Bremse             | …                  | 14          | 8     |
| CAN3    | 0x4A8  | Bremse             | …                  | 20          | 8     |
| CAN3    | 0x511  | HV Stromsensor     | Batteriemanagement | xxx         | 8     |
| CAN3    | 0x520  | Kombiinstrument    | …                  | 200         | 8     |
| CAN3    | 0x521  | HV Stromsensor     | Batteriemanagement | 20          | 8     |
| CAN3    | 0x522  | HV Stromsensor     | Batteriemanagement | 60          | 8     |
| CAN3    | 0x523  | HV Stromsensor     | Batteriemanagement | xxx         | 8     |
| CAN3    | 0x524  | HV Stromsensor     | Batteriemanagement | xxx         | 8     |
| CAN3    | 0x525  | HV Stromsensor     | Batteriemanagement | xxx         | 8     |
| CAN3    | 0x526  | HV Stromsensor     | Batteriemanagement | xxx         | 8     |
| CAN3    | 0x527  | HV Stromsensor     | Batteriemanagement | xxx         | 8     |
| CAN3    | 0x528  | HV Stromsensor     | Batteriemanagement | xxx         | 8     |
| CAN3    | 0x539  | Batteriemanagement | …                  | 500         | 8     |
| CAN3    | 0x560  | Batteriemanagement | …                  | 200         | 4     |
| CAN3    | 0x565  | Batteriemanagement | …                  | 200         | 5     |
| CAN3    | 0x580  | Motorsteuergerät   | …                  | 10          | 8     |
| CAN3    | 0x5A0  | Bremse             | …                  | 14          | 8     |
| CAN3    | 0x5D0  | …                  | …                  | 100         | 6     |
| CAN3    | 0x5DE  | …                  | …                  | 200         | 5     |
 
**…** – Aktuell keine Erkenntnis über den Wert vorhanden.
**xxx** – Timing nicht vorhanden. CAN-ID auf dem Bus nur messbar nach Aufforderung durch manuelles Senden.
 
---
 
## Debug-Nachrichten – Zellspannungen und Zelltemperaturen
 
Die CAN-Nachrichten vom Antriebs-CAN werden aktuell laufend erweitert. Zusätzlich zu den
regulären Nachrichten gibt es eine optionale Debug-Ausgabe mit allen Zellspannungen und
Zelltemperaturen. Diese wird standardmäßig nicht ausgegeben und soll nur für
Diagnosezwecke auf den CAN-Bus gelegt werden können.
 
| Datentyp       | Start-ID | Nachrichten pro Modul | Byte pro Nachricht | Beschreibung                          |
|:---------------|:--------:|:---------------------:|:------------------:|:--------------------------------------|
| Zellspannungen | 0x640    | 3                     | 8                  | 12 Zellen à 16 Bit = 3 Nachrichten    |
| Zelltemperaturen | 0x740  | 4                     | 8                  | 12 Temperaturen à 16 Bit = 4 Nachrichten |
 
Bei bis zu 10 Modulen im System sind dann bis zu 70 Nachrichten für alle Zelldaten auf dem
CAN-Bus vorhanden.
 
---
 
## Stromsensor-Kommunikation
 
CAN-Nachrichten, die das BMS benötigt, kommen hauptsächlich vom HV-Stromsensor. Dieser
misst den Strom des Hochvoltsystems. Zusätzlich misst der Stromsensor unabhängig vom BMS
die Gesamtspannung des HV-Systems. Dies hat den Vorteil, dass die vom BMS gemessenen
Werte mit einem unabhängigen Referenzwert auf Plausibilität geprüft werden können. Ist
die Diskrepanz zu groß, so kann das System abgeschaltet werden.
 
Weitere Nachrichten vom Batteriemanagement-System geben Aufschluss über den Zustand und
Status des BMS. Ebenfalls wird eine Nachricht für den IMD mit ausgegeben.
 
