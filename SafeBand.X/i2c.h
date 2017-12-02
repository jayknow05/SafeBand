/* 
 * File:   i2c.h
 * Author: Justin
 *
 * Created on September 23, 2017, 2:39 PM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

void init_i2c(void);
void i2c_read(void);
char i2c_read_eeprom(void);
int i2c_write_eeprom(char byte);
extern long head;

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

