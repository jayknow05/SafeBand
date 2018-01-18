#include <math.h>
#include "safeband.h"
#include "ms5541.h"
#include "config.h"

#define ABS(x) ((x) > 0 ? (x) : -(x)) 

long pressure_buffer[PRESSURE_BUFFER_SIZE];
long pressure_rate_of_change_buffer[PRESSURE_BUFFER_SIZE];
long buffer_index = 0;
float _InitialPressure;

void handle_sensors(void)
{   
    get_pressure(&pressure_buffer[buffer_index]);
    calculate_rate_of_change((long int *)&pressure_buffer, (long int *)&pressure_rate_of_change_buffer, buffer_index);
    buffer_index = (buffer_index + 1 + PRESSURE_BUFFER_SIZE) % PRESSURE_BUFFER_SIZE;
}

uint8_t calculate_rate_of_change(long * input_buffer, long * output_buffer, long index)
{
    long last_index;
    last_index = (index - 1 + PRESSURE_BUFFER_SIZE) % PRESSURE_BUFFER_SIZE;
    
    output_buffer[index] = input_buffer[index] - input_buffer[last_index];
    
    return 0;
}

uint8_t check_should_alarm(void)
{
    int i = 0;
    int count = 0;
    int start_index = 0;
    int end_index = buffer_index - 1;
    float average_movement = 0;
    float average_pressure = 0;
    long sum_of_pressure = 0;
    long total_movement = 0;
    start_index = (end_index - NUM_SECONDS_BEFORE_ALARM*SENSOR_SAMPLE_RATE + PRESSURE_BUFFER_SIZE) % PRESSURE_BUFFER_SIZE;
    
    // The first few cycles will always alarm since the pressure_buffer is empty
    if ( pressure_buffer[start_index] == 0 )
    {
        return 0;
    }
    
    if (start_index < end_index)
    {
        for (i = start_index; i < end_index; i++)
        {
            sum_of_pressure += pressure_buffer[i];
            total_movement += ABS(pressure_rate_of_change_buffer[i]);
            count++;
        }
        
        average_pressure = (float)sum_of_pressure/(float)count;
        average_movement = (float)total_movement/(float)count;
    }
    else
    {
        for (i = start_index; i < PRESSURE_BUFFER_SIZE; i++)
        {
            sum_of_pressure += pressure_buffer[i];
            total_movement += ABS(pressure_rate_of_change_buffer[i]);
            count++;
        }
        
        for (i = 0; i < end_index; i++)
        {
            sum_of_pressure += pressure_buffer[i];
            total_movement += ABS(pressure_rate_of_change_buffer[i]);
            count++;
        }
        
        average_pressure = (float)sum_of_pressure/(float)count;
        average_movement = (float)total_movement/(float)count;
    }
    
    if ((average_movement < ALARM_AVERAGE_MOVEMENT_THRESHOLD) && (average_pressure > (_InitialPressure + 16)))
    {
        return 1;
    }
    
    return 0;
}


