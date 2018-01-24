/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_display.c                                                     */
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
/* Source code for the Display Functions.                                    */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_display.h"
#include "font5x7.h"

/* Peripheral Includes */
#include "adc/r_adc.h"
#include "csi/r_csi.h"
#include "port/r_port.h"
/*===========================================================================*/
/* Functions */
/*===========================================================================*/
void writeCommand(uint8_t Command);
void writeData(uint16_t Data);
void writeBuffer(uint16_t* Buffer, uint16_t Length);
void delay(uint16_t count);
void drawChar(uint8_t x, uint8_t  y, char_t c, uint16_t  color, uint16_t  bg, uint8_t  size);
void goTo(uint8_t x, uint8_t y);
void drawPixel(uint8_t x, uint8_t y, uint16_t color);

/*****************************************************************************
** Function:    R_DISPLAY_SDCard_Test
** Description: Checks whether a SD Card is inserted in the dispay module.
** Parameter:   None
** Return:      None
******************************************************************************/
r_Error_t R_DISPLAY_SDCard_Test(void)
{
    if(R_PORT_GetLevel(Port11,5)==0)
    {
        return R_OK;
    }
    else
    {
        return R_ERROR;
    }
}
    
/*****************************************************************************
** Function:    R_DISPLAY_Deinit
** Description: Configures used pins back to default.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_DISPLAY_Deinit(void)
{
    R_PORT_SetGpioHighZ(Port10, 12);
    R_PORT_SetGpioHighZ(Port11, 0);
    R_PORT_SetGpioHighZ(Port11, 2);
    R_PORT_SetGpioHighZ(Port11, 3);
    R_PORT_SetGpioHighZ(Port11, 4);
    R_PORT_SetGpioHighZ(Port11, 5);
    R_PORT_SetGpioHighZ(Port11, 15);
    R_PORT_SetGpioHighZ(Port12, 1);
}

/*****************************************************************************
** Function:    R_DISPLAY_ResetRelease
** Description: Set display reset pin to high->operation mode.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_DISPLAY_ResetRelease(void)
{
    R_PORT_SetGpioOutput(Port10, 12, High);
}

/*****************************************************************************
** Function:    R_DISPLAY_Init
** Description: Configures pins, SPI and the display if connected.
** Parameter:   None
** Return:      R_OK - Configuration complete
**              R_ERROR - No display connected.
******************************************************************************/
r_Error_t R_DISPLAY_Init(void)
{
    /* Check if display is available */
    R_ADCA0_ConnectPullDown(AP0_4);       /* Connect internal Pull Down */
    delay(100); 
    if(R_ADCA0_PinRead(AP0_4)<2600) /* If display is connected, 3.3V = ~2700 should be measured */
    {
        return R_ERROR;
    }
    R_ADCA0_DisconnectPullDown(AP0_4);      /* Disconnect internal Pull Down */
    
    /* Reset - Low: Reset, High: Operation */
    R_PORT_SetGpioOutput(Port10, 12, High);
    delay(500);       
    R_PORT_SetGpioOutput(Port10, 12, Low);
    delay(500);
    R_PORT_SetGpioOutput(Port10, 12, High);
    delay(500);
    
    /* Data/Command - Low: Data interpreted as Command, High: Data interpreted as Data  */ 
    R_PORT_SetGpioOutput(Port11, 0, Low);
               
    /* Card Detect - Low: SD Card inserted, High: No SD Card inserted */ 
    R_PORT_SetGpioInput(Port11, 5);
    
    /* CSIH2 Port Configuration */
    R_PORT_SetAltFunc(Port11, 2, Alt1, Output);        /* CSIH2O - MOSI */
    R_PORT_SetAltFunc(Port11, 3, Alt1, Output);        /* CSI2SC - CLK  */
    R_PORT_SetAltFunc(Port11, 15, Alt1, Output);       /* CSIH2CSS4 - Chip Select Signal 4 */
    
    R_PORT_SetAltFunc(Port11, 4, Alt1, Input);         /* CISH2I - MISO  */

    R_CSIH2_Init();
    R_CSIH2_C4_SetTxSize(8);
    
      /* Initialization Sequence */
    writeCommand(SSD1351_CMD_COMMANDLOCK);  /* set command lock */
    writeData(0x12u);  
    writeCommand(SSD1351_CMD_COMMANDLOCK);  /* set command lock */
    writeData(0xB1u);
   
    writeCommand(SSD1351_CMD_DISPLAYOFF);   /* 0xAE */
    writeCommand(SSD1351_CMD_CLOCKDIV);     /* 0xB3 */
    writeData(0xF1u);                       /* 7:4 = Oscillator Frequency, 3:0 = CLK Div Ratio (A[3:0]+1 = 1..16) */
      
    writeCommand(SSD1351_CMD_MUXRATIO);
    writeData(127u);
      
    writeCommand(SSD1351_CMD_SETREMAP);
    writeData(0x74u);
    
    writeCommand(SSD1351_CMD_SETCOLUMN);
    writeData(0x00u);
    writeData(0x7Fu);
    writeCommand(SSD1351_CMD_SETROW);
    writeData(0x00u);
    writeData(0x7Fu);
    
    writeCommand(SSD1351_CMD_STARTLINE);        /* 0xA1 */
    writeData(96u);
    
    writeCommand(SSD1351_CMD_DISPLAYOFFSET);    /* 0xA2 */
    writeData(0x00u);
    
    writeCommand(SSD1351_CMD_SETGPIO);
    writeData(0x00u);
      
    writeCommand(SSD1351_CMD_FUNCTIONSELECT);
    writeData(0x41u);                           /* internal (diode drop) */
    
    writeCommand(SSD1351_CMD_PRECHARGE);        /* 0xB1 */
    writeData(0x32u);
    
    writeCommand(SSD1351_CMD_VCOMH);            /* 0xBE */
    writeData(0x05u);
    
    writeCommand(SSD1351_CMD_NORMALDISPLAY);    /* 0xA6 */
    
    writeCommand(SSD1351_CMD_CONTRASTABC);
    writeData(0x8Au);
    writeData(0x41u);
    writeData(0x8Au);
    
    writeCommand(SSD1351_CMD_CONTRASTMASTER);
    writeData(0x07u);
    
    writeCommand(SSD1351_CMD_SETVSL );
    writeData(0xA0u);
    writeData(0xB5u);
    writeData(0x55u);
     
    writeCommand(SSD1351_CMD_PRECHARGE2);
    writeData(0x01u);
    
    R_DISPLAY_DrawRect(0,0,128,96,0);           /* Fill up */
      
    writeCommand(SSD1351_CMD_DISPLAYON);		/*--turn on oled panel */   
    delay(200); 
    
    return R_OK;
}

/*****************************************************************************
** Function:    R_DISPLAY_DrawImg
** Description: Draws rectangular image data on the display.
** Parameter:   x - Start coordinate x (pixels)
**              y - Start coordimate y (pixels)
**              width - Width of image (pixels)
**              height - Height of image (pixels)
**              *data - Pointer to image data
** Return:      None
******************************************************************************/
void R_DISPLAY_DrawImg(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t* data)
{
   uint32_t i;
   
  /* Bounds check */
  while(x >= SSD1351WIDTH)
  {
      x -= SSD1351WIDTH;
  }
  while(y >= SSD1351HEIGHT)
  {
      y -= SSD1351HEIGHT;
  }
  

  /* Y bounds check */
  if (y+height > SSD1351HEIGHT)
  {
    height = SSD1351HEIGHT - y - 1;
  }

  /* X bounds check */
  if (x+width > SSD1351WIDTH)
  {
    width = SSD1351WIDTH - x - 1;
  }
  
  R_CSIH2_C4_SetTxSize(8);
  
  /* Set X-Y-Coordinates */
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(x+width-1);
  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(y+height-1);
  /* fill! */
  writeCommand(SSD1351_CMD_WRITERAM);
  delay(20);
  
  R_CSIH2_C4_SetTxSize(16);
  for (i=0; i < height*width; i++) 
  {
    writeData(*data);
    data++;
  }
}

/*****************************************************************************
** Function:    R_DISPLAY_DrawRect
** Description: Draw a rectangle on the display.
** Parameter:   x - Start coordinate x (pixels)
**              y - Start coordimate y (pixels)
**              width - Width of image (pixels)
**              height - Height of image (pixels)
**              color - Color of rectangle
** Return:      None
******************************************************************************/
void R_DISPLAY_DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color)
{
  uint32_t i;
    
    /* Bounds check */
  while(x >= SSD1351WIDTH)
  {
      x -= SSD1351WIDTH;
  }
  while(y >= SSD1351HEIGHT)
  {
      y -= SSD1351HEIGHT;
  }
  

  /* Y bounds check */
  if (y+height > SSD1351HEIGHT)
  {
    height = SSD1351HEIGHT - y - 1;
  }

  /* X bounds check */
  if (x+width > SSD1351WIDTH)
  {
    width = SSD1351WIDTH - x - 1;
  }
  
  R_CSIH2_C4_SetTxSize(8);
  
  /* Set X-Y-Coordinates */
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(x+width-1);
  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(y+height-1);
  /* fill! */
  writeCommand(SSD1351_CMD_WRITERAM);
  delay(20);
  
  R_CSIH2_C4_SetTxSize(16);
  for (i=0; i < height*width; i++) 
  {
    writeData(color);
  }
}

/*****************************************************************************
** Function:    drawChar
** Description: Draw single character.
** Parameter:   x - Start coordinate x (pixels)
**              y - Start coordimate y (pixels)
**              c - character
**              color - Color of character
**              bg - nackground color
**              size - font size
** Return:      None
******************************************************************************/
void drawChar(uint8_t x, uint8_t  y, char_t c, uint16_t  color, uint16_t  bg, uint8_t  size)
{
  uint8_t line,i,j;
  for (i=0; i<6; i++ ) 
  {
    
    if (i == 5) 
    {
      line = 0x0;
    }
    else 
    {
      line = font[c*5+i];
    }
      
    for (j = 0; j<8; j++)
      {
        if (line & 0x1) 
        {
           if (size == 1) /* default size */
           drawPixel(x+i, y+j, color);
           
           else  /*big size*/ 
           {  
             R_DISPLAY_DrawRect(x+(i*size), y+(j*size), size, size, color);
           } 
       } 
       
       else if (bg != color) 
        {
         if (size == 1) /* default size */
         drawPixel(x+i, y+j, bg);
         
         else /* big size*/
         {  
           R_DISPLAY_DrawRect(x+i*size, y+j*size, size, size, bg);
         }
       }
        line >>= 1;
     }
  
  }

}

/*****************************************************************************
** Function:    goTo
** Description: Go to specified display coordinates.
** Parameter:   x - Start coordinate x (pixels)
**              y - Start coordimate y (pixels)
** Return:      None
******************************************************************************/
void goTo(uint8_t x, uint8_t y)
{
  if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT)) 
  return;
  
  R_CSIH2_C4_SetTxSize(8);
  /* set x and y coordinate */
  writeCommand(SSD1351_CMD_SETCOLUMN);
  writeData(x);
  writeData(SSD1351WIDTH-1);

  writeCommand(SSD1351_CMD_SETROW);
  writeData(y);
  writeData(SSD1351HEIGHT-1);

  writeCommand(SSD1351_CMD_WRITERAM);  
}

/*****************************************************************************
** Function:    drawPixel
** Description: Draw a rectangle on the display.
** Parameter:   x - Start coordinate x (pixels)
**              y - Start coordimate y (pixels)
**              color - Color of pixel
** Return:      None
******************************************************************************/
void drawPixel(uint8_t x, uint8_t y, uint16_t color)
{

  /* Bounds check */
  if ((x >= SSD1351WIDTH) || (y >= SSD1351HEIGHT)) 
  return;

  goTo(x, y);
  
  //writeData(color >> 8); 
  R_CSIH2_C4_SetTxSize(16);   
  writeData(color);
  
}

/*****************************************************************************
** Function:    drawText
** Description: Draw a rectangle on the display.
** Parameter:   x - Start coordinate x (pixels)
**              y - Start coordimate y (pixels)
**              *c - Pointer to text
**              color - Color of text
**              bg - Color of background
**              size - Font size 
** Return:      None
******************************************************************************/
void R_DISPLAY_DrawText(uint8_t x, uint8_t  y, char_t* c,  uint16_t color, uint16_t bg, uint8_t size) 
{
  uint8_t i=0;

  while(*c != 0)
    {  
      drawChar(x+(i*size*6),y,*c,color,bg,size);
      c++;
      i++;
    }
}

/*****************************************************************************
** Function:    writeCommand
** Description: Set D/C to command and transmit command. 
** Parameter:   Command - Display controller command. 
** Return:      None
******************************************************************************/
void writeCommand(uint8_t Command) 
{
   R_PORT_SetGpioOutput(Port11, 0, Low);       /* Set D/C to Command */  
   R_CSIH2_TransmitData(Command);
}

/*****************************************************************************
** Function:    writeData
** Description: Set D/C to data and transmit single data. 
** Parameter:   Data - 16bit data
** Return:      None
******************************************************************************/
void writeData(uint16_t Data) 
{
   R_PORT_SetGpioOutput(Port11, 0, High);      /* Set D/C to Data */
   R_CSIH2_TransmitData(Data);
}

/*****************************************************************************
** Function:    writeBuffer
** Description: Set D/C to data and transmit data buffer. 
** Parameter:   *Buffer - pointer to data
**              Length - length of data buffer
** Return:      None
******************************************************************************/
void writeBuffer(uint16_t* Buffer, uint16_t Length) 
{
   R_PORT_SetGpioOutput(Port11, 0, High);      /* Set D/C to Data */
   R_CSIH2_TransmitBuffer(Buffer, Length);
} 

/*****************************************************************************
** Function:    delay
** Description: Simple local delay function.
** Parameter:   count
** Return:      None
******************************************************************************/
void delay(uint16_t count)
{
  
  uint32_t i;
  
  for(i=0;i<8000*count;i++);

}
