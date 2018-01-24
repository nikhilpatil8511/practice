/*===========================================================================*/
/* Project:  F1x StarterKit Sample Software                                  */
/* Module :  r_tasks.c                                                       */
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
/* This file contains the basic tasks and mode handling.                     */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_tasks.h"
#include <stdio.h>

/* Include application */
#include "renesas128x96.h"

/* Include modules */
#include "can/r_can.h"
#include "display/r_display.h"
#include "led/r_led.h"
#include "lin/r_lin.h"
#include "system/r_system.h"
#include "uart/r_uart.h"
#include "user_input/r_ui.h"

/* Include Peripherals */
#include "enc/r_enc.h"
#include "intc/r_intc.h"
#include "stbc/r_stbc.h"
#include "tau/r_tau.h"
#include "adc/r_adc.h"
#include "pwmd/r_pwmd.h"
#include "rlin/r_rlin.h"


/*===========================================================================*/
/* Defines */
/*===========================================================================*/
/* Some defines for dynamic LED1,LED2 and ring LEDs behavior */
#define R_LED_WAVE_DOWN 0
#define R_LED_WAVE_UP	1
#define R_LED1_WAVE 	0
#define R_LED2_WAVE     1

/* DeepSTOP counter 30s */
#define DEEPSTOP_COUNT_DOWN        30000u

/* Time in ms status is updated and output */
#define STATUS_UPDATE_INTERVAL      100u
/*===========================================================================*/
/* Variables */
/*===========================================================================*/
/* Mode is stored in Retention RAM (so it is retained during DeepSTOP) */
#ifdef __GHS__
  #pragma ghs startdata 
  #pragma ghs section bss  = ".rdata"
  r_System_s g_SystemStatus;
  #pragma ghs section bss = default
  #pragma ghs enddata
#endif

#ifdef __IAR__
  #pragma location="RETENTION_RAM.noinit"
  __no_init __brel23 r_System_s g_SystemStatus;
#endif

#ifdef __CSP__
  #pragma section r0_disp32 "RETENTION_RAM"
  r_System_s g_SystemStatus;
  #pragma section default
#endif

/* Pattern to turn on all ring LEDs successively */
const uint16_t g_LEDRingPattern[16]={ 0x0001, 0x0003, 0x0007, 0x000F,
                                0x001F, 0x003F, 0x007F, 0x00FF,
                                0x80FF, 0xC0FF, 0xE0FF, 0xF0FF,
                                0xF8FF, 0xFCFF, 0xFEFF, 0xFFFF };

                                /* RED        YELLOW        GREEN      CYAN          BLUE       MAGENTA       WHITE       */ 
const uint16_t g_FixedRGBColors[7][3] = {{4095,0,0},{4095,4095,0},{0,4095,0},{0,4095,4095},{0,0,4095},{4095,0,4095},{4095,4095,4095}};


/* Potentiometer and Encoder status variables for global use */
uint32_t g_Pot1Value, g_Enc1Value, g_Enc1Compare;

/* Char array for status print */
char_t g_StatusText[100];



/*===========================================================================*/
/* Functions */
/*===========================================================================*/


/*****************************************************************************
** Function:    PrintText
** Description: Prints the text with printf in the Compiler IO and via UART.
** Parameter:   TextArray - Array containing Text to be sent. 
** Return:      None
******************************************************************************/
void PrintText(char_t* TextArray)
{
  R_UART_SendString(TextArray);
  
  #ifdef __GHS__ 
  printf((const char_t*)TextArray);
  #endif
}
/*****************************************************************************
** Function:    PwmErrorCallBack
** Description: Function called in case of ADC detected PWM upper/lowe limit
**              error.
** Parameter:   ADCA0ULER - Upper/lowe limit error information register
** Return:      None
******************************************************************************/
void PwmErrorCallBack(uint32_t ErrorStatus)
{
    /* Error on physical channel 1 - Red LED */
    if((ErrorStatus & 0x1F) == 0x01)
    {   
      if(g_SystemStatus.LEDR_Error == R_OK)
      {
        g_SystemStatus.LEDR_Error = R_ERROR_NOTIFY;
        R_LED_PwmStop(LEDR);
      }
    }
    /* Error on physical channel 2 - Blue LED */
    if((ErrorStatus & 0x1F) == 0x02)
    {
      if(g_SystemStatus.LEDB_Error == R_OK)
      {
        g_SystemStatus.LEDB_Error = R_ERROR_NOTIFY;
        R_LED_PwmStop(LEDB);
      }
    }
    /* Error on physical channel 3 - Green LED */
    if((ErrorStatus & 0x1F) == 0x03)
    {
      if(g_SystemStatus.LEDG_Error == R_OK)
      {
        g_SystemStatus.LEDG_Error = R_ERROR_NOTIFY;
        R_LED_PwmStop(LEDG);
      }
    }
}

void RgbLedDiagOutput(void)
{
  if(g_SystemStatus.LEDR_Error == R_ERROR_NOTIFY)
  {
    g_SystemStatus.LEDR_Error = R_ERROR;
    PrintText("\r>RGB LED error: red LED        \n\r");
  }
  if(g_SystemStatus.LEDG_Error == R_ERROR_NOTIFY)
  {
    g_SystemStatus.LEDG_Error = R_ERROR;
    PrintText("\r>RGB LED error: green LED      \n\r");
  }
  if(g_SystemStatus.LEDB_Error == R_ERROR_NOTIFY)
  {
    g_SystemStatus.LEDB_Error = R_ERROR;
    PrintText("\r>RGB LED error: blue LED       \n\r");
  }
}

/*****************************************************************************
** Function:    UpperByteMirror
** Description: Mirrors the upper byte of a 16bit value to match LED Ring arrangement. 
** Parameter:   CurrentValue - Value that shall be mirrored. 
** Return:      loc_MirroredValue
******************************************************************************/
uint16_t UpperByteMirror(uint16_t CurrentValue)
{
    uint16_t loc_MirroredValue, i;
    
    loc_MirroredValue = CurrentValue;
    loc_MirroredValue &= 0x00FF;
    
    CurrentValue >>= 8;
    for(i=0; i<8; i++)
    {
        if(CurrentValue & (1<<i))
        {
            loc_MirroredValue |= (0x8000>>i);
        }
    }
    
    return loc_MirroredValue;
}

/*****************************************************************************
** Function:    LedUpdate
** Description: Function that is called periodically in Mode 2 creating a 
**              dynamic LED behavior. 
** Parameter:   None
** Return:      None
******************************************************************************/
void LedUpdate(void)
{
    static uint32_t loc_LED1Duty = 0, 
                    loc_LED2Duty = 0,
                    loc_LEDWaveDirection = R_LED_WAVE_UP,
                    loc_LEDWave = R_LED1_WAVE,
                    loc_UpdateCounter = 0,
                    loc_LEDRingMask = 1,
                    loc_temp;
                    
    
    /* Update execution frequency depending on Pot1 position */
    R_TAUJ0_CDR_Update(TAUJ0C1, (6000-g_Pot1Value));

    
    if(loc_LEDWave == R_LED1_WAVE)
    {
        if(loc_LEDWaveDirection == R_LED_WAVE_UP)
        {
            loc_LED1Duty++;
            R_LED_SetPwmDuty(LED1, (loc_LED1Duty*41));
            if(loc_LED1Duty == 99)
            {
                loc_LEDWaveDirection = R_LED_WAVE_DOWN;
            }
        }
        else
        {
            loc_LED1Duty--;
            R_LED_SetPwmDuty(LED1, (loc_LED1Duty*41));
            if(loc_LED1Duty == 0)
            {
                loc_LEDWaveDirection = R_LED_WAVE_UP;
                loc_LEDWave = R_LED2_WAVE;
            }
        }
    }
    if(loc_LEDWave == R_LED2_WAVE)
    {
        if(loc_LEDWaveDirection == R_LED_WAVE_UP)
        {
            loc_LED2Duty++;
            R_LED_SetPwmDuty(LED2, (loc_LED2Duty*41));
            if(loc_LED2Duty == 99)
            {
                loc_LEDWaveDirection = R_LED_WAVE_DOWN;
            }
        }
        else
        {
            loc_LED2Duty--;
            R_LED_SetPwmDuty(LED2, (loc_LED2Duty*41));
            if(loc_LED2Duty == 0)
            {
                loc_LEDWaveDirection = R_LED_WAVE_UP;
                loc_LEDWave = R_LED1_WAVE;
            }
        }
    }

    /* Nummber of circulating ring LEDs is set bei Enc1 */
    if(g_Enc1Compare != g_Enc1Value)
    {
      g_SystemStatus.DeepSTOP_Counter = 0;
        if(R_ENCA0_GetFlags() & R_ENCA_DOWN_COUNT)
        {
            loc_temp = loc_LEDRingMask;
            loc_temp <<= 1;
            loc_LEDRingMask |= loc_temp;
            if(loc_LEDRingMask == 0)
            {
                loc_LEDRingMask = 1;
            }
        }
        else
        {
            if(loc_LEDRingMask >= 0xFFFFF)
            {
                loc_LEDRingMask = 0xFFFFE;
            }
            else
            {
                loc_temp = loc_LEDRingMask;
                loc_temp >>= 1;
                loc_temp |= 0x80000;
                loc_LEDRingMask &= loc_temp;
            }
        }
    }

    g_Enc1Compare = g_Enc1Value;
    
    /* Update ring LED output */
    if(!(loc_UpdateCounter%20))
    {
        /* This part mirrors the upper byte because of the LED Ring order */
        loc_temp = UpperByteMirror(loc_LEDRingMask);
        
        R_LED_RingUpdate(loc_temp);
        loc_LEDRingMask <<= 1;
    }
    if(loc_LEDRingMask & (1<<20))
    {
        loc_LEDRingMask |= 0x01;
    }
    loc_LEDRingMask &= 0xFFFFF;
    
    loc_UpdateCounter++;
}


/*****************************************************************************
** Function:    PrintStatus
** Description: Current status such as DeepSTOP timer and Pot1 position via UART.
** Parameter:   None
** Return:      None
******************************************************************************/
void PrintStatus(void)
{
    char_t *tmp = g_StatusText;
    uint32_t loc_percentPot;
    
    
    loc_percentPot = g_Pot1Value/40;
    
    if( loc_percentPot > 100)
    {
      loc_percentPot = 100;
    }
    
    sprintf(tmp, "\rPot1: %3i%%, DeepSTOP in %2is", loc_percentPot, (30-(g_SystemStatus.DeepSTOP_Counter/1000)));
    R_UART_SendString(tmp);
}

/*****************************************************************************
** Function:    SwitchRGBColor
** Description: Switches the color of the RGB to colors given in g_FixedRGBColors
** Parameter:   None
** Return:      None
******************************************************************************/
void SwitchRGBColor(void)
{
    if(g_SystemStatus.CurrentRGB == WHITE)
    {
        g_SystemStatus.CurrentRGB = RED;
    }
    else
    {
        g_SystemStatus.CurrentRGB++;
    }    
    R_LED_SetPwmDuty(LEDR, g_FixedRGBColors[g_SystemStatus.CurrentRGB][LEDR]);
    R_LED_SetPwmDuty(LEDG, g_FixedRGBColors[g_SystemStatus.CurrentRGB][LEDG]);
    R_LED_SetPwmDuty(LEDB, g_FixedRGBColors[g_SystemStatus.CurrentRGB][LEDB]);
}

/*****************************************************************************
** Function:    Mode1
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
void Mode1(void)
{
    r_Button_t loc_ButtonS1State, loc_ButtonEnc1State;
    static uint16_t loc_PatternNr = 0;
    uint16_t loc_tmpPot1;
    uint32_t loc_i;
    /* Reset the counter values */
    g_SystemStatus.System_Counter = 0u;                
    g_SystemStatus.DeepSTOP_Counter = 0u;
    
    /* Reset RGB Status */
    g_SystemStatus.LEDR_Error = R_OK;
    g_SystemStatus.LEDG_Error = R_OK;
    g_SystemStatus.LEDB_Error = R_OK;
	
    R_UI_ButtonS1_Init();
    R_UI_ButtonEnc1_Init();
    
    /* Init LEDs and PWM Diagnosis */
    R_LED_SetPwmDuty(LEDR, g_FixedRGBColors[g_SystemStatus.CurrentRGB][LEDR]);
    R_LED_SetPwmDuty(LEDG, g_FixedRGBColors[g_SystemStatus.CurrentRGB][LEDG]);
    R_LED_SetPwmDuty(LEDB, g_FixedRGBColors[g_SystemStatus.CurrentRGB][LEDB]);

    R_LED_PwmStart(LED1);
    R_LED_PwmStart(LED2);
    R_LED_PwmStart(LEDR);
    R_LED_PwmStart(LEDG);
    R_LED_PwmStart(LEDB);
    
    R_ADCA0_AssignLimitErrorCB(PwmErrorCallBack);
    R_INTC_SetTableBit((uint16_t*)R_ICADCA0ERR);
    R_INTC_UnmaskInterrupt((uint16_t*)R_ICADCA0ERR);
    R_ADCA0_SetUpperLowerLimit(0,1000,600);
    R_ADCA0_PwsaTriggerEnable();
    R_PWMD_DiagStart();
      
    R_LED_RingOutputEnable();
    
    /* Initial Encoder read */
    g_Enc1Value = R_ENCA0_Read();
    g_Enc1Compare = g_Enc1Value;
    
    if(loc_PatternNr > 15)
    {
        R_LED_RingUpdate(~g_LEDRingPattern[loc_PatternNr-16]);
    }
    else
    {
        R_LED_RingUpdate(g_LEDRingPattern[loc_PatternNr]);
    }
    
    R_SYSTEM_TimerStart();
    
    /* Enter Mode1 loop */
    while(g_SystemStatus.CurrentMode == R_MODE1)
    {
        /* Update LED1 and LED2 Duty Cycle depending on position of Potentiometer 1 */
        g_Pot1Value = R_ADCA0_PinRead(AP0_0);
        R_LED_SetPwmDuty(LED1, g_Pot1Value);
        if(g_Pot1Value <= 4050)
        {
            R_LED_SetPwmDuty(LED2, (4095-g_Pot1Value));
        }
        else
        {
            R_LED_SetPwmDuty(LED2, 0);
        }
        
        /* Follow encoder position with LED ring */
        if(g_Enc1Compare != g_Enc1Value)
        {
          g_SystemStatus.DeepSTOP_Counter = 0;
          if(R_ENCA0_GetFlags() & R_ENCA_DOWN_COUNT)
          {
              if(loc_PatternNr == 31)
              {
                  loc_PatternNr = 0;
              }
              else
              {
                  loc_PatternNr++;
              }
          }
          else
          {
              if(loc_PatternNr == 0)
              {
                  loc_PatternNr = 31;
              }
              else
              {
                  loc_PatternNr--;
              }
          }
          if(loc_PatternNr > 15)
          {
              R_LED_RingUpdate(~g_LEDRingPattern[loc_PatternNr-16]);
          }
          else
          {
              R_LED_RingUpdate(g_LEDRingPattern[loc_PatternNr]);
          }
        }
        g_Enc1Compare = g_Enc1Value;
    
        g_Enc1Value = R_ENCA0_Read();
    

        /* Print RGB LED diagnostic information */
        RgbLedDiagOutput();
               
        /* Print time to DeepSTOP and Pot1 position via UART */
        if(!(g_SystemStatus.System_Counter % STATUS_UPDATE_INTERVAL))
        {
            PrintStatus();
            
            /* If Pot1 was changed more than DEEPSTOP_POTI_SENSE (defined in r_system.h), reset DeepSTOP counter */
            if(g_Pot1Value > loc_tmpPot1)
            {
                if((g_Pot1Value - loc_tmpPot1)>DEEPSTOP_POTI_SENSE)
                {
                    g_SystemStatus.DeepSTOP_Counter = 0;
                }
            }
            else
            {
                if((loc_tmpPot1 - g_Pot1Value)>DEEPSTOP_POTI_SENSE)
                {
                    g_SystemStatus.DeepSTOP_Counter = 0;
                }
            }
            loc_tmpPot1 = g_Pot1Value;
        }
        
        /* Check buttons */
        loc_ButtonS1State = R_UI_ButtonS1_Handler();
        loc_ButtonEnc1State = R_UI_ButtonEnc1_Handler();
        if(loc_ButtonS1State == R_BUTTON_PRESSED_SHORT)
        {
            PrintText("\r>>Button short pressed: switch to mode 2...         \n\r");
            g_SystemStatus.CurrentMode = R_MODE2;
            g_SystemStatus.PreviousMode = R_MODE1;
        }
        
        if(loc_ButtonEnc1State == R_BUTTON_PRESSED_SHORT)
        {
          
          g_SystemStatus.DeepSTOP_Counter = 0;
          SwitchRGBColor();
        }
        
        if(loc_ButtonS1State == R_BUTTON_PRESSED_LONG)
        {
          PrintText("\r>>Button long pressed: enter DeepSTOP...\n\r");
          g_SystemStatus.CurrentMode = R_DEEPSTOP;
          g_SystemStatus.PreviousMode = R_MODE1;
        }
        
		/* Enter DeepSTOP after 30s */
		if(g_SystemStatus.DeepSTOP_Counter >= DEEPSTOP_COUNT_DOWN)      
        {                                        
            PrintText("\r>>30s without action - enter DeepSTOP\n\r");
            while(R_RLIN30_GetStatus() == RLIN_BUSY){}
            g_SystemStatus.CurrentMode = R_DEEPSTOP;
            g_SystemStatus.PreviousMode = R_MODE1;                                    
        }
    
        /* Wait for 1ms System Timer tick */
        R_SYSTEM_TimerTick();
    	/* Increment global counter */
        g_SystemStatus.System_Counter++;
        g_SystemStatus.DeepSTOP_Counter++;
    } 
    
    /* Leave Mode1 */
       
    R_LED_PwmStop(LED1);
    R_LED_PwmStop(LED2);
    R_LED_PwmStop(LEDR);
    R_LED_PwmStop(LEDG);
    R_LED_PwmStop(LEDB);
    R_LED_RingOutputDisable();
    
        /* wait for PWM channels to stop */
    for(loc_i=0; loc_i<5; loc_i++)
    {
      R_SYSTEM_TimerTick();
    }
    R_SYSTEM_TimerStop();
}

/*****************************************************************************
** Function:    Mode2
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
void Mode2(void)
{
	
    r_Button_t loc_ButtonS1State, loc_ButtonEnc1State;
    uint16_t loc_tmpPot1;
    uint32_t loc_i;
    /* Reset the counter values */
    g_SystemStatus.System_Counter = 0u;                
    g_SystemStatus.DeepSTOP_Counter = 0u;
    
    /* Reset RGB Status */
    g_SystemStatus.LEDR_Error = R_OK;
    g_SystemStatus.LEDG_Error = R_OK;
    g_SystemStatus.LEDB_Error = R_OK;
    
    R_UI_ButtonS1_Init();
    
    /* Init LEDs and PWM Diagnosis */
    R_LED_SetPwmDuty(LEDR, g_FixedRGBColors[g_SystemStatus.CurrentRGB][LEDR]);
    R_LED_SetPwmDuty(LEDG, g_FixedRGBColors[g_SystemStatus.CurrentRGB][LEDG]);
    R_LED_SetPwmDuty(LEDB, g_FixedRGBColors[g_SystemStatus.CurrentRGB][LEDB]);
    
    R_LED_PwmStart(LED1);
    R_LED_PwmStart(LED2);
    R_LED_PwmStart(LEDR);
    R_LED_PwmStart(LEDG);
    R_LED_PwmStart(LEDB);
    
    R_ADCA0_AssignLimitErrorCB(PwmErrorCallBack);
    R_INTC_SetTableBit((uint16_t*)R_ICADCA0ERR);
    R_INTC_UnmaskInterrupt((uint16_t*)R_ICADCA0ERR);
    R_ADCA0_SetUpperLowerLimit(0,1000,600);
    R_ADCA0_PwsaTriggerEnable();
    R_PWMD_DiagStart();
    
    R_LED_RingInit();    
    R_LED_RingOutputEnable();
    
    R_ENCA0_Start();
    g_Enc1Value = R_ENCA0_Read();
    g_Enc1Compare = g_Enc1Value;
    
    R_TAUJ0_AssignChannel1ISR(LedUpdate);
    R_INTC_UnmaskInterrupt((uint16_t*)R_ICTAUJ0I1);
    R_TAUJ0_Channel_Start(TAUJ0C1);
    
    R_SYSTEM_TimerStart();
    
    /* Enter Mode2 loop */
    while(g_SystemStatus.CurrentMode == R_MODE2)
    {
        g_Pot1Value = R_ADCA0_PinRead(AP0_0);
            
        g_Enc1Value = R_ENCA0_Read();
        
        /* Print time to DeepSTOP and Pot1 position via UART */
        if(!(g_SystemStatus.System_Counter % STATUS_UPDATE_INTERVAL))
        {
            PrintStatus();
            
            /* If Pot1 was changed more than DEEPSTOP_POTI_SENSE (defined in r_system.h), reset DeepSTOP counter */
            if(g_Pot1Value > loc_tmpPot1)
            {
                if((g_Pot1Value - loc_tmpPot1)>DEEPSTOP_POTI_SENSE)
                {
                    g_SystemStatus.DeepSTOP_Counter = 0;
                }
            }
            else
            {
                if((loc_tmpPot1 - g_Pot1Value)>DEEPSTOP_POTI_SENSE)
                {
                    g_SystemStatus.DeepSTOP_Counter = 0;
                }
            }
            loc_tmpPot1 = g_Pot1Value;
        }
        
        /* Print RGB LED diagnostic information */
        RgbLedDiagOutput();
        
        /* Check buttons */
        loc_ButtonS1State = R_UI_ButtonS1_Handler();
        loc_ButtonEnc1State = R_UI_ButtonEnc1_Handler();
        if(loc_ButtonS1State == R_BUTTON_PRESSED_SHORT)
        {
            PrintText("\r>>Button short pressed: switch to mode 1...\n\r");
            g_SystemStatus.CurrentMode = R_MODE1;
            g_SystemStatus.PreviousMode = R_MODE2;
        }
        
        if(loc_ButtonEnc1State == R_BUTTON_PRESSED_SHORT)
        {
          g_SystemStatus.DeepSTOP_Counter = 0;
          SwitchRGBColor();
        }
        
        if(loc_ButtonS1State == R_BUTTON_PRESSED_LONG)
        {
            PrintText("\r>>Button long pressed: enter DeepSTOP...\n\r");
            g_SystemStatus.CurrentMode = R_DEEPSTOP;
            g_SystemStatus.PreviousMode = R_MODE2;
        }
        /* Enter DeepSTOP after 30s */
	    if(g_SystemStatus.DeepSTOP_Counter >= DEEPSTOP_COUNT_DOWN)      
        {                                        
            PrintText("\r>>30s without action: enter DeepSTOP...\n\r");
            while(R_RLIN30_GetStatus() == RLIN_BUSY){}
            g_SystemStatus.CurrentMode = R_DEEPSTOP;
            g_SystemStatus.PreviousMode = R_MODE2;
        }
    
        /* Wait for 1ms System Timer tick */
        R_SYSTEM_TimerTick();
    	/* Increment global counter */
        g_SystemStatus.System_Counter++;
        g_SystemStatus.DeepSTOP_Counter++;
    }
	
    R_TAUJ0_Channel_Stop(TAUJ0C1);
    R_TAUJ0_AssignChannel1ISR(R_NULL);
    R_INTC_MaskInterrupt((uint16_t*)R_ICTAUJ0I1);
    
    R_LED_PwmStop(LED1);
    R_LED_PwmStop(LED2);
    R_LED_PwmStop(LEDR);
    R_LED_PwmStop(LEDG);
    R_LED_PwmStop(LEDB);
    R_LED_RingOutputDisable();
    
    /* wait for PWM channels to stop */
    for(loc_i=0; loc_i<5;loc_i++)
    {
      R_SYSTEM_TimerTick();
    }
    
}

/*****************************************************************************
** Function:    DeepSTOP
** Description: 
** Parameter:   None
** Return:      None
******************************************************************************/
void DeepSTOP(void)
{
   
    while(R_UI_Get_ButtonS1_State() == R_BUTTON_PRESSED);
    
    R_UI_INTP12_Init();
    R_UI_INTP15_Init();
    
    R_SYSTEM_PrepareDeepSTOP();
    R_STBC_EnterDeepSTOP();
}


/*****************************************************************************
** Function:    BoardCheck
** Description: This function checks the LED, CAN, and LIN functionality and 
**              prints the welcome screen and status via UART.
** Parameter:   None
** Return:      None
******************************************************************************/
void BoardCheck(void)
{
    uint32_t    i, 
                j = 0;
        
    R_CAN_Init();
    R_LIN_Init();
    R_UART_Init();
    
    /* Send Welcome Message via UART */
    PrintText("\r*****************************************\n\r");
    PrintText("*                RENESAS                *\n\r");
    PrintText("*      RH850/F1x Starter Kit Demo!      *\n\r");
    PrintText("*****************************************\n\r");
    PrintText("\n\rBegin with self test...\n\r");
    
    /* Check CAN-Function */
    if(R_CAN_Test() == R_OK)
    {
        PrintText("CAN test...Okay\n\r");
    }
    else
    { 
        PrintText("\n\rCAN-Error!\n\rPlease check if all jumpers of\n\rJ7 are closed and all switches of S4 are on.\n\n\r");
    } 
    
    /* Check LIN-Function */
    if(R_LIN_Test() == R_OK)
    {
        PrintText("LIN test...Okay\n\r");
    }
    else
    { 
        PrintText("LIN-Error!\n\rPlease check if all jumpers of\n\rJ17 are closed and switches 3-6 of S10 are off.\n\n\r");
    }


    
    R_CAN_Deinit();
    R_LIN_Deinit();
    
    /*Start RGB LED test sequence */
    PrintText("RGB LED test...");
    
    /* Start all LED functions */
    R_LED_SetPwmDuty(LED1, 4095);
    R_LED_SetPwmDuty(LED2, 4095);
    R_LED_SetPwmDuty(LEDR, 0);
    R_LED_SetPwmDuty(LEDG, 0);
    R_LED_SetPwmDuty(LEDB, 0);
    R_LED_PwmStart(LED1);
    R_LED_PwmStart(LED2);
    R_LED_PwmStart(LEDR);
    R_LED_PwmStart(LEDG);
    R_LED_PwmStart(LEDB);
    R_LED_RingOutputEnable();
    
    R_SYSTEM_TimerStart();
    
    /* Start ADC and PWM diagnosis and assign corresponding ADC call-back */
    g_SystemStatus.LEDR_Error = R_OK;
    g_SystemStatus.LEDG_Error = R_OK;
    g_SystemStatus.LEDB_Error = R_OK;
    R_ADCA0_AssignLimitErrorCB(PwmErrorCallBack);
    R_INTC_SetTableBit((uint16_t*)R_ICADCA0ERR);
    R_INTC_UnmaskInterrupt((uint16_t*)R_ICADCA0ERR);
    R_ADCA0_SetUpperLowerLimit(0,1000,600);
    R_ADCA0_PwsaTriggerEnable();
    R_PWMD_DiagStart();
    
    /* Generate RGB color flow and ring LEDs sequence */
    for(i=0; i<100; i++)
    {
        R_LED_SetPwmDuty(LEDR, (i*41));
        
        if(!(i%25))
        {
            R_LED_RingUpdate(g_LEDRingPattern[j++]);
        }
        R_SYSTEM_TimerTick();
        R_SYSTEM_TimerTick();
    }
    
    for(i=0; i<100; i++)
    {
        R_LED_SetPwmDuty(LEDG, (i*41));
        
        if(!(i%25))
        {
            R_LED_RingUpdate(g_LEDRingPattern[j++]);
        }
        R_SYSTEM_TimerTick();
        R_SYSTEM_TimerTick();
    }
    
    for(i=0; i<100; i++)
    {
        R_LED_SetPwmDuty(LEDR, (4059-(i*41)));
        
        if(!(i%25))
        {
            R_LED_RingUpdate(g_LEDRingPattern[j++]);
        }
        R_SYSTEM_TimerTick();
        R_SYSTEM_TimerTick();
    }
    
    for(i=1; i<100; i++)
    {
        R_LED_SetPwmDuty(LEDB, (i*41));
        
        if(!(i%25))
        {
            R_LED_RingUpdate(g_LEDRingPattern[j++]);
        }
        R_SYSTEM_TimerTick();
        R_SYSTEM_TimerTick();
    }
    
    j = 0;
    
    for(i=0; i<100; i++)
    {
        R_LED_SetPwmDuty(LEDG, (4059-(i*41)));
        
        if(!(i%25))
        {
            R_LED_RingUpdate(~g_LEDRingPattern[j++]);
        }
        R_SYSTEM_TimerTick();
        R_SYSTEM_TimerTick();
    }
    
    for(i=0; i<100; i++)
    {
        R_LED_SetPwmDuty(LEDR, (i*41));
        if(!(i%25))
        {
            R_LED_RingUpdate(~g_LEDRingPattern[j++]);
        }
        R_SYSTEM_TimerTick();
        R_SYSTEM_TimerTick();
    }
    
    for(i=0; i<100; i++)
    {
        R_LED_SetPwmDuty(LEDG, (i*41));
        
        if(!(i%25))
        {
            R_LED_RingUpdate(~g_LEDRingPattern[j++]);
        }
        R_SYSTEM_TimerTick();
        R_SYSTEM_TimerTick();
    }
    
    for(i=0; i<100; i++)
    {
        R_LED_SetPwmDuty(LEDR, (4059-(i*41)));
        R_LED_SetPwmDuty(LEDG, (4059-(i*41)));
        R_LED_SetPwmDuty(LEDB, (4059-(i*41)));
        if(!(i%25))
        {
            R_LED_RingUpdate(~g_LEDRingPattern[j++]);
        }
        R_SYSTEM_TimerTick();
        R_SYSTEM_TimerTick();
    }
    
    for(i=0; i<200; i++)
    {
        R_SYSTEM_TimerTick();
    }
    
    
    /* Turn RGB to white and all ring LEDs on */
    R_LED_SetPwmDuty(LEDR, 4095);
    R_LED_SetPwmDuty(LEDG, 4095);
    R_LED_SetPwmDuty(LEDB, 4095);
    R_LED_RingUpdate(0xFFFF);
    
    
            /* Check LED status and print message if error occured */
    if(g_SystemStatus.LEDR_Error == R_OK && g_SystemStatus.LEDG_Error == R_OK &&  g_SystemStatus.LEDB_Error == R_OK )
    {
        PrintText("Okay\n\r");
    }
      else
    {
        PrintText("failed\n\r");
    }
    
    /* Check LED status and print message if error occured */
    if(g_SystemStatus.LEDR_Error == R_ERROR)
    {
        PrintText("Red LED error detected.\n\r");
    }
    if(g_SystemStatus.LEDG_Error == R_ERROR)
    {
        PrintText("Green LED error detected.\n\r");
    }
    if(g_SystemStatus.LEDB_Error == R_ERROR)
    {
        PrintText("Blue LED error detected.\n\r");
    }
    

    
    
    /* Check if a display is connected. If so, image is output to it */
    if(R_DISPLAY_Init() == R_OK)
    {
        PrintText("Display detected.\n\r");
        R_DISPLAY_DrawImg(0,0,128,96,(uint16_t*)RenesasPicture);
        g_SystemStatus.DisplayDetected = 1;
    }
    else
    {
        
        PrintText("No display detected.\n\r");
        g_SystemStatus.DisplayDetected = 0;
    }
    
    /* Wait for 500ms */
    for(i=0; i<500; i++)
    {
        R_SYSTEM_TimerTick();
    }
    
    R_INTC_MaskInterrupt((uint16_t*)R_ICADCA0ERR);
    R_PWMD_DiagStop();
    
    /* Turn all LEDs off */
    R_LED_SetPwmDuty(LED1, 0);
    R_LED_SetPwmDuty(LED2, 0);
    R_LED_SetPwmDuty(LEDR, 0);
    R_LED_SetPwmDuty(LEDG, 0);
    R_LED_SetPwmDuty(LEDB, 0);
    R_LED_PwmStop(LED1);
    R_LED_PwmStop(LED2);
    R_LED_PwmStop(LEDR);
    R_LED_PwmStop(LEDG);
    R_LED_PwmStop(LEDB);
    R_LED_RingUpdate(0);
    
    
    for(i=0; i<200; i++)
    {
        R_SYSTEM_TimerTick();
    }
}

/*****************************************************************************
** Function:    R_TASKS_Start
** Description: Call peripheral initialization functions and handle executed 
**              modes.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_TASKS_Start(void)
{ 
    uint32_t loc_WakeUpFactor;
    
    R_SYSTEM_TimerInit();
    R_UART_Init();
    R_ADCA0_Init();
    R_PWMD_DiagInit();
    
    /* Set TAU prescalers to 2^4 = 16 */
    R_TAUB0_CK0_Prescaler(4);
    R_TAUJ0_CK0_Prescaler(4);
    
    R_TAUJ0_Channel1_Init();
    R_INTC_SetTableBit((uint16_t*)R_ICTAUJ0I1);
    
    R_LED_PwmInit(LED1);
    R_LED_PwmInit(LED2);
    R_LED_PwmInit(LEDR);
    R_LED_PwmInit(LEDG);
    R_LED_PwmInit(LEDB);
    R_LED_RingInit();  
    
    R_UI_Enc1_Init();
    R_UI_Pot1_Init();
    
    R_LED_RgbDiagInit();
    
    
    loc_WakeUpFactor = R_STBC_GetWakeUpFactor();
    /* No Wake-up -> Reset */
    if(loc_WakeUpFactor == R_WUF_RESET)
    {
        /* Test StarterKit Board functionalities */
        BoardCheck(); 
        
        /* Set initial values for System Status */
        g_SystemStatus.CurrentMode = R_MODE1;
        g_SystemStatus.PreviousMode = R_RESET;
        g_SystemStatus.CurrentRGB = WHITE;
        
        PrintText("\n\r>>Enter Mode 1\n\r");
    }
    /* Wake-up from DeepSTOP */
    else
    {
      if (R_WUF_INTP12&loc_WakeUpFactor)
      {
          PrintText("\n\r>>Wake-up from DeepSTOP by INTP Button!\n\r");
      }
      
      if (R_WUF_INTP15&loc_WakeUpFactor)
      {
          PrintText("\n\r>>Wake-up from DeepSTOP by Encoder Button!\n\r");
      }
      
      if (R_WUF_LPS_AI&loc_WakeUpFactor)
      {
          PrintText("\n\r>>Wake-up from DeepSTOP by LPS (analog input)!\n\r");
      }
      
      if (R_WUF_LPS_DI&loc_WakeUpFactor)
      {
          PrintText("\n\r>>Wake-up from DeepSTOP by LPS (digital input)!\n\r");
      }
      
      if (R_WUF_DCUTDI == loc_WakeUpFactor)
      {
          PrintText("\n\r>>Wake-up from DeepSTOP by debugger!\n\r");
      }
      

    
        
        
        switch(g_SystemStatus.PreviousMode)
        {
            case R_MODE1:
                PrintText("\n\r>>Enter previous mode 1\n\r");
            break;
            
            case R_MODE2:
                PrintText("\n\r>>Enter previous mode 2\n\r");
            break;
            
            default:
            break;
        }

        g_SystemStatus.CurrentMode = g_SystemStatus.PreviousMode;
        g_SystemStatus.PreviousMode = R_DEEPSTOP;
        
        /* If display was connected configure reset pin to reset release */
        if(g_SystemStatus.DisplayDetected)
        {
            R_DISPLAY_ResetRelease();
        }
        
        /* Release IO hold state of the Ports after DeepSTOP */
        R_STBC_ReleaseIoHold();
    }
    
    
    /* Mode handler loop */
    while(1)
    {
        switch(g_SystemStatus.CurrentMode)
        {
            case R_MODE1:
                Mode1();
            break;
            
            case R_MODE2:
                Mode2();
            break;
            
            case R_DEEPSTOP:
                DeepSTOP();
            break;
            
            default:
            break;
        }
    }
}

