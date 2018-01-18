#include <xc.h>
#include <stdint.h>
#include "i2c.h"
#include "lis2de12.h"

struct ctrl_reg1;

void init_accelerometer(void)
{
//    ctrl_reg1.ODR = 0b1001;
//    ctrl_reg1.LPen = 1;
//    ctrl_reg1.Zen = 1;
//    ctrl_reg1.Yen = 1;
//    ctrl_reg1.Xen = 1;
    
    write_byte_to_address(0b10011111, CTRL_REG1);
    
}

uint8_t read_byte_from_address(uint8_t * byte, uint8_t address)
{
    uint8_t err = 0;
    
    err = SendStartCondition();
    err = SendI2cWriteAddress(SLAVE_ADDRESS);
    err = SendByte(address);
    err = SendRestartCondition();
    err = SendI2cReadAddress(SLAVE_ADDRESS);
    err = ReceiveByte(byte, 0);
    
    return err;
}

uint8_t write_byte_to_address(uint8_t byte, uint8_t address)
{
    uint8_t err = 0;
    
    err = SendStartCondition();
    err = SendI2cWriteAddress(SLAVE_ADDRESS);
    err = SendByte(address);
    err = SendByte(byte);
    err = SendStopCondition();  
    
    return err;
}

void read_sensor_id(void)
{
    uint8_t byte;
    Nop();
    uint8_t err = 0;
    err = SendStartCondition();
    err = SendI2cWriteAddress(0x18);
    err = SendByte(0x0F);
    err = SendRestartCondition();
    err = SendI2cReadAddress(0x18);
    err = ReceiveByte(&byte, 0);
}
