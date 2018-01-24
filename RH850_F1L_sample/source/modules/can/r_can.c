/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_can.c                                                         */
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
/* Functions for CAN initialization and testing.                             */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "rscan/r_rscan.h"

/* Peripheral Includes */
#include "port/r_port.h"

/*===========================================================================*/
/* Variables */
/*===========================================================================*/
/* Create Can_FrameType for send and receive data */
const r_CANFrame_t CANTraStandData={
  /*CiTBpA */
  0x18u,
  0u,
  0u,
  0u,        
    
  /*CiTBpB */
  0x0000u,                            
  0x000u,                            
  0x8u,    
    
  {
    0x12u,                            /*DB0 */
    0x34u,                            /*DB1 */
    0x56u,                            /*DB2 */
    0x78u,                            /*DB3 */
    /*CiTBpD */
    0x87u,                            /*DB4 */
    0x65u,                            /*DB5 */
    0x43u,                            /*DB6 */
    0x21u                             /*DB7 */
  }
};

r_CANFrame_t CANRecData={
  /*CiTBpA */
  0x00u,
  0u,
  0u,
  0u,
    
  /*CiTBpB */
  0x0000u,                                
  0x000u,                            
  0x0u,                        

  /*CiTBpC */
  {
    0x00u,                            /*DB0 */
    0x00u,                            /*DB1 */
    0x00u,                            /*DB2 */
    0x00u,                            /*DB3 */
    /*CiTBpD */
    0x00u,                            /*DB4 */
    0x00u,                            /*DB5 */
    0x00u,                            /*DB6 */
    0x00u                             /*DB7 */
  }
};

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    R_CAN_Init
** Description: Configures CAN0 Channel 3 & 4 and the corresponding pins.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_CAN_Init(void)
{
    R_PORT_SetAltFunc(Port1, 2, Alt1, Input);   /* CAN3 RX */
    R_PORT_SetAltFunc(Port1, 3, Alt1, Output);  /* CAN3 TX*/
    R_PORT_SetAltFunc(Port1, 12, Alt1, Input);  /* CAN4 TX*/
    R_PORT_SetAltFunc(Port1, 13, Alt1, Output); /* CAN4 RX */
    
    /* Enable Transceiver CAN0 */
    R_PORT_SetGpioOutput(Port1, 1, High);
    
    /* Enable Transceiver CAN1 */
    R_PORT_SetGpioOutput(Port2, 6, High);
    
    R_RSCAN0_Init(); /* Initialize CAN3 and CAN4 */
}

/*****************************************************************************
** Function:    R_CAN_Deinit
** Description: Configures used pins back to default.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_CAN_Deinit(void)
{
    R_PORT_SetGpioHighZ(Port1, 2);
    R_PORT_SetGpioHighZ(Port1, 3);
    R_PORT_SetGpioHighZ(Port1, 12);
    R_PORT_SetGpioHighZ(Port1, 13);
    R_PORT_SetGpioHighZ(Port1, 1); 
    R_PORT_SetGpioHighZ(Port2, 6);
}
    
/*****************************************************************************
** Function:    R_CAN_Test
** Description: Sends a CAN frame on channel 3 and compares with received data 
**              on channel 4. 
** Parameter:   None
** Return:      R_OK - Received frame matches sent frame.
**              R_ERROR - Mismatch detected.
******************************************************************************/
r_Error_t R_CAN_Test(void)
{
  uint32_t db_count, i;
   
  if(R_RSCAN0_C3TrmByTxBuf(1u,&CANTraStandData)== CAN_RTN_OK)
  {
        /*Delay */
    for(i=0; i<100000;i++)
    {
       
    }
    
  }
  if(R_RSCAN0_ReadRxBuffer(&CANRecData)==CAN_RTN_OK)    /* Channel4 receive the Messages */
  {
      /* Compare each sent and received value */
      for(db_count=0; db_count<8; db_count++)
      {
        if(CANTraStandData.DB[db_count] != CANRecData.DB[db_count])
        {
          return R_ERROR;
        }
      }
      return R_OK;
  }
  else
    {
        return R_ERROR;
    }
}
