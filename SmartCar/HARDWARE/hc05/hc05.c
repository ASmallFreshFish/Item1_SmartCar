#include "head_include.h"


void HC05_init(void)
{
	
	TIM7_Int_Init(99, 7199);//10ms
	USART2_init(38400);
	
}

void HC05_handle(void)
{
	HC05_receive();
}


void HC05_send(void)
{}


void HC05_receive(void)
{	
	u16 len;
	static smartCar_status_t blue_sta;
	if(USART2_rx_sta &(1<<USART2_REC_FINISH_FLAG_BIT))
	{
		len=USART2_rx_sta&0X7FFF;
		USART2_rx_buf[len] =0;

		if(strcmp((const char*)USART2_rx_buf,"FORWARD")==0)
		{
			//前进
			blue_sta = BLUE_STATUS_FORWARD;
		}
		else if(strcmp((const char*)USART2_rx_buf,"LEFT")==0)
		{
			//左转
			blue_sta = BLUE_STATUS_LEFT;
		}
		else if(strcmp((const char*)USART2_rx_buf,"RIGHT")==0)
		{
			//右转
			blue_sta = BLUE_STATUS_RIGHT;
		}
		else if(strcmp((const char*)USART2_rx_buf,"BACKWARD")==0)
		{
			//倒退
			blue_sta = BLUE_STATUS_BACKWARD;
			
		}
		else if(strcmp((const char*)USART2_rx_buf,"STOP")==0)
		{
			//停止
			blue_sta = BLUE_STATUS_STOP;
		}

		g_smartCar_sta =blue_sta;
		
		USART2_rx_sta = 0;
		
		printf("%s",USART2_rx_buf);
		
	}

}

