#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "misc.h"
#include "delay.h"
#include "irsnd.h"	
	
//-------------------------------------This bit is directly tooked form irmp library examples
#include "irsnd.h"

#ifndef F_CPU
#error F_CPU unknown
#endif

uint32_t
SysCtlClockGet(void)
{
    RCC_ClocksTypeDef RCC_ClocksStatus;
    RCC_GetClocksFreq(&RCC_ClocksStatus);
    return RCC_ClocksStatus.SYSCLK_Frequency;
}

void
timer2_init (void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseStructure.TIM_ClockDivision                 = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode                   = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period                        = 7;
    TIM_TimeBaseStructure.TIM_Prescaler                     = ((F_CPU / F_INTERRUPTS)/8) - 1;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel                      = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                   = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority    = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority           = 0x0F;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}

void
TIM2_IRQHandler(void)                                                       // Timer2 Interrupt Handler
{
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
//   (void) irmp_ISR();                                                        // call irmp ISR
  (void) irsnd_ISR();
  // call other timer interrupt routines...
}
//-------------------------------------END OF STEALING IRMP LIBRARY CODE ;)
void InitInputOutput()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);					//Initilize clock of port A
	GPIO_InitTypeDef gpioa_init_struct={GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_Out_PP};  	//Define the port a init structure
	GPIO_Init(GPIOA,&gpioa_init_struct);							// Initialize it
	GPIO_SetBits(GPIOA,GPIO_Pin_5);	
}
int main(void)
{
	InitInputOutput();
	DelayInit();
	IRMP_DATA irmp_data;
	irsnd_init();
	timer2_init();
	uint16_t command=0x0;
	for(;;)
	{
		//Here as an example we bomb the Device with command from 0 to 54 every half a second on address 16
		while (command<54)
		{
			irmp_data.protocol = IRMP_RC5_PROTOCOL;			// use RC5 protocol (typical of e.g. Philips)
			irmp_data.address  = 16;				// set address 16
			irmp_data.command  = command;				// set command to 0x0001
			irmp_data.flags    = 0;					// don't repeat frame

			irsnd_send_data (&irmp_data, TRUE);           	
			command++;
// 			After each command blink a LED on A5 to "see it"
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			DelayMs(250);
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			DelayMs(250);
		}
		
	}
}
