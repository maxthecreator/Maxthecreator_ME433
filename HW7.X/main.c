#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <math.h> 
#include<stdio.h>
#include "imu.H"
#include "ili2.h"



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
 
   SPI1_init();
    LCD_init();
  
    
    LCD_clearScreen(ILI9341_PURPLE);
    
    imusetup();
 
 
 char xaccmessage[20];
 char yaccmessage[20];
 char zaccmessage[20];
 char xrotmessage[20];
 char yrotmessage[20];
 char zrotmessage[20];

 
 char c;
 
 int arlength = 14;
 unsigned char array[14];
         
 while(1){
    c = whoami();
    if (c == 0x69){
         LATAINV = 0x16;
    }
    
    I2C_read_multiple(imuadd, readreg, array, arlength);
 
    short xacc, yacc, zacc, temp, xrot, yrot, zrot;
    temp = (array[1] << 8) | array[0];
    xrot = (array[3] << 8) | array[2];
    yrot = (array[5] << 8) | array[4];
    zrot = (array[7] << 8) | array[6];
    xacc = (array[9] << 8) | array[8];
    yacc = (array[11] << 8) | array[10];
    zacc = (array[13] << 8) | array[12];
 
    sprintf(xaccmessage, "Xacc is:%d  ", xacc);
    sprintf(yaccmessage, "Yacc is:%d  ", yacc);
    sprintf(yaccmessage, "Zacc is:%d  ", zacc);
    sprintf(yaccmessage, "Xrot is:%d  ", xrot);
    sprintf(yaccmessage, "Yrot is:%d  ", yrot);
    sprintf(yaccmessage, "Zrot is:%d  ", zrot);
    
    LCD_drawString(xaccmessage, 30, 30, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(yaccmessage, 30, 50, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(zaccmessage, 30, 70, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(xrotmessage, 30, 90, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(yrotmessage, 30, 110, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(zrotmessage, 30, 130, ILI9341_WHITE, ILI9341_PURPLE);
    
 
    while (_CP0_GET_COUNT() <= 1200000) {
    }
    _CP0_SET_COUNT(0);
 
    }
   
}