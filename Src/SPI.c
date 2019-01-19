#include "SPI.h"
#include "RCC.h"
#include "common.h"
#include <stdint.h>

void spiEnableClock(spiRegs *spi){
	if(spi == spi1){
		ENABLLE_SPI1_CLK_GATING();
		RESET_SPI1_CLK_GATING();
		UNRESET_SPI1_CLK_GATING();
	}
	else if(spi == spi2){
		ENABLLE_SPI2_CLK_GATING();
		RESET_SPI2_CLK_GATING();
		UNRESET_SPI2_CLK_GATING();
	}
	else if(spi == spi3){
		ENABLLE_SPI3_CLK_GATING();
		RESET_SPI3_CLK_GATING();
		UNRESET_SPI3_CLK_GATING();
	}

}

void configureSPI(spiRegs *spi, uint32_t mode){
  (spi)-> CR1 = (uint16_t)(mode) & (0xffff);
  (spi)-> CR2 = (uint16_t)(mode >> 16) & (0xffff);
}

void spiWriteData(spiRegs *spi, uint16_t data){
  (spi)-> DR = data;
}

uint16_t spiReadData(spiRegs *spi){
  return (spi)-> DR;
}

// Expecting "command 14 2", after command have numbers
int compareSpiCommand(char *str){
	int i = 0;
	char command[] = "write";

	while(*str == ' '){
		str++;
	}
	while(command[i] != '\0'){
		if(*str == command[i]){
			str++;
			i++;
		}
		else
			return NOT_MATCH;
	}
	return i;

}
