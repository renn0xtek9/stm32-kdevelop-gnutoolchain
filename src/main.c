/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "delay.h"
	
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
	for(;;)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		DelayMs(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		DelayMs(1000);
	}
}
