/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.4
        Device            :  dsPIC33CK256MP508
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/


/**
    Section: Includes
*/

#include <xc.h>
#include <stdio.h>
#include "pin_manager.h"

/**
 Section: File specific functions
*/
void (*S1_InterruptHandler)(void) = NULL;
void (*S2_InterruptHandler)(void) = NULL;

/**
 Section: Driver Interface Function Definitions
*/
void PIN_MANAGER_Initialize (void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATA = 0x0000;
    LATB = 0x0000;
    LATC = 0x0000;
    LATD = 0x0000;
    LATE = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISA = 0x001F;
    TRISB = 0xFFFD;
    TRISC = 0xFFFF;
    TRISD = 0xFF78;
    TRISE = 0xFFFF;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPDA = 0x0000;
    CNPDB = 0x0000;
    CNPDC = 0x0000;
    CNPDD = 0x0000;
    CNPDE = 0x0000;
    CNPUA = 0x0000;
    CNPUB = 0x0000;
    CNPUC = 0x0000;
    CNPUD = 0x00F8;
    CNPUE = 0x6000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCA = 0x0000;
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;
    ODCE = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    ANSELA = 0x001F;
    ANSELB = 0x0099;
    ANSELC = 0x00CF;
    ANSELD = 0x2C00;
    ANSELE = 0x000F;
    
    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_RPCON(0x0000); // unlock PPS

    RPINR0bits.INT1R = 0x003A;    //RC10->EXT_INT:INT1

    __builtin_write_RPCON(0x0800); // lock PPS
    
    /****************************************************************************
     * Interrupt On Change: positive
     ***************************************************************************/
    CNEN0Ebits.CNEN0E7 = 1;    //Pin : RE7
    CNEN0Ebits.CNEN0E8 = 1;    //Pin : RE8
    /****************************************************************************
     * Interrupt On Change: flag
     ***************************************************************************/
    CNFEbits.CNFE7 = 0;    //Pin : RE7
    CNFEbits.CNFE8 = 0;    //Pin : RE8
    /****************************************************************************
     * Interrupt On Change: config
     ***************************************************************************/
    CNCONEbits.CNSTYLE = 1;    //Config for PORTE
    CNCONEbits.ON = 1;    //Config for PORTE
    
    /* Initialize IOC Interrupt Handler*/
    S1_SetInterruptHandler(&S1_CallBack);
    S2_SetInterruptHandler(&S2_CallBack);
    
    /****************************************************************************
     * Interrupt On Change: Interrupt Enable
     ***************************************************************************/
    IFS4bits.CNEIF = 0; //Clear CNEI interrupt flag
    IEC4bits.CNEIE = 1; //Enable CNEI interrupt
}

void __attribute__ ((weak)) S1_CallBack(void)
{

}

void __attribute__ ((weak)) S2_CallBack(void)
{

}

void S1_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC4bits.CNEIE = 0; //Disable CNEI interrupt
    S1_InterruptHandler = InterruptHandler; 
    IEC4bits.CNEIE = 1; //Enable CNEI interrupt
}

void S1_SetIOCInterruptHandler(void *handler)
{ 
    S1_SetInterruptHandler(handler);
}

void S2_SetInterruptHandler(void (* InterruptHandler)(void))
{ 
    IEC4bits.CNEIE = 0; //Disable CNEI interrupt
    S2_InterruptHandler = InterruptHandler; 
    IEC4bits.CNEIE = 1; //Enable CNEI interrupt
}

void S2_SetIOCInterruptHandler(void *handler)
{ 
    S2_SetInterruptHandler(handler);
}

/* Interrupt service routine for the CNEI interrupt. */
void __attribute__ (( interrupt, no_auto_psv, context )) _CNEInterrupt ( void )
{
    if(IFS4bits.CNEIF == 1)
    {
        if(CNFEbits.CNFE7 == 1)
        {
            if(S1_InterruptHandler) 
            { 
                S1_InterruptHandler(); 
            }
            
            CNFEbits.CNFE7 = 0;  //Clear flag for Pin - RE7

        }
        
        if(CNFEbits.CNFE8 == 1)
        {
            if(S2_InterruptHandler) 
            { 
                S2_InterruptHandler(); 
            }
            
            CNFEbits.CNFE8 = 0;  //Clear flag for Pin - RE8

        }
        
        
        // Clear the flag
        IFS4bits.CNEIF = 0;
    }
}

