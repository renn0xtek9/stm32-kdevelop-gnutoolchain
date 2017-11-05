#include "atoi.h"
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
	unsigned int ret=0;
	unsigned int digit,order;
	int iter=0;
	const unsigned int ascii_start=48;
	order=1;
	for (iter=0;iter<length;iter++)
	{
		digit=str[iter]-ascii_start;
		order = IntPow(10, length-iter-1);
		ret += order* digit;		
	}
	return ret;	
}

