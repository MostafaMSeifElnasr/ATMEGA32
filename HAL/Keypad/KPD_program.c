/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    KPD                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"


void KPD_voidInit(void)
{
	/*1)initialize all rows to be input pull up*/
	DIO_voidSetPinDirection(KPD_PORT , KPD_ROW0 , DIO_u8PIN_INPUT);
	DIO_voidSetPinDirection(KPD_PORT , KPD_ROW1 , DIO_u8PIN_INPUT);
	DIO_voidSetPinDirection(KPD_PORT , KPD_ROW2 , DIO_u8PIN_INPUT);
	DIO_voidSetPinDirection(KPD_PORT , KPD_ROW3 , DIO_u8PIN_INPUT);

	DIO_u8SetPinValue(KPD_PORT, KPD_ROW0, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT, KPD_ROW1, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT, KPD_ROW2, DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(KPD_PORT, KPD_ROW3, DIO_u8PIN_HIGH);


	/*2)initialize all columns to be output*/
	DIO_voidSetPinDirection(KPD_PORT , KPD_COL0 , DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(KPD_PORT , KPD_COL1 , DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(KPD_PORT , KPD_COL2 , DIO_u8PIN_OUTPUT);
	DIO_voidSetPinDirection(KPD_PORT , KPD_COL3 , DIO_u8PIN_OUTPUT);


	/*3)setting the columns to be high*/
	DIO_voidSetPinValue(KPD_PORT , KPD_COL0 ,  DIO_u8PIN_HIGH);
	DIO_voidSetPinValue(KPD_PORT , KPD_COL1 ,  DIO_u8PIN_HIGH);
	DIO_voidSetPinValue(KPD_PORT , KPD_COL2 ,  DIO_u8PIN_HIGH);
	DIO_voidSetPinValue(KPD_PORT , KPD_COL3 ,  DIO_u8PIN_HIGH);
}


u8 KPD_u8GetPressedKey(void)
{
	/*local variable to check whether the switch is pressed or not*/
	u8 Local_u8State ;

	/*local variable to store the value of the pressed key*/
	u8 Local_u8PressedKey = KPD_NO_PRESSED_KEY ;

	/*local variables to iterate over rows and columns*/
	u8 Local_u8RowIterator ;
	u8 Local_u8ColIterator ;

	u8 Local_au8Cols[COL_NUM]={KPD_COL0 , KPD_COL1 , KPD_COL2 , KPD_COL3};
	u8 Local_au8Rows[ROW_NUM]={KPD_ROW0 , KPD_ROW1 , KPD_ROW2 , KPD_ROW3};


	u8 KPD_ARR[ROW_NUM][COL_NUM] = KPD_VALUES;

	/*looping over columns to activate them*/
	for(Local_u8ColIterator=0 ; Local_u8ColIterator < COL_NUM ; Local_u8ColIterator++)
	{
		/*activate column be column*/
		DIO_voidSetPinValue(KPD_PORT ,Local_au8Cols[Local_u8ColIterator] , DIO_u8PIN_LOW );

		/*looping over rows to read them*/
		for(Local_u8RowIterator = 0 ; Local_u8RowIterator < ROW_NUM ; Local_u8RowIterator++)
		{
			/*checking whether any switch is pressed or not*/
			Local_u8State = DIO_u8GetPinValue(KPD_PORT ,Local_au8Rows[Local_u8RowIterator]) ;

			/*in case of a pressed key*/
			if(Local_u8State == 0)
			{
				/*getting the value of the pressed key*/
				Local_u8PressedKey = KPD_ARR[Local_u8RowIterator][Local_u8ColIterator];

				/*polling till the user releases the switch*/
				while(Local_u8State==0)
				{
					Local_u8State = DIO_u8GetPinValue(KPD_PORT ,Local_au8Rows[Local_u8RowIterator]) ;
				}

				//				/*deactivate the recent column before return*/
				//				DIO_voidSetPinValue(KPD_PORT ,Local_au8Cols[Local_u8ColIterator] , DIO_HIGH_PIN);

				/*ending the loop*/
				return Local_u8PressedKey ;
			}
		}

		/*deactivate column be column*/
		DIO_voidSetPinValue(KPD_PORT ,Local_au8Cols[Local_u8ColIterator] , DIO_u8PIN_HIGH);
	}

	return Local_u8PressedKey ;

}






