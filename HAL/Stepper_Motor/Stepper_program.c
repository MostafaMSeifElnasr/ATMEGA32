/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    Stepper             ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/
#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "Stepper_interface.h"
#include "Stepper_config.h"
#include "Stepper_private.h"


void Stepper_voidInit(void)
{
	/*set stepper pins to output*/
	DIO_u8SetPinDirection(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_OUTPUT);

	/*set stepper pins to output HIGH (stepper pins are activated by low signal)*/
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
}

void Stepper_voidRotateCWContinous(void)
{
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_LOW);
	_delay_ms(10);

	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_LOW);
	_delay_ms(10);

	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_LOW);
	_delay_ms(10);

	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_LOW);
	_delay_ms(10);
}

void Stepper_voidRotateCCWContinous(void)
{
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_LOW);
	_delay_ms(10);

	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_LOW);
	_delay_ms(10);

	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_LOW);
	_delay_ms(10);

	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_LOW);
	_delay_ms(10);
}

/*0.5 deg/step */
void Stepper_voidRotateCWAngle(f32 Copy_u8Angle)
{
	f32 Local_u16StepCounts = Copy_u8Angle / STEPPER_STEP ;
	u16 Local_u16Iterator = 0;

	while(Local_u16Iterator <= Local_u16StepCounts)
	{
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_LOW);
		_delay_ms(10);

		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_LOW);
		_delay_ms(10);

		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_LOW);
		_delay_ms(10);

		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_LOW);
		_delay_ms(10);

		Local_u16Iterator++;
	}
}

void Stepper_voidRotateCCWAngle(f32 Copy_u8Angle)
{
	f32 Local_u16Iterator = 0;

	while(Local_u16Iterator <= Copy_u8Angle)
	{
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_LOW);
		_delay_ms(10);
		Local_u16Iterator += STEPPER_STEP;

		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_LOW);
		_delay_ms(10);
		Local_u16Iterator += STEPPER_STEP;

		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_LOW);
		_delay_ms(10);
		Local_u16Iterator += STEPPER_STEP;

		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_LOW);
		_delay_ms(10);
		Local_u16Iterator += STEPPER_STEP;
	}
}

void Stepper_voidStop(void)
{
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_1, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_2, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_3, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(STEPPER_PORT, STEPPER_PIN_4, DIO_u8PIN_LOW);
}






