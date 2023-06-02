#include "stm32f10x.h" 

#include "delay.h"
#include "Control.h"
#include "Tracking.h"
#include "Tim.h"

/* 全局变量表 */
uint8_t WHEELS_LF_PW; 
uint8_t WHEELS_RF_PW; 
uint8_t WHEELS_LR_PW; 
uint8_t WHEELS_RR_PW; 

int main(void)
{				
	/* 初始化 */
	Stm32_Clock_Init(9);	/* 系统时钟初始化 */
	delay_init(72);			/* 延时函数初始化 */
	//Tracking_Init();		/* 寻迹模块初始化 */
	TIM6_Init();			/* 定时器6初始化 */
	Control_Init();			/* 控制模块初始化 */

	while(1)
	{
		Control_Forward(100);	delay_ms(1000);

		Control_Retreat(100);	delay_ms(1000);

		Control_Speed(0,100);	delay_ms(1000);

		Control_Speed(100,0);	delay_ms(1000);

		Control_Speed(-100,100);	delay_ms(1000);

		Control_Speed(100,-100);	delay_ms(1000);

		
		Control_Stop();		delay_ms(1000);
	}	 
} 






