#ifndef SYSTEM_CLOCK
#define SYSTEM_CLOCK
#include "r_typedefs.h"
/*===========================================================================*/
/* Defines */
/*===========================================================================*/
#define R_CLKC_STOPMASK_SET         0x03
#define R_CLKC_STOPMASK_RESET       0x02

#define R_CLKC_TAUJ_DISABLE         0x00
#define R_CLKC_TAUJ_HSINTOSC        0x01
#define R_CLKC_TAUJ_MOSC            0x02
#define R_CLKC_TAUJ_LSINTOSC        0x03
#define R_CLKC_TAUJ_PPLLCLK2        0x04

#define R_CLKC_ADCA_DISABLE         0x00
#define R_CLKC_ADCA_HSINTOSC        0x01
#define R_CLKC_ADCA_MOSC            0x02
#define R_CLKC_ADCA_PPLLCLK2        0x03

#define R_CLKC_RSCAN_DISABLE        0x00
#define R_CLKC_RSCAN_MOSC           0x01
#define R_CLKC_RSCAN_PPLLCLK        0x03
#define R_CLKC_RSCAN_DIV_DISBABLE   0x00
#define R_CLKC_RSCAN_DIV_MOSC1      0x01
#define R_CLKC_RSCAN_DIV_MOSC2      0x02

/*===========================================================================*/
/* Function defines */
/*===========================================================================*/

void R_CLKC_PllInit(void);
void R_CLKC_SetRscanClockDomain(uint32_t RscanModuleClockDomain, uint32_t RscanComClockDomain);
void R_CLKC_SetAdca0ClockDomain(uint32_t Adca0ClockDomain);
void R_CLKC_SetTaujClockDomain(uint32_t TaujClockDomain);

#endif