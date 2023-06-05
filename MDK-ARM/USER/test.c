#include "main.h"
#include "stm32f10x.h" 

#include "sys.h"
#include "delay.h"
#include "Control.h"
#include "Tracking.h"
#include "Avoid.h"

/* 全局变量表 */
uint8_t WHEELS_LF_PW; 
uint8_t WHEELS_RF_PW; 
uint8_t WHEELS_LR_PW; 
uint8_t WHEELS_RR_PW;
uint8_t	g_mode;		/* 模式：寻迹、避障、遥控 */

/* 函数声明 */
void Tracking(void);
void Avoid(void);

int main(void)
{				
	/* 初始化 */
	Stm32_Clock_Init(9);	/* 系统时钟初始化 */
	delay_init(72);			/* 延时函数初始化 */
	Tracking_Init();		/* 寻迹模块初始化 */
	Control_Init();			/* 控制模块初始化 */
	Avoid_Init();			/* 避障模块初始化 */

	g_mode = MODE_TRACKING;	/* 初始化为寻迹模式 */
	g_mode = MODE_AVOID;	/* 初始化为避障模式 */
	while(1)
	{
		if(g_mode == MODE_TRACKING)
		{
			Tracking();
		}
		else if (g_mode == MODE_AVOID)
		{
			Avoid();
		}
		
	}	 
} 

void Tracking(void)
{
	if (!Tracking_MI)
	{
		Control_Speed(100 , 100);
	}
	else if (!Tracking_L2)
	{
		Control_Speed(0 , 100);
	}
	else if (!Tracking_L1)
	{
		Control_Speed(-100 , 100);
	}
	else if (!Tracking_R2)
	{
		Control_Speed(100 , 0);
	}
	else if (!Tracking_R1)
	{
		Control_Speed(100 , -100);
	}
}

void Avoid(void)
{
	switch (Avoid_Test())
	{
	case 0:
		Control_Speed(100,100);
		break;
	case 1:
		Control_Speed(-100,100);
		delay_ms(1500);
		break;
	case 2:
		Control_Speed(100,-100);
		delay_ms(1500);
		break;
	case 3:
		Control_Speed(0,0);
		break;
	default:
		break;
	}
}


