#include "stm32f10x.h"          
#include "stm32f10x_conf.h"

void delay(void);

int main(void){
  RCC->APB2ENR = RCC_APB2ENR_IOPCEN;// I/O port C clock enable

  GPIOC->CRH &= ~(GPIO_CRH_MODE14 | GPIO_CRH_CNF14);
  GPIOC->CRH |= GPIO_CRH_MODE14;
	/*GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;         // Pin C14
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;   // Pinmode = Output, Push-Pull
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;  // Clock freq
	GPIO_Init(GPIOC, &GPIO_InitStruct); */
	
  while(1){
    GPIOC->BSRR = (1<<14);
    //GPIOC->BRR = (1<<14);
  }
}
