
#ifndef I2C_MASTER_NOINT_H__
#include <xc.h>
#define I2C_MASTER_NOINT_H__

// Header file for i2c_master_noint.c

// helps implement use I2C1 as a master without using interrupts

void i2c_master_setup(void)

void i2c_master_start(void);

void i2c_master_restart(void);

void i2c_master_send(unsigned char byte);

unsigned char i2c_master_recv(void);

void i2c_master_ack(int);

void i2c_master_stop(void);

#endif