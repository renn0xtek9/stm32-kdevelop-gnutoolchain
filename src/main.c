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
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"
void InitInputOutput()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);					//Initilize clock of port A
	GPIO_InitTypeDef gpioa_init_struct={GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_Out_PP};  	//Define the port a init structure
	GPIO_Init(GPIOA,&gpioa_init_struct);							// Initialize it
	GPIO_SetBits(GPIOA,GPIO_Pin_5);	
}

extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
extern __IO  uint32_t length ;
uint8_t Send_Buffer[64];
uint32_t packet_sent=1;
uint32_t packet_receive=1;

int main(void)
{
	DelayInit();
	Set_System();
	InitInputOutput();
	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();
	int ledstatus=1;
	for(;;)
	{
		char data[]={'B','l','i','n','k'};
		if(ledstatus==1)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			CDC_Send_DATA(data,5);
			DelayMs(500);
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		}
		DelayMs(1000);
		
		if (bDeviceState == CONFIGURED)
		{
			CDC_Receive_DATA();
			if (Receive_length  != 0)
			{
				//Just as an example if the data received is one bye length then we toggle the blinking the led off/on
				// WARNING if you use e.g. echo "t" >>/dev/ttyACM0 you might send two chars (carriage return at end)
				// prefere using small programm like picocom that will send char by char.
				if(Receive_length==1) 
				{
					ledstatus=ledstatus==1?0:1;
				}
				
				//Loop back (we sent back the data that we received so that it appear on the console of the PC)
				if (packet_sent == 1)
					CDC_Send_DATA ((unsigned char*)Receive_Buffer,Receive_length);
				Receive_length = 0;
			}
		}
		
		
	}
}
