/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_adc.c                                                         */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2015 by Renesas Electronics Europe GmbH,                    */
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
/* Source code for the ADC Functions.                                        */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_adc.h"
/*===========================================================================*/
/* Variables */
/*===========================================================================*/
/* Call-back function pointer called in ADCA0 error interrupt */
void (*R_ADCA0_LimitErrorCB)(uint32_t) = R_NULL;

/*===========================================================================*/
/* Interrupts */
/*===========================================================================*/
/******************************************************************************
** Function:    INTADCA0ERR
** Description: Interrupt is generated when an upper/lower limit error or 
**              overwrite error occurs. If the interrupt is caused by upper/lower
**              limit error, call-back function R_ADCA0_LimitErrorCB is called.
**              Content of upper/lower limit error information register is 
**              passed to the call-back function.
** Parameter:   None
** Return:      None
******************************************************************************/
#ifdef __IAR__
#pragma vector = NUMINTADCA0ERR
__interrupt void INTADCA0ERR(void)
#endif /* __IAR__ */
#ifdef __GHS__
  #pragma ghs interrupt
void INTADCA0ERR(void)
#endif /* __GHS__ */
#ifdef __CSP__
  #pragma interrupt INTADCA0ERR(enable=manual)
  void INTADCA0ERR(void)
#endif /* __CSP__*/
{
	if(ADCA0ULER & 0xC000)
	{
		if(R_ADCA0_LimitErrorCB != R_NULL)
		{
			R_ADCA0_LimitErrorCB(ADCA0ULER);	/* Upper/Lower Error information is given to the error call back function */
		}
		ADCA0ECR = 0x08u;            		    /* Set the ULEC bit of the ErrorClearRegister of ADCA0 to clear the upper/lower limit error flag */
	}
}

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/******************************************************************************
** Function:    R_ADCA0_AssignLimitErrorCB
** Description: Assigns a call-back function to the function pointer which is 
**              called inside the ADCA0 error interrupt in case of limite error
**              detection.
** Parameter :  CB_Ptr - Pointer to call back function. 
** Return:      None
******************************************************************************/
void R_ADCA0_AssignLimitErrorCB(void (CB_Ptr)(uint32_t))
{
    R_ADCA0_LimitErrorCB = CB_Ptr;
}

/******************************************************************************
** Function:    R_ADCA0_ConnectPullDown
** Description: Connect internal Pull Down resistance to pin AP0_x.
** Parameter :  AP0_x - Analog Port 0 Pin x
** Return:      None
******************************************************************************/
void R_ADCA0_ConnectPullDown(enum APorts AP_x)
{
  ADCA0PDCTL1 |= 1<<AP_x;
}

/******************************************************************************
** Function:    R_ADCA0_DisconnectPullDown
** Description: Disconnect internal Pull Down resistance to pin AP0_x.
** Parameter :  AP0_x - Analog Port 0 Pin x
** Return:      None
******************************************************************************/
void R_ADCA0_DisconnectPullDown(enum APorts AP0_x)
{
  ADCA0PDCTL1 &= ~(1<<AP0_x);
}

/******************************************************************************
** Function:    R_ADCA0_Init
** Description: This function initializes ADCA0 for the use of scan-group SG1
**              containing one virtual channel. 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_ADCA0_Init(void)
{
  ADCA0ADCR = 0x02u;      /* Asynchronous suspend / 12bit mode / PWDDR and ADCA0DR00 are set to right align */
                          /* The self-diagnostic voltage circuit is turned off */

  ADCA0SMPCR = 0x18u;     /* Set sampling time to 24*1/40MHz = 60us */
  ADCA0SFTCR = 0x08u;     /* Upper/Lower limit error enabled / DR/DIR registers are not cleared when read */
  ADCA0SGCR1 = 0x10u;     /* ScanGroup interrupt is output when scan ends */
  
  /* ScanGroup start/end registers */
  ADCA0SGVCSP1 = 0x00u;   /* ScanGroup starts at virtual channel 0 */
  ADCA0SGVCEP1 = 0x00u;   /* ScanGroup ends at virtual channel 0 */
}

/******************************************************************************
** Function:    R_ADCA0_PinRead
** Description: This function assigns the chosen analog port to virtual
**              channel 00 of ADCA0, performs the conversion.
** Parameter:   AP0_x - Analog Port 0 Pin x
** Return:      loc_ReturnValue - Result of virtual channel 00
******************************************************************************/
uint16_t R_ADCA0_PinRead(enum APorts AP0_x)
{
  uint16_t loc_ReturnValue = 0u;
  ADCA0VCR00 = AP0_x;
  
  ADCA0SGSTCR1 = 1u;                              /* Conversion start trigger */
  while((ADCA0DIR00&(1<<25))==0)
  {
      /* Wait until value is stored */
  }
  loc_ReturnValue = (uint16_t) ADCA0DIR00&0xffffu;  /* Return the lower 16bit which are the read value */

  return loc_ReturnValue;
}

/******************************************************************************
** Function:    R_ADCA0_LpsInit
** Description: This function initializes ADC for LPS usage.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_ADCA0_LpsInit(void)
{
  ADCA0VCR00 = 0x40u;      /* Virtual Channel 0 of ADCA0 is linked to physical channel ADCA0I4 (LPS) / Limits checked in ADCA0ULLMTBR0 */
  ADCA0ECR = 0x0cu;        /* Set the ULEC bit of the ErrorClearRegister of ADCA0 to clear the upper/lower limit error flag */
  
  ADCA0SGCR1 = 0x00u;      /* Hardware trigger disabled / No interrupt is output when scan ends */
  ADCA0SFTCR = 0x08u;      /* Upper/Lower limit interrupt enabled */
  ADCA0SMPCR = 0x12u;      /* ADC Sampling Control Setting */
  ADCA0ADCR = 0x00u;       /* ADC Common Operation Control Setting */
  ADCA0SGTSEL1 = 0x10u;    /* LPS as hardware trigger selected */
  ADCA0SGCR1 = 0x11u;      /* INT_SGx is output when the scan for SGx ends / Hardware trigger enabled */
}

/******************************************************************************
** Function:    R_ADCA0_SetUpperLowerLimit
** Description: This function sets the upper/lower limit for the corresponding
**              Upper/Lower Limit Table.
** Parameter:   limit_channel - Limit Channel [0-2]
**              upper - Upper Limit[0-4095]
**              lower - Lower Limit[0-4095]
** Return:      None
******************************************************************************/
void R_ADCA0_SetUpperLowerLimit(uint32_t limit_table, uint16_t upper, uint16_t lower)
{
  /* Select the upper and lower limit values */
  switch(limit_table)
  {
    /* Limit registers: [31:20] Upper limit, [15:4] Lower limit */
    case 0u:
      ADCA0ULLMTBR0 =  ((uint32_t)upper << 20);   /* Set upper limit */
      ADCA0ULLMTBR0 |=  ((uint32_t)lower << 4);   /* Set lower limit */
    break;
    
    case 1u:
      ADCA0ULLMTBR1 =  ((uint32_t)upper << 20);   /* Set upper limit */
      ADCA0ULLMTBR1 |=  ((uint32_t)lower << 4);   /* Set lower limit */
    break;
    
    case 2u:
      ADCA0ULLMTBR2 =  ((uint32_t)upper << 20);   /* Set upper limit */
      ADCA0ULLMTBR2 |=  ((uint32_t)lower << 4);   /* Set lower limit */
    break;
    
    default:
        
    break;
  }
  ADCA0ECR = 0x08u;    /* Set the ULEC bit of the ErrorClearRegister of ADCA0 to clear the upper/lower limit error flag */
}

/******************************************************************************
** Function:    R_ADCA0_PwsaTriggerEnable
** Description: Enables PWSA trigger input to trigger PWM-Diag scan group.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_ADCA0_PwsaTriggerEnable(void)
{
    ADCA0PWDSGCR = 1u;
    ADCA0PDCTL1  = 0x000e;
}

/******************************************************************************
** Function:    R_ADCA0_PwsaTriggerDisable
** Description: Disables PWSA trigger input.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_ADCA0_PwsaTriggerDisable(void)
{
    ADCA0PWDSGCR = 0u;
    ADCA0PDCTL1 = 0x0000;
}

