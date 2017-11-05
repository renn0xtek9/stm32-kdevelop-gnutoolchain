#ifndef DATA_FROM_PC_H
#define DATA_FROM_PC_H

#include "stm32f10x.h"
#include "hw_config.h"
#include "usb_core.h"
#include "usb_pwr.h"

struct DataFromPC {	
	uint8_t address[3];
	uint8_t command[3];
	uint8_t shoot_is_due;
} __attribute__((packed));

void ReceiveAndLoopBack();
uint8_t ConcatenateIntArrayToInt(uint8_t* array, unsigned int length);
void SendAsciRepresentationOfIntToPC(int int_to_send);

int __io_putchar(int c);
uint32_t n_ms ;


#endif
