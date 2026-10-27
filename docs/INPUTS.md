# Input Zuweisung – EAuto BMS
 
Es stehen für die Programmierung unterschiedlichste Eingänge am Mikrocontroller zur
Verfügung. Diese sind alle über eine entsprechende Logiklevel Schaltung nach außen
geführt.
 
---
 
Es stehen für die Auswertung zwei unterschiedliche Schaltungen zur Verfügung.
Bei der ersten Schaltung muss der Schalter ein 12 V Signal an den Eingang anlegen.
Dieses wird dann verarbeitet und an den Mikrocontroller invertiert mit einem 3,3 V Pegel
weitergegeben. Ist der Schalter nicht gedrückt, so liegt am Mikrocontroller 3,3 V an. Wird
der Schalter gedrückt, so fällt das Signal am Mikrocontroller auf 0 V ab. Die zweite Art
von Schaltung ist genau umgekehrt. Hier muss der Schalter das Signal mit Masse versorgen.
Dieses Signal wird ebenfalls über einen Pegelwandler in ein 3,3 V Signal umgewandelt.
Hier bekommt der Mikrocontroller ein 3,3 V Signal, sobald der Schalter gedrückt wird.
Ist der Schalter nicht gedrückt, so liegen am Eingang des Mikrocontrollers 0 V an.
 
---
 
Alle Eingänge sind kurzschlussfest und für Spannungen von 0 V bis 12 V ausgelegt. Darüber
hinaus sind die Eingänge sicher gegen Verpolung und Überspannungen bis 24 V.
 
---
 
## Liste der Eingänge
 
Nachfolgend ist eine Auflistung aller Eingangspins vom Mikrocontroller.
 
| Funktionsgruppe  | Pin  | Funktion    | Relevanz | Getestet |
|:-----------------|:----:|:------------|:---------|:--------:|
| Shutdown Circuit | PA0  | Crash       | System   | Ja       |
| STM32            | PA2  | Wakeup      | Komfort  | Nein     |
| STM32            | PA10 | Button 2    | Komfort  | Nein     |
| STM32            | PA11 | Button 1    | Komfort  | Nein     |
| SD-Card          | PC6  | SD Switch   | Komfort  | Nein     |
| Fahrzeug         | PD8  | KL15        | System   | Ja       |
| Shutdown Circuit | PE3  | HVIL Sense  | System   | Ja       |
| Shutdown Circuit | PE4  | BTB Sense   | System   | Ja       |
| Shutdown Circuit | PE5  | Motor Sense | System   | Ja       |
| Shutdown Circuit | PE8  | IMD OK      | System   | Ja       |
| Shutdown Circuit | PE9  | IMD PWM     | System   | Ja       |
| Stromsensor      | PF2  | Overcurrent | Komfort  | Nein     |
| Shutdown Circuit | PF15 | Precharge   | System   | Ja       |
 
## System relevante Eingänge
 
Alle system relevanten Eingänge haben etwas mit der Auswertung der Daten zum Fahren mit
dem Fahrzeug zu tun. Diese Eingänge werden deshalb öfter geprüft als Komforteingänge.
Zudem geben die system relevanten Eingänge Aufschluss auf Komponentenzustände, die zum
Fahren benötigt werden. Sie werden ebenfalls über den CAN-Bus als Nachricht versendet,
um die Zustände für Debug-Zwecke mitloggen zu können.
 
## Besondere Eingänge
 
Bei mehreren Eingängen gibt es noch zusätzliche Eigenschaften, weshalb diese nicht als
reine Logik IO betrachtet werden können. Dies liegt daran, dass sie entsprechend wichtig
sind oder noch eine andere Aufgabe haben, als nur einen Logikpegel einzulesen.
 
## Komfort Eingänge
 
Alle Komfort Eingänge sind zusätzlich vorhanden und dienen nur der Steuerung von Peripherie,
die nicht zum Fahren wichtig ist, aber mit im Fahrzeug verbaut werden soll. Diese Komponenten
werden zunächst nicht mit ihren eigentlichen Funktionen belegt und werden aktuell nur für
Debug-Zwecke verwendet.
 
Im weiteren Verlauf bekommen diese Eingänge ihre eigentliche Funktion zugewiesen.
 
## Standardwerte
 
Für sämtliche Eingänge liegen Standardwerte für die Auswertung vor. Diese liegen auch am
Mikrocontroller an, wenn kein Stecker am BMS gesteckt ist. Darüber hinaus wird in der
nachfolgenden Tabelle mit aufgeführt, welche Werte am Mikrocontroller eingelesen werden
können, wenn das BMS im Fahrzeug verbaut ist. Diese beiden Werte können sich gegebenenfalls
voneinander unterscheiden.
 
| Funktionsgruppe  | Pin  | Funktion    | Standardwert | Wert Fahrzeug |
|:-----------------|:----:|:------------|:------------:|:-------------:|
| Shutdown Circuit | PA0  | Crash       | 1            | 1             |
| STM32            | PA2  | Wakeup      | 0            | 0             |
| STM32            | PA10 | Button 2    | 1            | 1             |
| STM32            | PA11 | Button 1    | 1            | 1             |
| SD-Card          | PC6  | SD Switch   | 1            | 1             |
| Fahrzeug         | PD8  | KL15        | 0            | 0             |
| Shutdown Circuit | PE3  | HVIL Sense  | 1            | 0             |
| Shutdown Circuit | PE4  | BTB Sense   | 1            | 0             |
| Shutdown Circuit | PE5  | Motor Sense | 1            | 0             |
| Shutdown Circuit | PE8  | IMD OK      | 0            | 1             |
| Shutdown Circuit | PE9  | IMD PWM     | 0            | PWM           |
| Stromsensor      | PF2  | Overcurrent | 1            | 1             |
| Shutdown Circuit | PF15 | Precharge   | 0            | 1             |