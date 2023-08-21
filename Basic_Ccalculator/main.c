
#include "TM4C123.h"                    // Device header


/**@file Basic_Calculator
*@Editer :Earnest Gakure
*@Date :August 8 2023
*@brief This project is aimed to a basic calculator that uses a 
       4x4 keypad .The calculation is diplayed on a 16x2 LCD display.
			
			 LETS GET STARTED !!!


*/



#include "lcd_display.h"
#include "delay.h"
#include "keypad.h"
#include <stdint.h>
#include "math.h"
void error (void);
void calculate_operand (uint8_t arr[],uint32_t c );
void store (uint32_t number );
uint32_t charToint(uint8_t k);
void intTochar(uint32_t y);

uint8_t sign = 0 ;      //to store the input sign
uint32_t i = 0 ;       //index for the array of no[4]
uint8_t z = 1 ;        //to check that no signs can come after each other
uint8_t x = 0;        //to calculate the operands
uint8_t no[5];        //array to store the number of the operand 
uint8_t key ;         //to receive the returned character
uint32_t sum ;        //for the result
uint8_t op = 0 ;      //used in the operand calculation

int main()
{
	
	SYSCTL->RCGCGPIO |= 0x20;//Clock for PF
	GPIOF->DIR |= 0x0E;// P1,2,3 are OUTPUT
	GPIOF->DEN |= 0x0E; //digital enable 
	
  keypad_init();
	LCD_init();
	LCD_Screen_control();
	LCD_CMD(0x80); //line 1 beggining
	delay_milli(500);
	while(1)
	{
		do{                    //to be sure tha user realy entered a key
			key = get_key();
			delay_milli(200); //wait for the debounce
			
		   }while (key==0);
   


      switch(key){
				case '0':
					LCD_DATA(key);  //firstly show the number 
				//secondly ,store the number in an array to use it later in the calculation of the input operand
				  no[i] = key;
				//thirdly ,increase the index of the array and zeroing the z again to enable entering a sign or =
				i++;
				z = 0;
				GPIOF->DATA = 0x04 ;  //BLUE LED on to indicate an operand is input
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
				
				case '1':
					LCD_DATA(key);
				  no[i] = key ;
				  i++;
				  z = 0;
				 GPIOF->DATA = 0x04;
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
				
				
				case '2':
					LCD_DATA(key);
				  no[i] = key ;
				  i++;
				  z = 0;
				 GPIOF->DATA = 0x04;
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
				
				
				
				case '3':
					LCD_DATA(key);
				  no[i] = key ;
				  i++;
				  z = 0;
				 GPIOF->DATA = 0x04;
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
				
					case '4':
					LCD_DATA(key);
				  no[i] = key ;
				  i++;
				  z = 0;
				 GPIOF->DATA = 0x04;
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
					case '5':
					LCD_DATA(key);
				  no[i] = key ;
				  i++;
				  z = 0;
				 GPIOF->DATA = 0x04;
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
				
						case '6':
					LCD_DATA(key);
				  no[i] = key ;
				  i++;
				  z = 0;
				 GPIOF->DATA = 0x04;
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
				 
							case '7':
					LCD_DATA(key);
				  no[i] = key ;
				  i++;
				  z = 0;
				 GPIOF->DATA = 0x04;
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
				
							case '8':
					LCD_DATA(key);
				  no[i] = key ;
				  i++;
				  z = 0;
				 GPIOF->DATA = 0x04;
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
				
							case '9':
					LCD_DATA(key);
				  no[i] = key ;
				  i++;
				  z = 0;
				 GPIOF->DATA = 0x04;
				 delay_milli(500);
				 GPIOF->DATA = 0x00;
				break;
				
				
							
				
				case '+':
					//if z=1 that means that the previous pressed key was also a sign resulting in error
				if(z==0)
				{
					calculate_operand(no,i-1); //firstly calculate the operand  stored in n0[]
					store (op);
					LCD_DATA(key); //show the new sign
					z++; //to prevent two signs from coming after each other  
					i=0; //zeroing the index of the no[] again
					sign = key ;
					GPIOF->DATA = 0x04;
				  delay_milli(500);
					GPIOF->DATA = 0x00; //turn the blue led off when any sign is pressed
					//break;
					
				}
				else{
					error();
					
				}
				break;
				
				
				case '-':
					if(z==0){
						calculate_operand(no,i-1);
						store(op);
						LCD_DATA(key);
						z++;
						sign= key;
						GPIOF->DATA = 0x04;
				    delay_milli(500);
					  GPIOF->DATA = 0x00;
					
					}
					else{
				  error();
					    }
				break;
				
				case '*':
					if(z==0){
						calculate_operand(no,i-1);
						store(op);
						LCD_DATA(key);
						z++;
						sign= key;
						GPIOF->DATA = 0x04;
				    delay_milli(500);
					  GPIOF->DATA = 0x00;
					
					}
					else{
				  error();
					    }
				break;
				
				  
					case '/':
					if(z==0){
						calculate_operand(no,i-1);
						store(op);
						LCD_DATA(key);
						z++;
						sign= key;
						GPIOF->DATA = 0x04;
				    delay_milli(500);
					  GPIOF->DATA = 0x00;
					
					}
					else{
				  error();
					    }
				break;
				
						
				 case '=':
					if(z==0)
					{
						calculate_operand(no,i-1);
						switch(sign)
						{
							case '+':
							sum = sum + op ;
							LCD_DATA('=');
							intTochar(sum); 
						
							break;
							
							case '-':
							sum = sum - op ;
							LCD_DATA('=');
							intTochar(sum);
						
							break;
							
							case '*':
							sum = sum * op ;
							LCD_DATA('=');
							intTochar(sum);
						
							break;
							
							case '/':
							sum = sum / op ;
							LCD_DATA('=');
							intTochar(sum);
						
							break;
							
						}
						GPIOF->DATA = 0x08 ;   //turn on the green led when the result is calculated  well
						delay_milli(500);
						GPIOF->DATA = 0x00; //turn of green led
						delay_milli(500);
						sign = 0 ;
						i=0;
						z++;
						op=0;
						key=0;
						sum = 0;
						
					}
					else{
						error();
						op = 0;   //zeroing the operand variable again
						
					}
			
			}	 
	}
	
}
void error (void)
{
	LCD_CMD(0x01);   //clear the screen 
	LCD_CMD(0x80);   // line i beggining
	delay_milli(500);
	GPIOF->DATA = 0x02 ; //turn on R LED 
	delay_milli(500);
	GPIOF->DATA = 0x00; //LED off
	LCD_DATA('e');
	LCD_DATA('r');
	LCD_DATA('r');
	LCD_DATA('r');
	LCD_DATA('o');
	LCD_DATA('r');
	delay_milli(1000);
	LCD_CMD(0x01);//clear screen
	
	
}
//this function is used to calculate the operands 
void calculate_operand (uint8_t arr[],uint32_t c )
{
	int t = c;
	int r;
	int g;
	  
	 for (x=0;x<=t ; x++)
	{
		r=c;
		g=1;
		while (r>0)
		{
			g=g*10;
			if(r==0)
			break;
			r--;
		}
		op=op + charToint(arr[x])*g;
		if(c==0)
			break;
		c--;
	}
}
//this function to store the first operand then it zeros the op variable again in order to use the calcilate_oprerand again properly
void store (uint32_t number )
{
	sum = number ; //storing the operand in variable named sum 
	op = 0 ;
}

/* This function is used to convert the numbers of the array in which we store
the pressed keys from Character type to integer one in order to make the inner calculation right*/

uint32_t charToint(uint8_t k)
{
switch(k)
{
	case '0':
	   	return 0;
	case '1':
		  return 1;
	case '2':
		  return 2;
	case '3':
		  return 3;
					
  case '4':
		  return 4;
	case '5':
		  return 5;
	case '6':
		  return 6;
	
  case '7':
		  return 7;
	case '8':
		  return 8;
	case '9':
		  return 9;

}
return 0;
}



/* This function is used to convert the result from an integer type to character type in order to enable the printing
on the lcd using 'lcd_Data()'*/

void intTochar(uint32_t y)
{
	unsigned  int tenthousands;
	unsigned  int thousands;
	unsigned  int cents;
	unsigned  int tens;
	unsigned  int ones;
	
if(y<=9){
	switch(y)
	{
		case 0:
	        LCD_DATA('0');
		      break;
		case 1:
	        LCD_DATA('1');
		      break;
		case 2:
	        LCD_DATA('2');
		      break;
		case 3:
	        LCD_DATA('3');
		      break;
		case 4:
	        LCD_DATA('4');
		      break;
		case 5:
	        LCD_DATA('5');
		      break;
		case 6:
	        LCD_DATA('6');
		      break;
		case 7:
	        LCD_DATA('7');
		      break;
		case 8:
	        LCD_DATA('8');
		      break;
		case 9:
	        LCD_DATA('9');
		      break;
	
	}
}
if(y<100 && y>=10)
{
   tens=y/10;
	intTochar(tens);     // Recursive Function
	 ones=y-(tens*10);
	intTochar(ones);
}
if(y<1000 && y>=100)
{
 cents=y/100;
	intTochar(cents);
 tens=(y-(cents*100))/10;
	intTochar(tens);
 ones=y-(cents*100)-(tens*10);
	intTochar(ones);
}
if(y<10000 && y>=1000)
{
 thousands=y/1000;
	intTochar(thousands);
	cents=(y-(thousands*1000))/100;
	intTochar(cents);
 tens=(y-(thousands*1000)-(cents*100))/10;
	intTochar(tens);
 ones=y-(thousands*1000)-(cents*100)-(tens*10);
	intTochar(ones);
}
if(y<100000 && y>=10000)
{
  tenthousands=y/10000;
	intTochar(tenthousands);
	thousands=(y-(tenthousands*10000))/1000;
	intTochar(thousands);
	cents=(y-(tenthousands*10000)-(thousands*1000))/100;
	intTochar(cents);
 tens=(y-(tenthousands*10000)-(thousands*1000)-(cents*100))/10;
	intTochar(tens);
 ones=y-(tenthousands*10000)-(thousands*1000)-(cents*100)-(tens*10);
	intTochar(ones);
}
}

