#include "stm32f10x.h" 
#include "usart.h"
#include "delay.h"

void USART1_IRQHandler(void)
{
	u8 data;
	data=USART1->DR;
	USART1->DR=data;
}

void usart_init(u32 pclk2,u32 bound)
	{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	
		
	RCC->APB2ENR|=(1<<14);
	RCC->APB2ENR|=(1<<2);
	GPIOA->CRH&=0XFFFFF00F;
	GPIOA->CRH|=0x000008B0;
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位
	USART1->BRR=mantissa;
    USART1->CR1|=0x200C;//写一句上就行
    
    USART1->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(0,0,USART1_IRQn,0);//组2，最低优先级 
	}
int serial_SendByte(int Byte)
{	
		USART1->DR=Byte;
		return Byte;
	
}	
int main(void)
{	
	Stm32_Clock_Init(9);
	delay_init(8);	 
	usart_init(72,9600); 	
    
	while(1)
	{
	
	}
	
} 






