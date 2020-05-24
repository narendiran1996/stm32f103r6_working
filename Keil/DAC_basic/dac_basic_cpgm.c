#include "stm32f10x.h"
#include "naren_gpio_func.h"
void DAC_basic()
{
	// configure PA4 for DAC output channel 1
	GPIO_config(A, 4, ANALOG_IN);
	
	// enable DAC clock by setting DACEN - bit 29 of RCC_APB1ENR
	RCC->APB1ENR |= (1<<29);
	
	// disable DMA - bit 12 of DAC_CR
	DAC->CR &= ~(1<<12);
	
	// for basic operation need not worry about mask and amplitte - MAMP1
	
	// diable wave genration
	// WAVE1[1:0] -- 00 of DAC_CR[7:6]
	DAC->CR &= ~(1<<7);
	DAC->CR &= ~(1<<6);
	
	// for basic operation need not worry about trigger selection - TSEL1
	
	// disable trigger slection TSEN1 - bit 2 of DAC_CR
	DAC->CR &= ~(1<<2);
	
	// enable output buffer - BOFF1 - bit 1 of DAC_CR
	// by clearing BOFF1
	DAC->CR &= ~(1<<1);
	
	
	// now let's load the data
	// lets load 12-bit right aligned by writing into DAC_DHR12R1
	// max is 2^12 - 1 = 4095
	DAC->DHR12R1 = 4444; 
	
	// let's enable the DAC for conversion
	// EN1 - bit 0 of DAC_CR
	DAC->CR |= (1<<0);
	
}

int main(void)
{
	DAC_basic();
	while(1)
	{
		
	}
}
