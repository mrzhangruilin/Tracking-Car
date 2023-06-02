#include "Tracking.h"
#include "Control.h"

void Tracking_Init(void)
{
    RCC->APB2ENR |= (1<<2);				/* GPIOA开启 */

    GPIOA->CRL &= 0XF0F0FFF0;           /* PA0、PA4、PA6 */
    GPIOA->CRL |= 0x08880088;
}

	
	


