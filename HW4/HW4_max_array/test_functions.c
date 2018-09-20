#include <stdio.h>
#include <stdint.h> 
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "maxArray_c.h"

void maxArray_test(void) {
  int error_count=0;
  int i = 0;
  unsigned int list[15] = 
    {
      1, 2,3,4,5,6,7,8,10
    };
  for(i = 0; i < 15; i++){
    // test code here
    if(maxArray(list, i) != maxArray_c(list, i)){
      error_count++;
      printf("Max Array error: recieved %d, expected  %d\n",maxArray(list, i), maxArray_c(list, i));
    }
  }
  if (!error_count) {
    printf("Max Array Tests Passed\n");
  }
  else {
    printf("Max Array Test: %d errors\n",error_count);
  }
}


/* test.c ends here */
