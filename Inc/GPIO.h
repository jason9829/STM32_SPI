#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>

// GPIO mode is in bit 0 and 1
typedef enum{
	GPIO_INPUT = 0,
	GPIO_OUTPUT,
	GPIO_ALT_FUNC,
	GPIO_ANALOG
}	GpioMode;

// GPIO output driver type is in bit 2
typedef enum{
	GPIO_PUSH_PULL = 0,
	GPIO_OPEN_DRAIN = 1 << 2,	// use bit 3 bcz bit 1 and bit 2 used in GpioMode
}	GpioDriverType;

// GPIO output speed is in bits 3 and 4
typedef enum{
	GPIO_LOW_SPEED = 0,
	GPIO_MED_SPEED = 1 << 3,
	GPIO_HI_SPEED = 2 << 3,
	GPIO_VERY_HI_SPEED = 3 << 3,
}	GpioOutputSpeed;

// GPIO pull type is in bits 5 and 6
typedef enum{
	GPIO_NO_PULL = 0,
	GPIO_PULL_UP = 1 << 5,
	GPIO_PULL_DOWN = 2 << 5,
}	GpioPullType;

typedef enum{
	PIN_RESET = 0,
	PIN_SET,
}	GpioPinState;

typedef enum{
	gpioPin0  = 0x0001,
	gpioPin1  = 0x0002,
	gpioPin2  = 0x0004,
	gpioPin3  = 0x0008,
	gpioPin4  = 0x0010,
	gpioPin5  = 0x0020,
	gpioPin6  = 0x0040,
	gpioPin7  = 0x0080,
	gpioPin8  = 0x0100,
	gpioPin9  = 0x0200,
	gpioPin10 = 0x0400,
	gpioPin11 = 0x0800,
	gpioPin12 = 0x1000,
	gpioPin13 = 0x2000,
	gpioPin14 = 0x4000,
	gpioPin15 = 0x8000,
}	GpioPin;

typedef volatile uint32_t IORegister ;

typedef struct gpioRegs gpioRegs;
struct gpioRegs {
	IORegister mode;
	IORegister driverType;
	IORegister outSpeed;
	IORegister pullType;
	IORegister inData;
	IORegister outData;
	IORegister outBits;
	IORegister pinLock;
	IORegister altFuncLow;
	IORegister altFuncHi;
};

#define gpioA	((gpioRegs *)0x40020000)
#define gpioB	((gpioRegs *)0x40020400)
#define gpioC	((gpioRegs *)0x40020800)
#define gpioD	((gpioRegs *)0x40020c00)
#define gpioE	((gpioRegs *)0x40021000)
#define gpioF	((gpioRegs *)0x40021400)
#define gpioG	((gpioRegs *)0x40021800)
#define gpioH	((gpioRegs *)0x40021c00)
#define gpioI	((gpioRegs *)0x40022000)
#define gpioJ	((gpioRegs *)0x40022400)
#define gpioK	((gpioRegs *)0x40022800)


/*AF pins*/
typedef enum{
	AF0, AF1, AF2, AF3, AF4, AF5, AF6, AF7,
	AF8, AF9, AF10, AF11, AF12, AF13, AF14, AF15,

};
/*AF pins from bit 8 to 11*/
/*
#define AF0		(0 << 8)	// Port x Pin 0
#define AF1		(1 << 8)
#define AF2		(2 << 8)
#define AF3		(3 << 8)
#define AF4		(4 << 8)
#define AF5		(5 << 8)
#define AF6		(6 << 8)
#define AF7		(7 << 8)
#define AF8		(8 << 8)
#define AF9		(9 << 8)
#define AF10	(10 << 8)
#define AF11	(11 << 8)
#define AF12	(12 << 8)
#define AF13	(13 << 8)
#define AF14	(14 << 8)
#define AF15	(15 << 8)
*/
/*Functions*/

void GPIOConfigurePin(gpioRegs *port, GpioPin pins, int configuration);
void GPIOConfigureAltFunc(gpioRegs *port, GpioPin pin, int altFunc);
void GPIOwritePins(gpioRegs *port, GpioPin pins, GpioPinState pinState);
void GPIOTogglePin(gpioRegs *port, GpioPin pins);


#endif // __GPIO_H__
