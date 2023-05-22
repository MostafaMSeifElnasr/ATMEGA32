/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    TIMER               ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Timer_interface.h"
#include "Timer_private.h"
#include "Timer_config.h"


void(*Global_pfCTCcallback)(void);

void Timer0_voidRunTimer0CTCAsync(void(*Copy_pfCompareMatchInterrupt)(void))
{
	/*set timer 0 mode to be CTC*/
	SET_BIT(TCCR0, TCCR0_WGM01);
	CLR_BIT(TCCR0, TCCR0_WGM00);

	/*Disconnect OC0 pin*/
	CLR_BIT(TCCR0, TCCR0_COM0);
	CLR_BIT(TCCR0, TCCR0_COM1);

	/*setting Compare match value*/
	OCR0 = 250;

	/*enable compare match interrupt*/
	SET_BIT(TIMSK, TIMSK_OCIE0);

	/*enable global interrupt*/
	SET_BIT(SREG ,SREG_I);

	/*passing ISR address to global ptr to function*/
	if(Copy_pfCompareMatchInterrupt != NULL)
	{
		Global_pfCTCcallback = Copy_pfCompareMatchInterrupt;
	}

	/*Set Prescaler*/
	TCCR0 &= PRESCALER_MASK;
	TCCR0 |= DIVIDE_BY_8;
}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if(Global_pfCTCcallback != NULL)
	{
		Global_pfCTCcallback();
	}
	else
	{
		/*do nothing*/
	}
}



