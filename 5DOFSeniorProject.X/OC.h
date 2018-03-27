/* 
 * File:   OC.h
 * Author: Yves Losier
 *
 * Created on October 7, 2014, 11:18 PM
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

#ifndef OC_H
#define	OC_H

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



//*******************************************************************************
//  Output Comparator 1 Functions
//*******************************************************************************
void InitOC1Pin(void);     // Initializes OC1 Pin

void SetOC1AsPWM(void);    // Configure OC1 as PWM
void SetOC1AsPulse(void);  // Configure OC1 as Pulse

void SetPWM1DutyCycle(int cycle);    // Set PWM   value for OC1
void SetPulse1Length(float length);  // Set Pulse value for OC1
//*******************************************************************************


//*******************************************************************************
//  Output Comparator 2 Functions
//*******************************************************************************
void InitOC2Pin(void);     // Initializes OC2 Pin
void InitOC2Module(void);  // Initializes OC2 Module

void SetOC2AsPWM(void);    // Configure   OC2 as PWM
void SetOC2AsPulse(void);  // Configure   OC2 as Pulse

void SetPWM2DutyCycle(int cycle);    // Set PWM   value for OC2
void SetPulse2Length(float length);  // Set Pulse value for OC2
//*******************************************************************************


//*******************************************************************************
//  Output Comparator 3 Functions
//*******************************************************************************
void InitOC3Pin(void);     // Initializes OC3 Pin
void InitOC3Module(void);  // Initializes OC3 Module

void SetOC3AsPWM(void);    // Configure   OC3 as PWM
void SetOC3AsPulse(void);  // Configure   OC3 as Pulse

void SetPWM3DutyCycle(int cycle);    // Set PWM   value for OC3
void SetPulse3Length(float length);  // Set Pulse value for OC3
//*******************************************************************************


//*******************************************************************************
//  Output Comparator 4 Functions
//*******************************************************************************
void InitOC4Pin(void);     // Initializes OC4 Pin
void InitOC4Module(void);  // Initializes OC4 Module

void SetOC4AsPWM(void);    // Configure   OC4 as PWM
void SetOC4AsPulse(void);  // Configure   OC4 as Pulse

void SetPWM4DutyCycle(int cycle);    // Set PWM   value for OC4
void SetPulse4Length(float length);  // Set Pulse value for OC4
//*******************************************************************************


#ifdef	__cplusplus
}
#endif

#endif	/* OC_H */

