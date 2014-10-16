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
volatile int timerFlag=0;

// ******************************************************************************************* //

int main(void)
{
	char key;
        char password[4];


	
	// TODO: Initialize and configure IOs, LCD (using your code from Lab 1), 
	// UART (if desired for debugging), and any other configurations that are needed.

	// Initialize 32-bit timer
        TMR4 = 0;
        TMR5 = 0;
        PR4 = 0b0101110111111111;
        PR5 = 0b11010;
        IFS1bits.T5IF = 0;
        IEC1bits.T5IE = 1;
        T4CONbits.T32 = 1;
        T4CONbits.TON = 1;
        T4CONbits.TCKPS0 = 1;
        T4CONbits.TCKPS1 = 1;

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
                                state=4;
                            }
                            else if (key == '*') {
                                state = 7;
                                }
                            else {
                                password[0]=key;
                                state = 2;
                            }
                        }
                        
                    break;
            //State 2: Enter Password
            case 2:
                LCDMoveCursor(0,0);
                LCDPrintString("Good");
                state = 0;
//                PasswordArrayInit();
//                LCDClear();
//                LCDMoveCursor(0,0);
//                LCDPrintString("Bad");
//                state=6;
                break;

            //State 4: Bad Password
            case 4:
                LCDMoveCursor(0,0);
                LCDPrintString("Bad");
                state = 6;
//                PasswordArrayInit();
//                LCDClear();
//                LCDMoveCursor(0,0);
//                LCDPrintString("Bad");
//                state=6;
                break;

            //State 6: Timer Countdown
            case 6:
                TMR4 = 0;
                TMR5 = 0;
                T4CONbits.TON = 1;
                while(timerFlag!=1);
                state=0;
                LCDClear();
                break;

            //State 7: Set Password
            case 7:
                LCDMoveCursor(0,0);
                LCDPrintString("Set Mode");
                state = 6;
//                PasswordArrayInit();
//                LCDClear();
//                LCDMoveCursor(0,0);
//                LCDPrintString("Bad");
//                state=6;
                break;
		
	}
        }
	return 0;
}
// ******************************************************************************************* //
// Defines an interrupt service routine that will execute whenever Timer 5's
// count reaches the specfied period value defined within the PR5 register.
//
//     _ISR and _ISRFAST are macros for specifying interrupts that
//     automatically inserts the proper interrupt into the interrupt vector
//     table
//
//     _T1Interrupt is a macro for specifying the interrupt for Timer 1
//
// The functionality defined in an interrupt should be a minimal as possible
// to ensure additional interrupts can be processed.
//void _ISR _T1Interrupt(void)


void __attribute__((interrupt,auto_psv)) _T5Interrupt(void){
    IFS1bits.T5IF = 0;
    timerFlag=1;
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
