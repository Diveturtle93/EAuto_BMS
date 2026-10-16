# **CAN Bus**

Für die Programmierung am Mikrocontroller und zur Kommunikation mit dem Fahrzeug
stehen auf der Platine zwei CAN-Busse zur Verfügung. Diese laufen alle auf
unterschiedlichen Baudraten und sind für verschieden Einsatzzwecke vorgesehen.


Am Mikrocontroller sind jedoch nur zwei Registerbänke für die CAN-Interfaces
vorhanden. Da CAN1 und CAN2 am Mikrocontroller die Registerbank teilen, werden diese
für die niedriger priorisierten CAN-Busse genutzt. Im Fahrzeug sind das der Komfort-
und Infotainment-CAN.

Der Antriebs-CAN erhält eine höhere Priorisierung und bekommt deshalb den CAN-Bus,
welcher eine eigene Registerbank hat (CAN3). Dieser ist für die Kommunikation aller
Sicherheitsrelevanten Daten zuständig. Hier werden Infomationen vom Motorcontroller,
Batteriemanagement, ABS, Lenkwinkelsensor, Ladegerät, DCDC-Wandler und
Motorsteuergerät übertragen. Alle Infos laufen im Motorsteuergerät zusammen und
werden dann hier verarbeitet.

Des Weiteren werden die Informationen auch im Kombiinstrument genutzt und angezeigt.
Dieses zeigt einem die Drehzahl, die Geschwindigkeit, den Tankfüllstand / Akkustant
und die Motortemperatur an.


Auf dem Komfort-CAN sind weitere Informationen vom Fahrzeug. Diese sind zum jetztigen
Zeitpunkt nicht Relevant und werden zur Zeit in der Programmierung nicht
berücksichtigt.

---

## Liste alle CAN-IDs

Die Nachfolgenden CAN-IDs sind auf dem Antriebs-CAN aktuell messbar.

| CAN-Bus | CAN-ID | Sender | Empfänger | Timing [ms] | DLC |
|:------- |:------:|:-------|:--------- |:------:|:---:|
| CAN3 | 0x0C2 | Lenkwinkelsensor | ... | 10 | 8 |
| CAN3 | 0x181 | Bamocar | Motorsteuergerät | 100 | 3 - 6 |
| CAN3 | 0x1A0 | Bremse | ... | 7 | 8 |
| CAN3 | 0x201 | Motorsteuergerät | Bamocar | 100 | 3 - 6 |
| CAN3 | 0x237 | Batteriemanagement | ... | 200 | 5 |
| CAN3 | 0x238 | Batteriemanagement | ... | 200 | 4 |
| CAN3 | 0x239 | Batteriemanagement | ... | 500 | 8 |
| CAN3 | 0x280 | Motorsteuergerät | Kombiinstrument | 20 | 8 |
| CAN3 | 0x288 | Motorsteuergerät | ... | 20 | 8 |
| CAN3 | 0x2A0 | Bremse | ... | ... | ... |
| CAN3 | 0x320 | Kombiinstrument | ... | 20 | 8 |
| CAN3 | 0x380 | Motorsteuergerät | ... | 20 | 8 |
| CAN3 | 0x388 | Motorsteuergerät | ... | 20 | 3 |
| CAN3 | 0x3D0 | ... | ... | 20 | 2 |
| CAN3 | 0x411 | Batteriemanagement | HV Stromsensor | xxx | 8 |
| CAN3 | 0x420 | Kombiinstrument | ... | 200 | 8 |
| CAN3 | 0x480 | Motorsteuergerät | ... | 20 | 8 |
| CAN3 | 0x488 | Motorsteuergerät | ... | 20 | 8 |
| CAN3 | 0x4A0 | Bremse | ... | 14 | 8 |
| CAN3 | 0x4A8 | Bremse | ... | 20 | 8 |
| CAN3 | 0x511 | HV Stromsensor | Batteriemanagement | xxx | 8 |
| CAN3 | 0x520 | Kombiinstrument | ... | 200 | 8 |
| CAN3 | 0x521 | HV Stromsensor | Batteriemanagement | 20 | 8 |
| CAN3 | 0x522 | HV Stromsensor | Batteriemanagement | 60 | 8 |
| CAN3 | 0x523 | HV Stromsensor | Batteriemanagement | xxx | 8 |
| CAN3 | 0x524 | HV Stromsensor | Batteriemanagement | xxx | 8 |
| CAN3 | 0x525 | HV Stromsensor | Batteriemanagement | xxx | 8 |
| CAN3 | 0x526 | HV Stromsensor | Batteriemanagement | xxx | 8 |
| CAN3 | 0x527 | HV Stromsensor | Batteriemanagement | xxx | 8 |
| CAN3 | 0x528 | HV Stromsensor | Batteriemanagement | xxx | 8 |
| CAN3 | 0x539 | Batteriemanagement | ... | 500 | 8 |
| CAN3 | 0x560 | Batteriemanagement | ... | 200 | 4 |
| CAN3 | 0x565 | Batteriemanagement | ... | 200 | 5 |
| CAN3 | 0x580 | Motorsteuergerät | ... | 10 | 8 |
| CAN3 | 0x5A0 | Bremse | ... | 14 | 8 |
| CAN3 | 0x5D0 | ... | ... | 100 | 6 |
| CAN3 | 0x5DE | ... | ... | 200 | 5 |

... :	Aktuell keine Erkenntnis über den Wert vorhanden.
xxx :	Timing nich vorhanden. CAN-ID auf dem Bus nur messbar nach Aufforderung
		manuellem Senden

---

Die CAN-Nachrichten vom Antriebs CAN werden aktuell noch laufend erweitert. Dazu
kommt noch eine größere Liste mit allen Zellspannungen und -temperaturen. Diese
wird jedoch am Ende nicht mit ausgegeben. Und soll nur für Debugzwecke mit auf den
CAN-Bus gelegt werden können.

Dafür fangen dann die Nachrichten für die Zellspannungen mit der ID 0x640 an. Alle
Nachrichten für die Temperaturen der Zellen beginnen bei ID 0x740. Die Länge der
Nachrichten beträgt immer 8 Byte. Bei einem Wert von 16 Bit pro Spannung und
Temperatur brauchen 12 Zellen eines Modules drei Nachrichten für die Spannung und
vier Nachrichten für die Temperaturen. Bei weiteren sieben bis neun Modulen im
System, sind dann bis zu 70 Nachrichten für alle Zelldaten auf dem CAN-Bus vorhanden.

Weitere Nachrichten vom Batteriemanagement-System geben aufschluss über den Zustand
und Status des BMS. Ebenfalls wird eine Nachricht für den IMD mit ausgegeben.

---

CAN-Nachrichten die das BMS benötigt kommen hauptsächlich vom Stromsensor. Hier
wie der Strom des Hochvoltsystemes gemessen. Ebenfalls misst der Stromsensor nochmal
unabhängig die Gesamtspannung des HV-Systems. Dies hat dann den Vorteil, dass man
die gemessenen Werte vom BMS mit einem unabhängigen Referenzwert auf Plausibilität
prüfen kann. Ist hier die Diskrepanz zu groß, so kann man das System abschalten.