
#ifndef	__Wifi_Externs___H
	#define	__Wifi_Externs___H
	
		#include	"Common_Lables.h"
		
		extern		void 		Wifi_Vars_Init(void);
		
		extern		void 		WIFI_Main(void);
		extern 		void 		Start_Posting(void);
		extern		void 		Add_To_Connect_Send_Data(uint8_t *data);
		extern		void 		Int_To_String( uint32_t num, uint8_t *buffer);
		
		typedef 	enum 		{RST, ATE1, AT, CWMODE, CWJAP, CIPSTATUS, CIPSTART, CIPSEND, SEND_DATA, END, WAIT }states;
		
		extern		uint8_t		Wifi_Rx_Buff[ WIFI_RX_BUFFER_SIZE ];		
		extern		uint32_t	Wifi_RxBuff_Start_Addr;
		extern		uint32_t	Wifi_RxBuff_End_Addr;
		extern		uint8_t		*Wifi_RxBuff_Fill_Ptr;
		extern		uint8_t		*Wifi_RxBuff_Read_Ptr;
		
		extern		uint32_t	Wifi_TxBuff_Start_Addr;
		extern		uint32_t	Wifi_TxBuff_End_Addr;
		extern		uint8_t		*Wifi_TxBuff_Fill_Ptr;
		extern		uint8_t		*Wifi_TxBuff_Trans_Ptr;
		
		extern 		states 		W_TxPres_State;
		extern 		uint8_t 	complete;
		extern 		uint8_t 	call_it;
		
		extern 		uint32_t 	a, b, c; 
		
		extern		uint8_t 	Procrastinate;
		extern		uint32_t	Count_RST;
		extern		uint32_t	Minute_Count;
#endif