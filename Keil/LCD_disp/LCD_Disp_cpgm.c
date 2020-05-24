#include "stm32f10x.h"
#include "naren_gpio_func.h"
#include "naren_lcd_func.h"





int main(void)
{
	lcd_init();
	lcd_send_string("GOOD DAY");
	
	while(1)
	{
		
	}
}


