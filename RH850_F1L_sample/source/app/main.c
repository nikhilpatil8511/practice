/*===========================================================================*/
/* Project:  F1x StarterKit Sample Software                                  */
/* Module :  main.c                                                          */
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
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Main file for the F1x StarterKit Sample Software                          */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include <stdio.h>
#include "r_device.h"

/* Include Application */
#include "r_tasks.h"
//

 // #include "subproj.h"
/* Include Modules */
#include "system/r_system.h"

/*===========================================================================*/
/* Defines */
/*===========================================================================*/

/*===========================================================================*/
/* Prototypes */
/*===========================================================================*/
void  main                ( void );


/*===========================================================================*/
/* Interrupt Service Routines - ISR */
/*===========================================================================*/
/*****************************************************************************
** Function:    unused_isr
** Description: Dummy function for unused interrupts
** Parameter:   None
** Return:      None
******************************************************************************/

#ifdef __GHS__
  #pragma ghs interrupt
  void unused_isr(void)
  {
  while(1)
    {     
    }
  }
#endif
/*===========================================================================*/
/* Main function */
/*===========================================================================*/
void main(void) 
{
	    // Clock initialization 
    R_SYSTEM_ClockInit();
   /* int a,b,c;
    a=16;
    b=17;
    PM1  = 1;
    
    //c = add_kar_le(a,b);
   // printf("kitna hua ? %d",c);
    /* Enable interrupts */
    __EI();
    //some_func();
    /* Start the Task-Function */
    R_TASKS_Start();
}


