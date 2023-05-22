#ifndef CLCD2_INTERFACE_H_
#define CLCD2_INTERFACE_H_


void LCD_voidLCDInit(void);

void LCD_voidSendCommand(u8 CMD);

void LCD_voidSendCharacter(u8 Character);

void LCD_voidSendString(const char* Arr);

u8 LCD_voidGoTORowCol(u8 Copy_u8Row, u8 Copy_u8Col);

void LCD_voidSendSpecialCharacter(u8 * Copy_pu8Pattern, u8 Copy_u8Location,u8 Copy_u8Row, u8 Copy_u8Col);

void LCD_voidSendVariable(u8 Copy_u8Variable);

void LCD_voidSendCommand_4_bit(u8 CMD);

void LCD_voidSendCharacter_4_bit(u8 Character);

//4 bit mode init
//4 bit mode send data
//4 bit send command



#endif


