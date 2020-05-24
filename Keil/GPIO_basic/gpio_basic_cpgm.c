#include "stm32f10x.h"
#include "naren_gpio_func.h"

int main(void)
{
	
	GPIO_config(C,8,FLOATING_IN);
	GPIO_config(C,9,GPIO_OUTPUT_OPEN_DRAIN);
	
	uint8_t val;
	while(1)
	{
		val = GPIO_read_out(C, 8);
		if(val == 0)
			GPIO_set_out(C,9,0);
		else
			GPIO_set_out(C,9,1);
		
	}
}
