
#include "stm32f10x.h"

void mco_output()
{
	// dont' know why it doesn't work
	// clock enable for GPIOA
	// by setting IOPAEN - bit2 of RCC_APB2ENR
	RCC->APB2ENR |= (1<<2);
	RCC->APB2ENR |= (1<<0);
	
	// make PA8 as output - alternate function output
	// push pull for MCO-- CNF[1:0] = 10
	// GPIOA -- CRH[3:2] - CNF[1:0] for PA8
	GPIOA->CRH |= (1<<3);
	GPIOA->CRH &= ~(1<<2);
	
	// make PA8 as output maximum speed as 50MHz
	// 50MHz output -- MODE[1:0] = 11
	// GPIOA -- CRH[1:0] - MODE[1:0] for PA8
	GPIOA->CRH |= (1<<1);
	GPIOA->CRH |= (1<<0);
		
	
	// see the Microcontroller clock output in MCO pins - PA8
	// RCC_CFGR[26:24]
	// let's see the PLL Clock / 2 -- 111
	RCC->CFGR |= (1<<26);
	RCC->CFGR &= ~(1<<25);
	RCC->CFGR |= (1<<24);
//	
}
void set_HSI_SYSCLK(void)
{
	// switch on - enable Internal High-Speed Clock enable
	// HSION - 1 in RCC_CR[0]
	RCC->CR |= (1<<0);
	
	// wait until, HSI is ready AND stable to be used
	// by checking HSIRDY bit in RCC_CR[1]
	while( (RCC->CR & (1<<1)) == 0); 
	
	// select the SYSCLK source
	// by selecting HSI in SW of RCC_CFGR[1:0]
	// for HSI - 00 
	RCC->CFGR &= ~(1<<1);
	RCC->CFGR &= ~(1<<0);
	
	// check if HSI is used as sysclk
	// by chaking SWS of RCC_CFGR[3:2]
	// if HSI is SYSCLK -- 00
	while( !(((RCC->CFGR & (1<<3)) == 0) && ((RCC->CFGR & (1<<2)) == 0)) );
}
void set_HSE_SYSCLK_crystal(void)
{
	// use crystall as external INPUT
	// by BYPASS
	// clearing HSEBYP in RCC_CR[18]
	RCC->CR &= ~(1<<18);
	
	// switch on - enable External High-Speed Clock enable
	// HSEON - 1 in RCC_CR[16]
	RCC->CR |= (1<<16);
	
	// wait until, HSE is ready AND stable to be used
	// by checking HSERDY bit in RCC_CR[17]
	while( (RCC->CR & (1<<17)) == 0); 
	


	// select the SYSCLK source
	// by selecting HSE in SW of RCC_CFGR[1:0]
	// for HSE - 01
	RCC->CFGR &= ~(1<<1);
	RCC->CFGR |= (1<<0);
	
	// check if HSE is used as sysclk
	// by chaking SWS of RCC_CFGR[3:2]
	// if HSE is SYSCLK -- 01
	while( !(((RCC->CFGR & (1<<3)) == 0) && ((RCC->CFGR & (1<<2)) != 0)) );
}
void set_HSE_SYSCLK_oscillator(void)
{
	// use oscillatr as external INPUT
	// by BYPASS
	// setting HSEBYP in RCC_CR[18]
	RCC->CR |= (1<<18);
	
	
	// switch on - enable External High-Speed Clock enable
	// HSEON - 1 in RCC_CR[16]
	RCC->CR |= (1<<16);
	
	// wait until, HSE is ready AND stable to be used
	// by checking HSERDY bit in RCC_CR[17]
	while( (RCC->CR & (1<<17)) == 0); 
	
	// select the SYSCLK source
	// by selecting HSE in SW of RCC_CFGR[1:0]
	// for HSE - 01
	RCC->CFGR &= ~(1<<1);
	RCC->CFGR |= (1<<0);
	
	// check if HSE is used as sysclk
	// by chaking SWS of RCC_CFGR[3:2]
	// if HSE is SYSCLK -- 01
	while( !(((RCC->CFGR & (1<<3)) == 0) && ((RCC->CFGR & (1<<2)) != 0)) );
}

void PLL1_config(int source_0HSI_1HSE,int multiplier_val)
{
	// first change SYSCLK clock to HSI or HSE
	// we use HSI
	set_HSI_SYSCLK();
	
	// disbale PLL
	// by clearing PLLON in RCC_CR[24]
	RCC->CR &= ~(1<<24);
	
	
	

	if(source_0HSI_1HSE == 0)
	{
		// if PLL1 uses HSI, then the PLL input clock woule be 8MHz / 2
		// this is slected by PLLSRC in RCC_CFGR[16] - 0
		RCC->CFGR &= ~(1<<16);
	}
	else if(source_0HSI_1HSE == 1)
	{
		// PLL1 uses HSE
		// this is slected by PLLSRC in RCC_CFGR[16] - 1
		RCC->CFGR |= (1<<16);
	}
	else
		return;
	
	// now after the PLL input clock we can select the multiplier
	// by selecting from PLLMUL in RCC_CFGR[21:18]
	// can be  2 to 16
	// 0000 begin 2 and 1110/1111 being 16
	// se subtract by 2 since, 2 is the begiing
	RCC->CFGR = (RCC->CFGR & ~0X3F0000) | ((multiplier_val - 2) << 18);
	
	// now, we switch on the PLL clcok
	// by setting PLLON in RCC_CR[24]
	RCC->CR |= (1<<24);
	
	// now we wait till PLL becomes ready
	// by cheking PLLRDY in RCC_CR[25]
	while( (RCC->CR & (1<<25)) == 0);
}

void set_PLL_SYSCLK(void)
{
	// already enabled privously
	
	// select the SYSCLK source
	// by selecting PLL in SW of RCC_CFGR[1:0]
	// for PLL - 10 
	RCC->CFGR |= (1<<1);
	RCC->CFGR &= ~(1<<0);
	
	// check if PLL is used as sysclk
	// by chaking SWS of RCC_CFGR[3:2]
	// if PLL is SYSCLK -- 00
	while( !(((RCC->CFGR & (1<<3)) != 0) && ((RCC->CFGR & (1<<2)) == 0)) );
}

int main(void)
{
//	set_HSE_SYSCLK_crystal();

//	set_HSE_SYSCLK_oscillator();
	
	set_HSI_SYSCLK();
	
	
	PLL1_config(0, 3);
	set_PLL_SYSCLK();
	
	
	while(1)
	{
	}
}

