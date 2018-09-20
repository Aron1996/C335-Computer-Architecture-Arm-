/* main.c --- 
 * 
 * Filename: main.c
 * Description: 
 * Author: Yaokun Zhang, Jiebo Wang
 * Username: yaokzhan, jiebwang
 * Created: Thu Jan 10 11:23:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */
/* Code: */
  

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_led.h>
#include <f3d_uart.h>
#include <f3d_gyro.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <f3d_rtc.h>
#include <ff.h>
#include <diskio.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

void die (FRESULT rc) {
  printf("Failed with rc=%u.\n", rc);
  while (1);
}

FATFS Fatfs;	/* File system object */
FIL Fil;	/* File object */

typedef struct bmppixel { // little endian byte order
  uint8_t b;
  uint8_t g;
  uint8_t r;
}pix; 


pix Buff[128];	/* File read buffer */
uint8_t Buff2[54];
float a[3];  //accelerometer
float m[3];  // magntitude
int i = 0;
float pitch,roll;
nunchuk_t nundata;
int state,rotation;


int main(void) {
  
  int i,j;
  int manhelp1 = 0;
  int manhelp2 = 0;
  int manhelp3 = 0;
  int manhelp4 = 0;
  int trumphelp1 = 0;
  int trumphelp2 = 0;
  int trumphelp3 = 0;
  int trumphelp4 = 0;
  int smilehelp1 = 0;
  int smilehelp2 = 0;
  int smilehelp3 = 0;
  int smilehelp4 = 0;


  FRESULT rc;	/* Result code */
  DIR dir;	/* Directory object */
  FILINFO fno;	/* File information object */
  UINT bw, br;
  unsigned int retval;

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_uart_init();
  delay(10);
  f3d_lcd_init();
  delay(10);
  f3d_delay_init();
  delay(10);
  f3d_rtc_init();
  delay(10);
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);


  f_mount(0, &Fatfs);	/* Register volume work area (never fails) */
  
  f3d_lcd_fillScreen(BLACK);
 
  state = 0;
  rotation = 0;
  while(1){
    
    // read the nunchuk, acc and mag data 
    f3d_nunchuk_read(&nundata);
    f3d_accel_read(a);
    f3d_mag_read(m);
    delay(500);

    //switch image
    if(nundata.jx>175 ||nundata.jy<75) {
      state = (state + 1)%3;  // only have 3 images
    }

    else if(nundata.jy>175 ||nundata.jx<75) {
      if (state == 0){
	state = 2;
      }
      else{
	state = (state -1)%3; //only have 3 iamges
      }
    }
  
    //calculation 
    pitch = atan(a[0]/sqrt(pow(a[1],2) + pow(a[2],2)));
    roll = atan(a[1]/sqrt(pow(a[0],2) + pow(a[2],2)));
    pitch = pitch *180/PI;//covert to degree
    roll = roll *180 /PI;
    

     //rotation image 
    if(roll <- 45){
      rotation = 1;
    }
    else if ( pitch > 45){
      rotation = 2;

    }
    else if (roll > 45) {
      rotation = 3;

    }
    else if (pitch < -45){
      rotation =0;
  
    }
    else {} //do nothing 

    //man image process 
    //rotation state = 0
    if (state == 0 && manhelp1 == 0 && rotation == 0){
      rc = f_open(&Fil, "MAN.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      if (rc) die(rc);
      for(j = 128; j>0 ; j--){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	    
	  f3d_lcd_drawPixel(i,j,color);
	} 
      }
      manhelp1 =1;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 0;
      rc = f_close(&Fil);
    }
    
    //rotation state = 1
    if (state == 0 && manhelp2 == 0 && rotation == 1){
      rc = f_open(&Fil, "MAN.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      
      if (rc) die(rc);
      for(j = 128; j>0 ; j--){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	
	  f3d_lcd_drawPixel(j,i,color);
	}
      }
      manhelp1 =0;
      manhelp2 = 1;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 0;
      rc = f_close(&Fil);
    }
    
    //rotation state = 2
    if (state == 0 && manhelp3 == 0 && rotation == 2){
      rc = f_open(&Fil, "MAN.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      if (rc) die(rc);
      for(j = 0; j<128 ; j++){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	  
	  f3d_lcd_drawPixel(i,j,color);
	}
      }
      manhelp1 = 0;
      manhelp2 = 0;
      manhelp3 = 1;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 0;
      
      rc = f_close(&Fil);
    }
    //rotaion state = 3
    if (state == 0 && manhelp4 == 0 && rotation == 3){
      rc = f_open(&Fil, "MAN.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      if (rc) die(rc);
      for(j = 0; j<128 ; j++){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	  
	  f3d_lcd_drawPixel(j,i,color);
	}
      }
      manhelp1 = 0;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 1;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 0;
      rc = f_close(&Fil);
    }
    // image TRUMP state 
    //rotation state = 0 
    if (state == 1 && trumphelp1 == 0 && rotation == 0){
      rc = f_open(&Fil, "TRUMP.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      if (rc) die(rc);
      for(j = 128; j>0 ; j--){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	  
	  f3d_lcd_drawPixel(i,j,color);
	}
      }
      manhelp1 = 0;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 1;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 0;
      rc = f_close(&Fil);
      }

 
    //rotation state = 1
    if (state == 1 && trumphelp2 == 0 && rotation == 1){
      rc = f_open(&Fil, "TRUMP.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      
      if (rc) die(rc);
      for(j = 128; j>0 ; j--){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	
	  f3d_lcd_drawPixel(j,i,color);
	}
      }
      manhelp1 =0;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 1;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 0;
      rc = f_close(&Fil);
    }
    
    //rotation state = 2
    if (state == 1 && manhelp3 == 0 && rotation == 2){
      rc = f_open(&Fil, "TRUMP.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      if (rc) die(rc);
      for(j = 0; j<128 ; j++){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	  
	  f3d_lcd_drawPixel(i,j,color);
	}
      }
      manhelp1 = 0;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 1;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 0;
      
      rc = f_close(&Fil);
    }
    //rotaion state = 3
    if (state == 1 && trumphelp4 == 0 && rotation == 3){
      rc = f_open(&Fil, "TRUMP.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      if (rc) die(rc);
      for(j = 0; j<128 ; j++){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	  
	  f3d_lcd_drawPixel(j,i,color);
	}
      }
      manhelp1 = 0;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 1;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 0;
      rc = f_close(&Fil);
    }
    
    // image SMILE state  = 2
    //rotation state = 0 
    if (state == 2 && smilehelp1 == 0 && rotation == 0){
      rc = f_open(&Fil, "SMILE.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      if (rc) die(rc);
      for(j = 128; j>0 ; j--){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	  
	  f3d_lcd_drawPixel(i,j,color);
	}
      }
      manhelp1 = 0;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 1;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 0;
      rc = f_close(&Fil);
      }

 
    //rotation state = 1
    if (state == 2 && smilehelp2 == 0 && rotation == 1){
      rc = f_open(&Fil, "SMILE.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      
      if (rc) die(rc);
      for(j = 128; j>0 ; j--){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	
	  f3d_lcd_drawPixel(j,i,color);
	}
      }
      manhelp1 =0;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 1;
      smilehelp3 = 0;
      smilehelp4 = 0;
      rc = f_close(&Fil);
    }
    
    //rotation state = 2
    if (state == 2 && smilehelp3 == 0 && rotation == 2){
      rc = f_open(&Fil, "SMILE.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      if (rc) die(rc);
      for(j = 0; j<128 ; j++){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	  
	  f3d_lcd_drawPixel(i,j,color);
	}
      }
      manhelp1 = 0;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 1;
      smilehelp4 = 0;
      
      rc = f_close(&Fil);
    }
    //rotaion state = 3
    if (state == 2 && smilehelp4 == 0 && rotation == 3){
      rc = f_open(&Fil, "SMILE.bmp", FA_READ);
      if (rc) die(rc);
      rc = f_read(&Fil, Buff2,sizeof Buff2, &br);		
      if (rc) die(rc);
      for(j = 0; j<128 ; j++){
	rc = f_read(&Fil, Buff, sizeof Buff, &br);
	if(rc) die(rc);
	for(i = 0; i < 128; i++){
	  uint16_t color = ((uint16_t) (Buff[i].b >> 3)) << 11 | ((uint16_t) (Buff[i].g >> 2)) << 5  | (Buff[i].r >> 3);
	  
	  f3d_lcd_drawPixel(j,i,color);
	}
      }
      manhelp1 = 0;
      manhelp2 = 0;
      manhelp3 = 0;
      manhelp4 = 0;
      trumphelp1 = 0;
      trumphelp2 = 0;
      trumphelp3 = 0;
      trumphelp4 = 0;
      smilehelp1 = 0;
      smilehelp2 = 0;
      smilehelp3 = 0;
      smilehelp4 = 1;
      rc = f_close(&Fil);
    }


    


    
    printf("jx %d",nundata.jx);
    printf("jy %d\n\n", nundata.jy);
    printf("state num %d \n",state);
    printf("pitch %f, \n",pitch);  
    printf("rotation num %d \n",rotation); 
    
  
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

