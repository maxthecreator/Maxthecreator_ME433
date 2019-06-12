#include<xc.h>           // processor SFR definitions

#include<sys/attribs.h>  // __ISR macro

#include <stdio.h>
#include "ili2.h"
#include "imu.H"



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

#pragma config WDTPS = PS1048576 // use slowest wdt

#pragma config WINDIS = OFF // wdt no window mode

#pragma config FWDTEN = OFF // wdt disabled

#pragma config FWDTWINSZ = WINSZ_25 // wdt window at 25%



// DEVCFG2 - get the sysclk clock to 48MHz from the 8MHz crystal

#pragma config FPLLIDIV = DIV_2 // divide input clock to be in range 4-5MHz

#pragma config FPLLMUL = MUL_24 // multiply clock after FPLLIDIV

#pragma config FPLLODIV = DIV_2 // divide clock after FPLLMUL to get 48MHz

#pragma config UPLLIDIV = DIV_2 // divider for the 8MHz input clock, then multiplied by 12 to get 48MHz for USB

#pragma config UPLLEN = ON // USB clock on



// DEVCFG3

#pragma config USERID = 0 // some 16bit userid, doesn't matter what

#pragma config PMDL1WAY = ON // allow multiple reconfigurations

#pragma config IOL1WAY = ON // allow multiple reconfigurations

#pragma config FUSBIDIO = OFF // USB pins controlled by USB module

#pragma config FVBUSONIO = OFF // USB BUSON controlled by USB module



#define DIR1 LATAbits.LATA10

#define DIR2 LATAbits.LATA7

#define USER PORTBbits.RB4



void startup() {

    // set the CP0 CONFIG register to indicate that kseg0 is cacheable (0x3)

    __builtin_mtc0(_CP0_CONFIG, _CP0_CONFIG_SELECT, 0xa4210583);



    // 0 data RAM access wait states

    BMXCONbits.BMXWSDRM = 0x0;



    // enable multi vector interrupts

    INTCONbits.MVEC = 0x1;



    // disable JTAG to get pins back

    DDPCONbits.JTAGEN = 0;



    // do your TRIS and LAT commands here

    ANSELA = 0;

    ANSELB = 0;

    TRISAbits.TRISA7 = 0;

    DIR2 = 1;

    TRISAbits.TRISA10 = 0;

    DIR1 = 1;

    TRISBbits.TRISB4 = 1;

    
 

    T2CONbits.TCKPS = 0; // Timer2 prescaler N=1 (1:1)
    PR2 = 2399; // PR = PBCLK / N / desiredF - 1
    TMR2 = 0; // initial TMR2 count is 0
    OC1CONbits.OCM = 0b110; // PWM mode without fault pin; other OC1CON bits are defaults
    OC1RS = 600; // duty cycle
    OC1R = 0; // initialize before turning OC1 on; afterward it is read-only
    OC4CONbits.OCM = 0b110;
    OC4RS = 600;
    OC4R = 0;
    RPA4Rbits.RPA4R = 0b0101;
    RPB15Rbits.RPB15R = 0b0101;
    
   
    
    
    //Timer 3 for interrupt
    /*
    T3CONbits.TCKPS = 0b11; //was 0b01
    PR3 = 59999; //was 59999
    
    IEC0bits.T3IE = 1;
    //IECx, x=0, 1, or 2
    IFS0bits.T3IF = 1;
    // IFSx, x=0, 1, or 2
    IPC3bits.T3IP = 0b101;
    IPC3bits.T3IS = 0b1;
   */ T2CONbits.ON = 1; // turn on Timer2
    //T3CONbits.ON = 1;
    OC1CONbits.ON = 1; // turn on OC1
    OC4CONbits.ON = 1;

}



int main() {



    __builtin_disable_interrupts();



    startup();

   // SPI1_init();
   // LCD_init();
  
  
   // LCD_clearScreen(ILI9341_PURPLE);

    __builtin_enable_interrupts();

    

       

    while(1) {
        OC1RS = 300;
        OC4RS = 300;


        _CP0_SET_COUNT(0);

        while(_CP0_GET_COUNT()<48000000/2/2){

            while(USER == 0){}

        }

        DIR1 = 0;

        DIR2 = 1;

        

        _CP0_SET_COUNT(0);

        while(_CP0_GET_COUNT()<48000000/2/2){

            while(USER == 0){}

        }

        DIR1 = 1;

        DIR2 = 0;

    }

}