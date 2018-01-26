/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :Mon, Jan 25, 2018                                     */
/*  DESCRIPTION :This program is for testing basic fuctions of MC      */
/*  CPU TYPE    :TH850                                                 */
/*  Authors     :Charles, Nikhil                                       */
/*                                                                     */
/***********************************************************************/
#include "system.h"
#include "port.h"
#define WAIT_DELAY	110

void delay_us(int );
void delay_ms(int );
void main(void);


void main(void)
{
	R_SYSTEM_ClockInit();	
	
	while(1){
		delay_ms(500);
		 R_PORT_SetGpioOutput(Port1, 14, Low);
		 delay_ms(500);
		 R_PORT_SetGpioOutput(Port1, 14, High);
		//Port P1 = ~1;
	}
}

void delay_us(int x)  {
	int k = 0;
	do { 
		for (k = 0; k < WAIT_DELAY;k++);
	}while(x--);
}
void delay_ms(int x)  {
	int k =0;
	for (k = 0; k < x;k++){
		delay_us(1);
	}

}
