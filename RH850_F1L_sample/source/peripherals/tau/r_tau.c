/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_tau.c                                                         */
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
/* Source code for the TimerArrayUnit                                        */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_tau.h"
/*===========================================================================*/
/* Variables */
/*===========================================================================*/
void (*R_INTTAUJ0I1_ISR)(void) = R_NULL;

/*===========================================================================*/
/* Interrupts */
/*===========================================================================*/
/*****************************************************************************
** Function:    INTTAUJ0I1
** Description: Interrupt generated by channel 1 of TAUJ0. In case of interrupt,
**              ISR function assigned to pointer R_INTTAUJ0I1_ISR is called.
** Parameter:   None
** Return:      None
******************************************************************************/
#ifdef __IAR__
  #pragma vector = NUMINTTAUJ0I1
  __interrupt void INTTAUJ0I1(void)
#endif /* __IAR__ */
#ifdef __GHS__
  #pragma ghs interrupt
  void INTTAUJ0I1(void)
#endif /* __GHS__ */
#ifdef __CSP__
  #pragma interrupt INTTAUJ0I1(enable=manual)
  void INTTAUJ0I1(void)
#endif /* __CSP__ */
{
    if(R_INTTAUJ0I1_ISR != R_NULL)
    {
        R_INTTAUJ0I1_ISR();
    }
}


/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    R_TAUJ0_AssignChannel1ISR
** Description: Assigns a service routine to the function which is called inside 
**              the channel 1 interrupt.
** Parameter:   ISR_Ptr - Function pointer
** Return:      None
******************************************************************************/
void R_TAUJ0_AssignChannel1ISR(void ISR_Ptr(void))
{
    R_INTTAUJ0I1_ISR = ISR_Ptr;
}


/*****************************************************************************
** Function:    R_TAUJ0_CK0_Prescaler
** Description: Sets the Prescaler of TAUJ0 Clock 0.
** Parameter:   Prescaler - CK0 = TAUJ0CLK/(2^Prescaler)
** Return:      None
******************************************************************************/
void R_TAUJ0_CK0_Prescaler(uint8_t Prescaler)
{
  TAUJ0TPS &= 0xfff0;
  Prescaler &= 0x0f;
  TAUJ0TPS |= Prescaler;
}

/*****************************************************************************
** Function:    R_TAUJ0_CDR_Update
** Description: Update Channel Data Register
** Parameter:   CDR_val - new CDR Value
** Return:      None
******************************************************************************/
void R_TAUJ0_CDR_Update(uint16_t TAUJ0_Channel, uint16_t CDR_val)
{
  switch(TAUJ0_Channel)
  {
    case TAUJ0C0:
        TAUJ0CDR0 = CDR_val;
        TAUJ0RDT = TAUJ0C0;
    break;
    
    case TAUJ0C1:
        TAUJ0CDR1 = CDR_val;
        TAUJ0RDT = TAUJ0C1;
    break;
    
    case TAUJ0C2:
        TAUJ0CDR2 = CDR_val;
        TAUJ0RDT = TAUJ0C2;
    break;
    
    case TAUJ0C3:
        TAUJ0CDR3 = CDR_val;
        TAUJ0RDT = TAUJ0C3;
    break;
    
    default:
    break;
  }
  
}
/*****************************************************************************
** Function:    R_TAUJ0_Channel0_Init
** Description: Configures TAUJ0 Channel 0 to Interval Timer Mode.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_TAUJ0_Channel0_Init(void)
{
  TAUJ0CMOR0 = 0x0000u;            /* Select CK0 */
  TAUJ0CMUR0 = 0x00u;              /* Interval timer mode */
  TAUJ0CDR0 = 0x1D4Bu;
}

/*****************************************************************************
** Function:    R_TAUJ0_Channel1_Init
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_TAUJ0_Channel1_Init(void)
{  
  TAUJ0CMOR1 = 0x0000u;         /* Select CK0 */
  TAUJ0CMUR1 = 0x00u;           /* Interval timer mode */
  TAUJ0CDR1 = 0xFFFFu;
  TAUJ0RDT  = 0x02;
}

/*****************************************************************************
** Function:    R_TAUJ0_Channel2_Init
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_TAUJ0_Channel2_Init(void)
{  
  TAUJ0CMOR2 = 0x0801u;         /* Select CK0 / Channel 2 Master */
  TAUJ0CMUR2 = 0x00u;   
  TAUJ0CDR2 = 0x0FFFu;          /* The interval counter is 4095 */
  
  TAUJ0RDE |= 0x04u;            /* Enable simultaneous rewrite */
  TAUJ0RDM &= 0x0Bu;            /* The simultaneous rewrite trigger signal is generated when the master channel starts counting */
  
  
  TAUJ0RDT = 0x04u;             /* Reload all modified values */
}

/*****************************************************************************
** Function:    R_TAUJ0_Channel3_Init
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_TAUJ0_Channel3_Init(void)
{
  TAUJ0CMOR3 = 0x0409u;         /* Select CK0 / Channel 3 Slave */
  TAUJ0CMUR3 = 0x00u;
  TAUJ0CDR3  = 0x0000u;         /* The duty cycle is updated after ADC conversion */
  
  TAUJ0RDE |= 0x08u;            /* Enable simultaneous rewrite */
  TAUJ0RDM &= 0x07u;            /* The simultaneous rewrite trigger signal is generated when the master channel starts counting */
  
  TAUJ0TOE |= 0x08u;            /* Enables Independent Channel 3 Output Mode */
  TAUJ0TOM |= 0x08u;            /* Synchronous channel 3 operation */
  TAUJ0TOC &= 0x07u;            /* Set channel3 output as Operation mode */
  TAUJ0TOL &= 0x07u;            /* Set channel3 output as positive logic */
}

/*****************************************************************************
** Function:    R_TAUJ0_Channel_Start
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_TAUJ0_Channel_Start(uint16_t TAUJ0_Channel)
{
  TAUJ0TS = TAUJ0_Channel; 
}

/*****************************************************************************
** Function:    R_TAUJ0_Channel_Stop
** Description: Sets the Stop Trigger of the corresponding TAUJ0 Channel.
** Parameter:   
** Return:      None
******************************************************************************/
void R_TAUJ0_Channel_Stop(uint16_t TAUJ0_Channel)
{
  TAUJ0TT = TAUJ0_Channel;
}

/*****************************************************************************
** Function:    R_TAUB0_CK0_Prescaler
** Description: Sets the Prescaler of TAUB0 Clock 0.
** Parameter:   Prescaler - CK0 = TAUB0CLK/(2^Prescaler)
** Return:      None
******************************************************************************/
void R_TAUB0_CK0_Prescaler(uint8_t Prescaler)
{
  TAUB0TPS &= 0xfff0;
  Prescaler &= 0x0f;
  TAUB0TPS |= Prescaler;
}


/*****************************************************************************
** Function:    R_TAUB0_Channel6_Init
** Description: Initialize TAUB0 Channel 8 as Master.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_TAUB0_Channel6_Init(void)
{
  TAUB0CMOR6 = 0x0801u;         /* Select CK0 / Channel 6 Master */
  TAUB0CMUR6 = 0x00u;
  TAUB0CDR6  = 0x0FFFu;         /* The interval counter is 4095 */
  
  TAUB0RDE  |= 0x0040u;         /* Enable simultaneous rewrite */
  TAUB0RDM  &= 0xFFBFu;         /* The simultaneous rewrite trigger signal is generated when the master channel starts counting */

  TAUB0RDT  = 0x0040u;          /* Reload all modified values to the channels */
}

/*****************************************************************************
** Function:    R_TAUB0_Channel8_Init
** Description: Initialize TAUB0 Channel 8 as Slave and Output Mode.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_TAUB0_Channel8_Init(void)
{   
  TAUB0CMOR8 = 0x0409u;         /* Select CK0 / Channel 8 Slave */
  TAUB0CMUR8 = 0x00u;
    
  TAUB0RDE  |= 0x0100u;         /* Enable simultaneous rewrite */
  TAUB0RDM  &= 0xFEFFu;         /* The simultaneous rewrite trigger signal is generated when the master channel starts counting */

  TAUB0TOE |= 0x0100u;          /* Enables Independent Channel 8 Output Mode */
  TAUB0TOM |= 0x0100u;          /* Synchronous channel 8 operation */
  TAUB0TOC &= 0xFEFFu;          /* Set channel 8 output as Operation mode */
  TAUB0TOL &= 0xFEFFu;          /* Set channel 8 output as positive logic */
  
  TAUB0RDT  = 0x0100u;          /* Reload all modified values to the channels */
}


/*****************************************************************************
** Function:    R_TAUB0_CDR_Update
** Description: Update Channel Data Register
** Parameter:   TAUB0 Channel - Channel 6 | Channel 8
**              CDR_val - new CDR Value
** Return:      None
******************************************************************************/
void R_TAUB0_CDR_Update(uint16_t TAUB0_Channel, uint16_t CDR_val)
{
  switch(TAUB0_Channel)
  {
    case TAUB0C6:
        TAUB0CDR6 = CDR_val;
        TAUB0RDT = TAUB0C6;
    break;
    
    case TAUB0C8:
        TAUB0CDR8 = CDR_val;
        TAUB0RDT = TAUB0C8;
    break;
    
    default:
    break;
  }
  
}

/*****************************************************************************
** Function:    R_TAUB0_Channel_Start
** Description: Sets the Start Trigger of the corresponding TAUB0 Channel.
** Parameter:   TAUB0 Channel
** Return:      None
******************************************************************************/
void R_TAUB0_Channel_Start(uint16_t TAUB0_Channel)
{
  TAUB0TS = TAUB0_Channel;
}

/*****************************************************************************
** Function:    R_TAUB0_Channel_Stop
** Description: Sets the Stop Trigger of the corresponding TAUB0 Channel.
** Parameter:   TAUB0 Channel
** Return:      None
******************************************************************************/
void R_TAUB0_Channel_Stop(uint16_t TAUB0_Channel)
{
  TAUB0TT = TAUB0_Channel;
}
