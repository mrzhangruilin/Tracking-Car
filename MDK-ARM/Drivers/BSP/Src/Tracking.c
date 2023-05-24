#include "Tracking.h"
#include "Control.h"

void Tracking_Init(void)
{
    RCC -> APB2ENR|=(1<<0);//exti开启
	EXTI->IMR|=0x00031;
	EXTI->FTSR|=0x00031;
	EXTI->SWIER|=0X00031;

    MY_NVIC_Init(0,0,EXTI0_IRQn, 0);
    MY_NVIC_Init(0,0,EXTI4_IRQn, 0);//配置优先级
	MY_NVIC_Init(0,0,EXTI9_5_IRQn, 0);
}
/**
 * @brief   左转中断
 * @brief   直走中断
 * @brief   右转中断
*/
void EXTI0_IRQHandler(void)//中断函数
{
	if(GPIOA->ODR&&(1<<0))
	{   
                                                                        //调用左转
        EXTI->PR|=(1<<0);
	}
}
void EXTI4_IRQHandler(void)//中断函数
{
	if(GPIOA->ODR&&(1<<4))
	{   
                                                                        //直行
        EXTI->PR|=(1<<4);
	}
}
void EXTI9_5_IRQHandler(void)//中断函数
{
	
	if(GPIOA->ODR&&(1<<6))
	{   
                                                                       //右转
		EXTI->PR|=(1<<6);
	}
}
	
	
	


