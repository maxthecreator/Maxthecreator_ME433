#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include "NU32.h"       // constants, funcs for startup and UART
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

#pragma config WDTPS = PS1 // use slowest wdt ****************************************************************

#pragma config WINDIS = OFF // wdt no window mode

#pragma config FWDTEN = OFF // wdt disabled

#pragma config FWDTWINSZ = WINSZ_25// wdt window at 25%



// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal

#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz

#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV

#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz

#pragma config UPLLIDIV = DIV_1 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB

#pragma config UPLLEN = ON // USB clock on



// DEVCFG3

#pragma config USERID = 0b0000000000000013 // some 16bit userid, doesn't matter what

#pragma config PMDL1WAY = OFF // allow multiple reconfigurations

#pragma config IOL1WAY = OFF // allow multiple reconfigurations

#pragma config FUSBIDIO = ON // USB pins controlled by USB module

#pragma config FVBUSONIO = ON // USB BUSON controlled by USB module





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
  
// SDO4 -> SI (pin F5 -> pin 5)
    RPB2Rbits.RPB2R = 0b0011;  //SETS RPB2 (PIN 6) TO SDO1
// SDI4 -> SO (pin F4 -> pin 2)
    SDI1Rbits.SDI1R = 0b0000; //SETS SDI1 TO RPA1 (PIN 3)
// SCK4 -> SCK (pin B14 -> pin 6)   DONE
// SS4 -> CS (pin B8 -> pin 1)      DONE
    TRISBbits.TRISB8 = 0;      
// Additional SRAM connections
// Vss (Pin 4) -> ground            DONE
// Vcc (Pin 8) -> 3.3 V             DONE   
// Hold (pin 7) -> 3.3 V (we don't use the hold function)       DONE

  #define CS LATBbits.LATB8       // chip select pin
  
  CS = 1;
  SPI1CON = 0;              // turn off the spi module and reset it
  SPI1BUF;                  // clear the rx buffer by reading from it
  SPI1BRG = 0x3;            // baud rate to 10 MHz [SPI4BRG = (80000000/(2*desired))-1]
  SPI1STATbits.SPIROV = 0;  // clear the overflow bit
  SPI1CONbits.CKE = 1;      // data changes when clock goes from hi to lo (since CKP is 0)
  SPI1CONbits.MSTEN = 1;    // master operation
  SPI1CONbits.ON = 1;       // turn on spi 4
  CS = 0;                   // enable the ram
  spi_io(0x01);             // ram write status
  spi_io(0x41);             // sequential mode (mode = 0b01), hold disabled (hold = 0)
  CS = 1;                   // finish the command
  while(1) {

	_CPO_SET_COUNT(0);

	float f = 512 +512*sin(i*2*3.1415/1000*10);  //should make a 10Hz sin wave)
	i++;
	setVoltage(0,512);		//test

	setVoltage(1,256);		//test

	while(_CPO_GET_COUNT() < 2400000000/1000) {}  //check this is 24Million
    ;
    return 0;
}

//-----------------------------------------------------------------------
unsigned char spi_io(unsigned char o) {

  SPI2BUF = o;

  while(!SPI2STATbits.SPIRBF) { // wait to receive the byte
    ;
  }
  return SPI2BUF;
}
//-----------------------------------------------------------------------


 


                            // send a ram set status command.



// write len bytes to the ram, starting at the address addr

	init_spi();





}


void setVoltage(char a, int v) {



	unsigned short t1 = 0;
    unsigned short t2 = 0;
   

	t1 = a << 15; //a is at the very end of the data transfer

	t1 = t1 | 0b01110000;

	t1 = t1 | ((v&0b111111111111) >> 8); //rejecting excessive bits (above 12)

    t2 = v & 0b0000000011111111;
	

	CS = 0;

	spi_io(t1);

	spi_

	

}
    
    
    __builtin_enable_interrupts();

   // a4 led 
   // b4 pushbutton
/*
    while(1) {
        
         
            while (_CP0_GET_COUNT() <= 24000){ // flip twice every 1/1000 of a sec
            }
            if (PORTBbits.RB4 == 1){//high
                LATAINV = 0x8;
                _CP0_SET_COUNT(0);
            }
        

	// remember the core timer runs at half the sysclk

    }
*/
