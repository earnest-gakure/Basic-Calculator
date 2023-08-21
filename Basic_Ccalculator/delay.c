#include "TM4C123.h"                    // Device header
#include "delay.h"

void delay_U (int time )
{
	int i;
	
	SYSCTL->RCGCTIMER |= 0x01 ;//Enable clock for T0
	TIMER0->CTL &= ~0x01 ; //disable timer
	TIMER0->CFG |= 0x04 ;
	TIMER0->TAMR |= 0x02 ;
	TIMER0->TAILR |= 16 - 1;
	TIMER0->ICR |= 0x01 ;
	TIMER0->CTL |= 0x01;
	
	for(i=0;i<time;i++){
		while((TIMER0->RIS &0x01)==0){}
			TIMER0->ICR = 0x01 ;//clear prior timer flags
	}
	
}

void delay_milli(int time )
{
	int j ;
	SYSCTL->RCGCTIMER |= 0x02; //Enable clock for T1
	TIMER1->CTL &= ~0x01;
	TIMER1->CFG |= 0x04 ;
	TIMER1->TAMR |= 0x02;
	TIMER1->TAILR |= 16000 - 1 ;
	TIMER1->ICR |= 0x01;
	TIMER1->CTL |= 0x01;
	 
	for (j=0;j<time;j++)
	{
		while((TIMER1->RIS & 0x01 ) == 0);
			TIMER1->ICR = 0x01;
	}
}
