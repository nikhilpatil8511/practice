#ifndef ADC_H
#define ADC_H

#include "t_device_init.h"
#include "r_typedefs.h"
 
void adc_init(void);
uint16_t pin_analog_read(void);

#endif // ADC_H