/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    Switches            ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef SWITCHES_INTERFACE_H_
#define SWITCHES_INTERFACE_H_

#define PB_PULLUP      0
#define PB_PULLDOWN    1

#define PB_PU_PRESSED      0
#define PB_PU_RELEASED     1
#define PB_PD_PRESSED      2
#define PB_PD_RELEASED     3


void PB_voidInit(u8 Copy_u8PB_Port, u8 Copy_u8PB_Pin, u8 Copy_u8Connection);

u8 PB_u8GetState(u8 Copy_u8PB_Port, u8 Copy_u8PB_Pin, u8 Copy_u8Connection);

#endif
