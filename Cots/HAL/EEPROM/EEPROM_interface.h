/************************************************************************/
/*Author      : Saad Mohamed										    */
/*File Name   : EEPROM_interface.h                                      */
/*Layer       : HAL									     			    */
/*Description : This file contains interfacing parameters of TWI module */
/*Date        : 17 April 2023                                           */
/************************************************************************/

/******** Guard *********/
#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

/*************************************************************************/
/*************************Functions' prototypes***************************/
/*************************************************************************/

/*This Function Shall Send Data to EEPROM*/
void EEPROM_voidSendByte(u16 Copy_u16Address,u8 Copy_u8Data);

/*This Function Shall Read Data from EEPROM*/
u8 EEPROM_u8ReceiveByte(u16 Copy_u16Address);

/*This Function Shall Read String From EEPROM*/
void EEPROM_u8ReceiveStr(u16 Copy_u16Address,u8* Copy_u8Str, u8 Copy_strlength);
#endif /* EEPROM_INTERFACE_H_ */
