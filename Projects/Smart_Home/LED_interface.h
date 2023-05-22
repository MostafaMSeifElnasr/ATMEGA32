/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    LED                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

void LED_Init(u8 Copy_u8Port, u8 Copy_Pin);

void LED_ON(u8 Copy_u8Port, u8 Copy_Pin);

void LED_OFF(u8 Copy_u8Port, u8 Copy_Pin);

void LED_Toggle(u8 Copy_u8Port, u8 Copy_Pin);

#endif
