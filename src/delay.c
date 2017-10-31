#include "delay.h"
#include "stm32f10x_it.h"

void DelayInit()
{
    // Update SystemCoreClock value
    SystemCoreClockUpdate();
    // Configure the SysTick timer to overflow every 1 us
    SysTick_Config(SystemCoreClock / 1000000);
}
void DelayUs(uint32_t us)
{
    // Reload us value
    usTicks = us;
    // Wait until usTick reach zero
    while (usTicks);
}
void DelayMs(uint32_t ms)
{
	// Wait until ms reach zero
	while (ms--)
	{
		// Delay 1ms
		DelayUs(1000);
	}
}


