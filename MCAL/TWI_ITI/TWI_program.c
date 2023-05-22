/***************************************************************************/
/*Author      : Saad Mohamed										       */
/*File Name   : TWI_program.c                                              */
/*Layer       : MCAL										  		       */
/*Description : This file contains functions' implementation of TWI module */
/*Date        : 16 April 2023                                               */
/***************************************************************************/
#include "../../LIB/LIB_STD_TYPES.h"
#include "../../LIB/LIB_BIT_MATH.h"

#include "TWI_private.h"
#include "TWI_interface.h"


/*************************************************************************/
/*********************Functions' Implementation***************************/
/*************************************************************************/

void TWI_voidMasterInit(u8 Copy_u8SlaveAddress)
{
	/*Check if user want to set an Address
	 *for the master or not*/
	if(Copy_u8SlaveAddress != 0)
	{
		/*Assign the Node Address in the 7 MSB of TWAR*/
		TWAR = (Copy_u8SlaveAddress<<1);
	}

	/*Enable Acknowledge bit*/
//	SET_BIT(TWCR,TWCR_TWEA);

	/*Set Clock Frequency to 400Kbps*/
	/*Set TWBR to be 2 According to Provided Equation*/
	TWBR = 2;
	/*Assume the TWBR to be 0*/
	CLR_BIT(TWSR,TWSR_TWPS0);
	CLR_BIT(TWSR,TWSR_TWPS1);

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}

void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress)
{
	/*Assign the Node Address in the 7 MSB of TWAR*/
	TWAR = (Copy_u8SlaveAddress<<1);

	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Enable TWI*/
	SET_BIT(TWCR,TWCR_TWEN);
}

TWI_ErrorState TWI_SendStartCondition(void)
{
	TWI_ErrorState Local_ErrorState = NoError;

	/*Send Start Condition*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear The Interrupt Flag to operate the Command*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling till the Interrupt flag is raised
	 *Command is Executed*/
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/*Check 5 MSB in TWSR for Error*/
	if((TWSR & 0xF8) != START_ACK)
	{
		Local_ErrorState = StartConditionError;
	}
	else{/*Do Nothing*/}

	return Local_ErrorState;
}

TWI_ErrorState TWI_SendRepeatedStart(void)
{
	TWI_ErrorState Local_ErrorState = NoError;

	/*Send Start Condition*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear The Interrupt Flag to operate the Command*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling till the Interrupt flag is raised
	 *Command is Executed*/
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/*Check 5 MSB in TWSR for Error*/
	if((TWSR & STATUS_MASK) != REP_START_ACK)
	{
		Local_ErrorState = RepeatedStartError;
	}

	return Local_ErrorState;
}

TWI_ErrorState TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorState Local_ErrorState = NoError;

	/*Send the 7bit slave address to the bus*/
	TWDR = (Copy_u8SlaveAddress <<1);

	/*Clear the LSB in the data register for the write request*/
	CLR_BIT(TWDR,0);

	/*Clear The Start Condition Bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear The Interrupt Flag to operate the Command*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling till the Interrupt flag is raised
	 *Command is Executed*/
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/*Check 5 MSB in TWSR for Error*/
	if((TWSR & STATUS_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrorState = SlaveAddressWithWriteError;
	}

	return Local_ErrorState;
}

TWI_ErrorState TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorState Local_ErrorState = NoError;

	/*Send the 7bit slave address to the bus*/
	TWDR = (Copy_u8SlaveAddress <<1);

	/*Set the LSB in the data register for the write request*/
	SET_BIT(TWDR,0);

	/*Clear The Start Condition Bit*/
	CLR_BIT(TWCR,TWCR_TWSTA);

	/*Clear The Interrupt Flag to operate the Command*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling till the Interrupt flag is raised
	 *Command is Executed*/
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/*Check 5 MSB in TWSR for Error*/
	if((TWSR & STATUS_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_ErrorState = SlaveAddressWithReadError;
	}

	return Local_ErrorState;
}

TWI_ErrorState TWI_MasterSendData(u8 Copy_u8Data)
{
	TWI_ErrorState Local_ErrorState = NoError;

	/*Write Data on Data Register*/
	TWDR = Copy_u8Data ;

	/*Clear The Interrupt Flag to operate the Command*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling till the Interrupt flag is raised
	 *Command is Executed*/
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/*Check 5 MSB in TWSR for Error*/
	if((TWSR & STATUS_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_ErrorState = MasterSendDataError;
	}

	return Local_ErrorState;
}

TWI_ErrorState TWI_MasterReceiveData(u8* Copy_pu8Data)
{
	TWI_ErrorState Local_ErrorState = NoError;

	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	/*Clear The Interrupt Flag to Allow Slave to Send Data*/
	SET_BIT(TWCR,TWCR_TWINT);

	/*Polling till the Interrupt flag is raised
	 *Command is Executed*/
	while(!GET_BIT(TWCR,TWCR_TWINT));

	/*Check 5 MSB in TWSR for Error*/
	if((TWSR & STATUS_MASK) != MSTR_RD_BYTE_WITH_ACK)
	{
		Local_ErrorState = MasterReceiveDataError;
	}
	else
	{
		/*Read Received Data From Data Register*/
		* Copy_pu8Data = TWDR ;
	}

	return Local_ErrorState;
}

TWI_ErrorState TWI_MasterReceiveStr(u8* Copy_u8Str, u8 Copy_u8STRLength)
{
	TWI_ErrorState Local_ErrorState = NoError;
	u8 i;

	/*Enable Acknowledge bit*/
	SET_BIT(TWCR,TWCR_TWEA);

	for(i=0 ; i <= Copy_u8STRLength ; i++)
	{
		/*Clear The Interrupt Flag to Allow Slave to Send Data*/
		SET_BIT(TWCR,TWCR_TWINT);

		/*Polling till the Interrupt flag is raised
		 *Command is Executed*/
		while(!GET_BIT(TWCR,TWCR_TWINT));

		/*Check 5 MSB in TWSR for Error*/
		if((TWSR & STATUS_MASK) != MSTR_RD_BYTE_WITH_ACK)
		{
			Local_ErrorState = MasterReceiveDataError;
		}
		else
		{
			/*Read Received Data From Data Register*/
			Copy_u8Str[i] = TWDR ;
		}
		if (i == (Copy_u8STRLength-1))
		{
			/*Disable Acknowledge bit*/
			CLR_BIT(TWCR,TWCR_TWEA);
		}
	}
	Copy_u8Str[i-1]='\0';
	return Local_ErrorState;
}

void TWI_SendStopCondition(void)
{
	/*Generate Stop Condition on the bus*/
	SET_BIT(TWCR,TWCR_TWSTO);

	/*Clear The Interrupt Flag to operate the Command*/
	SET_BIT(TWCR,TWCR_TWINT);
}
