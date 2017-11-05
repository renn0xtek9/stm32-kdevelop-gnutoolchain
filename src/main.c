#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "misc.h"
#include "delay.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"
#include "irsnd.h"	
#include "data_from_pc.h"
#include "itoa.h"
//-------------------------------------This bit is directly tooked form irmp library examples

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
extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
extern __IO  uint32_t length ;
uint8_t Send_Buffer[64];
uint32_t packet_sent=1;
uint32_t packet_receive=1;

// For protocol communication with the computer
extern struct DataFromPC Datareceived;



int main(void)
{
	DelayInit();
	Set_System();
	InitInputOutput();
	//Init the USB
	Set_USBClock();
	USB_Interrupts_Config();
	USB_Init();
	//Init the Infra red
	IRMP_DATA irmp_data;
	irsnd_init();
	timer2_init();
	

	irmp_data.command=16;
	irmp_data.address=21;

	uint32_t n_ms=500;
	uint8_t iter_counter=0;
	for(;;)
	{
		ReceiveAndLoopBack();
		SendAsciRepresentationOfIntToPC(irmp_data.address); DelayMs(20);
		SendAsciRepresentationOfIntToPC(irmp_data.command); DelayMs(20);
		if(Datareceived.shoot_is_due==1)
		{
			
			irmp_data.protocol = IRMP_RC5_PROTOCOL;			// use RC5 protocol (typical of e.g. Philips)
			irmp_data.address=(uint16_t)ConcatenateIntArrayToInt(Datareceived.address,3);
			irmp_data.command=(uint16_t)ConcatenateIntArrayToInt(Datareceived.command,3);
			irmp_data.flags    = 0;					// don't repeat frame

// 			SendAsciRepresentationOfIntToPC((int)Datareceived.address[0]);
// 			DelayMs(50);
// 			SendAsciRepresentationOfIntToPC((int)Datareceived.address[1]);
// 			DelayMs(50);
// 			SendAsciRepresentationOfIntToPC((int)Datareceived.address[3]);
			
			
			SendAsciRepresentationOfIntToPC(irmp_data.address); DelayMs(20);
			SendAsciRepresentationOfIntToPC(irmp_data.command); DelayMs(20);
			
			irsnd_send_data (&irmp_data, TRUE);        
			Datareceived.shoot_is_due=0;
			
			n_ms=250;
		}
		if(n_ms==250) 
			iter_counter++;
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		DelayMs(n_ms);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		DelayMs(n_ms);
		if(iter_counter==10) 
		{
			n_ms=500;
			iter_counter=0;
		}
	}
}
