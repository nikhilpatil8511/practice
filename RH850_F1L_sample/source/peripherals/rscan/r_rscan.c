/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_rscan.c                                                       */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2015 by Renesas Electronics Europe GmbH,                    */
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
/* Source code for the RS CAN Functions.                                     */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "r_rscan.h"
#include "r_can_table.h"

/*===========================================================================*/
/* Functions */
/*===========================================================================*/
static void R_RSCAN0_SetRxRule(void);

/*****************************************************************************
** Function:    R_RSCAN0_Init
** Description: Configures the CAN0 macro for channel 3 and channel 4 usage
** Parameter:   None
** Return:      None
******************************************************************************/
void R_RSCAN0_Init(void)
{  
  /* Wait while CAN RAM initialization is ongoing */
  while((RSCAN0GSTS & 0x00000008u)) {}

  /* Switch to global/channel reset mode */
  RSCAN0GCTR &= 0xfffffffbu;
  RSCAN0C3CTR &= 0xfffffffbu;
  RSCAN0C4CTR &= 0xfffffffbu;

  /* Configure clk_xincan as CAN-ClockSource */
  RSCAN0GCFG = 0x00000010u;
    
  /* When fCAN is 16MHz, 
  Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2) = 16/2/16 = 0.5Mbps(500Kbps) */

  RSCAN0C3CFG = 0x023a0001u;    /* SJW =3TQ, TSEG1=10TQ, TSEG2=4TQ, BRP=1 */

  RSCAN0C4CFG = 0x023a0001u;    /* SJW =3TQ, TSEG1=10TQ, TSEG2=4TQ, BRP=1 */

  /* ==== Rx rule setting ==== */
  R_RSCAN0_SetRxRule();

  /* ==== Buffer setting ==== */    
  RSCAN0RMNB = 0x10u;  /*Can_SetGlobalBuffer */
    
  /* Set THLEIE disabled, MEIE(FIFO Message Lost Interrupt disabled) */
  RSCAN0GCTR &= 0xfffff8ffu;    

  /* If GlobalChannel in halt or reset mode */
  if (RSCAN0GSTS & 0x03u) 
  {
    RSCAN0GCTR &= 0xfffffffcu;     /* Switch to communication mode */
    while ((RSCAN0GSTS & 0x02u) == 2u)
	{
      /* While halt mode */
    }
    while ((RSCAN0GSTS & 0x01u) == 1u) 
	{
      /* While reset mode */
    }
  }

  /* If Channel3 in halt or reset mode */
  if (RSCAN0C3STS & 0x03u) 
  {
    RSCAN0C3CTR &= 0xfffffffcu;    /* Switch to communication mode */
    while ((RSCAN0C3STS & 0x02u) == 2u) 
	{
      /* While halt mode */
    }
    while ((RSCAN0C3STS & 0x01u) == 1u) 
	{
      /* While reset mode */
    }
  }
     
  /* If Channel4 in halt or reset mode */
  if (RSCAN0C4STS & 0x03u) 
  {
    RSCAN0C4CTR &= 0xfffffffcu;    /* Switch to communication mode */
    while ((RSCAN0C4STS & 0x02u) == 2u) 
	{
      /* While halt mode */
    }
    while ((RSCAN0C4STS & 0x01u) == 1u) 
	{
     /* While reset mode */
    }
  }   
}

/*****************************************************************************
** Function:    Can_SetRxRule
** Description: Set all Rx rules
** Parameter:   None
** Return:      None
******************************************************************************/
static void R_RSCAN0_SetRxRule(void)
{
  uint16_t RxRuleIdx;
  uint8_t PageRxRuleIdx;
  volatile CAN_RX_RULE_TYPE* pCRE;

  /* Set Rx rule number per channel */
  RSCAN0GAFLCFG0 |= 0x00000006u;    /* Channel3 rule number is 6 */

  RSCAN0GAFLCFG1 |= 0x06000000u;    /* Channel4 rule number is 6 */

  /* Get access base address of Rx rule */
  pCRE = (volatile CAN_RX_RULE_TYPE*)&(RSCAN0GAFLID0);

  /* Receive Rule Table Write Enable */
  RSCAN0GAFLECTR |= 0x00000100u;

  /* Copy Rx rule one by one */
  for (RxRuleIdx = 0U; RxRuleIdx < CAN_RX_RULE_NUM; RxRuleIdx++) 
  {
    PageRxRuleIdx = (uint8_t) (RxRuleIdx & CAN_PAGE_RX_RULE_IDX_MASK);

    /* Update target Rx rule page if necessary */
    if (PageRxRuleIdx == 0U) 
    {
      RSCAN0GAFLECTR |= RxRuleIdx >> CAN_RX_RULE_PAGE_IDX_BIT_POS;
    }

    /* Set a single Rx rule.*/
    pCRE[PageRxRuleIdx] = CAN_RX_RULE_TABLE[RxRuleIdx];
  }

  /* Rx rule write disable */
  RSCAN0GAFLECTR &= 0xfffffeffu;
}

/*****************************************************************************
** Function:    Can_ReadRx_buffer
** Description: This code shows how to read message from Rx buffer
** Parameter:   pRxBufIdx - Pointer to Rx buffer that receives frame
** Return:      CAN_RTN_OK           - A frame is successfully read out
**              CAN_RTN_BUFFER_EMPTY - No frame is read out   
******************************************************************************/
r_CANRtn_t R_RSCAN0_ReadRxBuffer(r_CANFrame_t* pFrame)
{
  uint8_t BufIdx;
  uint8_t CRBRCFiBufIdx;
  uint8_t OverwrittenFlag;
  uint32_t TempCRBRCF0;
  uint32_t TempCRBRCF1;
  uint32_t TempCRBRCF2;
  r_CANFrame_t* pRxBuffer;
  volatile uint32_t* pCRBRCF;
  r_CANRtn_t RtnValue;

  /* Judge if new messages are available */
  TempCRBRCF0 = RSCAN0RMND0;
  TempCRBRCF1 = RSCAN0RMND1;
  TempCRBRCF2 = RSCAN0RMND2;
  if ((TempCRBRCF0 == CAN_CLR) && (TempCRBRCF1 == CAN_CLR)&& (TempCRBRCF2 == CAN_CLR)) 
  {
    RtnValue = CAN_RTN_BUFFER_EMPTY;
  }
  else
  {
    /* Get Rx buffer that has new message */
    if (TempCRBRCF0 != CAN_CLR) 
    {
      pCRBRCF = (volatile uint32_t *)&(RSCAN0RMND0);
      for (BufIdx = 0U; BufIdx < CAN_CRBRCF0_RX_BUF_NUM; ++BufIdx) 
      {
        if ((TempCRBRCF0 & CAN_1_BIT_MASK) == CAN_SET) 
        {
          break;
        }
        TempCRBRCF0 = TempCRBRCF0 >> CAN_B1_BIT_POS;
      }
    }
    else if (TempCRBRCF1 != CAN_CLR)
    {
      pCRBRCF = (volatile uint32_t *)&(RSCAN0RMND1);
      for (BufIdx = 0U; BufIdx < CAN_CRBRCF1_RX_BUF_NUM; ++BufIdx) 
      {
        if ((TempCRBRCF1 & CAN_1_BIT_MASK) == CAN_SET) 
        {
          break;
        }
        TempCRBRCF1 = TempCRBRCF1 >> CAN_B1_BIT_POS;
      }
      BufIdx += CAN_CRBRCF0_RX_BUF_NUM;
    }
    else if (TempCRBRCF2 != CAN_CLR)
    {
      pCRBRCF = (volatile uint32_t *)&(RSCAN0RMND2);
      for (BufIdx = 0U; BufIdx < CAN_CRBRCF2_RX_BUF_NUM; ++BufIdx) 
	  {
        if ((TempCRBRCF2 & CAN_1_BIT_MASK) == CAN_SET) 
	    {
          break;
        }
        TempCRBRCF2 = TempCRBRCF2 >> CAN_B1_BIT_POS;
      }
      BufIdx += (CAN_CRBRCF0_RX_BUF_NUM+CAN_CRBRCF1_RX_BUF_NUM);
    }
    /* Calculate index value in CRBRCFi */
    CRBRCFiBufIdx = BufIdx & CAN_5_BIT_MASK;

    do 
    {
      /* Clear Rx complete flag of corresponding Rx buffer */
      do 
        {
          CLR_BIT(*pCRBRCF, CRBRCFiBufIdx);
        }while (GET_BIT(*pCRBRCF, CRBRCFiBufIdx) == CAN_SET);

        /* Read out message from Rx buffer */
        pRxBuffer = (r_CANFrame_t*) &(RSCAN0RMID0);
        *pFrame = pRxBuffer[BufIdx];

        /* Judge if current message is overwritten */
        OverwrittenFlag = GET_BIT(*pCRBRCF, CRBRCFiBufIdx);
        /* Message is overwritten */
        if (OverwrittenFlag == CAN_SET) 
        {
          /* User process for message overwritten */
        }
    }while (OverwrittenFlag == CAN_SET);

    RtnValue = CAN_RTN_OK;
  }
  return RtnValue;
}


r_CANRtn_t R_RSCAN0_C3TrmByTxBuf(uint8_t TxBufIdx, const r_CANFrame_t* pFrame)
{
  volatile uint8_t* pTBSR;
  r_CANFrame_t* pTxBuffer;
  volatile uint8_t* pTBCR;

  pTBSR = (volatile uint8_t *)&(RSCAN0TMSTS48);
  pTBCR = (volatile uint8_t *)&(RSCAN0TMC48);

  /* ---- Return if Tx Buffer is transmitting. ---- */    
  if( (pTBSR[TxBufIdx] & (uint8_t)0x01u) == CAN_TBTST_TRANSMITTING )
  {
    return CAN_RTN_ERR;
  }

  /* Clear Tx buffer status */
  do 
  {
    pTBSR[TxBufIdx] = CAN_CLR;
  }while (pTBSR[TxBufIdx] != CAN_CLR);

  /* Store message to Tx buffer */
  pTxBuffer = (r_CANFrame_t*) &(RSCAN0TMID48);
  pTxBuffer[TxBufIdx] = *pFrame;

  /* Set transmission request */
  pTBCR[TxBufIdx] = CAN_TBCR_TRM;

  return CAN_RTN_OK;
}


r_CANRtn_t R_RSCAN0_C4TrmByTxBuf(uint8_t TxBufIdx, const r_CANFrame_t* pFrame)
{
  volatile uint8_t* pTBSR;
  r_CANFrame_t* pTxBuffer;
  volatile uint8_t* pTBCR;

  pTBSR = (volatile uint8_t *)&(RSCAN0TMSTS64);
  pTBCR = (volatile uint8_t *)&(RSCAN0TMC64);

  /* ---- Return if Tx Buffer is transmitting. ---- */
  if( (pTBSR[TxBufIdx] & (uint8_t)0x01u) == CAN_TBTST_TRANSMITTING )
  {
    return CAN_RTN_ERR;
  }

  /* Clear Tx buffer status */
  do 
  {
    pTBSR[TxBufIdx] = CAN_CLR;
  }while (pTBSR[TxBufIdx] != CAN_CLR);

  /* Store message to Tx buffer */
  pTxBuffer = (r_CANFrame_t*) &(RSCAN0TMID64);
  pTxBuffer[TxBufIdx] = *pFrame;

  /* Set transmission request */
  pTBCR[TxBufIdx] = CAN_TBCR_TRM;

  return CAN_RTN_OK;
}
