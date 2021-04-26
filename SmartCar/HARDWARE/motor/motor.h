#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"

/**************************************************************
v1：just can move！

***************************************************************/

/**************************************************************
MOTOR:
（1）ENA、IN1、IN2:控制OU1、OU2输出，ENB、IN3、IN4:控制OU3、OU4输出，
ENA	IN1	IN2	直流电机状态
0	X	X	停止
1	0	0	制动
1	0	1	正传
1	1	0	反转
1	1	1	制动
（2）MCU引脚、驱动板引脚、电机关系、电压、前进方向、电机转动方向
PF0/PF1	MOTOR_LEFT_IN1/MOTOR_LEFT_IN2	左1电机	-/+ 向前 正传
PF3/PF4	MOTOR_LEFT_IN3/MOTOR_LEFT_IN4	右1电机 -/+ 向前 反传
PF5/PF6	MOTOR_RIGHT_IN1/MOTOR_RIGHT_IN2	右2电机 +/- 向前 反传
PF7/PF8	MOTOR_RIGHT_IN3/MOTOR_RIGHT_IN4	左2电机 +/- 向前 正传

***************************************************************/

#define MOTOR_LEFT_IN1 PFout(0)		//左1电机 
#define MOTOR_LEFT_IN2 PFout(1)
#define MOTOR_LEFT_IN3 PFout(2)		//右1电机 
#define MOTOR_LEFT_IN4 PFout(3)
#define MOTOR_RIGHT_IN1 PFout(4)	//右2电机 
#define MOTOR_RIGHT_IN2 PFout(5)
#define MOTOR_RIGHT_IN3 PFout(6)	//左2电机 
#define MOTOR_RIGHT_IN4 PFout(7)

#define MOTOR_LEFT_1_IN1 MOTOR_LEFT_IN1		//左1电机 
#define MOTOR_LEFT_1_IN2 MOTOR_LEFT_IN2
#define MOTOR_RIGHT_1_IN1 MOTOR_LEFT_IN3	//右1电机 
#define MOTOR_RIGHT_1_IN2 MOTOR_LEFT_IN4
#define MOTOR_RIGHT_2_IN1 MOTOR_RIGHT_IN1	//右2电机 
#define MOTOR_RIGHT_2_IN2 MOTOR_RIGHT_IN2
#define MOTOR_LEFT_2_IN1 MOTOR_RIGHT_IN3	//左2电机 
#define MOTOR_LEFT_2_IN2 MOTOR_RIGHT_IN4


void MOTOR_init(void);//初始化
void MOTOR_forward(void);
void MOTOR_turn_left(void);
void MOTOR_turn_right(void);
void MOTOR_backward(void);
void MOTOR_stop(void);

void MOTOR_move();


/*********************************************

CAR

*********************************************/
typedef enum smartCar_status
{
	REMOTEC_STATUS_STOP = 0,
	REMOTEC_STATUS_FORWARD,
	REMOTEC_STATUS_LEFT,
	REMOTEC_STATUS_RIGHT,
	REMOTEC_STATUS_BACKWARD,

	BLUE_STATUS_STOP=10,
	BLUE_STATUS_FORWARD,
	BLUE_STATUS_LEFT,
	BLUE_STATUS_RIGHT,
	BLUE_STATUS_BACKWARD
}smartCar_status_t;

extern smartCar_status_t g_smartCar_sta;












		 				    
#endif

