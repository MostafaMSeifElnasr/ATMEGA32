/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    EEPROM              ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#include "util/delay.h"

#include "STD_TYPES.h"
#include "BIT_MATH.h"

//#include "TWI_private.h"
#include "TWI_interface.h"

#include "EEPROM_private.h"
#include "EEPROM_config.h"
#include "EEPROM_interface.h"



void EEPROM_voidSendByte(u16 Copy_u16Address,u8 Copy_u8Data)
{
	u8 Local_u8Address = 0;

	/*EEPROM Slave Address*/
	Local_u8Address = ((EEPROM_ADDRESS_MASK)|(EEPROM_A2_ADDRESS<<2)|(u8)(Copy_u16Address>>8));

	/*Send Start Condition to Start Communication and Control the Bus*/
	TWI_SendStartCondition();

	/*Send EEPROM Slave Address with Write*/
	TWI_SendSlaveAddressWithWrite(Local_u8Address);

	/*Send the Byte Location in the EEPROM*/
	TWI_MasterSendData((u8)Copy_u16Address);

	/*Send Required Data*/
	TWI_MasterSendData(Copy_u8Data);

	/*Send Stop Condition to Stop Communication and Free the Bus*/
	TWI_SendStopCondition();

	/*Delay until the write cycle is finished*/
	_delay_ms(20);
}

//u8 EEPROM_u8ReceiveByte(u16 Copy_u16Address)
//{
//	u8 Local_u8Address = 0,Local_u8Data = 0;
//
//	Local_u8Address = ((EEPROM_ADDRESS_MASK)|(EEPROM_A2_ADDRESS<<2)|(u8)(Copy_u16Address>>8));
//
//	/*Send Start Condition to Start Communication and Control the Bus*/
//	TWI_SendStartCondition();
//
//	/*Send EEPROM Slave Address with Write*/
//	TWI_SendSlaveAddressWithWrite(Local_u8Address);
//
//	/*Send the Byte Location in the EEPROM*/
//	TWI_MasterSendData((u8)Copy_u16Address);
//
//	/*Send Repeat Start to Change Condition to Read*/
//	TWI_SendRepeatedStart();
//
//	/*Send EEPROM Slave Address with Write*/
//	TWI_SendSlaveAddressWithRead(Local_u8Address);
//
//	/*Send Required Data*/
//	TWI_MasterReceiveData(&Local_u8Data);
//
//	/*Send Stop Condition to Stop Communication and Free the Bus*/
//	TWI_SendStopCondition();
//
//	/*Delay until the write cycle is finished*/
//	_delay_ms(20);
//
//	return Local_u8Data;
//}

void EEPROM_voidReceiveStr(u16 Copy_u16Address,u8* Copy_u8Str, u8 Copy_strlength)
{
	u8 Local_u8Address = 0 ;
	Local_u8Address = ((EEPROM_ADDRESS_MASK)|(EEPROM_A2_ADDRESS<<2)|(u8)(Copy_u16Address>>8));

	/*Send Start Condition to Start Communication and Control the Bus*/
	TWI_SendStartCondition();

	/*Send EEPROM Slave Address with Write*/
	TWI_SendSlaveAddressWithWrite(Local_u8Address);

	/*Send the Byte Location in the EEPROM*/
	TWI_MasterSendData((u8)Copy_u16Address);

	/*Send Repeat Start to Change Condition to Read*/
	TWI_SendRepeatedStart();

	/*Send EEPROM Slave Address with Write*/
	TWI_SendSlaveAddressWithRead(Local_u8Address);

	/*Send Required Data*/
	TWI_MasterReceiveStr(Copy_u8Str,Copy_strlength);

	/*Send Stop Condition to Stop Communication and Free the Bus*/
	TWI_SendStopCondition();

	/*Delay until the write cycle is finished*/
	_delay_ms(20);
}

/*This Function Shall Send String to EEPROM*/
void EEPROM_voidSendString(u16 Copy_u16Address,u8* Copy_u8Str)
{
	u8 Iterator;
	for(Iterator = 0 ; Copy_u8Str[Iterator]!='\0' ; Iterator++ , Copy_u16Address++)
	{
		/*Send Received Char to EEPROM Addess*/
		EEPROM_voidSendByte(Copy_u16Address,Copy_u8Str[Iterator]);
	}
	/*Send Null Char to NEXT EEPROM Addess*/
//	EEPROM_voidSendByte(Copy_u16Address,'\0');

}
