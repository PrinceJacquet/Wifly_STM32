/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "wifly_lib.h"

/*	WIFLY_AUTH_OPEN        0    // Open (default)
	WIFLY_AUTH_WEP         1    // WEP-128
	WIFLY_AUTH_WPA1        2    // WPA1
	WIFLY_AUTH_WPA1_2      3    // Mixed-mode WPA1 and WPA2-PSK
	WIFLY_AUTH_WPA2_PSK    4    // WPA2-PSK
	WIFLY_AUTH_ADHOC       6    // Ad-hoc, join any Ad-hoc network
*/
#define SSID	"Galaxy-S8"
#define KEY		"123456789"
#define AUTH	WIFLY_AUTH_WPA2_PSK

#define URL		"httpbin.org"//"api.openweathermap.org" //"e40810fd255dcc.localhost.run"

#define HOST_IP "192.168.43.48"
#define HOST_PORT "4010"
#define STD_PORT "80"
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */



  int ok[MAX_RCP_LEN ] = {0};
  char GET_DATA_Send[100] = "GET /ShowData?id=10";
  //char path = "/ShowData?";
  int  id = 10, temp = 2000, humA = 4560, humS = 6700 , Waterlvl = 5000;
  int reboot = 0, i =0;



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


  commandMode();



  /* -----  WIFI_authentification(SSID,AUTH,KEY);  ----- */


	sendCommand("set wlan ssid " SSID "\r", "OK",ok);
	  if (strcmp(AUTH , WIFLY_AUTH_OPEN) > 0 || strcmp(AUTH , WIFLY_AUTH_OPEN) < 0 )
	    {
		  sendCommand("set wlan auth " AUTH "\r","OK", ok);
	  	  if (strcmp(AUTH , WIFLY_AUTH_WEP)==0)
	  	  {
	  		sendCommand("set wlan key " KEY "\r","OK", ok); // Key must be EXACTLY 13 bytes (26 ASCII chars)
	  	  }
	  	  else{
	  		sendCommand("set wlan phrase " KEY"\r","OK", ok);

	  	  }
	    }




   /* -----  Connect to server ----- */

  sendCommand("set ip protocol 18\r","OK",ok); //enable html client
  sendCommand("set com remote 0\r","OK",ok); // turn off the REMOTE string so it does not interfere with the post


  sendCommand("set ip host " HOST_IP"\r","OK",ok); //set remote IP to connect to
  sendCommand("set ip remote "HOST_PORT"\r","OK",ok); //set remote Port to connect to

  //sendCommand("set ip address 0\r","OK",ok);// so WiFly will use DNS (when of need of DNS)
  //sendCommand("set dns name " URL"\r", "AOK", ok);



  //sendCommand("set comm open *OPEN*\r","OK",ok); // set the string that the wifi shield will output when a connection is opened

  //sendCommand("open " HOST_IP " " HOST_PORT"\r","*OPEN*",ok);
  //sendCommand("open\r","*OPEN*",ok); // One time opening of connection to server

  sendCommand("set uart mode 2\r","AOK",ok); //auto connect on every UART message

  /* -----  Save wlan config ----- */

  sendCommand("save\r", "Storing in config",ok);
  sendCommand("reboot\r", "*READY*", ok); //After reboot we directly go to dataMode

 /*

   /* -----  Join access point ----- //
    HAL_Delay(1000);
    commandMode();
    sendCommand("join " SSID "\r", "Associated!",ok);

  sendCommand("exit\r", "EXIT", ok); // go into DATA mode (mode in which we can communicate with the network/http)

 */




  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  /*-----  Join access point -----*/

	  HAL_Delay(1000);
	  commandMode();
	  sendCommand("show  net\r", "Assoc=OK",ok);
	  if (strstr(ok,"Assoc=OK")==NULL)
	  {
		  sendCommand("join\r","Associated!",ok);
	  }
	  sendCommand("exit\r","EXIT", ok);



	  /* Code Capteurs */


















	  /* Send measures to server */

	  snprintf(GET_DATA_Send,100,"GET %sid=%d&temp=%d&huma=%d&hums=%d&wtrlvl=%d","/ShowData?",id + i,temp,humA,humS,Waterlvl);
	  sendData(GET_DATA_Send,"*OPEN*", ok);
	  i++;

	  /* test Failure and reboot Wifi Module*/
	  if( strstr((char *)ok,"ERR") != NULL ||  strcmp((char *)ok,"") == 0 )
	  {
		  reboot ++;
		  if(reboot >= 2)
		  {
			  reboot = 0;
			  commandMode();
			  sendCommand("reboot\r", "*READY*", ok);
		  }

	  }





	  HAL_Delay(5000);


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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
  __disable_irq();
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
