#include "stm32f10x.h" 

#include "delay.h"
#include "Control.h"

int main(void)
{				
	/* 初始化 */
	Stm32_Clock_Init(9);
	delay_init(72);
	Control_Init();

	while(1)
	{
		Control_Forward();
		delay_ms(1000);

		// Control_Left();
		// delay_ms(1000);

		// Control_Right();
		// delay_ms(1000);

		Control_Stop();
		delay_ms(1000);
	}	 
} 






