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
 * Row0 = Out3 => Pin2 = RA0 = //CN2
 * Row1 = Out7 => Pin3 = RA1 = //CN3
 * Row2 = Out6 => Pin9 = RA2 = //CN30
 * Row3 = Out4 => Pin10 = RA3 = //CN29
 * Col0 = In3 => Pin6 = RB2 = CN6
 * Col1 = In1 => Pin7 = RB3 = CN7
 * Col2 = In5 => Pin14 = RB5 = CN27
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
	//AD1PCFGbits.PCFG = 1;
	LATAbits.LATA1 = 0;
	ODCAbits.ODA1 = 1;  //enable open drain

	//Row 2
	TRISAbits.TRISA2 = 0;
	//AD1PCFGbits.PCFG = 1;
	LATAbits.LATA2 = 0;
	ODCAbits.ODA2 = 1;  //enable open drain

	//Row 3
	TRISAbits.TRISA3 =0;
	//AD1PCFGbits.PCFG = 1;
	LATAbits.LATA3 = 0;
	ODCAbits.ODA3 = 1;  //enable open drain

// ******************************************************************************************* //
	//configure RB5 pullup resistors
	//column 2
	CNPU2bits.CN27PUE = 1;
	TRISBbits.TRISB5 =1; //set input
	//IFS1bits.CNIF = 0;
	CNEN2bits.CN27IE = 1;


	//configure RB3 pull up resistors
	//column 1
	CNPU1bits.CN7PUE = 1;
	TRISBbits.TRISB3 =1;
	//IFS1bits.CNIF = 0;
	CNEN1bits.CN7IE =1;
	IEC1bits.CNIE = 1;
	AD1PCFGbits.PCFG5 = 1;



	//configure RB2 pull up resistors
	//column 0
	CNPU1bits.CN6PUE = 1 ;
	TRISBbits.TRISB2 =1 ; //enable as an input
	IFS1bits.CNIF = 0;
	CNEN1bits.CN6IE = 1;
	IEC1bits.CNIE = 1;
	AD1PCFGbits.PCFG4 = 1;

        IEC1bits.CNIE = 1;
        IFS1bits.CNIF = 0;



}

// ******************************************************************************************* //

    void DelayUs(unsigned int usDelay);


char KeypadScan() {

//	char key = -1;
//
//
//	// TODO: Implement the keypad scanning procedure to detect if exactly one button of the
//	// keypad is pressed. The function should return:
//	//
//	//      -1         : Return -1 if no keys are pressed.
//	//      '0' - '9'  : Return the ASCII character '0' to '9' if one of the
//	//                   numeric (0 - 9) keys are pressed.
//	//      '#'        : Return the ASCII character '#' if the # key is pressed.
//	//      '*'        : Return the ASCII character '*' if the * key is pressed.
//	//       -1        : Return -1 if more than one key is pressed simultaneously.
//	// Notes:
//	//        1. Only valid inputs should be allowed by the user such that all invalid inputs
//	//           are ignored until a valid input is detected.
//	//        2. The user must release all keys of the keypad before the following key press
//	//           is processed. This is to prevent invalid keypress from being processed if the
//	//           users presses multiple keys simultaneously.
//	//
//
//        // Begin Added Code
//        //while(key == -1);
//
//        int button = 0;
//
//
//        if(LATAbits.LATA1 == 0 && LATBbits.LATB3 == 0)  // if this input and output are set, print 1
//        {
//            key = '1';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATAbits.LATA0 == 0 && LATBbits.LATB3 == 0)  // if this input and output are set, print 2
//        {
//            key = '2';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATBbits.LATB2 == 0 && LATBbits.LATB3 == 0)  // if this input and output are set, print 3
//        {
//            key = '3';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATAbits.LATA1 == 0 && LATBbits.LATB11 == 0)  // if this input and output are set, print 4
//        {
//            key = '4';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATAbits.LATA0 == 0 && LATBbits.LATB11 == 0)  // if this input and output are set, print 5
//        {
//            key = '5';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATBbits.LATB2 == 0 && LATBbits.LATB11 == 0)  // if this input and output are set, print 6
//        {
//            key = '6';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATAbits.LATA1 == 0 && LATAbits.LATA3 == 0)  // if this input and output are set, print 7
//        {
//            key = '7';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATAbits.LATA0 == 0 && LATAbits.LATA3 == 0)  // if this input and output are set, print 8
//        {
//            key = '8';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATBbits.LATB2 == 0 && LATAbits.LATA3 == 0)  // if this input and output are set, print 9
//        {
//            key = '9';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATAbits.LATA1 == 0 && LATAbits.LATA2 == 0)  // if this input and output are set, print *
//        {
//            key = '*';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATAbits.LATA0 == 0 && LATAbits.LATA2 == 0)  // if this input and output are set, print 0
//        {
//            key = '0';
//            button++;   // adds 1 to the value of button
//        }
//
//        if(LATBbits.LATB2 == 0 && LATAbits.LATA2 == 0)  // if this input and output are set, print #
//
//        {
//            key = '#';
//            button++;   // adds 1 to the value of button
//        }
//
//        if (button == 1)    // if the button value is set to one
//        {
//            return key;     // return the value of key
//        }
//        else
//        {
//            return -1;      // otherwise, if more than one button is pressed or no buttons are pressed, return -1
//        }


//Begin Added Code

        int i = 0; //i is the index for the for loop
    int toggle = 0; //toggle rotates through rows while setting them to 0
    int keyDetect = 0;  //counts the number of keys detected
    char key = -1;

//    IEC1bits.CNIE = 0;





    //This loop runs through and sets each row individually to 1 while checking column inputs to determine which key is pressed
    for (i = 0; i < 4; i++){
        //LATB |= 0xF000;  //Make sure all outputs to rows begin as 1
        LATA &= 0xFFF0;  //Make sure all outputs to rows begin as 1
        toggle = 0xFFF7;  //begin with toggle = 1111 1111 1111 0111

        toggle = toggle >> i;  //shift the 0 over by i
        toggle |= 0x8000; //replace the shifted in 0 with a 1 on toggle
        //LATB &= toggle; //clear the selected bit in LATB, allowing one row to go to 0 (row0 --> row3)
        LATA &= toggle; //clear the selected bit in LATA, allowing one row to go to 0 (row0 --> row3)
        DelayUs(1);


        if (PORTBbits.RB5 == 0) {
            if (i == 0){
                key = '1';
                keyDetect++;
            }
            else if (i == 1){
                key = '4';
                keyDetect++;
            }
            else if (i == 2){
                key = '7';
                keyDetect++;
            }
            else if (i == 3){
                key = '*';
                keyDetect++;
            }
        }

        if (PORTBbits.RB3 == 0){
            if (i == 0){
                key = '2';
                keyDetect++;
            }
            else if (i == 1){
                key = '5';
                keyDetect++;
            }
            else if (i == 2){
                key = '8';
                keyDetect++;
            }
            else if (i == 3){
                key = '0';
                keyDetect++;
            }
        }

        if (PORTBbits.RB2 == 0){
            if (i == 0){
                key = '3';
                keyDetect++;
            }
            else if (i == 1){
                key = '6';
                keyDetect++;
            }
            else if (i == 2){
                key = '9';
                keyDetect++;
            }
            else if (i == 3){
                key = '#';
                keyDetect++;
            }
        }
    }

    if (keyDetect == 1) { //check if more than one key is pressed and return special character if so
    return key;
    }

    else { //check if no key is pressed

        key=-1;
    }
    //LATB = LATB & 0x0FFF;  //reset rows to all 0
    LATA = LATA & 0xFFF0;  //reset rows to all 0


// do we need to reset anything else? (i.e. flags, etc)


    return key; //returns key found

}


        // End Added Code
	


// ******************************************************************************************* //
