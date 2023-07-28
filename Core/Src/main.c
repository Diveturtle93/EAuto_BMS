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
#include "BatteriemanagementSystem.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// TODO:
// FIXME: CAN Bus (CAN-Bus braucht Ablaufprogramm)
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
	BMS_states BMS_state = {Start, true, false, false, false};

	uint32_t timeStandby = 0, timeError = 0;

	uint8_t can_online = 0;
	uint32_t timeBAMO = 0, timeMOTOR = 0;
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

	uartTransmit("Start\n", 6);

#ifdef DEBUG
	app_info();
	HAL_Delay(3000);
#endif
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN1_Init();
  MX_SPI4_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_SPI1_Init();
  MX_CAN3_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

#ifdef DEBUG
	#define MAINWHILE			"\nStarte While Schleife\n"
	uartTransmit(MAINWHILE, sizeof(MAINWHILE));

	uartTransmit("Ready\n", 6);
#endif

	CANinit(RX_SIZE_16, TX_SIZE_16);
	CAN_config();
	system_out.Power_On = true;
	BMS_state.States = Ready;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // Alle Eingaenge einlesen
	  readall_inputs();

	  // Alle ADC einlesen
	  // TODO: ADCs

	  // Shutdown-Circuit checken
	  // checkSDC();

	  if (millis() > (timeBAMO + CAN_TIMEOUT))
	  {
		  can_online &= ~(1 << 0);
	  }
	  if (millis() > (timeMOTOR + CAN_TIMEOUT))
	  {
		  can_online &= ~(1 << 1);
	  }

	  // Crash Ausgeloest
	  if (system_in.Crash != 1)
	  {
		  BMS_state.CriticalError = true;
		  BMS_state.Normal = false;
	  }

	  // Wenn Statemaschine nicht im Standby ist
	  if (BMS_state.States != Standby)
	  {
		  // Schreibe alle CAN-Nachrichten auf BUS, wenn nicht im Standby
		  CANwork();
	  }

	  // Statemaschine keine Fehler
	  if (BMS_state.Normal)
	  {
		  leuchten_out.RedLed = false;
		  leuchten_out.GreenLed = true;
	  }

	  // Statemaschine hat Warnungen
	  if (BMS_state.Warning)
	  {
		  if (millis() -timeError > 1000)
		  {
			  leuchten_out.RedLed = !leuchten_out.RedLed;
			  timeError = millis();
		  }

		  leuchten_out.GreenLed = true;
	  }

	  // Statemaschine hat Error
	  if (BMS_state.Error)
	  {
		  if (millis() -timeError > 1000)
		  {
			  leuchten_out.RedLed = !leuchten_out.RedLed;
			  timeError = millis();
		  }

		  leuchten_out.GreenLed = false;
	  }

	  // Statemaschine hat Kritische Fehler
	  if (BMS_state.CriticalError)
	  {
		  leuchten_out.RedLed = true;
		  leuchten_out.GreenLed = false;
	  }

	  // Statemaschine vom Batteriemanagement-System
	  switch(BMS_state.States)
	  {
		  // State Ready, Vorbereiten des Batteriemanagement
		  case Ready:
		  {
			  uartTransmit("KL15\n", 5);
			  BMS_state.States = KL15;

			  break;
		  }

		  // State KL15, wenn Schluessel auf Position 2, KL15 eingeschaltet
		  case KL15:
		  {
			  if (!(BMS_state.CriticalError))
			  {
				  uartTransmit("Anlassen\n", 9);
				  BMS_state.States = Anlassen;

				  sdc_in.Anlassen = true;

				  system_out.AmsOK = true;
			  }

			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  BMS_state.States = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Anlassen, wenn Schluessel auf Position 3 und keine kritischen Fehler, Anlasser einschalten
		  case Anlassen:
		  {
			  if (1)
			  {
				  uartTransmit("Precharge\n", 10);
				  BMS_state.States = Precharge;
			  }

			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  BMS_state.States = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Precharge,
		  case Precharge:
		  {
			  if (1)
			  {
				  uartTransmit("ReadyToDrive\n", 13);
				  BMS_state.States = ReadyToDrive;
			  }

			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  BMS_state.States = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State ReadyToDrive, wenn SDC OK ist
		  case ReadyToDrive:
		  {
			  if (1)
			  {
				  uartTransmit("Drive\n", 6);
				  BMS_state.States = Drive;
			  }

			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  BMS_state.States = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Drive, wenn Fahrmodus manuell aktiviert wird
		  case Drive:
		  {
			  if (system_in.KL15 == 1)
			  {
				  uartTransmit("Standby\n", 8);
				  BMS_state.States = Standby;
				  timeStandby = millis();
			  }

			  break;
		  }

		  // State Standby, wenn Schluessel gezogen wird, KL15 ausgeschaltet
		  case Standby:
		  {
			  if (millis() - timeStandby > BMSTIME)
			  {
				  uartTransmit("Ausschalten\n", 12);
				  BMS_state.States = Ausschalten;
			  }
			  else if (system_in.KL15 != 1)
			  {
				  uartTransmit("Ready\n", 6);
				  BMS_state.States = Ready;
			  }

			  break;
		  }

		  // State Ausschalten, wenn Standby State laenger als 5min dauert
		  case Ausschalten:
		  {
			  system_out.systemoutput = 0;
			  highcurrent_out.high_out = 0;
			  leuchten_out.ledoutput = 0;
			  sdc_in.sdcinput = 0;

			  break;
		  }

		  // Falls kein State zutrifft, dann kritischer Fehler
		  default:
		  {
			  uartTransmit("BMS Kritischer Fehler\n!", 24);
			  BMS_state.CriticalError = true;
			  BMS_state.Normal = false;

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
