/* 
 * File:   lis2de12.h
 * Author: Justin
 *
 * Created on December 31, 2017, 3:30 PM
 */

#ifndef LIS2DE12_H
#define	LIS2DE12_H

#ifdef	__cplusplus
extern "C" {
#endif

#define CTRL_REG1 0x20
#define CTRL_REG2 0x21
#define CTRL_REG3 0x22
#define CTRL_REG4 0x23
#define CTRL_REG5 0x24
#define CTRL_REG6 0x25
#define REFERENCE 0x26
#define OUT_X_H 0x29
#define OUT_Y_H 0x2B
#define OUT_Z_H 0x2D
#define INT1_CFG 0x30
#define INT1_SRC 0x31
#define INT1_THS 0x32
#define INT1_DURATION 0x33
#define INT2_CFG 0x34
#define INT2_SRC 0x35
#define INT2_THS 0x36
#define INT2_DURATION 0x37
#define SLAVE_ADDRESS 0x18
    
struct ctrl_reg1 {
    union {          
        uint8_t ODR;

        struct {
            uint8_t ODR0 : 1;
            uint8_t ODR1 : 1;
            uint8_t ODR2 : 1;
            uint8_t ODR3 : 1;
        };
    };

    uint8_t LPen : 1;
    uint8_t Zen : 1;
    uint8_t Yen : 1;
    uint8_t Xen : 1;
};

void init_accelerometer(void);
uint8_t read_byte_from_address(uint8_t * byte, uint8_t address);
uint8_t write_byte_to_address(uint8_t byte, uint8_t address);
void get_accelerometer_data(double * x, double * y, double * z);

uint8_t read_sensor_id(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LIS2DE12_H */

