#include "head_include.h"
 
 
/************************************************
 ALIENTEK战舰STM32开发板实验1
 跑马灯实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/


 int main(void)
 {	
 
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //
 	delay_init();
	USART1_init(115200);

	LED_Init();		  	//初始化与LED连接的硬件接口
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


