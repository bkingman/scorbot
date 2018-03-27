/*
 * File:   Timer2.c
 * Author: Yves Losier
 *
 * Created on October 7, 2014, 10:56 PM
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author		Date      	Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Y. Losier            07/10/14        First release of source file
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

#include "Timer2.h"



//*******************************************************************************
//
//    Function:       InitTmr2
//    Description:    Configures Timer2 Module
//
//    Note: The initialization function does NOT start Timer2
//
//*******************************************************************************
void InitTimer2(void)
{
    StopTimer2();

    TMR2   = 0x0000;     // Clear timer 2
    T2CONbits.TCKPS = 3; // Timer Prescalar (0 == 1:1, 1 == 1:8, 2 == 1:64, 3 == 1:256)
    PR2    = 96;      // Interrupt every 18.1818...us

    _T2IF = 0;   // Clear interrupt flag
    _T2IE = 0;   // Clear interrupt enable bit
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       StartTimer2
//    Description:    Starts Timer2 Module
//
//*******************************************************************************
void StartTimer2(void)
{
   T2CONbits.TON = 1;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       StopTimer2
//    Description:    Stops Timer2 Module
//
//*******************************************************************************
void StopTimer2(void)
{
   T2CONbits.TON = 0;
}
//*******************************************************************************



