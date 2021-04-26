#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

/**************************************************
LOG
***************************************************/

//如果想串口中断接收，请不要注释以下宏定义
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define USART1_REC_LEN  			200  	//定义最大接收字节数 200
	  	
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART1_RX_STA;         		//接收状态标记	

void USART1_init(u32 bound);





/**************************************************
bluetooth usart2
***************************************************/
#define BLUE_MODULE_HC05 
#define USART2_REC_LEN  			200  	//定义最大接收字节数 200
#define USART2_REC_FINISH_FLAG_BIT 15
	  	
extern u8 USART2_tx_buf[USART2_REC_LEN];
extern u8 USART2_rx_buf[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern u16 USART2_rx_sta;  


void USART2_init(u32 bound);
void USART2_printf(char* fmt,...) ;



#endif


