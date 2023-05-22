/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    SSD                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "SSD_interface.h"

u8 SSD_ARR[10]={0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110, 0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

void SSD_u8SetNumber(u8 Copy_Number, SSD_t* SSD)
{
	if(0<=Copy_Number && Copy_Number<=9)
	{
		if(SSD->SSD_CommType==SSD_u8COMM_CATHODE)
		{
			DIO_u8SetPortValue(SSD->SSD_Port, SSD_ARR[Copy_Number]);
			_delay_ms(500);
		}
		else if(SSD->SSD_CommType==SSD_u8COMM_ANODE)
		{
			DIO_u8SetPortValue(SSD->SSD_Port, ~(SSD_ARR[Copy_Number]));
			_delay_ms(500);
		}
	}

}

void SSD_voidEnable(SSD_t* SSD)
{
	DIO_u8SetPortDirection(SSD->SSD_Port,DIO_u8PORT_OUTPUT);

	DIO_u8SetPinDirection(SSD->SSD_ENPort,SSD->SSD_ENPin,DIO_u8PIN_OUTPUT);

	if(SSD->SSD_CommType == SSD_u8COMM_CATHODE)
	{
		DIO_u8SetPinValue(SSD->SSD_ENPort, SSD->SSD_ENPin, DIO_u8PIN_LOW);
	}
	else if(SSD->SSD_CommType == SSD_u8COMM_ANODE)
	{
		DIO_u8SetPinValue(SSD->SSD_ENPort, SSD->SSD_ENPin, DIO_u8PIN_HIGH);
	}
}

void SSD_voidDisable(SSD_t* SSD)
{
	if(SSD->SSD_CommType == SSD_u8COMM_CATHODE)
	{
		DIO_u8SetPinValue(SSD->SSD_ENPort, SSD->SSD_ENPin, DIO_u8PIN_HIGH);
	}
	else if(SSD->SSD_CommType == SSD_u8COMM_ANODE)
	{
		DIO_u8SetPinValue(SSD->SSD_ENPort, SSD->SSD_ENPin, DIO_u8PIN_LOW);
	}
}
