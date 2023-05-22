#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "CLCD2_interface.h"
#include "CLCD2_config.h"
#include "CLCD2_private.h"

/*global Flag*/
static u8 Global_u8Flag_4_bit = 0;

void LCD_voidLCDInit(void)
{
#if LCD_MODE == _8_BIT
	{
		DIO_u8SetPortDirection(LCD_DATA_PORT, DIO_u8PORT_OUTPUT);  //DATA
		DIO_u8SetPinDirection(LCD_CONTROL_PORT, RS_PIN, DIO_u8PIN_OUTPUT); //RS
		DIO_u8SetPinDirection(LCD_CONTROL_PORT, RW_PIN, DIO_u8PIN_OUTPUT); //R/W
		DIO_u8SetPinDirection(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_OUTPUT); //EN

		_delay_us(30);

		LCD_voidSendCommand(0x38);  //function set

		_delay_us(100);

		LCD_voidSendCommand(0x0C);   //

		_delay_us(100);

		LCD_voidSendCommand(0x01);   //clear screen
		_delay_ms(2);
	}


#elif LCD_MODE == _4_BIT
	{
		DIO_u8SetPinDirection(LCD_DATA_PORT, DIO_u8PIN4, DIO_u8PIN_OUTPUT);  //DATA
		DIO_u8SetPinDirection(LCD_DATA_PORT, DIO_u8PIN5, DIO_u8PIN_OUTPUT);
		DIO_u8SetPinDirection(LCD_DATA_PORT, DIO_u8PIN6, DIO_u8PIN_OUTPUT);
		DIO_u8SetPinDirection(LCD_DATA_PORT, DIO_u8PIN7, DIO_u8PIN_OUTPUT);

		DIO_u8SetPinDirection(LCD_CONTROL_PORT, RS_PIN, DIO_u8PIN_OUTPUT); //RS
		DIO_u8SetPinDirection(LCD_CONTROL_PORT, RW_PIN, DIO_u8PIN_OUTPUT); //R/W
		DIO_u8SetPinDirection(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_OUTPUT); //EN

		_delay_ms(30);

		LCD_voidSendCommand(0x20);  //function sets
		LCD_voidSendCommand(0x20);
		LCD_voidSendCommand(0x80);

		_delay_us(100);

		/*screen ON*/
		LCD_voidSendCommand(0x00);
		LCD_voidSendCommand(0xC0);

		_delay_us(40);

		/*clear display*/
		LCD_voidSendCommand(0x00);
		LCD_voidSendCommand(0x10);

		_delay_ms(2);

		Global_u8Flag_4_bit = 1;
	}

#endif
}


void LCD_voidSendCommand(u8 CMD)
{
	DIO_u8SetPinValue(LCD_CONTROL_PORT, RS_PIN, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(LCD_CONTROL_PORT, RW_PIN, DIO_u8PIN_LOW);

#if LCD_MODE == _8_BIT
	{
		DIO_u8SetPortValue(LCD_DATA_PORT, CMD);

		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_HIGH);
		_delay_us(100);
		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_LOW);
	}
#elif LCD_MODE == _4_BIT
	{
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN4, GET_BIT(CMD,4));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN5, GET_BIT(CMD,5));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN6, GET_BIT(CMD,6));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN7, GET_BIT(CMD,7));

		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_HIGH);
		_delay_us(100);
		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_LOW);
	}
#endif

	if(Global_u8Flag_4_bit == 1)
	{
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN4, GET_BIT(CMD,0));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN5, GET_BIT(CMD,1));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN6, GET_BIT(CMD,2));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN7, GET_BIT(CMD,3));

		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_HIGH);
		_delay_us(100);
		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_LOW);
	}
}

void LCD_voidSendCharacter(u8 Character)
{
	DIO_u8SetPinValue(LCD_CONTROL_PORT, RS_PIN, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(LCD_CONTROL_PORT, RW_PIN, DIO_u8PIN_LOW);

#if(LCD_MODE == _8_BIT)
	{

		DIO_u8SetPortValue(LCD_DATA_PORT, Character);

		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_HIGH);
		_delay_us(100);
		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_LOW);
	}
#elif(LCD_MODE == _4_BIT)
	{
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN4, GET_BIT(Character,4));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN5, GET_BIT(Character,5));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN6, GET_BIT(Character,6));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN7, GET_BIT(Character,7));

		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_HIGH);
		_delay_us(100);
		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_LOW);

		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN4, GET_BIT(Character,0));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN5, GET_BIT(Character,1));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN6, GET_BIT(Character,2));
		DIO_u8SetPinValue(LCD_DATA_PORT, DIO_u8PIN7, GET_BIT(Character,3));

		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_HIGH);
		_delay_us(100);
		DIO_u8SetPinValue(LCD_CONTROL_PORT, EN_PIN, DIO_u8PIN_LOW);

		_delay_ms(2);
	}
#endif
}

void LCD_voidSendString(const char* Arr)
{
	u8 i = 0;
	while(Arr[i] != '\0')
	{
		LCD_voidSendCharacter(Arr[i]);
		i++;
	}
}

/*Row (0->1) , Col (0->15)*/
u8 LCD_voidGoTORowCol(u8 Copy_u8Row, u8 Copy_u8Col)
{
	u8 Local_u8ErrorState = 0;

	u8 Local_u8DDRAMAddress;

	if(((Copy_u8Row == 0) || (Copy_u8Row == 1)) && ((Copy_u8Col >= 0) && (Copy_u8Col < 16)))
	{
		if(Copy_u8Row == 0)
		{
			Local_u8DDRAMAddress = Copy_u8Col;
		}
		else if(Copy_u8Row == 1)
		{
			Local_u8DDRAMAddress = Copy_u8Col + 0x40;
		}
	}
	else
	{
		Local_u8ErrorState = 1;
	}

	/*modify the command to make bit 7 = 1*/
	Local_u8DDRAMAddress += 128;

	/*send command : Set DDRAM address*/
	LCD_voidSendCommand(Local_u8DDRAMAddress);

	return Local_u8ErrorState;
}

void LCD_voidSendSpecialCharacter(u8 * Copy_pu8Pattern, u8 Copy_u8Location,u8 Copy_u8Row, u8 Copy_u8Col)
{
	/*to calculate CGRAM location*/
	u8 Local_u8CGRAMAddress;
	u8 Local_u8PatternIterator;

	Local_u8CGRAMAddress = Copy_u8Location * 8;

	SET_BIT(Local_u8CGRAMAddress, 6);

	LCD_voidSendCommand(Local_u8CGRAMAddress);

	for(Local_u8PatternIterator = 0;Local_u8PatternIterator<=7;Local_u8PatternIterator++)
	{
		LCD_voidSendCharacter(Copy_pu8Pattern[Local_u8PatternIterator]);
	}

	LCD_voidGoTORowCol(Copy_u8Row, Copy_u8Col);

	LCD_voidSendCharacter(Copy_u8Location);
}

void LCD_voidSendVariable(u8 Copy_u8Variable)
{
	u8 Local_u8Remainder = 0;
	u8 Local_u8Arr[16];
	u8 Local_u8Iterator = 0, Local_u8Counter = 0;

	while(Copy_u8Variable > 0)
	{
		Local_u8Remainder = Copy_u8Variable % 10;
		Local_u8Arr[Local_u8Iterator] = Local_u8Remainder;
		Copy_u8Variable = Copy_u8Variable /10;
		Local_u8Counter ++ ;
		Local_u8Iterator++;
	}

	for(Local_u8Iterator = Local_u8Counter; Local_u8Iterator > 0; Local_u8Iterator--)
	{
		if(Local_u8Arr[Local_u8Iterator-1] == 0)
		{
			LCD_voidSendCharacter('0');
		}
		else if(Local_u8Arr[Local_u8Iterator-1] == 1)
		{
			LCD_voidSendCharacter('1');
		}
		else if(Local_u8Arr[Local_u8Iterator-1] == 2)
		{
			LCD_voidSendCharacter('2');
		}
		else if(Local_u8Arr[Local_u8Iterator-1] == 3)
		{
			LCD_voidSendCharacter('3');
		}
		else if(Local_u8Arr[Local_u8Iterator-1] == 4)
		{
			LCD_voidSendCharacter('4');
		}
		else if(Local_u8Arr[Local_u8Iterator-1] == 5)
		{
			LCD_voidSendCharacter('5');
		}
		else if(Local_u8Arr[Local_u8Iterator-1] == 6)
		{
			LCD_voidSendCharacter('6');
		}
		else if(Local_u8Arr[Local_u8Iterator-1] == 7)
		{
			LCD_voidSendCharacter('7');
		}
		else if(Local_u8Arr[Local_u8Iterator-1] == 8)
		{
			LCD_voidSendCharacter('8');
		}
		else if(Local_u8Arr[Local_u8Iterator-1] == 9)
		{
			LCD_voidSendCharacter('9');
		}
	}
}




