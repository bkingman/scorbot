/* 
 * File:   ADC1.h
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

#ifndef ADC1_H
#define	ADC1_H

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


#define  SAMP_BUFF_SIZE	1  // Size of the input buffer per analog input
#define  NUM_CHS2SCAN	2  // Number of channels enabled for channel scan



void InitADC1Pins(void);    // Initializes ADC1 Pins
void InitADC1Module(void);  // Initializes ADC1 Module

unsigned int GetDataX(void);  // Retrieve current value from X axis
unsigned int GetDataY(void);  // Retrieve current value from Y axis


void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void);  // ADC1 ISR

#ifdef	__cplusplus
}
#endif

#endif	/* ADC1_H */

