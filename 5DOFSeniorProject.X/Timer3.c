/*
 * File:   Timer3.c
 * Author: Yves Losier
 *
 * Created on October 7, 2014, 11:02 PM
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

#include "Timer3.h"




//*******************************************************************************
//
//    Function:       InitTmr3
//    Description:    Configures Timer3 Module
//
//    Note: The initialization function does NOT start Timer3
//
//*******************************************************************************
void InitTimer3(void)
{
    StopTimer3();

    TMR3   = 0x0000;     // Clear timer 3
    T3CONbits.TCKPS = 1; // Timer Prescalar (0 == 1:1, 1 == 1:8, 2 == 1:64, 3 == 1:256)
    PR3    = 9212;      // Interrupt every 20ms

    _T3IF = 0;   // Clear interrupt flag
    _T3IE = 0;   // Clear interrupt enable bit
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       StartTimer3
//    Description:    Starts Timer3 Module
//
//*******************************************************************************
void StartTimer3(void)
{
   T3CONbits.TON = 1;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       StopTimer3
//    Description:    Stops Timer3 Module
//
//*******************************************************************************
void StopTimer3(void)
{
   T3CONbits.TON = 0;
}
//*******************************************************************************



