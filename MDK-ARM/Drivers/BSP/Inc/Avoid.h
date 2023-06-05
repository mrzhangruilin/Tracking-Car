#ifndef _AVOID_H_
#define _AVOID_H_


/* 头文件包含 */
#include "sys.h"
#include "stm32f10x.h"

/* 宏定义 */
#define AVOID_RIGHT     0
#define AVOID_RIHGT_45  45
#define AVOID_MI        90
#define	AVOID_LEFT_45	135
#define	AVOID_LEFT		180


/* 函数声明 */
void Avoid_Init(void);
void Avoid_Turn(uint8_t angle);
uint8_t Avoid_Test(void);
float Avoid_Trig(void);
#endif


