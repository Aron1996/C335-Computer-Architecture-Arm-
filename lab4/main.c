/* main.c --- 
 * 
 * Filename: main.c
 * Description: main  
 * Author:Yaokun Zhang, William Ollo 
 * username: yaokzhan, wbollo
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: Yaokun Zhang
 *           Date: 09/21/17
 */

#include <f3d_uart.h>
#include <stdio.h>
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {
  f3d_uart_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  int c;
  int count_Lines ;
  int count_Words ;
  int count_Char = 0;
  while(1){
    while ((c = getchar()) != 0x1b){
      if(c == '\n'){
	count_Lines++;
      }if(c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\f' || c == '\v'){
	count_Words++;
      }
      count_Char++;
    }
    printf("%d ", count_Lines);
    printf("%d ", count_Words);
    printf("%d\n", count_Char);
  
    count_Lines =0;
    count_Words =0;
    count_Char = 0;
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
