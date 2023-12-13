/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
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
  Section: Included Files
*/
#include "mcc_generated_files/mcc.h"
#ifndef FCY
#define FCY (_XTAL_FREQ / 2)
#endif
#include <libpic30.h>
#include <stdint.h>
#include "mcc_generated_files/interrupt_manager.h"

uint8_t t = 0;

// Shift register control functions
void shiftOut(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        if ((data >> (7 - i)) & 0x01) {
            DATA_SetHigh();   // Set the Data pin high
        } else {
            DATA_SetLow();    // Set the Data pin low
        }
        CLOCK_SetHigh();    // Pulse the clock pin high
        __delay_us(10);     // Short delay
        CLOCK_SetLow();     // Set the clock pin low
    }
}


void latch() {
    LATCH_SetHigh();
    __delay_us(10);
    LATCH_SetLow();
}

void writeLEDs(uint8_t data) {
    shiftOut(data);
    latch();
}

// LED patterns
void type1() {
    writeLEDs(0x00);  // All LEDs off
    __delay_ms(200);
    writeLEDs(0xFF);  // All LEDs on
    __delay_ms(200);
}
void type2() {
    uint8_t pattern = 0x00; // B?t ??u v?i t?t c? LED t?t
    // S�ng d?n t? ph?i qua tr�i
    for (uint8_t i = 0; i < 8; i++) {
        pattern |= (1 << i); // Th�m m?t LED s�ng v�o m?u
        writeLEDs(pattern);
        __delay_ms(200);
    }
    // T?t d?n t? ph?i qua tr�i
    for (uint8_t i = 0; i < 8; i++) {
        pattern &= ~(1 << i); // T?t m?t LED t? tr?ng th�i s�ng ??y ??
        writeLEDs(pattern);
        __delay_ms(200);
    }
}


void type3() {
    uint8_t pattern = 0x00; 
    
    for (uint8_t i = 0; i < 8; i++) {
        pattern |= (1 << (7 - i)); 
        writeLEDs(pattern);
        __delay_ms(200);
    }

    for (uint8_t i = 0; i < 8; i++) {
        pattern &= ~(1 << (7 - i)); 
        writeLEDs(pattern);
        __delay_ms(200);
    }
}


void type4() {
    for (uint8_t i = 0; i < 4; i++) {
        writeLEDs((1 << i) | (1 << (7 - i)));
        __delay_ms(100);
    }
    for (uint8_t i = 0; i < 4; i++) {
        writeLEDs(~((1 << i) | (1 << (7 - i))));
        __delay_ms(100);
    }
}

void type5() {
    for (uint8_t i = 0; i < 4; i++) {
        writeLEDs((1 << (3 - i)) | (1 << (4 + i)));
        __delay_ms(100);
    }
    for (uint8_t i = 0; i < 4; i++) {
        writeLEDs(~((1 << (3 - i)) | (1 << (4 + i))));
        __delay_ms(100);
    }
}

void type6() {
    writeLEDs(0xAA);  // Alternate LEDs on (10101010)
    __delay_ms(100);
    writeLEDs(0x55);  // Alternate LEDs on (01010101)
    __delay_ms(200);
}

void type7() {
    uint8_t y = 0x01;
    for (uint8_t i = 0; i < 8; i++) {
        y |= (1 << i);
        writeLEDs(y);
        __delay_ms(200);
    }
}

void type8() {
    uint8_t y = 0x80;
    for (uint8_t i = 0; i < 8; i++) {
        y |= (0x80 >> i);
        writeLEDs(y);
        __delay_ms(200);
    }
}

void type9() {
    uint8_t y = 0xFE;
    for (uint8_t i = 0; i < 8; i++) {
        y &= ~(1 << i);
        writeLEDs(y);
        __delay_ms(200);
    }
}

void type10() {
    uint8_t y = 0x7F;
    for (uint8_t i = 0; i < 8; i++) {
        y &= ~(0x80 >> i);
        writeLEDs(y);
        __delay_ms(200);
    }
}

static void INT0_CallBack(void) {
    if (S1_GetValue() == 1) {
        t++;
        if (t == 11) t = 0;
    }
}

static void INT1_CallBack(void) {
    if (S2_GetValue() == 1) {
        t--;
        if (t == 0) t = 10;
    }
}

int main(void) {
    SYSTEM_Initialize();
    INTERRUPT_GlobalEnable();
    EXT_INT_Initialize();
    S1_SetInterruptHandler(INT0_CallBack);
    S2_SetInterruptHandler(INT1_CallBack);
    t = 0;
    while (1) {
        switch (t) 
        {
            case 1: type1(); break;
            case 2: type2(); break;
            case 3: type3(); break;
            case 4: type4(); break;
            case 5: type5(); break;
            case 6: type6(); break;
            case 7: type7(); break;
            case 8: type8(); break;
            case 9: type9(); break;
            case 10: type10(); break;
            default: break;
        }
    }
    return 1;
}

/**
 End of File
*/

