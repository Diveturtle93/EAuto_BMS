# EAuto BMS

Dieses Projekt ist für die Elektrifizierung eines Autos. Dabei wird der alte Diesel-
Motor ausgebaut und gegen einen Elektromotor getauscht. Um nun das Fahrzeug mit
Spannung zu versorgen, wird ein entsprechend großer Akku benötit. Da hier dann alle
Zellen im Akku ständig überwacht werden müssen, wir ein Batteriemanagement-System
im Akkukasten implementiert.

Dieses überwacht alle Zellen ständig. Dabei werden dann die Zellspannungen und 
-temperaturen eingelesen und verarbeitet. Zudem wird neben den Zellen noch weitere
Aufgaben erledigt. Dies sind das Überwachen des HV-Stromes, das einlesen eines
Isolationswächters, die Ausgabe der Akkukapazität auf dem Kombiinstrument sowie
die Überwachung einer Interlock-Schleife.

---

Das eigentliche Batteriemanagement-System basiert auf dem LTC6811-1 und liest alle
Zellspannungen und -temperaturen ein. Diese werden dann intern verarbeitet und
ausgewertet. Das Einlesen erfolgt über eine isolierte SPI-Schnittstelle. Damit
können die Daten auch an ICs mit einem anderen Spannungsbezugpunkt übertragen werden.

Des Weiteren werden im System die Minimal- und Maximal-Spannung und Temperatur
sowie die Gesamtspannung eines Akkumodules ermittelt. Ein Modul besteht aus zwölf
in Reihe geschalteten Zellen. Von diesen Modulen werden dann acht bis zehn im
Fahrzeug verbaut.

---

##Isolationswächter

Der IMD wertet die Verbindung des Hochvoltsystemes zur Fahrzeugkarosserie aus.
Hier wied ermittelt, ob der Widerstandswert zur Fahrzeugkarosserie größer einem
vorgegebenen Wert ist. Sollte dieser Wert überschritten werden, so ist eine
Betreiben des Fahrzeuges nicht möglich und das System soll unverzüglich abschalten.

Damit soll verhindert werden, dass man Aufgrund eines Isolationsfehlers einen
Stromschlag bekommt. Ein Isolationsfehler stellt eine Gefahr für Leib und Leben dar
und ist somit ein kritischer Fehler.

## Stromsensor

Der Stromsensor misst den HV-Strom im System und kann zusätzlich noch drei
Spannungen mit Bezug zum HV-System einlesen. Diese werden dann an das BMS
übertragen und von diesem mit ausgewertet oder für Plausibilitätsprüfungen benutzt.