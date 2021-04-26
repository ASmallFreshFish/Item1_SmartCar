#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h"

/**************************************************************
v1��just can move��

***************************************************************/

/**************************************************************
MOTOR:
��1��ENA��IN1��IN2:����OU1��OU2�����ENB��IN3��IN4:����OU3��OU4�����
ENA	IN1	IN2	ֱ�����״̬
0	X	X	ֹͣ
1	0	0	�ƶ�
1	0	1	����
1	1	0	��ת
1	1	1	�ƶ�
��2��MCU���š����������š������ϵ����ѹ��ǰ�����򡢵��ת������
PF0/PF1	MOTOR_LEFT_IN1/MOTOR_LEFT_IN2	��1���	-/+ ��ǰ ����
PF3/PF4	MOTOR_LEFT_IN3/MOTOR_LEFT_IN4	��1��� -/+ ��ǰ ����
PF5/PF6	MOTOR_RIGHT_IN1/MOTOR_RIGHT_IN2	��2��� +/- ��ǰ ����
PF7/PF8	MOTOR_RIGHT_IN3/MOTOR_RIGHT_IN4	��2��� +/- ��ǰ ����

***************************************************************/

#define MOTOR_LEFT_IN1 PFout(0)		//��1��� 
#define MOTOR_LEFT_IN2 PFout(1)
#define MOTOR_LEFT_IN3 PFout(2)		//��1��� 
#define MOTOR_LEFT_IN4 PFout(3)
#define MOTOR_RIGHT_IN1 PFout(4)	//��2��� 
#define MOTOR_RIGHT_IN2 PFout(5)
#define MOTOR_RIGHT_IN3 PFout(6)	//��2��� 
#define MOTOR_RIGHT_IN4 PFout(7)

#define MOTOR_LEFT_1_IN1 MOTOR_LEFT_IN1		//��1��� 
#define MOTOR_LEFT_1_IN2 MOTOR_LEFT_IN2
#define MOTOR_RIGHT_1_IN1 MOTOR_LEFT_IN3	//��1��� 
#define MOTOR_RIGHT_1_IN2 MOTOR_LEFT_IN4
#define MOTOR_RIGHT_2_IN1 MOTOR_RIGHT_IN1	//��2��� 
#define MOTOR_RIGHT_2_IN2 MOTOR_RIGHT_IN2
#define MOTOR_LEFT_2_IN1 MOTOR_RIGHT_IN3	//��2��� 
#define MOTOR_LEFT_2_IN2 MOTOR_RIGHT_IN4


void MOTOR_init(void);//��ʼ��
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

