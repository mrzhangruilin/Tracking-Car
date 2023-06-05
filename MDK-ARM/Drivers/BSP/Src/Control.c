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
#include "Tim.h"

extern  uint8_t WHEELS_LF_PW;   //脉宽，0-100
extern  uint8_t WHEELS_RF_PW;   
extern  uint8_t WHEELS_LR_PW;   
extern  uint8_t WHEELS_RR_PW;   


/**
 * @brief   电机驱动初始化函数
 * @retval  无返回值
*/
void Control_Init(void)
{
    /* 定时器6初始化 */
    TIM6_Init();			

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
    Control_SetSpeed(WHEELS_LF|WHEELS_LR|WHEELS_RF|WHEELS_RR , 0);
}

/**
 * @brief   四驱前进
 * @param   speed   0-100速度可调
*/
void Control_Forward(uint8_t speed)
{
    Control_Speed(speed , speed);
}

/**
 * @brief   四驱后退
 * @param   speed   0-100速度可调
*/
void Control_Retreat(uint8_t speed)
{
    Control_Speed(0-speed , 0-speed);
}

/**
 * @brief   四驱停止
*/
void Control_Stop(void)
{
    Control_Speed(0,0);
}

/**
 * @brief   调节轮子速度
 * @param   speed_L    左轮速度
 * @param   speed_R    右轮速度
 * 速度为±100，负值表示反转速度
*/
void Control_Speed(int8_t speed_L , int8_t speed_R)
{
    if (speed_L>=0)
    {
        Control_SwDir(WHEELS_LF|WHEELS_LR, DIR_FORWARD);
        Control_SetSpeed(WHEELS_LF|WHEELS_LR , speed_L);
    }
    else
    {
        Control_SwDir(WHEELS_LF|WHEELS_LR, DIR_RETREAT);
        Control_SetSpeed(WHEELS_LF|WHEELS_LR , 0-speed_L);
    }
    
    if (speed_R>=0)
    {
        Control_SwDir(WHEELS_RF|WHEELS_RR, DIR_FORWARD);
        Control_SetSpeed(WHEELS_RF|WHEELS_RR , speed_R);
    }
    else
    {
        Control_SwDir(WHEELS_RF|WHEELS_RR, DIR_RETREAT);
        Control_SetSpeed(WHEELS_RF|WHEELS_RR , 0-speed_R);
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
 * @param   speed   0-100
*/
void Control_SetSpeed(uint8_t wheel , uint8_t speed)
{
    if (wheel&WHEELS_LF)
    {
        WHEELS_LF_PW = speed;
    }

    if (wheel&WHEELS_RF)
    {
        WHEELS_RF_PW = speed;
    }

    if (wheel&WHEELS_LR)
    {
        WHEELS_LR_PW = speed;
    }

    if (wheel&WHEELS_RR)
    {
        WHEELS_RR_PW = speed;
    }
}
