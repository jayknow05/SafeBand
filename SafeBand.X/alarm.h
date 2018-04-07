/* 
 * File:   alarm.h
 * Author: Justin
 *
 * Created on December 15, 2017, 9:09 PM
 */

#ifndef ALARM_H
#define	ALARM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
    
#define NUM_ALARM_SEGMENTS 5
#define ALARM_SIGNAL_FREQUENCIES { 5000, 10000, 15000, 20000, 0 }
#define ALARM_SIGNAL_DURATIONS { 10, 10, 10, 10, 40 }
#define BACKOFF_COUNT 100
    
extern uint32_t AlarmSignalFrequencies[NUM_ALARM_SEGMENTS];
extern uint32_t AlarmSignalDurations[NUM_ALARM_SEGMENTS];
void HandleAlarm(uint8_t shouldAlarm);

typedef enum
{
    Init = 0,
    Off,
    On,
} AlarmState;

extern AlarmState _AlarmState;
extern uint32_t _AlarmCounter;
extern uint32_t AlarmIndex;
    
#ifdef	__cplusplus
}
#endif

#endif	/* ALARM_H */

