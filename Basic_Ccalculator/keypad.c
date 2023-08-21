#include "TM4C123.h"                    // Device header
#include "keypad.h"
#include "delay.h"

#define K_ROW GPIOE
#define K_COLUMN GPIOC
/**@bdrief
  *ROW = PE0-PE4
  *COLUMN = PC4-PC7
  *ROWS ate set as output and initially set HIGH
  *COLUMNS are set as INPUT  and PULLUP is enabled

*/

void keypad_init (void)
{
	SYSCTL->RCGCGPIO |= 0x10 ;//enable clock for PE
	SYSCTL->RCGCGPIO |= 0x04 ;//enable clock for PC
	
	K_ROW->DIR |= 0x0F ; //pins are set to out put
	K_ROW->DEN |= 0x0F ; //digital enable pins 
	K_ROW->ODR |= 0x0F ; //set pins HIGH
	
	K_COLUMN->DIR &= ~0xF0 ; //pins are set to INPUT
	K_COLUMN->DEN |= 0xF0 ; //digitaly enable pins
	K_COLUMN->PUR |= 0xF0 ; //enable pullup
}
unsigned char get_key(void)
{
	 const unsigned char keymap[4][4]={
		{'1','2','3','+'},
		{'4','5','6','-'},
		{'7','8','9','.'},
		{'*','0','=','/'}
		};
	 
		//this variables will be used to get the key pressed
		uint8_t k_row ,k_col ;
		//to access K+ROW DATA it is set low  
		K_ROW->DATA = 0x00 ;
		
		k_col = K_COLUMN->DATA & 0xF0 ;
		//if no key pressed return 0
		if(k_col == 0 )
			return 0;
		
 for(;;)
		  {
		k_row = 0 ;
    K_ROW->DATA = 0x0E ; // enable ROW 1 ob 1110
		delay_milli(100);
    k_col = K_COLUMN->DATA & 0xF0; //when no key is pressed k_col = 0 
    if (k_col != 0xF0)
        break;			
		
		k_row = 1 ;
    K_ROW->DATA = 0x0D ; // enable ROW 2 ob 1101
		delay_milli(100);
    k_col = K_COLUMN->DATA & 0xF0; //when no key is pressed k_col = 0 
    if (k_col != 0xF0)
        break;	
		
		k_row = 2 ;
    K_ROW->DATA = 0x0B ; // enable ROW 3 ob 1011
		delay_milli(100);
    k_col = K_COLUMN->DATA & 0xF0; //when no key is pressed k_col = 0 
    if (k_col != 0xF0)
        break;

    k_row = 3 ;
    K_ROW->DATA = 0x07 ; // enable ROW 4 ob 0111
		delay_milli(100);
    k_col = K_COLUMN->DATA & 0xF0; //when no key is pressed k_col = 0 
    if (k_col != 0xF0)
        break;
		
 return 0 ;		
	  }	
	
if (k_col == 0xE0)
  return keymap[k_row][0]; //means a key in column o and row 'n' is pressed 
if (k_col == 0xD0)
  return keymap[k_row][1]; //means a key in column 1 and row 'n' is pressed 
if (k_col == 0xB0)
  return keymap[k_row][2]; //means a key in column 2 and row 'n'is pressed 
if (k_col == 0x70)
  return keymap[k_row][3]; //means a key in column 3 and row 'n' is pressed 
	

return 0 ;
}



