#ifndef _CONTROL_H__
#define _CONTROL_H__

/* 头文件定义 */
#include "sys.h"
#include "stm32f10x.h" 

/* 宏定义 */
    //wheels
#define WHEELS_LF   1
#define WHEELS_RF   2
#define WHEELS_LR   4
#define WHEELS_RR   8

#define WHEELS_ENABLE       1
#define WHEELS_DISABLE      0

    //Dir
#define DIR_FORWARD         1
#define DIR_RETREAT         0

    //TurnAround
#define TURNAROUND_LEFT     0
#define TURNAROUND_RIGHT    1

/* 函数声明 */
void Control_Init(void);
void Control_Forward(void);
void Control_Retreat(void);
void Control_Stop(void);
void Control_Left(void);
void Control_Right(void);
void Control_TurnAround(uint8_t dir);

void Control_SwDir(uint8_t wheel , uint8_t dir);
void Control_SwEnable(uint8_t wheel , uint8_t status);

#endif

