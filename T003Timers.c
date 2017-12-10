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
    INTCONbits.TMR0IE = 1; // Enable timer 0 interrupt
    INTCONbits.PEIE_GIEL = 1; // Enable peripheral interrupts, for other timers
    
    while(1){
        // Open Tiimer 0 when pressing a button
        if(BUT_1 != 1){
            __delay_ms(300);
        }        
    }    
}

void interrupt ISR(void){
    
    if (TMR0IF && TMR0IE){
        return; // Useful when dealing with many interrupt's sources
    }
}

