#include "stm32f10x.h"
#include "naren_gpio_func.h"

void init_external_hadware_interrupt(enum PORTS_MINE port_, uint8_t pin_, uint8_t rising0_falling1)
{		
	// we make it pull down - can be anything
	GPIO_config(port_, pin_ ,FLOATING_IN);
	
	
	uint16_t mask_val=0;
	uint8_t port_val=0;
	uint8_t shift_val=0;

	/* find mask value for selection of EXTI0,EXTI1,EXTI2, .., EXTI15 */
	/* find shift value for placing the port value in that particular EXTIx */
	if((pin_ == 0) || (pin_ == 4) || (pin_ == 8) || (pin_ == 12))	
	{
		mask_val = 0xFFF0;	
		shift_val = 0;
	}
	else if((pin_ == 1) || (pin_ == 5) || (pin_ == 9) || (pin_ == 13))	
	{
		mask_val = 0xFF0F;
		shift_val = 4;
	}
	else if((pin_ == 2) || (pin_ == 6) || (pin_ == 10) || (pin_ == 14))	
	{
		mask_val = 0xF0FF;	
		shift_val = 8;
	}
	else if((pin_ == 3) || (pin_ == 7) || (pin_ == 11) || (pin_ == 15))	
	{
		mask_val = 0x0FFF;
		shift_val = 12;
	}
	
	/* find the portvalue to be placed */
	if(port_ == A)
	{
		port_val = 0b0000;
	}
	else if(port_ == B)
	{
		port_val = 0b0001;
	}
	else if(port_ == C)
	{
		port_val = 0b0010;
	}
	
	/* placing the port values and pin vaues in particular AFIO_EXTICR registers */
	if(pin_ <= 3)
		AFIO->EXTICR[0] = (AFIO->EXTICR[0] & mask_val) | (port_val << shift_val);
	else if(pin_ <= 7)
		AFIO->EXTICR[1] = (AFIO->EXTICR[1] & mask_val) | (port_val << shift_val);
	else if(pin_ <= 11)
		AFIO->EXTICR[2] = (AFIO->EXTICR[2] & mask_val) | (port_val << shift_val);
	else if(pin_ <= 15)
		AFIO->EXTICR[3] = (AFIO->EXTICR[3] & mask_val) | (port_val << shift_val);
	
	/* selection between rising or falling edge */
	if(rising0_falling1 == 0)	
		EXTI->RTSR |= (1<<pin_);
	else
		EXTI->FTSR |= (1<<pin_);
	
	// Interupt Mask should be disbaled for Interrupt request line
	EXTI->IMR |= (1<<pin_);	
	
	
	/* selcting adn enabled of ISR and IRQ */
	if(pin_== 0)
		NVIC_EnableIRQ(EXTI0_IRQn);
	else if(pin_== 1)
		NVIC_EnableIRQ(EXTI1_IRQn);
	else if(pin_== 2)
		NVIC_EnableIRQ(EXTI2_IRQn);
	else if(pin_== 3)
		NVIC_EnableIRQ(EXTI3_IRQn);
	else if(pin_== 4)
		NVIC_EnableIRQ(EXTI4_IRQn);
	else if(pin_<= 9)
		NVIC_EnableIRQ(EXTI9_5_IRQn);
	else if(pin_<= 15)
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	
}


int main(void)
{
	for(int i=0;i<15;i++)
	{
		GPIO_config(C, i, GPIO_OUTPUT_PUSH_PULL);
		GPIO_set_out(C, i, 0);
	}
	
//	init_external_hadware_interrupt(A, 0 , 0);
//	init_external_hadware_interrupt(A, 1 , 1);
//	init_external_hadware_interrupt(A, 2 , 1);
//	init_external_hadware_interrupt(A, 3 , 0);
//	init_external_hadware_interrupt(A, 4 , 1);
//	init_external_hadware_interrupt(A, 5 , 0);
//	init_external_hadware_interrupt(A, 6 , 0);
	init_external_hadware_interrupt(A, 7 , 0);
//	init_external_hadware_interrupt(A, 8 , 1);
//	init_external_hadware_interrupt(A, 9 , 1);
//	init_external_hadware_interrupt(A, 10 , 1);
//	init_external_hadware_interrupt(A, 11 , 1);
//	init_external_hadware_interrupt(A, 12 , 0);
//	init_external_hadware_interrupt(A, 13 , 0);
//	init_external_hadware_interrupt(A, 14 , 0);
//	init_external_hadware_interrupt(A, 15 , 0);
	
	while(1)
	{
		
	}
}

void EXTI0_IRQHandler(void)
{
	if(GPIO_read_out(C,0, 1) == 0)
		GPIO_set_out(C, 0, 1);
	else
		GPIO_set_out(C, 0, 0);
	EXTI->PR |= (1<<0);	
}

void EXTI1_IRQHandler(void)
{
	if(GPIO_read_out(C,1, 1) == 0)
		GPIO_set_out(C, 1, 1);
	else
		GPIO_set_out(C, 1, 0);
	EXTI->PR |= (1<<1);	
}

void EXTI2_IRQHandler(void)
{
	if(GPIO_read_out(C,2, 1) == 0)
		GPIO_set_out(C, 2, 1);
	else
		GPIO_set_out(C, 2, 0);
	EXTI->PR |= (1<<2);	
}
void EXTI3_IRQHandler(void)
{
	if(GPIO_read_out(C,3, 1) == 0)
		GPIO_set_out(C, 3, 1);
	else
		GPIO_set_out(C, 3, 0);
	EXTI->PR |= (1<<3);	
}

void EXTI4_IRQHandler(void)
{
	if(GPIO_read_out(C,4, 1) == 0)
		GPIO_set_out(C, 4, 1);
	else
		GPIO_set_out(C, 4, 0);
	EXTI->PR |= (1<<4);	
}
void EXTI9_5_IRQHandler(void)
{
	uint8_t pin_f = 0;
	if((EXTI->PR & (1<<5)) != 0)
		pin_f = 5;
	else if((EXTI->PR & (1<<6)) != 0)
		pin_f = 6;
	else if((EXTI->PR & (1<<7)) != 0)
		pin_f = 7;
	else if((EXTI->PR & (1<<8)) != 0)
		pin_f = 8;
	else if((EXTI->PR & (1<<9)) != 0)
		pin_f = 9;
	
	if(GPIO_read_out(C,pin_f, 1) == 0)
		GPIO_set_out(C, pin_f, 1);
	else
		GPIO_set_out(C, pin_f, 0);
	
	EXTI->PR |= (1<<pin_f);	
}
void EXTI15_10_IRQHandler(void)
{
	uint8_t pin_f = 0;
	if((EXTI->PR & (1<<10)) != 0)
		pin_f = 10;
	else if((EXTI->PR & (1<<11)) != 0)
		pin_f = 11;
	else if((EXTI->PR & (1<<12)) != 0)
		pin_f = 12;
	else if((EXTI->PR & (1<<13)) != 0)
		pin_f = 13;
	else if((EXTI->PR & (1<<14)) != 0)
		pin_f = 14;
	else if((EXTI->PR & (1<<15)) != 0)
		pin_f = 15;
	
	if(GPIO_read_out(C,pin_f, 1) == 0)
		GPIO_set_out(C, pin_f, 1);
	else
		GPIO_set_out(C, pin_f, 0);
	
	EXTI->PR |= (1<<pin_f);	
}
