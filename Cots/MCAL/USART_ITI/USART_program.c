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
#include "PORT_interface.h"
#include "DIO_interface.h"

#include "USART_register.h"
#include "USART_interface.h"
#include "USART_config.h"
#include "USART_private.h"

void USART_voidInit(void)
{
    /*Set Baud Rate to 9600 bPS*/
	UBRRL = 51;

	/*Enable Receiver & Transmitter*/
	UCSRB = (1<<UCSRB_TXEN) | (1<<UCSRB_TXEN);

	/*Set frame format: 8-bits data, 1 stop bit*/
	UCSRC = (1<<UCSRC_URSEL) | (1<<UCSRC_UCSZ1) | (1<<UCSRC_UCSZ0);
}

void USART_voidSendData(u8 Copy_u8Data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UCSRA_UDRE)) );

	/* Put data into buffer, sends the data */
	UDR = Copy_u8Data;
}

u8 USART_u8ReceiveData(void)
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<UCSRA_RXC)) );

	/* Get and return received data from buffer */
	return UDR;
}
