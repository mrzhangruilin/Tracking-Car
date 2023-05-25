#include "stm32f10x.h"                  // Device header

void serial_Init(void)
{

    RCC->APB2ENR|=(1<<14);
	RCC->APB2ENR|=(1<<2);
	GPIOA->CRL=0x00049000;
}
void serial_SendByte(uint8_t Byte)
{
	USART1->DR= Byte;
}	
	