#ifndef SYSTEM_H
#define SYSTEM_H
#include "r_typedefs.h"
#include "iodefine.h"


#define R_RESF_PowerUp        (uint32_t)(1<< 9)
/*===========================================================================*/
/* Function defines */
/*===========================================================================*/
void R_SYSTEM_ClockInit(void); 
void R_SYSTEM_TimerInit(void);
void R_SYSTEM_TimerTick(void);
void R_SYSTEM_TimerStart(void);
void R_SYSTEM_TimerStop(void);
uint32_t R_SYSTEM_GetResetCause(void);
void R_SYSTEM_ClearResetCause(void);

void R_SYSTEM_ClockInit(void);

#endif 