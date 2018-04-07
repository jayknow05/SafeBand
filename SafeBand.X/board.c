
// PIC24FJ128GB202 Configuration Bit Settings

// 'C' source line config statements

// CONFIG4
#pragma config DSWDTPS = DSWDTPSA       // Deep Sleep Watchdog Timer Postscale Select bits (1:32768 (1.057 Secs))
#pragma config DSWDTOSC = LPRC          // DSWDT Reference Clock Select (DSWDT uses LPRC as reference clock)
#pragma config DSBOREN = ON             // Deep Sleep BOR Enable bit (DSBOR Enabled)
#pragma config DSWDTEN = ON             // Deep Sleep Watchdog Timer Enable (DSWDT Enabled)
#pragma config DSSWEN = ON              // DSEN Bit Enable (Deep Sleep is controlled by the register bit DSEN)
#pragma config PLLDIV = DISABLED        // USB 96 MHz PLL Prescaler Select bits (PLL Disabled)
#pragma config I2C1SEL = DISABLE        // Alternate I2C1 enable bit (I2C1 uses SCL1 and SDA1 pins)
#pragma config IOL1WAY = OFF            // PPS IOLOCK Set Only Once Enable bit (The IOLOCK bit can be set and cleared using the unlock sequence)

// CONFIG3
#pragma config WPFP = WPFP127           // Write Protection Flash Page Segment Boundary (Page 127 (0x1FC00))
#pragma config SOSCSEL = OFF            // SOSC Selection bits (Digital (SCLKI) mode)
#pragma config WDTWIN = PS25_0          // Window Mode Watchdog Timer Window Width Select (Watch Dog Timer Window Width is 25 percent)
#pragma config PLLSS = PLL_PRI          // PLL Secondary Selection Configuration bit (PLL is fed by the Primary oscillator)
#pragma config BOREN = OFF              // Brown-out Reset Enable (Brown-out Reset Disabled)
#pragma config WPDIS = WPDIS            // Segment Write Protection Disable (Disabled)
#pragma config WPCFG = WPCFGDIS         // Write Protect Configuration Page Select (Disabled)
#pragma config WPEND = WPENDMEM         // Segment Write Protection End Page Select (Write Protect from WPFP to the last page of memory)

// CONFIG2
#pragma config POSCMD = HS              // Primary Oscillator Select (HS Oscillator Enabled)
#pragma config WDTCLK = LPRC            // WDT Clock Source Select bits (WDT uses LPRC)
#pragma config OSCIOFCN = ON            // OSCO Pin Configuration (OSCO/CLKO/RA3 functions as port I/O (RA3))
#pragma config FCKSM = CSDCMD           // Clock Switching and Fail-Safe Clock Monitor Configuration bits (Clock switching and Fail-Safe Clock Monitor are disabled)
#pragma config FNOSC = FRCDIV           // Initial Oscillator Select (Low-Power RC Oscillator (LPRC))
#pragma config ALTRB6 = APPEND          // Alternate RB6 pin function enable bit (Append the RP6/ASCL1/PMPD6 functions of RB6 to RA1 pin functions)
#pragma config ALTCMPI = CxINC_RB       // Alternate Comparator Input bit (C1INC is on RB13, C2INC is on RB9 and C3INC is on RA0)
#pragma config WDTCMX = LPRC            // WDT Clock Source Select bits (WDT always uses LPRC as its clock source)
#pragma config IESO = ON                // Internal External Switchover (Enabled)

// CONFIG1
#pragma config WDTPS = PS512            // Watchdog Timer Postscaler Select (1:1024)
#pragma config FWPSA = PR128            // WDT Prescaler Ratio Select (1:128)
#pragma config WINDIS = OFF             // Windowed WDT Disable (Standard Watchdog Timer)
#pragma config FWDTEN = NOSLP              // Watchdog Timer Enable (WDT disabled in hardware; SWDTEN bit disabled)
#pragma config ICS = PGx3               // Emulator Pin Placement Select bits (Emulator functions are shared with PGEC3/PGED3)
#pragma config LPCFG = OFF              // Low power regulator control (Disabled - regardless of RETEN)
#pragma config GWRP = OFF               // General Segment Write Protect (Write to program memory allowed)
#pragma config GCP = OFF                // General Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (Disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#include "board.h"
#include "i2c.h"
#include "spi.h"
#include "config.h"

void init_board(void)
{
    DSCONbits.RELEASE = 0;
    DSCONbits.RELEASE = 0;
    init_oscillator();
    init_gpio();
    //CLKDIVbits.PLLEN = 0;
    init_spi1();
    I2cInitialize(I2C_FREQUENCY);
    
}

void init_oscillator(void)
{
    
    // CF no clock failure; NOSC FRCDIV; SOSCEN disabled; POSCEN disabled; CLKLOCK unlocked; OSWEN Switch is Complete; IOLOCK not-active; 
    __builtin_write_OSCCONL((char) (0x0700 & 0x00FF)); // 0x0700 for FRCDIV
    // CPDIV 1:1; PLLEN disabled; RCDIV FRC/1; DOZE 1:8; DOZEN disabled; ROI disabled; 
    CLKDIV = 0x0000;
    // STOR disabled; STORPOL Interrupt when STOR is 1; STSIDL disabled; STLPOL Interrupt when STLOCK is 1; STLOCK disabled; STSRC SOSC; STEN disabled; TUN Center frequency; 
    OSCTUN = 0x0000;
    // ROEN disabled; ROSEL FOSC; ROSIDL disabled; ROSWEN disabled; ROOUT disabled; ROSLP disabled; 
    REFOCONL = 0x0000;
    // RODIV 0; 
    REFOCONH = 0x0000;
    // ROTRIM 0; 
    REFOTRIML = 0x0000;
}

void init_gpio(void)
{
    LedRed_SetLow();
    LedGreen_SetLow();
    LedBlue_SetLow();
    LedRed_SetOutput();
    LedGreen_SetOutput();
    LedBlue_SetOutput();
    P2V5_Enable_SetOutput();
    SPI1_MISO_SetInput();
    I2C_SDA1_SetOutput();
    I2C_SCL1_SetOutput();
    
    P2V5_OFF();
    
    ANSB = 0;
}

