/*
 * File:   ConfigDevice.c
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


/* Device header file */
#if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "ConfigDevice.h"



//---------------------------------------------------------------
// Configuration bits Registers Assignments
//---------------------------------------------------------------
_FPOR(PWMPIN_ON); //PWM Module Pin Mode: PWM module pins controlled by PORT register at device reset
        
_FOSCSEL(FNOSC_FRC);
// Oscillator Mode: Internal Fast RC (FRC)
// Note: Internal Microstick II Oscillator (7.37MHz)

_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & IOL1WAY_OFF & POSCMD_NONE);
// Primary Oscillator Source: Primary Oscillator Disabled
// OSC2 Pin Function: OSC2 pin has digital I/O function
// Peripheral Pin Select Configuration: Allow Multiple Re-configurations
// Clock Switching and Monitor: Clock switching is enabled, Fail-Safe Clock Monitor is disabled

_FWDT(FWDTEN_OFF);
// Watchdog Timer Enable: Watchdog Timer Enabled/disabled by user software

_FICD(JTAGEN_OFF & ICS_PGD1);
// JTAG Port Enable: JTAG is Disabled
// Comm Channel Select: Communicate on PGC1/EMUC1 and PGD1/EMUD1

//-- End of Configuration Bits Registers Assignments ------




void ConfigureOscillator(void)
{
    /* Disable Watch Dog Timer */
    _SWDTEN = 0;
}


/* I/O and Peripheral Initialization */
void InitDevice(void)
{
    // --------------------------------------------------------------
    // LED0 Digital Output Pin Configuration
    // --------------------------------------------------------------
    _TRISA0 = 0;   // output i/o
    _PCFG0  = 1;   // set pin as a digital pin
    
    
    //Digital Output Pin config
    _TRISB13 = 0;
    _TRISB14 = 0;
    
    //Digital Input Pin config
    _TRISA4 = 1;
   // _TRISB8 = 1;
   // _TRISB9 = 1;
    
    // --------------------------------------------------------------
}



//ENABLE control
void ENABLE_ON(void) {
    MICROSTICK_ENABLE_PIN = 1;
}

void ENABLE_OFF(void) {
    MICROSTICK_ENABLE_PIN = 0;
}
void ENABLE_TOGGLE(void) {
    MICROSTICK_ENABLE_PIN = ~MICROSTICK_ENABLE_PIN;
}

//IN1 control 
void IN1_ON(void) {
    MICROSTICK_IN1_PIN = 1;
}

void IN1_OFF(void) {
    MICROSTICK_IN1_PIN = 0;
}

void IN1_TOGGLE(void) {
    MICROSTICK_IN1_PIN = ~MICROSTICK_IN1_PIN;
}

//IN2 control 
void IN2_ON(void) {
    MICROSTICK_IN2_PIN = 1;
}

void IN2_OFF(void) {
    MICROSTICK_IN2_PIN = 0;
}

void IN2_TOGGLE(void) {
    MICROSTICK_IN2_PIN =~ MICROSTICK_IN2_PIN;
}

void LIMSW_HOLD(void){
    MICROSTICK_LIMSW_PIN = MICROSTICK_LIMSW_PIN;
}

//LED0 control 
void LED0_ON(void) {
    MICROSTICK_LED0_PIN = 1;
}

void LED0_OFF(void) {
    MICROSTICK_LED0_PIN = 0;
}

void LED0_TOGGLE(void) {
    MICROSTICK_LED0_PIN = ~MICROSTICK_LED0_PIN;
}

