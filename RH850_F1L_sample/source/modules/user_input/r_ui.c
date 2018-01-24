/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_ui.c                                                          */
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
/* Functions to handle user inputs on the StarterKit Board.                  */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_ui.h"

/* Peripheral Includes */
#include "adc/r_adc.h"
#include "enc/r_enc.h"
#include "port/r_port.h"

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
#define R_PRESS_SHORT         10
#define R_PRESS_LONG        1000

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
/*****************************************************************************
** Function:    R_UI_Poti1_Init
** Description: Configure AP0_0 to high impedant input mode of potentiometer 
**              POT1.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UI_Pot1_Init(void)
{ 
  R_PORT_SetGpioOutput(Port0, 1, High);
  R_PORT_SetGpioHighZ(APort0, 0);
}

/*****************************************************************************
** Function:    R_UI_Pot1_Read
** Description: Returns the value of AP0_0, which is connected to 
**              potentiometer POT1.
** Parameter:   None
** Return:      ADCA0 Port Read Result
******************************************************************************/
uint16_t R_UI_Pot1_Read(void)
{ 
  return R_ADCA0_PinRead(AP0_0);
}

/*****************************************************************************
** Function:    R_UI_ButtonS1_Init
** Description: Configures the port pin connected to switch S1 to input.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UI_ButtonS1_Init(void)
{
    R_PORT_SetGpioInput(Port0, 9);
}

/*****************************************************************************
** Function:    R_UI_ButtonS1_Deinit
** Description: Configures the port pin connected to button S1 to default.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UI_ButtonS1_Deinit(void)
{
    R_PORT_SetGpioHighZ(Port0, 9);
}

/*****************************************************************************
** Function:    R_UI_Get_ButtonS1_State
** Description: Returns whether button S1 is pressed or not.
** Parameter:   None
** Return:      R_BUTTON_PRESSED or
**              R_BUTTON_NOT_PRESSED
******************************************************************************/
r_Button_t R_UI_Get_ButtonS1_State(void)
{
    /*  Button S1 is pressed when level is low */
    if(!R_PORT_GetLevel(Port0, 9))
    {
        return R_BUTTON_PRESSED;
    }
    else
    {
        return R_BUTTON_NOT_PRESSED;
    }
}

/*****************************************************************************
** Function:    R_UI_ButtonS1_Handler
** Description: Function to check if the button S1 is pressed long or short. 
** Parameter:   None
** Return:      R_BUTTON_NOT_PRESSED or
**              R_BUTTON_PRESSED_SHORT or
**              R_BUTTON_PRESSED_LONG
******************************************************************************/
r_Button_t R_UI_ButtonS1_Handler(void)
{
    static uint32_t loc_ButtonS1Count = 0;
    
    /*  Button S1 is pressed when level is low */
    if(!R_PORT_GetLevel(Port0, 9))
    {
        loc_ButtonS1Count++;
        /* If button is pressed for 3s */
        if(loc_ButtonS1Count >= R_PRESS_LONG)
        {
            return R_BUTTON_PRESSED_LONG;
        }
    }
    /* If button is not pressed, check if button was pressed at least 10ms (R_PRESS_SHORT) */
    else
    {
        if((loc_ButtonS1Count >= R_PRESS_SHORT) && (loc_ButtonS1Count < R_PRESS_LONG))
        {
            loc_ButtonS1Count = 0;
            return R_BUTTON_PRESSED_SHORT;
        }
        else
        {
            loc_ButtonS1Count = 0;
        }
    }
    return R_BUTTON_NOT_PRESSED;
}

/*****************************************************************************
** Function:    R_UI_ButtonEnc1_Init
** Description: Configures the port pin connected to the button of the rotary  
**              switch ENC1 to input.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UI_ButtonEnc1_Init(void)
{
    R_PORT_SetGpioInput(Port1, 4);
}

/*****************************************************************************
** Function:    R_UI_ButtonEnc_Deinit
** Description: Configures the port pin connected to the button of the rotary  
**              switch ENC1 to default.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UI_ButtonEnc_Deinit(void)
{
    R_PORT_SetGpioHighZ(Port1, 4);
}

/*****************************************************************************
** Function:    R_UI_Get_ButtonEnc1_State
** Description: Returns whether button of ENC1 is pressed or not.
** Parameter:   None
** Return:      R_BUTTON_PRESSED or
**              R_BUTTON_NOT_PRESSED
******************************************************************************/
r_Button_t R_UI_Get_ButtonEnc1_State(void)
{
    /*  Encoder button is pressed when level is high */
    if(R_PORT_GetLevel(Port1, 4))
    {
        return R_BUTTON_PRESSED;
    }
    else
    {
        return R_BUTTON_NOT_PRESSED;
    }
}

/*****************************************************************************
** Function:    R_UI_ButtonEnc1_Handler
** Description: Function to check if the button of ENC1 is pressed long or short. 
** Parameter:   None
** Return:      R_BUTTON_NOT_PRESSED or
**              R_BUTTON_PRESSED_SHORT or
**              R_BUTTON_PRESSED_LONG
******************************************************************************/
r_Button_t R_UI_ButtonEnc1_Handler(void)
{
    static uint32_t loc_ButtonEnc1Count = 0;
    
    /*  Encoder button is pressed when level is high */
    if(R_PORT_GetLevel(Port1, 4))
    {
        loc_ButtonEnc1Count++;
        if(loc_ButtonEnc1Count >= R_PRESS_LONG)
        {
            return R_BUTTON_PRESSED_LONG;
        }
    }
    /* If button is not pressed, check if button was pressed at least 10ms (R_PRESS_SHORT) */
    else
    {
        if((loc_ButtonEnc1Count >= R_PRESS_SHORT) && (loc_ButtonEnc1Count < R_PRESS_LONG))
        {
            loc_ButtonEnc1Count = 0;
            return R_BUTTON_PRESSED_SHORT;
        }
        else
        {
            loc_ButtonEnc1Count = 0;
        }
    }
    return R_BUTTON_NOT_PRESSED;
}

/*****************************************************************************
** Function:    R_UI_INTP12_Init
** Description: Configures the port pin connected to button S1 for INTP12 usage
**              and the analog filter to falling edge detection. INTP12 is used
**              as wake-up signal in DeepSTOP.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UI_INTP12_Init(void)
{
    R_PORT_SetAnalogFilter(R_FCLA_INTP12, (R_FCLA_EDGE_DETECTION||R_FCLA_FALLING_EDGE));
    R_PORT_SetAltFunc(Port0, 9, Alt1, Input);
}

/*****************************************************************************
** Function:    R_UI_INTP15_Init
** Description: Configures the port pin connected to the button of ENC1 for INTP15 
**              usage and the analog filter to falling edge detection. INTP15 is 
**              used as wake-up signal in DeepSTOP.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UI_INTP15_Init(void)
{
    R_PORT_SetAnalogFilter(R_FCLA_INTP15, (R_FCLA_EDGE_DETECTION||R_FCLA_FALLING_EDGE));
    R_PORT_SetAltFunc(Port1, 4, Alt2, Input);
}

/*****************************************************************************
** Function:    R_UI_Enc1_Init
** Description: Initializes the encoder timer and the corresponding pins.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UI_Enc1_Init(void)
{
    R_PORT_SetAltFunc(Port10, 9, Alt3, Input);
    R_PORT_SetAltFunc(Port10, 10, Alt3, Input);
    R_ENCA0_Init();
    R_ENCA0_Start();
}

/*****************************************************************************
** Function:    R_UI_Enc1_Deinit
** Description: Stops the encoder timer and configure the used pins to default.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_UI_Enc1_Deinit(void)
{
    R_PORT_SetGpioHighZ(Port10, 9);
    R_PORT_SetGpioHighZ(Port10, 10);
    R_ENCA0_Stop();
}

