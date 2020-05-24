#include "stm32f10x.h"
int main(void)
{
	int i;
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	

	GPIOC->CRH &= ~(0X0F << 20);
	GPIOC->CRH |= (1<<21);

	while(1)
	{
		GPIOC->BSRR = (1 << 13);
		for(i=0;i<1000;i++);
		GPIOC->BRR = (1 << 13);
		for(i=0;i<1000;i++);

	}
}

