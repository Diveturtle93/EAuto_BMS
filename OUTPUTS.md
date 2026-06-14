# Output Zuweisung – EAuto BMS
 
Es stehen für die Programmierung unterschiedlichste Ausgänge am Mikrocontroller zur
Verfügung. Diese sind alle über eine entsprechende Logiklevel Schaltung nach außen
geführt.
 
---
 
Es stehen für die Ansteuerung zwei unterschiedliche Schaltungen zur Verfügung.
Unterschieden werden die beiden Ausgangsschaltungen nur in ihrer Stromtragfähigkeit.
Die beiden Ausgangsstufen haben unterschiedliche Leistungsmosfets verbaut, welche
somit eine unterschiedliche Stromtragfähigkeit besitzen. Somit können unterschiedlichste
Peripheriekomponenten angesteuert und geschaltet werden.
 
---
 
Alle Ausgänge arbeiten mit der angelegten Fahrzeugspannung. Sie sind alle ausgelegt
für 12 V, können aber auch mit 24 V betrieben werden.
 
---
 
## Liste der Ausgänge
 
Nachfolgend ist eine Auflistung aller Ausgangspins vom Mikrocontroller.
 
| Funktionsgruppe  | Pin  | Funktion             | Relevanz | Getestet |
|:-----------------|:----:|:---------------------|:---------|:--------:|
| Shutdown Circuit | PA1  | IMD OK               | System   | Ja       |
| Akkukasten       | PA9  | Heizung 1            | System   | Nein     |
| Akkukasten       | PA10 | Heizung 2            | System   | Nein     |
| STM32            | PB2  | LED Red              | Komfort  | Ja       |
| STM32            | PB7  | LED Green            | Komfort  | Ja       |
| STM32            | PB14 | LED Blue             | Komfort  | Ja       |
| Fahrzeug         | PC13 | Power On             | System   | Ja       |
| Fahrzeug         | PD3  | Digital 1            | Komfort  | Nein     |
| Fahrzeug         | PD4  | Digital 2            | Komfort  | Nein     |
| Akkukasten       | PD12 | HV- Relais PWM       | System   | Nein     |
| Akkukasten       | PD13 | HV+ Relais PWM       | System   | Nein     |
| Akkukasten       | PD14 | HV/ Relais PWM       | System   | Nein     |
| Akkukasten       | PD15 | HV Charge Relais PWM | System   | Nein     |
| Shutdown Circuit | PE0  | Freigabe Run         | System   | Ja       |
| Ladebuchse       | PE1  | Inlet LED Green      | Komfort  | Nein     |
| Ladebuchse       | PE2  | Inlet LED Green      | Komfort  | Nein     |
| Shutdown Circuit | PE7  | Akku OK              | System   | Ja       |
| Akkukasten       | PE15 | ISO SPI Enable       | System   | Ja       |
| Stromsensor      | PF1  | Trigger Out          | Komfort  | Nein     |
| Akkukasten       | PF13 | Precharge Relais     | System   | Ja       |
| Akkukasten       | PG2  | HV- Relais           | System   | Nein     |
| Akkukasten       | PG3  | HV+ Relais           | System   | Ja       |
| Akkukasten       | PG9  | HV/ Relais           | Komfort  | Nein     |
| Akkukasten       | PG10 | HV Charge Relais     | Komfort  | Nein     |
| Akkukasten       | PG11 | Ladeleuchte          | System   | Nein     |
| Fahrzeug         | PG14 | Recuperation         | Komfort  | Nein     |
| Fahrzeug         | PG15 | AMS I Limit          | System   | Ja       |
 
## System relevante Ausgänge
 
Alle system relevanten Ausgänge sind für die Ansteuerung von Komponenten, die etwas mit dem
Fahren des Fahrzeugs zu tun haben. Diese Ausgänge werden deshalb öfter betrachtet als
Komfortausgänge. Zudem dürfen die system relevanten Ausgänge nicht ausfallen und müssen
auch im Notfall funktionieren. Sie werden ebenfalls über den CAN-Bus als Nachricht versendet,
um die Zustände für Debug-Zwecke mitloggen zu können.
 
## Besondere Ausgänge
 
Bei mehreren Ausgängen gibt es noch zusätzliche Eigenschaften, weshalb diese nicht als
reine Logik IO betrachtet werden können. Dies liegt daran, dass sie mit einer PWM ein
Gerät ansteuern müssen. Dies betrifft die vier HV-Relais im Akkukasten (PD12–PD15), die
über PWM-Signale angesteuert werden, um die Einschaltströme zu begrenzen und die Lebensdauer
der Relais zu verlängern.
 
## Komfort Ausgänge
 
Alle Komfort Ausgänge sind zusätzlich vorhanden und dienen nur der Steuerung von Peripherie,
die nicht zum Fahren wichtig ist, aber mit im Fahrzeug verbaut werden soll. Diese Komponenten
werden zunächst nicht mit ihren eigentlichen Funktionen belegt und können aktuell für
Debug-Zwecke verwendet werden.
 
Im weiteren Verlauf bekommen diese Ausgänge ihre eigentliche Funktion zugewiesen.