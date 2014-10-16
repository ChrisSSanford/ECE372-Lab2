/**************************************************************************************************/

/*
 * File: Lab2.c
 * Team: Lambda^3
 * Members: Chris Houseman
 *          Randy Martinez
 *          Rachel Powers
 *          Chris Sanford
 *
 * Date: October 6, 2014
 *
 * Description: Code that defines functions for password system
 *
 */

// ******************************************************************************************* //
// ******************************************************************************************* //
// ******************************************************************************************* //
// Include file for PIC24FJ64GA002 microcontroller. This include file defines
// MACROS for special function registers (SFR) and control bits within those
// registers.

#include "p24fj64ga002.h"
#include <stdio.h>
#include "lcd.h"
#include "keypad.h"

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings. 
//
// Make sure "Configuration Bits set in code." option is checked in MPLAB.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to 
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & 
		 BKBUG_ON & COE_ON & ICS_PGx1 & 
		 FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

// ******************************************************************************************* //
// Configuration bits for CONFIG2 settings.
// Make sure "Configuration Bits set in code." option is checked in MPLAB.

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
		 IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

// ******************************************************************************************* //

// Varible used to indicate that the current configuration of the keypad has been changed,
// and the KeypadScan() function needs to be called.

volatile char scanKeypad;
volatile int state = 0;

// ******************************************************************************************* //

int main(void)
{
	char key;


	
	// TODO: Initialize and configure IOs, LCD (using your code from Lab 1), 
	// UART (if desired for debugging), and any other configurations that are needed.
	
	LCDInitialize();
	KeypadInitialize();

	
	// TODO: Initialize scanKeypad variable.
        scanKeypad = 0;

        LCDPrintString("Hello");
        LCDMoveCursor(0,0);
	
	while(1)
	{
            switch(state){
            //State 0: Ready State
            //Wait for user input
                case 0:
                    LCDMoveCursor(0,0);
                    LCDPrintString("Enter");
                    if( scanKeypad == 1 ) {
                        state = 1;
                    scanKeypad = 0;
                    }
                    break;

                case 1:
                    key = KeypadScan();
                        if( key != -1 ) {
                            LCDMoveCursor(1,0);
                            LCDPrintChar(key);
                            if (key == '#') {
                                state=0;
                            }
//                            else if (key == '*') {
//                                scanKeypad=0;
//                                while (scanKeypad != 1);
//                                starkey = KeypadScan();
//                                if (key!= -1) {
//                                    if (starkey == '*'){
//                                        state = 7;
//                                    }
//                                    else {
//                                        state = 4;
//                                    }
//                                }
//                            }
//                            else {
//                                password[0]=key;
//                                state = 2;
//                            }
                        }
                        
                    break;
		
	}
        }
	return 0;
}

// ******************************************************************************************* //
// Defines an interrupt service routine that will execute whenever any enable
// input change notifcation is detected.
// 
//     In place of _ISR and _ISRFAST, we can directy use __attribute__((interrupt))
//     to inform the compiler that this function is an interrupt. 
//
//     _CNInterrupt is a macro for specifying the interrupt for input change 
//     notification.
//
// The functionality defined in an interrupt should be a minimal as possible
// to ensure additional interrupts can be processed. 
void __attribute__((interrupt)) _CNInterrupt(void)
{	
	// TODO: Clear interrupt flag
	IFS1bits.CNIF = 0;
	
	// TODO: Detect if *any* key of the keypad is *pressed*, and update scanKeypad
	// variable to indicate keypad scanning process must be executed.
    scanKeypad = 1;
}

// ******************************************************************************************* //
