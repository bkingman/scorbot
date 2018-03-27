/*
 * File:   OC.c
 * Author: Yves Losier
 *
 * Created on October 7, 2014, 11:59 PM
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


/* Device header file */
#if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "OC.h"



//*******************************************************************************
//
//    Function:       InitOC1Pin
//    Description:    Configure OC1 Pin
//
//    Note: The initialization function does NOT configure the OC1 module
//
//*******************************************************************************
void InitOC1Pin(void)
{
    _TRISB12 = 0;  // output digital I/O (to be used for OC1)

    //*************************************************************
    // Unlock Registers:
    //
    // Clear the bit 6 of OSCCONL to unlock Pin Re-map
    //
    //*************************************************************
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    //*************************************************************

    _RP12R = 18; // OC1_IO (mapped onto pin RB12)

    //************************************************************
    // Lock Registers:
    //
    // Set the bit 6 of OSCCONL to lock Pin Re-map
    //
    //************************************************************
    __builtin_write_OSCCONL(OSCCON | 0x40);
    //*************************************************************

}
//*************************************************************************


//*******************************************************************************
//
//    Function:       SetOC1AsPWM
//    Description:    Configures Output Comparator Module 1 as a PWM output pin
//
//    Note: The initialization function does NOT configure an I/O pin for OC1
//
//*******************************************************************************
void SetOC1AsPWM(void)
{
   OC1CON = 0x0000; // Turn off Output Compare 1 Module

   OC1CONbits.OCTSEL = 0; // Select Timer2 as timer source

   OC1R = 0; // Initialize Compare Register with 0x0000
   OC1RS = 0; // Initialize Secondary Compare Register with 0x0000

   OC1CONbits.OCM = 0x06; // Load new output compare mode to OC1CON (PWM mode)
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetOC1AsPulse
//    Description:    Configures Output Comparator Module 1 as a Pulse output pin
//
//    Note: The initialization function does NOT configure an I/O pin for OC1
//
//*******************************************************************************
void SetOC1AsPulse(void)
{
   OC1CON = 0x0000; // Turn off Output Compare 1 Module

   OC1CONbits.OCTSEL = 1; // Select Timer3 as timer source

   OC1R = 0; // Initialize Compare Register with 0x0000
   OC1RS = 0; // Initialize Secondary Compare Register with 0x0000

   OC1CONbits.OCM = 0x05; // Load new output compare mode to OC1CON (Pulse mode)
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetPWM1DutyCycle
//    Description:    Configures PWM value for Output Comparator Module 1
//
//    Input Value Range: 0-100
//
//*******************************************************************************
void SetPWM1DutyCycle(int cycle)
{
    if (OC1CONbits.OCM == 0x06)
    {
        if (cycle>100)
        {
            cycle = 100;
        }
        else if (cycle <0)
        {
            cycle = 0;
        }

        OC1RS = (PR2*cycle)/100;
    }
    else
    {
        while(1) {}  // Trap will occur only if OC is NOT configured for PWM mode
    }
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetPulse1Length
//    Description:    Configures Pulse value for Output Comparator Module 1
//
//    Input Value Range: 0.5-2.5
//
//*******************************************************************************
void SetPulse1Length(float length)
{
    if (OC1CONbits.OCM == 0x05)
    {
        if (length>2.5)
        {
            length = 2.5;
        }
        else if (length<0.5)
        {
            length = 0.5;
        }
        OC1RS = (int)(length/20*PR3);
    }
    else
    {
        while(1) {}  // Trap will occur only if OC is NOT configured for Pulse mode
    }
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       InitOC2Pin
//    Description:    Configure OC2 Pin
//
//    Note: The initialization function does NOT configure the OC2 module
//
//*******************************************************************************
void InitOC2Pin(void)
{
    _TRISB13 = 0;  // output digital I/O (to be used for OC2)

    //*************************************************************
    // Unlock Registers:
    //
    // Clear the bit 6 of OSCCONL to unlock Pin Re-map
    //
    //*************************************************************
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    //*************************************************************

    _RP13R = 19; // OC2_IO (mapped onto pin RB13)

    //************************************************************
    // Lock Registers:
    //
    // Set the bit 6 of OSCCONL to lock Pin Re-map
    //
    //************************************************************
    __builtin_write_OSCCONL(OSCCON | 0x40);
    //*************************************************************

}
//*************************************************************************


//*******************************************************************************
//
//    Function:       SetOC2AsPWM
//    Description:    Configures Output Comparator Module 2 as a PWM output pin
//
//    Note: The initialization function does NOT configure an I/O pin for OC2
//
//*******************************************************************************
void SetOC2AsPWM(void)
{
   OC2CON = 0x0000; // Turn off Output Compare 2 Module

   OC2CONbits.OCTSEL = 0; // Select Timer2 as timer source

   OC2R = 0; // Initialize Compare Register with 0x0000
   OC2RS = 0; // Initialize Secondary Compare Register with 0x0000

   OC2CONbits.OCM = 0x06; // Load new output compare mode to OC2CON (PWM mode)
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetOC2AsPulse
//    Description:    Configures Output Comparator Module 2 as a Pulse output pin
//
//    Note: The initialization function does NOT configure an I/O pin for OC2
//
//*******************************************************************************
void SetOC2AsPulse(void)
{
   OC2CON = 0x0000; // Turn off Output Compare 2 Module

   OC2CONbits.OCTSEL = 1; // Select Timer3 as timer source

   OC2R = 0; // Initialize Compare Register with 0x0000
   OC2RS = 0; // Initialize Secondary Compare Register with 0x0000

   OC2CONbits.OCM = 0x05; // Load new output compare mode to OC2CON (Pulse mode)
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetPWM2DutyCycle
//    Description:    Configures PWM value for Output Comparator Module 2
//
//    Input Value Range: 0-100
//
//*******************************************************************************
void SetPWM2DutyCycle(int cycle)
{
    
    if (OC2CONbits.OCM == 0x06)
    {
        if (cycle>100)
        {
            cycle = 100;
        }
        else if (cycle <0)
        {
            cycle = 0;
        }

        OC2RS = (PR2*cycle)/100;
    }
    else
    {
        while(1) {}  // Trap will occur only if OC is NOT configured for PWM mode
    }
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetPulse2Length
//    Description:    Configures Pulse value for Output Comparator Module 2
//
//    Input Value Range: 0.5-2.5
//
//*******************************************************************************
void SetPulse2Length(float length)
{
    if (OC2CONbits.OCM == 0x05)
    {
        if (length>2.5)
        {
            length = 2.5;
        }
        else if (length<0.5)
        {
            length = 0.5;
        }
        OC2RS = (int)(length/20*PR3);
    }
    else
    {
        while(1) {}  // Trap will occur only if OC is NOT configured for Pulse mode
    }
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       InitOC3Pin
//    Description:    Configure OC3 Pin
//
//    Note: The initialization function does NOT configure the OC3 module
//
//*******************************************************************************
void InitOC3Pin(void)
{
    _TRISB14 = 0;  // output digital I/O (to be used for OC3)

    //*************************************************************
    // Unlock Registers:
    //
    // Clear the bit 6 of OSCCONL to unlock Pin Re-map
    //
    //*************************************************************
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    //*************************************************************

    _RP14R = 20; // OC3_IO (mapped onto pin RB14)

    //************************************************************
    // Lock Registers:
    //
    // Set the bit 6 of OSCCONL to lock Pin Re-map
    //
    //************************************************************
    __builtin_write_OSCCONL(OSCCON | 0x40);
    //*************************************************************

}
//*************************************************************************


//*******************************************************************************
//
//    Function:       SetOC3AsPWM
//    Description:    Configures Output Comparator Module 3 as a PWM output pin
//
//    Note: The initialization function does NOT configure an I/O pin for OC3
//
//*******************************************************************************
void SetOC3AsPWM(void)
{
   OC3CON = 0x0000; // Turn off Output Compare 3 Module

   OC3CONbits.OCTSEL = 0; // Select Timer2 as timer source

   OC3R = 0; // Initialize Compare Register with 0x0000
   OC3RS = 0; // Initialize Secondary Compare Register with 0x0000

   OC3CONbits.OCM = 0x06; // Load new output compare mode to OC3CON (PWM mode)
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetOC3AsPulse
//    Description:    Configures Output Comparator Module 3 as a Pulse output pin
//
//    Note: The initialization function does NOT configure an I/O pin for OC3
//
//*******************************************************************************
void SetOC3AsPulse(void)
{
   OC3CON = 0x0000; // Turn off Output Compare 3 Module

   OC3CONbits.OCTSEL = 1; // Select Timer3 as timer source

   OC3R = 0; // Initialize Compare Register with 0x0000
   OC3RS = 0; // Initialize Secondary Compare Register with 0x0000

   OC3CONbits.OCM = 0x05; // Load new output compare mode to OC3CON (Pulse mode)
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetPWM3DutyCycle
//    Description:    Configures PWM value for Output Comparator Module 3
//
//    Input Value Range: 0-100
//
//*******************************************************************************
void SetPWM3DutyCycle(int cycle)
{
    if (OC3CONbits.OCM == 0x06)
    {
        if (cycle>100)
        {
            cycle = 100;
        }
        else if (cycle <0)
        {
            cycle = 0;
        }

        OC3RS = (PR2*cycle)/100;
    }
    else
    {
        while(1) {}  // Trap will occur only if OC is NOT configured for PWM mode
    }
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetPulse3Length
//    Description:    Configures Pulse value for Output Comparator Module 3
//
//    Input Value Range: 0.5-2.5
//
//*******************************************************************************
void SetPulse3Length(float length)
{
    if (OC3CONbits.OCM == 0x05)
    {
        if (length>2.5)
        {
            length = 2.5;
        }
        else if (length<0.5)
        {
            length = 0.5;
        }
        OC3RS = (int)(length/20*PR3);
    }
    else
    {
        while(1) {}  // Trap will occur only if OC is NOT configured for Pulse mode
    }
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       InitOC4Pin
//    Description:    Configure OC4 Pin
//
//    Note: The initialization function does NOT configure the OC4 module
//
//*******************************************************************************
void InitOC4Pin(void)
{
    _TRISB15 = 0;  // output digital I/O (to be used for OC4)

    //*************************************************************
    // Unlock Registers:
    //
    // Clear the bit 6 of OSCCONL to unlock Pin Re-map
    //
    //*************************************************************
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    //*************************************************************

    _RP15R = 21; // OC4_IO (mapped onto pin RB15)

    //************************************************************
    // Lock Registers:
    //
    // Set the bit 6 of OSCCONL to lock Pin Re-map
    //
    //************************************************************
    __builtin_write_OSCCONL(OSCCON | 0x40);
    //*************************************************************

}
//*************************************************************************


//*******************************************************************************
//
//    Function:       SetOC4AsPWM
//    Description:    Configures Output Comparator Module 4 as a PWM output pin
//
//    Note: The initialization function does NOT configure an I/O pin for OC4
//
//*******************************************************************************
void SetOC4AsPWM(void)
{
   OC4CON = 0x0000; // Turn off Output Compare 4 Module

   OC4CONbits.OCTSEL = 0; // Select Timer2 as timer source

   OC4R = 0; // Initialize Compare Register with 0x0000
   OC4RS = 0; // Initialize Secondary Compare Register with 0x0000

   OC4CONbits.OCM = 0x06; // Load new output compare mode to OC4CON (PWM mode)
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetOC4AsPulse
//    Description:    Configures Output Comparator Module 4 as a Pulse output pin
//
//    Note: The initialization function does NOT configure an I/O pin for OC4
//
//*******************************************************************************
void SetOC4AsPulse(void)
{
   OC4CON = 0x0000; // Turn off Output Compare 4 Module

   OC4CONbits.OCTSEL = 1; // Select Timer3 as timer source

   OC4R = 0; // Initialize Compare Register with 0x0000
   OC4RS = 0; // Initialize Secondary Compare Register with 0x0000

   OC4CONbits.OCM = 0x05; // Load new output compare mode to OC4CON (Pulse mode)
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetPWM4DutyCycle
//    Description:    Configures PWM value for Output Comparator Module 4
//
//    Input Value Range: 0-100
//
//*******************************************************************************
void SetPWM4DutyCycle(int cycle)
{
    if (OC4CONbits.OCM == 0x06)
    {
        if (cycle>100)
        {
            cycle = 100;
        }
        else if (cycle <0)
        {
            cycle = 0;
        }

        OC4RS = (PR2*cycle)/100;
    }
    else
    {
        while(1) {}  // Trap will occur only if OC is NOT configured for PWM mode
    }
}
//*******************************************************************************


//*******************************************************************************
//
//    Function:       SetPulse4Length
//    Description:    Configures Pulse value for Output Comparator Module 4
//
//    Input Value Range: 0.5-2.5
//
//*******************************************************************************
void SetPulse4Length(float length)
{
    if (OC4CONbits.OCM == 0x05)
    {
        if (length>2.5)
        {
            length = 2.5;
        }
        else if (length<0.5)
        {
            length = 0.5;
        }
        OC4RS = (int)(length/20*PR3);
    }
    else
    {
        while(1) {}  // Trap will occur only if OC is NOT configured for Pulse mode
    }
}
//*******************************************************************************


