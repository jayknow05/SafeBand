/* 
 * File:   ms5541.h
 * Author: Justin
 *
 * Created on October 4, 2017, 10:36 PM
 */

#ifndef MS5541_H
#define	MS5541_H

#ifdef	__cplusplus
extern "C" {
#endif

extern unsigned int c1;
extern unsigned int c2;
extern unsigned int c3;
extern unsigned int c4;
extern unsigned int c5;
extern unsigned int c6;

int read_register(char address, char length, const long * data);
void init_pressure_sensor(void);
void get_pressure_temperature(long * pressure, long * temperature);

#ifdef	__cplusplus
}
#endif

#endif	/* MS5541_H */

