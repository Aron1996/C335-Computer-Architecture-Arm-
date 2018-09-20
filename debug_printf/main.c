/********************************************************** 
 *   Author: Akash Shah, Yaokun Zhang
 *   Date Created: 9-29-17
 *   Last Modified by: Akash Shah, Yaokun Zhang
 *   Date Last Modified: 9-29-17 
 *   Assignment: lab6 
 *   Part of: lab6
 */ 

/* main.c 
   debug this function using gdb*/


/*
  The expected performace of the program is as follows:
  We want to print out the actual bits of numbers! What a great
  way to understand how number representation works

 */

//The libraries to include
#include <f3d_uart.h>
#include <stdio.h> 
#include <stdint.h>
#include <f3d_led.h>

//function to delay
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

//runs some test on our program
int main(){
  //initialize
  f3d_led_init();
  f3d_uart_init();

  //while running
  while(1) {
    //turn on LED
    f3d_led_on(0);

    //delay with printf
    printf("This is a longer sentence that takes longer\n");
    printf("This is a longer sentence that takes longer\n");
    printf("This is a longer sentence that takes longer\n");
    printf("This is a longer sentence that takes longer\n");
    printf("This is a longer sentence that takes longer\n");

    //turn off LED
    f3d_led_off(0);

    //delay with printf
    printf("This is a longer sentence that takes longer\n");
    printf("This is a longer sentence that takes longer\n");
    printf("This is a longer sentence that takes longer\n");
    printf("This is a longer sentence that takes longer\n");
    printf("This is a longer sentence that takes longer\n");
  }

}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
