/* 
 * File:   safeband.h
 * Author: Justin
 *
 * Created on December 9, 2017, 9:02 PM
 */

#ifndef SAFEBAND_H
#define	SAFEBAND_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>
#include "config.h"

typedef struct {
    float x[ACCELEROMETER_BUFFER_SIZE];
    float y[ACCELEROMETER_BUFFER_SIZE];
    float z[ACCELEROMETER_BUFFER_SIZE];
} AccelerometerData;    
    
extern long pressure_buffer[PRESSURE_BUFFER_SIZE];
extern long pressure_rate_of_change_buffer[PRESSURE_BUFFER_SIZE];
extern long buffer_index;
extern float _InitialPressure;
extern AccelerometerData accelerometerData;
    
uint8_t calculate_rate_of_change(long * input_buffer, long * output_buffer, long index);
void handle_sensors(void);
uint8_t check_should_alarm(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SAFEBAND_H */

