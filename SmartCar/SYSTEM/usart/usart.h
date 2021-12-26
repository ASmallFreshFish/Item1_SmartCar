#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

/**************************************************
LOG
***************************************************/

//����봮���жϽ��գ��벻Ҫע�����º궨��
#define USART1_REC_LEN  			200  	//�����������ֽ��� 200
	  	
extern u8  USART1_RX_BUF[USART1_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         		//����״̬���	

void USART1_init(u32 bound);


/**************************************************
bluetooth usart2
***************************************************/
#define BLUE_MODULE_HC05 
#define USART2_REC_LEN  			200  	//�����������ֽ��� 200
#define USART2_REC_FINISH_FLAG_BIT 15
	  	
extern u8 USART2_tx_buf[USART2_REC_LEN];
extern u8 USART2_rx_buf[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u16 USART2_rx_sta;  


void USART2_init(u32 bound);
void USART2_printf(char* fmt,...) ;



/**************************************************
bluetooth usart3
***************************************************/
#define USART3_DEBUG_MCRO 
#define USART3_REC_LEN  			200  	//�����������ֽ��� 200
#define USART3_REC_FINISH_FLAG_BIT 15
	  	
extern u8 USART3_tx_buf[USART2_REC_LEN];
extern u8 USART3_rx_buf[USART2_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u16 USART3_rx_sta;  


void USART3_init(u32 bound);
void USART3_printf(char* fmt,...) ;



#endif


