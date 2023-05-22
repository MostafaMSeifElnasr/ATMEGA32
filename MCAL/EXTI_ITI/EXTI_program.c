/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    EXTI                ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

/*Global pointer to function to holdINT0 ISR address*/
void (*EXTI_pvInt0Func)(void)=NULL;

/*Global pointer to function to holdINT1 ISR address*/
void (*EXTI_pvInt1Func)(void)=NULL;

/*Global pointer to function to holdINT2 ISR address*/
void (*EXTI_pvInt2Func)(void)=NULL;

/*******************************************************************************************/

void EXTI_voidEnable_INT0pre(void)
{
	/* SIE of INT0 */
	SET_BIT(GICR, GICR_INT0);

#if (EXTI_INT0_SENSE == EXTI_INT0_LOWLEVEL)
	{
		CLR_BIT(MCUCR, MCUCR_ISC00);
		CLR_BIT(MCUCR, MCUCR_ISC01);
	}

#elif (EXTI_INT0_SENSE == EXTI_INT0_ONCHANGE)
	{
		SET_BIT(MCUCR, MCUCR_ISC00);
		CLR_BIT(MCUCR, MCUCR_ISC01);
	}

#elif (EXTI_INT0_SENSE == EXTI_INT0_FALLINGEDGE)
	{
		CLR_BIT(MCUCR, MCUCR_ISC00);
		SET_BIT(MCUCR, MCUCR_ISC01);
	}

#elif (EXTI_INT0_SENSE == EXTI_INT0_RISINGEDGE)
	{
		SET_BIT(MCUCR, MCUCR_ISC00);
		SET_BIT(MCUCR, MCUCR_ISC01);
	}

#endif
}

/*******************************************************************************************/

void EXTI_voidEnable_INT1pre(void)
{
	/* SIE of INT1 */
	SET_BIT(GICR, GICR_INT1);

#if (EXTI_INT1_SENSE == EXTI_INT1_LOWLEVEL)
	{
		CLR_BIT(MCUCR, MCUCR_ISC10);
		CLR_BIT(MCUCR, MCUCR_ISC11);
	}

#elif (EXTI_INT1_SENSE == EXTI_INT1_ONCHANGE)
	{
		SET_BIT(MCUCR, MCUCR_ISC10);
		CLR_BIT(MCUCR, MCUCR_ISC11);
	}

#elif (EXTI_INT1_SENSE == EXTI_INT1_FALLINGEDGE)
	{
		CLR_BIT(MCUCR, MCUCR_ISC10);
		SET_BIT(MCUCR, MCUCR_ISC11);
	}

#elif (EXTI_INT1_SENSE == EXTI_INT1_RISINGEDGE)
	{
		SET_BIT(MCUCR, MCUCR_ISC10);
		SET_BIT(MCUCR, MCUCR_ISC11);
	}
#endif
}

/*******************************************************************************************/

void EXTI_voidEnable_INT2pre(void)
{
	/* SIE of INT2 */
	SET_BIT(GICR, GICR_INT2);
#if (EXTI_INT2_SENSE == EXTI_INT2_FALLINGEDGE)
	{
		CLR_BIT(MCUCSR, MCUCSR_ISC2);
	}

#elif (EXTI_INT2_SENSE == EXTI_INT2_RISINGEDGE)
	{
		SET_BIT(MCUCSR, MCUCSR_ISC2);
	}
#endif
}

/*******************************************************************************************/

void EXTI_voidEnableInterrupt(u8 Copy_u8INT_ID, u8 Copy_u8Signal)
{
	/* SIE */
	switch(Copy_u8INT_ID)
	{
	case EXTI_INT0:

		/* SIE of INT0 */
		SET_BIT(GICR, GICR_INT0);

		/* Set INT0 Sense Signal */
		switch(Copy_u8Signal)
		{
		case INT0_LOW_LEVEL:
			CLR_BIT(MCUCR, MCUCR_ISC00);
			CLR_BIT(MCUCR, MCUCR_ISC01);
			break;

		case INT0_ON_CHANGE:
			SET_BIT(MCUCR, MCUCR_ISC00);
			CLR_BIT(MCUCR, MCUCR_ISC01);
			break;

		case INT0_FALLING_EDGE:
			CLR_BIT(MCUCR, MCUCR_ISC00);
			SET_BIT(MCUCR, MCUCR_ISC01);
			break;

		case INT0_RISING_EDGE:
			SET_BIT(MCUCR, MCUCR_ISC00);
			SET_BIT(MCUCR, MCUCR_ISC01);
			break;
		}
		break;
		case EXTI_INT1:

			/* SIE of INT1 */
			SET_BIT(GICR, GICR_INT1);

			/* Set INT1 Sense Signal */
			switch(Copy_u8Signal)
			{
			case INT1_LOW_LEVEL:
				CLR_BIT(MCUCR, MCUCR_ISC10);
				CLR_BIT(MCUCR, MCUCR_ISC11);
				break;

			case INT1_ON_CHANGE:
				SET_BIT(MCUCR, MCUCR_ISC10);
				CLR_BIT(MCUCR, MCUCR_ISC11);
				break;

			case INT1_FALLING_EDGE:
				CLR_BIT(MCUCR, MCUCR_ISC10);
				SET_BIT(MCUCR, MCUCR_ISC11);
				break;

			case INT1_RISING_EDGE:
				SET_BIT(MCUCR, MCUCR_ISC10);
				SET_BIT(MCUCR, MCUCR_ISC11);
				break;
			}
			break;
			case EXTI_INT2:

				/* SIE of INT2 */
				SET_BIT(GICR, GICR_INT2);

				/* Set INT1 Sense Signal */
				switch(Copy_u8Signal)
				{
				case INT2_FALLING_EDGE:
					CLR_BIT(MCUCSR, MCUCSR_ISC2);
					break;

				case INT2_RISING_EDGE:
					SET_BIT(MCUCSR, MCUCSR_ISC2);
					break;
				}
				break;
	}

}

/*******************************************************************************************/

void EXTI_voidDisableInterrupt(u8 Copy_u8INT_ID)
{
	/* SIE */
	switch(Copy_u8INT_ID)
	{
	case EXTI_INT0:
		CLR_BIT(GICR, GICR_INT0);
		break;
	case EXTI_INT1:
		CLR_BIT(GICR, GICR_INT1);
		break;
	case EXTI_INT2:
		CLR_BIT(GICR, GICR_INT2);
		break;
	}
}

/*******************************************************************************************/

u8 EXTI_voidSetCallBackINT0(void(*Copy_pvToFunc)(void))
{
	u8 Local_ErrorState = OK;

	if(Copy_pvToFunc != NULL)
	{
		EXTI_pvInt0Func = Copy_pvToFunc;
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}
	return Local_ErrorState;
}

/*******************************************************************************************/

u8 EXTI_voidSetCallBackINT1(void(*Copy_pvToFunc)(void))
{
	u8 Local_ErrorState = OK;

	if(Copy_pvToFunc != NULL)
	{
		EXTI_pvInt1Func = Copy_pvToFunc;
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}
	return Local_ErrorState;
}

/*******************************************************************************************/

u8 EXTI_voidSetCallBackINT2(void(*Copy_pvToFunc)(void))
{
	u8 Local_ErrorState = OK;

	if(Copy_pvToFunc != NULL)
	{
		EXTI_pvInt2Func = Copy_pvToFunc;
	}
	else
	{
		Local_ErrorState = NULL_POINTER;
	}
	return Local_ErrorState;
}

/*******************************************************************************************/


/*INT0 ISR*/
void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if(EXTI_pvInt0Func != NULL)
	{
		EXTI_pvInt0Func();
	}
	else
	{
		//do nothing
	}
}

/*******************************************************************************************/

/*INT1 ISR*/
void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if(EXTI_pvInt1Func != NULL)
	{
		EXTI_pvInt1Func();
	}
	else
	{
		//do nothing
	}
}

/*******************************************************************************************/

/*INT2 ISR*/
void __vector_3 (void) __attribute__((signal));
void __vector_3 (void)
{
	if(EXTI_pvInt2Func != NULL)
	{
		EXTI_pvInt2Func();
	}
	else
	{
		//do nothing
	}
}

/*******************************************************************************************/


