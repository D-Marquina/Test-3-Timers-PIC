/* 
 * File:   T003Timers.c
 * Author: Daniel Marquina
 *
 * Created on 9/12/17
 */

#include "T003Timers.h"

void main(void) {
    
    // Interrupt configuration
    RCONbits.IPEN = 0; // Disable priority feature
    IPR1bits.RCIP = 0; // Set low priority, useless when IPEN = 0
    INTCONbits.GIE_GIEH = 1; // Enable global interrupts
    INTCONbits.PEIE_GIEL = 0; // Disable peripheral interrupts, for other timers
    //INTCONbits.TMR0IE = 1; // Enable timer 0 interrupt, included in t0open()
    
    while(1){
        // Open Tiimer 0 when pressing a button
        if(BUT_1 != 1){
            WriteTimer0(0x00FF);
            OpenTimer0(TIMER_INT_ON & // Enable interrupt
                    T0_16BIT & // Use 16 bit mode
                    T0_SOURCE_INT & // Use internal clock source
                    T0_PS_1_8); // Prescaler
            __delay_ms(300);
        }
        if(BUT_2 != 1){
            CloseTimer0();
            __delay_ms(300);
        } 
    }    
}

void interrupt ISR(void){
    
    if (TMR0IF && TMR0IE){
        if(LED_1 == 1){
            LED_1 = 0;
        }else{
            LED_1 = 1;
        }
        TMR0IF = 0;
        return; // Useful when dealing with many interrupt's sources
    }
}

