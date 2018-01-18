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

void read_sensors(void);

int main(void) {

    init_board();
    pwm_init();
    // P2V5_ON();
    // init_pressure_sensor(); // Reading calibration is still broken! Only works with sample calibration factors.
    // init_timer();
    SetI2cTimeout(1000);

    LedRed_SetLow();
    LedBlue_SetLow();
    LedGreen_SetLow();
    uint8_t tmp[64];
    int i = 0;
//    for (i = 0; i<64; i++)
//    {
//        tmp[i] = i+5;
//    }
    //WriteEeprom(&tmp, 64, 0);
    //memset(tmp, 0x00, 256);
    uint8_t res[5];
    init_accelerometer();
    uint8_t b;
    read_byte_from_address(&b, OUT_Y_H);
    double ret = ((double)b * 15.6)/1000;
    Nop();
    while(1)
    {
        read_byte_from_address(&b, OUT_Y_H);
        ret = ((double)b * 15.6)/1000;
//        ReadByteEeprom(&res[0], 0);
//        ReadByteEeprom(&res[1], 1);
//        ReadByteEeprom(&res[2], 2);
    }    
}

void __attribute__((__interrupt__, __shadow__)) _T1Interrupt(void)
{
    /* Interrupt Service Routine code goes here */
    IFS0bits.T1IF = 0; //Reset Timer1 interrupt flag and Return from ISR
    handle_sensors();
    HandleAlarm(check_should_alarm() );
}
