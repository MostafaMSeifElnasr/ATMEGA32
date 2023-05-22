/************************************************************************/
/*Author      : Saad Mohamed										    */
/*File Name   : TWI_interface.h                                         */
/*Layer       : MCAL									   			    */
/*Description : This file contains interfacing parameters of TWI module */
/*Date        : 16 April 2023                                           */
/************************************************************************/

/******** Guard *********/
#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

/*Enum to define different Error State Types for TWI*/
typedef enum
{
	NoError,
	StartConditionError,
	RepeatedStartError,
	SlaveAddressWithWriteError,
	SlaveAddressWithReadError,
	MasterSendDataError,
	MasterReceiveDataError,
}TWI_ErrorState;

/*************************************************************************/
/*************************Functions' prototypes***************************/
/*************************************************************************/

/*Pass 0 in the slave address argument if master will not be addressed*/
void TWI_voidMasterInit(u8 Copy_u8SlaveAddress);

void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress);

TWI_ErrorState TWI_SendStartCondition(void);

TWI_ErrorState TWI_SendRepeatedStart(void);

TWI_ErrorState TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);

TWI_ErrorState TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);

TWI_ErrorState TWI_MasterSendData(u8 Copy_u8Data);

TWI_ErrorState TWI_MasterReceiveData(u8* Copy_pu8Data);

TWI_ErrorState TWI_MasterReceiveStr(u8* Copy_u8Str, u8 Copy_u8STRLength);

void TWI_SendStopCondition(void);

#endif /* TWI_INTERFACE_H_ */
