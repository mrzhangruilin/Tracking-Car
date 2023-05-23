#ifndef _CONTROL_H__
#define _CONTROL_H__

//头文件定义
#include "sys.h"
#include "stm32f10x.h" 



//函数声明		//接口	//开漏输出
void Control_Init(void);
void Control_Forward(void);
void Control_Left(void);
void Control_Right(void);


#endif

