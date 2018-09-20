//Partner: Yaokun Zhang

/* f3d_i2c.h ---
 *
 * Filename: f3d_i2c.h
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

void f3d_i2c1_init();
void f3d_i2c1_read(uint8_t device, uint8_t reg, uint8_t* buffer, uint16_t numbytes);
void f3d_i2c1_read_nunchuck (uint8_t device, uint8_t* buffer, uint16_t numbytes);
void f3d_i2c1_write(uint8_t device, uint8_t reg, uint8_t* value);
void f3d_i2c2_init();
void f3d_i2c2_read(uint8_t device, uint8_t reg, uint8_t* buffer, uint16_t numbytes);
void f3d_i2c2_read_nunchuck (uint8_t device, uint8_t* buffer, uint16_t numbytes);
void f3d_i2c2_write(uint8_t device, uint8_t reg, uint8_t* value);


/* f3d_i2c.h ends here */
