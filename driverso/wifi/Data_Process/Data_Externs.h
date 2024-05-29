
#ifndef	__Data_Externs___H
	#define	__Data_Externs___H
		
		#include	<wifi/Common_Lables.h>
		
		extern		void 		Connect_Send(uint32_t co2, uint32_t humidity, uint32_t temp);
		extern		uint8_t 	Connect_Data[ CONNECT_DATA_SIZE ];				/* Data to be used with AT commands*/
		extern		uint8_t 	Connect_To_Data[ CONNECT_TO_DATA_SIZE ];
		extern		uint8_t 	Connect_Send_Data[ CONNECT_SEND_DATA_SIZE ];

#endif /*__Data_Externs___H*/