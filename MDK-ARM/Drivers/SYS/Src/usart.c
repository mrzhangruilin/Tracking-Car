//初始化IO 串口1
//pclk2:PCLK2时钟频率(Mhz)
//bound:波特率 
void uart_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  //使能串口时钟 
	GPIOA->CRH&=0XFFFFF00F;//IO状态设置
	GPIOA->CRH|=0X000008B0;//IO状态设置 
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位	   	   
	//波特率设置
 	USART1->BRR=mantissa; // 波特率设置	 
	USART1->CR1|=0X200C;  //1位停止,无校验位.
#if EN_USART1_RX		  //如果使能了接收
	//使能接收中断 
	USART1->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART1_IRQn,2);//组2，最低优先级 
#endif