/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_led.c                                                         */
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
/* Functions for controlling LEDs on the StarterKit.                         */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_led.h"

/* Peripheral Includes */
#include "port/r_port.h"
#include "pwmd/r_pwmd.h"
#include "tau/r_tau.h"
#include "csi/r_csi.h"

/*===========================================================================*/
/* Variables */
/*===========================================================================*/
uint32_t g_PWMDClockInitDone = 0;
/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    R_LED_GpioInit
** Description: Set to Pin to which the corresponding LED is connected to GPIO Output
** Parameter:   LED1
**              LED2
**              LEDR - Red LED
**              LEDG - Green LED
**              LEDB - Blue LED
** Return:      None
******************************************************************************/
void R_LED_GpioInit(enum LEDs LED)
{ 
  switch(LED)
  {
    case LED1:
        R_PORT_SetGpioOutput(Port0, 11, Low);
    break;
    
    case LED2:
        R_PORT_SetGpioOutput(Port8, 5, Low);
    break;
    
    case LEDR:
        R_PORT_SetGpioOutput(Port20, 0, Low);
    break;
    
    case LEDG:
        R_PORT_SetGpioOutput(Port20, 1, Low);
    break;
    
    case LEDB:
        R_PORT_SetGpioOutput(Port20, 2, Low);
    break;
    
    default:
    break;
  }
}

/*****************************************************************************
** Function:    R_LED_GpioOn
** Description: Switches specified LED on.
** Parameter:   LED1
**              LED2
**              LEDR - Red LED
**              LEDG - Green LED
**              LEDB - Blue LED
** Return:      None
******************************************************************************/
void R_LED_GpioOn(enum LEDs LED)
{ 
  switch(LED)
  {
    case LED1:
        R_PORT_SetGpioOutput(Port0, 11, High);
    break;
    
    case LED2:
        R_PORT_SetGpioOutput(Port8, 5, High);
    break;
    
    case LEDR:
        R_PORT_SetGpioOutput(Port20, 0, High);
    break;
    
    case LEDG:
        R_PORT_SetGpioOutput(Port20, 1, High);
    break;
    
    case LEDB:
        R_PORT_SetGpioOutput(Port20, 2, High);
    break;
    
    default:
    break;
  }
}

/*****************************************************************************
** Function:    R_LED_GpioOff
** Description: Switches specified LED off.
** Parameter:   LED1
**              LED2
**              LEDR - Red LED
**              LEDG - Green LED
**              LEDB - Blue LED
** Return:      None
******************************************************************************/
void R_LED_GpioOff(enum LEDs LED)
{ 
  switch(LED)
  {
    case LED1:
        R_PORT_SetGpioOutput(Port0, 11, Low);
    break;
    
    case LED2:
        R_PORT_SetGpioOutput(Port8, 5, Low);
    break;
    
    case LEDR:
        R_PORT_SetGpioOutput(Port20, 0, Low);
    break;
    
    case LEDG:
        R_PORT_SetGpioOutput(Port20, 1, Low);
    break;
    
    case LEDB:
        R_PORT_SetGpioOutput(Port20, 2, Low);
    break;
    
    default:
    break;
  }
}

/*****************************************************************************
** Function:    R_LED_PwmInit
** Description: Initializes PWM usage for specified LED.
** Parameter:   LED1
**              LED2
**              LEDR - Red LED
**              LEDG - Green LED
**              LEDB - Blue LED
** Return:      None
******************************************************************************/
void R_LED_PwmInit(enum LEDs LED)
{
    switch(LED)
    {
        case LED1:
            R_TAUB0_Channel6_Init();
            R_TAUB0_Channel8_Init();
            R_PORT_SetAltFunc(Port0, 11, Alt3, Output);
        break;
        
        case LED2:
            R_TAUJ0_Channel2_Init();
            R_TAUJ0_Channel3_Init();
            R_PORT_SetAltFunc(Port8, 5, Alt1, Output);
        break;
        
        case LEDR:
            R_PWMD_Channel64Init();
            R_PORT_SetAltFunc(Port20, 0, Alt2, Output);
        break;
        
        case LEDG:
            R_PWMD_Channel65Init();
            R_PORT_SetAltFunc(Port20, 1, Alt2, Output);
        break;
        
        case LEDB:
            R_PWMD_Channel66Init();
            R_PORT_SetAltFunc(Port20, 2, Alt2, Output);
        break;
        
        default:
        break;
    }
    if(!g_PWMDClockInitDone)
    {
        R_PWMD_ClockInit();
        g_PWMDClockInitDone = 1;
    }
}
            
            
/*****************************************************************************
** Function:    R_LED_SetPwmDuty
** Description: Sets the duty cycle of specified LED correspondingly.
** Parameter:   LED1
**              LED2
**              LEDR - Red LED
**              LEDG - Green LED
**              LEDB - Blue LED
**
**              CompareValue - compare value [0-4095]
** Return:      None
******************************************************************************/
void R_LED_SetPwmDuty(enum LEDs LED, uint16_t CompareValue)
{
    switch(LED)
    {
        case LED1:
            R_TAUB0_CDR_Update(TAUB0C8, CompareValue);
        break;
        
        case LED2:
            R_TAUJ0_CDR_Update(TAUJ0C3, CompareValue);
        break;
        
        case LEDR:
            R_PWMD_Channel64DutyUpdate(CompareValue);
        break;
        
        case LEDG:
            R_PWMD_Channel65DutyUpdate(CompareValue);
        break;
        
        case LEDB:
            R_PWMD_Channel66DutyUpdate(CompareValue);
        break;
        
        default:
        break;
    }        
}        

/*****************************************************************************
** Function:    R_LED_PwmStart
** Description: Starts PWM output for specified LED.
** Parameter:   LED1
**              LED2
**              LEDR - Red LED
**              LEDG - Green LED
**              LEDB - Blue LED
** Return:      None
******************************************************************************/
void R_LED_PwmStart(enum LEDs LED)
{
    switch(LED)
    {
        case LED1:
            R_TAUB0_Channel_Start(TAUB0C6|TAUB0C8);
        break;
        
        case LED2:
            R_TAUJ0_Channel_Start(TAUJ0C2|TAUJ0C3);
        break;
        
        case LEDR:
            R_PWMD_StartChannel(64);
        break;
        
        case LEDG:
            R_PWMD_StartChannel(65);
        break;
        
        case LEDB:
            R_PWMD_StartChannel(66);
        break;
        
        default:
        break;
    }     
}        
        
/*****************************************************************************
** Function:    R_LED_PwmStop
** Description: Stops PWM output for specified LED.
** Parameter:   LED1
**              LED2
**              LEDR - Red LED
**              LEDG - Green LED
**              LEDB - Blue LED
** Return:      None
******************************************************************************/
void R_LED_PwmStop(enum LEDs LED)
{
    switch(LED)
    {
        case LED1:
            R_TAUB0_Channel_Stop(TAUB0C6|TAUB0C8);
        break;
        
        case LED2:
            R_TAUJ0_Channel_Stop(TAUJ0C2|TAUJ0C3);
        break;
        
        case LEDR:
            R_PWMD_StopChannel(64);
        break;
        
        case LEDG:
            R_PWMD_StopChannel(65);
        break;
        
        case LEDB:
            R_PWMD_StopChannel(66);
        break;
        
        default:
        break;
    }
}

/*****************************************************************************
** Function:    R_LED_RgbDiagInit
** Description: Initializes the PWM diagnostic functionality for the RGB LEDs.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LED_RgbDiagInit(void)
{
    R_PWMD_DiagInit();
}

/*****************************************************************************
** Function:    R_LED_RgbDiagStart
** Description: Starts RGB LED PWM diagnosis.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LED_RgbDiagStart(void)
{
    R_PWMD_DiagStart();
}

/*****************************************************************************
** Function:    R_LED_RgbDiagStop
** Description: Initializes the PWM diagnostic functionality for the RGB LEDs.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LED_RgbDiagStop(void)
{
    R_PWMD_DiagStop();
}

/*****************************************************************************
** Function:    R_LED_RingInit
** Description: Initializes CSIH and Ports for LED Ring.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LED_RingInit(void)
{
    /* Configure GPIO Pins */
    R_PORT_SetGpioOutput(Port1, 14, Low);           /* LatchEnable      */
    R_PORT_SetGpioOutput(Port1, 15, High);          /* nOutputEnable    */
    
    /* Configure CSIG0 Pins */
    R_PORT_SetAltFunc(Port0, 12, Alt4, Input);      /* CSIG0 MISO   */
    R_PORT_SetAltFunc(Port0, 13, Alt4, Output);     /* CSIG0 MOSI   */
    R_PORT_SetAltFunc(Port0, 14, Alt4, Output);     /* CSIG0 CLK    */
    
    R_CSIG0_Init();
    R_CSIG0_TransmitData(0);                        /* All LEDs off */
    R_PORT_SetGpioOutput(Port1, 14, High);          /* Toggle Latch */
    R_PORT_SetGpioOutput(Port1, 14, Low);
}

/*****************************************************************************
** Function:    R_LED_RingOutputEnable
** Description: Enables output to Ring LEDs.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LED_RingOutputEnable(void)
{
    R_PORT_SetGpioOutput(Port1, 15, Low);
}

/*****************************************************************************
** Function:    R_LED_RingOutputDisable
** Description: Disables output to Ring LEDs.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LED_RingOutputDisable(void)
{
    R_PORT_SetGpioOutput(Port1, 15, High);
}

/*****************************************************************************
** Function:    R_LED_RingUpdate
** Description: Updates the output pattern of Ring LEDs.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_LED_RingUpdate(uint16_t LedBitMask)
{
    R_CSIG0_TransmitData(LedBitMask);
    R_PORT_SetGpioOutput(Port1, 14, High);    /* Toggle Latch */
    R_PORT_SetGpioOutput(Port1, 14, Low);
}
