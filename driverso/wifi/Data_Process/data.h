#ifndef __data_h
	#define __data_h
	
	#include	<wifi/Common_Lables.h>
	
	uint8_t Public_Key1[30] 			= "5JXvMoorx4tgjMnqjQ02"; 					/* For Sprakfun Data posting*/
	uint8_t Private_Key1[30] 			= "7Ba4n881xofeYxpEYb0y"; 					/* For Sprakfun Data posting*/
	
	uint8_t Connect_Data[ CONNECT_DATA_SIZE ] 			= "\"EFF-WIFI\",\"eff@ronics\"";			/* SSID and  password for WIFI Access point*/
	uint8_t Connect_To_Data[ CONNECT_TO_DATA_SIZE ] 		= "\"TCP\",\"data.sparkfun.com\",80\r\n";	/* For connecting to sparkfun server using port 80 and TCP protocol */
	uint8_t Connect_Send_Data[ CONNECT_SEND_DATA_SIZE ];
	/*
	GET /input/5JXvMoorx4tgjMnqjQ02?private_key=7Ba4n881xofeYxpEYb0y&temperature=99.18&humidity=100&co2=22\r\n
	Host:data.sparkfun.com\r\n\r\n
	*/

	void Connect_Send(uint32_t co2, uint32_t humidity, uint32_t temp);

#endif