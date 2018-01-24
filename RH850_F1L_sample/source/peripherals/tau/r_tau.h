/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_tau.h                                                         */
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
#ifndef R_TAU_H
#define R_TAU_H

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
#define TAUJ0C0     0x01
#define TAUJ0C1     0x02
#define TAUJ0C2     0x04
#define TAUJ0C3     0x08

#define TAUB0C6     0x0040
#define TAUB0C8     0x0100

/*===========================================================================*/
/* Function defines */
/*===========================================================================*/
void R_TAUJ0_CK0_Prescaler(uint8_t Prescaler);
void R_TAUJ0_CDR_Update(uint16_t TAUJ0_Channel, uint16_t CDR_val);
void R_TAUJ0_Channel0_Init(void);
void R_TAUJ0_Channel1_Init(void);
void R_TAUJ0_Channel2_Init(void);
void R_TAUJ0_Channel3_Init(void);
void R_TAUJ0_Channel_Start(uint16_t TAUJ0_Channel);
void R_TAUJ0_Channel_Stop(uint16_t TAUJ0_Channel);
void R_TAUJ0_AssignChannel1ISR(void ISR_Ptr(void));

void R_TAUB0_CK0_Prescaler(uint8_t Prescaler);
void R_TAUB0_Channel6_Init(void);
void R_TAUB0_Channel8_Init(void);
void R_TAUB0_CDR_Update(uint16_t TAUB0_Channel, uint16_t CDR_val);
void R_TAUB0_Channel_Start(uint16_t TAUB0_Channel);
void R_TAUB0_Channel_Stop(uint16_t TAUB0_Channel);

#endif /* R_TAU_H */
