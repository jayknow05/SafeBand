/* 
 * File:   config.h
 * Author: Justin
 *
 * Created on December 2, 2017, 12:46 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#define PWM_FREQUENCY 32000
#define ALARM_FREQUENCY 4000
#define I2C_FREQUENCY 100000
#define PRESSURE_BUFFER_SIZE 20
#define ACCELEROMETER_BUFFER_SIZE 20

#define NUM_SECONDS_BEFORE_ALARM 2
#define SENSOR_SAMPLE_RATE 1
#define ALARM_AVERAGE_MOVEMENT_THRESHOLD 14

#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

