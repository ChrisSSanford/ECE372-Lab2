/**************************************************************************************************/

/*
 * File: keypad.c
 * Team: Lambda^3
 * Members: Chris Houseman
 *          Randy Martinez
 *          Rachel Powers
 *          Chris Sanford
 *
 * Date: October 6, 2014
 *
 * Description: Code that defines keypad functions
 *
 */

/*
 * Pin2 = In1 = RA0 = CN2
 * Pin3 = In3 = RA1 = CN3
 * Pin6 = In5 = RB2 = CN6
 * Pin7 = Out2 = RB3 = //CN7
 * Pin9 = Out4 = RA2 = //CN30
 * Pin10 = Out6 = RA3 = //CN29
 * Pin22 = Out7 = RB11 = //CN15
 */

// ******************************************************************************************* //
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "keypad.h"

// ******************************************************************************************* //

void KeypadInitialize() {
	
	// TODO: Configure IOs and Change Notification interrupt for keypad scanning. This
	// configuration should ensure that if any key is pressed, a change notification interrupt 
	// will be generated.
    //set columns INPUTS
    //configure RA0 pull up resistor
    
    // column 0
    CNPU1bits.CN2PUE = 1;
    TRISAbits.TRISA0 = 1; //set input
    AD1PCFGbits.PCFG/*missing*/  = 0; // sets as digital input
    CNEN1bits.CN2IE = 1;
    
    // column 1
    CNPU1bits.CN3PUE = 1;
    TRISAbits.TRISA1 = 1; //set input
    AD1PCFGbits.PCFG/*missing*/  = 0; //sets as digital input
    CNEN1bits.CN2IE = 1;
    
    // column 2
    CNPU1bits.CN6PUE = 1;
    TRISBbits.TRISB2 = 1; //set input
    AD1PCFGbits.PCFG/*missing*/  = 0; //sets as digital input
    CNEN1bits.CN2IE = 1;
    
    //Enable Interrupts
    IFS1bits.CNIF = 0;
    IEC1bits.CNIE = 1;
    
    // ******************************************************************************************* //
    
    //set rows OUTPUTS
    
    //Row 0
    TRISBbits.TRISB3 = 0;	//enable as output
    LATBbits.LATB3 = 0;
    ODCBbits.ODB3 = 1;  //enable open drain
    
    //Row 1
    TRISAbits.TRISA2 = 0;	//enable as output
    LATAbits.LATA2 = 0;
    ODCAbits.ODA2 = 1;  //enable open drain
    
    //Row 2
    TRISBbits.TRISA3 = 0;	//enable as output
    LATAbits.LATA3 = 0;
    ODCAbits.ODA3 = 1;  //enable open drain
    
    //Row 3
    TRISBbits.TRISB11 = 0;	//enable as output
    LATBbits.LATB11 = 0;
    ODCBbits.ODB11 = 1;  //enable open drain
    

}

// ******************************************************************************************* //

char KeypadScan() {
	char key = -1;
	

	// TODO: Implement the keypad scanning procedure to detect if exactly one button of the 
	// keypad is pressed. The function should return:
	//
	//      -1         : Return -1 if no keys are pressed.
	//      '0' - '9'  : Return the ASCII character '0' to '9' if one of the 
	//                   numeric (0 - 9) keys are pressed.
	//      '#'        : Return the ASCII character '#' if the # key is pressed. 
	//      '*'        : Return the ASCII character '*' if the * key is pressed. 
	//       -1        : Return -1 if more than one key is pressed simultaneously.
	// Notes: 
	//        1. Only valid inputs should be allowed by the user such that all invalid inputs 
	//           are ignored until a valid input is detected.
	//        2. The user must release all keys of the keypad before the following key press
	//           is processed. This is to prevent invalid keypress from being processed if the 
	//           users presses multiple keys simultaneously.
	//

        // Begin Added Code
        //while(key == -1);

        int button = 0;


        if(LATAbits.LATA1 == 0 && LATBbits.LATB3 == 0)
        {
            key = '1';
            button++;
        }

        if(LATAbits.LATA0 == 0 && LATBbits.LATB3 == 0)
        {
            key = '2';
            button++;
        }

        if(LATBbits.LATB2 == 0 && LATBbits.LATB3 == 0)
        {
            key = '3';
            button++;
        }

        if(LATAbits.LATA1 == 0 && LATBbits.LATB11 == 0)
        {
            key = '4';
            button++;
        }

        if(LATAbits.LATA0 == 0 && LATBbits.LATB11 == 0)
        {
            key = '5';
            button++;
        }

        if(LATBbits.LATB2 == 0 && LATBbits.LATB11 == 0)
        {
            key = '6';
            button++;
        }

        if(LATAbits.LATA1 == 0 && LATAbits.LATA3 == 0)
        {
            key = '7';
            button++;
        }

        if(LATAbits.LATA0 == 0 && LATAbits.LATA3 == 0)
        {
            key = '8';
            button++;
        }

        if(LATBbits.LATB2 == 0 && LATAbits.LATA3 == 0)
        {
            key = '9';
            button++;
        }

        if(LATAbits.LATA1 == 0 && LATAbits.LATA2 == 0)
        {
            key = '*';
            button++;
        }

        if(LATAbits.LATA0 == 0 && LATAbits.LATA2 == 0)
        {
            key = '0';
            button++;
        }

        if(LATBbits.LATB2 == 0 && LATAbits.LATA2 == 0)
            
        {
            key = '#';
            button++;
        }

        if (button == 1)
        {
            return key;
        }
        else
        {
            return -1;
        }





        // End Added Code
	
}

// ******************************************************************************************* //
