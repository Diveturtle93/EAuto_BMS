# EAuto BMS – Batteriemanagement-System
 
Firmware für ein Batteriemanagement-System (BMS) zum Betrieb eines Hochvolt-Akkumulators in einem Elektrofahrzeug,
basierend auf einem **STM32F767ZI** und dem Zellüberwachungs-IC **LTC6811-1** von Analog Devices. Das BMS ist Teil
des Elektrifizierungsprojekts, bei dem ein Dieselfahrzeug auf einen Elektroantrieb umgerüstet wird.
 
## Beschreibung
 
Das BMS überwacht kontinuierlich alle Zellen des Hochvolt-Akkumulators. Es liest Zellspannungen und -temperaturen
über eine isolierte SPI-Schnittstelle aus, verarbeitet diese intern und gibt relevante Daten über den
Antriebs-CAN-Bus aus. Zusätzlich zur Zellüberwachung sind ein HV-Stromsensor, ein Isolationswächter (IMD) und
eine Interlock-Schleife in das System integriert.
 
Das Projekt ist in zwei Bereiche aufgeteilt:
 
- **Core/** – Grundlegende Systeminitialisierung, HAL-Treiber und CubeMX-generierter Code
- **Application/** – BMS-Anwendungslogik: LTC6811-Kommunikation, Zellauswertung, Zustandsmaschine,
CAN-Kommunikation, Fehlerbehandlung

## Hardware
 
| Merkmal              | Beschreibung                                                               |
|----------------------|----------------------------------------------------------------------------|
| Mikrocontroller      | STM32F767ZIT (Cortex-M7, 216 MHz, 2 MB Flash, 512 kB RAM)                 |
| Zellüberwachungs-IC  | LTC6811-1 (bis zu 12 Zellen pro IC, isoSPI-Kommunikation)                 |
| Akkustruktur         | 8–10 Module à 12 Zellen in Reihe (96–120 Zellen gesamt)                   |
| Kommunikation        | Isoliertes SPI (isoSPI) zum LTC6811, CAN3 für Fahrzeugkommunikation       |
| Stromsensor          | HV-Stromsensor mit CAN-Ausgabe (misst Strom und HV-Gesamtspannung)        |
| Isolationswächter    | IMD – überwacht Widerstand zwischen HV-System und Fahrzeugkarosserie       |
| Antriebs-CAN         | CAN3 – 500 kBit/s, sicherheitsrelevante Daten                             |
| Komfort-CAN          | CAN1/CAN2 – aktuell nicht ausgewertet                                      |
| Eingänge             | 13 digitale Eingänge (3,3 V Logikpegel, kurzschlussfest, 0–24 V)          |
| Ausgänge             | 27 digitale Ausgänge (12 V / 24 V, zwei Stromklassen, inkl. PWM-Ausgänge) |
 
## Projektstruktur
 
| Ordner / Datei                 | Beschreibung                                                        |
|--------------------------------|---------------------------------------------------------------------|
| `Core/`                        | CubeMX-generierter Code, HAL-Treiber, Systeminitialisierung         |
| `Application/`                 | BMS-Anwendungslogik: LTC6811, Zellauswertung, CAN, Fehlerbehandlung |
| `Drivers/`                     | STM32 HAL und CMSIS-Treiber                                         |
| `Lib/`                         | Git-Submodule der verwendeten Bibliotheken                          |
| `ADC.md`                       | Dokumentation der ADC-Kanäle mit Pinbelegung                        |
| `CAN.md`                       | CAN-Bus-Dokumentation: Busse, Priorisierung, CAN-ID-Tabelle         |
| `INPUTS.md`                    | Dokumentation aller digitalen Eingänge mit Pinbelegung              |
| `OUTPUTS.md`                   | Dokumentation aller digitalen Ausgänge mit Pinbelegung              |
| `SDC.md`                       | Beschreibung des Shutdown-Circuits und der Fehlerbehandlung         |
| `AD8403.md`                    | Dokumentation des digitalen Potentiometers AD8403                   |
| `BatteriemanagementSystem.ioc` | STM32CubeMX-Projektdatei                                            |
| `STM32F767ZITX_FLASH.ld`       | Linker-Skript für Flash-Betrieb                                     |
| `STM32F767ZITX_RAM.ld`         | Linker-Skript für RAM-Betrieb (Debug)                               |
 
## Zellüberwachung mit LTC6811-1
 
Der **LTC6811-1** überwacht bis zu 12 in Reihe geschaltete Zellen pro IC. Mehrere ICs können über **isoSPI** in einer
Daisy-Chain-Topologie verbunden werden, sodass alle Zellen des gesamten Akkupacks mit einem einzigen SPI-Master
ausgelesen werden können. Die isoSPI-Schnittstelle trennt galvanisch den Mikrocontroller vom Hochvoltsystem.
 
Für jedes Modul werden folgende Werte ermittelt:
 
- Einzelne Zellspannungen (12 Zellen pro Modul)
- Einzelne Zelltemperaturen
- Minimalspannung, Maximalspannung und Gesamtspannung des Moduls
- Minimaltemperatur und Maximaltemperatur des Moduls

## Isolationswächter (IMD)
 
Der IMD überwacht kontinuierlich den Widerstand zwischen dem Hochvoltsystem und der Fahrzeugkarosserie.
Unterschreitet dieser Widerstand einen vorgegebenen Grenzwert, liegt ein Isolationsfehler vor. Da ein
Isolationsfehler eine direkte Gefahr für Leib und Leben darstellt, wird das Fahrzeug unverzüglich abgeschaltet.
Ein Isolationsfehler wird als kritischer Fehler eingestuft.
 
## HV-Stromsensor
 
Der HV-Stromsensor misst den Strom im Hochvoltkreis und gibt die Messwerte über den CAN-Bus aus. Zusätzlich misst
der Sensor unabhängig vom LTC6811 die Gesamtspannung des HV-Systems. Dieser unabhängige Referenzwert ermöglicht eine
Plausibilitätsprüfung: Weicht die vom BMS gemessene Gesamtspannung zu stark von der Sensorspannung ab, kann das
System abgeschaltet werden.
 
## Shutdown-Circuit (SDC)
 
Der SDC validiert den HV-Kreis und prüft, ob alle HV-Stecker gesteckt und keine Fehler im System aufgetreten sind.
Ohne gültigen SDC ist ein Vorladen des HV-Kreises und damit ein Fahrbetrieb nicht möglich.
 
Das Fehlerverhalten ist zweistufig:
 
| Fehlerstufe       | Reaktion                                                                        |
|-------------------|---------------------------------------------------------------------------------|
| Warnung / Leicht  | Notlaufprogramm mit verminderter Leistung, Fehlermeldung, Fehlerspeicherung     |
| Kritisch          | Sofortiges Öffnen der HV-Schütze, Fahrzeug nicht mehr betriebsbereit            |
 
Mögliche Fehlerquellen sind u. a. Steuergeräteausfall, HV-Kurzschluss zur Karosserie, Über-/Unterspannung
einzelner Zellen, Übertemperatur, Überstrom, Vorladefehler und Kommunikationsfehler.
 
Eine ausführliche Beschreibung findet sich in [SDC.md](SDC.md).
 
## CAN-Bus-Architektur
 
Am STM32F767 stehen drei CAN-Interfaces zur Verfügung, von denen zwei eine gemeinsame Registerbank teilen.
Die Buszuweisung erfolgt nach Sicherheitsrelevanz:
 
| Bus   | Interface | Baudrate     | Zweck                                                         |
|-------|-----------|--------------|---------------------------------------------------------------|
| CAN3  | CAN3      | 500 kBit/s   | Antriebs-CAN: sicherheitsrelevante Fahrzeugkommunikation      |
| CAN1  | CAN1/CAN2 | –            | Komfort-CAN (aktuell nicht ausgewertet)                       |
| CAN2  | CAN1/CAN2 | –            | Infotainment-CAN (aktuell nicht ausgewertet)                  |
 
CAN3 hat eine eigene Registerbank und erhält daher die höchste Priorisierung. Alle sicherheitsrelevanten Daten
laufen hier zusammen und werden im BMS verarbeitet.
 
### CAN-IDs (Antriebs-CAN, CAN3)
 
| CAN-ID | Sender             | Empfänger          | Timing [ms] | DLC   |
|--------|--------------------|--------------------|-------------|-------|
| 0x0C2  | Lenkwinkelsensor   | –                  | 10          | 8     |
| 0x181  | Bamocar            | Motorsteuergerät   | 100         | 3–6   |
| 0x1A0  | Bremse             | –                  | 7           | 8     |
| 0x201  | Motorsteuergerät   | Bamocar            | 100         | 3–6   |
| 0x237  | Batteriemanagement | –                  | 200         | 5     |
| 0x238  | Batteriemanagement | –                  | 200         | 4     |
| 0x239  | Batteriemanagement | –                  | 500         | 8     |
| 0x280  | Motorsteuergerät   | Kombiinstrument    | 20          | 8     |
| 0x288  | Motorsteuergerät   | –                  | 20          | 8     |
| 0x320  | Kombiinstrument    | –                  | 20          | 8     |
| 0x380  | Motorsteuergerät   | –                  | 20          | 8     |
| 0x388  | Motorsteuergerät   | –                  | 20          | 3     |
| 0x411  | Batteriemanagement | HV Stromsensor     | auf Anfrage | 8     |
| 0x420  | Kombiinstrument    | –                  | 200         | 8     |
| 0x480  | Motorsteuergerät   | –                  | 20          | 8     |
| 0x488  | Motorsteuergerät   | –                  | 20          | 8     |
| 0x4A0  | Bremse             | –                  | 14          | 8     |
| 0x4A8  | Bremse             | –                  | 20          | 8     |
| 0x511  | HV Stromsensor     | Batteriemanagement | auf Anfrage | 8     |
| 0x520  | Kombiinstrument    | –                  | 200         | 8     |
| 0x521  | HV Stromsensor     | Batteriemanagement | 20          | 8     |
| 0x522  | HV Stromsensor     | Batteriemanagement | 60          | 8     |
| 0x523  | HV Stromsensor     | Batteriemanagement | auf Anfrage | 8     |
| 0x524  | HV Stromsensor     | Batteriemanagement | auf Anfrage | 8     |
| 0x525  | HV Stromsensor     | Batteriemanagement | auf Anfrage | 8     |
| 0x526  | HV Stromsensor     | Batteriemanagement | auf Anfrage | 8     |
| 0x527  | HV Stromsensor     | Batteriemanagement | auf Anfrage | 8     |
| 0x528  | HV Stromsensor     | Batteriemanagement | auf Anfrage | 8     |
| 0x539  | Batteriemanagement | –                  | 500         | 8     |
| 0x560  | Batteriemanagement | –                  | 200         | 4     |
| 0x565  | Batteriemanagement | –                  | 200         | 5     |
| 0x580  | Motorsteuergerät   | –                  | 10          | 8     |
| 0x5A0  | Bremse             | –                  | 14          | 8     |
 
Zusätzlich werden im Debug-Betrieb Zellspannungen ab CAN-ID **0x640** (je 3 Nachrichten à 8 Byte pro Modul) und
Zelltemperaturen ab **0x740** (je 4 Nachrichten à 8 Byte pro Modul) übertragen. Bei bis zu 10 Modulen können bis
zu 70 zusätzliche Nachrichten auf den Bus gelegt werden. Diese Ausgabe ist optional und nur für Diagnosezwecke
vorgesehen.
 
Eine vollständige Beschreibung der CAN-Kommunikation findet sich in [CAN.md](CAN.md).
 
## Digitale Eingänge
 
13 digitale Eingänge, kurzschlussfest, ausgelegt für 0–12 V (sicher bis 24 V), intern auf 3,3 V Logikpegel gewandelt.
Die Eingänge sind in System- (sicherheitsrelevant) und Komforteingänge unterteilt. Sicherheitsrelevante Eingänge
werden häufiger abgefragt und zusätzlich über CAN übertragen.
 
Ausgewählte System-Eingänge:
 
| Funktionsgruppe  | Pin  | Funktion    |
|------------------|------|-------------|
| Shutdown Circuit | PA0  | Crash       |
| Fahrzeug         | PD8  | KL15        |
| Shutdown Circuit | PE3  | HVIL Sense  |
| Shutdown Circuit | PE4  | BTB Sense   |
| Shutdown Circuit | PE5  | Motor Sense |
| Shutdown Circuit | PE8  | IMD OK      |
| Shutdown Circuit | PE9  | IMD PWM     |
| Shutdown Circuit | PF15 | Precharge   |
 
Eine vollständige Pinbelegung findet sich in [INPUTS.md](INPUTS.md).
 
## Digitale Ausgänge
 
27 digitale Ausgänge in zwei Stromklassen, ausgelegt für 12 V / 24 V Fahrzeugspannung. Vier HV-Relais werden über
PWM-Ausgänge angesteuert. Sicherheitsrelevante Ausgänge dürfen im Notbetrieb nicht ausfallen.
 
Ausgewählte System-Ausgänge:
 
| Funktionsgruppe  | Pin  | Funktion             |
|------------------|------|----------------------|
| Shutdown Circuit | PA1  | IMD OK               |
| Shutdown Circuit | PE0  | Freigabe Run         |
| Shutdown Circuit | PE7  | Akku OK              |
| Akkukasten       | PE15 | ISO SPI Enable       |
| Akkukasten       | PD12 | HV- Relais PWM       |
| Akkukasten       | PD13 | HV+ Relais PWM       |
| Akkukasten       | PD14 | HV/ Relais PWM       |
| Akkukasten       | PD15 | HV Charge Relais PWM |
| Akkukasten       | PF13 | Precharge Relais     |
| Akkukasten       | PG2  | HV- Relais           |
| Akkukasten       | PG3  | HV+ Relais           |
| Fahrzeug         | PG15 | AMS I Limit          |
 
Eine vollständige Pinbelegung findet sich in [OUTPUTS.md](OUTPUTS.md).
 
## Git-Submodule
 
Das Projekt bindet folgende Bibliotheken als Git-Submodule im Ordner `Lib/` ein:
 
| Bibliothek                                                                                 | Beschreibung                                   |
|--------------------------------------------------------------------------------------------|------------------------------------------------|
| [STM32_Basicuart](https://github.com/Diveturtle93/STM32_Basicuart)                         | UART-Sende- und Empfangsfunktionen             |
| [STM32_Systeminfo](https://github.com/Diveturtle93/STM32_Systeminfo)                       | Systeminformationen beim Start                 |
| [STM32_Hardfault](https://github.com/Diveturtle93/STM32_Hardfault)                         | Erweiterter HardFault-Handler mit UART-Ausgabe |
| [STM32_Resetreason](https://github.com/Diveturtle93/STM32_Resetreason)                     | Reset-Ursachen-Analyse                         |
| [STM32_DataWatchpointTrigger](https://github.com/Diveturtle93/STM32_DataWatchpointTrigger) | DWT-Zykluszähler für Zeitmessungen             |
| [STM32_Canbus](https://github.com/Diveturtle93/STM32_Canbus)                               | CAN-Bus-Kommunikation mit Ringpuffer           |
| [STM32_Statemaschine](https://github.com/Diveturtle93/STM32_Statemaschine)                 | Zustandsmaschine für den BMS-Betriebszustand   |
 
### Repository klonen (inkl. Submodule)
 
```bash
git clone --recurse-submodules https://github.com/Diveturtle93/EAuto_BMS.git
```
 
Oder nach einem bereits erfolgten Clone:
 
```bash
git submodule update --init --recursive
```
 
## Voraussetzungen
 
- STM32CubeIDE
- STM32CubeMX (optional, zum Öffnen der `.ioc`-Datei)
- [EAuto_Bootloader](https://github.com/Diveturtle93/EAuto_Bootloader) – zuvor auf den Mikrocontroller geflasht

## Abhängigkeiten
 
- `main.h` – STM32 HAL
- [`basicuart.h`](https://github.com/Diveturtle93/STM32_Basicuart) – UART-Sende- und Empfangsfunktionen
- [STM32_Canbus](https://github.com/Diveturtle93/STM32_Canbus) – CAN-Bus-Kommunikation
- [STM32_Statemaschine](https://github.com/Diveturtle93/STM32_Statemaschine) – Zustandsmaschine
- [STM32_Hardfault](https://github.com/Diveturtle93/STM32_Hardfault) – Erweiterter HardFault-Handler
- [STM32_Resetreason](https://github.com/Diveturtle93/STM32_Resetreason) – Reset-Ursachen-Analyse
- [STM32_Systeminfo](https://github.com/Diveturtle93/STM32_Systeminfo) – Systeminformationen beim Start
- [STM32_DataWatchpointTrigger](https://github.com/Diveturtle93/STM32_DataWatchpointTrigger) – DWT-Zykluszähler für Zeitmessungen

## Lizenz
 
Dieses Projekt steht unter der [GPL-3.0 Lizenz](LICENSE).
