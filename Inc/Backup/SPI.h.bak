#ifndef __SPI_H__
#define __SPI_H__

#include "common.h"

typedef struct spiRegs spiRegs;
struct spiRegs{         // offset         // Description
  IoRegister CR1;       // 0x00           // SPI control register 1
  IoRegister CR2;       // 0x04           // SPI control register 2
  IoRegister SR;        // 0x08           // SPI status register
  IoRegister DR;        // 0x0c           // SPI data register
  IoRegister CRCPR;     // 0x10           // SPI CRC polynomial register
  IoRegister RXCRCR;    // 0x14           // SPI RX CRC register
  IoRegister TXCRCR;    // 0x18           // SPI TX CRC register
  IoRegister I2SCFGR;   // 0x1c           // SPI_I2S configuration register
  IoRegister I2SPR;     // 0x20           // SPI_I2S prescaler register
};

#define spi1    (spiRegs *)(0x40013000)
#define spi2    (spiRegs *)(0x40003800)
#define spi3    (spiRegs *)(0x40003C00)
#define spi4    (spiRegs *)(0x40013400)
#define spi5    (spiRegs *)(0x40015000)
#define spi6    (spiRegs *)(0x40015400)

/**************************CONFIGURATIONS DEFINITION****************************/
// SPI control register 1 (SPI_CR1) (not used in I2S mode)
#define SPI_CLKPHASE_1ST          (0 << 0)  // The first clock transition is the first data capture edge
#define SPI_CLKPHASE_2ND          (1 << 0)  // The second clock transition is the first data capture edge
#define SPI_CLKPOLAR_L            (0 << 1)  // CK to 0 when idle
#define SPI_CLKPOLAR_H            (1 << 1)  // CK to 1 when idle
#define SPI_SLAVE_MODE            (0 << 2)  // Slave Configuration
#define SPI_MASTER_MODE           (1 << 2)  // Master Configuration
#define SPI_BAUD_CONTRL_2         (0 << 3)  // peripheral clk freq divide by 2
#define SPI_BAUD_CONTRL_4         (1 << 3)  // peripheral clk freq divide by 4
#define SPI_BAUD_CONTRL_8         (2 << 3)  // peripheral clk freq divide by 8
#define SPI_BAUD_CONTRL_16        (3 << 3)  // peripheral clk freq divide by 16
#define SPI_BAUD_CONTRL_32        (4 << 3)  // peripheral clk freq divide by 32
#define SPI_BAUD_CONTRL_64        (5 << 3)  // peripheral clk freq divide by 64
#define SPI_BAUD_CONTRL_128       (6 << 3)  // peripheral clk freq divide by 128
#define SPI_BAUD_CONTRL_256       (7 << 3)  // peripheral clk freq divide by 256
#define SPI_DIS         		  (0 << 6)  // Disable peripheral
#define SPI_EN         			  (1 << 6)  // Enable peripheral
#define SPI_MSB_TRANSMIT_1ST      (0 << 7)  // MSB transmitted first
#define SPI_LSB_TRANSMIT_1ST      (1 << 7)  // LSB transmitted first
#define SPI_NSS_LOW			 	  (0 << 8)
#define SPI_NSS_HIGH			  (1 << 8)	// This bit has an effect only when the SSM bit is set. \
											   The value of this bit is forced onto the\
											   NSS pin and the IO value of the NSS pin is ignored.
#define SPI_SOFTWARE_SLAVE_MANAGEMENT (1 << 9)  // Software slave management enabled
#define SPI_FULL_DUPLEX           (0 << 10)  // Full duplex (Transmit and receive)
#define SPI_RECEIVE_ONLY          (1 << 10)  // Output disabled (Receive-only mode)
#define SPI_DATA_FRAME_8_BITS     (0 << 11)  // 8-bit data frame format is selected for transmission/reception
#define SPI_DATA_FRAME_16_BITS    (1 << 11)  // 16-bit data frame format is selected for transmission/reception
#define SPI_CRC_NEXT_EN           (1 << 12)  // Next transfer is CRC (CRC phase) else no CRC phase
#define SPI_HW_CRC_CALC_EN        (1 << 13)  // Hardware CRC calculation enable
#define SPI_BIDIRECTIONAL_OUT_EN   (1 << 14) // Output enabled (transmit-only mode)
#define SPI_BIDIRECTIONAL_DATA_EN  (1 << 15) // 1-line bidirectional data mode selected \
                                                else 2-line unidirectional data mode selected
// SPI control register 2 (SPI_CR2)
#define SPI_RX_DMA_BUFFER_EN          (1 << 16) // Rx buffer DMA enabled
#define SPI_TX_DMA_BUFFER_EN          (1 << 17) // Tx buffer DMA enabled
#define SPI_SS_OUT_EN                 (1 << 18) // SS output is enabled in master mode and when the cell is enabled. \
                                                   The cell cannot work in a multimaster environment
#define SPI_FRAME_MOTOROLA_FORMAT     (0 << 20) // SPI Motorola mode
#define SPI_FRAME_TI_FORMAT           (1 << 20) // SPI TI mode
#define SPI_ERR_INTERRUPT_EN          (1 << 21) // Error interrupt is enabled
#define SPI_RX_BUFFER_XEMPTY_INTERRUPT_EN   (1 << 22) // RXNE interrupt not masked. Used to generate an \
                                                         interrupt request when the RXNE flag is set.
#define SPI_TX_BUFFER_XEMPTY_INTERRUPT_EN   (1 << 23) // TXE interrupt not masked. Used to generate an \
                                                         interrupt request when the TXE flag is set.

/****************************STATUS FLAGS DEFINITION****************************/
// SPI status register (SPI_SR)
#define SPI_RX_BUFFER_XEMPTY                (1 << 0) // Rx buffer not empty
#define SPI_TX_BUFFER_EMPTY                 (1 << 1) // Tx buffer empty
#define SPI_CH_RIGHT                        (1 << 2) // Channel Right has to be transmitted or has been received
#define SPI_UNDERRUN                        (1 << 3) // Underrun flag
#define SPI_CRC_ERR                         (1 << 4) // CRC value received does not match the SPI_RXCRCR value
#define SPI_MODE_FAULT                      (1 << 5) // Mode fault occurred
#define SPI_OVERRUN                         (1 << 6) // Overrun occurred
#define SPI_BUSY                            (1 << 7) // SPI (or I2S) is busy in communication or Tx buffer is not empty
#define SPI_FRAME_FORMAT_ERR                (1 << 8) // A frame format error occurred

/****************************MACROS DEFINITION***************************/
#define spiGetStatus(spi, whichFlag)    (spi)->SR & whichFlag
#define isSpiTxBufferEmpty(spi) 		spiGetStatus(spi, SPI_TX_BUFFER_EMPTY)
#define isSpiRxBufferNotEmpty(spi)		spiGetStatus(spi, SPI_RX_BUFFER_XEMPTY)
#define isSpiBusy(spi)					spiGetStatus(spi, SPI_BUSY)
#define spiClearFlag(spi, whichFlag)    (spi)->SR &= ~(whichFlag)
#define spiClearAllFlags(spi)           spiClearFlag(spi, SPI_RX_BUFFER_XEMPTY |  SPI_TX_BUFFER_EMPTY |\
                                                          SPI_CH_RIGHT | SPI_UNDERRUN | SPI_CRC_ERR | \
                                                          SPI_MODE_FAULT | SPI_OVERRUN | SPI_BUSY | \
                                                          SPI_FRAME_FORMAT_ERR)

/**************************FUNCTIONS DECLARATION*************************/
void spiEnableClock(spiRegs *spi);
void configureSPI(spiRegs *spi, uint32_t mode);
void spiWriteData(spiRegs *spi, uint16_t data);
uint16_t spiReadData(spiRegs *spi);

#endif /* __SPI_H__ */
