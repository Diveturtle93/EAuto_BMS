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
#include <math.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BasicUart.h"
#include "SystemInfo.h"
#include "inputs.h"
#include "outputs.h"
#include "imd.h"
#include "..\..\Application\Src\my_math.c"
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
	// Definiere Variablen fuer Main-Funktion
	uint16_t dutyCycle, timerPeriod, frequency, count = 0, R_IMD;

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

	timerPeriod = (HAL_RCC_GetPCLK2Freq() / htim1.Init.Prescaler);
  	// Start timer
	if (HAL_TIM_Base_Start_IT(&htim1) != HAL_OK);
	if (HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1) != HAL_OK);
	if (HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2) != HAL_OK);
  	HAL_TIM_Base_Start(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		// Task wird jede Millisekunde ausgefuehrt
		if (millisekunden_flag_1 == 1)
		{
			count++;													// Zaehler count hochzaehlen
			millisekunden_flag_1 = 0;									// Setze Millisekunden-Flag zurueck
		}

		// Task wird alle 50 Millisekunden ausgefuehrt
		if ((count % 500) == 0)
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
							system_in.IMD_PWM_STATUS = IMD_ERROR;
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
							system_in.IMD_PWM_STATUS = IMD_ERROR;
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
							system_in.IMD_PWM_STATUS = IMD_ERROR;
						}
						break;
					case 40:
						system_in.IMD_PWM_STATUS = IMD_GERAETEFEHLER;
						if (dutyCycle > 47 && dutyCycle < 53)								// IMD PWM
						{

						}
						else																// IMD Invalid
						{
							system_in.IMD_PWM_STATUS = IMD_ERROR;
						}
						break;
					case 50:
						system_in.IMD_PWM_STATUS = IMD_ANSCHLUSSFEHLER_ERDE;
						if (dutyCycle > 47 && dutyCycle < 53)								// IMD PWM
						{

						}
						else																// IMD Invalid
						{
							system_in.IMD_PWM_STATUS = IMD_ERROR;
						}
						break;
					default:
						system_in.IMD_PWM_STATUS = IMD_ERROR;
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
							system_in.IMD_PWM_STATUS = IMD_ERROR;
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
							system_in.IMD_PWM_STATUS = IMD_ERROR;
						}
						break;
					default:
						system_in.IMD_PWM_STATUS = IMD_ERROR;
						break;
				}
			}

			count = 0;
		}
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
