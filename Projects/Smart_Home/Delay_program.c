/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    Delay               ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"

#include "Delay_interface.h"
#include "Delay_private.h"
#include "Delay_config.h"

void (*GlobalCallBackFuncPtr)(void) = NULL;

void Delay_voidSync(u16 Copy_u16Time_ms)
{
	/*setting timer1 to CTC mode*/
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TCCR1A, TCCR1A_WGM11);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TCCR1B, TCCR1B_WGM13);

	/*setting timer1 to normal mode*/
	CLR_BIT(TCCR1A, TCCR1A_COM1A0);
	CLR_BIT(TCCR1A, TCCR1A_COM1A1);

	if((Copy_u16Time_ms > 0) && (Copy_u16Time_ms < 8300))
	{
		/*setting compare match value = delay_time * 1000 / 128 */
		OCR1A = ((u32)Copy_u16Time_ms * (125UL / 16UL));
	}

	/*setting prescaler*/
	TCCR1B &= PRESCALER_MASK;
	TCCR1B |= DIVIDE_BY_1024;

	/*wait till timer reaches OCR1A value*/
	while((GET_BIT(TIFR, TIFR_OCF1A)) == 0);

	/*Clear interrupt flag of OCR1A*/
	SET_BIT(TIFR, TIFR_OCF1A);
}

void Delay_voidAsync(u16 Copy_u16Time_ms, void (*CallBackFuncPtr)(void))
{
	/*setting timer1 to normal mode*/
	CLR_BIT(TCCR1A, TCCR1A_COM1A0);
	SET_BIT(TCCR1A, TCCR1A_COM1A1);

	/*setting timer1 to CTC mode*/
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TCCR1A, TCCR1A_WGM11);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TCCR1B, TCCR1B_WGM13);

	/*setting prescaler*/
	TCCR1B &= PRESCALER_MASK;
	TCCR1B |= DIVIDE_BY_1024;

	if((Copy_u16Time_ms > 0) && (Copy_u16Time_ms < 8300))
	{
		/*setting compare match value = delay_time * 1000 / 128 */
		OCR1A = (((u32)Copy_u16Time_ms * 125UL) / 16UL);
	}

	/*Enable GIE*/
	GIE_voidEnable();

	/*enable compare_matchA interrupt*/
	SET_BIT(TIMSK, TIMSK_OCIE1A);

	/*passing ISR ptr to func to global*/
	GlobalCallBackFuncPtr = CallBackFuncPtr;
}


/*OCR1A ISR*/
void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	if(GlobalCallBackFuncPtr != NULL)
	{
		GlobalCallBackFuncPtr();
	}
}











