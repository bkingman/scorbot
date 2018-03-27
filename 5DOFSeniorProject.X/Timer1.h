/* 
 * File:   Timer1.h
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

#ifndef TIMER1_H
#define	TIMER1_H

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


void InitTimer1(void);      // Initializes Timer1 module
void StartTimer1(void);     // Starts Timer1 module
void StopTimer1(void);      // Stop   Timer1 module

unsigned long GetTimer1CounterValue(void);  // Acquire timer1Counter value
unsigned char GetTimer1FlagValue(void);     // Acquire timer1Flag value
void ClearTimer1FlagValue(void);            // Clears  timer1Flag variable

void __attribute__((interrupt, no_auto_psv)) _T1Interrupt(void);  // Timer1 ISR

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER1_H */

