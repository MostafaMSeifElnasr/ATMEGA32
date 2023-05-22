/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    LED                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "LED_interface.h"
#include "LED_private.h"
#include "LED_config.h"

/**********************************************************/

void LED_Init(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	DIO_u8SetPinDirection(Copy_u8Port, Copy_u8Pin, DIO_u8PIN_OUTPUT);
}

void LED_ON(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	DIO_u8SetPinValue(Copy_u8Port, Copy_u8Pin, DIO_u8PIN_HIGH);
}

void LED_OFF(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	DIO_u8SetPinValue(Copy_u8Port, Copy_u8Pin, DIO_u8PIN_LOW);
}

void LED_Toggle(u8 Copy_u8Port, u8 Copy_u8Pin)
{
	DIO_u8ToggleBit(Copy_u8Port, Copy_u8Pin);
}

/***********************************************************/
