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
#include "error.h"
#include "inputs.h"
#include "outputs.h"
#include "my_math.h"
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
  /* USER CODE BEGIN 2 */

	/* Schreibe Resetquelle auf die Konsole */
#ifdef DEBUG
	printResetSource(readResetSource());

	/* Teste serielle Schnittstelle*/
	#define TEST_STRING_UART	"\nUART2 Transmitting in polling mode, Hello Diveturtle93!\n"
	uartTransmit(TEST_STRING_UART, sizeof(TEST_STRING_UART));

	/* Sammel Systeminformationen */
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

	/*if ((temp = ltc6811_check()) != 0)									// LTC6804 Selftest durchfuehren
	{
#define LTC6811_FAILED	"Selbsttest LTC6811 fehlerhaft\n"
		uartTransmit(LTC6811_FAILED, sizeof(LTC6811_FAILED));			// Ausgabe bei Fehlerhaftem Selbsttest
		leuchten_out.RedLed = 1;										// Variable setzen
	    HAL_GPIO_WritePin(RED_LED_GPIO_Port, RED_LED_Pin, leuchten_out.RedLed);// Ausgabe auf LEDs

	    uartTransmitNumber(temp, 10);
		uartTransmit("\n", 1);

		//return 0;														// Programm abbrechen
	}
	else
	{
#define LTC6811_PASSED	"Selbsttest LTC6811 erfolgreich\n"
		uartTransmit(LTC6811_PASSED, sizeof(LTC6811_PASSED));			// Ausgabe bei Erfolgreichem Selbsttest
	}*/

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

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		ltc6811(ADCVC | MD73 | CELLALL);
		HAL_Delay(300);

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
			HAL_Delay(100);
			ltc6811(ADAX | MD262 | GPIOALL);								// Initial Command Zellen auslesen
			HAL_Delay(300);
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

		temp++;

		if(temp == 2)
			return 1;
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
	while (1);
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

