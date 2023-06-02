#include "Tim.h"

extern  uint8_t WHEELS_LF_PW;   //脉宽，0-100
extern  uint8_t WHEELS_RF_PW;   
extern  uint8_t WHEELS_LR_PW;   
extern  uint8_t WHEELS_RR_PW;   

uint8_t	g_cnt;

/**
 * @brief   定时器6初始化
 * 由于四个轮子输出PWM方波的引脚没有被定时器复用
 * 所以用定时器6来输出PWM方波控制四个引脚
*/
void TIM6_Init(void)
{
	RCC->APB1ENR |= (1<<4);	/* TIM6时钟使能 */
    TIM6->CR1 |= (1<<7);    /* 预装载使能 */
    TIM6->DIER |= (1<<0);   /* 使能更新中断 */
    TIM6->PSC = 719;		/* 预分频，10Khz时钟，周期0.1ms */
    TIM6->ARR = 100;        /* 自动重装载值，10ms */

	MY_NVIC_Init(0,0,TIM6_IRQn,0);

    TIM6->CR1 |= (1<<0);    /* 使能计数器 */
}


void TIM6_IRQHandler(void)
{
	if (g_cnt < 100)
	{
		g_cnt++;
		if (g_cnt<WHEELS_LF_PW)
		{
			GPIOB->ODR |= (1<<3);
		}
		else
		{
			GPIOB->ODR &= ~(1<<3);
		}
		
		if (g_cnt<WHEELS_RF_PW)
		{
			GPIOB->ODR |= (1<<8);
		}
		else
		{
			GPIOB->ODR &= ~(1<<8);
		}

		if (g_cnt<WHEELS_LR_PW)
		{
			GPIOC->ODR |= (1<<1);
		}
		else
		{
			GPIOC->ODR &= ~(1<<1);
		}

		if (g_cnt<WHEELS_RR_PW)
		{
			GPIOC->ODR |= (1<<4);
		}
		else
		{
			GPIOC->ODR &= ~(1<<4);
		}
	}
	else
	{
		g_cnt = 0;
	}
	TIM6->SR &= ~(1<<0);		/* 清除标志位 */
}

