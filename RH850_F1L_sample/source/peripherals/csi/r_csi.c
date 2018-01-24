/*===========================================================================*/
/* Project:  F1x StarterKit Sample Software                                  */
/* Module :  r_csi.c                                                         */
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
/* Source code for the SPI modules CSIG0 and CSIH2.                          */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_csi.h"

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    R_CSIH2_Init
** Description: This function initializes the CSIH2 module for use with 
**              chip-select 4.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_CSIH2_Init(void)
{
   
    CSIH2CTL0   =   0x01;                   // disable CSI
  
    CSIH2CTL1   =  ((1 << 16)|(1 << 4));    //Bit24     :0  internal synchronization timing for receive data input is rising edge of PCLK
                                            //Bit17     :0  The default level of CSIHTSCK is high
                                            //Bit16     :1  early interrupt timing
                                            //Bit8-15   :0  Chip select is active low.
                                            //Bit7      :0  Disables extended data length mode
                                            //Bit6      :0  disables job mode.
                                            //Bit5      :0  Disables data consistency check.
                                            //Bit4      :1  Chip select signal returns to the inactive level after last data transfer
                                            //Bit3      :0  Deactivates loop-back mode (LBM)
                                            //Bit2      :0  No interrupt delay mode
                                            //Bit1      :0  Disables the handshake function.
                                            //Bit0      :0  disables the slave select function.

    CSIH2CTL2   = 0x2000;           // Clock selection: PCLK / 4
  
    CSIH2STCR0  = 0xFFFF;           // clear all status flags

    CSIH2MCTL0  = 0x0100;           // Bit8-9:1 Dual buffer mode
                                    // Bit0-4:0 no time-out detection
                                  
    CSIH2MRWP0  = 0x00000000;       // reset read and write pointers
 
    CSIH2BRS0   = 0x0002;           //  10MHz
  

 /* CSIHnCFGx specifys each chip select signal 
    Bit 30-31 select the baud rate setting
    Bit 24-27 select the data length for the chip select signal
    Bit 17    clock phase selection
    Bit 16    data phase selection */
    
    CSIH2CFG4   = 0x08030000;      // configure CS2: Baudrate BRS0, 8 Bit, MSB first
 
    CSIH2CTL0  |=  0xC0;           // provides operation clock, permits transmission
}

/******************************************************************************
** Function:    R_CSIH2_C4_SetTxSize
** Description: Configures the number of bits sent by each tranfer of chip-select 4.
** Parameter:   Size - Number of transmitted bits.
** Return:      None
******************************************************************************/
void R_CSIH2_C4_SetTxSize(uint8_t Size)
{
    Size &= 0xF;
    CSIH2CFG4 &= 0xF0FFFFFF;
    CSIH2CFG4 |= Size<<24;
} 

/******************************************************************************
** Function:    R_CSIH2_TransmitBuffer
** Description: Transmits an array of 16bit values with chip-select 4.
** Parameter:   TxDataPtr - Pointer to Transmission Data
**              length - Length of array
** Return:      None
******************************************************************************/
void R_CSIH2_TransmitBuffer(uint16_t* TxDataPtr, uint16_t length)
{   
    uint16_t i;
    
    while(CSIH2STR0 & (1 << 7));                /* Wait until transmission finished */
    for(i=0; i<length; i++)
    {
        CSIH2TX0W = 0x00EF0000|TxDataPtr[i];    /* Set Transmit Data */ 
        while(CSIH2STR0 & (1 << 7));            /* Wait until transmission finished */
    }
}

/******************************************************************************
** Function:    R_CSIH2_TransmitData
** Description: Transmits a single data frame with chip-select 4.
** Parameter:   TxDataPtr - Pointer to Transmission Data
** Return:      None
******************************************************************************/
void R_CSIH2_TransmitData(uint16_t TxData)
{
    while(CSIH2STR0 & (1 << 7));        /* Wait until transmission finished */
    CSIH2TX0W  = 0x00EF0000|TxData;     /* Set Transmit Data */ 
    while(CSIH2STR0 & (1 << 7));        /* Wait until transmission finished */
}


/******************************************************************************
** Function:    R_CSIG0_Init
** Description: This function initializes the CSIG0 module.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_CSIG0_Init (void)
{
    CSIG0CTL0= 0xc1;            /* Transmission enabled/ Reception disabled/ supplies operation clock */
    CSIG0CTL1= 0x200a1;         /* Enables slave select function/ handshake disabled */
                                /* No interrupt delay/ loop-back mode deactivated */
                                /* Data consitency check enabled/ enables extended data length */
                                /* Normal interrupt timing*/
                          
    CSIG0CTL2= 0x8001;          /* PCLK/16 -> communication clock/ PCLK/32 transfer clock frequency */
    
    /* Configures the communication protocol */
    CSIG0CFG0=0x00010000;       /* Data phase selection CSIGnDAP set to 0 */
                                /* Data transmitted/received with MSB first/ data length is 16bits */
                                /* No parity bit transmitted */
  
     
}
/******************************************************************************
** Function:    R_CSIG0_TransmitData
** Description: Transmits a single data frame with CSIG0.
** Parameter:   TxData - Transmission Data
** Return:      None
******************************************************************************/
 void R_CSIG0_TransmitData(uint16_t TxData)
{
    while(CSIG0STR0 & (1<<7));  /* Wait until transmission finished */
    CSIG0TX0H = TxData;
    while(CSIG0STR0 & (1<<7));  /* Wait until transmission finished */
}  
