/*********************************************************************************
 * \file   	: wifly_lib.c														 *
 * \date  	: Mar 20, 2021														 *
 * \brief 	: Wifi shield seedstudio v2 library									 *
 *																				 *
 *********************************************************************************
 *	 	 	 	 	 	 Released under MIT License								 *
 * 	 	 	 	 	 			Copyright 2021 									 *
 *																				 *
 * Permission is hereby granted, free of charge, to any person obtaining a		 *
 * copy of this software and associated documentation files (the "Software"),	 *
 * to deal in the Software without restriction, including without limitation	 *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,		 *
 * and/or sell copies of the Software, and to permit persons to whom the		 *
 * Software is furnished to do so, subject to the following conditions:			 *
 *																				 *
 * The above copyright notice and this permission notice shall be included in	 *
 * all copies or substantial portions of the Software.							 *
 *																				 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR	 *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,		 *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL		 *
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER	 *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE *
 * SOFTWARE.																	 *
 *********************************************************************************/

#include "wifly_lib.h"
#include "usart.h"



void commandMode()
{
	HAL_UART_Transmit_IT(&huart2, (uint8_t *)"\nPasser en mode Commande\n\n", 27);

	//Go into Command mode
		char CMD_MODE[4] = {'$','$','$'};
		uint8_t ok[5] = {0};

		HAL_Delay(250);

		do{
			HAL_UART_Transmit(&huart1, (uint8_t *)CMD_MODE, strlen(CMD_MODE), 5000);
		 	HAL_UART_Receive(&huart1, (uint8_t *)ok, MAX_RCP_LEN, DEFAULT_WAIT_RESPONSE_TIME);
		  }while (strstr((char *) ok, "CMD")==NULL);
		HAL_Delay(250);
}


//void sendCommand(char * CMD, char * ACK,uint8_t timeout , uint8_t * ANS)
void sendCommand(char * CMD, char * ACK, uint8_t * ANS)
{
	int i =0;
	int k = 0;
	//uint8_t TIME_Delay;

	if(strstr(CMD, "scan")==NULL)
		k = 1;
	else
		k = 10;

	memset(ANS,0,MAX_RCP_LEN);


	//TIME_Delay =  DEFAULT_WAIT_RESPONSE_TIME*k;



	//Go into Command mode
		//commandMode();

	//Pass the command to the module

	 	 do{
	 		 i++;
	 		 HAL_Delay(200);

	 		 HAL_UART_Transmit_IT(&huart1,  (uint8_t *)CMD, strlen(CMD));
	 		 HAL_UART_Receive(&huart1,  ANS, MAX_RCP_LEN, DEFAULT_WAIT_RESPONSE_TIME*k);

	 		 HAL_UART_Transmit_IT(&huart2,  (uint8_t *)CMD, strlen(CMD)+1);

	 	 }while (strstr(( char *)ANS, ACK)==NULL && i <5);

 }

void sendData(char * DATA, char * ACK, uint8_t * ANS)
{
	int i =0;

	memset(ANS,0,MAX_RCP_LEN);


	//TIME_Delay =  DEFAULT_WAIT_RESPONSE_TIME*k;



	//Go into DATA mode
		//commandMode();

	//Pass the command to the module

	 	 do{
	 		i++;
	 		HAL_Delay(200);

	 		 HAL_UART_Transmit_IT(&huart1,  (uint8_t *)DATA, strlen(DATA)+1);
	 		 HAL_UART_Receive(&huart1,  ANS, MAX_RCP_LEN, DEFAULT_WAIT_RESPONSE_TIME*3);

	 		 HAL_UART_Transmit_IT(&huart2,  (uint8_t *)DATA, strlen(DATA)+1);

	 	 }while (strstr(( char *)ANS, ACK)==NULL && i <5);

 }
