/* 
 * File:   board.h
 * Author: Justin
 *
 * Created on September 23, 2017, 10:53 AM
 */

#ifndef BOARD_H
#define	BOARD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
    
void init_board(void);
void init_oscillator(void);
void init_gpio(void);
void init_interrupt(void);

#define LEDGREEN_TRIS TRISBbits.TRISB15
#define LEDRED_TRIS TRISBbits.TRISB14
#define LEDBLUE_TRIS TRISBbits.TRISB13
#define P2V5_ENABLE_TRIS TRISBbits.TRISB7
#define I2C_SDA1_TRIS TRISBbits.TRISB9
#define I2C_SCL1_TRIS TRISBbits.TRISB8
#define SPI1_MISO_TRIS TRISBbits.TRISB2

#define LEDGREEN_LAT LATBbits.LATB15
#define LEDRED_LAT LATBbits.LATB14
#define LEDBLUE_LAT LATBbits.LATB13
#define P2V5_ENABLE_LAT LATBbits.LATB7
#define SPI1_MISO_STATE PORTBbits.RB2
#define INT2_ACCELEROMETER_STATE PORTBbits.RB4
#define INT1_ACCELEROMETER_STATE PORTAbits.RA4

#define I2C_SDA1_LAT LATBbits.LATB9
#define I2C_SCL1_LAT LATBbits.LATB8

#define LedRed_SetOutput() LEDRED_TRIS = 0
#define LedGreen_SetOutput() LEDGREEN_TRIS = 0
#define LedBlue_SetOutput() LEDBLUE_TRIS = 0
#define P2V5_Enable_SetOutput() P2V5_ENABLE_TRIS = 0
#define I2C_SDA1_SetOutput() I2C_SDA1_TRIS = 0
#define I2C_SCL1_SetOutput() I2C_SCL1_TRIS = 0
#define SPI1_MISO_SetInput() SPI1_MISO_TRIS = 1

#define LedRed_SetHigh() LEDRED_LAT = 0
#define LedGreen_SetHigh() LEDGREEN_LAT = 0
#define LedBlue_SetHigh() LEDBLUE_LAT = 0
#define P2V5_ON() P2V5_ENABLE_LAT = 1

#define LedRed_SetLow() LEDRED_LAT = 1
#define LedGreen_SetLow() LEDGREEN_LAT = 1
#define LedBlue_SetLow() LEDBLUE_LAT = 1
#define P2V5_OFF() P2V5_ENABLE_LAT = 0

#define LedRed_Toggle() LEDRED_LAT ^= 1
#define LedGreen_Toggle() LEDGREEN_LAT ^= 1
#define LedBlue_Toggle() LEDBLUE_LAT ^= 1

#define I2C_SDA1_SetLow() I2C_SDA1_LAT = 0
#define I2C_SCL1_SetLow() I2C_SCL1_LAT = 0
#define I2C_SDA1_SetHigh() I2C_SDA1_LAT = 1
#define I2C_SCL1_SetHigh() I2C_SCL1_LAT = 1

#define spi1_sclk _RP3R
#define spi1_mosi _RP1R
#define spi1_miso 2

#define CLOCK_FREQUENCY 4000000
        
#ifdef	__cplusplus
}
#endif

#endif	/* BOARD_H */

