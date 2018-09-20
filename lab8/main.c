/* main.c ---
 *
 * Filename: main.c
 * Description: main for lcd
 * Author: Yaokun Zhang, Jiebo Wang
 * Username: yaokzhan, jiebwang
 * Created: Thu Jan 10 11:23:43 2013
 /* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_led.h> 
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <stdio.h>
#include <math.h>
#include <f3d_gyro.h>
#include <f3d_nunchuk.h>

#define TIMER 20000
#define PI 3.14159265


void drawLength(uint8_t x, uint8_t y, int length,uint16_t color){
  int i = 0;
  if (length > 0) {
    while (i < length) {
      f3d_lcd_drawPixel(x,y-i,color);
      i = i+1;
    }
  } else {
    while(i < (-1*length)) {
      f3d_lcd_drawPixel(x,y+i,color);
      i=i+1;
    }
  }
}
void drawWide(uint8_t x, uint8_t y, int length,uint16_t color){
  int i = 0;
  if (length > 0) {
    while (i < length) {
      f3d_lcd_drawPixel(x+i,y,color);
      i = i+1;
    }
  } else {
    while(i < (-1*length)) {
      f3d_lcd_drawPixel(x-i,y,color);
      i=i+1;
    }
  }
}
void drawNWSE(uint8_t x, uint8_t y, int length,uint16_t color){
  int i = 0;
  if (length > 0) {
    while (i < length) {
      f3d_lcd_drawPixel(x+i,y-i,color);
      i = i+1;
    }
  } else {
    while(i < (-1*length)) {
      f3d_lcd_drawPixel(x-i,y+i,color);
      i=i+1;
    }
  }
}
void drawSWNE(uint8_t x, uint8_t y, int length,uint16_t color){
  int i = 0;
  if (length > 0) {
    while (i < length) {
      f3d_lcd_drawPixel(x+i,y+i,color);
      i = i+1;
    }
  } else {
    while(i < (-1*length)) {
      f3d_lcd_drawPixel(x-i,y-i,color);
      i=i+1;
    }
  }
}


// use previous to create the bar
void drawBar(uint8_t x, uint8_t y, int length,uint16_t color){
  int i = 0;
  //set width to 15 
  while (i < 15) {
    drawLength(x+i,y,length,color);
    i = i + 1;
  }
}

void clean(void){
  f3d_lcd_drawString(60,60,"N",WHITE,WHITE);
  f3d_lcd_drawString(25,80,"W",WHITE,WHITE);
  f3d_lcd_drawString(90,80,"E",WHITE,WHITE);
  f3d_lcd_drawString(55,100,"S",WHITE,WHITE);

  f3d_lcd_drawString(50,45,"N",WHITE,WHITE);
  f3d_lcd_drawString(65,130,"S",WHITE,WHITE);

  f3d_lcd_drawString(15,60,"N",WHITE,WHITE);
  f3d_lcd_drawString(0,150,"W",WHITE,WHITE);
  f3d_lcd_drawString(100,70,"E",WHITE,WHITE);
  f3d_lcd_drawString(65,130,"S",WHITE,WHITE);

  f3d_lcd_drawString(0,85,"N",WHITE,WHITE);
  f3d_lcd_drawString(50,50,"E",WHITE,WHITE);
  f3d_lcd_drawString(50,120,"W",WHITE,WHITE);
  f3d_lcd_drawString(100,85,"S",WHITE,WHITE);
}


int main(void) {
  float gyro[3];
  float a[3];
  float m[3];
  int i = 0;
  char output[1000];
  char output2[1000];
  int button = 0;
  int screenint = 0;
  float pitch, heading, roll, xh, yh, degree, nun_pitch, nun_roll;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  // Set up your inits before you go ahead
  f3d_uart_init();
  delay(10);
  f3d_lcd_init();
  delay(10);
  f3d_led_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  f3d_i2c2_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_gyro_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  nunchuk_t nundata;
  f3d_lcd_fillScreen2(WHITE);
  
  while (1){
     
    // f3d_nunchuk_read(&nundata);
    f3d_accel_read(a);
    f3d_mag_read(m);
      
    //press button on the board to swtich condition 
    if (user_btn_read()){
      button= (button + 1)%4;
      while(user_btn_read());
    }
      
    //nunchuk button to change the button value to switch condition
    if (nundata.c != 0 ||nundata.jx>175 ||nundata.jy>175  ){
      button= (button + 1)%4;
      
    }
    //the other part
    if(nundata.z != 0||nundata.jx<50||nundata.jy<75){
      if (button == 0){
	button = 3;
	
      }
      else{
	button =( button - 1)%4;
	
      }
    }
    
    
    
    // gyro part
    if (button == 0){
      //clear the previous graph
      if (screenint == 0){
	f3d_lcd_fillScreen2(WHITE);
	screenint = (screenint + 1)%2;
      }
      //descrption part 
      f3d_lcd_drawString(0,150,"gryo part",RED,WHITE);
      
      //get gyro data
      f3d_gyro_getdata(gyro);
      // draw the basic stuff
      snprintf(output, 10, "%f", gyro[0]);
      f3d_lcd_drawString(0,0,"X: ",BLACK,WHITE);
      f3d_lcd_drawString(15,0,output,BLACK,WHITE);
      snprintf(output, 10, "%f", gyro[1]);
      f3d_lcd_drawString(0,10,"Y: ",BLACK,WHITE);
      f3d_lcd_drawString(15,10,output,BLACK,WHITE);
      snprintf(output, 10, "%f", gyro[2]);
      f3d_lcd_drawString(0,20,"Z: ",BLACK,WHITE);
      f3d_lcd_drawString(15,20,output,BLACK,WHITE);
      
      f3d_lcd_drawString(0,90,"0: ",BLACK,WHITE);
      //draw zero line //Separate the positive and negative value 
      for ( i = 0; i < 200; i++){
	f3d_lcd_drawPixel(i,90, RED);
  
      }
      //draw X Y Z bar
      f3d_lcd_drawString(5,80,"X: ",BLACK,WHITE);
      drawBar(20,90,(int) gyro[0]/8,RED);
      f3d_lcd_drawString(45,80,"Y: ",BLACK,WHITE);
      drawBar(70,90,(int) gyro[1]/8,GREEN);
      f3d_lcd_drawString(90,80,"Z: ",BLACK,WHITE);
      drawBar(110,90,(int) gyro[2]/8,BLUE); 
      delay(100);
      drawBar(20,90,(int) gyro[0]/8,WHITE);
      drawBar(70,90,(int) gyro[1]/8,WHITE);
      drawBar(110,90,(int) gyro[2]/8,WHITE);
      
    }


    // board titl angle part 
    else if (button == 1){
      //clear the previous graph
      if (screenint == 1){
	f3d_lcd_fillScreen2(WHITE);
	screenint = (screenint + 1)%2;
      }
      //description
      f3d_lcd_drawString(0,0,"board pitch roll part",RED,WHITE);
      // f3d_accel_read(a);
      //f3d_mag_read(m);
      //calculate the pitch, roll
      pitch = atan(a[0]/sqrt(pow(a[1],2) + pow(a[2],2)));
      roll = atan(a[1]/sqrt(pow(a[0],2) + pow(a[2],2)));
      xh = m[0] * cos(pitch) + m[2]*sin(pitch);
      yh = m[0] * sin(roll)*sin(pitch) + m[1]*cos(roll)-m[2]*sin(roll)*cos(pitch);
      heading = atan2f(yh,xh);
      
      //convert to degree 
      pitch = pitch *180/PI;
      roll = roll *180 /PI;
      
      //pitch part
      snprintf(output, 10, "%f", pitch);
      f3d_lcd_drawString(0,10,"pitch:",BLACK,WHITE);
      f3d_lcd_drawString(0,90 ,"pitch: ", BLACK, WHITE);
      f3d_lcd_drawString(40,10,output,BLACK,WHITE);
      //make sure will not excess the screen
      drawBar(40,90,(int)pitch*180/PI/90,BLUE);
      
      printf("pitch %f\n\n", pitch);
      
      //roll part
      snprintf(output, 10, "%f", roll);
      f3d_lcd_drawString(70,90,"roll: ", BLACK, WHITE);
      f3d_lcd_drawString(0,30,"roll",BLACK,WHITE);
      f3d_lcd_drawString(40,30,output,BLACK,WHITE);
      //make sure will not excess the screen
      drawBar(108,90,(int)roll*180/PI/90,RED);
      printf("roll %f\n", roll);
      
      delay(200);
      //clear bar
      drawBar(40,90,(int)pitch*180/PI/90,WHITE);
      drawBar(108,90,(int)roll*180/PI/90,WHITE);

    }
  



    //compass graph 
    else if (button ==2){
      //clear the previous graph
      if (screenint == 0){
	f3d_lcd_fillScreen2(WHITE);
	screenint = (screenint + 1)%2;
      }
     f3d_lcd_drawString(0,0,"compass roll part",RED,WHITE);
    
     //calculate the pitch, roll
     pitch = atan(a[0]/sqrt(pow(a[1],2) + pow(a[2],2)));
     roll = atan(a[1]/sqrt(pow(a[0],2) + pow(a[2],2)));
     xh = m[0] * cos(pitch) + m[2]*sin(pitch);
     yh = m[0] * sin(roll)*sin(pitch) + m[1]*cos(roll)-m[2]*sin(roll)*cos(pitch);
     heading = atan2f(yh,xh);
      
      //convert to degree 
      pitch = pitch *180/PI;
      roll = roll *180 /PI;
      heading = (heading + PI)/2;
      degree = heading/PI *360;
      snprintf(output, 10, "%f", degree);
      f3d_lcd_drawString(0,10,"degree",BLACK,WHITE);
      f3d_lcd_drawString(40,10,output,BLACK,WHITE);
      f3d_lcd_drawString(0,30,"it is degree north",BLACK,WHITE);
      
      f3d_lcd_drawString(60,50,"W",BLACK,WHITE);
      f3d_lcd_drawString(30,70,"SW",BLACK,WHITE);
      f3d_lcd_drawString(110,90,"N",BLACK,WHITE);
      f3d_lcd_drawString(85,70,"NW",BLACK,WHITE);
      f3d_lcd_drawString(60,140,"E",BLACK,WHITE);
      f3d_lcd_drawString(30,115,"SE",BLACK,WHITE);
      f3d_lcd_drawString(10 ,90,"S",BLACK,WHITE);
      f3d_lcd_drawString(85,115,"NE",BLACK,WHITE);

      if(degree > 350 ){
	//clean
	drawLength(60,90,-40,WHITE);
	drawWide(60,90,-40,WHITE);
	drawWide(60,90,40,WHITE);
	drawNWSE(60,90,20,WHITE);
	drawNWSE(60,90,-20,WHITE);
	drawSWNE(60,90,20,WHITE);
	drawSWNE(60,90,-20,WHITE);

      	drawLength(60,90,40,BLACK);
	     
      } 
      else if(degree > 0 && degree < 10){
	drawLength(60,90,-40,WHITE);
	drawWide(60,90,-40,WHITE);
	drawWide(60,90,40,WHITE);
	drawNWSE(60,90,20,WHITE);
	drawNWSE(60,90,-20,WHITE);
	drawSWNE(60,90,20,WHITE);
	drawSWNE(60,90,-20,WHITE);

      	drawLength(60,90,40,BLACK); 
      }
      
      else if(degree > 35 && degree < 50){
	//clean
	drawLength(60,90,-40,WHITE);
	drawWide(60,90,-40,WHITE);
	drawWide(60,90,40,WHITE);
	drawNWSE(60,90,20,WHITE);
	drawNWSE(60,90,-20,WHITE);
	drawSWNE(60,90,20,WHITE);
	drawLength(60,90,40,WHITE);

	drawSWNE(60,90,-20,BLACK);
      }
      else if(degree > 70 && degree < 95){
	//clean
	drawLength(60,90,-40,WHITE);
	drawWide(60,90,40,WHITE);
	drawNWSE(60,90,20,WHITE);
	drawNWSE(60,90,-20,WHITE);
	drawSWNE(60,90,20,WHITE);
	drawLength(60,90,40,WHITE);
	drawSWNE(60,90,-20,WHITE);

	drawWide(60,90,-40,BLACK);
      }
      else if(degree > 100 && degree < 120){
	//clean
	drawLength(60,90,-40,WHITE);
	drawWide(60,90,40,WHITE);
	drawNWSE(60,90,20,WHITE);
	drawSWNE(60,90,20,WHITE);
	drawLength(60,90,40,WHITE);
	drawSWNE(60,90,-20,WHITE);
	drawWide(60,90,-40,WHITE);

	drawNWSE(60,90,-20,BLACK);
      }
      else if(degree > 155 && degree < 170){
	//clean
	drawWide(60,90,40,WHITE);
	drawNWSE(60,90,20,WHITE);
	drawSWNE(60,90,20,WHITE);
	drawLength(60,90,40,WHITE);
	drawSWNE(60,90,-20,WHITE);
	drawWide(60,90,-40,WHITE);
	drawNWSE(60,90,-20,WHITE);

	drawLength(60,90,-40,BLACK);
      }
      else if(degree > 195 && degree < 215){
	//clean
	drawWide(60,90,40,WHITE);
	drawNWSE(60,90,20,WHITE);
	drawLength(60,90,40,WHITE);
	drawSWNE(60,90,-20,WHITE);
	drawWide(60,90,-40,WHITE);
	drawNWSE(60,90,-20,WHITE);
	drawLength(60,90,-40,WHITE);
	
       
	drawSWNE(60,90,20,BLACK);
      }
      else if(degree > 255 && degree < 275){
	//clean
	drawNWSE(60,90,20,WHITE);
	drawLength(60,90,40,WHITE);
	drawSWNE(60,90,-20,WHITE);
	drawWide(60,90,-40,WHITE);
	drawNWSE(60,90,-20,WHITE);
	drawLength(60,90,-40,WHITE);
	drawSWNE(60,90,20,WHITE);

	drawWide(60,90,40,BLACK);
      }
      else if (degree > 315 && degree < 330){
	//clean
	drawLength(60,90,40,WHITE);
	drawSWNE(60,90,-20,WHITE);
	drawWide(60,90,-40,WHITE);
	drawNWSE(60,90,-20,WHITE);
	drawLength(60,90,-40,WHITE);
	drawSWNE(60,90,20,WHITE);
	drawWide(60,90,40,WHITE);

	drawNWSE(60,90,20,BLACK);
      }
      else{
	//do nothing 
      }

	
    }
    
    //nunchuk part
    else {
      //clear the previous graph
      if (screenint == 1){
	f3d_lcd_fillScreen2(WHITE);
	screenint = (screenint + 1)%2;
      }
      f3d_nunchuk_read(&nundata);
      f3d_lcd_drawString(0,5,"nunchuk part",RED,WHITE);
      nun_pitch = atan(nundata.ax/sqrt(pow(nundata.ay,2) + pow(nundata.z,2)))*180/PI;
      nun_roll = atan(nundata.ay/sqrt(pow(nundata.ax,2) + pow(nundata.az,2)))*180/PI;
      
      snprintf(output2, 10, "%f", nun_pitch);
      f3d_lcd_drawString(0,20,"Nunchuk pitch:",BLACK,WHITE);
      f3d_lcd_drawString(0,130 ,"pitch: ", BLACK, WHITE);
      f3d_lcd_drawString(60,30,output2,BLACK,WHITE);
      //make sure will not excess the screen
      drawBar(40,130,(int)nun_pitch,BLUE);
      
      
      //roll part
      snprintf(output2, 10, "%f", nun_roll);
      f3d_lcd_drawString(70,130,"roll: ", BLACK, WHITE);
      f3d_lcd_drawString(0,40,"Nunchuk roll:",BLACK,WHITE);
      f3d_lcd_drawString(60,50,output2,BLACK,WHITE);
      //make sure will not excess the screen
      drawBar(108,130,(int)nun_roll,RED);
     
      delay(200);
      //clear bar
      drawBar(40,130,(int)nun_pitch,WHITE);
      drawBar(108,130,(int)nun_roll,WHITE);
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




