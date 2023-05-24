#include "Control.h"

/**
 * @brief   电机驱动初始化函数
 * @param   参数一  void
 * @retval  无返回值
*/
void Control_Init(void)
{
    RCC->APB2ENR |= 1<<4;               /*使能GPIOC时钟*/
    GPIOC->CRL &= 0X00FFFFFF;           /*给PC6和PC7清零*/
    GPIOC->CRH &= 0XFFFFFF00;           /*给PC8和PC9清零*/
    GPIOC->CRL |= 0x33000000;
    GPIOC->CRH |= 0x00000033;           /*配置PC6.7.8.9的模式为推挽输出，最大速度50MHZ*/
}
void Control_Forward(void)
{
    GPIOC->ODR |= (1<<6);
    GPIOC->ODR |= (1<<7);
    GPIOC->ODR |= (1<<8);
    GPIOC->ODR |= (1<<9);               /*四个PC口均输出高电平*/
}
void Control_Left(void)
{
    GPIOC->ODR |= (1<<6);
    GPIOC->ODR &= ~(1<<7);
    GPIOC->ODR |= (1<<8);
    GPIOC->ODR &= ~(1<<9);               /*控制左前轮和左后轮的PC口输出高电平，控制右前轮和右后轮的PC口输出高电平*/
}
void Control_Right(void)
{
    GPIOC->ODR &= ~(1<<6);
    GPIOC->ODR |= (1<<7);
    GPIOC->ODR &= ~(1<<8);
    GPIOC->ODR |= (1<<9);                 /*控制左前轮和左后轮的PC口输出低电平，控制右前轮和右后轮的PC口输出高电平*/
}
void Control_stop(void)
{
    GPIOC->ODR &= ~(1<<6);
    GPIOC->ODR &= ~(1<<7);
    GPIOC->ODR &= ~(1<<8);
    GPIOC->ODR &= ~(1<<9);                /*四个PC口均输出低电平*/
}


