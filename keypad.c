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
