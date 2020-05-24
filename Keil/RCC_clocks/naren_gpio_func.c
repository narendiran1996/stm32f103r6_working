#include "stm32f10x.h"
#include "naren_gpio_func.h"





unsigned char GPIO_read_out(enum PORTS_MINE port_, unsigned char pin_, unsigned char in0_out1)
{
	if(port_ == A)
	{
		if(in0_out1 == 0)	
			return ((GPIOA->IDR & (1<<pin_)) == 0) ? 0 : 1;
		else
			return ((GPIOA->ODR & (1<<pin_)) == 0) ? 0 : 1;
	}
	else if(port_ == B)
	{
		if(in0_out1 == 0)	
			return ((GPIOB->IDR & (1<<pin_)) == 0) ? 0 : 1;
		else
			return ((GPIOB->ODR & (1<<pin_)) == 0) ? 0 : 1;
	}
	else if(port_ == C)
	{
		if(in0_out1 == 0)	
			return ((GPIOC->IDR & (1<<pin_)) == 0) ? 0 : 1;
		else
			return ((GPIOC->ODR & (1<<pin_)) == 0) ? 0 : 1;
	}
	return 0;
}


void GPIOA_config(unsigned char pin_,enum CONFIGURATION_MODE config_)
{
	unsigned char x,pos;
	unsigned int L_CNF_MODE, H_CNF_MODE;
	L_CNF_MODE = H_CNF_MODE = 0;
	if(pin_ <= 7)
	{
		x=pin_;
		// gettinG the pins' corresponding 4 bit CONF and MODE
		pos = x<<2;
		L_CNF_MODE = (GPIOA->CRL & ~((1 << (pos+3)) | (1 << (pos+2) | (1 << (pos+1)) | (1 << (pos+0)))));
	}
	else
	{
		x=pin_-8;
		// gettinG the pins' corresponding 4 bit CONF and MODE
		pos = x<<2;
		H_CNF_MODE = (GPIOA->CRH & ~((1 << (pos+3)) | (1 << (pos+2) | (1 << (pos+1)) | (1 << (pos+0)))));
	}
		
	// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
	switch(config_)
	{
		
		case GPIO_OUTPUT_PUSH_PULL: 
		{		
			if(pin_ <= 7)
			{
				// for GPIO_OUTPUT_PUSH_PULL - CNF[1:0] =00
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOA->CRL = L_CNF_MODE | (0b00 << (pos+2)) | (0b11 << (pos+0));				
			}
			else
			{
				// for GPIO_OUTPUT_PUSH_PULL - CNF[1:0] =00
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOA->CRH = H_CNF_MODE | (0b00 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}
		case GPIO_OUTPUT_OPEN_DRAIN:
		{		
			if(pin_ <= 7)
			{
				// for GPIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =01
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOA->CRL = L_CNF_MODE | (0b01 << (pos+2)) | (0b11 << (pos+0));	
			}
			else
			{
				// for GPIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =01
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOA->CRH = H_CNF_MODE | (0b01 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}
		case AFIO_OUTPUT_PUSH_PULL: 
		{		
			if(pin_ <= 7)
			{
				// for AFIO_OUTPUT_PUSH_PULL - CNF[1:0] =10
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOA->CRL = L_CNF_MODE | (0b10 << (pos+2)) | (0b11 << (pos+0));	
			}
			else
			{
				// for AFIO_OUTPUT_PUSH_PULL - CNF[1:0] =10
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOA->CRH = H_CNF_MODE | (0b10 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}
		case AFIO_OUTPUT_OPEN_DRAIN: 
		{		
			if(pin_ <= 7)
			{
				// for AFIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =11
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOA->CRL = L_CNF_MODE | (0b11 << (pos+2)) | (0b11 << (pos+0));	
			}
			else
			{
				// for AFIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =11
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOA->CRH = H_CNF_MODE | (0b11 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}		
		case ANALOG_IN:
		{		
			if(pin_ <= 7)
			{
				// for ANALOG_IN - CNF[1:0] =00 - MODE[1:0] = 00
				GPIOA->CRL = L_CNF_MODE | (0b00 << (pos+2)) | (0b00 << (pos+0));	
			}
			else
			{
				// for ANALOG_IN - CNF[1:0] =00 - MODE[1:0] = 00
				GPIOA->CRH = H_CNF_MODE | (0b00 << (pos+2)) | (0b00 << (pos+0));	
			}		
			break;
		}		
		case FLOATING_IN:
		{		
			if(pin_ <= 7)
			{
				// for FLOATING_IN - CNF[1:0] =01 - MODE[1:0] = 00
				GPIOA->CRL = L_CNF_MODE | (0b01 << (pos+2)) | (0b00 << (pos+0));	
			}
			else
			{
				// for FLOATING_IN - CNF[1:0] =01 - MODE[1:0] = 00
				GPIOA->CRH = H_CNF_MODE | (0b01 << (pos+2)) | (0b00 << (pos+0));	
			}		
			break;
		}		
		case PD_IN:
		{		
			if(pin_ <= 7)
			{
				// for PD_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOA->CRL = L_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));		
			}
			else
			{
				// for PD_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOA->CRH = H_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));
			}		
			// for pull down make outptu bit 0
			GPIOA->ODR &= ~(1<<x);
			break;
		}		
		case PU_IN:{		
			if(pin_ <= 7)
			{
				// for PU_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOA->CRL = L_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));		
			}
			else
			{
				// for PU_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOA->CRH = H_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));	
			}		
			// for pull up make outptu bit 1
			GPIOA->ODR |= (1<<x);
			break;
		}		
		default:break;
	}
}



void GPIOB_config(unsigned char pin_,enum CONFIGURATION_MODE config_)
{
	unsigned char x,pos;
	unsigned int L_CNF_MODE, H_CNF_MODE;
	L_CNF_MODE = H_CNF_MODE = 0;
	if(pin_ <= 7)
	{
		x=pin_;
		// gettinG the pins' corresponding 4 bit CONF and MODE
		pos = x<<2;
		L_CNF_MODE = (GPIOB->CRL & ~((1 << (pos+3)) | (1 << (pos+2) | (1 << (pos+1)) | (1 << (pos+0)))));
	}
	else
	{
		x=pin_-8;
		// gettinG the pins' corresponding 4 bit CONF and MODE
		pos = x<<2;
		H_CNF_MODE = (GPIOB->CRH & ~((1 << (pos+3)) | (1 << (pos+2) | (1 << (pos+1)) | (1 << (pos+0)))));
	}
		
	// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
	switch(config_)
	{
		
		case GPIO_OUTPUT_PUSH_PULL: 
		{		
			if(pin_ <= 7)
			{
				// for GPIO_OUTPUT_PUSH_PULL - CNF[1:0] =00
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOB->CRL = L_CNF_MODE | (0b00 << (pos+2)) | (0b11 << (pos+0));				
			}
			else
			{
				// for GPIO_OUTPUT_PUSH_PULL - CNF[1:0] =00
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOB->CRH = H_CNF_MODE | (0b00 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}
		case GPIO_OUTPUT_OPEN_DRAIN:
		{		
			if(pin_ <= 7)
			{
				// for GPIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =01
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOB->CRL = L_CNF_MODE | (0b01 << (pos+2)) | (0b11 << (pos+0));	
			}
			else
			{
				// for GPIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =01
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOB->CRH = H_CNF_MODE | (0b01 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}
		case AFIO_OUTPUT_PUSH_PULL: 
		{		
			if(pin_ <= 7)
			{
				// for AFIO_OUTPUT_PUSH_PULL - CNF[1:0] =10
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOB->CRL = L_CNF_MODE | (0b10 << (pos+2)) | (0b11 << (pos+0));	
			}
			else
			{
				// for AFIO_OUTPUT_PUSH_PULL - CNF[1:0] =10
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOB->CRH = H_CNF_MODE | (0b10 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}
		case AFIO_OUTPUT_OPEN_DRAIN: 
		{		
			if(pin_ <= 7)
			{
				// for AFIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =11
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOB->CRL = L_CNF_MODE | (0b11 << (pos+2)) | (0b11 << (pos+0));	
			}
			else
			{
				// for AFIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =11
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOB->CRH = H_CNF_MODE | (0b11 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}		
		case ANALOG_IN:
		{		
			if(pin_ <= 7)
			{
				// for ANALOG_IN - CNF[1:0] =00 - MODE[1:0] = 00
				GPIOB->CRL = L_CNF_MODE | (0b00 << (pos+2)) | (0b00 << (pos+0));	
			}
			else
			{
				// for ANALOG_IN - CNF[1:0] =00 - MODE[1:0] = 00
				GPIOB->CRH = H_CNF_MODE | (0b00 << (pos+2)) | (0b00 << (pos+0));	
			}		
			break;
		}		
		case FLOATING_IN:
		{		
			if(pin_ <= 7)
			{
				// for FLOATING_IN - CNF[1:0] =01 - MODE[1:0] = 00
				GPIOB->CRL = L_CNF_MODE | (0b01 << (pos+2)) | (0b00 << (pos+0));	
			}
			else
			{
				// for FLOATING_IN - CNF[1:0] =01 - MODE[1:0] = 00
				GPIOB->CRH = H_CNF_MODE | (0b01 << (pos+2)) | (0b00 << (pos+0));	
			}		
			break;
		}		
		case PD_IN:
		{		
			if(pin_ <= 7)
			{
				// for PD_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOB->CRL = L_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));		
			}
			else
			{
				// for PD_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOB->CRH = H_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));
			}		
			// for pull down make outptu bit 0
			GPIOB->ODR &= ~(1<<x);
			break;
		}		
		case PU_IN:{		
			if(pin_ <= 7)
			{
				// for PU_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOB->CRL = L_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));		
			}
			else
			{
				// for PU_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOB->CRH = H_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));	
			}		
			// for pull up make outptu bit 1
			GPIOB->ODR |= (1<<x);
			break;
		}		
		default:break;
	}
}



void GPIOC_config(unsigned char pin_,enum CONFIGURATION_MODE config_)
{
	unsigned char x,pos;
	unsigned int L_CNF_MODE, H_CNF_MODE;
	L_CNF_MODE = H_CNF_MODE = 0;
	if(pin_ <= 7)
	{
		x=pin_;
		// gettinG the pins' corresponding 4 bit CONF and MODE
		pos = x<<2;
		L_CNF_MODE = (GPIOC->CRL & ~((1 << (pos+3)) | (1 << (pos+2) | (1 << (pos+1)) | (1 << (pos+0)))));
	}
	else
	{
		x=pin_-8;
		// gettinG the pins' corresponding 4 bit CONF and MODE
		pos = x<<2;
		H_CNF_MODE = (GPIOC->CRH & ~((1 << (pos+3)) | (1 << (pos+2) | (1 << (pos+1)) | (1 << (pos+0)))));
	}
		
	// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
	switch(config_)
	{
		
		case GPIO_OUTPUT_PUSH_PULL: 
		{		
			if(pin_ <= 7)
			{
				// for GPIO_OUTPUT_PUSH_PULL - CNF[1:0] =00
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOC->CRL = L_CNF_MODE | (0b00 << (pos+2)) | (0b11 << (pos+0));				
			}
			else
			{
				// for GPIO_OUTPUT_PUSH_PULL - CNF[1:0] =00
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOC->CRH = H_CNF_MODE | (0b00 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}
		case GPIO_OUTPUT_OPEN_DRAIN:
		{		
			if(pin_ <= 7)
			{
				// for GPIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =01
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOC->CRL = L_CNF_MODE | (0b01 << (pos+2)) | (0b11 << (pos+0));	
			}
			else
			{
				// for GPIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =01
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOC->CRH = H_CNF_MODE | (0b01 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}
		case AFIO_OUTPUT_PUSH_PULL: 
		{		
			if(pin_ <= 7)
			{
				// for AFIO_OUTPUT_PUSH_PULL - CNF[1:0] =10
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOC->CRL = L_CNF_MODE | (0b10 << (pos+2)) | (0b11 << (pos+0));	
			}
			else
			{
				// for AFIO_OUTPUT_PUSH_PULL - CNF[1:0] =10
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOC->CRH = H_CNF_MODE | (0b10 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}
		case AFIO_OUTPUT_OPEN_DRAIN: 
		{		
			if(pin_ <= 7)
			{
				// for AFIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =11
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOC->CRL = L_CNF_MODE | (0b11 << (pos+2)) | (0b11 << (pos+0));	
			}
			else
			{
				// for AFIO_OUTPUT_OPEN_DRAIN - CNF[1:0] =11
				// the maimum speed is always 50MHz for outptut - MODE[1:0] = 11
				GPIOC->CRH = H_CNF_MODE | (0b11 << (pos+2)) | (0b11 << (pos+0));	
			}		
			break;
		}		
		case ANALOG_IN:
		{		
			if(pin_ <= 7)
			{
				// for ANALOG_IN - CNF[1:0] =00 - MODE[1:0] = 00
				GPIOC->CRL = L_CNF_MODE | (0b00 << (pos+2)) | (0b00 << (pos+0));	
			}
			else
			{
				// for ANALOG_IN - CNF[1:0] =00 - MODE[1:0] = 00
				GPIOC->CRH = H_CNF_MODE | (0b00 << (pos+2)) | (0b00 << (pos+0));	
			}		
			break;
		}		
		case FLOATING_IN:
		{		
			if(pin_ <= 7)
			{
				// for FLOATING_IN - CNF[1:0] =01 - MODE[1:0] = 00
				GPIOC->CRL = L_CNF_MODE | (0b01 << (pos+2)) | (0b00 << (pos+0));	
			}
			else
			{
				// for FLOATING_IN - CNF[1:0] =01 - MODE[1:0] = 00
				GPIOC->CRH = H_CNF_MODE | (0b01 << (pos+2)) | (0b00 << (pos+0));	
			}		
			break;
		}		
		case PD_IN:
		{		
			if(pin_ <= 7)
			{
				// for PD_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOC->CRL = L_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));		
			}
			else
			{
				// for PD_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOC->CRH = H_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));
			}		
			// for pull down make outptu bit 0
			GPIOC->ODR &= ~(1<<x);
			break;
		}		
		case PU_IN:{		
			if(pin_ <= 7)
			{
				// for PU_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOC->CRL = L_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));		
			}
			else
			{
				// for PU_IN - CNF[1:0] =10 - MODE[1:0] = 00
				GPIOC->CRH = H_CNF_MODE | (0b10 << (pos+2)) | (0b00 << (pos+0));	
			}		
			// for pull up make outptu bit 1
			GPIOC->ODR |= (1<<x);
			break;
		}		
		default:break;
	}
}




void GPIO_config(enum PORTS_MINE port_, unsigned char pin_, enum CONFIGURATION_MODE config_)
{
	// clock enable for alternate function
	// AFIOEN - bit 0 of RCC_APB2ENR
	RCC->APB2ENR |= (1<<0);
	
	// clock enable for gpio function
	// IOPAEN - bit 2 of RCC_APB2ENR
	// IOPBEN - bit 3 of RCC_APB2ENR
	// IOPCEN - bit 4 of RCC_APB2ENR
	if(port_ == A)
	{
		RCC->APB2ENR |= (1<<2);
		GPIOA_config(pin_,config_);
	}
	else if(port_ == B)
	{
		RCC->APB2ENR |= (1<<3);
		GPIOB_config(pin_,config_);
	}
	else if(port_ == C)
	{
		RCC->APB2ENR |= (1<<4);
		GPIOC_config(pin_,config_);
	}
}
