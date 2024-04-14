#ifndef __Common_Lables_h
	#define __Common_Labels_h
	#include	"stdint.h"
	
	#define	UART0_VECT_INTR_NUM			5								/* UART0 bit number in the NVIC Registers*/
	#define	UART_TX_BUFF_SIZE			16								/* UART FIFO Maximum size*/
	#define	UART_RX_BUFF_SIZE			16								/* UART FIFO Maximum size*/
	
	#define INTERRUPT_TYPE 				(LPC_UART0->IIR & 0x0F)
	#define RECEIVE_DATA_INTERRUPT 		( val == 0x04 )
	#define TX_DATA_INTERRUPT 			( val == 0x02 )
	#define RECEIVER_DATA_READY 		(LPC_UART0->LSR & 0x01)
	#define	UART0_RX_DATA				LPC_UART0->RBR
	#define	UART0_TX_REG				LPC_UART0->THR
	#define UART0_IER_REG				LPC_UART0->IER
	#define	THRE_ENABLE_PIN				(1<<1)
	
	#define MAX_WAIT_CYCLES 			1000000							/* max wait time for wait_till_response function*/
	#define MAX_WAIT_CYCLES_RST_FUNC 	0x20000							/* max wait time for Reset function to respond complete*/
	#define NEEDS_RESET 				(Check_To_Rst == 1)
	
	
	#define TIMER_OVER					LPC_TIM0->IR & 0x01
	#define TIMER0_TCR					LPC_TIM0->TCR
	#define TIMER1_TCR					LPC_TIM1->TCR
	#define TIMER1_OVER					LPC_TIM0->IR & 0x01
	#define CLEAR_TIMER_INTERRUPT		(1 << 0)
	#define CLEAR_TIMER0_VEC_INT		(1 << 1)
	#define CLEAR_TIMER1_VEC_INT		(1 << 2)
	#define TIMER_START					0x01
	#define TIMER_RESET					0x02
	
	#define MAX_RST_ALLOWED				5
	#define MAX_MINUTES_TO_WAIT			10
	
	#define WIFI_TX_BUFFER_SIZE			600
	#define WIFI_RX_BUFFER_SIZE			600
	#define UART_RX_BUFFER_SIZE			600
	#define TEMP_DATA_BUFFER_SIZE		500
	#define SERVER_RESPONSE_BUFFER_SIZE	600
	
	#define CONNECT_SEND_DATA_SIZE		200
	#define CONNECT_DATA_SIZE			100
	#define CONNECT_TO_DATA_SIZE		100
	
#endif