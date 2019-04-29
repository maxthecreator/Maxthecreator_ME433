/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    TRISAbits.TRISA4 = 0;
    TRISBbits.TRISB4 = 1;
    LATAbits.LATA4 = 1;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
       
        
            if (appInitialized)
            {
            
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
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
            unsigned short percent1, percent2, percent3, percent4;
         
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
            sprintf(zaccmessage, "Zacc is:%d  ", zacc);
            sprintf(xrotmessage, "Xrot is:%d  ", xrot);
            sprintf(yrotmessage, "Yrot is:%d  ", yrot);
            sprintf(zrotmessage, "Zrot is:%d  ", zrot);

            LCD_drawString(xaccmessage, 30, 30, ILI9341_WHITE, ILI9341_PURPLE);
            LCD_drawString(yaccmessage, 30, 50, ILI9341_WHITE, ILI9341_PURPLE);
            LCD_drawString(zaccmessage, 30, 70, ILI9341_WHITE, ILI9341_PURPLE);
            LCD_drawString(xrotmessage, 30, 90, ILI9341_WHITE, ILI9341_PURPLE);
            LCD_drawString(yrotmessage, 30, 110, ILI9341_WHITE, ILI9341_PURPLE);
            LCD_drawString(zrotmessage, 30, 130, ILI9341_WHITE, ILI9341_PURPLE);

            percent1 = 0;
            percent2 = 0;
            percent3 = 0;
            percent4 = 0;

            if (xacc>0){
                percent1 = xacc/160;
            }
            else{
                percent2 = -xacc/160;
            }
            if (yacc>0){
                percent3 = yacc/160;
            }
            else{
                percent4 = -yacc/160;
            }
    
      
            LCD_drawBar(110, 160, 80, percent2, ILI9341_BLACK, ILI9341_WHITE);
            LCD_drawBarLeft(101, 160, 80, percent1, ILI9341_BLACK, ILI9341_WHITE);
            LCD_drawBarUp(102, 159, 80, percent3, ILI9341_BLACK, ILI9341_WHITE);
            LCD_drawBarDown(102, 168, 80, percent4, ILI9341_BLACK, ILI9341_WHITE);
            LCD_drawBar(102, 160, 8, 100, ILI9341_BLACK, ILI9341_WHITE);
    
            while (_CP0_GET_COUNT() <= 1200000) {
            }
            _CP0_SET_COUNT(0);
        }
        }

        /* TODO: implement your application state machine.*/
        

        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
