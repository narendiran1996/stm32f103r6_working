#include "stm32f10x.h"
#include "naren_gpio_func.h"
#include "naren_lcd_func.h"
unsigned int a,b;

void init_dma_mem_mem_transfer()
{
	// lets' use channel 1
	
	
	// enabling memory to memory transfer - by setting MEM2MEM bit 14 of DMA_CCRx
	DMA1_Channel1->CCR |= (1<<14);
	
	// let's give highest channel prioirty
	// PL[1:0] = 11 -- DMA_CCRx[13:12]
	DMA1_Channel1->CCR |= (1<<13);
	DMA1_Channel1->CCR |= (1<<12);
	
	// let's transfer 32-bit data size
	// memory size - MSIZE - 10 -- DMA_CCRx[11:10]
	DMA1_Channel1->CCR |= (1<<11);
	DMA1_Channel1->CCR &= ~(1<<10);
	
	// peripheral size - PSIZE - 10 -- DMA_CCRx[9:8]
	DMA1_Channel1->CCR |= (1<<9);
	DMA1_Channel1->CCR &= ~(1<<8);
	
	// enable memory increment mode
	// by setting MINC - bit 7  of DMA_CCRx
	DMA1_Channel1->CCR |= (1<<7);
	
	// enable peripheral incremnt mode- because it is alos ememory
	// by setting PINC - bit 6  of DMA_CCRx
	DMA1_Channel1->CCR |= (1<<6);
	
	// disbale cjircular mode
	// by clearing CIRC - bit 5 of DMA_CCRx
	DMA1_Channel1->CCR &= ~(1<<5);
	
	// data transfer direction
	// read from memory by setting DIR - bit 4 of DMA_CCRx
	DMA1_Channel1->CCR |= (1<<4);
	
	// clearing Transfer error interrupt
	// TEIE - bit 3 of DMA_CCRx
	DMA1_Channel1->CCR &= ~(1<<3);
	
	// clearing half Transfer complete interrupt
	// HTIE - bit 2 of DMA_CCRx
	DMA1_Channel1->CCR &= ~(1<<2);
	
	// clearing Transfer COMPLETE interrupt
	// TCIE - bit 1 of DMA_CCRx
	DMA1_Channel1->CCR &= ~(1<<1);
	
	// let's transfer just two data
	DMA1_Channel1->CNDTR = 2;
	
	// let's give the destination location in pheriperal address
	DMA1_Channel1->CPAR = 0x20000016;
	
	// let's give the source location in memory address
	DMA1_Channel1->CMAR = 0x20000000;
	
	// let's initate the transaction by writing 1 to bit 0 - EN
	DMA1_Channel1->CCR |= (1<<0);
}

int main(void)
{

	a = 0xabcdef12;
	b = 0x55766755;
	
	// see the output in keil at location specficied in source and destination
	init_dma_mem_mem_transfer();
	
	while(1)
	{
	}
}
