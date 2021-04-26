#include "remotecontrol.h"
#include "motor.h"

//remote control IO��ʼ��
void REMOTECONTROL_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);	 //ʹ��PB,PE�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;				 
	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;		//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);				//�����趨������ʼ��
	
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
��

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




