#include "imu.h"

void i2c_master_setup(void) {
    
  ANSELBbits.ANSB2 = 0;
  ANSELBbits.ANSB3 = 0;
                                 
  I2C2BRG = 0x035;            // I2CBRG = [1/(2*Fsck) - PGD]*Pblck - 2 
  I2C2CONbits.ON = 1;               // turn on the I2C1 module

}

// Start a transmission on the I2C bus

void i2c_master_start(void) {

    I2C2CONbits.SEN = 1;            // send the start bit

    while(I2C2CONbits.SEN) { ; }    // wait for the start bit to be sent

}

void i2c_master_restart(void) {     

    I2C2CONbits.RSEN = 1;           // send a restart 

    while(I2C2CONbits.RSEN) { ; }   // wait for the restart to clear

}

void i2c_master_send(unsigned char byte) { // send a byte to slave

  I2C2TRN = byte;                   // if an address, bit 0 = 0 for write, 1 for read

  while(I2C2STATbits.TRSTAT) { ; }  // wait for the transmission to finish

  if(I2C2STATbits.ACKSTAT) {        // if this is high, slave has not acknowledged

    // ("I2C2 Master: failed to receive ACK\r\n");

  }

}

unsigned char i2c_master_recv(void) { // receive a byte from the slave

    I2C2CONbits.RCEN = 1;             // start receiving data

    while(!I2C2STATbits.RBF) { ; }    // wait to receive the data

    return I2C2RCV;                   // read and return the data

}


void i2c_master_ack(int val) {        // sends ACK = 0 (slave should send another byte)

                                      // or NACK = 1 (no more bytes requested from slave)

    I2C2CONbits.ACKDT = val;          // store ACK/NACK in ACKDT

    I2C2CONbits.ACKEN = 1;            // send ACKDT

    while(I2C2CONbits.ACKEN) { ; }    // wait for ACK/NACK to be sent

}


void i2c_master_stop(void) {          // send a STOP:

  I2C2CONbits.PEN = 1;                // comm is complete and master relinquishes bus

  while(I2C2CONbits.PEN) { ; }        // wait for STOP to complete

}


//To set the sample rate to 1.66 kHz, with 2g sensitivity, and 100 Hz filter. 

//address: CTRL1_XL (10h) 
//bit:   10000010 (82h)

//CTRL2_G register. Set the sample rate to 1.66 kHz, with 1000 dps sensitivity.
//address: CTRL2_G (11h) 
//bit: 10001000


//CTRL3_C (12h) 
//address: CTRL3_C (12h) 
//bit: 00000100

void imusetup(void){
    i2c_master_setup();
    i2c_master_start();
    
    i2c_master_send(imuwrite);
    
    i2c_master_send(ctrl1_xl);
    i2c_master_send (0x82);
  //  i2c_master_stop();
    i2c_master_stop();
    i2c_master_start();
    i2c_master_send(imuwrite);
    
    i2c_master_send(ctrl2_g);
    i2c_master_send(0x88);
    
    i2c_master_stop();
    i2c_master_start();
    i2c_master_send(imuwrite);
    
    i2c_master_send(ctrl3_c);
    i2c_master_send(0x04);
    
    i2c_master_stop();
}    

unsigned char whoami(void){
    unsigned char c;
    i2c_master_start();
    
    i2c_master_send(imuwrite);
    i2c_master_send(0x0f); //who am i register
    i2c_master_restart();
    i2c_master_send(imuread);
    c = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    return c;
}


void I2C_read_multiple(unsigned char address, unsigned char reg, unsigned char * data, int length){
    char c, d;
    int i;
    c = (address << 1) | 0;
    d = (address << 1) | 1;
    
    i2c_master_start();
    i2c_master_send(c);
    i2c_master_send(reg);
    i2c_master_restart();
    i2c_master_send(d);
    for (i=0; i<length; i++){
        
        data[i] = i2c_master_recv();
        if (i == length - 1){
            i2c_master_ack(1);
        }
        else{
            i2c_master_ack(0);
        }
    }
    i2c_master_stop();
    
}
 
/*
void setExpander(char pin, char level){
    i2c_master_start();
    i2c_master_send(0x44); //chip address for write is 01000100
    i2c_master_send(0x09); //select gpio
    i2c_master_send(level << pin); //turn pin high
    i2c_master_stop();
}
        
unsigned char getExpander(void){
    i2c_master_start();
    i2c_master_send(0x44); //chip address for write is 01000100
    i2c_master_send(0x09); //select gpio
    i2c_master_restart();
    i2c_master_send(0x45); //chip address for read is 01000101
    unsigned char r = i2c_master_recv();
    i2c_master_ack(1);
    i2c_master_stop();
    return r;
}
 */