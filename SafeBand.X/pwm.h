/* 
 * File:   pwm.h
 * Author: Justin
 *
 * Created on October 4, 2017, 11:01 PM
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void pwm_init(void);
void DisablePwm(void);
void EnablePwm(void);
void SetFrequency(uint32_t frequency);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

