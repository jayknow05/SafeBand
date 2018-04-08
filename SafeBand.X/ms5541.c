#include <xc.h>
#include <stdint.h>
#include <string.h>
#include "ms5541.h"
#include "spi.h"
#include "safeband.h"
#include "deepsleep.h"

long c1 = 2319;
long c2 = 4864;
long c3 = 349;
long c4 = 219;
long c5 = 2002;
long c6 = 51;

void init_pressure_sensor(void)
{
    long sum_pressure = 0;
    long last_pressure = 0;
    int i = 0; 
    uint16_t word1;
    uint16_t word2;
    uint16_t word3;
    uint16_t word4;
    char data[2];
        
    reset_sensor();
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0x1D);
    spi_transfer(0x50);
    SPI1CON1Lbits.CKE = 0;
    
//    i = 100;
//    while(i--)
//    {
//        Nop();
//    }
    
    spi_transfer_block(0, data, 2);
    word1 = data[0] * 256 + data[1];   
    
    
    reset_sensor();
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0x1D);
    spi_transfer(0x60);
    SPI1CON1Lbits.CKE = 0;
    
//    i = 100;
//    while(i--)
//    {
//        Nop();
//    }
    
    spi_transfer_block(0, data, 2);
    word2 = data[0] * 256 + data[1];
            
    reset_sensor();    
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0x1D);
    spi_transfer(0x90);
    SPI1CON1Lbits.CKE = 0;
//    
//    i = 100;
//    while(i--)
//    {
//        Nop();
//    }
    
    spi_transfer_block(0, data, 2);
    word3 = data[0] * 256 + data[1];
    
    reset_sensor();
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0x1D);
    spi_transfer(0xA0);
    SPI1CON1Lbits.CKE = 0;
    
//    i = 100;
//    while(i--)
//    {
//        Nop();
//    }
//    
    spi_transfer_block(0, data, 2);
    word4 = data[0] * 256 + data[1];
    
    c1 = word1 >> 3 & 0x1FFF;
	c2 = ((word1 & 0x07) << 10) | ((word2 >> 6) & 0x03FF);
	c3 = (word3 >> 6) & 0x03FF;
	c4 = (word4 >> 7) & 0x07FF;
	c5 = ((word2 & 0x003F) << 6) | (word3 & 0x003F);
	c6 = word4 & 0x007F;

    
    get_pressure(&last_pressure);
    
    for (i = 0; i < 8; i++)
    {
        get_pressure(&last_pressure);
        sum_pressure += last_pressure;
    }
    
    _InitialPressure = (float)sum_pressure/(float)8;  

}

void get_pressure(long * pressure)
{
    char data[2];
    long d1;
    long d2;
    int i;
    long ut1;
    long temp;
    long dT;
    long off;
    long sens;
    long press;
    long word;   
    
    reset_sensor();
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0x0F);
    spi_transfer(0x40);
    i = 50000000;
    while((SPI1_MISO_STATE == 1) && (i--))
    {
        ClrWdt();
    };
    
    SPI1CON1Lbits.CKE = 0;
    spi_transfer_block(0, data, 2);
    d1 = data[0] * 256 + data[1];
    
    reset_sensor();
    SPI1CON1Lbits.CKE = 1;  
    spi_transfer(0x0F);
    spi_transfer(0x20);
    
    i = 50000000;
    while((SPI1_MISO_STATE == 1) && (i--)) 
    {
        ClrWdt();
    };
    SPI1CON1Lbits.CKE = 0;
    spi_transfer_block(0, data, 2);
    d2 = data[0] *256 + data[1];
    
    ut1 = 8*c5 + 10000;
    dT = d2 - ut1;
    temp = 200 + (dT * (c6 + 100)) / 2048;

    off = c2 + ( ( c4 - 250 )*dT ) / 4096 + 10000;
    // OFF = C2 + ( ( C4 - 250 )*dT ) / pow(2,12) + 10000;
    
    sens = ( c1 / 2 ) + ( ( c3 + 200 )*dT ) / 8192 + 3000;
    // SENS = ( C1 / 2 ) + ( ( C3 + 200 )*dT ) / pow(2,13) + 3000;
    
    press = ( sens * ( d1 - off ) ) / 4096 + 1000;
    // P =     ( SENS * ( D1 - OFF ) ) / pow(2,11) + 1000;

    memcpy(pressure, &press, sizeof(long));
}

void reset_sensor(void)
{
    SPI1CON1Lbits.CKE = 1;
    spi_transfer(0x15);
    spi_transfer(0x55);
    spi_transfer(0x40);
    SPI1CON1Lbits.CKE = 0;
    int i = 50;
    while(i--)
    {
        Nop();
    }
}