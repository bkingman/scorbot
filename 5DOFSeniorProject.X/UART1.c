
/*/ 
 * File:   UART1.c
 * Author: Yves Losier
 *
 * Created on September 30, 2014, 11:46 PM
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

#include "UART1.h"


unsigned int  UART1Index = 0;
unsigned char UARTBuffer[32];




//*******************************************************************************
//
//    Function:       InitUART1Pins
//    Description:    Configure UART1 Pins
//
//    Note: The initialization function does NOT configure the UART1 module
//
//*******************************************************************************
void InitUART1Pins(void)
{
    // UART TX pin
    _TRISB11 = 0;  // output digital I/O

    // UART RX pin
    _TRISB10 = 1;  // input  digital I/O


    //*************************************************************
    // Unlock Registers:
    //
    // Clear the bit 6 of OSCCONL to unlock Pin Re-map
    //
    //*************************************************************
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    //*************************************************************

    _U1RXR = 10;  // UART1 RX mapped onto RP10
    _RP11R = 3;   // UART1 TX mapped onto RP11

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
//    Function:       InitUART1Module
//    Description:    Configures UART1 Module
//
//    Note: The initialization function does NOT configure the UART1 I/O pins
//
//*******************************************************************************
void InitUART1Module(void)
{
    U1MODEbits.UARTEN = 0;	// Bit15 TX, RX DISABLED, ENABLE at end of func
    //U1MODEbits.notimplemented;	// Bit14
    U1MODEbits.USIDL = 0;	// Bit13 Continue in Idle
    U1MODEbits.IREN = 0;	// Bit12 No IR translation
    U1MODEbits.RTSMD = 0;	// Bit11 Simplex Mode
    //U1MODEbits.notimplemented;	// Bit10
    U1MODEbits.UEN = 0;		// Bits8,9 TX,RX enabled, CTS,RTS not
    U1MODEbits.WAKE = 0;	// Bit7 No Wake up (since we don't sleep here)
    U1MODEbits.LPBACK = 0;	// Bit6 No Loop Back
    U1MODEbits.ABAUD = 0;	// Bit5 No Autobaud (would require sending '55')
    U1MODEbits.URXINV = 0;	// Bit4 IdleState = 1  (for dsPIC)
    U1MODEbits.BRGH = 0;	// Bit3 16 clocks per bit period
    //U1MODEbits.BRGH = 1;	// Bit3 4 clocks per bit period
    U1MODEbits.PDSEL = 0;	// Bits1,2 8bit, No Parity
    U1MODEbits.STSEL = 0;	// Bit0 One Stop Bit

    // Load a value into Baud Rate Generator.  Example is for 9600.
    // See section 19.3.1 of datasheet.
    //  U1BRG = (3685000/(16*BaudRate))-1
    //  U1BRG = (3685000/(16*9600))-1
    //  U1BRG = 23

    //U1BRG = (((FCY/(UART1_BAUDRATE*16)-1);	// BAUD Rate Setting of Uart1
    U1BRG = 11;  // (7370000/2)/(19200*16)-1) = 10.9954 ~~ 11

    // Load all values in for U1STA SFR
    U1STAbits.UTXISEL1 = 0;	//Bit15 Int when Char is transferred (1/2 config!)
    U1STAbits.UTXINV = 0;	//Bit14 N/A, IRDA config
    U1STAbits.UTXISEL0 = 0;	//Bit13 Other half of Bit15
    //U1STAbits.notimplemented = 0;	//Bit12
    U1STAbits.UTXBRK = 0;	//Bit11 Disabled
    U1STAbits.UTXEN = 0;	//Bit10 TX pins controlled by periph
    U1STAbits.UTXBF = 0;	//Bit9 *Read Only Bit*
    U1STAbits.TRMT = 0;	//Bit8 *Read Only bit*
    U1STAbits.URXISEL = 0;	//Bits6,7 Int. on character recieved
    U1STAbits.ADDEN = 0;	//Bit5 Address Detect Disabled
    U1STAbits.RIDLE = 0;	//Bit4 *Read Only Bit*
    U1STAbits.PERR = 0;		//Bit3 *Read Only Bit*
    U1STAbits.FERR = 0;		//Bit2 *Read Only Bit*
    U1STAbits.OERR = 0;		//Bit1 *Read Only Bit*
    U1STAbits.URXDA = 0;	//Bit0 *Read Only Bit*

//    _U1RXIP = 4;// Mid Range Interrupt Priority level, no urgent reason
//    _U1TXIP = 4;// Mid Range Interrupt Priority level, no urgent reason

    IFS0bits.U1TXIF = 0;	// Clear the Transmit Interrupt Flag
    IEC0bits.U1TXIE = 1;	// Enable Transmit Interrupts
    IFS0bits.U1RXIF = 0;	// Clear the Recieve Interrupt Flag
    IEC0bits.U1RXIE = 1;	// Enable Recieve Interrupts

    U1MODEbits.UARTEN = 1;	// And turn the peripheral on

    U1STAbits.UTXEN = 1;
}
//*******************************************************************************




//*******************************************************************************
//
//    Function:       ClearUART1IndexPointer
//    Description:    Reset UART1 Index Pointer in preparation for new incoming
//                     data on UART1 RX pin.
//
//*******************************************************************************
void ClearUART1IndexPointer(void)
{
    UART1Index = 0;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       GetUART1IndexPointerValue
//    Description:    Return current UART1 Index Pointer value
//
//*******************************************************************************
unsigned int GetUART1IndexPointerValue(void)
{
    return UART1Index;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       GetUART1BufferPointer
//    Description:    Return UART1 Buffer Pointer Address
//
//*******************************************************************************
unsigned char * GetUART1BufferPointer(void)
{
    return UARTBuffer;
}
//*******************************************************************************



//*******************************************************************************
//
//    Function:       UART1 RX ISR
//    Description:    Handles interrupts caused by UART1 RX module.
//                    Used to store incoming byte into a buffer in RAM.  The
//                     ISR will also increment the UART1Index which indicates
//                     how many bytes have been received since last clearing
//                     the buffer.
//
//                     Note: This is NOT a circular buffer implementation...
//
//*******************************************************************************
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    UARTBuffer[UART1Index] = U1RXREG; // Retrieving UART char from HW RX buffer

    UART1Index++;  // Incrementing the index pointer

    _U1RXIF = 0;  // Clear the UART Rx Interrupt Flag
}
//*******************************************************************************

//*******************************************************************************
//
//    Function:       UART1 TX ISR
//    Description:    Handles interrupts caused by UART1 TX module.
//                    Currently not used for anything since printf() is used to
//                     transmit data on the UART1 TX pin.
//  
//*******************************************************************************
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void)
{
    _U1TXIF = 0;  // Clear the UART Rx Interrupt Flag
}
//*******************************************************************************



