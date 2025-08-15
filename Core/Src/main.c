/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "can.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BatteriemanagementSystem.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// TODO:
// FIXME:
// xxx: Schlechte Performance
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// ADC Array
static uint16_t ADC_VAL[8] = {0};

// Fehler Speicher CAN-Bus
uint8_t can_online = 0;

// IMD Variablen fuer Timer
static volatile uint16_t rising = 0, falling = 0;
static volatile uint8_t pwm_change = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void checkSDC(void);
void sortCAN(void);
void setState(uint8_t State);
void setStatus(uint8_t Status);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	// BMS Statemaschine Zeitvariablen
	uint32_t timeStandby = 0, timeErrorLED = 0;
	uint32_t timeZyklus = 0, lasttimeZyklus = 0;

	// BMS Abfrage Zeitvariablen
	uint32_t timeBMSWork = 0;

	// BMS CAN-Bus Zeitvariable
	uint32_t timeBAMO = 0, timeMOTOR = 0, timeStromHV = 0;

	// Zeitvariable Precharge
	uint32_t timePrecharge = 0;

	// CAN-Bus Receive Message
	CAN_message_t RxMessage;

	// Anforderung Motorsteuergeraet Drive-Modus aktivieren
	bool ActivDrive = false;
	Statemaschine mStrg = {{Start, true, false, false, false}};

	// Stromsensor Nachrichten definieren
	stromsensor_ivtmod current;
	stromsensor_ivtmod voltage1;
	stromsensor_ivtmod voltage2;
	stromsensor_ivtmod voltage3;

	// IMD Variablen fuer Berechnung
	uint32_t timer1Periode = 0, timeIMD = 0;

	// Testvariablen
	uint32_t zweisekunden = 0, temp;

	// Backup Data, stored in RTC_Backup Register
//	uint32_t Backup = 0xFFFF;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  MX_USART2_UART_Init();

#ifdef DEBUG
	app_info();
	HAL_Delay(3000);
#endif

#if MOTOR_AVAILIBLE != 1
	#if TISCHAUFBAU == 1
		sdc_in.Anlassen = true;
	#endif
#endif

	uartTransmit("Start\n", 6);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_SPI4_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_SPI1_Init();
  MX_CAN3_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */

//	HAL_PWR_EnableBkUpAccess();
//	Backup = HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0);
//	HAL_PWR_DisableBkUpAccess();

	// Timer 1 fuer IMD PWM-Eingang aktivieren
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK);
	if (HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1) != HAL_OK);
	if (HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2) != HAL_OK);
	timer1Periode = (HAL_RCC_GetPCLK2Freq() / (htim1.Init.Prescaler / 2));

	// CAN-Bus initalisieren
	CANinit(RX_SIZE_16, TX_SIZE_16);
	CAN_config();

	// System Selbsterhaltung einschalten
	system_out.PowerOn = true;

	// BMS initialisieren
	if (bms_init() != false)
	{
		uartTransmit("BMS gestartet\n", 14);
		system_out.AmsOK = true;
		system_out.AmsLimit = true;
	}
	else
	{
		uartTransmit("BMS konnte nicht gestartet werden\n", 34);
		system_out.AmsOK = false;
		system_out.AmsLimit = false;
		setStatus(StateError);
	}

	// IMD Fehler zuruecksetzen bei Systemstart
	system_out.ImdOK = true;

	for (uint8_t j = 0; j < ANZAHL_OUTPUT_PAKETE; j++)
	{
		CAN_Output_PaketListe[j].msg.buf[0] = 0;
		CAN_Output_PaketListe[j].msg.buf[1] = 0;
		CAN_Output_PaketListe[j].msg.buf[2] = 0;
		CAN_Output_PaketListe[j].msg.buf[3] = 0;
		CAN_Output_PaketListe[j].msg.buf[4] = 0;
		CAN_Output_PaketListe[j].msg.buf[5] = 0;
		CAN_Output_PaketListe[j].msg.buf[6] = 0;
		CAN_Output_PaketListe[j].msg.buf[7] = 0;
	}
	
#ifdef DEBUG
	#define MAINWHILE			"\nStarte While Schleife\n"
	uartTransmit(MAINWHILE, sizeof(MAINWHILE));
#endif

	timeZyklus = millis();
	// Nach erfolgreicher Initialisiserung aller Konfigurationen
	setState(Ready);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
#ifdef DEBUG_ZYKLUS
	  uartTransmit("Zykluszeit:\t\t", 13);
	  uartTransmitNumber(millis() - timeZyklus, 10);
	  uartTransmit("\n", 1);
#endif

	  lasttimeZyklus = timeZyklus;
	  timeZyklus = millis();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // Alle Eingaenge einlesen
	  readall_inputs();

	  // Alle ADC einlesen
	  ADC_VAL[0] = ADC_STMTemperatur();
	  ADC_VAL[1] = ADC_PCBTemperatur();
	  ADC_VAL[2] = ADC_KL15();
	  ADC_VAL[3] = ADC_KL30_Relais();
	  ADC_VAL[4] = ADC_Temp1();
	  ADC_VAL[5] = ADC_Temp2();
	  ADC_VAL[6] = ADC_Temp3();
	  ADC_VAL[7] = ADC_Temp4();

	  // Sortiere CAN-Daten auf CAN-Buffer
	  sortCAN();

	  // Lese IMD Status ein
	  // Wenn sich der Pegel am IMD_PWM aendert
	  if (pwm_change == 1)
	  {
		  if (rising != 0 && falling != 0)
		  {
			  // Berechne DutyCycle und Frequenzy von IMD_PWM
			  uint16_t imd_diff = getDifference(rising, falling);
			  imd.DutyCycle = 100 - round((float)(imd_diff * 100) / (float)rising);
			  imd.Frequency = timer1Periode / rising;
		  }

		  if (millis() > (timeIMD + 5000))
		  {
			  imd_status();
			  timeIMD = millis();
		  }

		  pwm_change = 0;
	  }

	  // Lese CAN-Nachrichten ein
	  if (CAN_available() >= 1)
	  {
		  CANread(&RxMessage);

		  switch (RxMessage.id)
		  {
#if BAMOCAR_AVAILABLE == 1
			  // Bamocar ID
			  case BAMOCAR_CAN_RX:
			  {
				  can_online |= (1 << 0);
				  timeBAMO = millis();

				  setStatus(StateNormal);

				  break;
			  }
#endif

#if MOTOR_AVAILABLE == 1
			  // Motorsteuergeraet Status ID
			  case MOTOR_CAN_STATUS:
			  {
				  can_online |= (1 << 1);
				  timeMOTOR = millis();

				  setStatus(StateNormal);

				  mStrg.Status = RxMessage.buf[0];

				  break;
			  }

			  // Motorsteuergeraet Digital Input ID
			  case MOTOR_CAN_DIGITAL_IN:
			  {
				  // TODO: Zuordnung Signal Bit
				  // Abfrage Anlasser, Default 1, Geschaltet 0
				  if (~RxMessage.buf[2] & (1 << 7))
				  {
					  // Anlasser Pin von Motorsteuergeraet abspeichern
					  sdc_in.Anlassen = true;
				  }

				  // Abrage ASR1
				  // FIXME: Pruefen ob wirklich in State ReadyToDrive oder Drive umgeschaltet wird. Nicht das Precharge oder Standby auch einen einfluss haben
				  if ((RxMessage.buf[5] & (1 << 0)) && (mStrg.State & (ReadyToDrive & Drive)))
				  {
					  // DriveMode aktivieren
					  ActivDrive = true;
				  }

				  break;
			  }
#endif

#if STROM_HV_AVAILABLE == 1
			  // Stromwert
			  case STROM_HV_CAN_I:
			  {
				  // Speichern wenn verfuegbar, Zeit zuruecksetzen
				  can_online |= (1 << 2);
				  timeStromHV = millis();

				  // Statemaschine setzen
				  setStatus(StateNormal);

				  // Stromwert uebernehmen
				  // TODO: Umrechnung der Vorzeichenbehafteten Variable
				  current.data[0] = RxMessage.buf[0];
				  current.data[1] = RxMessage.buf[1];
				  current.result = (RxMessage.buf[2] << 24) | (RxMessage.buf[3] << 16) | (RxMessage.buf[4] << 8) | RxMessage.buf[5];
				  break;
			  }

			  // Spannungswert 1
			  case STROM_HV_CAN_U1:
			  {
				  // Spannungswerte uebernehmen
				  // TODO: Umrechnung der Vorzeichenbehafteten Variable
				  voltage1.data[0] = RxMessage.buf[0];
				  voltage1.data[1] = RxMessage.buf[1];
				  voltage1.result = (RxMessage.buf[2] << 24) | (RxMessage.buf[3] << 16) | (RxMessage.buf[4] << 8) | RxMessage.buf[5];
				  break;
			  }

			  // Spannungswert 2
			  case STROM_HV_CAN_U2:
			  {
				  // Spannungswerte uebernehmen
				  // TODO: Umrechnung der Vorzeichenbehafteten Variable
				  voltage2.data[0] = RxMessage.buf[0];
				  voltage2.data[1] = RxMessage.buf[1];
				  voltage2.result = (RxMessage.buf[2] << 24) | (RxMessage.buf[3] << 16) | (RxMessage.buf[4] << 8) | RxMessage.buf[5];
				  break;
			  }

			  // Spannungswert 3
			  case STROM_HV_CAN_U3:
			  {
				  // Spannungswerte uebernehmen
				  // TODO: Umrechnung der Vorzeichenbehafteten Variable
				  voltage3.data[0] = RxMessage.buf[0];
				  voltage3.data[1] = RxMessage.buf[1];
				  voltage3.result = (RxMessage.buf[2] << 24) | (RxMessage.buf[3] << 16) | (RxMessage.buf[4] << 8) | RxMessage.buf[5];
				  break;
			  }
#endif

			  //
			  default:
			  {
				  break;
			  }
		  }
	  }

#if BAMOCAR_AVAILABLE == 1
	  if ((BMSstate.State != Standby) && (millis() > (timeBAMO + CAN_TIMEOUT)))
	  {
		  can_online &= ~(1 << 0);
		  longWarning |= (1 << 0);

		  setStatus(StateWarning);
	  }
#endif

#if MOTOR_AVAILABLE == 1
	  if ((BMSstate.State != Standby) && (millis() > (timeMOTOR + CAN_TIMEOUT)))
	  {
		  can_online &= ~(1 << 1);
		  longWarning |= (1 << 1);

		  setStatus(StateWarning);
	  }
#endif

#if STROM_HV_AVAILABLE == 1
	  if ((BMSstate.State != Standby) && (millis() > (timeStromHV + CAN_TIMEOUT)))
	  {
		  can_online &= ~(1 << 2);
		  longWarning |= (1 << 2);

		  setStatus(StateWarning);
	  }
#endif

	  // Crash Ausgeloest
	  if (system_in.Crash != 1)
	  {
		  // Setze BMS Error Critical und Status auf Ready
		  setStatus(CriticalError);
		  BMSstate.State = Ready;

		  // BMS zuruecksetzen, dass kein HV mehr eingeschaltet werden kann
		  system_out.Freigabe = false;
		  system_out.AmsLimit = false;
		  system_out.AmsOK = false;
		  system_out.ImdOK = false;
		  system_out.Recuperation = false;
		  sdc_in.Anlassen = false;
	  }

	  // Wenn Statemaschine nicht im Standby ist
	  if (BMSstate.State != Standby)
	  {
		  // Schreibe alle CAN-Nachrichten auf BUS, wenn nicht im Standby
		  CANwork();

		  // Shutdown-Circuit checken
		  checkSDC();
		  
		  // TODO: Zellspannungen und -temperaturen in CAN-Nachrichten schreiben
		  // TODO: Timeout fuer LTC6811
		  // BMS-Work Funktion nur alle 100ms aufrufen
		  if (millis() > (timeBMSWork + BMS_WORK_TIME))
		  {
			  bms_work();
			  timeBMSWork = millis();
		  }

		  // 2s Task
		  if (millis() > (zweisekunden + 2000))
		  {
			  uartTransmitNumber(current.result, 10);
			  uartTransmit("\n", 1);
			  uartTransmitNumber(voltage1.result, 10);
			  uartTransmit("\n", 1);

			  zweisekunden = millis();
		  }
	  }

	  // Statemaschine keine Fehler
	  if (BMSstate.Normal)
	  {
		  leuchten_out.RedLed = false;
		  leuchten_out.GreenLed = true;

		  system_out.AmsLimit = true;
	  }

	  // Statemaschine hat Warnungen
	  if (BMSstate.Warning)
	  {
		  if (millis() > (timeErrorLED + 1000))
		  {
			  leuchten_out.RedLed = !leuchten_out.RedLed;
			  timeErrorLED = millis();
		  }

		  leuchten_out.GreenLed = true;
		  system_out.AmsLimit = true;
	  }

	  // Statemaschine hat Error
	  if (BMSstate.Error)
	  {
		  if (millis() > (timeErrorLED + 1000))
		  {
			  leuchten_out.RedLed = !leuchten_out.RedLed;
			  timeErrorLED = millis();
		  }

		  leuchten_out.GreenLed = false;
		  system_out.AmsLimit = false;
	  }

	  // Statemaschine hat Kritische Fehler
	  if (BMSstate.CriticalError)
	  {
		  leuchten_out.RedLed = true;
		  leuchten_out.GreenLed = false;

		  system_out.AmsLimit = false;
	  }

	  // Statemaschine vom Batteriemanagement-System
	  switch(BMSstate.State)
	  {
		  // State Ready, Vorbereiten des Batteriemanagement
		  case Ready:
		  {
			  // Solange kein kritischer Fehler auftritt
			  if (!(BMSstate.CriticalError))
			  {
				  setState(KL15);
			  }

			  break;
		  }

		  // State KL15, wenn Schluessel auf Position 2, KL15 eingeschaltet
		  case KL15:
		  {
			  // Wenn Anlassen aktiviert wird
			  if (sdc_in.Anlassen == true)
			  {
				  // Solange kein kritischer Fehler auftritt
				  if (!(BMSstate.CriticalError))
				  {
					  system_out.AmsOK = true;

					  setState(Anlassen);
				  }
			  }

			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  setState(Standby);
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Anlassen, wenn Schluessel auf Position 3 und keine kritischen Fehler, Anlasser einschalten
		  case Anlassen:
		  {
			  // Wenn Anlassen aktiviert wird
			  if (mStrg.State == Precharge)
			  {
				  // Solange kein kritischer Fehler auftritt
				  if (!(BMSstate.CriticalError))
				  {
					  // Precharge Relais aktivieren
					  highcurrent_out.PrechargeOut = true;

					  setState(Precharge);
					  timePrecharge = millis();
				  }
			  }

			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  setState(Standby);
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Precharge, lade HV-Kreis und warte bis aufgeladen ist
		  case Precharge:
		  {
			  // Wenn Precharge nach 10s nicht Abgeschlossen werden konnte
			  if (millis() > (timePrecharge + 10000))
			  {
				  // Precharge Relais abschalten und kritischer Fehler
				  highcurrent_out.PrechargeOut = false;
				  setStatus(CriticalError);
			  }

			  // Wenn Precharge angeschlossen ist
			  if ((sdc_in.PrechargeIn == 0) && (millis() > (timePrecharge + 5000)))
			  {
				  // HV+ Relais activieren
//				  system_out.HV_P = true;
				  HAL_GPIO_WritePin(PWM_HV_Charger_GPIO_Port, PWM_HV_Charger_Pin, GPIO_PIN_SET);

				  setState(ReadyToDrive);
			  }

			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  if (sdc_in.PrechargeIn == 1)
				  {
					  // Precharge wieder abschalten
					  highcurrent_out.PrechargeOut = false;
				  }

				  setState(Standby);
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State ReadyToDrive, wenn SDC OK ist
		  case ReadyToDrive:
		  {
			  // Nach 10s nach dem Precharge gestartet wurde, wird das Precharge Relais wieder abgeschaltet
			  if (millis() > (timePrecharge + 10000))
			  {
				  highcurrent_out.PrechargeOut = false;
			  }

			  // Sobald ActivDrive aktiviert ist in den Drive Modus gehen und Freigabe an Bamocar senden
			  if (ActivDrive && (highcurrent_out.PrechargeOut == false))
			  {
				  // Freigabe fuer Bamocar aktivieren
				  system_out.Freigabe = true;

				  setState(Drive);
			  }

			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  system_out.Freigabe = false;
				  ActivDrive = false;

				  setState(Standby);
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Drive, wenn Fahrmodus manuell aktiviert wird
		  case Drive:
		  {
			  // Falls KL15 abfaellt und der Schluessel abgezogen wird
			  if (system_in.KL15 == 1)
			  {
				  system_out.Freigabe = false;
				  ActivDrive = false;

				  setState(Standby);
				  timeStandby = millis();
			  }

			  if (mStrg.State == KL15)
			  {
				  ActivDrive = false;
				  setState(ReadyToDrive);
			  }

			  break;
		  }

		  // State Standby, wenn Schluessel gezogen wird, KL15 ausgeschaltet
		  case Standby:
		  {
			  // Fuer 5min warten und BMS weiterhin aktiv halten
			  if (millis() > (timeStandby + BMSTIME))
			  {
				  setState(Ausschalten);
			  }
			  // Falls innerhalb der 5min die KL15 wieder aktiviert wird
			  else if (system_in.KL15 != 1)
			  {
				  setState(Ready);
			  }

			  // Fuer 5s warten bis BMS HV-Relais abschaltet, Anlassen zuruecksetzen
			  if (millis() > (timeStandby + HVRELAISTIME))
			  {
				  sdc_in.Anlassen = false;
				  HAL_GPIO_WritePin(PWM_HV_Charger_GPIO_Port, PWM_HV_Charger_Pin, GPIO_PIN_RESET);
			  }

			  break;
		  }

		  // State Ausschalten, wenn Standby State laenger als 5min dauert
		  case Ausschalten:
		  {
			  // Alle Ausgaenge auf Null setzen
			  system_out.systemoutput = 0;
			  highcurrent_out.high_out = 0;
			  leuchten_out.ledoutput = 0;
			  sdc_in.sdcinput = 0;

			  break;
		  }

		  // Falls kein State zutrifft, dann kritischer Fehler
		  default:
		  {
			  uartTransmit("BMS Kritischer Fehler While\n!", 30);
			  setStatus(CriticalError);

			  break;
		  }
	  }

	  // Alle Ausgaenge schreiben
	  writeall_outputs();
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void checkSDC(void)
{
	sdc_in.SDC_OK = true;

#if IMD_AVAILABLE == 1
	// IMD abfragen, wenn angeschlossen und OK, Pin am uC ist 0, Wenn nicht Pin am uC ist 1
	if (sdc_in.IMD_OK_IN == 1)
	{
		setStatus(StateError);
		sdc_in.SDC_OK = false;
	}
#endif

#if BAMOCAR_AVAILABLE == 1
	// HV-Stecker abfragen
	if (sdc_in.HVIL == 1)
	{
		setStatus(StateError);
		sdc_in.SDC_OK = false;
	}

	// BTB-Eingang abfragen
	if (sdc_in.BTB_SDC == 1)
	{
		setStatus(StateError);
		sdc_in.SDC_OK = false;
	}
#endif

#if MOTOR_AVAILABLE == 1
	// Motor-Eingang abfragen
	if (sdc_in.MotorSDC == 1)
	{
		setStatus(StateWarning);
		sdc_in.SDC_OK = false;
	}
#endif

	if (sdc_in.SDC_OK == 1)
	{
		setStatus(StateNormal);
	}
}

// Sortiere CAN Daten
void sortCAN(void)
{
	// Digital-Ausgaenge
	CAN_Output_PaketListe[1].msg.buf[0] = system_out.systemoutput;
	CAN_Output_PaketListe[1].msg.buf[1] = highcurrent_out.high_out;
	CAN_Output_PaketListe[1].msg.buf[2] = leuchten_out.ledoutput;
	CAN_Output_PaketListe[1].msg.buf[3] = komfort_out.komfortoutput;
	CAN_Output_PaketListe[1].msg.buf[4] = 0;

	// Digital-Eingaenge
	CAN_Output_PaketListe[2].msg.buf[0] = 0;
	CAN_Output_PaketListe[2].msg.buf[1] = system_in.systeminput;
	CAN_Output_PaketListe[2].msg.buf[2] = sdc_in.sdcinput;
	CAN_Output_PaketListe[2].msg.buf[3] = komfort_in.komfortinput;

	// Analogeingaenge
	CAN_Output_PaketListe[3].msg.buf[0] = ADC_VAL[0];
	CAN_Output_PaketListe[3].msg.buf[1] = (ADC_VAL[0] >> 8) | (ADC_VAL[1] << 4);
	CAN_Output_PaketListe[3].msg.buf[2] = (ADC_VAL[1] >> 4);
	CAN_Output_PaketListe[3].msg.buf[3] = ADC_VAL[2];
	CAN_Output_PaketListe[3].msg.buf[4] = (ADC_VAL[2] >> 8) | (ADC_VAL[3] << 4);
	CAN_Output_PaketListe[3].msg.buf[5] = (ADC_VAL[3] >> 4);
	CAN_Output_PaketListe[3].msg.buf[6] = 0;
	CAN_Output_PaketListe[3].msg.buf[7] = 0;

	// Temperatureingaenge
	CAN_Output_PaketListe[4].msg.buf[0] = ADC_VAL[4];
	CAN_Output_PaketListe[4].msg.buf[1] = (ADC_VAL[4] >> 8) | (ADC_VAL[7] << 4);
	CAN_Output_PaketListe[4].msg.buf[2] = (ADC_VAL[5] >> 4);
	CAN_Output_PaketListe[4].msg.buf[3] = ADC_VAL[6];
	CAN_Output_PaketListe[4].msg.buf[4] = (ADC_VAL[6] >> 8) | (ADC_VAL[7] << 4);
	CAN_Output_PaketListe[4].msg.buf[5] = (ADC_VAL[7] >> 4);
	CAN_Output_PaketListe[4].msg.buf[6] = 0;
	CAN_Output_PaketListe[4].msg.buf[7] = 0;

	// Batteriemanagement Status
	CAN_Output_PaketListe[5].msg.buf[0] = BMSstate.Status;
	CAN_Output_PaketListe[5].msg.buf[1] = longWarning;
	CAN_Output_PaketListe[5].msg.buf[2] = longError;
	CAN_Output_PaketListe[5].msg.buf[3] = can_online;

	// IMD Status
	CAN_Output_PaketListe[6].msg.buf[0] = imd.status[0];
	CAN_Output_PaketListe[6].msg.buf[1] = imd.status[1];
	CAN_Output_PaketListe[6].msg.buf[2] = imd.status[2];
	CAN_Output_PaketListe[6].msg.buf[3] = imd.status[3];
	CAN_Output_PaketListe[6].msg.buf[4] = imd.status[4];
}

// Timer Interrupt
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	// Timer 1 fuer IMD PWM-Auswertung
	if (htim == &htim1)
	{
		pwm_change = 1;
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			rising = calculateMovingAverage(rising, HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1), 10);
		}
		else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			falling = calculateMovingAverage(falling, HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_2), 10);
		}
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();														// Interrupts deaktivieren

	// Schalte Fehler LED ein
	leuchten_out.RedLed = 1;												// Setze Variable
	HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);	// Fehler LED einschalten

	// Schalte Ok LED aus
	leuchten_out.GreenLed = 0;												// Zuruechsetzen Variable
	HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);// Fehler LED ausschalten

	// Sende Nachricht auf Uart-Interface
#ifdef DEBUG
#define STRING_ERROR_HANDLER			"Error Handler wird ausgefuehrt!!!"
	uartTransmit(STRING_ERROR_HANDLER, sizeof(STRING_ERROR_HANDLER));
#endif
	// Beginne Endlosschleife nachdem Fehler aufgetreten ist
	while (1)
	{

	}
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
