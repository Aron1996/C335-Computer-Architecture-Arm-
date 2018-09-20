/**********************************************************                                                                                       
 * poly.c                                                                                                              
 * show the content in memory address                                                                                                   
 * Author: Yaokun Zhang              
 * Partners: Jiebo Wang, Yuhan Zeng                                                                                                             
 * Date Created: Sep 1, 2017                                                                                                                      
 * Last Modified by: Yaokun Zhang                                                                                                                 
 * Date Last Modified: Sep 7, 2017                                                                                                                
 * Assignment: Lab2                                                                                                                      
 * Part of: C335 assignment                                                                                                                       
 */
#include <stdio.h>

void dump_memory(void *p, int len)
{
  int i;
  int c;
  printf("address      char hexCh short     integer         float      doubleFloat\n");

  for (i = 0; i < len; i++) {
    c = *(unsigned char *)(p + i);

    if (c >= 32 && c < 127) { // Check if the character is printable or not.
      printf("%8p%3c 0x%2x", p + i, c, c); // Print address, char, hexCh if printable.
    } else {
      printf("%8p  ? 0x%2x", p + i, c); // Print address, '?', hexCh if unprintable.
    }

    if (i % 2 == 0) {
      printf(" %+6d", *(unsigned short *)(p + i)); // Print short every 2 bytes.
    }
    
    if (i % 4 == 0) {
      printf(" %+11d %+13e", *(unsigned int *)(p + i), *(float *)(p + i)); // Print integer and float every 4 bytes.
    }

    if (i % 8 == 0) {
      printf("   %+14e", *(double *)(p + i)); // Print double every 8 bytes.
    }

    printf("\n");
  }
}
