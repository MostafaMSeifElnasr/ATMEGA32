/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    KPD                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

/*This function shall initialize the KPD*/
void KPD_voidInit(void);

/*This function shall return the value of any pressed key*/
u8 KPD_u8GetPressedKey(void);

#endif
