/*
 * File:   main.c
 * Author: Justin
 *
 * Created on September 20, 2017, 9:46 PM
 */

#include <xc.h>
#include <stdint.h>
#include "board.h"
#include "spi.h"
#include "pwm.h"
#include "ms5541.h"
#include "timer.h"
#include "i2c.h"
#include "eeprom.h"
#include "safeband.h"
#include "alarm.h"
#include "lis2de12.h"
#include "rtcc.h"
#include "deepsleep.h"
#include "interrupt.h"

void read_sensors(void);
typedef enum {
    INIT = 0,
    ACQUIRING_PRESSURE,
    IDLE,
            
} State;

State state;

int main(void) {
    
    // RCONbits.SWDTEN = 0;
    init_board();
    P2V5_ON();    
    uint16_t current_state = DSGPR0;
    RCON = 0;
//    if (RCONbits.POR == 1)
//    {
//        RCONbits.POR = 0;
//        RCONbits.EXTR = 0;
    current_state = IDLE; // INIT;
//    }
    
    long pressure;
    int i = 10;    
    SetI2cTimeout(1000);
    // init_interrupt();
    //clear_interrupt();
//    pwm_init();
//    EnablePwm();
//    SetFrequency(5000);
//    while(1);
    while(1)
    {
        switch(current_state)
        {
            case(INIT):
                // RCONbits.SWDTEN = 0;
                LedRed_SetHigh();
                LedGreen_SetHigh();
                LedBlue_SetHigh();
                init_accelerometer();
                P2V5_ON();
                pwm_init();
                init_pressure_sensor();
                current_state = ACQUIRING_PRESSURE;
                // RCONbits.SWDTEN = 1;
                // GoToSleep(ACQUIRING_PRESSURE, 0);
                // GoToDeepSleep(ACQUIRING_PRESSURE, 0);
                break;
            case(ACQUIRING_PRESSURE):
                
                LedRed_SetLow();
                LedGreen_SetLow();
                LedBlue_SetLow();
                //P2V5_ON();
                init_accelerometer();
                handle_sensors();
                HandleAlarm( check_should_alarm() );
                //GoToDeepSleep(ACQUIRING_PRESSURE, 0);
                power_down_accelerometer();
                //P2V5_OFF();
                //GoToSleep(ACQUIRING_PRESSURE, 0);
                break;
            case(IDLE):
                break;
            default:
                current_state = INIT;
                //LedGreen_SetHigh();
                // GoToDeepSleep(current_state, 0);
                break;
        }    
        HandleAlarm(1);//ClrWdt();
    }
}

void __attribute__ ((interrupt, auto_psv))  _INT1Interrupt(void)
{
    uint8_t byte;
    // write_byte_to_address(0x2A, INT1_CFG);
    _INT1IF = 0;
    
    read_byte_from_address(&byte, REFERENCE);
    
    read_byte_from_address(&byte, INT1_SRC);
    read_byte_from_address(&byte, INT2_SRC);
    write_byte_to_address(0x2A, INT1_CFG);
    write_byte_to_address(0x2A, INT2_CFG);
};

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void)
{
    /* Interrupt Service Routine code goes here */
    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
}