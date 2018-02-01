/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :Mon, Jan 25, 2018                                     */
/*  DESCRIPTION :This program is for testing basic fuctions of MCU     */
/*  CPU TYPE    :TH850                                                 */
/*  Authors     :Charles, Nikhil                                       */
/*                                                                     */
/***********************************************************************/
#include "system.h"
#include "port.h"
#include "taud.h"
#include "r_intc.h"
#include "t_device_init.h"
#include "r_tau.h"


#define WAIT_DELAY	10

uint16_t dummy_Read = 0;


void delay_us(int );
void delay_ms(int );
void main(void);
void toggle_LED_timer(void);
void config_timer(void);
char test_string[] = "Test Project:\t Test UART communication \r ";

void main(void)
{
	R_SYSTEM_ClockInit();
	__EI();
	R_SYSTEM_TimerInit();
	R_SYSTEM_TimerStart();
	R_UART_Init();	
	R_INTC_SetTableBit((uint16_t*)R_ICTAUJ0I1);
	
	config_timer();
	while(1){
		R_UART_SendString(test_string);
		delay_ms(1000);
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
	do{ 
		for (k = 0; k < 1000;k++){
			delay_us(1);
		}
	}while(x--);

}

void config_timer(){
	//test
	TAUJ0_CK0_Prescaler(10);
	TAUJ0_Channel1_Init();
	R_INTC_SetTableBit((uint16_t*)R_ICTAUJ0I1);
	TAUJ0_AssignChannel1ISR(toggle_LED_timer);
	R_INTC_UnmaskInterrupt((uint16_t*)R_ICTAUJ0I1);
	TAUJ0_Channel_Start(TAUJ0C1);
}

void toggle_LED_timer(){
	volatile static unsigned int count = 0;
	volatile static uint8_t LED_state = 0;
	count++; 

	if (LED_state == 0){
		R_PORT_SetGpioOutput(Port8, 5, Low);
		LED_state = 1;
	}else{
		R_PORT_SetGpioOutput(Port8, 5, High);
		LED_state = 0;	
	}

}
