/**************************************************************************************************/

/*
 * File: keypad.c
 * Team: Lambda^3
 * Members: Chris Houseman
 *          Randy Martinez
 *          Rachel Powers
 *          Chris Sanford
 *
 * Date: October 17, 2014
 *
 * Description: Code that defines keypad functions
 *
 */

/*
 * Row0 = Out2 => Pin2 = RB12
 * Row1 = Out7 => Pin3 = RB13
 * Row2 = Out6 => Pin9 = RB14
 * Row3 = Out4 => Pin10 = RB15
 * Col0 = In3 => Pin6 = RB2 = CN6
 * Col1 = In1 => Pin7 = RB3 = CN7
 * Col2 = In5 => Pin22 = RB11 = CN15
 */

// ******************************************************************************************* //
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "keypad.h"
#include "lcd.h"

// ******************************************************************************************* //

void KeypadInitialize()
{
	//set rows

	//Row 0
	TRISBbits.TRISB12 = 0;	//enable as output
	AD1PCFGbits.PCFG12 = 1;
	LATBbits.LATB12 = 0;
	ODCBbits.ODB12 = 1;  //enable open drain

	//Row 1
	TRISBbits.TRISB13 =0;
	AD1PCFGbits.PCFG11 = 1;
	LATBbits.LATB13 = 0;
	ODCBbits.ODB13 = 1;  //enable open drain

	//Row 2
	TRISBbits.TRISB14 = 0;
        AD1PCFGbits.PCFG10 = 1;
	LATBbits.LATB14 = 0;
	ODCBbits.ODB14 = 1;  //enable open drain

	//Row 3
	TRISBbits.TRISB15 =0;
        AD1PCFGbits.PCFG9 = 1;
	LATBbits.LATB15 = 0;
	ODCBbits.ODB15 = 1;  //enable open drain

// ******************************************************************************************* //
//	//configure RB5 pullup resistors
//	//column 2
        //configure RB11 as input
        TRISBbits.TRISB11 =1; //set input
    	CNPU1bits.CN15PUE = 1;
        CNEN1bits.CN15IE = 1;

	//configure RB3 pull up resistors
	//column 1
	TRISBbits.TRISB3 =1;
	CNPU1bits.CN7PUE = 1;
	CNEN1bits.CN7IE =1;
	AD1PCFGbits.PCFG5 = 1;



	//configure RB2 pull up resistors
	//column 0
	TRISBbits.TRISB2 =1 ; //enable as an input
	CNPU1bits.CN6PUE = 1 ;
	CNEN1bits.CN6IE = 1;
	AD1PCFGbits.PCFG4 = 1;

        IEC1bits.CNIE = 1;
        IFS1bits.CNIF = 0;



}

// ******************************************************************************************* //

    void DelayUs(unsigned int usDelay);


char KeypadScan() {

    int i = 0; //i is the index for the for loop
    int toggle = 0; //toggle rotates through rows while setting them to 0
    int keyDetect = 0;  //counts the number of keys detected
    char key = -1;

    //This loop runs through and sets each row individually to 1 while checking column inputs to determine which key is pressed
    for (i = 0; i < 4; i++){
        LATB |= 0xF000;  //Make sure all outputs to rows begin as 1
        
        toggle = 0xEFFF;  //begin with toggle = 1110 1111 1111 1111

        toggle = toggle << i;  //shift the 0 over by i
        toggle |= 0x0001; //replace the shifted in 0 with a 1 on toggle
        LATB &= toggle; //clear the selected bit in LATB, allowing one row to go to 0 (row0 --> row3)
        
        DelayUs(50);
        
        if (PORTBbits.RB11 == 0) {
            if (i == 3){
                key = '#';
                keyDetect++;
            }
            if (i == 2){
                key = '9';
                keyDetect++;
            }
            if (i == 1){
                key = '6';
                keyDetect++;
            }
            if (i == 0){
                key = '3';
                keyDetect++;
            }
        }

        if (PORTBbits.RB3 == 0){
            if (i == 3){
                key = '0';
                keyDetect++;
            }
            if (i == 2){
                key = '8';
                keyDetect++;
            }
            if (i == 1){
                key = '5';
                keyDetect++;
            }
            if (i == 0){
                key = '2';
                keyDetect++;
            }
        }

        if (PORTBbits.RB2 == 0){
            if (i == 3){
                key = '*';
                keyDetect++;
            }
            if (i == 2){
                key = '7';
                keyDetect++;
            }
            if (i == 1){
                key = '4';
                keyDetect++;
            }
            if (i == 0){
                key = '1';
                keyDetect++;
            }
        }
    
    }
    LATB = LATB & 0x0FFF;  //reset rows to all 0
    KeypadInitialize();
    if (keyDetect > 1) { //check if more than one key is pressed and return special character if so
        LCDMoveCursor(1,0);
        LCDPrintString("No!");
        LCDMoveCursor(0,0);
        keyDetect=0;
        key=-1;
        return key; //returns key found
    }

    else if (keyDetect == 1) { //check if no key is pressed
        keyDetect=0;
        return key;
    }
    else {
        key=-1;
        keyDetect=0;
        return key;
    }
    

}


        // End Added Code
	


// ******************************************************************************************* //
