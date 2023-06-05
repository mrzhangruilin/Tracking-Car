#ifndef _TRACKING_H__
#define _TRACKING_H__

/* 头文件包含 */
#include "sys.h"
#include "stm32f10x.h" 

/* 函数声明 */
void Tracking_Init(void);

/* 宏定义 */
#define Tracking_L1 ((GPIOA->IDR&1<<0)>>0)
#define Tracking_L2 ((GPIOA->IDR&1<<1)>>1)
#define Tracking_MI ((GPIOA->IDR&1<<4)>>4)
#define Tracking_R1 ((GPIOA->IDR&1<<6)>>6)
#define Tracking_R2 ((GPIOA->IDR&1<<5)>>5)

#endif


