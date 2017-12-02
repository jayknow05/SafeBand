#include <p24FJ128GB202.h>

#include "i2c.h"
#include "board.h"

long head;

void init_i2c(void)
{   
    I2C1CONLbits.I2CEN = 0;
    I2C1CONLbits.A10M = 0;    //Using a 7 bit slave address
    I2C1CONLbits.SMEN = 1;
    I2C1CONLbits.DISSLW = 0;
    I2C1BRG = 255;         //100kHz clock
    
    TRISBbits.TRISB9 = 0;
    LATBbits.LATB9 = 0;        
    I2C1CONLbits.I2CEN = 1;
    LATBbits.LATB9 = 1;
        
    head = 0;
    
    Nop();
}

 #define I2C_WaitIdle()  do {\
                            while(I2C1CON1bits.SEN\
                               || I2C1CON1bits.PEN || I2C1CON1bits.RCEN\
                               || I2C1CON1bits.ACKEN || I2C1STATbits.TRSTAT)\
                               continue;\
                         } while (0)

void i2c_read(void)
{
    
    if (I2C1STATbits.BCL == 1)
    {
        init_i2c();
    }
   
    while(I2C1CON1bits.SEN || I2C1CON1bits.PEN || I2C1CON1bits.RCEN || I2C1CON1bits.ACKEN || I2C1STATbits.TRSTAT);
    
//    I2C1CON1bits.SEN = 1;
//    while(I2C1CON1bits.SEN);
    
    I2C_SDA1_SetHigh();
    I2C_SCL1_SetHigh();
    
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();

    I2C_SDA1_SetLow();
    
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    
    I2C_SCL1_SetLow();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    
    I2C1TRN = 0x31;    
    while(I2C1STATbits.TRSTAT);
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        LedRed_SetHigh();
        return;
    }

    I2C1TRN = 0x0F;    
    while(I2C1STATbits.TRSTAT);
    
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        LedRed_SetHigh();
    }
    
    I2C1CON1bits.RSEN = 1;
    while(I2C1CON1bits.RSEN);
    
    I2C1TRN = 0x30;
    
    while(I2C1STATbits.TRSTAT)
        ;
    
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        LedRed_SetHigh();
    }
    
    I2C1CON1bits.ACKDT = 1;
    
    I2C1CON1bits.RCEN = 1;
    while(I2C1CON1bits.RCEN);
    
    long res;
    res = I2C1RCV;
    long tmp = I2C1CON1;
    I2C1CON1bits.ACKEN = 1;
    while(I2C1CON1bits.ACKEN)	
        ;
    
    I2C1CON1bits.PEN = 1;
    while(I2C1CON1bits.PEN)	
        ;   
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
}
//void i2c_read(void)
//{
//    if (I2C1STATbits.BCL == 1)
//    {
//        init_i2c();
//    }
//   
//    while(I2C1CON1bits.SEN || I2C1CON1bits.PEN || I2C1CON1bits.RCEN || I2C1CON1bits.ACKEN || I2C1STATbits.TRSTAT);
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    LATBbits.LATB9 = 0;
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    LATBbits.LATB9 = 1;
//    I2C1CON1bits.SEN = 1;
//    while(I2C1CON1bits.SEN);
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    Nop();
//    I2C1TRN = 0x31;    
//    while(I2C1STATbits.TRSTAT);
//    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
//    {
//        LedRed_SetHigh();
//        return;
//    }
//
//    I2C1TRN = 0x0F;    
//    while(I2C1STATbits.TRSTAT);
//    
//    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
//    {
//        LedRed_SetHigh();
//    }
//    
//    I2C1CON1bits.RSEN = 1;
//    while(I2C1CON1bits.RSEN);
//    
//    I2C1TRN = 0x30;
//    
//    while(I2C1STATbits.TRSTAT)
//        ;
//    
//    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
//    {
//        LedRed_SetHigh();
//    }
//    
//    I2C1CON1bits.ACKDT = 1;
//    
//    I2C1CON1bits.RCEN = 1;
//    while(I2C1CON1bits.RCEN);
//    
//    long res;
//    res = I2C1RCV;
//    long tmp = I2C1CON1;
//    I2C1CON1bits.ACKEN = 1;
//    while(I2C1CON1bits.ACKEN)	
//        ;
//    
//    I2C1CON1bits.PEN = 1;
//    while(I2C1CON1bits.PEN)	
//        ;   
//
//}
char i2c_read_eeprom(void)
{
    I2C1CON1bits.SEN = 1;
    while(I2C1CON1bits.SEN);
    
    I2C1TRN = 0b10100000;    
    while(I2C1STATbits.TRSTAT);
    
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        return 1;
    }

    I2C1TRN = head - 16;    
    while(I2C1STATbits.TRSTAT);
    
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        return 1;
    }
    
    I2C1TRN = 0b00000000;    
    while(I2C1STATbits.TRSTAT);
    
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        return 1;
    }
    
    I2C1CON1bits.SEN = 1;
    while(I2C1CON1bits.SEN);
    
    I2C1TRN = 0b10100001;    
    while(I2C1STATbits.TRSTAT);
    
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        return 1;
    }
        
    I2C1CON1bits.ACKDT = 1;
    
    I2C1CON1bits.RCEN = 1;
    while(I2C1CON1bits.RCEN);
    
    long res;
    res = I2C1RCV;

    I2C1CON1bits.ACKEN = 1;
    while(I2C1CON1bits.ACKEN)	
        ;
    
    I2C1CON1bits.PEN = 1;
    while(I2C1CON1bits.PEN)	
        ;   

    return 1;

}

int i2c_write_eeprom(char byte)
{
    I2C1CON1bits.SEN = 1;
    while(I2C1CON1bits.SEN);
    
    I2C1TRN = 0b10100000;    
    while(I2C1STATbits.TRSTAT);
    Nop();
    Nop();
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        return 1;
    }
    
    I2C1TRN = head;    
    head += 16;
    while(I2C1STATbits.TRSTAT);
    
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        return 1;
    }
    
    I2C1TRN = 0b00000000;    
    while(I2C1STATbits.TRSTAT);
    
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        return 1;
    }
    
    I2C1TRN = byte;    
    while(I2C1STATbits.TRSTAT);
    
    if(I2C1STATbits.ACKSTAT || I2C1STATbits.BCL)
    {
        return 1;
    }

    I2C1CON1bits.PEN = 1;
    while(I2C1CON1bits.PEN)	
        ;   
    
    int i = 5000000;
    while(i--)
    {
        Nop();
    }
    
    return 0;
}