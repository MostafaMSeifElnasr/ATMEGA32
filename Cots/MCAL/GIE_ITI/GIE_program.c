/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    GIE                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_private.h"

void GIE_voidEnable(void)
{
	SET_BIT(SREG,SREG_I);
}

void GIE_viodDisable(void)
{
	CLR_BIT(SREG,SREG_I);
}
