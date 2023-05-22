/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    USART               ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"

#include "GIE_interface.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

u8 * Global_u8ptrReading = NULL;

void (*GlobalPtrTOFunc)(void)=NULL;

void USART_voidInit(void)
{
	/*Set Baud Rate to 9600 bPS*/
	UBRRL = 51;

	/*Enable Receiver & Transmitter*/
	UCSRB = (1<<UCSRB_RXEN) | (1<<UCSRB_TXEN);

	/*Set frame format: 8-bits data, 1 stop bit*/
	UCSRC = (1<<UCSRC_URSEL) | (1<<UCSRC_UCSZ1) | (1<<UCSRC_UCSZ0);
}

void USART_voidTransmitDataSync(u8 Copy_u8Data)
{
	/* Wait for empty transmit buffer */
	/* wait : while GETBIT(UCSRA,UCSRA_UDRE) == 0*/
	while ( !( UCSRA & (1<<UCSRA_UDRE)) );

	/* Put data into buffer, sends the data */
	UDR = Copy_u8Data;

	/*wait till transmit is complete*/
	while( !(UCSRA & (1<<UCSRA_TXC)) );

	/*setting the flag back*/
	SET_BIT(UCSRA, UCSRA_TXC);
}

u8 USART_u8ReceiveDataSync(void)
{
	/* Wait for data to be received */
	/* wait : while there is no data to read */
	while ( GET_BIT(UCSRA, UCSRA_RXC)==0 );

	/* Get and return received data from buffer */
	return UDR;
}

void USART_voidRecieveDataAsync(u8 * Copy_u8Reading, void(*PTF_Application)(void))
{
	/*enable global interrupt*/
	GIE_voidEnable();

	/*pass reading address to global variable*/
	Global_u8ptrReading = Copy_u8Reading;

	/*pass application function to be executed in ISR*/
	GlobalPtrTOFunc = PTF_Application;

	/*enable recieve complete interrupt*/
	SET_BIT(UCSRB, UCSRB_RXCIE);
}

void USART_voidSendString(u8 Copy_Arr[])
{
	u8 Local_u8Iterator;

	while(Copy_Arr[Local_u8Iterator] != '\0')
	{
		USART_voidTransmitDataSync(Copy_Arr[Local_u8Iterator]);
		Local_u8Iterator ++;
	}
}

void USART_voidReceiveString(u8 * Copy_u8Arr)
{
	u8 Local_u8Iterator=0;

	Copy_u8Arr[Local_u8Iterator]=USART_u8ReceiveDataSync();

	while(Copy_u8Arr[Local_u8Iterator] != '#')
	{
		Local_u8Iterator++;
		Copy_u8Arr[Local_u8Iterator]=USART_u8ReceiveDataSync();
	}
	Copy_u8Arr[Local_u8Iterator] = '\0';
}

void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	*Global_u8ptrReading = UDR;

	if(GlobalPtrTOFunc != NULL)
	{
		GlobalPtrTOFunc();
	}
}
