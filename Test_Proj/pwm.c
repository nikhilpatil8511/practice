#include "t_device_init.h"
#include "iodefine.h"
#include "pwm.h"


/*****************************************************************************
** Function:    pwm_clockInit
** Description: initializes the clock for PWM via PWBA.
** Parameter:   None
** Return:      None
******************************************************************************/    

void pwm_clockInit(void){
	PWBA0BRS0 = 0x04u;      /* Set ClockCycle of PWMCLK0 = PCLK/(2*(PWBA0BRS0[10:0])) = 5MHz */
	PWBA0TS = 0x01u;        /* Starts Output of PWMCLK0 */
}

/*****************************************************************************
** Function:    pwm_init
** Description: initializes PWM via PWGA
** Parameter:   None
** Return:      None
******************************************************************************/    
void pwm_init(void){

	PWGA64CTL = 0x00u;        /* Use PWMCLK0 */
    	PWGA64CSDR = 0x00u;       /* Delay = 0 */
    	PWGA64CTDR = 200u;        /* Set the trigger for the PWSA to ~40us ((1/PWMClock)*PWGAnCTDR) */
    	PWGA64CRDR = 0x00u;       /* Duty cycle = 0. This will be updated via duty function */
	pwm_clockInit();
}

/*****************************************************************************
** Function:    pwm_dutycycle_update
** Description: changes the duty cycle to a new value
** Parameter:   duty cycle value
** Return:      None
******************************************************************************/  
void pwm_dutycycle_update(uint16_t duty){
	PWGA64CRDR = duty;      
    	PWGA64RDT = 1u;         /* Load the new duty cycle */
}

/*****************************************************************************
** Function:    pwm_start
** Description: starts the pwm with given configuraton 
** Parameter:   duty cycle value
** Return:      None
******************************************************************************/ 
void pwm_start(void){
    	 SLPWGA2 |= 1u;          /* Start PWSA */ 
}

/*****************************************************************************
** Function:    pwm_stop
** Description: stops the pwm output
** Parameter:   duty cycle value
** Return:      None
******************************************************************************/ 
void pwm_stop(void){
	 PWSA0CTL = 0u;          /* Stop PWSA */
}
