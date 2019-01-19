#include "SPI.h"

void configureSPI(spiRegs *spi, uint32_t mode){
  (spi)-> CR1 = (mode) & (0xffff);
  (spi)-> CR2 = (mode >> 16) & (0xffff);
}
