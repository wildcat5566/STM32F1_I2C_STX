#include "delay.h"

// For store tick counts in us
static __IO uint32_t usTicks;

// SysTick_Handler function will be called every 1 us
void SysTick_Handler(){
	if (usTicks != 0){
		usTicks--;
	}
}

void DelayInit()
{
	// Update SystemCoreClock value
	SystemCoreClockUpdate();
	// Configure the SysTick timer to overflow every 1 us
	SysTick_Config(SystemCoreClock / 1000000);
}

void DelayUs(uint32_t us){
	// Reload us value
	usTicks = us;
	while (usTicks);
}

void DelayMs(uint32_t ms){
	while (ms--){
		DelayUs(1000);
	}
}
