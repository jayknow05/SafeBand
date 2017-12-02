/*
 * File:   main.c
 * Author: Justin
 *
 * Created on September 20, 2017, 9:46 PM
 */

#include <xc.h>
#include "board.h"
#include "spi.h"
#include "pwm.h"
#include "ms5541.h"
#include "timer.h"
#include "i2c.h"

void read_sensors(void);

int main(void) {

    init_board();
    pwm_init();
    init_timer();
    P2V5_ON();
    init_pressure_sensor();

    Nop();
    Nop();
    LedRed_SetLow();
    LedBlue_SetLow();
    LedGreen_SetLow();
    while(1)
    {
        //i2c_read();
    }    
}

void __attribute__((__interrupt__, __shadow__)) _T1Interrupt(void)
{
    /* Interrupt Service Routine code goes here */
    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
    Nop();
    read_sensors();
}

void read_sensors(void)
{
    i2c_read();
    
    static long pressure;
    static long temperature;
    
    get_pressure_temperature(&pressure, &temperature);
    // i2c_write_eeprom(temperature);
    // i2c_read_eeprom();
    Nop();
    Nop();
    Nop();
    Nop();
    
    
}
