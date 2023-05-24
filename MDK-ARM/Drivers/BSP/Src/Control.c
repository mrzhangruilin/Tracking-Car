#include "Control.h"

/**
 * @brief   电机驱动初始化函数
 * @retval  无返回值
*/
void Control_Init(void)
{
    RCC->APB2ENR |= 1<<4;               /* 使能GPIOC时钟 */
    GPIOC->CRL &= 0X00FFFFFF;           /* 给PC6和PC7清零 */
    GPIOC->CRH &= 0XFFFFFF00;           /* 给PC8和PC9清零 */
    GPIOC->CRL |= 0x33000000;  
    GPIOC->CRH |= 0x00000033;           /* 配置PC6.7.8.9的模式为开漏输出，最大速度50MHZ */
}

void Control_Forward(void)
{
    GPIOC->ODR |= (1<<6|1<<7|1<<8|1<<9);             
}

void Control_Stop(void)
{
    GPIOC->ODR &= ~(1<<6|1<<7|1<<8|1<<9);           
}

void Control_Left(void)
{
    GPIOC->ODR &= ~(1<<6|1<<8);
    GPIOC->ODR |= ~(1<<7|1<<9);             
}

void Control_Right(void)
{
    GPIOC->ODR &= ~(1<<7|1<<9);
    GPIOC->ODR |= ~(1<<6|1<<8);                
}



