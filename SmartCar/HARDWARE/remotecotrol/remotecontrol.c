#include "remotecontrol.h"
#include "motor.h"

//remote control IO初始化
void REMOTECONTROL_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;				 
	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//下拉输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口速度为50MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);				//根据设定参数初始化
	
	REMOECONTROL_FRONT = 0; 	
	REMOECONTROL_LEFT = 0; 	
	REMOECONTROL_RIGHT = 0; 
	REMOECONTROL_STOP = 0; 
}

void remoteC_handle(void)
{
	g_smartCar_sta = remoteC_get_status();
}


/***********************************************
右

************************************************/
smartCar_status_t remoteC_get_status(void)
{
	static smartCar_status_t sta = REMOTEC_STATUS_STOP;

	if((REMOECONTROL_FRONT ==1)&&(REMOECONTROL_LEFT ==1))
	{
		sta = REMOTEC_STATUS_BACKWARD;
	}
	else if(REMOECONTROL_FRONT ==1)
	{
		sta = REMOTEC_STATUS_FORWARD;
	}
	else if(REMOECONTROL_LEFT ==1)
	{
		sta = REMOTEC_STATUS_LEFT;
	}
	else if(REMOECONTROL_RIGHT ==1)
	{
		sta = REMOTEC_STATUS_RIGHT;
	}
	else if(REMOECONTROL_STOP == 1)
	{
		sta = REMOTEC_STATUS_STOP;
	}
	
	return sta;
}




