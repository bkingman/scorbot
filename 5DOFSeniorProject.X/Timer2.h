/* 
 * File:   Timer2.h
 * Author: Yves Losier
 *
 * Created on October 7, 2014, 10:54 PM
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

#ifndef TIMER2_H
#define	TIMER2_H

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


void InitTimer2(void);      // Initializes Timer2 module
void StartTimer2(void);     // Starts Timer2 module
void StopTimer2(void);      // Stops  Timer2 module

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER2_H */

