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
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BasicUart.h"
#include "SystemInfo.h"
#include "LTC6811.h"
#include "LTC1380.h"
#include "outputs.h"
#include "error.h"
#include "inputs.h"
#include "my_math.h"
#include "BatteriemanagementSystem.h"
#include "imd.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
CAN_RxHeaderTypeDef RxMessage;
uint8_t RxData[8], can_change = 0;
static volatile uint16_t rising = 0;
static volatile uint16_t falling = 0;
volatile uint8_t millisekunden_flag_1 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  uint8_t data[36] = {0}, temp, CFG[6] = {0};
  uint32_t tmp;
  uint16_t spannungen[12] = {0}, temperatur[2] = {0}, tmp_mean;
	// Definiere Variablen fuer Main-Funktion
	uint16_t dutyCycle, timerPeriod, frequency, count = 0, R_IMD;
	uint8_t start_flag = 0;

	// Definiere Variablen fuer Main-Funktion
	uint8_t TxData[8], OutData[4], InData[3], status;
  	CAN_FilterTypeDef sFilterConfig;

  	// Erstelle Can-Nachrichten
  	CAN_TxHeaderTypeDef TxMessage = {0x123, 0, CAN_RTR_DATA, CAN_ID_STD, 8, DISABLE};
  	CAN_TxHeaderTypeDef TxOutput = {BMS_CAN_DIGITAL_OUT, 0, CAN_RTR_DATA, CAN_ID_STD, 4, DISABLE};
  	CAN_TxHeaderTypeDef TxInput = {BMS_CAN_DIGITAL_IN, 0, CAN_RTR_DATA, CAN_ID_STD, 3, DISABLE};
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

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
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

	/* Schreibe Resetquelle auf die Konsole */
#ifdef DEBUG
	printResetSource(readResetSource());

	/* Teste serielle Schnittstelle*/
	#define TEST_STRING_UART		"\nUART2 Transmitting in polling mode, Hello Diveturtle93!\n"
	uartTransmit(TEST_STRING_UART, sizeof(TEST_STRING_UART));

  	// Sammel Systeminformationen
  	collectSystemInfo();
#endif

	// Leds Testen
	testPCB_Leds();

  	// Lese alle Eingaenge
  	readall_inputs();

  	// IsoSPI einschalten, Isolierte Spannungsversorgung IsoSPI und HV-Precharge Messung einschalten
  	ISOSPI_ENABLE();

  	// Warten fuer eine kurze Zeit
  	HAL_Delay(20);

    uartTransmit("\n", 1);
#define TEST_LTC6811	"Starte Batteriemanagement-System\n"
    uartTransmit(TEST_LTC6811, sizeof(TEST_LTC6811));

	if ((temp = ltc6811_check()) != 0)									// LTC6804 Selftest durchfuehren
	{
#define LTC6811_FAILED	"Selbsttest LTC6811 fehlerhaft\n"
		uartTransmit(LTC6811_FAILED, sizeof(LTC6811_FAILED));			// Ausgabe bei Fehlerhaftem Selbsttest
		leuchten_out.RedLed = 1;										// Variable setzen
	    HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);// Ausgabe auf LEDs

	    uartTransmitNumber(temp, 10);
		uartTransmit("\n", 1);

		return 0;														// Programm abbrechen
	}
	else
	{
#define LTC6811_PASSED	"Selbsttest LTC6811 erfolgreich\n"
		uartTransmit(LTC6811_PASSED, sizeof(LTC6811_PASSED));			// Ausgabe bei Erfolgreichem Selbsttest
	}

    // LTC6811 initialisieren
	CFG[0] = 0xF8;
	CFG[1] = 0xCF;
	CFG[2] = 0x17;
	CFG[3] = 0xA4;
	CFG[4] = 0x00;
	CFG[5] = 0x00;
	ltc6811_write(WRCFG, &CFG[0]);

	/*ltc6811_read(RDCFG, &data[10]);
	for (uint8_t i = 0; i < 8; i++)
	{
		uartTransmitNumber(data[10+i], 10);
	}
	uartTransmit(";", 1);*/

	// Alle Register zuruecksetzen
	ltc6811(CLRCELL);
	ltc6811(CLRSTAT);
	ltc6811(CLRAUX);

	// Erster ADC Vorgang ist ungueltig
	ltc6811(ADCVAX | MD73 | CELLALL);									// Initial Command Zellen auslesen

	tmp_mean = 65535;
	timerPeriod = (HAL_RCC_GetPCLK2Freq() / htim1.Init.Prescaler);
  	// Start timer
	if (HAL_TIM_Base_Start_IT(&htim1) != HAL_OK);
	if (HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1) != HAL_OK);
	if (HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2) != HAL_OK);
  	HAL_TIM_Base_Start_IT(&htim6);

  	// Starte CAN Bus
  	if((status = HAL_CAN_Start(&hcan3)) != HAL_OK)
  	{
  		/* Start Error */
  		hal_error(status);
  		Error_Handler();
  	}
  	uartTransmit("CAN START\n", 10);

  	// Aktiviere Interrupts für CAN Bus
  	if((status = HAL_CAN_ActivateNotification(&hcan3, CAN_IT_RX_FIFO0_MSG_PENDING)) != HAL_OK)
  	{
  		/* Notification Error */
  		hal_error(status);
  		Error_Handler();
  	}
  	uartTransmit("Send Message\n", 13);

  	// Filter Bank initialisieren um Daten zu empfangen
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = 0;
    sFilterConfig.FilterActivation = ENABLE;

    // Filter Bank schreiben
    if((status = HAL_CAN_ConfigFilter(&hcan3, &sFilterConfig)) != HAL_OK)
    {
    	/* Filter configuration Error */
  		hal_error(status);
  		Error_Handler();
    }

    // Test CAN Nachricht beschreiben
    for (uint8_t j = 0; j < 8; j++)
    {
    	TxData[j] = (j + 1);
    }

	if (!(sdc_in.sdcinput && 0b00001111))										// SDC OK; Motor, BTB, IMD und HVIL OK
	{
		#define SDC_STRING_ERROR			"\nSDC ist nicht geschlossen"
		uartTransmit(SDC_STRING_ERROR, sizeof(SDC_STRING_ERROR));

		// LEDs setzen bei SDC Fehler
		leuchten_out.GreenLed = 0;
		leuchten_out.RedLed = 1;
		leuchten_out.AkkuErrorLed = 0;
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);
		HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);
		HAL_GPIO_WritePin(AKKU_LED_GPIO_Port, AKKU_LED_Pin, leuchten_out.AkkuErrorLed);

		// Ausgabe welcher Fehler vorhanden
		// Motorsteuergeraet Fehler
		if(!(sdc_in.MotorSDC == 1))
		{
			#define SDC_STRING_MOTOR		"\nSDC Motor hat einen Fehler und ist offen"
			uartTransmit(SDC_STRING_MOTOR, sizeof(SDC_STRING_MOTOR));
		}

		// BamoCar Fehler
		if (!(sdc_in.BTB_SDC == 1))
		{
			#define SDC_STRING_BTB			"\nSDC BTB hat einen Fehler und ist offen"
			uartTransmit(SDC_STRING_BTB, sizeof(SDC_STRING_BTB));
		}

		// HVIL Fehler
		if (!(sdc_in.HVIL == 1))
		{
			#define SDC_STRING_HVIL			"\nSDC HVIL ist nicht geschlossen"
			uartTransmit(SDC_STRING_HVIL, sizeof(SDC_STRING_HVIL));
		}

		// IMD Fehler
		if (!(sdc_in.IMD_OK_IN == 1))
		{
			#define SDC_STRING_IMD			"\nSDC IMD hat einen Fehler"
			uartTransmit(SDC_STRING_IMD, sizeof(SDC_STRING_IMD));
		}
	}
	else
	{
		// Keine Fehler, LEDs fuer OK setzen
		system_out.AmsOK = 1;
		HAL_GPIO_WritePin(AMS_OK_GPIO_Port, AMS_OK_Pin, system_out.AmsOK);
		leuchten_out.GreenLed = 1;
		HAL_GPIO_WritePin(GREEN_LED_GPIO_Port, GREEN_LED_Pin, leuchten_out.GreenLed);

		// Ausgabe SDC geschlossen
		#define SDC_STRING_OK				"\nSDC ist geschlossen"
		uartTransmit(SDC_STRING_OK, sizeof(SDC_STRING_OK));
	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		/*ltc6811(ADCVC | MD73 | CELLALL);
		HAL_Delay(100);

		ltc6811_read(RDCVA, &data[0]);
		ltc6811_read(RDCVB, &data[6]);
		ltc6811_read(RDCVC, &data[12]);
		ltc6811_read(RDCVD, &data[18]);

		uartTransmit("Spannungen\n", 11);

		for (uint8_t i = 0; i < 12; i++)
		{
			spannungen[i] = ((data[i*2+1]<<8) | data[i*2]);
		}

		for (uint8_t i = 0; i < 12; i++)
		{
			uartTransmitNumber(spannungen[i], 10);
			uartTransmit(";", 1);
		}

		tmp = 0;
		for (uint8_t i = 0; i < 12; i++)
		{
			tmp += spannungen[i];
		}
		tmp /= 12;
		uartTransmitNumber(tmp, 10);
		uartTransmit(";", 1);

		tmp_mean = calculateMovingAverage(tmp_mean, tmp, 10);
		uartTransmitNumber(tmp_mean, 10);

		uartTransmit("\n", 1);

		uartTransmit("Temperaturen\n", 13);

		for (uint8_t j = 0; j < 8; j++)
		{
			ltc1380_write(LTC1380_MUX0, j);									// Multiplexer 0 einstellen
			ltc1380_write(LTC1380_MUX2, j);									// Multiplexer 1 einstellen
			ltc6811(ADAX | MD73 | GPIOALL);									// Initial Command Zellen auslesen
			ltc6811_read(RDAUXA, &data[0]);

			for (uint8_t i = 0; i < 3; i++)
			{
				temperatur[i] = ((data[i*2+1]<<8) | data[i*2]);
			}
			uartTransmitNumber(temperatur[0], 10);
			uartTransmit(";", 1);
			uartTransmitNumber(temperatur[1], 10);
			uartTransmit(";", 1);

			if (j == 7)
			{
				uartTransmitNumber(temperatur[2], 10);
				uartTransmit(";", 1);
			}
		}

		uartTransmit("\n", 1);

		temp++;*/

		// Task wird jede Millisekunde ausgefuehrt
		if (millisekunden_flag_1 == 1)
		{
			count++;													// Zaehler count hochzaehlen
			millisekunden_flag_1 = 0;									// Setze Millisekunden-Flag zurueck

			// Setzen des Start Flags,  damit Tasks nur einmal pro ms aufgerufen werden kann
			start_flag = 1;												// Setze Start Flag
		}

		// Task wird alle 500 Millisekunden ausgefuehrt
		if (((count % 500) == 0) && (start_flag == 1))
		{
			if (rising != 0 && falling != 0)
			{
				int diff = getDifference(rising, falling);
				dutyCycle = round((float)(diff * 100) / (float)rising);	// (width / period ) * 100
				frequency = timerPeriod / rising;						// timer restarts after rising edge so time between two rising edge is whatever is measured
			}
			else
			{
				dutyCycle = 0;
				frequency = 0;
			}

			uartTransmitNumber(dutyCycle, 10);
			uartTransmitNumber(frequency, 10);

			if (sdc_in.IMD_OK_IN == 1)
			{
				switch (frequency)
				{
					case 0:
						system_in.IMD_PWM = HAL_GPIO_ReadPin(IMD_PWM_GPIO_Port, IMD_PWM_Pin);						// Eingang IMD PWM
						if (system_in.IMD_PWM == 1)
						{
							system_in.IMD_PWM_STATUS = IMD_KURZSCHLUSS_KL15;
						}
						else
						{
							system_in.IMD_PWM_STATUS = IMD_KURZSCHLUSS_GND;
						}
						break;
					case 10:
						system_in.IMD_PWM_STATUS = IMD_NORMAL;
						if (dutyCycle > 5 && dutyCycle < 95)								// IMD PWM
						{
							R_IMD = 90 * 1200 / (dutyCycle - 5) - 1200;
							uartTransmitNumber(R_IMD, 10);
						}
						else																// IMD Invalid
						{
							system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;
						}
						break;
					case 20:
						system_in.IMD_PWM_STATUS = IMD_UNTERSPANNUNG;
						if (dutyCycle > 5 && dutyCycle < 95)								// IMD PWM
						{
							R_IMD = 90 * 1200 / (dutyCycle - 5) - 1200;
							uartTransmitNumber(R_IMD, 10);
						}
						else																// IMD Invalid
						{
							system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;
						}
						break;
					case 30:
						system_in.IMD_PWM_STATUS = IMD_SCHNELLSTART;
						if (dutyCycle > 5 && dutyCycle < 11)								// IMD Gut
						{

						}
						else if (dutyCycle > 89 && dutyCycle < 95)							// IMD Schlecht
						{

						}
						else																// IMD Fehlerhaft
						{
							system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;
						}
						break;
					case 40:
						system_in.IMD_PWM_STATUS = IMD_GERAETEFEHLER;
						if (dutyCycle > 47 && dutyCycle < 53)								// IMD PWM
						{

						}
						else																// IMD Invalid
						{
							system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;
						}
						break;
					case 50:
						system_in.IMD_PWM_STATUS = IMD_ANSCHLUSSFEHLER_ERDE;
						if (dutyCycle > 47 && dutyCycle < 53)								// IMD PWM
						{

						}
						else																// IMD Invalid
						{
							system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;
						}
						break;																// IMD Error, kein anderes Ereignis zutrefend
					default:
						system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;
						break;
				}
			}
			else
			{
				switch (frequency)
				{

					case 10:
						system_in.IMD_PWM_STATUS = IMD_NORMAL;
						if (dutyCycle > 5 && dutyCycle < 95)								// IMD PWM
						{
							R_IMD = 90 * 1200 / (dutyCycle - 5) - 1200;
							uartTransmitNumber(R_IMD, 10);
						}
						else																// IMD Invalid
						{
							system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;
						}
						break;
					case 20:
						system_in.IMD_PWM_STATUS = IMD_UNTERSPANNUNG;
						if (dutyCycle > 5 && dutyCycle < 95)								// IMD PWM
						{
							R_IMD = 90 * 1200 / (dutyCycle - 5) - 1200;
							uartTransmitNumber(R_IMD, 10);
						}
						else																// IMD Invalid
						{
							system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;
						}
						break;																// IMD Error, kein anderes Ereignis zutrefend
					default:
						system_in.IMD_PWM_STATUS = IMD_FREQ_ERROR;
						break;
				}
			}
	
			count = 0;
		}
		
		if ((count % 250) == 0)
		{
			// Daten fuer Ausgaenge zusammenfuehren
			OutData[0] = system_out.systemoutput;
			OutData[1] = highcurrent_out.high_out;
			OutData[2] = leuchten_out.ledoutput;
			OutData[3] = komfort_out.komfortoutput;
	
			// Sende Nachricht digitale Ausgaenge
			status = HAL_CAN_AddTxMessage(&hcan3, &TxOutput, OutData, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);

			// Daten fuer Eingaenge zusammenfuehren
			InData[0] = system_in.systeminput;
			InData[1] = sdc_in.sdcinput;
			InData[2] = komfort_in.komfortinput;
	
			// Sende Nachricht digitale Eingaenge
			status = HAL_CAN_AddTxMessage(&hcan3, &TxInput, InData, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);
	
			// Sende Nachricht digitale Eingaenge
			status = HAL_CAN_AddTxMessage(&hcan3, &TxMessage, TxData, (uint32_t *)CAN_TX_MAILBOX0);
			hal_error(status);
		}

		// Zuruecksetzen des Start Flags, damit Tasks erst nach einer ms wieder aufgerufen werden kann
		start_flag = 0;																		// Zuruechsetze Start Flag
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
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
// Interrupts
// Can-Interrupt: Nachricht wartet
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, RxData);
	can_change = 1;
}

// Timer-Interrupt: Timer ist uebergelaufen
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	// Kontrolliere welcher Timer den Ueberlauf ausgeloest hat
	if (htim == &htim6)
	{
		millisekunden_flag_1 = 1;
	}

	// Timer IMD
	if (htim == &htim1)
	{
		if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
		{
			rising = calculateMovingAverage(rising, HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_1), 64);
		}
		else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
			falling = calculateMovingAverage(falling, HAL_TIM_ReadCapturedValue(&htim1, TIM_CHANNEL_2), 64);
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

#ifdef  USE_FULL_ASSERT
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
