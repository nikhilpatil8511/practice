/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_led.h                                                         */
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
#ifndef R_LED_H
#define R_LED_H

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
enum LEDs
{
    LEDR,
    LEDG,
    LEDB,
    LED1,
    LED2
};

/*===========================================================================*/
/* Function defines */
/*===========================================================================*/
void R_LED_GpioInit(enum LEDs LED);
void R_LED_GpioOn(enum LEDs LED);
void R_LED_GpioOff(enum LEDs LED);
void R_LED_PwmInit(enum LEDs LED);
void R_LED_SetPwmDuty(enum LEDs LED, uint16_t CompareValue);
void R_LED_PwmStart(enum LEDs LED);
void R_LED_PwmStop(enum LEDs LED);
void R_LED_RgbDiagInit(void);
void R_LED_RgbDiagStart(void);
void R_LED_RgbDiagStop(void);
void R_LED_RingInit(void);
void R_LED_RingOutputEnable(void);
void R_LED_RingOutputDisable(void);
void R_LED_RingUpdate(uint16_t LedBitMask);


#endif /* R_LED_H */