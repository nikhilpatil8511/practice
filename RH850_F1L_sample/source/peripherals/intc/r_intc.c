/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_intc.c                                                        */
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
/* Source code for the interrupt controller functions.                       */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_intc.h"

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/******************************************************************************
** Function:    R_INTC_MaskInterrupt
** Description: Sets the mask bit of the corresponding interrupt control register.
** Parameter:   IC_ptr - Address of interrupt control register
** Return:      None
******************************************************************************/
void R_INTC_MaskInterrupt(volatile uint16_t *IC_ptr)
{
    *IC_ptr |= 0x80;
}

/******************************************************************************
** Function:    R_INTC_UnmaskInterrupt
** Description: Resets the mask bit of the corresponding interrupt control register.
** Parameter:   IC_ptr - Address of interrupt control register
** Return:      None
******************************************************************************/
void R_INTC_UnmaskInterrupt(volatile uint16_t *IC_ptr)
{
    *IC_ptr &= ~0x80;
}

/******************************************************************************
** Function:    R_INTC_SetPriority
** Description: Sets the priority of the corresponding interrupt.
** Parameter:   IC_ptr - Address of interrupt control register
**              Priority 
** Return:      None
******************************************************************************/
void R_INTC_SetPriority(volatile uint16_t *IC_ptr, uint8_t Priority)
{
    Priority &= 0x07;
    *IC_ptr &= ~0x0007;
    *IC_ptr |= Priority;
}

/******************************************************************************
** Function:    R_INTC_SetTableBit
** Description: Sets the table bit of the corresponding interrupt control register
**              for interrupt vector table usage.
** Parameter:   IC_ptr - Address of interrupt control register
** Return:      None
******************************************************************************/
void R_INTC_SetTableBit(volatile uint16_t *IC_ptr)
{
    *IC_ptr |= 0x40;
}

/******************************************************************************
** Function:    R_INTC_ResetTableBit
** Description: Resets the table bit of the corresponding interrupt control register
**              for handling interrupts by priority.
** Parameter:   IC_ptr - Address of interrupt control register
** Return:      None
******************************************************************************/
void R_INTC_ResetTableBit(volatile uint16_t *IC_ptr)
{
    *IC_ptr &= ~0x40;
}

/******************************************************************************
** Function:    R_INTC_SetRequestFlag
** Description: Sets the request flag of the corresponding interrupt control register
**              so interupt will occur.
** Parameter:   IC_ptr - Address of interrupt control register
** Return:      None
******************************************************************************/
void R_INTC_SetRequestFlag(volatile uint16_t *IC_ptr)
{
    *IC_ptr |= 0x1000;
}

/******************************************************************************
** Function:    R_INTC_GetRequestFlag
** Description: Gets the status of the request flag.
** Parameter:   IC_ptr - Address of interrupt control register
** Return:      R_REQUEST_FLAG_SET
**              R_REQUEST_FLAG_NOT_SET
******************************************************************************/
uint32_t R_INTC_GetRequestFlag(volatile uint16_t *IC_ptr)
{
    if((*IC_ptr&0x1000) == 0) /* If request flag == 0 */
    {
        return R_REQUEST_FLAG_NOT_SET;
    }
    else
    {
        return R_REQUEST_FLAG_SET;
    }
}

/******************************************************************************
** Function:    R_INTC_ResetRequestFlag
** Description: Resets the request flag of the corresponding interrupt control 
**              register.
** Parameter:   IC_ptr - Address of interrupt control register
** Return:      None
******************************************************************************/
void R_INTC_ResetRequestFlag(volatile uint16_t *IC_ptr)
{
    *IC_ptr &= ~0x1000;
}