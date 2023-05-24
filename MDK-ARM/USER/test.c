#include "stm32f10x.h" 


#include "Control.h"

int main(void)
{				
	/* 初始化 */
	Stm32_Clock_Init(9);
	Control_Init();


	while(1)
	{
		Control_Forward();
		
	}	 
} 






