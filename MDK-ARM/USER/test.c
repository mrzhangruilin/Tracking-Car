#include "stm32f10x.h" 

#include "delay.h"
#include "Control.h"
#include "Tracking.h"

int main(void)
{				
	/* 初始化 */
	Stm32_Clock_Init(9);	/* 系统时钟初始化 */
	delay_init(72);			/* 延时函数初始化 */
	Tracking_Init();		/* 寻迹模块初始化 */
	Control_Init();			/* 控制模块初始化 */


	while(1)
	{
		if (Tracking_MI == 0)
		{
			Control_Forward();
		}
		else if (Tracking_L1 == 0)
		{
			Control_Left();
		}else if (Tracking_R1 == 0)
		{
			Control_Right();
		}
	}	 
} 






