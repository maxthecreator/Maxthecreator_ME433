#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <math.h> 

// DEVCFG0
#pragma config DEBUG = OFF // no debugging
#pragma config JTAGEN = OFF // no jtag
#pragma config ICESEL = ICS_PGx1 // use PGED1 and PGEC1
#pragma config PWP = OFF // no write protect
#pragma config BWP = OFF // no boot write protect
#pragma config CP = OFF // no code protect

// DEVCFG1
#pragma config FNOSC = PRIPLL // use primary oscillator with pll
#pragma config FSOSCEN = OFF // turn off secondary oscillator
#pragma config IESO = OFF // no switching clocks
#pragma config POSCMOD = HS // high speed crystal mode
#pragma config OSCIOFNC = OFF // disable secondary osc
#pragma config FPBDIV = DIV_1 // divide sysclk freq by 1 for peripheral bus clock
#pragma config FCKSM = CSDCMD // do not enable clock switch
#pragma config WDTPS = PS1 // use slowest wdt
#pragma config WINDIS = OFF // wdt no window mode
#pragma config FWDTEN = OFF // wdt disabled
#pragma config FWDTWINSZ = WINSZ_25 // wdt  window at 25%

// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal
#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz
#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV
#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz
#pragma config UPLLIDIV = DIV_2 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB
#pragma config UPLLEN = ON // USB clock on

// DEVCFG3
#pragma config USERID = 0x0013 // some 16bit userid, doesn't matter what
#pragma config PMDL1WAY = OFF // allow multiple reconfigurations
#pragma config IOL1WAY = OFF // allow multiple reconfigurations
#pragma config FUSBIDIO = ON // USB pins controlled by USB module
#pragma config FVBUSONIO = ON // USB BUSON controlled by USB module

void initExpander(void);
void setExpander(char pin, char level);
unsigned char getExpander(void);


int main() {
    __builtin_disable_interrupts();
    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)
    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);
    // 0 data RAM access wait states
    BMXCONbits.BMXWSDRM = 0x0;
    // enable multi vector interrupts
    INTCONbits.MVEC = 0x1;
    // disable JTAG to get pins back
    DDPCONbits.JTAGEN = 0;
    // do your TRIS and LAT commands here
    // tris is i/o
            //lat is hi-low for output
            //port reads hi-lo for input
    TRISAbits.TRISA4 = 0;
    TRISBbits.TRISB4 = 1;
    LATAbits.LATA4 = 1;
   
    
    
 __builtin_enable_interrupts();
 
 initExpander();
 
 while(1){
    
 if (_CP0_GET_COUNT() > 12000000){ // flip twice every 1/1000 of a sec
 LATAINV = 0x16;  
 _CP0_SET_COUNT(0);
 }
 
 
 if (getExpander() == 0){ //128 would be hi
     setExpander(0, 1);
 }
 else{
     setExpander(0,0);
 }
 
 
 
 

}
}

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

void initExpander(void){
    i2c_master_setup();
    i2c_master_start();
    i2c_master_send(0x44);
    i2c_master_send(0x00);//iodir
    i2c_master_send(0xf0);//gp0-3 are outputs, 4-7 are inputs
    i2c_master_stop();
}

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