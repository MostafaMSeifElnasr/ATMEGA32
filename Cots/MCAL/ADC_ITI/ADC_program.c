/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    ADC                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"
#include "GIE_interface.h"


/*global ptr to function to set end of conversion interrupt callback*/
void (*Global_ptrEndOfConversion)(void) = NULL;

/*global pointer to receive the reading*/
u16 * Global_u8Reading = NULL;

void ADC_voidInit(u8 Copy_u8Prescaler)
{
	/*set reference voltage to AVCC (5v)*/
	SET_BIT(ADMUX, ADMUX_REFS0);
	CLR_BIT(ADMUX, ADMUX_REFS1);

	/*left adjustment for result*/
	SET_BIT(ADMUX, ADMUX_ADLAR);

	/*ADC enable*/
	SET_BIT(ADCSRA, ADCSRA_ADEN);

	/*set Clock Prescaler*/
	ADCSRA &= PRESCALERMASK;
	ADCSRA |= Copy_u8Prescaler;
}


void ADC_voidStartConversionAsync(u16 * Copy_u8Reading, u8 Copy_u8Channel)
{
	/*ADC Conversion complete interrupt enable*/
	SET_BIT(ADCSRA, ADCSRA_ADIE);

	/*enable GIE*/
	GIE_voidEnable();

	/*setting the channel*/
	/*configurable by bit masking*/
	ADMUX &= ADMUX_MASK;
	ADMUX |= Copy_u8Channel;

	/*Assign global variable to get the reading from ISR by Setcallback*/
	Global_u8Reading = Copy_u8Reading;

	/*ADC Start conversion*/
	SET_BIT(ADCSRA, ADCSRA_ADSC);
}

u8 ADC_voidStartConversionSync(u8 Copy_u8Channel)
{
	u8 Reading;
	/*setting the channel*/
	/*configurable by bit masking*/
	ADMUX &= ADMUX_MASK;
	ADMUX |= Copy_u8Channel;

	/*ADC Start conversion*/
	SET_BIT(ADCSRA, ADCSRA_ADSC);

	/*polling till get the result*/
	while((GET_BIT(ADCSRA, ADCSRA_ADIF)) == 0);

	/*getting data from ADCH*/
	Reading = ADCH;

	/*clearing ADIF*/
	SET_BIT(ADCSRA, ADCSRA_ADIF);

	return Reading;
}

u8 ADC_voidSetCallBack(void(*Copy_PtrToFunc)(void))
{
	u8 Local_u8ErrorState = OK;
	if(Copy_PtrToFunc != NULL)
	{

		Global_ptrEndOfConversion = Copy_PtrToFunc;
	}
	else
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	return Local_u8ErrorState;
}

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
	if(Global_ptrEndOfConversion != NULL)
	{
#if (ADC_READING_MODE == EIGHT_bit_mode)
		{
		*Global_u8Reading = ADCH;
		}
#elif(ADC_READING_MODE == TEN_bit_mode)
		{
			*Global_u8Reading = ADCL;
		}
#endif
		Global_ptrEndOfConversion();
	}
}

