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

#define MOTOR_LEFT_1_2	1
#define MOTOR_RIGHT_1_2	2

void MOTOR_init(void);//��ʼ��
void MOTOR_handle(void);

void MOTOR_forward(void);
void MOTOR_turn_left(void);
void MOTOR_turn_right(void);
void MOTOR_backward(void);
void MOTOR_stop(void);

void MOTOR_set_speed(u8 ch,u8 speed_level);
void MOTOR_speed_up(u8 *speed_level);
void MOTOR_speed_down(u8 *speed_level);





/*********************************************

CAR

*********************************************/
typedef enum _smartCar_status
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

//��ΪTIM4����������Ϊ10���ʷ�Ϊ10��
typedef enum _smartCar_speed_level
{
	MOTOR_SPEED_LEVEL1=1,
	MOTOR_SPEED_LEVEL2=2,
	MOTOR_SPEED_LEVEL3=3,
	MOTOR_SPEED_LEVEL4=4,
	MOTOR_SPEED_LEVEL5=5,
	MOTOR_SPEED_LEVEL6=6,
	MOTOR_SPEED_LEVEL7=7,
	MOTOR_SPEED_LEVEL8=8,
	MOTOR_SPEED_LEVEL9=9,
	MOTOR_SPEED_LEVEL10=10
}smartCar_speed_level_t;

typedef enum _smartCar_speed_sta
{
	MOTOR_SPEED_STA_KEEP=0,
	MOTOR_SPEED_STA_UP=1,
	MOTOR_SPEED_STA_DOWN=2,
}smartCar_speed_sta_t;

extern smartCar_status_t g_smartCar_sta;
extern smartCar_speed_level_t g_smartCar_speed;
extern smartCar_speed_sta_t g_smartCar_speed_sta;




		 				    
#endif

