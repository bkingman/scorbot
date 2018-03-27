/*
 * File:   Timer1.c
 * Author: Yves Losier
 *
 * Created on September 23, 2014, 11:52 PM
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author		Date      	Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Y. Losier            23/09/14        First release of source file
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

#include "Timer1.h"



unsigned long timer1Counter = 0;
unsigned char timer1Flag    = 0;





//*******************************************************************************
//
//    Function:       InitTmr1
//    Description:    Configures Timer1 Module
//
//    Note: The initialization function does NOT start Timer1
//
//*******************************************************************************
void InitTimer1(void)
{
    StopTimer1();

    TMR1   = 0x0000;  // Clear timer 1
    _TCKPS = 2;       // Timer Prescalar (0 == 1:1, 1 == 1:8, 2 == 1:64, 3 == 1:256)
    PR1    = 28788;   // Interrupt every 0.5 seconds

    _T1IF = 0;   // Clear interrupt flag
    _T1IE = 1;   // Set interrupt enable bit
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       StartTimer1
//    Description:    Starts Timer1 Module
//
//*******************************************************************************
void StartTimer1(void)
{
   T1CONbits.TON = 1;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       StopTimer1
//    Description:    Stops Timer1 Module
//
//*******************************************************************************
void StopTimer1(void)
{
   T1CONbits.TON = 0;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       GetTimer1CounterValue
//    Description:    Helper function used by other c files to acquire the
//                    current value of the timer1Counter variable
//
//*******************************************************************************
unsigned long GetTimer1CounterValue(void)
{
    unsigned long volatile currentValue;

    if (_T1IE == 1)
    {
        _T1IE = 0;
        currentValue = timer1Counter;
        _T1IE = 1;
    }
    else
    {
        currentValue = timer1Counter;
    }

    return currentValue;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       GetTimer1FlagValue
//    Description:    Helper function used by other c files to acquire the
//                    current value of the timer1Flag variable
//
//*******************************************************************************
unsigned char GetTimer1FlagValue(void)
{
    unsigned char volatile currentValue;

    if (_T1IE == 1)
    {
        _T1IE = 0;
        currentValue = timer1Flag;
        _T1IE = 1;
    }
    else
    {
        currentValue = timer1Flag;
    }

    return currentValue;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       ClearTimer1FlagValue
//    Description:    Helper function used by other c files to clear the
//                    timer1Flag variable
//
//*******************************************************************************
void ClearTimer1FlagValue(void)
{
    if (_T1IE == 1)
    {
        _T1IE = 0;
        timer1Flag = 0;
        _T1IE = 1;
    }
    else
    {
        timer1Flag = 0;
    }
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       T1 ISR
//    Description:    Handles interrupts caused by Timer1 module.
//                    Used to increment the timer1Counter variable
//
//*******************************************************************************
void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void)
{
   timer1Counter++;     // Increment timer1Counter variable
   timer1Flag = 1;      // Set timer1Flag to indicate that timer1 period elapsed

   _T1IF = 0;   // clear interrupt flag
}
//*******************************************************************************


