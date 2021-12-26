#include "sys.h"
#include "usart.h"	
#include "timer.h"

#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 

////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
 
/**************************************************
LOG
***************************************************/

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 


//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记	  
  
void USART1_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟

	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据

		if((USART1_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART1_RX_STA&0x4000)//接收到了0x0d
			{
				if(Res!=0x0a)USART1_RX_STA=0;//接收错误,重新开始
				else USART1_RX_STA|=0x8000;	//接收完成了 
			}
			else //还没收到0X0D
			{	
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
				{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}   		 
	} 
} 





/**************************************************

bluetooth usart2

***************************************************/


#ifdef BLUE_MODULE_HC05

u8 USART2_tx_buf[USART2_REC_LEN];
u8 USART2_rx_buf[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
 u16 USART2_rx_sta =0;  

void USART2_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2，GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	//USART1_TX   GPIOA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
   
  	//USART1_RX	  GPIOA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//P3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART2, ENABLE);                    //使能串口2 

	memset(USART2_tx_buf,0,sizeof(USART2_tx_buf));
	memset(USART2_rx_buf,0,sizeof(USART2_tx_buf));
}

void USART2_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res =USART_ReceiveData(USART2);		 
		if((USART2_rx_sta&(1<<USART2_REC_FINISH_FLAG_BIT))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
		{ 
			if(USART2_rx_sta<USART2_REC_LEN)	//还可以接收数据
			{
				TIM_SetCounter(TIM7,0);//计数器清空      	//计数器清空
				if(USART2_rx_sta==0) 					//使能定时器7的中断 
				{
					TIM_Cmd(TIM7,ENABLE);//使能定时器7
				}
				USART2_rx_buf[USART2_rx_sta++]=res;	//记录接收到的值	 
			}else 
			{
				USART2_rx_sta|=1<<USART2_REC_FINISH_FLAG_BIT;				//强制标记接收完成
			} 
		}
	}  				 											 
}      

//void USART2_IRQHandler(void)                	//串口1中断服务程序
//{
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//	{
//		USART2_rx_buf[USART2_rx_sta] =USART_ReceiveData(USART2);	//读取接收到的数据
//		printf("%c",USART2_rx_buf[USART2_rx_sta]);
//		USART2_rx_sta++;
//	} 
//} 

void USART2_SendStr(u8 *SendBuf) //发送字符串
{
	while(*SendBuf)
	{
		while((USART2->SR&0X40)==0){} 
		USART2->DR = (u8) *SendBuf; 
		SendBuf++;
	}
	
}

void USART2_trans_back(u8 *SendBuf)
{
	USART2_SendStr(USART2_rx_buf);
}

/************************
//usart2 仿照printf函数
//非常值得学习！！！
*************************/
void USART2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_tx_buf,fmt,ap);
	va_end(ap);
	
	i=strlen((const char*)USART2_tx_buf);		//计算发送数据长度
	for(j=0;j<i;j++)							//真正的发送数据
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);    
		USART_SendData(USART2,USART2_tx_buf[j]); 
	} 
}

#endif


/**************************************************

bluetooth usart2

***************************************************/

#ifdef BLUE_MODULE_HC05

u8 USART2_tx_buf[USART2_REC_LEN];
u8 USART2_rx_buf[USART2_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
 u16 USART2_rx_sta =0;  

void USART2_init(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2，GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	//USART1_TX   GPIOA.2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA.2
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.2
   
  	//USART1_RX	  GPIOA.3
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//P3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.3

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级1
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
	//USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART2, &USART_InitStructure); //初始化串口2
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART2, ENABLE);                    //使能串口2 

	memset(USART2_tx_buf,0,sizeof(USART2_tx_buf));
	memset(USART2_rx_buf,0,sizeof(USART2_tx_buf));
}

void USART2_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res =USART_ReceiveData(USART2);		 
		if((USART2_rx_sta&(1<<USART2_REC_FINISH_FLAG_BIT))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
		{ 
			if(USART2_rx_sta<USART2_REC_LEN)	//还可以接收数据
			{
				TIM_SetCounter(TIM7,0);//计数器清空      	//计数器清空
				if(USART2_rx_sta==0) 					//使能定时器7的中断 
				{
					TIM_Cmd(TIM7,ENABLE);//使能定时器7
				}
				USART2_rx_buf[USART2_rx_sta++]=res;	//记录接收到的值	 
			}else 
			{
				USART2_rx_sta|=1<<USART2_REC_FINISH_FLAG_BIT;				//强制标记接收完成
			} 
		}
	}  				 											 
}      

//void USART2_IRQHandler(void)                	//串口1中断服务程序
//{
//	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//	{
//		USART2_rx_buf[USART2_rx_sta] =USART_ReceiveData(USART2);	//读取接收到的数据
//		printf("%c",USART2_rx_buf[USART2_rx_sta]);
//		USART2_rx_sta++;
//	} 
//} 

void USART2_SendStr(u8 *SendBuf) //发送字符串
{
	while(*SendBuf)
	{
		while((USART2->SR&0X40)==0){} 
		USART2->DR = (u8) *SendBuf; 
		SendBuf++;
	}
	
}

void USART2_trans_back(u8 *SendBuf)
{
	USART2_SendStr(USART2_rx_buf);
}

/************************
//usart2 仿照printf函数
//非常值得学习！！！
*************************/
void USART2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_tx_buf,fmt,ap);
	va_end(ap);
	
	i=strlen((const char*)USART2_tx_buf);		//计算发送数据长度
	for(j=0;j<i;j++)							//真正的发送数据
	{
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);    
		USART_SendData(USART2,USART2_tx_buf[j]); 
	} 
}

#endif


