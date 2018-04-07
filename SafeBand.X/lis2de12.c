#include <xc.h>
#include <stdint.h>
#include "i2c.h"
#include "lis2de12.h"

struct ctrl_reg1;

void init_accelerometer(void)
{

    uint8_t err = 0;
    while(read_sensor_id())
        ;
    
    err = write_byte_to_address(0x5F, CTRL_REG1);
    err = write_byte_to_address(0x09, CTRL_REG2);
    err = write_byte_to_address(0x40, CTRL_REG3);
    err = write_byte_to_address(0x00, CTRL_REG4);
    err = write_byte_to_address(0x00, CTRL_REG5);
    err = write_byte_to_address(0x40, CTRL_REG6);
    err = write_byte_to_address(0x10, INT1_THS);
    err = write_byte_to_address(0x00, INT1_DURATION);
    read_byte_from_address(&err, REFERENCE);
    err = write_byte_to_address(0x2A, INT1_CFG); //0x40, INT1_CFG); //AA, INT1_CFG); // 0x95, INT1_CFG);
    err = write_byte_to_address(0x2A, INT2_CFG);
    read_byte_from_address(&err, INT1_SRC);
    read_byte_from_address(&err, INT2_SRC);
}

uint8_t read_byte_from_address(uint8_t * byte, uint8_t address)
{
    uint8_t err = 0;
    
    err = SendStartCondition();
    err = SendI2cWriteAddress(SLAVE_ADDRESS);
    err = SendByte(address);
    err = SendRestartCondition();
    err = SendI2cReadAddress(SLAVE_ADDRESS);
    err = ReceiveByte(byte, 1);
    
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

uint8_t read_sensor_id(void)
{
    uint8_t byte;
    uint8_t err = 0;

    err = SendStartCondition();
    err = SendI2cWriteAddress(0x18);
    err = SendByte(0x0F);
    err = SendRestartCondition();
    err = SendI2cReadAddress(0x18);
    err = ReceiveByte(&byte, 1);
    
    if (byte == 0x33)
    {
        return 0;
    }
    
    return 1;
}

void get_accelerometer_data(double * x, double * y, double * z)
{
    uint8_t err = 0;
    signed char b;
    double res;
    
    read_byte_from_address(&b, OUT_X_H);    
    res = (double)((signed char)b * 15.6)/1000;
    memcpy(x, &res, sizeof(double));
    
    read_byte_from_address(&b, OUT_Y_H);
    res = (double)((signed char)b * 15.6)/1000;
    memcpy(y, &res, sizeof(double));
    
    read_byte_from_address(&b, OUT_Z_H);
    res = (double)((signed char)b * 15.6)/1000;
    memcpy(z, &res, sizeof(double));
    
    return err;
}

void clear_interrupt(void)
{
    uint8_t byte;
    read_byte_from_address(&byte, INT1_SRC);
    read_byte_from_address(&byte, INT2_SRC);
}

void power_down_accelerometer(void)
{
    write_byte_to_address(0x08, CTRL_REG1);
}