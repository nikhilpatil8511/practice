/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_uart.c                                                        */
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
/* Source code for UART initialization and testing.                          */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_uart.h"

/* Peripheral Includes */
#include "intc/r_intc.h"
#include "port/r_port.h"
#include "rlin/r_rlin.h"

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    R_UART_Init
** Description: Configures Ports and RLIN30 for UART usage and enables the Tx 
**              interrupt for string transmission.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UART_Init(void)
{
    R_PORT_SetAltFunc(Port0, 2, Alt2, Output);
    R_PORT_SetAltFunc(Port0, 3, Alt2, Input);
    
    R_RLIN30_UartInit();
    
    /* Enable Table Interrupt */
    R_INTC_SetTableBit((uint16_t*)R_ICRLIN30UR0);
    R_INTC_UnmaskInterrupt((uint16_t*)R_ICRLIN30UR0);
}

/*****************************************************************************
** Function:    R_UART_Deinit
** Description: Sets the used ports back to default configuration. 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UART_Deinit(void)
{
    R_PORT_SetGpioHighZ(Port0, 2);
    R_PORT_SetGpioHighZ(Port0, 3);
}

/*****************************************************************************
** Function:    R_UART_SendString
** Description: Waits if transmission is still in progress and then sends a string.
**              string - Buffer with string to send.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UART_SendString(char_t string[])
{
    while(R_RLIN30_GetStatus() == RLIN_BUSY);
    
    if(R_RLIN30_GetStatus()== RLIN_READY)
        {
            R_RLIN30_UartSendString(string);
        }
}
