#include "atoi.h"
#include "printf_.h"
unsigned int IntPow(unsigned int a , unsigned int exponent)
{
	unsigned int ret=1;
	int iter=0;
	for (iter=0;iter<exponent;iter++)
	{
		ret=ret*10;
	}
	return ret;
}

unsigned int atoi(char* str, int length)
{
	printf_("Enter atoi \n\r");
	unsigned int ret=0;
	unsigned int digit,order;
	int iter=0;
	const unsigned int ascii_start=48;
	order=1;
	for (iter=0;iter<length;iter++)
	{
		printf_("atoi:: str[%d]=%d\n\r",iter,str[iter]);
		digit=str[iter]-ascii_start;
		printf_("atoi:: digit=%d\n\r",digit);
		order = IntPow(10, length-iter-1);
		ret += order* digit;		
		printf_("atoi:: ret=%d\n\r",ret);
	}
	return ret;	
}

