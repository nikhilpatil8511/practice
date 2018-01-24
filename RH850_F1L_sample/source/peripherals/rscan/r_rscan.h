/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_rscan.h                                                       */
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
#ifndef R_RSCAN_H
#define R_RSCAN_H

/*
*******************************************************************************
**  Register bit define
*******************************************************************************
*/

/* ---- CAN frame ----- */
typedef struct
{
    uint32_t ID :29;
    uint32_t THLEN :1;
    uint32_t RTR :1;
    uint32_t IDE :1;
    
    uint32_t TS :16;
    uint32_t LBL :12;
    uint32_t DLC :4;
    uint8_t DB[8];
} r_CANFrame_t;

/*---- structure for Tx Frame information --------------------*/
/* ---- CAN function return ---- */
typedef uint8_t r_CANRtn_t;

/* ---- function return value ---- */
#define CAN_RTN_OK                          0U
#define CAN_RTN_FIFO_FULL                   1U
#define CAN_RTN_BUFFER_EMPTY                2U
#define CAN_RTN_ERR                         255U


/*
*******************************************************************************
**  Macro define
*******************************************************************************
*/
#ifndef CAN_ENABLE
#define CAN_ENABLE                          1U
#endif
#ifndef CAN_DISABLE
#define CAN_DISABLE                         0U
#endif

/* ---- bit value ---- */
#define CAN_SET                             1U
#define CAN_CLR                             0U

/* ---- bit mask ---- */
#define CAN_1_BIT_MASK                      1U
#define CAN_2_BIT_MASK                      3U
#define CAN_3_BIT_MASK                      7U
#define CAN_4_BIT_MASK                      0xfU
#define CAN_5_BIT_MASK                      0x1fU

/* ---- bit position ---- */
#define CAN_B0_BIT_POS                      0U
#define CAN_B1_BIT_POS                      1U
#define CAN_B2_BIT_POS                      2U
#define CAN_B3_BIT_POS                      3U
#define CAN_B4_BIT_POS                      4U
#define CAN_B5_BIT_POS                      5U
#define CAN_B6_BIT_POS                      6U
#define CAN_B7_BIT_POS                      7U
#define CAN_B8_BIT_POS                      8U
#define CAN_B9_BIT_POS                      9U
#define CAN_B10_BIT_POS                     10U
#define CAN_B11_BIT_POS                     11U
#define CAN_B12_BIT_POS                     12U
#define CAN_B13_BIT_POS                     13U
#define CAN_B14_BIT_POS                     14U
#define CAN_B15_BIT_POS                     15U

/* **** CAN channel usage **** */
#define RS_CAN_CH3                 CAN_ENABLE  //CAN_DISABLE

#define RS_CAN_CH4                 CAN_ENABLE

/* ---- CAN resource ---- */
/*#define CAN_CHNL_NUM                        3U
#define CAN_RFIFO_NUM                       8U
#define CAN_CHNL_TRFIFO_NUM                 3U
#define CAN_TRFIFO_NUM                      (CAN_CHNL_TRFIFO_NUM * CAN_CHNL_NUM)
#define CAN_FIFO_NUM                        (CAN_RFIFO_NUM + CAN_TRFIFO_NUM)
#define CAN_CHNL_TX_BUF_NUM                 16U
*/
#define CAN_CRBRCF0_RX_BUF_NUM              32U
#define CAN_CRBRCF1_RX_BUF_NUM              32U
#define CAN_CRBRCF2_RX_BUF_NUM              32U
#define CAN_PAGE_RX_RULE_IDX_MASK           0xfU
#define CAN_RX_RULE_PAGE_IDX_BIT_POS        4U
#define CAN_RAM_LW_SIZE                     (0x1C20U >> 2U)
#define CAN_RAM_PAGE_IDX_BIT_POS            6U
#define CAN_RAM_DATA_IDX_MASK               0x3fU

#define RX_RULE_NUM_MAX              (192U)       /* Max Rx Rule number */
#define RX_RULE_PAGE_NUM             (1U)         /* Rx Rule Table page number */


/* ==== Rx rule table (Refer to can_table.h) ==== */
#define CAN_C0RN                       RX_RULE_NUM_CH0
#define CAN_C1RN                       RX_RULE_NUM_CH1
#define CAN_C2RN                       RX_RULE_NUM_CH2
#define CAN_C3RN                       RX_RULE_NUM_CH3
#define CAN_C4RN                       RX_RULE_NUM_CH4
#define CAN_RX_RULE_NUM                (CAN_C0RN + CAN_C1RN + CAN_C2RN + CAN_C3RN + CAN_C4RN)
#define CAN_RX_RULE_TABLE              RX_RULE_TABLE_LIST
#define CAN_RX_RULE_TYPE               can_cre_type

/* ---- TX buffer, TX status flag ---- */
#define CAN_TBTST_NOT_TRANSMITTING          0U
#define CAN_TBTST_TRANSMITTING              1U

/* ---- bit operations ---- */
#define GET_BIT(reg, pos)              (((reg) >> (pos)) & 1U)
#define SET_BIT(reg, pos)              ((reg) |= 1U << (pos))
#define CLR_BIT(reg, pos)              ((reg) &= ~(1UL << (pos)))

/* ---- CiTBCRj ---- */
#define CAN_TBTR_BIT_POS                    0U
#define CAN_TBAR_BIT_POS                    1U
#define CAN_TBOE_BIT_POS                    2U

/* transmission command */
#define CAN_TBCR_TRM                        (CAN_ENABLE << CAN_TBTR_BIT_POS)

/*
*******************************************************************************
**  Function define
******************************************************************************/
void R_RSCAN0_Init(void);

r_CANRtn_t R_RSCAN0_C3TrmByTxBuf(uint8_t TxBufIdx, const r_CANFrame_t* pFrame);
r_CANRtn_t R_RSCAN0_C4TrmByTxBuf(uint8_t TxBufIdx, const r_CANFrame_t* pFrame);
r_CANRtn_t R_RSCAN0_ReadRxBuffer(r_CANFrame_t* pFrame);

extern const r_CANFrame_t CANTraStandData;
extern r_CANFrame_t CANRecData;
extern r_CANFrame_t CANTxData;

#endif /* R_RSCAN_H */

