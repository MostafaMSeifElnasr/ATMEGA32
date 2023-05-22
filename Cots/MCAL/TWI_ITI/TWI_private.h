/************************************************************************/
/*Author      : Saad Mohamed										    */
/*File Name   : TWI_private.h                                           */
/*Layer       : MCAL									        	    */
/*Description : This file contains private parameters of TWI module     */
/*Date        : 16 April 2023                                           */
/************************************************************************/

/******** Guard *********/
#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_

/***********Private macros*************/
#define STATUS_MASK              0b11111000


/***********Actions' IDs***************/

#define START_ACK                0x08 /* start has been sent */
#define REP_START_ACK            0x10 /* repeated start */
#define SLAVE_ADD_AND_WR_ACK     0x18 /* Master transmit ( slave address + Write request ) ACK */
#define SLAVE_ADD_AND_RD_ACK     0x40 /* Master transmit ( slave address + Read request ) ACK */
#define MSTR_WR_BYTE_ACK         0x28 /* Master transmit data ACK */
#define MSTR_RD_BYTE_WITH_ACK    0x50 /* Master received data with ACK */
#define MSTR_RD_BYTE_WITH_NACK   0x58 /* Master received data with not ACK */
#define SLAVE_ADD_RCVD_RD_REQ    0xA8 /* means that slave address is received with read request */
#define SLAVE_ADD_RCVD_WR_REQ    0x60 /* means that slave address is received with write request */
#define SLAVE_DATA_RECEIVED      0x80 /* means that a byte is received */
#define SLAVE_BYTE_TRANSMITTED   0xB8 /* means that the written byte is transmitted */


/************Private bits***************/

#define TWCR    *((volatile u8*)(0x56))    //TWI Control Register
#define TWCR_TWINT               7			 //TWI interrupt flag
#define TWCR_TWEA                6			 //TWI Enable Acknowledge bit
#define TWCR_TWSTA               5			 //TWI Start Condition bit
#define TWCR_TWSTO               4			 //TWI Stop Condition bit
#define TWCR_TWWC                3			 //TWI Write Collision flag
#define TWCR_TWEN                2			 //TWI Enable bit
#define TWCR_TWIE                0			 //TWI Interrupt Enable bit

#define TWSR    *((volatile u8*)(0x21))    //TWI Status Register
#define TWSR_TWPS1               1           //TWI Prescaler bits
#define TWSR_TWPS0               0

#define TWAR    *((volatile u8*)(0x22))    //TWI Slave Address Register
#define TWAR_TWGCE               0           //TWI General Call Enable

#define TWDR    *((volatile u8*)(0x23))    //TWI Data Register

#define TWBR    *((volatile u8*)(0x20))    //TWI Bit rate Register

#endif /* TWI_PRIVATE_H_ */
