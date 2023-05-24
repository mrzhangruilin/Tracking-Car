#include "stm32f10x.h" 


int main(void)
{				 
	while(1)
	{
		Control_Init();
		Control_Forward();
		Control_Left();
		Control_Right();
	}	 
} 






