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
#include "GIE_interface.h"



void(*Global_pfCTCcallback)(void) = NULL;

void(*ICU_pvCallBackFunc)(void) = NULL;

void Timer0_voidRunTimer0CTCAsync(void(*Copy_pfCompareMatchInterrupt)(void))
{
	/*set timer 0 mode to be CTC*/
	SET_BIT(TCCR0, TCCR0_WGM01);
	CLR_BIT(TCCR0, TCCR0_WGM00);

	/*Disconnect OC0 pin*/
	CLR_BIT(TCCR0, TCCR0_COM0);
	CLR_BIT(TCCR0, TCCR0_COM1);

	/*setting Compare match value*/
	OCR0 = 78;

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
	TCCR0 |= DIVIDE_BY_256;
}

/*non inverted PWM signal from timer0*/
void Timer0_voidRunPWMFastNonInverted(void)
{
	/*set timer 0 mode to be PWM*/
	SET_BIT(TCCR0, TCCR0_WGM01);
	SET_BIT(TCCR0, TCCR0_WGM00);

	/*OC0 pin mode : Noninverted*/
	CLR_BIT(TCCR0, TCCR0_COM0);
	SET_BIT(TCCR0, TCCR0_COM1);

	/*Set Prescaler*/
	TCCR0 &= PRESCALER_MASK;
	TCCR0 |= DIVIDE_BY_8;

}

/*set OCR0 value to adjust Duty Cycle (compare match value)*/
void Timer0_voidSetCR0Value(u8 Copy_u8CR0Value)
{
	OCR0 = Copy_u8CR0Value;
}

void TIMER0_voidRunTimer0OFAsync(void(*ptr_pfCompareMatchInterrupt)(void),u8 Copy_u8PreLoad)
{
	/*Set Timer0 Mode to be OF*/
	CLR_BIT(TCCR0 , TCCR0_WGM01);
	CLR_BIT(TCCR0 , TCCR0_WGM00);

	/*Setting PreLoad Vlaue*/
	TCNT0 = Copy_u8PreLoad;

	/*Enable Compare match Interrupt*/
	SET_BIT(TIMSK,TIMSK_OCIE0);

	/*Enable Global Interrupt*/
	GIE_voidEnable();

	if(ptr_pfCompareMatchInterrupt != NULL)
		Global_pfCTCcallback = ptr_pfCompareMatchInterrupt;

	/*Setting Prescaler ==> 8*/
	TCCR0 &= PRESCALER_MASK;
	TCCR0 |= DIVIDE_BY_256;
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

void Timer1_voidInitPWM(void)
{
	/*Fast PWM channel A*/
	CLR_BIT(TCCR1A, TCCR1A_COM1A0);
	SET_BIT(TCCR1A, TCCR1A_COM1A1);

	/*set wave generation mode*/
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	SET_BIT(TCCR1A, TCCR1A_WGM11);
	SET_BIT(TCCR1B, TCCR1B_WGM12);
	SET_BIT(TCCR1B, TCCR1B_WGM13);

	/*Set the TOP value (for set on top)*/
	ICR1 = 20000;

	/*set prescaler*/
#if(TMR1_PRESCALER == DIV_BY_8)
	{
		CLR_BIT(TCCR1B, TCCR1_CS10);
		SET_BIT(TCCR1B, TCCR1_CS11);
		CLR_BIT(TCCR1B, TCCR1_CS12);
	}
#endif
}

void Timer1_voidSetAngle(u16 Copy_u16Angle)
{
	if((Copy_u16Angle >= 1000) || (Copy_u16Angle <= 2000))
	{
		OCR1A = Copy_u16Angle;
	}
}

void Timer1_voidICUInit(void)  /*pin D6*/
{
	/*Run timer in normal mode*/
	CLR_BIT(TCCR1A, TCCR1A_WGM10);
	CLR_BIT(TCCR1A, TCCR1A_WGM11);
	CLR_BIT(TCCR1B, TCCR1B_WGM12);
	CLR_BIT(TCCR1B, TCCR1B_WGM13);

	/*Compare output mode : normal*/
	CLR_BIT(TCCR1A, TCCR1A_COM1A0);
	CLR_BIT(TCCR1A, TCCR1A_COM1A1);

	/*set prescaler to DIV_8*/
	TCCR0 &= PRESCALER_MASK;
	TCCR0 |= DIVIDE_BY_8;

	/*set trigger source to rising edge initially*/
	SET_BIT(TCCR1B,TCCR1B_ICES1);

	/*enable input capture interrupt*/
	SET_BIT(TIMSK,TIMSK_TICIE1);
}

u8 Timer1_u8GetICUReading(void)
{
	return ICR1;
}

void ICU_voidSetTriggerEdge(u8 Copy_u8Edge)
{
	if(Copy_u8Edge == ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B,TCCR1B_ICES1);
	}
	else if(Copy_u8Edge == ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B,TCCR1B_ICES1);
	}
}

void ICU_u8SetCallBack(void (*Copy_pvCallBackFunc)(void))
{
	if(Copy_pvCallBackFunc != NULL)
	{
		ICU_pvCallBackFunc = Copy_pvCallBackFunc;
	}
	else
	{
		/*do nothing*/
	}
}

void __vector__6 (void) __attribute__((signal));
void __vector__6 (void)
{
	if(ICU_pvCallBackFunc != NULL)
	{
		ICU_pvCallBackFunc();
	}
}



