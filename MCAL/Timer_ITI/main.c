#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "Timer_interface.h"

void Application(void);

void main(void)
{
	DIO_u8SetPinDirection(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_OUTPUT);

	Timer0_voidRunTimer0CTCAsync(Application);

	while(1)
	{

	}
}

void Application(void)
{
	static u16 counter = 0;
	counter++;
	if(counter == 5)
	{
		DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_LOW);

	}
	else if(counter == 20)
	{
		DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN0, DIO_u8PIN_HIGH);
		counter = 0;
	}
}
