/*
 * File:   ADC1.c
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

#include "ADC1.h"


unsigned int dataX[SAMP_BUFF_SIZE];
unsigned int dataY[SAMP_BUFF_SIZE];



//*******************************************************************************
//
//    Function:       InitADC1Pins
//    Description:    Configure ADC1 Pins
//
//    Note: The initialization function does NOT configure the ADC1 module
//
//*******************************************************************************
void InitADC1Pins(void)
{
    _TRISB2= 1;  // input i/o
    _TRISB3= 1;  // input i/o

    _PCFG4 = 0;	 // AN4 as Analog Input
    _PCFG5 = 0;	 // AN5 as Analog Input
}
//*************************************************************************



//*******************************************************************************
//
//    Function:       InitADC1Module
//    Description:    Configures ADC1 Module
//
//    Note: The initialization function does NOT configure the ADC1 I/O pins
//
//*******************************************************************************
void InitADC1Module(void)
{
    AD1CON1bits.FORM   = 0;		// Data Output Format: Unsigned Integer
    AD1CON1bits.SSRC   = 0;		// Sample Clock Source: Clear Sample bit to start conversion
    AD1CON1bits.ASAM   = 1;		// ADC Sample Control: Sampling begins immediately after conversion
    AD1CON1bits.AD12B  = 1;		// 12-bit ADC operation

    AD1CON2bits.CSCNA = 1;		// Scan Input Selections for CH0+ during Sample A bit
    AD1CON2bits.CHPS  = 0;		// Converts CH0

    AD1CON3bits.ADRC = 0;		// ADC Clock is derived from Systems Clock
    AD1CON3bits.ADCS = 63;		// ADC Conversion Clock Tad=Tcy*(ADCS+1)= (1/3685000)*64 = 17.4us (57578Hz)

    AD1CON2bits.SMPI    = (NUM_CHS2SCAN-1);	// 2 ADC Channel is scanned


    _CSS4 = 1;	           // Enable AN4 for channel scan
    _CSS5 = 1;	           // Enable AN5 for channel scan

    _AD1IF = 0;	           // Clear the A/D interrupt flag bit
    _AD1IE = 1;	           // Enable A/D interrupt

    AD1CON1bits.ADON = 1;  // Turn on the A/D converter
}
//*******************************************************************************




//*******************************************************************************
//
//    Function:       GetDataX
//    Description:    Helper function used by other c files to acquire the
//                    current value of the dataX variable
//
//*******************************************************************************
unsigned int GetDataX(void)
{
    unsigned int volatile currentValue;

    if (_AD1IE == 1)
    {
        _AD1IE = 0;
        currentValue = dataX[0];
        _AD1IE = 1;
    }
    else
    {
        currentValue = dataX[0];
    }

    return currentValue;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       GetDataY
//    Description:    Helper function used by other c files to acquire the
//                    current value of the dataY variable
//
//*******************************************************************************
unsigned int GetDataY(void)
{
    unsigned int volatile currentValue;

    if (_AD1IE == 1)
    {
        _AD1IE = 0;
        currentValue = dataY[0];
        _AD1IE = 1;
    }
    else
    {
        currentValue = dataY[0];
    }

    return currentValue;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       ADC1 ISR
//    Description:    Handles interrupts caused by ADC1 module when conversion
//                     is completed.  The ISR takes the value and stores it in
//                     the appropriate buffer.  The next data conversion takes
//                     place when the Timer4 ISR occurs.
//
//*******************************************************************************
void __attribute__((interrupt, no_auto_psv)) _ADC1Interrupt(void)
{
    static unsigned char scanCounter   = 0;
    static unsigned char sampleCounter = 0;

    switch (scanCounter)
    {
            case 0:
                    dataX[sampleCounter] = ADC1BUF0;
                    break;

            case 1:
                    dataY[sampleCounter] = ADC1BUF0;
                    break;

            default:
                    break;
    }

    scanCounter++;
    if(scanCounter==NUM_CHS2SCAN)
    {
      scanCounter=0;
      sampleCounter++;
    }

    if(sampleCounter==SAMP_BUFF_SIZE)
    {
      sampleCounter=0;
    }

    _AD1IF = 0;		// Clear the ADC1 Interrupt Flag
}
//*******************************************************************************

