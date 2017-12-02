#include <xc.h>

#define CLOCK_FREQUENCY 4000000
#define PWM_FREQUENCY 32000
#define ALARM_FREQUENCY 4000

void pwm_init(void)
{

    LATBbits.LATB0 = 0;
    TRISBbits.TRISB0 = 0;

    /* Reset PWM */
    OC1CON1 = 0x0000;
    OC1CON2 = 0x0000;

    /* set PWM duty cycle to 50% */
    OC1R    = CLOCK_FREQUENCY/PWM_FREQUENCY >> 1; /* set the duty cycle tp 50% */
    OC1RS   = CLOCK_FREQUENCY/PWM_FREQUENCY - 1;  /* set the period */

    /* configure PWM */
    OC1CON2 = 0x001F;   /* Sync with This OC module                               */
    OC1CON1 = 0x1C08;   /* Clock sourc Fcyc, trigger mode 1, Mode 0 (disable OC1) */

    /* enable the PWM */
    OC1CON1 = OC1CON1 | 0x0006;   /* Mode 6, Edge-aligned PWM Mode */
    _RP0R = _RPOUT_OC1;
    
    LATBbits.LATB11 = 0;
    TRISBbits.TRISB11 = 0;
    
    /* Reset PWM */
    OC2CON1 = 0x0000;
    OC2CON2 = 0x0000;

    /* set PWM duty cycle to 50% */
    OC2R    = CLOCK_FREQUENCY/ALARM_FREQUENCY >> 1; /* set the duty cycle tp 50% */
    OC2RS   = CLOCK_FREQUENCY/ALARM_FREQUENCY - 1;  /* set the period */

    /* configure PWM */
    OC2CON2 = 0x001F;   /* Sync with This OC module                               */
    OC2CON1 = 0x1C08;   /* Clock sourc Fcyc, trigger mode 1, Mode 0 (disable OC1) */

    /* enable the PWM */
//    OC2CON1 = OC2CON1 | 0x0006;   /* Mode 6, Edge-aligned PWM Mode */
//    _RP11R = _RPOUT_OC2;
}