/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define INLET_RED_Pin GPIO_PIN_2
#define INLET_RED_GPIO_Port GPIOE
#define SENSE_SDC_HVIL_Pin GPIO_PIN_3
#define SENSE_SDC_HVIL_GPIO_Port GPIOE
#define SENSE_SDC_BTB_Pin GPIO_PIN_4
#define SENSE_SDC_BTB_GPIO_Port GPIOE
#define SENSE_SDC_MOTOR_Pin GPIO_PIN_5
#define SENSE_SDC_MOTOR_GPIO_Port GPIOE
#define POWER_ON_Pin GPIO_PIN_13
#define POWER_ON_GPIO_Port GPIOC
#define TRIGGER_CURRENT_Pin GPIO_PIN_1
#define TRIGGER_CURRENT_GPIO_Port GPIOF
#define OVC_SENSE_Pin GPIO_PIN_2
#define OVC_SENSE_GPIO_Port GPIOF
#define SPI_CS_Pin GPIO_PIN_6
#define SPI_CS_GPIO_Port GPIOF
#define SPI_SCK_Pin GPIO_PIN_7
#define SPI_SCK_GPIO_Port GPIOF
#define SPI_MISO_Pin GPIO_PIN_8
#define SPI_MISO_GPIO_Port GPIOF
#define SPI_MOSI_Pin GPIO_PIN_9
#define SPI_MOSI_GPIO_Port GPIOF
#define RCC_OSC_IN_Pin GPIO_PIN_0
#define RCC_OSC_IN_GPIO_Port GPIOH
#define RCC_OSC_OUT_Pin GPIO_PIN_1
#define RCC_OSC_OUT_GPIO_Port GPIOH
#define CRASH_Pin GPIO_PIN_0
#define CRASH_GPIO_Port GPIOA
#define IMD_OK_OUT_Pin GPIO_PIN_1
#define IMD_OK_OUT_GPIO_Port GPIOA
#define HW_WAKE_Pin GPIO_PIN_2
#define HW_WAKE_GPIO_Port GPIOA
#define SENSE_TEMP1_Pin GPIO_PIN_3
#define SENSE_TEMP1_GPIO_Port GPIOA
#define SENSE_TEMP2_Pin GPIO_PIN_4
#define SENSE_TEMP2_GPIO_Port GPIOA
#define SENSE_TEMP3_Pin GPIO_PIN_5
#define SENSE_TEMP3_GPIO_Port GPIOA
#define SENSE_TEMP4_Pin GPIO_PIN_6
#define SENSE_TEMP4_GPIO_Port GPIOA
#define SENSE_PCB_Pin GPIO_PIN_7
#define SENSE_PCB_GPIO_Port GPIOA
#define GREEN_LED_Pin GPIO_PIN_2
#define GREEN_LED_GPIO_Port GPIOB
#define PRECHARGE_OUT_Pin GPIO_PIN_13
#define PRECHARGE_OUT_GPIO_Port GPIOF
#define PRECHARGE_IN_Pin GPIO_PIN_15
#define PRECHARGE_IN_GPIO_Port GPIOF
#define AMS_OK_Pin GPIO_PIN_7
#define AMS_OK_GPIO_Port GPIOE
#define IMD_OK_IN_Pin GPIO_PIN_8
#define IMD_OK_IN_GPIO_Port GPIOE
#define IMD_PWM_Pin GPIO_PIN_9
#define IMD_PWM_GPIO_Port GPIOE
#define ISOSPI_CS_Pin GPIO_PIN_11
#define ISOSPI_CS_GPIO_Port GPIOE
#define ISOSPI_SCK_Pin GPIO_PIN_12
#define ISOSPI_SCK_GPIO_Port GPIOE
#define ISOSPI_MISO_Pin GPIO_PIN_13
#define ISOSPI_MISO_GPIO_Port GPIOE
#define ISOSPI_MOSI_Pin GPIO_PIN_14
#define ISOSPI_MOSI_GPIO_Port GPIOE
#define ISOSPI_EN_Pin GPIO_PIN_15
#define ISOSPI_EN_GPIO_Port GPIOE
#define RED_LED_Pin GPIO_PIN_14
#define RED_LED_GPIO_Port GPIOB
#define KL15_Pin GPIO_PIN_11
#define KL15_GPIO_Port GPIOD
#define PWM_HV_N_Pin GPIO_PIN_12
#define PWM_HV_N_GPIO_Port GPIOD
#define PWM_HV_P_Pin GPIO_PIN_13
#define PWM_HV_P_GPIO_Port GPIOD
#define PWM_HV_M_Pin GPIO_PIN_14
#define PWM_HV_M_GPIO_Port GPIOD
#define PWM_HV_Charger_Pin GPIO_PIN_15
#define PWM_HV_Charger_GPIO_Port GPIOD
#define HV_N_Pin GPIO_PIN_2
#define HV_N_GPIO_Port GPIOG
#define HV_P_Pin GPIO_PIN_3
#define HV_P_GPIO_Port GPIOG
#define HV_M_Pin GPIO_PIN_4
#define HV_M_GPIO_Port GPIOG
#define HV_Charger_Pin GPIO_PIN_5
#define HV_Charger_GPIO_Port GPIOG
#define AKKU_LED_Pin GPIO_PIN_7
#define AKKU_LED_GPIO_Port GPIOG
#define SD_SW_Pin GPIO_PIN_6
#define SD_SW_GPIO_Port GPIOC
#define SD_D0_Pin GPIO_PIN_8
#define SD_D0_GPIO_Port GPIOC
#define SD_D1_Pin GPIO_PIN_9
#define SD_D1_GPIO_Port GPIOC
#define HEATER2_Pin GPIO_PIN_9
#define HEATER2_GPIO_Port GPIOA
#define HEATER1_Pin GPIO_PIN_10
#define HEATER1_GPIO_Port GPIOA
#define BUTTON2_Pin GPIO_PIN_11
#define BUTTON2_GPIO_Port GPIOA
#define BUTTON1_Pin GPIO_PIN_12
#define BUTTON1_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SD_D2_Pin GPIO_PIN_10
#define SD_D2_GPIO_Port GPIOC
#define SD_D3_Pin GPIO_PIN_11
#define SD_D3_GPIO_Port GPIOC
#define SD_SCK_Pin GPIO_PIN_12
#define SD_SCK_GPIO_Port GPIOC
#define SD_CMD_Pin GPIO_PIN_2
#define SD_CMD_GPIO_Port GPIOD
#define DIGITAL1_Pin GPIO_PIN_3
#define DIGITAL1_GPIO_Port GPIOD
#define DIGITAL2_Pin GPIO_PIN_4
#define DIGITAL2_GPIO_Port GPIOD
#define POTI_MOSI_Pin GPIO_PIN_7
#define POTI_MOSI_GPIO_Port GPIOD
#define POTI_MISO_Pin GPIO_PIN_9
#define POTI_MISO_GPIO_Port GPIOG
#define POTI_CS_Pin GPIO_PIN_10
#define POTI_CS_GPIO_Port GPIOG
#define POTI_SCK_Pin GPIO_PIN_11
#define POTI_SCK_GPIO_Port GPIOG
#define POTI_RS_Pin GPIO_PIN_12
#define POTI_RS_GPIO_Port GPIOG
#define POTI_SHDN_Pin GPIO_PIN_13
#define POTI_SHDN_GPIO_Port GPIOG
#define RECUPERATION_Pin GPIO_PIN_14
#define RECUPERATION_GPIO_Port GPIOG
#define AMS_LIMIT_Pin GPIO_PIN_15
#define AMS_LIMIT_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define BLUE_LED_Pin GPIO_PIN_7
#define BLUE_LED_GPIO_Port GPIOB
#define I2C_SCL_Pin GPIO_PIN_8
#define I2C_SCL_GPIO_Port GPIOB
#define I2C_SDA_Pin GPIO_PIN_9
#define I2C_SDA_GPIO_Port GPIOB
#define FREIGABE_Pin GPIO_PIN_0
#define FREIGABE_GPIO_Port GPIOE
#define INLET_GREEN_Pin GPIO_PIN_1
#define INLET_GREEN_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */
// Anzahl der CAN Output Pakete defineren
//----------------------------------------------------------------------
#define ANZAHL_OUTPUT_PAKETE			7									// Anzahl Sende Nachrichten
//----------------------------------------------------------------------

// Typedefine Boolean definieren
//----------------------------------------------------------------------
typedef enum
{
	false,
	true,
} bool;
//----------------------------------------------------------------------
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
