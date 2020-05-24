#include "stm32f10x.h"
#include "naren_gpio_func.h"
#include "naren_lcd_func.h"



void ADC_calibration()
{
	// let's enable the Alternate Function clock - AFIOEN - bit0 of RCC_APB2ENR
	RCC->APB2ENR |= (1<<0);
	
	// let's enable ADC1 clock by enabling ADC1EN - bit 9 of RCC_APB2ENR
	RCC->APB2ENR |= (1<<9);
	
	// powering on the ADC by setting ADCON bit - bit 0 of ADCx_CR2
	ADC1->CR2 |= (1<<0);
	
	// wait for some time to power on
	for(int i=0;i<5;i++);
	
	// let's calibration by setting CAL bit - bit 2 of ADCx_CR2
	//ADC1->CR2 |= (1<<2);
	
	
	// ADC OFF
	ADC1->CR2 &= ~(1<<0);
	

}


void ADC1_init_channel_config(unsigned char channel_no_) 
{
	if(channel_no_<=7)
		GPIO_config(A, channel_no_, ANALOG_IN);
	else if(channel_no_<=9)
		GPIO_config(B, channel_no_ - 8, ANALOG_IN);
	else if(channel_no_<=15)
		GPIO_config(C, channel_no_ - 10, ANALOG_IN);
}



uint16_t ADC1_single_channel(unsigned char channel_no_)
{	
	ADC1_init_channel_config(channel_no_);
	
	// selecting which channel to be sacned for first conversion
	ADC1->SQR3 =  channel_no_;
	
	
	// disbale scan mode by clearing SCAN - bit 8 of ADCx_CR1
	ADC1->CR1 &= ~(1<<8);
	
	// disabling the interrupt
	// by clearing EOCIE - bit 5 of ADCx_CR1	
	ADC1->CR1 &= ~(1<<5);
	
	// setting the data aligment 
	// to right align by clearing ALIGN - bit 11 of ADCx_CR2
	ADC1->CR2 &= ~(1<<11);
	
	// single ADC by clearing CONT - bit 1 of ADCx_CR2
	ADC1->CR2 = ADC1->CR2 & ~(1<<1);
	
	// start ADC by setting ADCON - bit 0 of ADCx_CR2
	ADC1->CR2 = ADC1->CR2 | (1<<0); 
	
//	ADC1->CR1 = ADC_CR1_EOCIE; // Enable interrupt form End Of Conversion
	//NVIC_EnableIRQ(ADC1_2_IRQn); // Enable interrupt form ACD1 peripheral

	 // Turn on conversion
	ADC1->CR2 = ADC1->CR2 | (1<<0); 
	
	// check if conversion over
	while((ADC1->SR & (1<<1)) == 0);
	
	// read the value also this resets the ADC
	return ADC1->DR;
	
}


void ADC1_continuous_channel(unsigned char channel_no_)
{
	ADC1_init_channel_config(channel_no_);
	
	// selecting which channel to be sacned for first conversion
	ADC1->SQR3 =  channel_no_;
	
	
	// disbale scan mode by clearing SCAN - bit 8 of ADCx_CR1
	ADC1->CR1 &= ~(1<<8);
	
	// enabling the interrupt
	// by setting EOCIE - bit 5 of ADCx_CR1	
	ADC1->CR1 |= (1<<5);
	
	// setting the data aligment 
	// to right align by clearing ALIGN - bit 11 of ADCx_CR2
	ADC1->CR2 &= ~(1<<11);
	
	// contious ADC by clearing CONT - bit 1 of ADCx_CR2
	ADC1->CR2 = ADC1->CR2 | (1<<1);
	
	// start ADC by setting ADCON - bit 0 of ADCx_CR2
	ADC1->CR2 = ADC1->CR2 | (1<<0); 
	

	 // Turn on conversion
	ADC1->CR2 = ADC1->CR2 | (1<<0); 
	
	
	// Enable interrupt form ACD1 peripheral
	NVIC_EnableIRQ(ADC1_2_IRQn);
	
}	

volatile unsigned int mtd=1;
int main(void)
{
	ADC_calibration();
	lcd_init();
	lcd_display_on_cursor_on_blink_on();
	ADC1_continuous_channel(0);
	
	while(1)
	{
		//lcd_set_cursor(1,1);
		//lcd_print_num( mtd,10);
		
		
	 	lcd_print_num(ADC1_single_channel(8),10);
		//lcd_print_num(ADC1_single_channel(0),10);
		//lcd_print_num(ADC1_single_channel(1),10);
		
		 
	}
}

void ADC1_2_IRQHandler(void)
{

	if((ADC1->SR & (1<<1)) != 0)
	{
		
		mtd = ADC1->DR;
	}
}

