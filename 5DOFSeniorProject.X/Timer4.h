/* 
 * File:   Timer4.h
 * Author: Yves Losier
 *
 * Created on September 30, 2014, 11:58 PM
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

#ifndef TIMER4_H
#define	TIMER4_H

#ifdef	__cplusplus
extern "C" {
#endif


/* Device header file */
#if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */


void InitTimer4(void);      // Initializes Timer4 module
void StartTimer4(void);     // Starts Timer4 module
void StopTimer4(void);      // Stops  Timer4 module

unsigned long GetTimer4CounterValue(void);  // Acquire timer4Counter value
unsigned char GetTimer4FlagValue(void);     // Acquire timer4Flag value
void ClearTimer4FlagValue(void);            // Clears  timer4Flag variable

void __attribute__((interrupt, no_auto_psv)) _T4Interrupt(void);  // Timer4 ISR

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER4_H */

