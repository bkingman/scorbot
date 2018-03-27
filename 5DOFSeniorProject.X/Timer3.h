/* 
 * File:   Timer3.h
 * Author: Yves Losier
 *
 * Created on October 7, 2014, 11:01 PM
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

#ifndef TIMER3_H
#define	TIMER3_H

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


void InitTimer3(void);      // Initializes Timer3 module
void StartTimer3(void);     // Starts Timer3 module
void StopTimer3(void);      // Stops  Timer3 module

#ifdef	__cplusplus
}
#endif

#endif	/* TIMER3_H */

