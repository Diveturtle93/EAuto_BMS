# ** Shutdown-Circuit **

Der Shutdown-Circuit (SDC) dient der Validierung des HV-Kreises und der HV-Stecker.
Er prüft, ob alle Stecker gesteckt und ob Fehler im System aufgetreten sind.

Wird ein Fehler festgestellt oder sind nicht alle Stecker gesteckt, so ist ein
Vorladen des HV-Kreises nicht möglich. Ein fahren mit dem Fahrzeug ist dann ebenfalls
nicht gegeben. Wir allerding ein Fehler beim Fahren festgestellt, so ist hier noch
eine Priorisierung notwendig. Je nach Fehlerart und -auswirkung muss anders Reagiert
werden.

Tritt ein Fehler auf, der es noch ermöglicht weiter zu fahren, jedoch umgehend geprüft
werden sollte, so ist Vorgesehen das Fahrzeug in einem Notlaufprogramm weiter zu
betreiben. Dabei wird dann eine Fehlermeldung angezeigt und das Fahrzeug noch mit
verminderter Leistung betrieben. Des Weiteren wird der Fehler gespeichert, so dass auch
bei einem totalen Systemausfall der Fehler weiterhin erscheint.

Sollte hingegen ein kritischer Fehler auftretten, der das sofortige abschalten des
HV-Kreises bedarf, so wird neben der Fehlermeldung das HV-System direkt unterbrochen.
Die HV-Schütze öffenen den HV-Kreis und ein fahren mit dem Fahrzeug ist dann nicht
mehr möglich. 

Somit soll verhindert werden, dass durch einen Fehler im HV-System, Gefahren für
Personen entstehen!

## Mögliche Fehler

Mögliche Fehler im System können sein:
	- Ein Steuergeräte fällt aus
	- Eine HV-Leitung liegt am Fehrzeugrahmen
	- Eine oder mehrere Akkuzellen sind leer
	- Eine oder mehrere Akkuzellen sind zu warm
	- Der Strom im System ist zu hoch
	- Vorladen schlägt fehl
	- Kommunikationsfehler in den Steuergeräten