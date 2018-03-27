/*
 * File:   Timer4.c
 * Author: Yves Losier
 *
 * Created on September 30, 2014, 11:59 PM
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author		Date      	Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Y. Losier            30/09/14        First release of source file
 *
 * ADDITIONAL NOTES:
 *
 */


/* Device header file */
#if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "Timer4.h"



unsigned long timer4Counter = 0;
unsigned char timer4Flag    = 0;





//*******************************************************************************
//
//    Function:       InitTmr4
//    Description:    Configures Timer4 Module
//
//    Note: The initialization function does NOT start Timer4
//
//*******************************************************************************
void InitTimer4(void)
{
    StopTimer4();

    TMR4   = 0x0000;     // Clear timer 4
    T4CONbits.TCKPS = 1; // Timer Prescalar (0 == 1:1, 1 == 1:8, 2 == 1:64, 3 == 1:256)
    PR4    = 23030;      // Interrupt every 0.05 seconds

    _T4IF = 0;   // Clear interrupt flag
    _T4IE = 1;   // Set interrupt enable bit
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       StartTimer4
//    Description:    Starts Timer4 Module
//
//*******************************************************************************
void StartTimer4(void)
{
   T4CONbits.TON = 1;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       StopTimer4
//    Description:    Stops Timer4 Module
//
//*******************************************************************************
void StopTimer4(void)
{
   T4CONbits.TON = 0;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       GetTimer4CounterValue
//    Description:    Helper function used by other c files to acquire the
//                    current value of the timer4Counter variable
//
//*******************************************************************************
unsigned long GetTimer4CounterValue(void)
{
    unsigned long volatile currentValue;

    if (_T4IE == 1)
    {
        _T4IE = 0;
        currentValue = timer4Counter;
        _T4IE = 1;
    }
    else
    {
        currentValue = timer4Counter;
    }

    return currentValue;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       GetTimer4FlagValue
//    Description:    Helper function used by other c files to acquire the
//                    current value of the timer4Flag variable
//
//*******************************************************************************
unsigned char GetTimer4FlagValue(void)
{
    unsigned char volatile currentValue;

    if (_T4IE == 1)
    {
        _T4IE = 0;
        currentValue = timer4Flag;
        _T4IE = 1;
    }
    else
    {
        currentValue = timer4Flag;
    }

    return currentValue;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       ClearTimer4FlagValue
//    Description:    Helper function used by other c files to clear the
//                    timer4Flag variable
//
//*******************************************************************************
void ClearTimer4FlagValue(void)
{
    if (_T4IE == 1)
    {
        _T4IE = 0;
        timer4Flag = 0;
        _T4IE = 1;
    }
    else
    {
        timer4Flag = 0;
    }
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       T4 ISR
//    Description:    Handles interrupts caused by Timer4 module.
//                    Used to increment the timer4Counter variable
//
//*******************************************************************************
void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void)
{
   timer4Counter++;     // Increment timer4Counter variable

   _SAMP = 0;  // Start ADC Conversion of next channel

   if ((timer4Counter & 0x00000001) == 0)
   {
       timer4Flag = 1;      // Set timer4Flag to indicate that 2 x timer4 period elapsed
   }

   _T4IF = 0;   // clear interrupt flag
}
//*******************************************************************************


