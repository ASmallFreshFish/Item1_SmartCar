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
	static smartCar_status_t blue_sta=REMOTEC_STATUS_STOP;
	smartCar_speed_sta_t speed_sta=MOTOR_SPEED_STA_KEEP;
	
	if(USART2_rx_sta &(1<<USART2_REC_FINISH_FLAG_BIT))
	{
		len=USART2_rx_sta&0X7FFF;
		USART2_rx_buf[len] =0;

		if(strcmp((const char*)USART2_rx_buf,"FORWARD")==0)
		{
			//Ç°½ø
			blue_sta = BLUE_STATUS_FORWARD;
		}
		else if(strcmp((const char*)USART2_rx_buf,"LEFT")==0)
		{
			//×ó×ª
			blue_sta = BLUE_STATUS_LEFT;
		}
		else if(strcmp((const char*)USART2_rx_buf,"RIGHT")==0)
		{
			//ÓÒ×ª
			blue_sta = BLUE_STATUS_RIGHT;
		}
		else if(strcmp((const char*)USART2_rx_buf,"BACKWARD")==0)
		{
			//µ¹ÍË
			blue_sta = BLUE_STATUS_BACKWARD;
			
		}
		else if(strcmp((const char*)USART2_rx_buf,"STOP")==0)
		{
			//Í£Ö¹
			blue_sta = BLUE_STATUS_STOP;
		}
		else if(strcmp((const char*)USART2_rx_buf,"SPEEDUP")==0)
		{
			//Í£Ö¹
			speed_sta = MOTOR_SPEED_STA_UP;
		}
		else if(strcmp((const char*)USART2_rx_buf,"SPEEDDOWN")==0)
		{
			//Í£Ö¹
			speed_sta = MOTOR_SPEED_STA_DOWN;
		}

		g_smartCar_sta =blue_sta;
		g_smartCar_speed_sta =speed_sta;

		
		USART2_rx_sta = 0;
		memset(USART2_rx_buf,0,sizeof(USART2_rx_buf));
		
		printf("%s",USART2_rx_buf);
		
	}

}

