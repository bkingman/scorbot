/* 
 * File:   UART1.h
 * Author: Yves Losier
 *
 * Created on September 30, 2014, 11:42 PM
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

#ifndef UART1_H
#define	UART1_H

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

void InitUART1Pins(void);    // Initializes UART1 Pins
void InitUART1Module(void); // Initializes UART1 Module

void ClearUART1IndexPointer(void);
unsigned int GetUART1IndexPointerValue(void);
unsigned char * GetUART1BufferPointer(void);

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);  // UART1 RX ISR
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void);  // UART1 TX ISR

#ifdef	__cplusplus
}
#endif

#endif	/* UART1_H */

