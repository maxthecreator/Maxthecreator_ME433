#include<xc.h>
#include<stdio.h>
#include "ili2.h"



void LCD_init() {

    int time = 0;

    

    CS = 0; // CS

   

    LCD_command(ILI9341_SWRESET);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 7200000) {} // 300ms



    LCD_command(0xEF);

  	LCD_data(0x03);

	LCD_data(0x80);

	LCD_data(0x02);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(0xCF);

  	LCD_data(0x00);

	LCD_data(0xC1);

	LCD_data(0x30);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(0xED);

  	LCD_data(0x64);

	LCD_data(0x03);

	LCD_data(0x12);

    LCD_data(0x81);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(0xE8);

  	LCD_data(0x85);

	LCD_data(0x00);

	LCD_data(0x78);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(0xCB);

  	LCD_data(0x39);

	LCD_data(0x2C);

	LCD_data(0x00);

    LCD_data(0x34);

    LCD_data(0x02);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(0xF7);

  	LCD_data(0x20);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(0xEA);

  	LCD_data(0x00);

	LCD_data(0x00);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_PWCTR1);

  	LCD_data(0x23);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_PWCTR2);

  	LCD_data(0x10);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_VMCTR1 );

  	LCD_data(0x3e);

    LCD_data(0x28);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_VMCTR2);

  	LCD_data(0x86);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_MADCTL);

  	LCD_data(0x48);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

/*    

    LCD_command(ILI9341_VSCRSADD);

  	LCD_data(0x00);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

 */   

    LCD_command(ILI9341_PIXFMT);

  	LCD_data(0x55);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_FRMCTR1);

  	LCD_data(0x00);

    LCD_data(0x18);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command( ILI9341_DFUNCTR);

  	LCD_data(0x08);

    LCD_data(0x82);

    LCD_data(0x27);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(0xF2);

  	LCD_data(0); // 1

    LCD_data(0x00);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_GAMMASET);

  	LCD_data(0x01);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_GMCTRP1);

  	LCD_data(0x0F);

    LCD_data(0x31);

    LCD_data(0x2B);

    LCD_data(0x0C);

    LCD_data(0x0E);

    LCD_data(0x08);

    LCD_data(0x4E);

    LCD_data(0xF1);

    LCD_data(0x37);

    LCD_data(0x07);

    LCD_data(0x10);

    LCD_data(0x03);

    LCD_data(0x0E);

    LCD_data(0x09);

    LCD_data(0x00);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_GMCTRN1);

  	LCD_data(0x00);

    LCD_data(0x0E);

    LCD_data(0x14);

    LCD_data(0x03);

    LCD_data(0x11);

    LCD_data(0x07);

    LCD_data(0x31);

    LCD_data(0xC1);

    LCD_data(0x48);

    LCD_data(0x08);

    LCD_data(0x0F);

    LCD_data(0x0C);

    LCD_data(0x31);

    LCD_data(0x36);

    LCD_data(0x0F);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(0xB1);

  	LCD_data(0x00);

    LCD_data(0x10);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_SLPOUT);

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    LCD_command(ILI9341_DISPON);

    

    CS = 1; // CS

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    

    CS = 0; // CS

    

    LCD_command(ILI9341_MADCTL);

    LCD_data(MADCTL_MX | MADCTL_BGR); // rotation

    time = _CP0_GET_COUNT();

    while (_CP0_GET_COUNT() < time + 3600000) {} // 150ms

    

    CS = 1; // CS

}



void SPI1_init() {

  SDI1Rbits.SDI1R = 0b0000; // A1 is SDI1

  RPA0Rbits.RPA0R = 0b0011; // A0 is SDO1

  TRISBbits.TRISB7 = 0; // CS is B7
  
  TRISBbits.TRISB9 = 0; // CS2 is B9

  CS = 1; // CS starts high

  CS2 = 1; // CS2 starts high

  // DC pin

  TRISBbits.TRISB15 = 0;

  DC = 1;

  

  SPI1CON = 0; // turn off the spi module and reset it

  SPI1BUF; // clear the rx buffer by reading from it

  SPI1BRG = 3;// changed from 0 // baud rate to 12 MHz [SPI1BRG = (48000000/(2*desired))-1]

  SPI1STATbits.SPIROV = 0; // clear the overflow bit

  SPI1CONbits.CKE = 1; // data changes when clock goes from hi to lo (since CKP is 0)

  SPI1CONbits.MSTEN = 1; // master operation

  SPI1CONbits.ON = 1; // turn on spi1

}



unsigned char spi_io(unsigned char o) {

  SPI1BUF = o;

  while(!SPI1STATbits.SPIRBF) { // wait to receive the byte

    ;

  }

  return SPI1BUF;

}



void LCD_command(unsigned char com) {

    DC = 0; // DC

    spi_io(com);

    DC = 1; // DC

}



void LCD_data(unsigned char dat) {

    spi_io(dat);

}



void LCD_data16(unsigned short dat) {

    spi_io(dat>>8);

    spi_io(dat);

}



void LCD_setAddr(unsigned short x, unsigned short y, unsigned short w, unsigned short h) {

    LCD_command(ILI9341_CASET); // Column

    LCD_data16(x);

	LCD_data16(x+w-1);



	LCD_command(ILI9341_PASET); // Page

	LCD_data16(y);

	LCD_data16(y+h-1);



	LCD_command(ILI9341_RAMWR); // Into RAM

}



void LCD_drawPixel(unsigned short x, unsigned short y, unsigned short color) {

  // check boundary

    

    CS = 0; // CS

    

    LCD_setAddr(x,y,1,1);

    LCD_data16(color);

    

    CS = 1; // CS

}



void LCD_clearScreen(unsigned short color) {

    int i;

    

    CS = 0; // CS

    

    LCD_setAddr(0,0,ILI9341_TFTWIDTH,ILI9341_TFTHEIGHT);

	for (i = 0;i < ILI9341_TFTWIDTH*ILI9341_TFTHEIGHT; i++){

		LCD_data16(color);

	}

    

    CS = 1; // CS

}
void LCD_drawLetter(char letter, unsigned short x, unsigned short y, unsigned short lettercolor, unsigned short bckcolor){
    int i, j;
    for(i=0; i<5; i++){
        for (j=0; j<8; j++){
    
            char bit = (ASCII[letter - 32][i] >> j) & 0b1;
            if (bit == 1){
                LCD_drawPixel(x+i, y+j, lettercolor);
            }
            else {
                LCD_drawPixel(x+i, y+j, bckcolor);
            }
        }
    }
}

void LCD_drawBar(unsigned short x, unsigned short y, unsigned short length, unsigned short percent, unsigned short barcolor, unsigned short bckcolor){
    int i, j;
    for (i = 0; i< length; i++){
        for (j=0; j<8; j++){
            if (i<(length*percent/100)){
                LCD_drawPixel(x+i, y+j, barcolor);
            }
            else{
                LCD_drawPixel(x+i, y+j, bckcolor);
            }
        }
    }
}

void LCD_drawString(char* message, unsigned short x, unsigned short y, unsigned short lettercolor, unsigned short bckcolor){
        
    int i;
    i = 0;
    while (message[i]){
        LCD_drawLetter(message[i], x+5*i, y, lettercolor, bckcolor);
        i++;
    }
}
void LCD_drawBarLeft(unsigned short x, unsigned short y, unsigned short length, unsigned short percent, unsigned short barcolor, unsigned short bckcolor){
    int i, j;
    for (i = 0; i< length; i++){
        for (j=0; j<8; j++){
            if (i<(length*percent/100)){
                LCD_drawPixel(x-i, y+j, barcolor);
            }
            else{
                LCD_drawPixel(x-i, y+j, bckcolor);
            }
        }
    }
}

void LCD_drawBarUp(unsigned short x, unsigned short y, unsigned short length, unsigned short percent, unsigned short barcolor, unsigned short bckcolor){
    int i, j;
    for (i = 0; i< length; i++){
        for (j=0; j<8; j++){
            if (i<(length*percent/100)){
                LCD_drawPixel(x+j, y-i, barcolor);
            }
            else{
                LCD_drawPixel(x+j, y-i, bckcolor);
            }
        }
    }
}
void LCD_drawBarDown(unsigned short x, unsigned short y, unsigned short length, unsigned short percent, unsigned short barcolor, unsigned short bckcolor){
    int i, j;
    for (i = 0; i< length; i++){
        for (j=0; j<8; j++){
            if (i<(length*percent/100)){
                LCD_drawPixel(x+j, y+i, barcolor);
            }
            else{
                LCD_drawPixel(x+j, y+i, bckcolor);
            }
        }
    }
}

void XPT2046_read(unsigned short *x, unsigned short *y, unsigned int *z){
    unsigned char c, d, e, f;
 
    CS2 = 0;
    spi_io(0b10010001); //read y
    c = spi_io(0x00);
    d = spi_io(0x00);
    
    *y = (c << 5) | (d >> 3);
        
    CS2 = 1;
    CS2 = 0;  
    
    spi_io(0b11010001); //read x
    c = spi_io(0x00);
    d = spi_io(0x00);       
    *x = (c << 5) | (d >> 3);
    
    CS2 = 1;
    CS2 = 0;  
    
    spi_io(0b10110001); //read z1
    c = spi_io(0x00);
    d = spi_io(0x00);   

    CS2 = 1;
    CS2 = 0;      
   
    spi_io(0b11000001); //read z2
    e = spi_io(0x00);
    f = spi_io(0x00);     
    
    *z = ((c << 5) | (d >> 3)) - ((e << 5) | (f >> 3)) + 4095;
    
    CS2 = 1;
    
}


void LCD_drawButton(unsigned short x, unsigned short y, unsigned short width, unsigned short height, unsigned short barcolor){
    int i, j;
    for (i = 0; i< height; i++){
        for (j=0; j<width; j++){
            LCD_drawPixel(x+j, y+i, barcolor);
          
        }
    }
}
void LCD_plotArray(char* array, unsigned short x, unsigned short y, unsigned short color, int arraylength){
    int i = 0;
    unsigned char temp;
    for (i = 0; i < arraylength; i++){
        temp = array[i];
        temp = temp >> 5;
        LCD_drawPixel(x + i, y - temp*2, color);
    }
}
