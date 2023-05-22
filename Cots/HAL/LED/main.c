/************************************************************************/
/*Author      : Saad Mohamed										    */
/*File Name   : main.c (LED_String)                                     */
/*Layer       : APP									     			    */
/*Description : This file contains the code for the LED_String project  */
/*Date        : 27 March 2023                                           */
/************************************************************************/

#include <util/delay.h>

#include "LIB_BIT_MATH.h"
#include "LIB_STD_TYPES.h"
#include "DIO_interface.h"
#include "LED_interface.h"

/*Macro definitions*/
#define Mode_One   0
#define Mode_Two   1
#define Mode_Three 2
#define Mode_Four  3
#define Mode_Five  4
#define Mode_Six   5
#define Mode_Seven 6
#define Mode_Eight 7

/*Function Prototypes*/

/*This function is to read the value of the Dip switch and convert it to decimal values*/
u8 APP_u8GetDipValue(void);

/*This function is for Mode_One flashing every 500ms*/
void APP_voidFlashing(void);

/*This function is for Mode_Two Shifting Left every 250ms*/
void APP_voidShiftingLeft(void);

/*This function is for Mode_Three Shifting Right every 250ms*/
void APP_voidShiftingRight(void);

/*This function is for Mode_Four Converging 2-LEDs every 300ms*/
void APP_voidConverging(void);

/*This function is for Mode_Five Diverging 2-LEDs every 300ms*/
void APP_voidDiverging(void);

/*This function is for Mode_Six Ping-Bong effect every 250ms*/
void APP_voidPingPong(void);

/*This function is for Mode_Seven Snake effect every 300ms*/
void APP_voidSnakeEffect(void);

/*This function is for Mode_Eight Converging Diverging 2-LEDs every 300ms*/
void APP_voidConvergingDiverging(void);

void main(void)
{
	/*Initializing three pins in port C as out put for the Dip switch connection*/
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN0,DIO_PIN_INPUT_PULLUP);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN1,DIO_PIN_INPUT_PULLUP);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_PIN_INPUT_PULLUP);

	/*Initializing port A as out put for the LED String connection*/
	LED_voidPortInit(LED_PORTA);

	/*Creating a variable to store the decimal equivalent of the dip switch value*/
	u8 App_u8DipVlaue;

	while(1)
	{
		/*Reading the value of the Dip Switch*/
		App_u8DipVlaue = APP_u8GetDipValue();
		/*Switching over the Dip Switch values*/
		switch(App_u8DipVlaue)
		{
		  case(Mode_One):
				  APP_voidFlashing();
	    		  break;
		  case(Mode_Two):
				  APP_voidShiftingLeft();
		  	      break;
		  case(Mode_Three):
				  APP_voidShiftingRight();
		  	      break;
		  case(Mode_Four):
				  APP_voidConverging();
		  		  break;
		  case(Mode_Five):
		          APP_voidDiverging();
		  	      break;
		  case(Mode_Six):
				  APP_voidPingPong();
		  	      break;
		  case(Mode_Seven):
				  APP_voidSnakeEffect();
		  	      break;
		  case(Mode_Eight):
				  APP_voidConvergingDiverging();
		  	     break;
		}
	}
}

u8 APP_u8GetDipValue(void)
{
	/*Creating three local variables to store the dip switch values*/
	u8 Local_u8DipSwitchPin0;
	u8 Local_u8DipSwitchPin1;
	u8 Local_u8DipSwitchPin2;

	/*Creating a local variable to store the decimal equivalent of the dip switch value*/
	u8 Local_u8DipVlaue;

	/*Get the value of the three Dip switch ports*/
	Local_u8DipSwitchPin0 = DIO_u8GetPinValue(DIO_PORTC,DIO_PIN0);
	Local_u8DipSwitchPin1 = DIO_u8GetPinValue(DIO_PORTC,DIO_PIN1);
	Local_u8DipSwitchPin2 = DIO_u8GetPinValue(DIO_PORTC,DIO_PIN2);

	/*Binary to Decimal conversion function*/
	Local_u8DipVlaue = (Local_u8DipSwitchPin0*1)+(Local_u8DipSwitchPin1*2)+(Local_u8DipSwitchPin2*4);

	/*Return the final Decimal value of the Dip Switch*/
	return Local_u8DipVlaue;
}

void APP_voidFlashing(void)
{
	/*Creating a local variable to store the decimal value of dip switch*/
	u8 Local_u8DipVlaue;

	/*loop to perform the required task and re-reads the value of switch*/
	do{
		LED_voidPortValue(LED_PORTA,0xff);
		_delay_ms(500);
		LED_voidPortValue(LED_PORTA,0);
		_delay_ms(500);

		/*Re-reading the value of dip switch to exit the function*/
		Local_u8DipVlaue = APP_u8GetDipValue();
	}while(Local_u8DipVlaue == Mode_One);
}

void APP_voidShiftingLeft(void)
{
	/*Creating a local variable to store the decimal value of dip switch*/
	u8 Local_u8DipVlaue;

	/*Creating local array to store the values of the led port*/
	u8 Local_u8Array[8]={1,2,4,8,16,32,64,128};

	/*Creating local iterator*/
	u8 Local_u8I;

	/*loop to perform the required task and re-reads the value of switch*/
	do{

		/*loop for passing different values to the led port*/
		for(Local_u8I = 0 ; Local_u8I < 8 ; Local_u8I++)
		{
			LED_voidPortValue(LED_PORTA,Local_u8Array[Local_u8I]);
			_delay_ms(250);
		}

		/*Re-reading the value of dip switch to exit the function*/
		Local_u8DipVlaue = APP_u8GetDipValue();
	}while(Local_u8DipVlaue == Mode_Two);
}

void APP_voidShiftingRight(void)
{
	/*Creating a local variable to store the decimal value of dip switch*/
	u8 Local_u8DipVlaue;

	/*Creating local array to store the values of the led port*/
	u8 Local_u8Array[8]={128,64,32,16,8,4,2,1};

	/*Creating local iterator*/
	u8 Local_u8I;

	/*loop to perform the required task and re-reads the value of switch*/
	do{

		/*loop for passing different values to the led port*/
		for(Local_u8I=0;Local_u8I<8;Local_u8I++)
		{
			LED_voidPortValue(LED_PORTA,Local_u8Array[Local_u8I]);
			_delay_ms(250);
		}

		/*Re-reading the value of dip switch to exit the function*/
		Local_u8DipVlaue = APP_u8GetDipValue();
	}while(Local_u8DipVlaue == Mode_Three);
}

void APP_voidConverging(void)
{
	/*Creating a local variable to store the decimal value of dip switch*/
	u8 Local_u8DipVlaue;

	/*Creating local array to store the values of the led port*/
	u8 Local_u8Array[4]={24,36,66,129};

	/*Creating local iterator*/
	u8 Local_u8I;

	/*loop to perform the required task and re-reads the value of switch*/
	do{

		/*loop for passing different values to the led port*/
		for(Local_u8I=0;Local_u8I<4;Local_u8I++)
		{
			LED_voidPortValue(LED_PORTA,Local_u8Array[Local_u8I]);
			_delay_ms(300);
		}

		/*Re-reading the value of dip switch to exit the function*/
		Local_u8DipVlaue = APP_u8GetDipValue();
	}while(Local_u8DipVlaue == Mode_Four);
}

void APP_voidDiverging(void)
{
	/*Creating a local variable to store the decimal value of dip switch*/
	u8 Local_u8DipVlaue;

	/*Creating local array to store the values of the led port*/
	u8 Local_u8Array[4]={129,66,36,24};

	/*Creating local iterator*/
	u8 Local_u8I;

	/*loop to perform the required task and re-reads the value of switch*/
	do{

		/*loop for passing different values to the led port*/
		for(Local_u8I=0;Local_u8I<4;Local_u8I++)
		{
			LED_voidPortValue(LED_PORTA,Local_u8Array[Local_u8I]);
			_delay_ms(300);
		}

		/*Re-reading the value of dip switch to exit the function*/
		Local_u8DipVlaue = APP_u8GetDipValue();
	}while(Local_u8DipVlaue == Mode_Five);
}

void APP_voidPingPong(void)
{
	/*Creating a local variable to store the decimal value of dip switch*/
	u8 Local_u8DipVlaue;

	/*Creating local array to store the values of the led port*/
	u8 Local_u8Array[15]={1,2,4,8,16,32,64,128,64,32,16,8,4,2,1};

	/*Creating local iterator*/
	u8 Local_u8I;

	/*loop to perform the required task and re-reads the value of switch*/
	do{

		/*loop for passing different values to the led port*/
		for(Local_u8I=0;Local_u8I<15;Local_u8I++)
		{
			LED_voidPortValue(LED_PORTA,Local_u8Array[Local_u8I]);
			_delay_ms(250);
		}

		/*Re-reading the value of dip switch to exit the function*/
		Local_u8DipVlaue = APP_u8GetDipValue();
	}while(Local_u8DipVlaue == Mode_Six);
}

void APP_voidSnakeEffect(void)
{
	/*Creating a local variable to store the decimal value of dip switch*/
	u8 Local_u8DipVlaue;

	/*Creating local array to store the values of the led port*/
	u8 Local_u8Array[6]={7,14,28,56,112,224};

	/*Creating local iterator*/
	u8 Local_u8I;

	/*loop to perform the required task and re-reads the value of switch*/
	do{

		/*loop for passing different values to the led port*/
		for(Local_u8I=0;Local_u8I<6;Local_u8I++)
		{
			LED_voidPortValue(LED_PORTA,Local_u8Array[Local_u8I]);
			_delay_ms(300);
		}

		/*Re-reading the value of dip switch to exit the function*/
		Local_u8DipVlaue = APP_u8GetDipValue();
	}while(Local_u8DipVlaue == Mode_Seven);
}

void APP_voidConvergingDiverging(void)
{
	/*Creating a local variable to store the decimal value of dip switch*/
	u8 Local_u8DipVlaue;

	/*Creating local array to store the values of the led port*/
	u8 Local_u8Array[7]={24,36,66,129,66,36,24};

	/*Creating local iterator*/
	u8 Local_u8I;

	/*loop to perform the required task and re-reads the value of switch*/
	do{

		/*loop for passing different values to the led port*/
		for(Local_u8I=0;Local_u8I<7;Local_u8I++)
		{
			LED_voidPortValue(LED_PORTA,Local_u8Array[Local_u8I]);
			_delay_ms(300);
		}

		/*Re-reading the value of dip switch to exit the function*/
		Local_u8DipVlaue = APP_u8GetDipValue();
	}while(Local_u8DipVlaue == Mode_Eight);
}

