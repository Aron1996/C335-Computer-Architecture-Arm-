/**********************************************************                                               
 * mywc.c                                                                                                              
 * main                                                                                           
 * Author: Yaokun Zhang                                                                                          
 * Date Created: Sep 8, 2017                                     
 * Last Modified by: Yaokun Zhang                                                                                 
 * Date Last Modified: Sep 8, 2017                                                                              
 * Assignment: Lab3                                                                                          
 * Part of: C335 assignment                                                        
 */
#include <stm32f30x.h>  // Pull in include files for F30x standard drivers 
#include <f3d_led.h>     // Pull in include file for the local drivers
#include <f3d_user_btn.h>

// Simple looping delay function
void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int main(void) {

  f3d_led_init();
  f3d_user_btn_init();
  while(1){
    while(user_btn_read()){}
    f3d_led_all_off();
    int i;
    for(i = 0; i < 8; i++){
      f3d_led_on(i);
      delay();
      while(user_btn_read()){}
      f3d_led_off(i);
    }
    f3d_led_all_on();
    delay();
    
  }
}
/* main.c ends here */
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
while(1);
/* Infinite loop */
/* Use GDB to find out why we're here */
}
#endif

