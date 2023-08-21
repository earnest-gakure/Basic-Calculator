#ifndef _LCD_DISPLAY_H
#define _LCD_DISPLAY_H

void LCD_init (void);
void LCD_CMD (unsigned char command);
void LCD_DATA (unsigned char data );
void LCD_String (unsigned char *str ,unsigned char len );
void LCD_Screen_control( void);
#endif

