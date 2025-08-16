# **ADC Zuweisung**

Es sind sechs Kanäle für die ADC Auswertung vorgesehen. Jedem Kanal ist eine entsprechende
Priorisierung und ein dafür vorgesehenes Timing zugewiesen. Die Priorisierung ist von eins
bis sechs (wichtig bis unwichtig) aufgelistet. System relevante Signale bekommen eine hohe
Priorität, Signale die eher dem Komfort dienen eine niedrige Priorität. Zusätzlich ist
die Pinbelegung und die Aufgabe mit aufgeführt.

Der AD-Wandler kann nur mit einer maximalen Frequenz von 2.4 MHz Konversationen durchführen.
Bei einer APB2-Frequenz von 108 MHz muss noch ein Vorteiler gewählt werden, um den
AD-Wandler wieder mit einem zulässigen Clock zu betreiben. Gewählt wird hier der Teiler
vier. Mit diesem läuft der AD-Wandler nun mit einer Frequenz von 27 MHz.

Alle Ergbnisse werden als 12bit ausgegeben.

## Liste der AD-Kanäle

| Kanal | Pin | Funktion | Timing | Priorisierung |
|:----- |:---:|:-------- | ------:|:-------------:|
| Channel 3 | PA3 | Temperatur 1 | 5000ms | 3 |
| Channel 4 | PA4 | Temperatur 2 | 5000ms | 4 |
| Channel 5 | PA5 | Temperatur 3 | 5000ms | 5 |
| Channel 6 | PA6 | Temperatur 4 | 5000ms | 6 |
| Channel 7 | PA7 | PCB Temperatur | 5000ms | 1 |
| Channel 18 | Temperatur Sensor | STM32 Temperatur | 1000ms | 2 |

## Priorisierung der AD-Kanäle

Die Priorisierung dient dazu die Wichtigkeit eins Signales festzulegen. Diese müssen im
Programm entsprechend deutlich häufiger eingelesen und ausgewertet werden. Zudem können
Signale mit eine niedrigen Priorisierung auch wärend des Programmablaufes vernachlässigt
werden, sollte dies den Programmablauf stören.

## Zeitliches Timing der einzelnen Konversationen

Das zeitliche Timing gibt an wie oft ein Signal ausgewertet werden muss. Dabei ist wichtig
eine dynamische Veränderung des Signales mit zu berücksichtigen. So sind schnell veränderbare
Signale deutlich häufiger ausgewertet als langsame Temperaturanstiege.

## Pinbeschreibung

Im nachfolgenden werden die Aufgaben der Pins beschrieben. Dabei werden insgesamt nur
Temperaturen gemessen. Vier Temperaturen davon kommen von den Heizungen, die zwischen den
Akkuzellen des Akkukastens verbaut werden. Die anderen beiden Messungen sind auf der Platine.

Das sind einmal der STM32 selbst und ein Temperatursensor neben dem DC/DC-Wandler.

## Sampletime Cycles

Eine zusätzliche Einstellung wird noch an den Sampletime Cycles vorgenommen. Dies ist eine
Zeitverzögerung, die für ein genaueres Ergebnis sorgen soll. Dabei wird der halte Konensator
um die entsprechenden Clock-Cycles geladen. Danach werden nochmal zwölf Clock-Cycles
für eine Konversation des AD-Wertes benötigt.

## ADC-Werte

Nachfolgend werden im weiten Verlauf die ADC-Werte dokumentiert, welche standardmäßig an
den ADC-Eingängen anliegen. Zusätzlich werden noch für die Auswertung wichtige ADC-Werte
mit berücksichtigt. Auch diese sollen mit aufgefürt werden.

| Kanal | Funktion | Default-Wert |
|:----- |:-------- | ------------:|
| Channel 3 | Temperatur 1 | ... |
| Channel 4 | Temperatur 2 | ... |
| Channel 5 | Temperatur 3 | ... |
| Channel 6 | Temperatur 4 | ... |
| Channel 7 | PCB Temperatur | 2050 |
| Channel 18 | STM32 Temperatur | 965 |

Diese Werte sind nur durch eine einzige ADC-Messung ermittelt worden. Sie schwanken bedingt
durch Messungenauigkeiten mit einer Genauigkeit von +/- 10 um den ermittelten Wert.