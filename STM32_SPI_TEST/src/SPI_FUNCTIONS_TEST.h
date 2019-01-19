#ifndef _SPI_FUNCTIONS_TEST_H
#define _SPI_FUNCTIONS_TEST_H

char buffer[128];

// compare the command
int compareSpiCommand(char *str, char *command);
// save numbers in string to an buffer
void numbersInString(char *str, int base);

#endif // _SPI_FUNCTIONS_TEST_H
