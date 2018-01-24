/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_stbc.c                                                        */
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
/* Source code for the StandBy Controller                                    */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_stbc.h"

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
 
/*****************************************************************************
** Function:    R_STBC_PrepareWakeUp
** Description: This function clears all reset and wake-up flags and sets the 
**              enabled WakeUp factors.
** Parameter:   WUFMSKx - WakeUp mask register settings.
** Return:      None
******************************************************************************/
void R_STBC_PrepareWakeUp(uint32_t WUFMSK0_Reg, uint32_t WUFMSK20_Reg, uint32_t WUFMSK_ISO0_Reg)
{
  /* Configure valid wake-up conditions */
  WUFMSK0 = WUFMSK0_Reg;
  WUFMSK20 = WUFMSK20_Reg;
  WUFMSK_ISO0 = WUFMSK_ISO0_Reg;
  
  /* WakeUpFactor RegisterReset */
  WUFC0 = 0xffffffffu;
  WUFC20 = 0xfffffffu;
  WUFC_ISO0 = 0xfffffffu;
  
  /* Clear all ResetFactor Flags */
  RESFC = 0x000007ffu;
}

/*****************************************************************************
** Function:    R_STBC_EnterDeepSTOP
** Description: This function enters the DeepSTOP.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_STBC_EnterDeepSTOP(void)
{
    protected_write(PROTCMD0,PROTS0,STBC0PSC,0x02u);   /* Enter DeepSTOP */
    while(1){}
}

/*****************************************************************************
** Function:    R_STBC_GetWakeUpFactor
** Description: This function returns the WakeUpFactor register.
** Parameter:   None
** Return:      WUF0 - WakeUpFactor register
******************************************************************************/
uint32_t R_STBC_GetWakeUpFactor(void)
{
    return WUF0;
}

/*****************************************************************************
** Function:    R_STBC_ReleaseIoHold
** Description: This function releases the IO Hold function of ISO ports.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_STBC_ReleaseIoHold(void)
{
  /* Release I/O-Hold Buffer */
  protected_write(PROTCMD0,PROTS0,IOHOLD,0x00u);
  while(IOHOLD!=0x00u){}
}
