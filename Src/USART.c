#include <stdio.h>
#include <stdint.h>
#include "USART.h"
#include "common.h"


void usartConfigure(USARTRegs *usart, long long mode, int desiredBaudrate, int peripheralFreq){
	int mantissa, fractional;
	float divider;
	int shiftFrac = 8;
	int over8 = 1;

	usart->CR1 = (uint32_t)(mode & 0xffff);
	usart->CR2 = (uint32_t)((mode >>16)& 0xffff);
	usart->CR3 = (uint32_t)(mode >> 32);


	if(usartOverSample16(usart)){
		shiftFrac = 16;
		over8 = 0;
	}

	divider = ((float)peripheralFreq/ (8 * ((2 - over8) * desiredBaudrate)));
	mantissa = (int) divider;
	fractional = (int)((float)(divider - mantissa) * shiftFrac);

	usart->BRR = (mantissa << 4)	| (fractional);

}


int usartOverSample16(USARTRegs *usart){
	// if 1 then its oversampling8
	if(usart->CR1 & USART_OVERSAMPLING_8){
		return FALSE;
	}
	else{
		return TRUE;
	}
}

#define MAX_BUFFER_SIZE	512
char uartPrintBuffer[MAX_BUFFER_SIZE];
void uartPrintf(char *message, ...){
	va_list args;
	int length, i;

	va_start(args, message);
	length = vsnprintf(uartPrintBuffer, 0, message, args);

	if(length > MAX_BUFFER_SIZE - 1){
		length = MAX_BUFFER_SIZE - 1;
	}

	vsnprintf(uartPrintBuffer, length +1, message, args);

	for(i = 0; i < length; i++){
		while(!(usartIsTxRegEmpty(uart5)));
		(uart5)->DR = uartPrintBuffer[i];
	}
}
