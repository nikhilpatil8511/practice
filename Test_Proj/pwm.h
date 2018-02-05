#ifndef PWM_H
#define PWM_H

#include "r_typedefs.h" 


void pwm_clockInit(void);
void pwm_init(void);
void pwm_dutycycle_update(uint16_t duty);
void pwm_start(void);
void pwm_stop(void);


#endif 