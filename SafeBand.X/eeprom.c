#include <xc.h>
#include <string.h>
#include <stdint.h>
#include "i2c.h"
#include "eeprom.h"

#define EEPROM_SLAVE_ADDRESS 0b01010000

uint8_t ReadByteEeprom(uint8_t data, uint16_t start_address)
{
    uint8_t error;
    uint8_t received_byte;
    
    error = I2cWaitIdle();
    error = SendStartCondition();
    error = SendI2cWriteAddress(EEPROM_SLAVE_ADDRESS);
    
    error = SendByte( (uint8_t)(start_address >> 8) );
    error = SendByte( (uint8_t)start_address );
    
    error = SendStartCondition();
    
    error = SendI2cReadAddress(EEPROM_SLAVE_ADDRESS);
    
    error = ReceiveByte(&received_byte, I2C_NACK);
    memcpy(data, &received_byte, 1);
        
    error = SendStopCondition();
    
    return error;
    
}

uint8_t ReadEeprom(uint8_t * data, uint16_t length, uint16_t start_address)
{
    uint8_t error;
    uint8_t received_byte;
    uint16_t num_bytes_read = 0;
    
    error = I2cWaitIdle();
    
    error = SendStartCondition();
    error = SendI2cWriteAddress(EEPROM_SLAVE_ADDRESS);
    
    error = SendByte( (uint8_t)(start_address >> 8) );
    error = SendByte( (uint8_t)start_address );
    
    error = SendStartCondition();
    
    error = SendI2cReadAddress(EEPROM_SLAVE_ADDRESS);
    
    while ( num_bytes_read < (length - 1) )
    {
        error = ReceiveByte(&received_byte, I2C_ACK);
        memcpy(data + num_bytes_read, &received_byte, 1);
        num_bytes_read++;
    }
    
    error = ReceiveByte(&received_byte, I2C_NACK);
    memcpy(data + num_bytes_read, &received_byte, 1);
        
    error = SendStopCondition();
    
    return error;
    
}

uint8_t WriteEeprom(uint8_t * data, uint16_t length, uint16_t start_address)
{
    uint8_t error;
    uint8_t byte_to_send;
    uint16_t num_bytes_written = 0;
    
    error = I2cWaitIdle();
    
    error = SendStartCondition();
    error = SendI2cWriteAddress(EEPROM_SLAVE_ADDRESS);
    
    error = SendByte( (uint8_t)(start_address >> 8) );
    error = SendByte( (uint8_t)start_address );
        
    while ( num_bytes_written < length )
    {
        memcpy(&byte_to_send, data + num_bytes_written, 1);
        error = SendByte(byte_to_send);
        num_bytes_written++;
    }    

    error = SendStopCondition();
    
    return error;
    
}