/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_clkc.h                                                        */
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
#ifndef R_CLKC_H
#define R_CLKC_H

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
#define R_CLKC_STOPMASK_SET         0x03
#define R_CLKC_STOPMASK_RESET       0x02

#define R_CLKC_TAUJ_DISABLE         0x00
#define R_CLKC_TAUJ_HSINTOSC        0x01
#define R_CLKC_TAUJ_MOSC            0x02
#define R_CLKC_TAUJ_LSINTOSC        0x03
#define R_CLKC_TAUJ_PPLLCLK2        0x04

#define R_CLKC_ADCA_DISABLE         0x00
#define R_CLKC_ADCA_HSINTOSC        0x01
#define R_CLKC_ADCA_MOSC            0x02
#define R_CLKC_ADCA_PPLLCLK2        0x03

#define R_CLKC_RSCAN_DISABLE        0x00
#define R_CLKC_RSCAN_MOSC           0x01
#define R_CLKC_RSCAN_PPLLCLK        0x03
#define R_CLKC_RSCAN_DIV_DISBABLE   0x00
#define R_CLKC_RSCAN_DIV_MOSC1      0x01
#define R_CLKC_RSCAN_DIV_MOSC2      0x02

/*===========================================================================*/
/* Function defines */
/*===========================================================================*/
void R_CLKC_PllInit(void);
void R_CLKC_SetRscanClockDomain(uint32_t RscanModuleClockDomain, uint32_t RscanComClockDomain);
void R_CLKC_SetAdca0ClockDomain(uint32_t Adca0ClockDomain);
void R_CLKC_SetTaujClockDomain(uint32_t TaujClockDomain);
void R_CLKC_SetAdca0StopMask(void);
void R_CLKC_ResetAdca0StopMask(void);
void R_CLKC_SetTaujStopMask(void);
void R_CLKC_ResetTaujStopMask(void);

#endif /* R_CLKC_H */