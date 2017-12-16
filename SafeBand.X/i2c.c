#include <stdint.h>
#include <string.h>
#include <xc.h>
#include "i2c.h"
#include "board.h"
#include "error.h"
#include "config.h"


uint32_t _timeout = 0;

void I2cInitialize(uint32_t i2c_frequency_hz)
{   
    I2C1CONLbits.I2CEN = 0;
    I2C1CONLbits.A10M = 0;    //Using a 7 bit slave address
    I2C1CONLbits.SMEN = 1;
    I2C1CONLbits.DISSLW = 0;
    I2C1BRG = CLOCK_FREQUENCY/i2c_frequency_hz - 2;
    I2C1CONLbits.I2CEN = 1;  
    
    return;
}

void SetI2cTimeout(uint32_t timeout)
{
    _timeout = timeout;
   
    return;
}

uint8_t SendStartCondition(void)
{
    uint32_t timeout_counter = _timeout;
    
    I2C1CON1bits.SEN = 1;
    while( I2C1CON1bits.SEN && (timeout_counter-- || !_timeout) );
    
    if(I2C1STATbits.BCL)
    {
        return ERROR_BUS_COLLISION;
    }
    
    if(CheckTimeout(timeout_counter))
    {
        return ERROR_TIMEOUT;
    }
    else
    {
        return SUCCESS;
    }
}

uint8_t SendStopCondition(void)
{
    uint32_t timeout_counter = _timeout;
    
    I2C1CON1bits.PEN = 1;
    while( I2C1CON1bits.PEN && (timeout_counter-- || !_timeout) );
    
    if(CheckTimeout(timeout_counter))
    {
        return ERROR_TIMEOUT;
    }
    else
    {
        return SUCCESS;
    }
}

uint8_t SendRestartCondition(void)
{
    uint32_t timeout_counter = _timeout;
    
    I2C1CON1bits.RSEN = 1;
    while( I2C1CON1bits.RSEN && (timeout_counter-- || !_timeout) );
    
    if(CheckTimeout(timeout_counter))
    {
        return ERROR_TIMEOUT;
    }
    else
    {
        return SUCCESS;
    }
}

uint8_t SendByte(uint8_t byte)
{
    I2C1TRN = byte;
    return WaitForSlaveResponse();    
}

uint8_t SendI2cReadAddress(uint8_t address)
{
    return SendByte( ( address << 1 ) | 1 );
}

uint8_t SendI2cWriteAddress(uint8_t address)
{
    return SendByte( address << 1 );
}

uint8_t WaitForSlaveResponse(void)
{
    uint32_t timeout_counter = _timeout;
    
    while( I2C1STATbits.TRSTAT && (timeout_counter-- || !_timeout) );
    
    if(CheckTimeout(timeout_counter))
    {
        return ERROR_TIMEOUT;
    }
    
    if(I2C1STATbits.ACKSTAT)
    {
        return ERROR_SLAVE_NACK;
    }
    else if(I2C1STATbits.BCL)
    {
        return ERROR_BUS_COLLISION;
    }
    
    return SUCCESS;
}

uint8_t CheckTimeout(uint32_t timeout_counter)
{   
    if ( (timeout_counter == 0) && _timeout )
    {
        return ERROR_TIMEOUT;
    }

    return SUCCESS;
}

uint8_t I2cWaitIdle(void)
{
    uint32_t timeout_counter = _timeout;
    
    if( I2C1STATbits.BCL )
    {
        I2cInitialize(I2C_FREQUENCY);
    }
    
    while(( I2C1CON1bits.SEN || 
            I2C1CON1bits.PEN || 
            I2C1CON1bits.RCEN || 
            I2C1CON1bits.ACKEN ||
            I2C1STATbits.TRSTAT )  && ( timeout_counter-- || !_timeout ));
    
    if(CheckTimeout(timeout_counter))
    {
        return ERROR_TIMEOUT;
    }
    
    return SUCCESS;
}

uint8_t ReceiveByte(uint8_t * byte, uint8_t master_response)
{
    uint32_t timeout_counter = _timeout;
    uint8_t received_byte;        
    I2C1CON1bits.ACKDT = master_response;    
    I2C1CON1bits.RCEN = 1;
    
    while( I2C1CON1bits.RCEN && (timeout_counter-- || !_timeout) );
    
    if(CheckTimeout(timeout_counter))
    {
        return ERROR_TIMEOUT;
    }
    
    timeout_counter = _timeout;
    
    received_byte = I2C1RCV;
    memcpy(byte, &received_byte, 1);
    
    I2C1CON1bits.ACKEN = 1;
    while(I2C1CON1bits.ACKEN && (timeout_counter-- || !_timeout) );
    
    if(CheckTimeout(timeout_counter))
    {
        return ERROR_TIMEOUT;
    }
    
    return SUCCESS;
}