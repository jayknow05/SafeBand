#include <xc.h>
#include "ms5541.h"
#include "spi.h"
#include <stdint.h>
#include <string.h>

unsigned int c1 = 2319;
unsigned int c2 = 4864;
unsigned int c3 = 349;
unsigned int c4 = 219;
unsigned int c5 = 2002;
unsigned int c6 = 51;

int read_register(char address, char length, const long * data)
{
    return 1;
}

void init_pressure_sensor(void)
{
    uint16_t word1;
    uint16_t word2;
    uint16_t word3;
    uint16_t word4;
    char data[2];
    int i;
    
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0b1110);
    spi_transfer(0b10101000);
    SPI1CON1Lbits.CKE = 0;
    
    i = 100;
    while(i--)
    {
        Nop();
    }
    
    spi_transfer_block(0, data, 2);
    word1 = data[0] * 256 + data[1];
   
    
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0b1110);
    spi_transfer(0b10110000);
    SPI1CON1Lbits.CKE = 0;
    spi_transfer_block(0, data, 2);
    word2 = data[0] * 256 + data[1];
    
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0b1110);
    spi_transfer(0b11001000);
    SPI1CON1Lbits.CKE = 0;
    spi_transfer_block(0, data, 2);
    word3 = data[0] * 256 + data[1];
    
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0b1110);
    spi_transfer(0b11010000);
    SPI1CON1Lbits.CKE = 0;
    spi_transfer_block(0, data, 2);
    word4 = data[0] * 256 + data[1];
    
    c1 = ( word1 & 0b1111111111111000 ) >> 3;
    c2 = (( word1 & 0b111 ) << 10 ) + (( word2 & 0b1111111111000000 ) >> 6 );
    c3 = ( word3 & 0b1111111111000000 ) >> 6;
    c4 = (( word4 & 0b1111111110000000 ) >> 7 );
    c5 = (( word2 & 0b111111 ) << 6 ) + ( word3 & 0b111111 );
    c6 = word4 & 0b1111111;
        
}

void get_pressure_temperature(long * pressure, long * temperature)
{
    char data[2];
    int d1;
    int d2;
    int i;
    unsigned int ut1;
    long temp;
    long dT;
    int off;
    int sens;
    long press;
    int word;   
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();    
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0b1110);
    spi_transfer(0b10101000);
    SPI1CON1Lbits.CKE = 0;
    spi_transfer_block(0, data, 2);
    word = ( data[0] << 8 ) + data[1];

    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0xF4);
    spi_transfer(0x00);
    i = 50000000;
    while(i--)
    {
        Nop();
    }
    SPI1CON1Lbits.CKE = 0;
    spi_transfer_block(0, data, 2);
    d1 = ( data[0] << 8 ) + data[1];
    SPI1CON1Lbits.CKE = 1;

    spi_transfer(0xF2);
    spi_transfer(0x00);
    i = 50000000;
    while(i--)
    {
        Nop();
    }
    SPI1CON1Lbits.CKE = 0;
    spi_transfer_block(0, data, 2);
    d2 = ( data[0] << 8 ) + data[1];

    ut1 = 8*c5 + 10000;
    dT = (long)d2 - (long)ut1;
    temp = 200 + ((unsigned)( dT*(c6 + 100) ) >> 11 );

    off = c2 + (((unsigned)( c4 - 250 )*dT ) >> 12 ) + 10000;
    sens = ( (unsigned)c1 >> 1 ) + ((( c3 + 200 )*dT ) >> 13 ) + 3000;
    press = ( (unsigned)(sens * ( d1 - off )) >> 12 ) + 1000;
    
    memcpy(temperature, &temp, sizeof(long));
    memcpy(pressure, &press, sizeof(long));
}
//
//void get_pressure_temperature(void)
//{
//    char data[2];
//    int d1;
//    int d2;
//    int i;
//    unsigned int ut1;
//    long temperature;
//    long dT;
//    int off;
//    int sens;
//    long pressure;
//    int word;   
//    
//    SPI1CON1Lbits.CKE = 1;
//    spi_transfer(0b1110);
//    spi_transfer(0b10101000);
//    SPI1CON1Lbits.CKE = 0;
//    spi_transfer_block(0, data, 2);
//    word = ( data[0] << 8 ) + data[1];
//
//    SPI1CON1Lbits.CKE = 1;
//    spi_transfer(0xF4);
//    spi_transfer(0x00);
//    i = 50000000;
//    while(i--)
//    {
//        Nop();
//    }
//    SPI1CON1Lbits.CKE = 0;
//    spi_transfer_block(0, data, 2);
//    d1 = ( data[0] << 8 ) + data[1];
//    SPI1CON1Lbits.CKE = 1;
//
//    spi_transfer(0xF2);
//    spi_transfer(0x00);
//    i = 50000000;
//    while(i--)
//    {
//        Nop();
//    }
//    SPI1CON1Lbits.CKE = 0;
//    spi_transfer_block(0, data, 2);
//    d2 = ( data[0] << 8 ) + data[1];
//
//    ut1 = 8*c5 + 10000;
//    dT = (long)d2 - (long)ut1;
//    temperature = 200 + ((unsigned)( dT*(c6 + 100) ) >> 11 );
//
//    off = c2 + (((unsigned)( c4 - 250 )*dT ) >> 12 ) + 10000;
//    sens = ( (unsigned)c1 >> 1 ) + ((( c3 + 200 )*dT ) >> 13 ) + 3000;
//    pressure = ( (unsigned)(sens * ( d1 - off )) >> 12 ) + 1000;
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//}