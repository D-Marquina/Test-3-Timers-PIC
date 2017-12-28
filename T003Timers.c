/* 
 * File:   T003Timers.c
 * Author: Daniel Marquina
 *
 * Created on 9/12/17
 */

#include "T003Timers.h"

#define SPBRG_115200 42 // Refer to PIC18F4550's datasheet, page 250

unsigned int timeA, timeB, timeT;

void main(void) {
    
    // Interrupt configuration
    RCONbits.IPEN = 0; // Disable priority feature
    IPR1bits.RCIP = 0; // Set low priority, useless when IPEN = 0
    INTCONbits.GIE_GIEH = 1; // Enable global interrupts
    INTCONbits.PEIE_GIEL = 0; // Disable peripheral interrupts, for other timers
    //INTCONbits.TMR0IE = 1; // Enable timer0 interrupt, included in OpenTimer()
    
    // Serial port initialization
    OpenUSART(USART_TX_INT_OFF &
            USART_RX_INT_OFF & // Enable USART's receiver interrupt
            USART_BRGH_HIGH & 
            USART_CONT_RX & // Enables receiver in asynchronous mode
            USART_EIGHT_BIT & 
            USART_ASYNCH_MODE & 
            USART_ADDEN_OFF, SPBRG_115200);
    BAUDCONbits.BRG16 = 1; // More resolution
    
    while(1){
        // Open Timer 0 when pressing a button
        if(BUT_1 != 1){
            WriteTimer0(0x00FF);
            OpenTimer0(TIMER_INT_ON & // Enable interrupt
                    T0_16BIT & // Use 16 bit mode
                    T0_SOURCE_INT & // Use internal clock source
                    T0_PS_1_8); // Prescaler
            __delay_ms(300);
        }
        // Calculate cycles needed to read timer register
        if(BUT_2 != 1){
            timeA = ReadTimer0();
            timeB = ReadTimer0();
            timeT = timeB - timeA;
            char* pF = (char*)(&timeT);      
            for(char i = 0; i < 2; i++){
                while(BusyUSART());
                putcUSART(*(pF + i));
            }
            __delay_ms(300);
        } 
        if(BUT_4 != 1){
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

