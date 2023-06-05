#include "Avoid.h"
#include "Tim.h"
#include "delay.h"
#include "Control.h"

void Avoid_Init(void)
{
	RCC->APB2ENR |= (1<<2);		/* GPIOA时钟使能 */
	RCC->APB2ENR |= (1<<3);		/* GPIOB时钟使能 */

	GPIOA->CRL &= 0X0FFFFFFF;	/* PA7复用推挽输出模式 */
    GPIOA->CRL |= 0xB0000000;
	GPIOA->ODR |= (1<<7);
	GPIOB->CRL &= 0x00FFFFFF;	/* PB6-Echo上拉输入，PB7-Trig推挽输出*/
	GPIOB->CRL |= 0x34000000;
	GPIOB->ODR &= ~(1<<7);

	TIM3_Init();				/* PWM初始化 */
	TIM7_Init();				/* 测量Echo高电平时间 */
	Avoid_Turn(AVOID_MI);		/* 转到中间 */
}

/**
 * @brief	控制舵机旋转
 * @param	angle	舵机旋转角度
*/
void Avoid_Turn(uint8_t angle)
{
	TIM3->CCR2 = angle*20/180+5;
}

/**
 * @brief	检测前方障碍物
 * @retval	返回障碍物情况
 * 0-正前方无障碍物，1-左前方无障碍物，2-右前方无障碍物，3-前方都有障碍物
*/
uint8_t Avoid_Test(void)
{
	if(Avoid_Trig()>0.2)
	{
		return 0;
	}
	
	Control_Speed(0,0);			/* 先让车停下来 */

	Avoid_Turn(AVOID_LEFT);		/* 转到左边 */
	delay_ms(500);				/* 等待转向到位 */
	if(Avoid_Trig()>0.2)
	{
		Avoid_Turn(AVOID_MI);		/* 转到中间 */
		delay_ms(500);
		return 1;
	}
	
	Control_Speed(0,0);
	Avoid_Turn(AVOID_RIGHT);	/* 转到右边 */
	delay_ms(1000);
	if(Avoid_Trig()>0.2)
	{
		Avoid_Turn(AVOID_MI);		/* 转到中间 */
		delay_ms(500);
		return 2;
	}
	
	Avoid_Turn(AVOID_MI);		/* 转到中间 */
	delay_ms(500);
	return 3;
}


/**
 * @brief	触发trig引脚，开始测量
 * @retval	返回测量出的距离
 * 测量距离=（高电平时间*声速（340m/s）/2）
*/
float Avoid_Trig(void)
{
	TIM7->CNT = 0;			/* 清空计数器 */
	GPIOB->ODR &= ~(1<<7);	/* 先拉低Trig */
	GPIOB->ODR |= (1<<7);	/* 拉高Trig，触发测量 */
	delay_us(10);
	GPIOB->ODR &= ~(1<<7);				/* 拉低Trig */
	while ((GPIOB->IDR&(1<<6)) == 0);		/* 等待高电平 */
	TIM7->CR1 |= (1<<0);    				/* 使能计数器 */
	while (GPIOB->IDR&(1<<6));		/* 等待低电平或者距离超出范围 */
	TIM7->CR1 &= ~(1<<0);    			/* 关闭计数器 */
	return (TIM7->CNT*0.00001*340/2);	/* CNT是10us一次*/
}
