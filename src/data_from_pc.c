#include "data_from_pc.h"
#include "itoa.h"
#include "atoi.h"
#include "delay.h"
struct DataFromPC Datareceived ={{0,0,0},{0,0,0},0};
extern __IO uint8_t Receive_Buffer[64];
extern __IO  uint32_t Receive_length ;
extern __IO  uint32_t length ;
char MsgReceived[]={'R','e','c','e','v','e','i','d','\n'};
char nl='\n';
char MsgLength[]={'L','e','n','g','t','h','\n'};
void ReceiveAndLoopBack()
{
	if (bDeviceState == CONFIGURED)
	{
		CDC_Receive_DATA();
		if (Receive_length  != 0)
		{
			//Just as an example if the data received is one bye length then we toggle the blinking the led off/on
			// WARNING if you use e.g. echo "t" >>/dev/ttyACM0 you might send two chars (carriage return at end)
			// prefere using small programm like picocom that will send char by char
			if(Receive_length==7) 
			{
				//very ugly way to copy data I know..
				CDC_Send_DATA((uint8_t*)MsgReceived,sizeof(MsgReceived)); DelayMs(20);
// 				Datareceived.address[0]=Receive_Buffer[0];
// 				Datareceived.address[1]=Receive_Buffer[1];
// 				Datareceived.address[2]=Receive_Buffer[2];
// 				Datareceived.command[0]=Receive_Buffer[4];
// 				Datareceived.command[1]=Receive_Buffer[5];
// 				Datareceived.command[2]=Receive_Buffer[6];
				Datareceived.address[0]=atoi(Receive_Buffer+0,1);
				Datareceived.address[1]=atoi(Receive_Buffer+0,1);
				Datareceived.address[2]=atoi(Receive_Buffer+0,1);
				Datareceived.command[0]=atoi(Receive_Buffer+0,1);
				Datareceived.command[1]=atoi(Receive_Buffer+0,1);
				Datareceived.command[2]=atoi(Receive_Buffer+0,1);

				

				Datareceived.shoot_is_due=1;
				/*DelayMs(20);
				int i;
				for(i=0;i<7;i++)
				{
					SendAsciRepresentationOfIntToPC(Receive_Buffer[i]);
					DelayMs(20);
				}*/
				
			}	
			//Loop back (we sent back the data that we received so that it appear on the console of the PC)
			CDC_Send_DATA ((unsigned char*)Receive_Buffer,Receive_length);DelayMs(20);
// 			CDC_Send_DATA ((unsigned char*)Receive_Buffer,64);
			CDC_Send_DATA(&nl,1);
			Receive_length = 0;
		}
	}	
};
uint8_t ConcatenateIntArrayToInt(uint8_t* array, unsigned int length)
{
	/*STATUS [x]Reviewed [x]Verified []Extensively Unit-Tested
	 * This concatenate an array of digit to int. It is assume tha the digit come stored with ascii code	
	*/
	uint8_t ret=0;
	char str[64]; // TODO  use malloc over length here !!
	char c;
// 	char ** str = (char **) malloc(length * sizeof(char *));
	unsigned int iter=0;
	for (iter=0; iter<length;iter++)
	{
		int sublength;
		itoa(array[iter],&c,10,&sublength);
		str[iter]=c;		
	}
	//Now the first length character of str are the number (e.g if array= {4,5,6} then str should be {'4','5','6','whatever','whateve',...}
	ret=(uint8_t)atoi(str,length);
	return ret;
}
void SendAsciRepresentationOfIntToPC(int int_to_send)
{	
	/*STATUS [x]Reviewed [x]Verified []Extensively Unit-Tested
	 * Send the ASCI sequence corresponding to an interger to the PC via virtual comport !
	*/
	char buf[64];
	int length;
	itoa(int_to_send,buf,10,&length);
	CDC_Send_DATA((unsigned char*) buf,length); DelayMs(20);
}

