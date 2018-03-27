/* 
 * File:   ConfigDevice.h
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

#ifndef CONFIGDEVICE_H
#define	CONFIGDEVICE_H

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


/* Microcontroller MIPs (FCY) */
#define SYS_FREQ        7370000L
#define FCY             SYS_FREQ/2

#define MICROSTICK_LED0_PIN _LATA0

//Digital Output setup
#define MICROSTICK_ENABLE_PIN _LATB8 //enable
#define MICROSTICK_IN1_PIN _LATB14 //IN1
#define MICROSTICK_IN2_PIN _LATB13 //IN2
//Digital Input setup
#define MICROSTICK_LIMSW_PIN _RA4 //Limitswitch
    
   



void ConfigureOscillator(void);  // Handles clock switching/osc initialization

void InitDevice(void);
//Enable control
void ENABLE_ON(void);
void ENABLE_OFF(void);
void ENABLE_TOGGLE(void);

//IN1 control
void IN1_ON(void);
void IN1_OFF(void);
void IN1_TOGGLE(void);

//IN2 Control
void IN2_ON(void);
void IN2_OFF(void);
void IN2_TOGGLE(void);

//INPUT RA4
void LIMSW_HOLD(void);

//LED0 Control
void LED0_ON(void);
void LED0_OFF(void);
void LED0_TOGGLE(void);


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIGDEVICE_H */

