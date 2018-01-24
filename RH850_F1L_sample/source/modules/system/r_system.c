/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_system.c                                                      */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2016 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* In case of any question please do not hesitate to contact:                */
/*                                                                           */
/*        ABG Software Tool Support                                          */
/*                                                                           */
/*        Renesas Electronics Europe GmbH                                    */
/*        Arcadiastrasse 10                                                  */
/*        D-40472 Duesseldorf, Germany                                       */
/*                                                                           */
/*        e-mail: software_support-eu@lm.renesas.com                         */
/*        FAX:   +49 - (0)211 / 65 03 - 11 31                                */
/*                                                                           */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Source code for System functionalities.                                   */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_system.h"                 

/* Peripheral Includes */
#include "adc/r_adc.h"
#include "clkc/r_clkc.h"
#include "intc/r_intc.h"
#include "lps/r_lps.h"
#include "ostm/r_ostm.h"
#include "port/r_port.h"
#include "stbc/r_stbc.h"
#include "tau/r_tau.h"

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    loc_LpsManualRead
** Description: Manually reads states of Digital Input Switch S3.
** Parameter:   None
** Return:      8bit Switch states.
******************************************************************************/
uint8_t loc_LpsManualRead(void)
{
	uint8_t loc_ReturnValue = 0;

    R_PORT_SetPushPull(Port0 ,0);

    R_PORT_SetGpioOutput(Port0, 0, High);   /* DPO    */
    R_PORT_SetGpioInput(Port8, 1);			/* DPIN0   */

    /* MUX = 0 */
    R_PORT_SetGpioOutput(Port0, 4, Low);	/* SELDP0 */
    R_PORT_SetGpioOutput(Port0, 5, Low);	/* SELDP1 */
    R_PORT_SetGpioOutput(Port0, 6, Low);	/* SELDP2 */
    loc_ReturnValue |= (R_PORT_GetLevel(Port8, 1) << 0);

    /* MUX = 1 */
    R_PORT_SetGpioOutput(Port0, 4, High);	/* SELDP0 */
    R_PORT_SetGpioOutput(Port0, 5, Low);	/* SELDP1 */
    R_PORT_SetGpioOutput(Port0, 6, Low);	/* SELDP2 */
    loc_ReturnValue |= (R_PORT_GetLevel(Port8, 1) << 1);

    /* MUX = 2 */
    R_PORT_SetGpioOutput(Port0, 4, Low);	/* SELDP0 */
    R_PORT_SetGpioOutput(Port0, 5, High);	/* SELDP1 */
    R_PORT_SetGpioOutput(Port0, 6, Low);	/* SELDP2 */
    loc_ReturnValue |= (R_PORT_GetLevel(Port8, 1) << 2);

    /* MUX = 3 */
    R_PORT_SetGpioOutput(Port0, 4, High);	/* SELDP0 */
    R_PORT_SetGpioOutput(Port0, 5, High);	/* SELDP1 */
    R_PORT_SetGpioOutput(Port0, 6, Low);	/* SELDP2 */
    loc_ReturnValue |= (R_PORT_GetLevel(Port8, 1) << 3);

    /* MUX = 4 */
    R_PORT_SetGpioOutput(Port0, 4, Low);	/* SELDP0 */
    R_PORT_SetGpioOutput(Port0, 5, Low);	/* SELDP1 */
    R_PORT_SetGpioOutput(Port0, 6, High);	/* SELDP2 */
    loc_ReturnValue |= (R_PORT_GetLevel(Port8, 1) << 4);

    /* MUX = 5 */
    R_PORT_SetGpioOutput(Port0, 4, High);	/* SELDP0 */
    R_PORT_SetGpioOutput(Port0, 5, Low);	/* SELDP1 */
    R_PORT_SetGpioOutput(Port0, 6, High);	/* SELDP2 */
    loc_ReturnValue |= (R_PORT_GetLevel(Port8, 1) << 5);

    /* MUX = 6 */
    R_PORT_SetGpioOutput(Port0, 4, Low);	/* SELDP0 */
    R_PORT_SetGpioOutput(Port0, 5, High);	/* SELDP1 */
    R_PORT_SetGpioOutput(Port0, 6, High);	/* SELDP2 */
    loc_ReturnValue |= (R_PORT_GetLevel(Port8, 1) << 6);

    /* MUX = 7 */
    R_PORT_SetGpioOutput(Port0, 4, High);	/* SELDP0 */
    R_PORT_SetGpioOutput(Port0, 5, High);	/* SELDP1 */
    R_PORT_SetGpioOutput(Port0, 6, High);	/* SELDP2 */
    loc_ReturnValue |= (R_PORT_GetLevel(Port8, 1) << 7);

    return loc_ReturnValue;
}


/*****************************************************************************
** Function:    R_SYSTEM_ClockInit
** Description: This function calls PLL initialization and configures clock
** 				domains of used peripherals.
** Parameter:   None
** Return:      None
******************************************************************************/
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
** Function:    R_SYSTEM_PrepareDeepSTOP
** Description: This function prepares clocks, peripherals and wakeup factors
** 				for usage in DeepSTOP.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_SYSTEM_PrepareDeepSTOP(void)
{
    uint32_t loc_WufMask0, loc_WufMask20, loc_WufMaskIso;
    uint8_t loc_LpsCompareValue;
    uint32_t adc0_value;

    loc_WufMask0    = ~(R_WUF_INTP12|R_WUF_INTP15|R_WUF_LPS_DI|R_WUF_LPS_AI|R_WUF_DCUTDI);
    loc_WufMask20   = 0xffffffffu;
    loc_WufMaskIso = 0xffffffffu;
    
    R_CLKC_SetTaujClockDomain(R_CLKC_TAUJ_LSINTOSC);
    R_CLKC_SetAdca0ClockDomain(R_CLKC_ADCA_HSINTOSC);
    
    R_CLKC_SetAdca0StopMask();
    R_CLKC_SetTaujStopMask();

     /* Prepare Low Power Sampler */
    R_PORT_SetGpioOutput(Port0, 1, High);
   //  ADC_interrupt_disable();              /* Disable the ADC error table interrupt */

     adc0_value=R_ADCA0_PinRead(AP0_0);
     /* Set values for upper/lower limit +-DEEPSTOP_POTI_SENSE for LPS in DEEPSTOP */
     if(adc0_value<=DEEPSTOP_POTI_SENSE)                                   /* If value is <= 1024 lower limit is 0(min), upper limit is +DEEPSTOP_POTI_SENSE */
     {
       R_ADCA0_SetUpperLowerLimit(AP0_0, adc0_value+DEEPSTOP_POTI_SENSE, 0u);
      }
      else if(adc0_value>=(0xfffu-DEEPSTOP_POTI_SENSE))                     /* If value is >= 3071 upper limit is 4095(max), lower limit is -DEEPSTOP_POTI_SENSE */
      {
       R_ADCA0_SetUpperLowerLimit(AP0_0, 0xfffu, adc0_value-DEEPSTOP_POTI_SENSE);
      }
      else
       {    
       R_ADCA0_SetUpperLowerLimit(AP0_0, adc0_value+DEEPSTOP_POTI_SENSE, adc0_value-DEEPSTOP_POTI_SENSE);     /* Else upper limit is +DEEPSTOP_POTI_SENSE and lower limit is -DEEPSTOP_POTI_SENSE */
       }
     
    R_PORT_SetAltFunc(Port0, 1, Alt4, Output);   /* Initialize the APO Pin for the ADC usage */
    
    R_ADCA0_LpsInit();
    
    loc_LpsCompareValue = loc_LpsManualRead();
    
    R_LPS_SetCompareValue(loc_LpsCompareValue);

    R_PORT_SetAltFunc(Port0, 0, Alt4, Output);	/* DPO */
    

    R_PORT_SetAltFunc(Port0, 4, Alt3, Output);	/* SELDP0 */
    R_PORT_SetAltFunc(Port0, 5, Alt2, Output);	/* SELDP1 */
    R_PORT_SetAltFunc(Port0, 6, Alt2, Output);	/* SELDP2 */

    R_PORT_SetAltFunc(Port8, 1, Alt2, Input);	/* DPIN0 */

    R_TAUJ0_Channel0_Init(); 
    
    R_LPS_Init();
    R_TAUJ0_Channel_Start(TAUJ0C0);
    
    /* LED2 2s interval, 5% duty - DeepSTOP LED */
    R_TAUJ0_CDR_Update(TAUJ0C2, 0x752F);
    R_TAUJ0_CDR_Update(TAUJ0C3, 0x05DC);
    R_TAUJ0_Channel_Start(TAUJ0C2|TAUJ0C3);
    
    
    R_STBC_PrepareWakeUp(loc_WufMask0, loc_WufMask20, loc_WufMaskIso);
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



#ifdef __IAR__ 
extern unsigned int RAM_RET_BEG;
extern unsigned int RAM_RET_END;
/*****************************************************************************
** Function:    R_SYSTEM_ClearRetentionRAM
** Description: Clears Retention RAM area (IAR version)
** Parameter:   None
** Return:      None
******************************************************************************/

void R_SYSTEM_ClearRetentionRAM(void)
{  
   uint32_t* loc_ptr;
  
  loc_ptr = (uint32_t*)&RAM_RET_BEG;
  while(((uint32_t*)&RAM_RET_END) > loc_ptr)
  {
    *loc_ptr=0x00000000;
    loc_ptr++;
  }
   
}
/*****************************************************************************
** Function:    __low_level_init
** Description: called during start-up (IAR version)
** Parameter:   None
** Return:      None
******************************************************************************/
extern void *_cstart_low_level_init;
#pragma required=_cstart_low_level_init
unsigned char __low_level_init (int peId)
{
 
  
   /* check if power-up reset has occured */
   if(R_SYSTEM_GetResetCause()&R_RESF_PowerUp)
   {
     /*clear noinit area of retention RAM */
     R_SYSTEM_ClearRetentionRAM();
   }

  /*==================================*/
  /* Choose if segment initialization */
  /* should be done or not.           */
  /* Return: 0 to omit seg_init       */
  /*         1 to run seg_init        */
  /*==================================*/
  return 1;
}

#endif  /* __IAR__ */


#ifdef __GHS__ 
extern unsigned int __ghs_rramstart;
extern unsigned int __ghs_rramend;
/*****************************************************************************
** Function:    R_SYSTEM_ClearRetentionRAM
** Description: Clears Retention RAM area (GHS version)
** Parameter:   None
** Return:      None
******************************************************************************/
void R_SYSTEM_ClearRetentionRAM(void)
{  
   uint32_t* loc_ptr;
  
  loc_ptr = (uint32_t*)&__ghs_rramstart;
  while(((uint32_t*)&__ghs_rramend ) > loc_ptr)
  {
    *loc_ptr=0x00000000;
    loc_ptr++;
  }
   
}
/*****************************************************************************
** Function:    __lowinit
** Description: called during start-up (GHS version)
** Parameter:   None
** Return:      None
******************************************************************************/
void __lowinit(void)
{
    /* check if power-up reset has occured */
   if(R_SYSTEM_GetResetCause()&R_RESF_PowerUp)
   {
     /*clear noinit area of retention RAM */
     R_SYSTEM_ClearRetentionRAM();
   }

}

#endif  /* __GHS__*/

#ifdef __CSP__ 
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

#endif  /* __CSP__*/