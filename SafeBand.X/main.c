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
    ALARMING,            
} State;

State state;

int main(void) {
    
    init_board();
    P2V5_ON();
    uint16_t current_state = INIT;
    SetI2cTimeout(1000);
    
    while(1)
    {
        switch(current_state)
        {
            case(INIT):
                //P2V5_ON();
                pwm_init();
                init_accelerometer();
                init_pressure_sensor();
                current_state = ACQUIRING_PRESSURE;
                // GoToSleep(ACQUIRING_PRESSURE, 0);
                break;
            case(ACQUIRING_PRESSURE):
                // P2V5_ON();
                init_accelerometer();
                handle_sensors();
                
                if (check_should_alarm())
                {
                    current_state = ALARMING;
                    HandleAlarm(1);
                }
                else
                {
                    HandleAlarm(0);
                    power_down_accelerometer();
                    SleepOneWdtPeriod();
                }
                                
                
                // P2V5_OFF();
                // GoToSleep(ACQUIRING_PRESSURE, 0);
                break;
            case(ALARMING):
                handle_sensors();
                if (check_should_alarm())
                {   
                    HandleAlarm(1);
                }
                else
                {
                    if (!HandleAlarm(0))
                    {
                        current_state = ACQUIRING_PRESSURE;
                    }
                }                
                break;
            default:
                current_state = INIT;
                break;
        }   
    }
}

void __attribute__ ((interrupt, auto_psv))  _INT1Interrupt(void)
{
    uint8_t byte;
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