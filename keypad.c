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
 * Row0 = Out2 => Pin2 = RA0 = //CN2
 * Row1 = Out7 => Pin3 = RA1 = //CN3
 * Row2 = Out6 => Pin9 = RA2 = //CN30
 * Row3 = Out4 => Pin10 = RA3 = //CN29
 * Col0 = In3 => Pin6 = RB2 = CN6
 * Col1 = In1 => Pin7 = RB3 = CN7
 * Col2 = In5 => Pin22 = RB11 = CN27
 */

// ******************************************************************************************* //
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "keypad.h"
#include "lcd.h"

// ******************************************************************************************* //

//void KeypadInitialize() {
//
//	// TODO: Configure IOs and Change Notification interrupt for keypad scanning. This
//	// configuration should ensure that if any key is pressed, a change notification interrupt
//	// will be generated.
//    //set columns INPUTS
//    //configure RA0 pull up resistor
//
//    // column 0
//    CNPU1bits.CN2PUE = 1;
//    TRISAbits.TRISA0 = 1; //set input
//    AD1PCFGbits.PCFG0  = 1; // sets as digital input
//    CNEN1bits.CN2IE = 1;
//
//    // column 1
//    CNPU1bits.CN3PUE = 1;
//    TRISAbits.TRISA1 = 1; //set input
//    AD1PCFGbits.PCFG1  = 1; //sets as digital input
//    CNEN1bits.CN2IE = 1;
//
//    // column 2
//    CNPU1bits.CN6PUE = 1;
//    TRISBbits.TRISB2 = 1; //set input
//    AD1PCFGbits.PCFG4  = 1; //sets as digital input
//    CNEN1bits.CN2IE = 1;
//
//    //Enable Interrupts
//    IFS1bits.CNIF = 0;
//    IEC1bits.CNIE = 1;
//
//    // ******************************************************************************************* //
//
//    //set rows OUTPUTS
//
//    //Row 0
//    TRISBbits.TRISB3 = 0;	//enable as output
//    LATBbits.LATB3 = 0;
//    ODCBbits.ODB3 = 1;  //enable open drain
//
//    //Row 1
//    TRISAbits.TRISA2 = 0;	//enable as output
//    LATAbits.LATA2 = 0;
//    ODCAbits.ODA2 = 1;  //enable open drain
//
//    //Row 2
//    TRISAbits.TRISA3 = 0;	//enable as output
//    LATAbits.LATA3 = 0;
//    ODCAbits.ODA3 = 1;  //enable open drain
//
//    //Row 3
//    TRISBbits.TRISB11 = 0;	//enable as output
//    LATBbits.LATB11 = 0;
//    ODCBbits.ODB11 = 1;  //enable open drain
//
//
//}

void KeypadInitialize()
{
	//set rows

	//Row 0
	TRISAbits.TRISA0 = 0;	//enable as output
	AD1PCFGbits.PCFG0 = 1;
	LATAbits.LATA0 = 0;
	ODCAbits.ODA0 = 1;  //enable open drain

	//Row 1
	TRISAbits.TRISA1 =0;
	AD1PCFGbits.PCFG1 = 1;
	LATAbits.LATA1 = 0;
	ODCAbits.ODA1 = 1;  //enable open drain

	//Row 2
	TRISAbits.TRISA2 = 0;
	LATAbits.LATA2 = 0;
	ODCAbits.ODA2 = 1;  //enable open drain

	//Row 3
	TRISAbits.TRISA3 =0;
	LATAbits.LATA3 = 0;
	ODCAbits.ODA3 = 1;  //enable open drain

// ******************************************************************************************* //
//	//configure RB5 pullup resistors
//	//column 2
//	TRISBbits.TRISB5 =1; //set input
//	CNPU2bits.CN27PUE = 1;
//	CNEN2bits.CN27IE = 1;
//
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
        //LATB |= 0xF000;  //Make sure all outputs to rows begin as 1
        LATA |= 0x000F;  //Make sure all outputs to rows begin as 1
        toggle = 0xFFF7;  //begin with toggle = 1111 1111 1111 0111

        toggle = toggle >> i;  //shift the 0 over by i
        toggle |= 0x8000; //replace the shifted in 0 with a 1 on toggle
        //LATB &= toggle; //clear the selected bit in LATB, allowing one row to go to 0 (row0 --> row3)
        LATA &= toggle; //clear the selected bit in LATA, allowing one row to go to 0 (row0 --> row3)
        DelayUs(1);


        if (PORTBbits.RB11 == 0) {
            if (i == 0){
                LCDMoveCursor(0,0);
                LCDPrintChar(i);
                LCDMoveCursor(0,0);
                key = '#';
                //key = '1';
                keyDetect++;
            }
            else if (i == 1){
                LCDMoveCursor(0,2);
                LCDPrintChar(i);
                LCDMoveCursor(0,0);
                key = '9';
                //key = '4';
                keyDetect++;
            }
            else if (i == 2){
                LCDMoveCursor(0,3);
                LCDPrintChar(i);
                LCDMoveCursor(0,0);
                key = '6';
                //key = '7';
                keyDetect++;
            }
            else if (i == 3){
                LCDMoveCursor(0,4);
                LCDPrintChar(i);
                LCDMoveCursor(0,0);
                key = '3'
                //key = '*';
                keyDetect++;
            }
        }

        if (PORTBbits.RB3 == 0){
            if (i == 0){
                key = '0';
                //key = '2';
                keyDetect++;
            }
            else if (i == 1){
                key = '8';
                //key = '5';
                keyDetect++;
            }
            else if (i == 2){
                key = '5';
                //key = '8';
                keyDetect++;
            }
            else if (i == 3){
                key = '2';
                //key = '0';
                keyDetect++;
            }
        }

        if (PORTBbits.RB2 == 0){
            if (i == 0){
                key = '*';
                //key = '3';
                keyDetect++;
            }
            else if (i == 1){
                key = '7';
                //key = '6';
                keyDetect++;
            }
            else if (i == 2){
                key = '4';
                //key = '9';
                keyDetect++;
            }
            else if (i == 3){
                key = '1';
                //key = '#';
                keyDetect++;
            }
        }
        LATA = LATA & 0xFFF0;  //reset rows to all 0
    }

    if (keyDetect > 1) { //check if more than one key is pressed and return special character if so
        LCDMoveCursor(1,0);
        LCDPrintString("s");
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
    //LATB = LATB & 0x0FFF;  //reset rows to all 0
    


// do we need to reset anything else? (i.e. flags, etc)




}


        // End Added Code
	


// ******************************************************************************************* //
