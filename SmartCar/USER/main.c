#include "head_include.h"
 
 
/************************************************
 ALIENTEKս��STM32������ʵ��1
 �����ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/


 int main(void)
 {	
 
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //
 	delay_init();
	USART1_init(115200);

	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	HC05_init();
	MOTOR_init();
	REMOTECONTROL_init();
	
	while(1)
	{
		HC05_handle();
		MOTOR_handle();

		LED0 =!LED0;
		
		


	}
 }

void hardware_init();


