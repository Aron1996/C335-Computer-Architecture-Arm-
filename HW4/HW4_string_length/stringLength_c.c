#include <stdio.h>
#include <string.h>


int stringLength_c(char *c ){
  int length = 0;
  while(*(c + length)) length++;
  return length;
}
