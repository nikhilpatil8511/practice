/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_pwmd.c                                                        */
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
/* Source code for the PWM generation and diagnostic functions.              */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_pwmd.h"

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    R_PWMD_Channel64Init
** Description: Initializes the PWM channel 64.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_PWMD_Channel64Init(void)
{
    PWGA64CTL = 0x00u;        /* Use PWMCLK0 */
    PWGA64CSDR = 0x00u;       /* Delay = 0 */
    PWGA64CTDR = 200u;        /* Set the trigger for the PWSA to ~40us ((1/PWMClock)*PWGAnCTDR) */
    PWGA64CRDR = 0x00u;       /* Duty cycle = 0. This will be updated via duty function */
}

/*****************************************************************************
** Function:    R_PWMD_Channel65Init
** Description: Initializes the PWM channel 65.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_PWMD_Channel65Init(void)
{
    PWGA65CTL = 0x00u;        /* Use PWMCLK0 */
    PWGA65CSDR = 0x000u;      /* Delay = 0 */
    PWGA65CTDR = 200u;        /* Set the trigger for the PWSA to ~40us ((1/PWMClock)*PWGAnCTDR) */
    PWGA65CRDR = 0x000u;      /* Duty cycle = 0. This will be updated via duty function */
}

/*****************************************************************************
** Function:    R_PWMD_Channel66Init
** Description: Initializes the PWM channels 66.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_PWMD_Channel66Init(void)
{
    PWGA66CTL = 0x00u;        /* Use PWMCLK0 */
    PWGA66CSDR = 0x000u;      /* Delay = 0 */
    PWGA66CTDR = 200u;        /* Set the trigger for the PWSA to ~40us ((1/PWMClock)*PWGAnCTDR) */
    PWGA66CRDR = 0x000u;      /* Duty cycle = 0. This will be updated via duty function */
}

/*****************************************************************************
** Function:    R_PWMD_ClockInit
** Description: Sets PWM Clock divider and starts clock output.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_PWMD_ClockInit(void)
{
	PWBA0BRS0 = 0x04u;      /* Set ClockCycle of PWMCLK0 = PCLK/(2*(PWBA0BRS0[10:0])) = 5MHz */
	PWBA0TS = 0x01u;        /* Starts Output of PWMCLK0 */
}

/*****************************************************************************
** Function:    R_PWMD_StartChannel
** Description: Starts the PWM output of the chosen channel.
** Parameter:   PWGA_Channel 0-71
** Return:      None
******************************************************************************/
void R_PWMD_StartChannel(uint32_t PWGA_Channel)
{
    if(PWGA_Channel <= 31)
        {
            SLPWGA0 |= 1u<<PWGA_Channel;
        }
    else if(PWGA_Channel <= 63)
        {
            SLPWGA1 |= 1u<<(PWGA_Channel - 32);
        }
    else if(PWGA_Channel <= 71)
        {
            SLPWGA2 |= 1u<<(PWGA_Channel - 64);
        }
}

/*****************************************************************************
** Function:    R_PWMD_StopChannel
** Description: Starts the PWM output of the chosen channel.
** Parameter:   PWGA_Channel 0-71
** Return:      None
******************************************************************************/
void R_PWMD_StopChannel(uint32_t PWGA_Channel)
{
    if(PWGA_Channel <= 31)
        {
            SLPWGA0 &= ~(1u<<PWGA_Channel);
        }
    else if(PWGA_Channel <= 63)
        {
            SLPWGA1 &= ~(1u<<(PWGA_Channel - 32));
        }
    else if(PWGA_Channel <= 71)
        {
            SLPWGA2 &= ~(1u<<(PWGA_Channel - 64));
        }
}
    
/*****************************************************************************
** Function:    R_PWMD_Channel64DutyUpdate
** Description: Updates the duty for the chosen LED
** Parameter:   duty - Duty cycle [0-4095]
** Return:      None
******************************************************************************/
void R_PWMD_Channel64DutyUpdate(uint16_t duty)
{
    PWGA64CRDR = duty;      
    PWGA64RDT = 1u;         /* Load the new duty cycle */
}

/*****************************************************************************
** Function:    R_PWMD_Channel65DutyUpdate
** Description: Updates the duty for the chosen LED
** Parameter:   duty - Duty cycle [0-4095]
** Return:      None
******************************************************************************/
void R_PWMD_Channel65DutyUpdate(uint16_t duty)
{
    PWGA65CRDR = duty;      
    PWGA65RDT = 1u;         /* Load the new duty cycle */
}

/*****************************************************************************
** Function:    R_PWMD_Channel66DutyUpdate
** Description: Updates the duty for the chosen LED
** Parameter:   duty - Duty cycle [0-4095]
** Return:      None
******************************************************************************/
void R_PWMD_Channel66DutyUpdate(uint16_t duty)
{
    PWGA66CRDR = duty;      
    PWGA66RDT = 1u;         /* Load the new duty cycle */
}

/*****************************************************************************
** Function:    R_PWMD_DiagInit
** Description: Specifies an analog pin for diagnose and the Upper/Lower limit channel:
**              PVCR64: AP0_1, Limit Channel 0
**              PVCR65: AP0_3, Limit Channel 0
**              PVCR66: AP0_2, Limit Channel 0
** Parameter:   None
** Return:      None
******************************************************************************/    
void R_PWMD_DiagInit(void)
{
    PWSA0PVCR64_65 = 0x00430041u;
    PWSA0PVCR66_67 = 0x00000042u;    
}

/*****************************************************************************
** Function:    R_PWMD_DiagStart
** Description: Starts the PWM-Diagnostic function.
** Parameter:   None
** Return:      None
******************************************************************************/    
void R_PWMD_DiagStart(void)
{
    PWSA0CTL = 1u;          /* Start PWSA */   
    
}

/*****************************************************************************
** Function:    R_PWMD_DiagStop
** Description: Stops the PWM-Diagnostic function.
** Parameter:   None
** Return:      None
******************************************************************************/    
void R_PWMD_DiagStop(void)
{
    PWSA0CTL = 0u;          /* Stop PWSA */
}
