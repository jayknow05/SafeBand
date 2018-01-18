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
#define OUT_X_H 0x29
#define OUT_Y_H 0x2B
#define OUT_Z_H 0x2D
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
void read_sensor_id(void);

#ifdef	__cplusplus
}
#endif

#endif	/* LIS2DE12_H */

