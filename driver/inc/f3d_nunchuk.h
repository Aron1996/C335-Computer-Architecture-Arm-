/* f3d_nunchuk.h --- 
 * Filename: f3d_nunchuk.h
 * Description: main for lcd
 * Author: Yaokun Zhang, Jiebo Wang
 * Username: yaokzhan, jiebwang
 * Created: Thu Jan 10 11:23:43 2013

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */
#include <stm32f30x.h>

typedef struct nunchuk_data { 
  unsigned char jx;
  unsigned char jy;
  unsigned short ax;
  unsigned short ay;
  unsigned short az;
  unsigned char c;
  unsigned char z;
} nunchuk_t; 

void f3d_nunchuk_init(void);
void f3d_nunchuk_read(nunchuk_t *);

/* f3d_nunchuk.h ends here */
