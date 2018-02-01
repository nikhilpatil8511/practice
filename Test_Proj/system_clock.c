#include "system_clock.h"
#include "iodefine.h"
#include "t_device_init.h"
/*
void protected_write2(uint32_t preg,uint32_t  pstatus, uint32_t  reg,uint32_t value)  
{
	do{
	          (preg)=0xa5u;
	          (reg)=(value);
	          (reg)=~(value);
	          (reg)=(value);
          }while((pstatus)==1u);
}
*/
void R_CLKC_PllInit(void)
{ 
  /* Prepare 16MHz MainOsc */
    if((MOSCS&0x04u) != 0x4u)                       /* Check if MainOsc needs to be started */
  {
   MOSCC=0x06;                                      /* Set MainOSC gain for 16MHz */
   MOSCST=0x00008000;                               /* Set MainOSC stabilization time to ~4.1ms */

 protected_write(PROTCMD0,PROTS0,MOSCE,0x01u);    /* Trigger Enable (protected write) */
   while ((MOSCS&0x04u) != 0x04u);                  /* Wait for active MainOSC */// MOSCCLKACT bit is set to 1 after the mainOsc is stable (bit 3 hence 0x04)
  }

  if((PLLS&0x04u) != 0x04u)                         /* Check if PLL needs to be started */ // stable and active state of PLL is indicated by PLLCLKACT bit 2 
  {
    /* Prepare PLL*/
    PLLC=0x00000a27u;                               /* 16 MHz MainOSC -> 80MHz PLL */
	//           M1     P divider    reserved       Division 
	//	            selection			 Ratio
	//0b 0000    00        101          00          0100111

    protected_write(PROTCMD1,PROTS1,PLLE,0x01u);    /* Enable PLL */           
    while((PLLS&0x04u) != 0x04u){}                  /* Wait for active PLL */   
  }
  
  /* PLL0 -> CPU Clock */ // CPU clock source selected by this register 
  protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKS_CTL,0x03u);
  while(CKSC_CPUCLKS_ACT!=0x03u);
  // b0-b2     b1-b0
  // res.      Clock source 
  // 0	       0x11(3: CPLLCLK)
  
  /* CPU Clock divider = PLL0/1 */
  
  protected_write(PROTCMD1,PROTS1,CKSC_CPUCLKD_CTL,0x01u);
  while(CKSC_CPUCLKD_ACT!=0x01u);
   // b0-b3     b2-b0
  // res.      Clock divider 
  // 0	       0x001 (1: divide by 1/ pass with no change)

  /* Set Peripheral CLK2 to 40 MHZ (PPLL2) */
  protected_write(PROTCMD1,PROTS1,CKSC_IPERI2S_CTL,0x02u);
  // b0-b3     b2-b0
  // res.      Clock divider 
  // 0	       0x010 (PPLLCLK2)
  while(CKSC_IPERI2S_ACT!=0x02u);
}

void R_CLKC_SetRscanClockDomain(uint32_t RscanModuleClockDomain, uint32_t RscanComClockDomain)
{
  /* Select RS-CAN Module Clock */
  protected_write(PROTCMD1, PROTS1, CKSC_ICANS_CTL, RscanModuleClockDomain);
  while (CKSC_ICANS_ACT !=RscanModuleClockDomain);

  /* Select RS-CAN Communication Clock */
  protected_write(PROTCMD1, PROTS1, CKSC_ICANOSCD_CTL, RscanComClockDomain);
  while (CKSC_ICANOSCD_CTL != RscanComClockDomain);
}

/*****************************************************************************
** Function:    R_CLKC_SetAdca0ClockDomain
** Description: Select the ADCA0 Clock domain. 
** Parameter:   None
** Return:      None
******************************************************************************/
void R_CLKC_SetAdca0ClockDomain(uint32_t Adca0ClockDomain)
{
  protected_write(PROTCMD0, PROTS0, CKSC_AADCAS_CTL, Adca0ClockDomain);
  while(CKSC_AADCAS_ACT != Adca0ClockDomain);
}

/*****************************************************************************
** Function:    R_CLKC_SetTaujClockDomain // Timer Array unit
** Description: Select the TAUJ Clock domain.
** Parameter:   None
** Return:      None
******************************************************************************/
void R_CLKC_SetTaujClockDomain(uint32_t TaujClockDomain)
{
  protected_write(PROTCMD0, PROTS0, CKSC_ATAUJS_CTL, TaujClockDomain);
  while(CKSC_ATAUJS_CTL != TaujClockDomain);
}  
