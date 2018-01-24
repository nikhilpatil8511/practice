/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_enc.c                                                         */
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
/*                                                                           */
/* Source code for the Encoder timer functions.                              */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_enc.h"

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/******************************************************************************
** Function:    R_ENCA0_Init
** Description: Initializes the ENCA encoder module.
** Parameter:   None            
** Return:      None
******************************************************************************/
void R_ENCA0_Init(void)
{
  DNFAENCA0IEN = 0x1f;   /* Noise Filter */
  ENCA0CTL  = 0x02;      /* Rising edge - up-count, falling edge - down-count */
}

/******************************************************************************
** Function:    R_ENCA0_Start
** Description: Starts the ENCA0 operation.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_ENCA0_Start(void)
{
   ENCA0TS = 0x01;
}  

/******************************************************************************
** Function:    R_ENCA0_Stop
** Description: Stops the ENCA0 operation.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_ENCA0_Stop(void)
{
   ENCA0TT = 0x01;  
}

/******************************************************************************
** Function:    R_ENCA0_Read
** Description: Returns the value of the ENCA0 count register.
** Parameter:   None
** Return:      ENCA0CNT
******************************************************************************/
uint16_t R_ENCA0_Read(void)
{
    return ENCA0CNT;
}

/******************************************************************************
** Function:    R_ENCA0_GetFlags
** Description: Returns the ENCA0 flags such as count direction.
** Parameter:   None
** Return:      ENCA0FLG
******************************************************************************/
uint8_t R_ENCA0_GetFlags(void)
{
    return ENCA0FLG;
}
