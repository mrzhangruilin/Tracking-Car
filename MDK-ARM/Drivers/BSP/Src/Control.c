/**
 * LF_1		PB0
 * LF_2		PB1
 * LF_PWM	PB3
 * RF_1		PB4
 * RF_2		PB5
 * RF_PWM	PB8
 * 
 * LR_1     PB9
 * LR_2     PC0
 * LR_PWM   PC1
 * RR_1     PC2
 * RR_2     PC3
 * RR_PWM   PC4
*/

#include "Control.h"

/**
 * @brief   电机驱动初始化函数
 * @retval  无返回值
*/
void Control_Init(void)
{
    /* GPIOB GPIOC AFIO时钟使能 */
    RCC->APB2ENR |= (1<<3|1<<4|1<<0);
  
    /* JTAG引脚重映射 */
    AFIO->MAPR &= ~(7<<24);             
    AFIO->MAPR |= (2<<24);              /* 关闭JTAG，启用SWD */


    GPIOB->CRL &= 0xFF000F00;			/* 清零PB0 1 3 4 5 */
    GPIOB->CRH &= 0XFFFFFF00;           /* 清零PB8 9 */
    GPIOC->CRL &= 0xFFF00000;			/* 清零PC0 1 2 3 4*/
	GPIOB->CRL |= 0X00333033;			/* 通用推挽输出模式 */
    GPIOB->CRH |= 0x00000033;
    GPIOC->CRL |= 0X00033333;

    Control_SwDir(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , DIR_FORWARD);
    Control_SwEnable(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , WHEELS_DISABLE);
}

/**
 * @brief   四驱前进
*/
void Control_Forward(void)
{
    Control_SwDir(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , DIR_FORWARD);
    Control_SwEnable(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , WHEELS_ENABLE);
}

/**
 * @brief   四驱后退
*/
void Control_Retreat(void)
{
    Control_SwDir(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , DIR_RETREAT);
    Control_SwEnable(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , WHEELS_ENABLE);
}

/**
 * @brief   四驱停止
*/
void Control_Stop(void)
{
    Control_SwEnable(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , WHEELS_DISABLE);
}

/**
 * @brief   左转
*/
void Control_Left(void)
{
    Control_SwDir(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , DIR_FORWARD);
    Control_SwEnable(WHEELS_LF|WHEELS_LR , WHEELS_DISABLE);
    Control_SwEnable(WHEELS_RF|WHEELS_RR , WHEELS_ENABLE);
}

/**
 * @brief   右转
*/
void Control_Right(void)
{
    Control_SwDir(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , DIR_FORWARD);
    Control_SwEnable(WHEELS_LF|WHEELS_LR , WHEELS_ENABLE);
    Control_SwEnable(WHEELS_RF|WHEELS_RR , WHEELS_DISABLE);
}

/**
 * @brief   原地掉头
 * @param   dir 方向，向左或向右掉头
*/
void Control_TurnAround(uint8_t dir)
{
    if (dir == TURNAROUND_LEFT)
    {
        Control_SwDir(WHEELS_LF|WHEELS_LR , DIR_RETREAT);
        Control_SwDir(WHEELS_RF|WHEELS_RR , DIR_FORWARD);
        Control_SwEnable(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , WHEELS_ENABLE);
    }
    else
    {
        Control_SwDir(WHEELS_LF|WHEELS_LR , DIR_FORWARD);
        Control_SwDir(WHEELS_RF|WHEELS_RR , DIR_RETREAT);
        Control_SwEnable(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , WHEELS_ENABLE);
    }
}

/**
 * @brief   选择轮子方向
 * @param   wheel   参考表wheels
 * @param   dir     DIR_FORWARD     DIR_RETREAT
 * 选择轮子可以同时选择多个轮子
*/
void Control_SwDir(uint8_t wheel , uint8_t dir)
{
    if (wheel&WHEELS_LF)
    {
        if (dir == DIR_FORWARD)        //前进
        {
            GPIOB->ODR |= (1<<0);
            GPIOB->ODR &= ~(1<<1);
        }
        else
        {
            GPIOB->ODR &= ~(1<<0);
            GPIOB->ODR |= (1<<1);
        }
    }

    if (wheel&WHEELS_RF)
    {
        if (dir == DIR_FORWARD)        //前进
        {
            GPIOB->ODR |= (1<<4);
            GPIOB->ODR &= ~(1<<5);
        }
        else
        {
            GPIOB->ODR &= ~(1<<4);
            GPIOB->ODR |= (1<<5);
        }
    }
    
    if (wheel&WHEELS_LR)
    {
        if (dir == DIR_FORWARD)        //前进
        {
            GPIOB->ODR |= (1<<9);
            GPIOC->ODR &= ~(1<<0);
        }
        else
        {
            GPIOB->ODR &= ~(1<<9);
            GPIOC->ODR |= (1<<0);
        }
    }
    
    if (wheel&WHEELS_RR)
    {
        if (dir == DIR_FORWARD)        //前进
        {
            GPIOC->ODR |= (1<<2);
            GPIOC->ODR &= ~(1<<3);
        }
        else
        {
            GPIOC->ODR &= ~(1<<2);
            GPIOC->ODR |= (1<<3);
        }
    }
}

/**
 * @brief   控制轮子使能
 * @param   wheel   参考表wheels
 * @param   status  Enable or Disable
*/
void Control_SwEnable(uint8_t wheel , uint8_t status)
{
    if (wheel&WHEELS_LF)
    {
        if (status == WHEELS_ENABLE)
        {
            GPIOB->ODR |= (1<<3);
        }
        else
        {
            GPIOB->ODR &= ~(1<<3);
        }
    }

    if (wheel&WHEELS_RF)
    {
        if (status == WHEELS_ENABLE)
        {
            GPIOB->ODR |= (1<<8);
        }
        else
        {
            GPIOB->ODR &= ~(1<<8);
        }
    }

    if (wheel&WHEELS_LR)
    {
        if (status == WHEELS_ENABLE)
        {
            GPIOC->ODR |= (1<<1);
        }
        else
        {
            GPIOC->ODR &= ~(1<<1);
        }
    }

    if (wheel&WHEELS_RR)
    {
        if (status == WHEELS_ENABLE)
        {
            GPIOC->ODR |= (1<<4);
        }
        else
        {
            GPIOC->ODR &= ~(1<<4);
        }
    }
}
