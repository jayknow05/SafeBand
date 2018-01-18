#include <stdint.h>
#include "board.h"
#include "alarm.h"
#include "pwm.h"

uint32_t AlarmSignalFrequencies[NUM_ALARM_SEGMENTS] = ALARM_SIGNAL_FREQUENCIES;
uint32_t AlarmSignalDurations[NUM_ALARM_SEGMENTS] = ALARM_SIGNAL_DURATIONS;
uint32_t AlarmCounter = 0;
uint32_t AlarmIndex = 0;
uint32_t BackoffCounter = 0;

#define MIN_FREQUENCY 0
#define MAX_FREQUENCY 50000
#define FREQUENCY_STEP 100
uint32_t CurrentFrequency = 0;

AlarmState _AlarmState = Off;

void HandleAlarm(uint8_t shouldAlarm)
{
    if (!shouldAlarm) 
    {
        BackoffCounter++;
        if (BackoffCounter >= BACKOFF_COUNT)
        {
            _AlarmState = Off;
            LedRed_SetLow();
            LedGreen_SetLow();
            LedBlue_SetLow();
            DisablePwm();
        }
        else
        {
            LedRed_Toggle();
            LedGreen_Toggle();
            LedBlue_Toggle();
        }
    }    
    else
    {
        LedRed_Toggle();
        LedGreen_Toggle();
        LedBlue_Toggle();
        BackoffCounter = 0;
    }
    
    switch(_AlarmState)
    {
        case Init:
            BackoffCounter = 0;
            AlarmCounter = 0;
            AlarmIndex = 0;
            SetFrequency(0);
            EnablePwm();
            _AlarmState = On;
            AlarmCounter++;
            break;
        case On:
            CurrentFrequency = ( CurrentFrequency + FREQUENCY_STEP > MAX_FREQUENCY ) ? MIN_FREQUENCY : CurrentFrequency + FREQUENCY_STEP;
            SetFrequency(CurrentFrequency);
//            if (AlarmCounter >= AlarmSignalDurations[AlarmIndex])
//            {
//                AlarmIndex = ( AlarmIndex + 1 > NUM_ALARM_SEGMENTS - 1) ? 0 : AlarmIndex + 1 ;                
//                SetFrequency(AlarmSignalFrequencies[AlarmIndex]);
//                AlarmCounter = 0;
//            }
//            else
//            {
//                
//                AlarmCounter++;
//            }
            break;
        case Off:
            if (shouldAlarm) 
            {
                _AlarmState = Init;
            }
            break;
        default:
            break;
    }
}


