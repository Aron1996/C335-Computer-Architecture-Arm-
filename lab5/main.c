//Joseph Hodson
//jthodson
//Yaokun Zhang
//yaokzhan

//main.c for lab5
#include <f3d_uart.h>
#include <stdio.h>
#include <f3d_gyro.h>
#include <f3d_led.h>
#include <f3d_user_btn.h>

void delay(void) {
  int i = 2000000;
  while (i-- > 0) {
    asm("nop"); /* This stops it optimising code out */
  }
}

int getchar2(void) {
  char c = 0;
  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != (uint16_t)RESET) {
    c = USART_ReceiveData(USART1);
  }
  return c;
}

int main(void){
  f3d_gyro_init();
  f3d_uart_init();
  f3d_led_init();
  f3d_user_btn_init();


  float test[3];
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  int count = 0;
  int mod = 0;

  char ch = 'x';
  

  while(1){
    f3d_gyro_getdata(test);

    switch (getchar2()) {
    case 'x':
      count = 0;
      break;
    case 'y':
      count = 1;
      break;
    case 'z':
      count = 2;
      break;
    default:
      break;
    }

    while (user_btn_read()) {
      count++;
      mod = count%3;
      delay();
    }
    
    if (test[count] <= 72 && test[count] >= 0) {
      GPIOE->BSRR = GPIO_Pin_9;
      delay();
      f3d_led_all_off();
    } 
    
    if (test[count] > 72 && test[count] <= 144) {
      GPIOE->BSRR = GPIO_Pin_9;
      GPIOE->BSRR = GPIO_Pin_8;
      delay();
      f3d_led_all_off();
    } 
    
    if (test[count] > 144 && test[count] <= 216) {
      GPIOE->BSRR = GPIO_Pin_9;
      GPIOE->BSRR = GPIO_Pin_8;
      GPIOE->BSRR = GPIO_Pin_15;
      delay();
      f3d_led_all_off();
    }
    
    if (test[count] > 216 && test[count] <= 288) {
      GPIOE->BSRR = GPIO_Pin_9;
      GPIOE->BSRR = GPIO_Pin_8;
      GPIOE->BSRR = GPIO_Pin_15;
      GPIOE->BSRR = GPIO_Pin_14;
      delay();
      f3d_led_all_off();
    }
    if (test[count] > 288 && test[count] <= 360) {
      GPIOE->BSRR = GPIO_Pin_9;
      GPIOE->BSRR = GPIO_Pin_8;
      GPIOE->BSRR = GPIO_Pin_15;
      GPIOE->BSRR = GPIO_Pin_14;
      GPIOE->BSRR = GPIO_Pin_13;
      delay();
      f3d_led_all_off();
    }
    if (test[count] >= -72 && test[count] <= 0) {
      GPIOE->BSRR = GPIO_Pin_9;
      delay();
      f3d_led_all_off();
    }
    if (test[count] < -72 && test[count] >= -144) {
      GPIOE->BSRR = GPIO_Pin_9;
      GPIOE->BSRR = GPIO_Pin_10;
      delay();
      f3d_led_all_off();
    } 
    if (test[count] < -144 && test[count] >= -216) {
      GPIOE->BSRR = GPIO_Pin_9;
      GPIOE->BSRR = GPIO_Pin_10;
      GPIOE->BSRR = GPIO_Pin_11;
      delay();
      f3d_led_all_off();
    } 
    if (test[count] < -216 && test[count] >= -288) {
      GPIOE->BSRR = GPIO_Pin_9;
      GPIOE->BSRR = GPIO_Pin_10;
      GPIOE->BSRR = GPIO_Pin_11;
      GPIOE->BSRR = GPIO_Pin_12;
      delay();
      f3d_led_all_off();
    } 
    if (test[count] < -288 && test[count] <= -360) {
      GPIOE->BSRR = GPIO_Pin_9;
      GPIOE->BSRR = GPIO_Pin_10;
      GPIOE->BSRR = GPIO_Pin_11;
      GPIOE->BSRR = GPIO_Pin_12;
      GPIOE->BSRR = GPIO_Pin_13;
      delay();
      f3d_led_all_off();
    }
    
    printf("X: %f Y: %f Z: %f\n", test[0], test[1], test[2]);
    printf("Velocity: %f\n", test[count]);
  }
}

void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
