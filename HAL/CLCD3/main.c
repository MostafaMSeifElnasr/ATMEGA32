#include <util/delay.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "Timer_interface.h"
#include "GIE_interface.h"
#include "CLCD2_interface.h"

static u16 PeriodTicks = 0;
static u16 ONTicks = 0;

void Application(void);

void main(void)
{
	/*timer1 OC0 pin*/
	DIO_u8SetPinDirection(DIO_u8PORTB, DIO_u8PIN3, DIO_u8PIN_OUTPUT);

	/*Timer1 ICP pin*/
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN6, DIO_u8PIN_INPUT);

	/*Enable LCD*/
	LCD_voidLCDInit();

	/*Enable global interrupt*/
	GIE_voidEnable();

	/*Timer0 (Generated signal)*/
	Timer0_voidSetCR0Value(128);
	Timer0_voidRunPWMFastNonInverted();

	/*Timer1 ICU*/
	ICU_u8SetCallBack(Application);
	Timer1_voidICUInit();


	while(1)
	{
		/*wait till OnTicks and PeriodTicks are measured*/
		while((ONTicks == 0) && (PeriodTicks == 0));

		LCD_voidGoTORowCol(0, 0);
		LCD_voidSendString("ON Ticks =");
		LCD_voidSendVariable(ONTicks);
		LCD_voidGoTORowCol(1, 0);
		LCD_voidSendString("Period Ticks =");
		LCD_voidSendVariable(PeriodTicks);
	}
}

void Application(void)
{
	static u16 Reading1=0, Reading2=0, Reading3=0;
	static u8 counter=0;
	counter++;
	if(counter == 1)
	{
		Reading1 = Timer1_u8GetICUReading();
	}
	else if(counter == 2)
	{
		Reading2 = Timer1_u8GetICUReading();
		PeriodTicks = Reading2 - Reading1;
		ICU_voidSetTriggerEdge(ICU_FALLING_EDGE);
	}
	else if(counter == 3)
	{
		Reading3 = Timer1_u8GetICUReading();
		ONTicks = Reading3 - Reading2;
	}

}


