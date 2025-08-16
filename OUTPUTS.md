# **Output Zuweisung**

Es stehen für die Programmierung unterschiedlichste Ausgänge am Mikrocontroller zur
Verfügung. Diese sind alle über eine entsprechende Logiklevel Schaltung nach aussen
geführt.

---

Es stehen für die Ansteuerung zwei unterschiedlicher Schaltungen zur Verfügung.
Unterschieden werden die beiden Ausgangsschaltungen nur in ihrer Stromtragfähigkeit.
Die beiden Ausgangsstufen haben unterschiedliche Leistungsmosfets verbaut, welche
somit eine unterschiedliche Stromtragfähigkeit besitzen. Somit kann man
unterschiedlichste Periferie ansteueren und schalten.

---

Alle Ausgänge arbeiten mir der angelegten Fahrzeugspannung. Sie sind alle ausgelegt
für 12V, können aber auch mit 24V betrieben werden.


## Liste der Ausgänge

Nachfolgend ist eine Auflistung aller Ausgangspins vom Mikrocontroller.

| Funktionsgruppe | Pin | Funktion | Relevanz | Getestet |
|:--------------- |:---:|:-------- |:-------- | --------:|
| Shutdown Circuit | PA1 | IMD OK | System | No |
| Akkukasten | PA9 | Heizung 1 | System | No |
| Akkukasten | PA10 | Heizung 2 | System | No |
| STM32 | PB2 | LED Red | Komfort | Ja |
| STM32 | PB7 | LED Green | Komfort | Ja |
| STM32 | PB14 | LED Blue | Komfort | Ja |
| Fahrzeug | PC13 | Power On | System | Ja |
| Fahrzeug | PD3 | Digital 1 | Komfort | No |
| Fahrzeug | PD4 | Digital 2 | Komfort | No |
| Akkukasten | PD12 | HV- Relais PWM | System | No |
| Akkukasten | PD13 | HV+ Relais PWM | System | No |
| Akkukasten | PD14 | HV/ Relais PWM | System | No |
| Akkukasten | PD15 | HV Charge Relais PWM | System | No |
| Shutdown Circuit | PE0 | Freigabe Run | System | No |
| Ladebuchse | PE1 | Inlet LED Green | Komfort | No |
| Ladebuchse | PE2 | Inlet LED Green | Komfort | No |
| Shutdown Circuit | PE7 | Akku OK | System | No |
| Akkukasten | PE15 | ISO SPI Enable | System | No |
| Stromsensor | PF1 | Trigger Out | Komfort | No |
| Akkukasten | PF13 | Precharge Relais | System | No |
| Akkukasten | PG2 | HV- Relais | System | No |
| Akkukasten | PG3 | HV+ Relais | System | No |
| Akkukasten | PG9 | HV/ Relais | Komfort | No |
| Akkukasten | PG10 | HV Charge Relais | Komfort | No |
| Akkukasten | PG11 | Ladeleuchte | System | No |
| Fahrzeug | PG14 | Recuperation | Komfort | No |
| Fahrzeug | PG15 | AMS I Limit | System | No |


## System relevante Ausgänge

Alle System relevanten Ausgänge sind für die Ansteuerung von Komponenten, die etwas mit dem
Fahren des Fahrzeug zu tun haben. Diese Ausgänge werden deshalb öfter betrachtet als
Komfortausgänge. Zudem dürfen die System relevanten Ausgänge nicht ausfallen und müssen
auch im Notfall funktionieren. Sie werden ebenfalls über den CAN-Bus als Nachricht versendet,
um die Zustände für Debug-Zwecke mitloggen zu können.


## Besondere Ausgänge

Bei mehreren Ausgängen gibt es noch zusätzliche Eigenschaften, weshalb diese nicht als
reine Logik IO betrachtet werden können. Dies liegt daran, dass sie mit einer PWM ein
Gerät ansteuern müssen.


## Komfort Ausgänge
Alle Komfort Ausgänge sind zusätzlich vorhanden und dienen nur der Steuerung von Periferie,
die nicht zum Fahren wichtig ist, aber mit im Fahrzeug verbaut werden soll. Diese Komponenten
werden erstmal nicht mit ihren eigentlichen Funktionen belegt und können aktuell für
Debug-Zwecke verwendet werden.

Im weiteren Verlauf bekommen diese Ausgänge ihrer eigentlichen Funktion zugewiesen.