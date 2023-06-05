#include "Tracking.h"

/*
L1  PA0
L2  PA1
MI  PA4
R2  PA5
R1  PA6
*/
void Tracking_Init(void)
{
    RCC->APB2ENR |= (1<<2);				/* GPIOA开启 */

    GPIOA->CRL &= 0XF000FF00;           /* PA0、1、4、PA5、PA6 */
    GPIOA->CRL |= 0x08880088;
}

	
	


