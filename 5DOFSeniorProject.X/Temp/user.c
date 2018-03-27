/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__dsPIC33E__)
	#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33Fxxxx.h>
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */

#include "user.h"            /* variables/params used by user.c               */



unsigned long timer1Counter = 0;
unsigned char timer1Flag    = 0;

/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    // --------------------------------------------------------------
    // LED0 Digital Output Pin Configuration
    // --------------------------------------------------------------
    _TRISA0 = 0;    // output i/o
    _PCFG0  = 1;   // set pin as a digital pin
    // --------------------------------------------------------------
}


