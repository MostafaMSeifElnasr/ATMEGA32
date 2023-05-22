/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    Switches            ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "Switches_interface.h"
#include "Switches_config.h"
#include "Switches_private.h"

void PB_voidInit(u8 Copy_u8PB_Port, u8 Copy_u8PB_Pin, u8 Copy_u8Connection)
{
	if(Copy_u8Connection == PB_PULLUP)
	{
		DIO_u8SetPinDirection(Copy_u8PB_Port, Copy_u8PB_Pin, DIO_u8PIN_INPUT);
		DIO_u8SetPinValue(Copy_u8PB_Port, Copy_u8PB_Pin, DIO_u8PIN_HIGH);
	}
	else if(Copy_u8Connection == PB_PULLDOWN)
	{
		DIO_u8SetPinDirection(Copy_u8PB_Port, Copy_u8PB_Pin, DIO_u8PIN_INPUT);
		DIO_u8SetPinValue(Copy_u8PB_Port, Copy_u8PB_Pin, DIO_u8PIN_LOW);
	}
}


u8 PB_u8GetState(u8 Copy_u8PB_Port, u8 Copy_u8PB_Pin, u8 Copy_u8Connection)
{
	u8 Local_u8Value = DIO_u8GetPinValue(Copy_u8PB_Port, Copy_u8PB_Pin);

	if(Copy_u8Connection == PB_PULLUP)
	{
		if(Local_u8Value == 0)
		{
			return PB_PU_PRESSED;
		}
		else if(Local_u8Value == 1)
		{
			return PB_PU_RELEASED;
		}
	}
	else if(Copy_u8Connection == PB_PULLDOWN)
	{
		if(Local_u8Value == 0)
		{
			return PB_PD_RELEASED;
		}
		else if(Local_u8Value == 1)
		{
			return PB_PD_PRESSED;
		}
	}
}





