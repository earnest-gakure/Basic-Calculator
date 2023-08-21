#include "TM4C123.h"                    // Device header
#include "lcd_display.h"
#include "delay.h"
#include "keypad.h"

/**@BRIEF Pin out put is 
 *D0-D7 = PB0 -> PB7
 RS = PA5
 RW = PA6
 EN = PA7

*/
void LCD_init (void)
{
	SYSCTL->RCGCGPIO |= 0x01 ;//Enable clock for PA
	SYSCTL->RCGCGPIO |= 0x02 ; //Enable clock for PB
	
	GPIOA->DIR |= 0xE0 ; //configure PA5-7 as OUTPUT
	GPIOA->DEN |= 0xE0 ; //digital enable PA5-7
	
	GPIOB->DIR |= 0xFF ; //configure PB1-7 as OUTPUT
	GPIOB->DEN |= 0xFF ; //digital enable PB1-7
	
	
}
void LCD_CMD (unsigned char command )
{
	
	GPIOA->DATA =0x00; //RS = 0
	GPIOB->DATA = command ;
	GPIOA->DATA |= 0x80;//EN = 1
	delay_U(0);
	GPIOA->DATA |= 0x00;
	
	
	if (command < 4)
		delay_milli(2);
	else
	delay_U(37); // delay_micro(40)

}
void LCD_DATA (unsigned char data )
{
  
	GPIOA->DATA = 0x20 ; //RS = 1
	GPIOB->DATA = data;
	GPIOA->DATA |= 0x80 ;  //EN = 1
	delay_U(0);
	GPIOA->DATA |= 0x00 ;
	delay_U(0);
	
}
void LCD_String (unsigned  char *str ,unsigned char len  )
{
	char  i ;
 for(i=0;i<len;i++)
	{
		LCD_DATA(str[i]);
		str++;
	}
	
	
}
void LCD_Screen_control (void )
{

  LCD_CMD(0x38); // 8 bit data 
  LCD_CMD(0x06);//shift cursor right
  LCD_CMD(0x0F); //turn on display
  LCD_CMD(0x01); // clear screen	
	
}

