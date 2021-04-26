#include "head_include.h"


smartCar_status_t g_smartCar_sta = REMOTEC_STATUS_STOP;



//motor IO初始化
void MOTOR_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_GPIOA, ENABLE);	 //使能PB,PE端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4 \
		|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 
	//LED0-->PB.5 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5

	MOTOR_LEFT_1_IN1 =0;	//左1电机
	MOTOR_LEFT_1_IN2 =0;	
	MOTOR_RIGHT_1_IN1 =0;	//右1电机
	MOTOR_RIGHT_1_IN2 =0;

	MOTOR_LEFT_2_IN1 =0;	//左2电机
	MOTOR_LEFT_2_IN2 =0;
	MOTOR_RIGHT_2_IN1 =0;	//右2电机
	MOTOR_RIGHT_2_IN2 =0;
}

/***********************************************
右

************************************************/

void MOTOR_forward(void)
{
	//左1：-/+；右1：+/-；左2：+/-；右2：-/+；
	MOTOR_LEFT_1_IN1 = 0; MOTOR_LEFT_1_IN2 = 1;	
	MOTOR_LEFT_2_IN1 = 1; MOTOR_LEFT_2_IN2 = 0;	
	MOTOR_RIGHT_1_IN1 = 0;MOTOR_RIGHT_1_IN2 = 1;
	MOTOR_RIGHT_2_IN1 = 1;MOTOR_RIGHT_2_IN2 = 0;
}

void MOTOR_turn_left(void)
{
	MOTOR_LEFT_1_IN1 = 1; MOTOR_LEFT_1_IN2 = 0;	
	MOTOR_LEFT_2_IN1 = 0; MOTOR_LEFT_2_IN2 = 1;	
	MOTOR_RIGHT_1_IN1 = 0;MOTOR_RIGHT_1_IN2 = 1;
	MOTOR_RIGHT_2_IN1 = 1;MOTOR_RIGHT_2_IN2 = 0;
	
}
void MOTOR_turn_right(void)
{
	MOTOR_LEFT_1_IN1 = 0; MOTOR_LEFT_1_IN2 = 1; 
	MOTOR_LEFT_2_IN1 = 1; MOTOR_LEFT_2_IN2 = 0; 
	MOTOR_RIGHT_1_IN1 = 1;MOTOR_RIGHT_1_IN2 = 0;
	MOTOR_RIGHT_2_IN1 = 0;MOTOR_RIGHT_2_IN2 = 1;

}
void MOTOR_backward(void)
{
	MOTOR_LEFT_1_IN1 = 1; MOTOR_LEFT_1_IN2 = 0;	
	MOTOR_LEFT_2_IN1 = 0; MOTOR_LEFT_2_IN2 = 1;	
	MOTOR_RIGHT_1_IN1 = 1;MOTOR_RIGHT_1_IN2 = 0;
	MOTOR_RIGHT_2_IN1 = 0;MOTOR_RIGHT_2_IN2 = 1;
	
}

void MOTOR_stop(void)
{
	MOTOR_LEFT_1_IN1 = 0; MOTOR_LEFT_1_IN2 = 0;	
	MOTOR_LEFT_2_IN1 = 0; MOTOR_LEFT_2_IN2 = 0;	
	MOTOR_RIGHT_1_IN1 = 0;MOTOR_RIGHT_1_IN2 = 0;
	MOTOR_RIGHT_2_IN1 = 0;MOTOR_RIGHT_2_IN2 = 0;
}



void MOTOR_left_1_forward(void)
{
	//左1：-/+；右1：+/-；左2：+/-；右2：-/+；
	MOTOR_LEFT_1_IN1 = 0; MOTOR_LEFT_1_IN2 = 1;	
	MOTOR_LEFT_2_IN1 = 0; MOTOR_LEFT_2_IN2 = 0;	
	MOTOR_RIGHT_1_IN1 = 0;MOTOR_RIGHT_1_IN2 = 0;
	MOTOR_RIGHT_2_IN1 = 0;MOTOR_RIGHT_2_IN2 = 0;
}

void MOTOR_left_2_forward(void)
{
	//左1：-/+；右1：+/-；左2：+/-；右2：-/+；
	MOTOR_LEFT_1_IN1 = 0; MOTOR_LEFT_1_IN2 = 0;	
	MOTOR_LEFT_2_IN1 = 1; MOTOR_LEFT_2_IN2 = 0;	
	MOTOR_RIGHT_1_IN1 = 0;MOTOR_RIGHT_1_IN2 = 0;
	MOTOR_RIGHT_2_IN1 = 0;MOTOR_RIGHT_2_IN2 = 0;
}

void MOTOR_right_1_forward(void)
{
	//左1：-/+；右1：+/-；左2：+/-；右2：-/+；
	MOTOR_LEFT_1_IN1 = 0; MOTOR_LEFT_1_IN2 = 0;	
	MOTOR_LEFT_2_IN1 = 0; MOTOR_LEFT_2_IN2 = 0;	
	MOTOR_RIGHT_1_IN1 = 0;MOTOR_RIGHT_1_IN2 = 1;
	MOTOR_RIGHT_2_IN1 = 0;MOTOR_RIGHT_2_IN2 = 0;
}

void MOTOR_right_2_forward(void)
{
	//左1：-/+；右1：+/-；左2：+/-；右2：-/+；
	MOTOR_LEFT_1_IN1 = 0; MOTOR_LEFT_1_IN2 = 0;	
	MOTOR_LEFT_2_IN1 = 0; MOTOR_LEFT_2_IN2 = 0;	
	MOTOR_RIGHT_1_IN1 = 0;MOTOR_RIGHT_1_IN2 = 0;
	MOTOR_RIGHT_2_IN1 = 1;MOTOR_RIGHT_2_IN2 = 0;
}




void MOTOR_handle()
{	
	switch(g_smartCar_sta)
	{	
		case REMOTEC_STATUS_FORWARD:
		case BLUE_STATUS_FORWARD:
			MOTOR_forward();
			break;
		case REMOTEC_STATUS_LEFT:
		case BLUE_STATUS_LEFT:
			MOTOR_turn_left();
			break;
		case REMOTEC_STATUS_RIGHT:
		case BLUE_STATUS_RIGHT:
			MOTOR_turn_right();
			break;
		case REMOTEC_STATUS_BACKWARD:
		case BLUE_STATUS_BACKWARD:
			MOTOR_backward();
			break;
		case REMOTEC_STATUS_STOP:
		case BLUE_STATUS_STOP:
			MOTOR_stop();
			break;
		default:
			break;
	}
}





 
