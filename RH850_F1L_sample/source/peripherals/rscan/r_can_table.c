/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_can_table.c                                                   */
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
/* CAN Rx rule table                                                         */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_can_table.h"

/*===========================================================================*/
/* Rx Rule Table */
/*===========================================================================*/

const can_cre_type RX_RULE_TABLE_LIST[RX_RULE_NUM] = {
/* CAN 3 reception rules */
    {{0x00000010UL, 0xDFFFFFF0UL, 0x00008000UL, 0x00000000UL}}, /* NO.000 : std data frm ID = H'10~1F will be accepted, destination Rx Buffer0 */
    {{0x00000020UL, 0xDFFFFFF0UL, 0x00008100UL, 0x00000000UL}}, /* NO.001 : std data frm ID = H'20~2F will be accepted, destination Rx Buffer1 */
    {{0x00000030UL, 0xDFFFFFF0UL, 0x00008200UL, 0x00000000UL}}, /* NO.002 : std data frm ID = H'30~3F will be accepted, destination Rx Buffer2 */
    {{0x00000040UL, 0xDFFFFFF0UL, 0x00008300UL, 0x00000000UL}}, /* NO.003 : std data frm ID = H'40~4F will be accepted, destination Rx Buffer3 */
    {{0x00000050UL, 0xDFFFFFFFUL, 0x00008400UL, 0x00000000UL}}, /* NO.004 : std data frm ID = H'50 will be accepted, destination Rx Buffer4 */
    {{0x00000060UL, 0xDFFFFFFFUL, 0x00008500UL, 0x00000000UL}}, /* NO.005 : std data frm ID = H'60 will be accepted, destination Rx Buffer5 */

/* CAN 4 reception rules */
    {{0x00000010UL, 0xDFFFFFF0UL, 0x00008600UL, 0x00000000UL}}, /* NO.000 : std data frm ID = H'10~1F will be accepted, destination Rx Buffer6 */
    {{0x00000020UL, 0xDFFFFFF0UL, 0x00008700UL, 0x00000000UL}}, /* NO.001 : std data frm ID = H'20~2F will be accepted, destination Rx Buffer7 */
    {{0x00000030UL, 0xDFFFFFF0UL, 0x00008800UL, 0x00000000UL}}, /* NO.002 : std data frm ID = H'30~3F will be accepted, destination Rx Buffer8 */
    {{0x00000040UL, 0xDFFFFFF0UL, 0x00008900UL, 0x00000000UL}}, /* NO.003 : std data frm ID = H'40~4F will be accepted, destination Rx Buffer9 */
    {{0x00000050UL, 0xDFFFFFFFUL, 0x00008a00UL, 0x00000000UL}}, /* NO.004 : std data frm ID = H'50 will be accepted, destination Rx Buffer10 */
    {{0x00000060UL, 0xDFFFFFFFUL, 0x00008b00UL, 0x00000000UL}}, /* NO.005 : std data frm ID = H'60 will be accepted, destination Rx Buffer11 */
};
