#ifndef TAUD_H
#define TAUD_H
// variables 
#include "iodefine.h"
#include "r_typedefs.h"
#define TAUD0C0		0x01




void TAUD_CK0_Prescaler(uint8_t Prescaler);
void TAUD0_CDR_Update(uint16_t CDR_val);
void TAUD0_AssignChannel0ISR(void ISR_Ptr(void));
// test feature 
void TAUD0_Channel0_Init(void);
void TAUD0_Channel_Start(void); 
uint16_t get_counter_value(void);
uint16_t get_status_reg(void);
// end test feature 

void TAUJ0_CK0_Prescaler(uint8_t Prescaler);
void TAUJ0_Channel1_Init(void );
void TAUJ0_AssignChannel1ISR(void ISR_Ptr(void));
void TAUJ0_Channel_Start(uint16_t TAUJ0_Channel);
void TAUJ0_Channel_Stop(void);
#endif