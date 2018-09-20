/********************************************************** 
 * main.c
 * 
 * 
 *   Author: Yaokun Zhang, Akash Shah 
 *   Username: yaokzhan, akjshah
 *   Date Created: 10/12/17 
 *   Assignment: lab6
 */ 
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>

#define TIMER 20000

int main(void) {
  //initialization
  f3d_gyro_init();
  f3d_uart_init();
  f3d_lcd_init();

  while(1) {
    f3d_lcd_fillScreen2(WHITE);  
    delay(250);
    
    f3d_lcd_fillScreen(WHITE);
    delay(250);
  }

  //array to store gyro data
  float test[3];
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  //variables
  char x[10];
  char y[10];
  char z[10];
  int i =0;
  
  //while running
  while(1){
    //get the gyro data
    f3d_gyro_getdata(test);

    //write the gyro data to the LCD
    f3d_lcd_drawString(0,0, "x: ", BLACK, WHITE);
    snprintf(x, 10, "%f", test[0]);
    f3d_lcd_drawString(15,0, x, BLACK, WHITE);

    f3d_lcd_drawString(0,10, "y: ", BLACK, WHITE);
    snprintf(y, 10, "%f", test[1]);
    f3d_lcd_drawString(15,10, y, BLACK, WHITE);

    f3d_lcd_drawString(0,20, "z: ", BLACK, WHITE);
    snprintf(z, 10, "%f", test[2]);
    f3d_lcd_drawString(15,20, z, BLACK, WHITE);

    //create a bar graph for the gyro data
    f3d_lcd_drawChar(20,150, 'x', BLACK, WHITE);
    f3d_lcd_drawChar(40,150, 'y', BLACK, WHITE);
    f3d_lcd_drawChar(60,150, 'z', BLACK, WHITE);
    
    //clear the previous graph
    for(i = 0; i < 150; i++){
      f3d_lcd_drawPixel(15, 150-i, WHITE);
      f3d_lcd_drawPixel(20, 150-i, WHITE);
      f3d_lcd_drawPixel(35, 150-i, WHITE);
      f3d_lcd_drawPixel(40, 150-i, WHITE);
      f3d_lcd_drawPixel(55, 150-i, WHITE);
      f3d_lcd_drawPixel(60, 150-i, WHITE);
    }
    //if negative, make a red bar; if positive, make a black bar
    //draw bars for x, y, z to the LCD
    if(test[0] < 0){
      for(i = 0; i > test[0]/5; i--){
	f3d_lcd_drawPixel(15, 150+i, RED);
      }
    }else{
      for(i = 0; i < test[0]/5; i++){
	f3d_lcd_drawPixel(20, 150-i, BLACK);
      }
    }
    if(test[1] < 0){
      for(i = 0; i > test[1]/5; i--){
	f3d_lcd_drawPixel(35, 150+i, RED);
      }
    }else{
      for(i = 0; i < test[1]/5; i++){
	f3d_lcd_drawPixel(40, 150-i, BLACK);
      }
    }
    if(test[2] < 0){
      for(i = 0; i > test[2]/5; i--){
	f3d_lcd_drawPixel(55, 150+i, RED);
      }
    }else{
      for(i = 0; i < test[2]/5; i++){
	f3d_lcd_drawPixel(60, 150-i, BLACK);
      }
    }
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
