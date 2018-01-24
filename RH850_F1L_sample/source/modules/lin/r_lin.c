/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_lin.c                                                         */
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
/* Source code for LIN initialization and testing.                           */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_lin.h"

/* Peripheral Includes */
#include "port/r_port.h"
#include "rlin/r_rlin.h"

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    R_LIN_Init
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LIN_Init(void)
{
    R_PORT_SetAltFunc(Port0, 7, Alt1, Input);  /* RLIN24RX */
    R_PORT_SetAltFunc(Port0, 8, Alt1, Output); /* RLIN24TX */
    
    R_RLIN24_BaudrateInit();
    R_RLIN24_Channel1Init();
}

/*****************************************************************************
** Function:    R_LIN_Test
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LIN_Deinit(void)
{
    R_PORT_SetGpioHighZ(Port0, 7);
    R_PORT_SetGpioHighZ(Port0, 8); 
}

/*****************************************************************************
** Function:    R_LIN_Test
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
r_Error_t R_LIN_Test(void)
{
    uint8_t ID = 0x00;
        
    uint8_t TxDB[8] = {
        0x55,
        0x55,
        0x55,
        0x55,
        0x55,
        0x55,
        0x55,
        0x55
    };

    if(R_RLIN24_Channel1TxFrame(ID, TxDB) == RLIN_OK)
        {
            return R_OK;
        }
    else
        {
            return R_ERROR;
        }
}

/*****************************************************************************
** Function:    R_LIN_Test
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
uint8_t R_LIN_TxFrame(uint8_t ID, uint8_t TxDB[])
{
    if(R_RLIN24_Channel1TxFrame(ID, TxDB)==RLIN_OK)
        {
            return LIN_OK;
        }
    else
        {
            return LIN_ERROR;
        }
}

/*****************************************************************************
** Function:    R_LIN_Test
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
uint8_t R_LIN_RxFrame(uint8_t RxDB[])
{
    if(R_RLIN24_Channel1RxFrame(RxDB)==RLIN_OK)
        {
            return LIN_OK;
        }
    else
        {
            return LIN_ERROR;
        }
}
