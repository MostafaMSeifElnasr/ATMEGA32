/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    USART               ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidInit(void);

void USART_voidTransmitDataSync(u8 Copy_u8Data);

u8 USART_u8ReceiveDataSync(void);

void USART_voidRecieveDataAsync(u8 * Copy_u8Reading, void(*PTF_Application)(void));

void USART_voidSendString(u8 Copy_Arr[]);

void USART_voidReceiveString(u8 * Copy_u8Arr);

#endif
