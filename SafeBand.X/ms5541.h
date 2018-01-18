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

extern long c1;
extern long c2;
extern long c3;
extern long c4;
extern long c5;
extern long c6;

int read_register(char address, char length, const long * data);
void init_pressure_sensor(void);
void get_pressure(long * pressure);
void reset_sensor(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MS5541_H */

