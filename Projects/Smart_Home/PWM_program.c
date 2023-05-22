/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    PWM                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "PWM_interface.h"
#include "PWM_private.h"
#include "PWM_config.h"


void PWM_voidProducePWM(u8 Copy_u8Channel, u16 Copy_u16Frequency)
{
	/*Set Channel*/
	if(Copy_u8Channel == CHANNEL_A)
	{
		CLR_BIT(TCCR1A, TCCR1A_COM1A0);
		SET_BIT(TCCR1A, TCCR1A_COM1A1);
	}
	else if(Copy_u8Channel == CHANNEL_B)
	{
		CLR_BIT(TCCR1A, TCCR1A_COM1B0);
		SET_BIT(TCCR1A, TCCR1A_COM1B1);
	}

	/*Set timer1 to FAST_PWM mode*/
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	SET_BIT(TCCR1A, TCCR1A_WGM11);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
	SET_BIT(TCCR1B, TCCR1B_WGM13);

	/*set the TOP value*/
	ICR1 = Copy_u16Frequency;

	/*set prescaler*/
	TCCR1B &= PRESCALER_MASK;
	TCCR1B |= DIVIDE_BY_8;
}

void PWM_voidSetDutyCycle(u8 Copy_u8DutyCycle, u16 Copy_u16Frequency)
{
	OCR1A = (((u32)Copy_u8DutyCycle * Copy_u16Frequency) / 100);
}

void PWM_voidSetDutyCycleRange0_180(u16 Copy_u8Angle, u16 Copy_u16Frequency)
{
	/*mapping OCR1A value from (0-100) to (0-180)*/
	u8 OCR1A_deg = ((((u32)Copy_u8Angle * 200) / 180) * Copy_u16Frequency);

	/*mapping from (0-180) to (750-2500)*/
	OCR1A = (((u32)OCR1A_deg * 10) + 750);
}

