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

#include <stdint.h>
    
void I2cInitialize(uint32_t i2c_frequency_hz);
void SetI2cTimeout(uint32_t timeout);
uint8_t SendStartCondition(void);
uint8_t SendStopCondition(void);
uint8_t SendRestartCondition(void);
uint8_t SendByte(uint8_t byte);
uint8_t SendI2cReadAddress(uint8_t address);  
uint8_t SendI2cWriteAddress(uint8_t address);
uint8_t WaitForSlaveResponse(void);
uint8_t CheckTimeout(uint32_t timeout_counter);
uint8_t I2cWaitIdle(void);
uint8_t ReceiveByte(uint8_t * byte, uint8_t master_response);

#define I2C_ACK     1
#define I2C_NACK    0

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

