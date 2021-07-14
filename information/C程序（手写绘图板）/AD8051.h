#ifndef _AD8051_H
#define _AD8051_H

#define uint unsigned int
#define uchar unsigned char

void init_I2C(void);
void write_I2C(uchar addr,uchar date);
uchar read_I2C(uchar addr);

unsigned char Read_AD(unsigned char Chl);
  
#endif
