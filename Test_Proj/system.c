#include "t_device_init.h"
#include "system.h"
#include "system_clock.h"
#include "r_intc.h"
#include "r_ostm.h"


void R_SYSTEM_ClockInit(void)
{
  R_CLKC_PllInit();                                    /* CPUCLK = 120MHz, PPLLCLK = 80MHz */
  R_CLKC_SetAdca0ClockDomain(R_CLKC_ADCA_PPLLCLK2);    /* ADCA0 Clock = PPLLCLK/2 */ //R_CLKC_ADCA_PPLLCLK2 = 0x03 defined in r_clkc.h
  R_CLKC_SetTaujClockDomain(R_CLKC_TAUJ_PPLLCLK2);     /* TAUJ Clock = PPLLCLK/2 */  //R_CLKC_TAUJ_PPLLCLK2 = 0x04 defined in r_clkc.h

  /*  Module Clock = PPLLCLK, Communication Clock = MainOSC */
  R_CLKC_SetRscanClockDomain(R_CLKC_RSCAN_PPLLCLK,
                               R_CLKC_RSCAN_DIV_MOSC1);
}

/*****************************************************************************
** Function:    R_SYSTEM_TimerInit
** Description: Initializes the OSTM0 timer to generate a 1ms tick.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_SYSTEM_TimerInit(void)
{
    R_OSTM0_Init();
    R_OSTM0_SetCompareValue(39999);    
}

/*****************************************************************************
** Function:    R_SYSTEM_TimerTick
** Description: Waits for the OSTM0 request flag and clears it afterwards.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_SYSTEM_TimerTick(void)
{
    while(R_INTC_GetRequestFlag((uint16_t*)R_ICOSTM0)==0);
    R_INTC_ResetRequestFlag((uint16_t*)R_ICOSTM0);    
}


/*****************************************************************************
** Function:    R_SYSTEM_TimerStart
** Description: Starts OSTM0 count operation.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_SYSTEM_TimerStart(void)
{
    R_OSTM0_Start();
}

/*****************************************************************************
** Function:    R_SYSTEM_TimerStop
** Description: Stops OSTM0 count operation.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_SYSTEM_TimerStop(void)
{
    R_OSTM0_Stop();
}

/*****************************************************************************
** Function:    R_SYSTEM_GetResetCause
** Description: Returns reset cause
** Parameter:   None
** Return:      Contens of reset cause register (RESF)
******************************************************************************/
uint32_t R_SYSTEM_GetResetCause(void)
{
    return (uint32_t)RESF;
}

/*****************************************************************************
** Function:    R_SYSTEM_ClearResetCause
** Description: Clears reset cause register
** Parameter:   None
** Return:      None
******************************************************************************/
void R_SYSTEM_ClearResetCause(void)
{
  /* clear all reset flags */ 
  RESFC=0x00003ff;
}

/*****************************************************************************
** Function:    R_SYSTEM_ClearRetentionRAM
** Description: Clears Retention RAM area (CS+ version)
** Parameter:   None
** Return:      None
******************************************************************************/
void R_SYSTEM_ClearRetentionRAM(void)
{  
   uint32_t* loc_ptr;
  
  loc_ptr = (uint32_t*)RET_RAM_BEG;
  while(((uint32_t*)RET_RAM_END ) > loc_ptr)
  {
    *loc_ptr=0x00000000;
    loc_ptr++;
  }
   
}
/*****************************************************************************
** Function:    __lowinit
** Description: called during start-up (CS+ version)
** Parameter:   None
** Return:      None
******************************************************************************/
void _lowinit(void)
{
    /* check if power-up reset has occured */
   if(R_SYSTEM_GetResetCause()&R_RESF_PowerUp)
   {
     /*clear noinit area of retention RAM */
     R_SYSTEM_ClearRetentionRAM();
   }

}
