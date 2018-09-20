#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "stringLength_c.h"

void stringLength_test(void) {
  int error_count=0;
  int i;
  char str[20] = "asdfasfasdfasdf";
  // test code here
  if(stringLength(str) != stringLength_c(str)){
    printf("String Length error: stringLength() = %d, expected stringLength_c() = %d\n", stringLength(str), stringLength_c(str));
  }
  else{
    printf("String Length Tests Passed\n");
  }
}


/* test.c ends here */
