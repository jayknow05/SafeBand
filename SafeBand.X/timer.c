#include "timer.h"
#include <xc.h>

void init_timer(void)
{
    /* The following code example will enable Timer1 interrupts, load the Timer1
    Period register and start Timer1.
    When a Timer1 period match interrupt occurs, the interrupt service
    routine must clear the Timer1 interrupt status flag in software.
    */
    CLKDIVbits.RCDIV = 0x100;
    T1CON = 0x00; //Stops the Timer1 and reset control reg.
    TMR1 = 15550; //Clear contents of the timer register
    PR1 = 0xFFFF; //Load the Period register with the value 0xFFFF
    IPC0bits.T1IP = 0x01; //Setup Timer1 interrupt for desired priority level
    T1CONbits.TCKPS = 0;
    IFS0bits.T1IF = 0; //Clear the Timer1 interrupt status flag
    IEC0bits.T1IE = 1; //Enable Timer1 interrupts
    T1CONbits.TON = 0x11; //Start Timer1 with prescaler settings at 1:1 and
    //clock source set to the internal instruction cycle
    /* Example code for Timer1 ISR*/
}
