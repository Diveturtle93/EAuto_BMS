# Shutdown-Circuit – EAuto BMS
 
Der Shutdown-Circuit (SDC) dient der Validierung des HV-Kreises und der HV-Stecker.
Er prüft, ob alle Stecker gesteckt und ob Fehler im System aufgetreten sind.
 
Wird ein Fehler festgestellt oder sind nicht alle Stecker gesteckt, so ist ein
Vorladen des HV-Kreises nicht möglich. Ein Fahren mit dem Fahrzeug ist dann ebenfalls
nicht möglich. Wird allerdings ein Fehler beim Fahren festgestellt, so ist hier noch
eine Priorisierung notwendig. Je nach Fehlerart und -auswirkung muss unterschiedlich
reagiert werden.
 
---
 
## Fehlerverhalten
 
### Leichter Fehler – Notlaufprogramm
 
Tritt ein Fehler auf, der es noch ermöglicht weiter zu fahren, jedoch umgehend geprüft
werden sollte, so ist vorgesehen das Fahrzeug in einem Notlaufprogramm weiter zu
betreiben. Dabei wird eine Fehlermeldung angezeigt und das Fahrzeug noch mit verminderter
Leistung betrieben. Des Weiteren wird der Fehler gespeichert, so dass auch bei einem
totalen Systemausfall der Fehler weiterhin erscheint.
 
### Kritischer Fehler – HV-Abschaltung
 
Sollte hingegen ein kritischer Fehler auftreten, der das sofortige Abschalten des
HV-Kreises erfordert, so wird neben der Fehlermeldung das HV-System direkt unterbrochen.
Die HV-Schütze öffnen den HV-Kreis und ein Fahren mit dem Fahrzeug ist dann nicht
mehr möglich.
 
Somit soll verhindert werden, dass durch einen Fehler im HV-System Gefahren für
Personen entstehen.
 
### Übersicht Fehlerverhalten
 
| Fehlerstufe | Reaktion                                                                          |
|:------------|:----------------------------------------------------------------------------------|
| Leicht      | Notlaufprogramm mit verminderter Leistung, Fehlermeldung, Fehlerspeicherung       |
| Kritisch    | Sofortiges Öffnen der HV-Schütze, Fehlermeldung, Fahrzeug nicht mehr betriebsbereit |
 
---
 
## Mögliche Fehler
 
Mögliche Fehler im System können sein:
 
| Fehler                                          | Priorisierung       |
|:------------------------------------------------|:--------------------|
| Ein Steuergerät fällt aus                       | noch zu definieren  |
| Eine HV-Leitung liegt am Fahrzeugrahmen         | noch zu definieren  |
| Eine oder mehrere Akkuzellen sind leer          | noch zu definieren  |
| Eine oder mehrere Akkuzellen sind zu warm       | noch zu definieren  |
| Der Strom im System ist zu hoch                 | noch zu definieren  |
| Vorladen schlägt fehl                           | noch zu definieren  |
| Kommunikationsfehler in den Steuergeräten       | noch zu definieren  |
 
Diese Fehler müssen noch priorisiert und im Detail ausgewertet werden. Eine erste
Version zeigt Fehler an, reagiert aber noch nicht korrekt.
 
Ebenfalls können noch weitere Fehler auftreten, die bisher nicht in der Liste
aufgeführt sind. Diese werden im weiteren Verlauf des Projektes ergänzt.