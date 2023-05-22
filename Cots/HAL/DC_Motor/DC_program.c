#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "DC_interface.h"
#include "DC_config.h"
#include "DC_private.h"

void DC_MotorInit(void)
{
	DIO_u8SetPinDirection(PORT_1, PIN_1, DIO_u8PIN_OUTPUT);
	DIO_u8SetPinDirection(PORT_2, PIN_2, DIO_u8PIN_OUTPUT);
}

void DC_MotorCWContinous(void)
{
	DIO_u8SetPinValue(PORT_1, PIN_1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(PORT_2, PIN_2, DIO_u8PIN_LOW);
}

void DC_MotorCCWContinous(void)
{
	DIO_u8SetPinValue(PORT_1, PIN_1, DIO_u8PIN_LOW);
	DIO_u8SetPinValue(PORT_2, PIN_2, DIO_u8PIN_HIGH);
}

void DC_MotorStop(void)
{
	DIO_u8SetPinValue(PORT_1, PIN_1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(PORT_2, PIN_2, DIO_u8PIN_HIGH);
}
