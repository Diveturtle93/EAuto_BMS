# EAuto BMS – Batteriemanagement-System

Firmware für das Batteriemanagement-System (BMS) eines zum Elektroauto umgebauten
Fahrzeugs. Das BMS sitzt im Akkukasten, überwacht alle Zellen über LTC6811-1-Bausteine
und steuert die HV-Relais, den Vorladekreis und den Shutdown-Circuit. Es läuft auf einem
STM32F767ZI und kommuniziert über CAN mit dem Motorsteuergerät, dem Stromsensor und dem
Kombiinstrument.

## Beschreibung

Beim Umbau wird der Dieselmotor gegen einen Elektromotor getauscht. Die Energie liefert
ein Akku aus acht bis zehn Modulen mit je zwölf in Reihe geschalteten Zellen. Damit
keine Zelle überladen, tiefentladen oder zu warm wird, müssen alle Zellen ständig
überwacht werden.

Das BMS liest dazu über eine isolierte SPI-Schnittstelle (isoSPI) die Zellspannungen und
-temperaturen aller Module ein. Durch die Isolation können die Daten auch an Bausteine
mit einem anderen Spannungsbezugspunkt übertragen werden. Aus den Messwerten ermittelt
das BMS die minimale und maximale Zellspannung und -temperatur sowie die Modul- und
Gesamtspannung.

Neben den Zellen übernimmt das BMS weitere Aufgaben:

- **Isolationswächter (IMD):** Der IMD prüft den Widerstand zwischen HV-System und
  Karosserie. Fällt er unter den vorgegebenen Wert, liegt ein Isolationsfehler vor. Das
  ist ein kritischer Fehler, denn er gefährdet Leib und Leben. Das Fahrzeug darf dann
  nicht betrieben werden und das System schaltet sofort ab.
- **Stromsensor:** Der Stromsensor misst den HV-Strom und bis zu drei Spannungen im
  HV-System und sendet sie per CAN an das BMS. Das BMS nutzt sie zur Auswertung und um
  die eigenen Messwerte auf Plausibilität zu prüfen.
- **Shutdown-Circuit:** Interlock-Schleife über HV-Stecker, IMD und Crash-Sensor, siehe
  [docs/SDC.md](docs/SDC.md).
- **Ladestandsanzeige:** Der Ladestand wird über ein digitales Potentiometer (AD8403) auf
  der Tankanzeige des Kombiinstruments ausgegeben.

## Hardware

| Eigenschaft | Wert |
|---|---|
| Mikrocontroller | STM32F767ZIT6 (Cortex-M7, LQFP144) |
| Takt | 25-MHz-Quarz (HSE), SYSCLK 216 MHz, APB1 54 MHz, APB2 108 MHz |
| Zellüberwachung | LTC6811-1 je Modul, angebunden über isoSPI, Temperatur-Multiplexer LTC1380 |
| Ladestandsanzeige | AD8403 (digitales Potentiometer, 4 Kanäle, 1 kΩ) |
| Isolationswächter | IR155-3204, PWM-Signal an PE9 |
| Platinen-Revision | wird per `REVISION` unterschieden, Abfrage in `BatteriemanagementSystem.h` derzeit auskommentiert |

Die Pinbelegung steht in [docs/INPUTS.md](docs/INPUTS.md), [docs/OUTPUTS.md](docs/OUTPUTS.md)
und [docs/ADC.md](docs/ADC.md). Die vollständige Konfiguration liegt in
[BatteriemanagementSystem.ioc](BatteriemanagementSystem.ioc) (STM32CubeMX,
Firmware-Paket STM32Cube FW_F7 V1.17.4).

## Bauen und Flashen

- **Toolchain:** STM32CubeIDE (GNU Arm Embedded), Projekt `BatteriemanagementSystem`.
- **Bibliotheken holen:** Die Bibliotheken unter `Lib/` sind Git-Submodule. Nach dem
  Klonen einmalig ausführen:

  ```sh
  git submodule update --init --recursive
  ```

- **Build-Konfigurationen:**

  | Konfiguration | Zweck |
  |---|---|
  | `Debug` | Entwicklung, `DEBUG` gesetzt: Versionsausgabe und Meldungen über UART |
  | `Release` | ohne `DEBUG`, keine Debug-Ausgaben |
  | `Test` | wie `Debug` mit `DEBUG`, eigener Build-Ordner `Test/` |

- **Aufbau wählen:** In `Application/Inc/BatteriemanagementSystem.h` vor dem Build
  festlegen, für welchen Aufbau kompiliert wird:

  | Define | Bedeutung |
  |---|---|
  | `TISCHAUFBAU` | `1` = Tischaufbau, `0` = Fahrzeug |
  | `BMS_VORNE` / `BMS_HINTEN` | vorderer oder hinterer Akkukasten, nie beide |
  | `MOTOR_AVAILABLE`, `IMD_AVAILABLE`, `BAMOCAR_AVAILABLE`, `STROM_HV_AVAILABLE`, `KOMBIINSTRUMENT_AVAILABLE` | angeschlossene Steuergeräte, `1` = vorhanden |

- **Git-Informationen:** `Make/git.mk` erzeugt beim Build `Application/Inc/git.h` mit
  Commit, Branch und Tag. Die Datei steht in der `.gitignore`.
- **Flashen:** über ST-Link (SWD) aus STM32CubeIDE mit den Startkonfigurationen
  `BatteriemanagementSystem Debug.launch`, `… Release.launch` und `… Test.launch`.
  Linker-Skripte: `STM32F767ZITX_FLASH.ld` (Flash) und `STM32F767ZITX_RAM.ld` (RAM).

## Schnittstellen

| Schnittstelle | Pins | Einstellung | Verwendung |
|---|---|---|---|
| CAN3 | PA15 (TX), PA8 (RX) | 500 kbit/s | Antriebs-CAN: Motorsteuergerät, Stromsensor, Bamocar, Kombiinstrument |
| CAN1 | PD1 (TX), PD0 (RX) | 843,75 kbit/s (CubeMX-Vorgabe) | Komfort-CAN, derzeit ungenutzt |
| SPI4 | PE12 (SCK), PE13 (MISO), PE14 (MOSI), PE11 (CS) | Master, 8 Bit, CPOL high, CPHA 2. Flanke, 843,75 kbit/s | isoSPI zu den LTC6811 |
| SPI1 | PG11 (SCK), PD7 (MOSI), PG10 (NSS) | Master, 8 Bit, CPOL low, CPHA 1. Flanke, 843,75 kbit/s | AD8403 |
| USART2 | PD5 (TX), PD6 (RX) | 115200 Baud, 8N1 | Debug-Ausgabe |
| SWO | PB3 | – | Debug-Ausgabe über ITM |

Die Botschaften auf dem CAN-Bus stehen in [docs/CAN.md](docs/CAN.md).

## Funktionsumfang

- Zellspannungen und -temperaturen aller Module zyklisch einlesen (alle 100 ms)
- Minimal-, Maximal-, Modul- und Gesamtspannung berechnen
- Zustandsautomat Ready → KL15 → Anlassen → Precharge → ReadyToDrive → Drive → Standby → Ausschalten
- Vorladen des HV-Kreises mit Zeitüberwachung (Abbruch nach 10 s)
- Shutdown-Circuit und Crash-Eingang auswerten
- IMD-PWM auswerten (Tastgrad und Frequenz über TIM1 Input Capture)
- Stromsensor über CAN einlesen, Über- und Unterspannung prüfen
- CAN-Timeout-Überwachung der Steuergeräte (10 s)
- Ausgabe von Status, Ein-/Ausgängen, Analogwerten, Temperaturen und Zelldaten auf CAN
- Selbsterhaltung: 5 min nach Abschalten von KL15 in den Zustand Ausschalten

## Dokumente

| Dokument | Inhalt |
|---|---|
| [ARCHITECTURE.md](ARCHITECTURE.md) | Aufbau der Firmware, Datenfluss, Ressourcen und Nebenläufigkeit |
| [docs/README.md](docs/README.md) | Übersicht der Fachdokumente |
| [docs/ADC.md](docs/ADC.md) | AD-Kanäle, Pins, Abtastung und Standardwerte |
| [docs/AD8403.md](docs/AD8403.md) | Digitales Potentiometer für die Ladestandsanzeige |
| [docs/CAN.md](docs/CAN.md) | CAN-Busse und Botschaften |
| [docs/INPUTS.md](docs/INPUTS.md) | Digitale Eingänge und Standardwerte |
| [docs/OUTPUTS.md](docs/OUTPUTS.md) | Digitale Ausgänge |
| [docs/SDC.md](docs/SDC.md) | Shutdown-Circuit und mögliche Fehler |

## Hinweise

- `TISCHAUFBAU` steht im Repository auf `1`. Für den Einbau ins Fahrzeug auf `0` setzen,
  der Compiler warnt bei jedem Build, für welchen Aufbau kompiliert wurde.
- Das Submodul `Lib/STM32_Basicuart` ist in der `.gitmodules` eingetragen, muss aber nach
  dem Klonen mit `git submodule update --init` geholt werden, sonst fehlt `BasicUart.h`.

## Quellen

- [STM32F767ZI – Datenblatt und Referenzhandbuch](https://www.st.com/en/microcontrollers-microprocessors/stm32f767zi.html)
- [LTC6811-1 – Datenblatt](https://www.analog.com/en/products/ltc6811-1.html)
- [AD8403 – Datenblatt](https://www.analog.com/en/products/ad8403.html)

## Abhängigkeiten

| Bibliothek | Tag | Zweck |
|---|---|---|
| [STM32_Basicuart](https://github.com/Diveturtle93/STM32_Basicuart) | – | UART-Ausgabe |
| [STM32_Canbus](https://github.com/Diveturtle93/STM32_Canbus) | – | CAN-Kommunikation mit Ringpuffer und Paketliste |
| [STM32_DataWatchpointTrigger](https://github.com/Diveturtle93/STM32_DataWatchpointTrigger) | – | Laufzeitmessung |
| [STM32_Hardfault](https://github.com/Diveturtle93/STM32_Hardfault) | – | Auswertung von Hardfaults |
| [STM32_Resetreason](https://github.com/Diveturtle93/STM32_Resetreason) | – | Ursache des letzten Resets |
| [STM32_Statemaschine](https://github.com/Diveturtle93/STM32_Statemaschine) | – | Zustandsautomat und Fehlerstatus |
| [STM32_Systeminfo](https://github.com/Diveturtle93/STM32_Systeminfo) | – | Ausgabe von Software- und Hardwareinformationen |
| [STM32_AD8403](https://github.com/Diveturtle93/STM32_AD8403) | – | Digitales Potentiometer |
| [STM32_LTC6811](https://github.com/Diveturtle93/STM32_LTC6811) | – | Zellüberwachung über isoSPI, LTC1380 |
| [IMD_IR155_3204](https://github.com/Diveturtle93/IMD_IR155_3204) | – | Isolationswächter |

Die Bibliotheken haben noch keinen Tag. Sie werden als Submodul von `main` eingebunden,
die Spalte `Tag` wird mit dem ersten Release der jeweiligen Bibliothek gefüllt.

Außerdem: STM32F7 HAL und CMSIS von ST (`Drivers/`).

## Lizenz

Dieses Projekt steht unter der [GPL-3.0 Lizenz](LICENSE).
