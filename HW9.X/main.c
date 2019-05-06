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
    
    unsigned short x, y;
    int z;
    int i = 0;
    int press = 0;
    int add = 0;
    unsigned short xpix, ypix;
    
    char xmessage[20];
    char ymessage[20];
    char zmessage[20];
    char xpixmessage[20];
    char ypixmessage[20];
    char iplusmessage[5];
    char iminusmessage[5];
    char imessage[10];
    char pressmessage[10];
    sprintf(iplusmessage, "i++");
    sprintf(iminusmessage, "i--");
    
    LCD_drawButton(120, 100, 90, 50, ILI9341_LIGHTGREY); /////i am here keep working from this point
    LCD_drawButton(120, 200, 90, 50, ILI9341_LIGHTGREY);
    
    LCD_drawString(iplusmessage, 155, 120, ILI9341_BLACK, ILI9341_LIGHTGREY);
    LCD_drawString(iminusmessage, 155, 220, ILI9341_BLACK, ILI9341_LIGHTGREY);
    
    while(1){
 
    XPT2046_read(&x, &y, &z);
    xpix = x/16;
    ypix = (4000-y)/12.5;
    
    if (z > 1000){
        press = 1;
        if ((xpix >  120) && (xpix < 210)){
                if ((ypix > 99) && (ypix < 151)){
                    add = 1;
                }
                if ((ypix > 199) && (ypix < 251)){
                    add = -1;
                } 
            }
            else{
                add = 0;
            }
    }
    if (z < 1000){
        if (press == 1){
           i = i + add; 
        }
        press = 0;
    }
    
    sprintf(pressmessage, "Press: %d", press);   
    sprintf(xmessage, "X is: %d   ", x);
    sprintf(ymessage, "Y is: %d   ", y);
    sprintf(zmessage, "Z is: %d   ", z);
    sprintf(imessage, "i: %d  ", i);
    
    LCD_drawString(xmessage, 30, 30, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(ymessage, 30, 50, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(zmessage, 30, 70, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(imessage, 125, 170, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(pressmessage, 30, 190, ILI9341_WHITE, ILI9341_PURPLE);

       
    sprintf(xpixmessage, "Xpix is: %d   ", xpix);
    sprintf(ypixmessage, "Ypix is: %d   ", ypix);
    LCD_drawString(xpixmessage, 30, 90, ILI9341_WHITE, ILI9341_PURPLE);
    LCD_drawString(ypixmessage, 30, 110, ILI9341_WHITE, ILI9341_PURPLE);
 
    }
}
   