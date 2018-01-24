/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_display.h                                                     */
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
#ifndef R_DISPLAY_H
#define R_DISPLAY_H

/*===========================================================================*/
/* Defines */
/*===========================================================================*/
/* Display Resolution */
#define SSD1351HEIGHT 96
#define SSD1351WIDTH 128

/* Display Detection Macros */
#define R_NO_DISPLAY                    0x00
#define R_DISPLAY_OK                    0x01

/* SD Card Detection Macros */
#define R_NO_SDCARD                     0x00
#define R_SDCARD_DETECTED               0x01

// SSD1351 Commands
#define SSD1351_CMD_SETCOLUMN 		    0x15
#define SSD1351_CMD_SETROW    		    0x75
#define SSD1351_CMD_WRITERAM   		    0x5C
#define SSD1351_CMD_READRAM   		    0x5D
#define SSD1351_CMD_SETREMAP 		    0xA0
#define SSD1351_CMD_STARTLINE 		    0xA1
#define SSD1351_CMD_DISPLAYOFFSET 	    0xA2
#define SSD1351_CMD_DISPLAYALLOFF 	    0xA4
#define SSD1351_CMD_DISPLAYALLON  	    0xA5
#define SSD1351_CMD_NORMALDISPLAY 	    0xA6
#define SSD1351_CMD_INVERTDISPLAY 	    0xA7
#define SSD1351_CMD_FUNCTIONSELECT 	    0xAB
#define SSD1351_CMD_DISPLAYOFF 		    0xAE
#define SSD1351_CMD_DISPLAYON     	    0xAF
#define SSD1351_CMD_PRECHARGE 		    0xB1
#define SSD1351_CMD_DISPLAYENHANCE	    0xB2
#define SSD1351_CMD_CLOCKDIV 		    0xB3
#define SSD1351_CMD_SETVSL 		        0xB4
#define SSD1351_CMD_SETGPIO 		    0xB5
#define SSD1351_CMD_PRECHARGE2 		    0xB6
#define SSD1351_CMD_SETGRAY 		    0xB8
#define SSD1351_CMD_USELUT 		        0xB9
#define SSD1351_CMD_PRECHARGELEVEL 	    0xBB
#define SSD1351_CMD_VCOMH 		        0xBE
#define SSD1351_CMD_CONTRASTABC		    0xC1
#define SSD1351_CMD_CONTRASTMASTER	    0xC7
#define SSD1351_CMD_MUXRATIO            0xCA
#define SSD1351_CMD_COMMANDLOCK         0xFD
#define SSD1351_CMD_HORIZSCROLL         0x96
#define SSD1351_CMD_STOPSCROLL          0x9E
#define SSD1351_CMD_STARTSCROLL         0x9F

/*===========================================================================*/
/* Function defines */
/*===========================================================================*/
r_Error_t R_DISPLAY_SDCard_Test(void);
void R_DISPLAY_Deinit(void);
void R_DISPLAY_DrawImg(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t* data);
void R_DISPLAY_DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint16_t color);
r_Error_t R_DISPLAY_Init(void);
void R_DISPLAY_ResetRelease(void);
void R_DISPLAY_DrawText(uint8_t x, uint8_t  y, char_t* c,  uint16_t color, uint16_t bg, uint8_t size);

#endif /* R_DISPLAY_H */
