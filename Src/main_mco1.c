#include <stdbool.h>
#include "stm32f446xx.h"

#define GPIOAEN 0
#define GPIOCEN 2
uint32_t ms;
void mco1_m4(void){
	uint32_t pllstatus = 0;
	 RCC->AHB1ENR |= (1<<0);  //GPIOA clock

    RCC->PLLCFGR &= ~(1<<22); //making sure only PLLSRC is HSI.
    //keeping default value for M=16,R=2,Q=4,P=2 and changing N= 8.
    RCC->PLLCFGR &= ~(0x1FF<<6);
    RCC->PLLCFGR |= (0x0C8 << 6);

	//PA8 pin connected to MCO1

	GPIOA->MODER &= ~(3<<16);   //Clear the 16-17 bit for PA8
	GPIOA->MODER |= (2<<16);    //PA8 set as Alternate function
	GPIOA->AFR[1] &= ~(0xF <<(4*0)); //Clear the AFRH (0-3 bit)
	GPIOA->AFR[1] |= (0x0 << (4*0));  //set the alternate function as MCO1
	GPIOA->OSPEEDR |= (3<<16);
	//PLL on process through RCC_CR (note HSION is default on)
	RCC->CR |=(1<<24);
	while(!pllstatus){
		pllstatus = RCC->CR;
		pllstatus &= (1 << 25);
	}
	//MCO1 Prescalar and input selection
	RCC->CFGR |=(7 << 24);  // prescalsr is max at 5
	RCC->CFGR |= (3 << 21);  //microcontroller output selected to be PLL Clock selected.

}

int main(void)
{
	mco1_m4();
    /* Loop forever */
	for(;;);
}


void demo_mco1_g0(void){
	uint32_t pllstatus = 0;
		RCC->PLLCFGR |= (2<<0);  //HSI16
		RCC->PLLCFGR |= (1<<16); //M=4
		RCC->PLLCFGR |= (0x8<<8); //N=8
		RCC->PLLCFGR |= (1<<29);   //R=2
		//RCC->IOPENR |= (1<< GPIOAEN) |(1<<GPIOCEN);//GPIOA and GPIOC
		GPIOA->MODER &= ~((3<<16)); //PA8 port for MCO
		GPIOA->MODER |= ((2<<16));
		GPIOA->AFR[1] |= ((8<<0));   //Alternate function for PA8.

		RCC->PLLCFGR |= (1<< 28); //PLLR EN
		RCC->CR |= (1<< 24);   //PLLEN
		while(!pllstatus){
			pllstatus = RCC->CR;
			pllstatus &= (1<<25);
		};
		//RCC->CFGR |= (2<<0); //PLLRCLK as SYSCLK
		RCC->CFGR |= (4<<28); //mco DIVIDED BY 16
		RCC ->CFGR |= (1<<24); //1 IS sysclk, 3 in HSI16, 5 is connected PLLRCLK to MCO.

}
