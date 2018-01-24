/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_port.h                                                        */
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
#ifndef R_PORT_H
#define R_PORT_H

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
/* Defines for filter settings */
#define R_FCLA_LEVEL_DETECTION  0x00
#define R_FCLA_LOW_LEVEL        0x00
#define R_FCLA_HIGH_LEVEL       0x01
#define R_FCLA_EDGE_DETECTION   0x04
#define R_FCLA_FALLING_EDGE     0x02
#define R_FCLA_RISING_EDGE      0x01

/* Enumeration for alternative functions of port pins */
enum alt_t
{
    Alt1,
    Alt2,
    Alt3,
    Alt4,
    Alt5,
};

enum io_t
{
    Input,
    Output
};

enum level_t
{
    Low = 0,
    High = 1
};

/* Enumeration for analog filter signals */
enum fcla_signal_t
{
    R_FCLA_INTP0 = 0,
    R_FCLA_INTP1,
    R_FCLA_INTP2,
    R_FCLA_INTP3,
    R_FCLA_INTP4,
    R_FCLA_INTP5,
    R_FCLA_INTP6,
    R_FCLA_INTP7,
    R_FCLA_INTP8,
    R_FCLA_INTP9,
    R_FCLA_INTP10,
    R_FCLA_INTP11,
    R_FCLA_INTP12,
    R_FCLA_INTP13,
    R_FCLA_INTP14,
    R_FCLA_INTP15,
    R_FCLA_NMI = 0x10
};

/* Structure of registers for each port */
struct pregs_t
{
    volatile uint16_t * P_Reg;
    volatile uint16_t * PNOT_Reg;
    volatile uint16_t * PM_Reg;
    volatile uint16_t * PMC_Reg;
    volatile uint16_t * PFC_Reg;
    volatile uint16_t * PFCE_Reg;
    volatile uint16_t * PFCAE_Reg;
    volatile uint16_t * PIPC_Reg;
    volatile uint16_t * PIBC_Reg;
    volatile const uint16_t * PPR_Reg;
    volatile uint16_t * PD_Reg;
    volatile uint16_t * PU_Reg;
    volatile uint32_t * PODC_Reg;
};

/* Enumeration for ports corresponding to the PortList */
enum port_t
{
    Port0 = 0,
    Port1,
    Port2,
    Port8,
    Port9,
    Port10,
    Port11,
    Port12,
    Port18,
    Port20,
    APort0,
    APort1
};

/* Array with available registers for the available ports. Registers that are not available */
/* for a port are 0.                                                                        */
static const struct pregs_t PortList[]=
{
  {(volatile uint16_t *)&P0,(volatile uint16_t *) &PNOT0,(volatile uint16_t *) &PM0,(volatile uint16_t *) &PMC0, (volatile uint16_t *)&PFC0, (volatile uint16_t *)&PFCE0, (volatile uint16_t *)&PFCAE0, (volatile uint16_t *)&PIPC0, (volatile uint16_t *)&PIBC0,(volatile uint16_t *) &PPR0, (volatile uint16_t *)&PD0, (volatile uint16_t *)&PU0,(volatile uint32_t *)&PODC0},
  {(volatile uint16_t *)&P1,(volatile uint16_t *) &PNOT1, (volatile uint16_t *)&PM1, (volatile uint16_t *)&PMC1, (volatile uint16_t *)&PFC1, 0, 0, 0, (volatile uint16_t *)&PIBC1, (volatile uint16_t *)&PPR1, 0, (volatile uint16_t *)&PU1, (volatile uint32_t *)&PODC1},
  {(volatile uint16_t *)&P2, (volatile uint16_t *)&PNOT2, (volatile uint16_t *)&PM2, (volatile uint16_t *)&PMC2, 0, 0, 0, 0, (volatile uint16_t *)&PIBC2, (volatile uint16_t *)&PPR2, 0, (volatile uint16_t *)&PU2, (volatile uint32_t *)&PODC2},
  {(volatile uint16_t *)&P8, (volatile uint16_t *)&PNOT8, (volatile uint16_t *)&PM8, (volatile uint16_t *)&PMC8, (volatile uint16_t *)&PFC8, (volatile uint16_t *)&PFCE8, 0, 0, (volatile uint16_t *)&PIBC8, (volatile uint16_t *)&PPR8, (volatile uint16_t *)&PD8, (volatile uint16_t *)&PU8, (volatile uint32_t *)&PODC8},
  {(volatile uint16_t *)&P9, (volatile uint16_t *)&PNOT9, (volatile uint16_t *)&PM9, (volatile uint16_t *)&PMC9, (volatile uint16_t *)&PFC9, (volatile uint16_t *)&PFCE9, 0, 0, (volatile uint16_t *)&PIBC9, (volatile uint16_t *)&PPR9, (volatile uint16_t *)&PD9, (volatile uint16_t *)&PU9, (volatile uint32_t *)&PODC9},
  {(volatile uint16_t *)&P10, (volatile uint16_t *)&PNOT10, (volatile uint16_t *)&PM10, (volatile uint16_t *)&PMC10, (volatile uint16_t *)&PFC10, (volatile uint16_t *)&PFCE10, (volatile uint16_t *)&PFCAE10, (volatile uint16_t *)&PIPC10, (volatile uint16_t *)&PIBC10, (volatile uint16_t *)&PPR10, (volatile uint16_t *)&PD10, (volatile uint16_t *)&PU10, (volatile uint32_t *)&PODC10},
  {(volatile uint16_t *)&P11, (volatile uint16_t *)&PNOT11, (volatile uint16_t *)&PM11, (volatile uint16_t *)&PMC11, (volatile uint16_t *)&PFC11, (volatile uint16_t *)&PFCE11, (volatile uint16_t *)&PFCAE11, (volatile uint16_t *)&PIPC11, (volatile uint16_t *)&PIBC11, (volatile uint16_t *)&PPR11, (volatile uint16_t *)&PD11, (volatile uint16_t *)&PU11, (volatile uint32_t *)&PODC11},
  {(volatile uint16_t *)&P12, (volatile uint16_t *)&PNOT12, (volatile uint16_t *)&PM12, (volatile uint16_t *)&PMC12, (volatile uint16_t *)&PFC12, (volatile uint16_t *)&PFCE12, 0, 0, (volatile uint16_t *)&PIBC12, (volatile uint16_t *)&PPR12, 0, (volatile uint16_t *)&PU12, (volatile uint32_t *)&PODC12},
  {(volatile uint16_t *)&P18, (volatile uint16_t *)&PNOT18, (volatile uint16_t *)&PM18, (volatile uint16_t *)&PMC18, (volatile uint16_t *)&PFC18, 0, 0, 0, (volatile uint16_t *)&PIBC18, (volatile uint16_t *)&PPR18, 0, (volatile uint16_t *)&PU18, (volatile uint32_t *)&PODC18},
  {(volatile uint16_t *)&P20, (volatile uint16_t *)&PNOT20, (volatile uint16_t *)&PM20, (volatile uint16_t *)&PMC20, (volatile uint16_t *)&PFC20, 0, 0, 0, (volatile uint16_t *)&PIBC20, (volatile uint16_t *)&PPR20, 0, (volatile uint16_t *)&PU20, (volatile uint32_t *)&PODC20},
  {(volatile uint16_t *)&AP0, (volatile uint16_t *)&APNOT0, (volatile uint16_t *)&APM0, 0, 0, 0, 0, 0, (volatile uint16_t *)&APIBC0, (volatile uint16_t *)&APPR0, 0, 0, 0},
  {(volatile uint16_t *)&AP1, (volatile uint16_t *)&APNOT1, (volatile uint16_t *)&APM1, 0, 0, 0, 0, 0, (volatile uint16_t *)&APIBC1, (volatile uint16_t *)&APPR1, 0, 0, 0}
};

/*===========================================================================*/
/* Function defines */
/*===========================================================================*/
void R_PORT_SetGpioOutput(enum port_t Port, uint32_t Pin, enum level_t Level);
void R_PORT_ToggleGpioOutput(enum port_t Port, uint32_t Pin);
void R_PORT_SetGpioInput(enum port_t Port, uint32_t Pin);
void R_PORT_SetGpioHighZ(enum port_t Port, uint32_t Pin);
void R_PORT_SetAltFunc(enum port_t Port, uint32_t Pin, enum alt_t Alt, enum io_t IO);
uint32_t R_PORT_GetLevel(enum port_t Port, uint32_t Pin);
void R_PORT_SetOpenDrain(enum port_t Port, uint32_t Pin);
void R_PORT_SetPushPull(enum port_t Port, uint32_t Pin);
void R_PORT_SetAnalogFilter(enum fcla_signal_t InputSignal, uint8_t FilterSetting);

#endif /* R_PORT_H */
