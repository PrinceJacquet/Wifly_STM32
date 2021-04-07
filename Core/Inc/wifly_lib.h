/*********************************************************************************
 * \file   	: wifly_lib.h														 *
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

#ifndef INC_WIFLY_LIB_H_
#define INC_WIFLY_LIB_H_

#define DEFAULT_WAIT_RESPONSE_TIME      1000        // 1000ms
#define DEFAULT_BAUDRATE                9600
#define MAX_CMD_LEN                     32
#define MAX_RCP_LEN                     10000
#define MAX_TRY_JOIN                    3

// Auth Modes for Network Authentication
// See WiFly manual for details
#define WIFLY_AUTH_OPEN        "0"    // Open (default)
#define WIFLY_AUTH_WEP         "1"    // WEP-128
#define WIFLY_AUTH_WPA1        "2"    // WPA1
#define WIFLY_AUTH_WPA1_2      "3"    // Mixed-mode WPA1 and WPA2-PSK
#define WIFLY_AUTH_WPA2_PSK    "4"    // WPA2-PSK
#define WIFLY_AUTH_ADHOC       "6"    // Ad-hoc, join any Ad-hoc network








void commandMode(void);
void sendCommand(char * CMD, char * ACK, int * ANS);
void sendData(char * DATA, char * ACK, int * ANS);
void WIFI_authentification(char * SSID, char * AUTH, char * KEY);


#endif /* INC_WIFLY_LIB_H_ */
