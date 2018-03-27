/*
 * File:   Main.c
 * Author: Brandon Kingman - Modified from Yves Losier
 *
 * Created on September 23, 2014, 11:52 PM
 * Senior Project 2017/2018
 *
 * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author		Date      	Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Y. Losier            23/09/14        First release of source file
 * B.Kingman            01/01/18        Senior Design test Code
 * ADDITIONAL NOTES:
 *
 */


/* Device header file */
#if defined(__dsPIC33E__)
#include <p33Exxxx.h>
#elif defined(__dsPIC33F__)
#include <p33Fxxxx.h>
#endif

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xc.h>
#include <libpic30.h>

#include "ConfigDevice.h"  // Device Specific Configuration (Generic I/O, etc)
#include "Timer1.h"        // Timer1 Hardware Module Configuration
#include "Timer2.h"        // Timer1 Hardware Module Configuration
#include "Timer3.h"        // Timer1 Hardware Module Configuration
#include "Timer4.h"        // Timer4 Hardware Module Configuration
#include "UART1.h"         // UART Hardware Module Configuration
#include "ADC1.h"          // ADC1 Hardware Module Configuration
#include "OC.h"            // Output Comparator Hardware Module Configuration
#include <qei.h>



/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/
char speed = 50;
char dirtoggle = 1;
char HomePosition = 0;
char inc = 2;
char baseStepConvert = 43; //base step conversion
//char  baseStepConvert = 36; //Shoulder step conversion
//char baseStepConvert = 36; //elbow step conversion
unsigned char data = 0;
char dataFlag = 0;
int posCountOffset = 10000;
int baseStep;
char safeRange = 10;

// PID controller
double Kp = 5; //base - 5, Shoulder/elbow - 3
double Ki = 0;
double Kd = 0;
float lastError = 0;
int16_t error = 0;
int16_t changeError = 0;
int32_t totalError = 0;
float pidTerm = 0;
float pidTermScaled = 0;
int8_t pidDir = 0;

void PIDcalculation(){
    error = (baseStep - POSCNT);
    changeError = (error - lastError);
    totalError += error;
    pidTerm = (Kp*error) + (Ki*totalError) + (Kd * changeError);
    
    
    if (pidTerm > 0)
    {
        pidDir  = 1;
    }
    else
    {
        pidDir  = -1;
    }
    
    if (pidTerm < 0)
    {
        pidTerm = -1*pidTerm;
    }
    
    if (pidTerm > 100){  //saturate the values to maximum pwm 
        pidTerm = 100;
    }
    lastError = error;
}

//typedef struct SPid
//{
//    float derState; // Last position input
//    float integratState; // Integrator state
//    float integratMax; // Maximum and minimum
//    float integratMin; // allowable integrator state
//    float integratGain; // integral gain
//    float propGain; // proportional gain
//    float derGain; // derivative gain
//};
//
//double UpdatePID;
//UpdatePID(SPid *pid, error, POSCNT) {
//    float pTerm, dTerm, iTerm;
//    pTerm = pid->propGain * error; // calculate the proportional term
//    // calculate the integral state with appropriate limiting
//    pid->integratState += error;
//    // Limit the integrator state if necessary
//    if (pid->integratState > pid->integratMax) {
//        pid->integratState = pid->integratMax;
//    } else if (pid->integratState < pid->integratMin) {
//        pid->integratState = pid->integratMin;
//    }
//    // calculate the integral term
//    iTerm = pid->integratGain * pid->integratState;
//    // calculate the derivative
//    dTerm = pid->derGain * (pid->derState - POSCNT);
//    pid->derState = POSCNT;
//    return pTerm + dTerm + iTerm;
//}



unsigned char* uartBufferPtr;
char uartIndex;

//float count = 0;
/******************************************************************************/
/* Main Program                                                               */

/******************************************************************************/
int16_t main(void) {
    unsigned int baudRate; // local variable used to simply store the calculated baudrate

    /* Configure the oscillator for the device */
    ConfigureOscillator();
    /* Initialize (non-hardware specific) IO ports */
    InitDevice();
    LED0_OFF();
    //ENABLE_ON();
    IN1_OFF();
    IN2_ON();

    InitTimer1();
    StartTimer1();

    InitTimer2();
    StartTimer2();

    InitTimer3();
    StartTimer3();

    InitTimer4();
    StartTimer4();


    InitUART1Pins();
    InitUART1Module();

    baudRate = FCY / ((U1BRG + 1)*16); // baud rate of Uart1

    InitADC1Pins();
    InitADC1Module();

    InitOC1Pin();
    SetOC1AsPWM();

    //InitOC2Pin(); //Setting up PWM pins
    // SetOC2AsPWM();

    // InitOC3Pin();
    //SetOC3AsPulse();

    // InitOC4Pin();
    // SetOC4AsPulse();

    _TRISB8 = 1;
    _TRISB9 = 1; //PIN 17,18 as digital inputs

    // To use pins 17 and 18 as QEA and QEB (quadrature encoding inputs) 

    //*******************
    //Unlock Registers:
    //
    //Clear the bit 6 of OSCCONL to unlock pin Re-map
    //
    //********************
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    //*******


  
    _QEA1R = 8; //Mapping QEA1 to pin 17
    _QEB1R = 9; //Mapping QEB1 to pin 18
    //*******************
    //Lock Registers:
    //
    //Set the bit 6 of OSCCONL to lock pin Re-map
    //
    //********************
    __builtin_write_OSCCONL(OSCCON & 0x40);
    //*******

    // Enable the QEI module (x4 mode with POSCNT reset by MAXCNT match)
    _QEIM = 0b111;

    //Digital filtering on the lines to help with any potential noise..... YGL
    DFLT1CONbits.QEOUT = 1;
    DFLT1CONbits.QECK = 7;

    uartBufferPtr = GetUART1BufferPointer();

   
    while (1) {
        if (HomePosition == 0) {
            if (MICROSTICK_LIMSW_PIN == 1 && HomePosition == 0) {
                SetPWM1DutyCycle(speed);
                dirtoggle = 0;
                if (GetTimer4FlagValue() == 1) {// Print current value of position counter register  0.05sec there is an interrupt
                    //count = count + 1;
                    printf("POSCNT = %d\n", POSCNT);
                    if (speed < 100) {
                        speed = speed + inc;
                    }
                    // LED Toggle
                    ClearTimer4FlagValue();
                }

            } else if (MICROSTICK_LIMSW_PIN == 0 && HomePosition == 0) {
                IN1_OFF();
                IN2_OFF();
                HomePosition = 1;
                POSCNT = posCountOffset;
                LED0_TOGGLE();
                printf("Scorbot Base at home position, POSCNT set to: %d\n", POSCNT);
                __delay32(300000); //(int * seconds *fcy) fcy = 3685000 -> therefore  delay = 100ms
                speed = 0;
            }
            
        } else if (HomePosition == 1) {
            uartIndex = GetUART1IndexPointerValue();

            if (uartIndex > 0) {
                data = *(uartBufferPtr + (uartIndex - 1));
                ClearUART1IndexPointer();
                LED0_TOGGLE();
                dataFlag = 1;
            }

            baseStep = ((uint16_t)data * (uint16_t)baseStepConvert) + posCountOffset; //pos request in Degrees converting to steps
            if (baseStep == 0) {
                LED0_TOGGLE();
                __delay32(300000);
            }
            if ((baseStep != POSCNT)&&(dataFlag == 1)) {
                PIDcalculation();
                speed = pidTerm;
                
                        
               // printf("baseStep data PODCNT: %d %d %d\r\n", baseStep, data, POSCNT);
                if ((error > safeRange) || (error < -safeRange)) {
                    
                    if (pidDir == 1)
                    {
                        IN1_ON();
                        IN2_OFF();                   
                        SetPWM1DutyCycle(speed);
                        printf("1 dir, baseStep, POSCNT, error, pidTerm %d %d %d %d\r\n", baseStep, POSCNT, error, speed);  
                    }
                    else if (pidDir == -1)
                    {
                        IN1_OFF();
                        IN2_ON();                   
                        SetPWM1DutyCycle(speed);
                        printf("-1 dir, baseStep, POSCNT, error, pidTerm %d %d %d %d\r\n", baseStep, POSCNT, error, speed);  
                    }      
                }
//                 else if (error < -safeRange) {
//
//                    if (pidDir == 1)
//                    {
//                        IN1_ON();
//                        IN2_OFF();                   
//                        SetPWM1DutyCycle(speed);
//                    }
//                    else if (pidDir == -1)
//                    {
//                        IN1_OFF();
//                        IN2_ON();                   
//                        SetPWM1DutyCycle(speed);
//                    }
//                                        
//                    printf("Loop < 0, baseStep, POSCNT, error, pidTerm %d %d %d %d\r\n", baseStep, POSCNT, error, speed);
//                }
                else if ((error < safeRange) && (error > -safeRange) ) {
                    IN1_ON();
                    IN2_ON();
                    printf("Scorbot base at requested Degree - Error %d %d\n", data, error);
                    dataFlag = 0;
                }
            }
        }
    }

}


