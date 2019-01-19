#include "SPI_FUNCTIONS_TEST.h"
#include <stdlib.h>

int compareSpiCommand(char *str, char *command){
	int i = 0;
  int offset = 0;

	while(*str == ' '){
		str++;
    offset++;
	}
	while(command[i] != '\0'){
		if(*str == command[i]){
			str++;
			i++;
      offset++;
		}
		else
			return -1;
	}
	return offset;
}

void numbersInString(char *str, int base){
  char *end = NULL;
  char *prevEndPtr = NULL;
  int i = 0;

  end = str;
//  while(prevEndPtr != &end){
        prevEndPtr = end;
      buffer[i] = strtol(end, &end ,base);
      //prevEndPtr = end;
      i++;
      printf("\n AFTER : end-> %p, &end-> %p, prevEndPtr-> %p", end, &end,prevEndPtr );
    //}
  /*
do{
    prevEndPtr = end;
    buffer[i] = strtol(end, &end ,base);
    i++;
      printf("\n AFTER : end-> %p, &end-> %p, prevEndPtr-> %p", end, &end,prevEndPtr );
  }while(prevEndPtr != &end);*/
}
