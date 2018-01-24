/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_system.h                                                      */
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
#ifndef R_SYSTEM_H
#define R_SYSTEM_H

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
/* Wake-up factors */
#define R_WUF_RESET                 (uint32_t)0x00
#define R_WUF_LPS_AI                (uint32_t)(1<<14)
#define R_WUF_LPS_DI                (uint32_t)(1<<19)
#define R_WUF_INTP12                (uint32_t)(1<<23)
#define R_WUF_INTP15                (uint32_t)(1<<27)
#define R_WUF_DCUTDI                (uint32_t)(1<<31)
#define R_WUF_ERROR                 (uint32_t)0xff


#define R_RESF_DeepSTOP       (uint32_t)(1<<10)
#define R_RESF_PowerUp        (uint32_t)(1<< 9)
#define R_RESF_External       (uint32_t)(1<< 8)
#define R_RESF_CVM            (uint32_t)(1<< 7)
#define R_RESF_LVI            (uint32_t)(1<< 6)
#define R_RESF_CLMA2          (uint32_t)(1<< 5)
#define R_RESF_CLMA1          (uint32_t)(1<< 4)
#define R_RESF_CLMA0          (uint32_t)(1<< 3)
#define R_RESF_WDTA1          (uint32_t)(1<< 2)
#define R_RESF_WDTA0          (uint32_t)(1<< 1)
#define R_RESF_Software       (uint32_t)(1<< 0)

       
/* Poti sense for DeepSTOP timer reset and Wake-up */
#define DEEPSTOP_POTI_SENSE         256u
/*===========================================================================*/
/* Function defines */
/*===========================================================================*/
void R_SYSTEM_ClockInit(void); 
void R_SYSTEM_PrepareDeepSTOP(void);
void R_SYSTEM_TimerInit(void);
void R_SYSTEM_TimerTick(void);
void R_SYSTEM_TimerStart(void);
void R_SYSTEM_TimerStop(void);
uint32_t R_SYSTEM_GetResetCause(void);
void R_SYSTEM_ClearResetCause(void);



#endif /* R_SYSTEM_H */
