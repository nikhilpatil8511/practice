#include "adc.h"


/*********************************************************************
** function	adc_init
** Description  initializes ADC scan group with 1 virtual channel 
** Paramenter 	none
** Return 	none
**********************************************************************/
void adc_init(){
  ADCA0ADCR = 0x02u;      /* Asynchronous suspend / 12bit mode / PWDDR and ADCA0DR00 are set to right align */
                          /* The self-diagnostic voltage circuit is turned off */

  ADCA0SMPCR = 0x18u;     /* Set sampling time to 24*1/40MHz = 60us */
 ADCA0SGCR1 = 0x10u;     /* ScanGroup interrupt is output when scan ends */
  
  /* ScanGroup start/end registers */
  ADCA0SGVCSP1 = 0x00u;   /* ScanGroup starts at virtual channel 0 */
  ADCA0SGVCEP1 = 0x00u;   /* ScanGroup ends at virtual channel 0 */
}


/*********************************************************************
** function	pin_analog_read
** Description  if the channel is initialized properly this functions 
		reads the adc value [0-4096]
** Paramenter 	none
** Return 	adc value
**********************************************************************/
uint16_t pin_analog_read(){
  uint16_t read_data = 0u;
  ADCA0VCR00 = 0; // Analog cannel 0 has potentiometer 
  
  ADCA0SGSTCR1 = 1u;                              /* Conversion start trigger */
  while((ADCA0DIR00&(1<<25))==0)
  {
      /* Wait until value is stored */
  }
  read_data = (uint16_t) ADCA0DIR00&0xffffu;  /* Return the lower 16bit which are the read value */

  return read_data;


}