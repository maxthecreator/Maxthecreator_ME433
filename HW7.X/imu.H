#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <math.h> 

#define imuwrite 0xd6
#define imuread 0xd7
#define ctrl1_xl 0x10
#define ctrl2_g 0x11
#define ctrl3_c 0x12


void i2c_master_setup(void) ;

void i2c_master_start(void) ;

void i2c_master_restart(void) ;

void i2c_master_send(unsigned char byte) ;

unsigned char i2c_master_recv(void) ;

void i2c_master_ack(int val) ;

void i2c_master_stop(void) ;

void I2C_read_multiple(unsigned char address, unsigned char reg, unsigned char * data, int length);

void imusetup(void);

unsigned char whoami(void);

void I2C_read_multiple(unsigned char address, unsigned char register, unsigned char * data, int length);
