/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    SSD                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef SSD_INTERFACE_H_
#define SSD_INTERFACE_H_

#define  SSD_u8COMM_ANODE      0
#define  SSD_u8COMM_CATHODE    1



typedef struct
{
	u8 SSD_Port;
	u8 SSD_ENPort;
	u8 SSD_ENPin;
	u8 SSD_CommType;
}SSD_t;

void SSD_u8SetNumber(u8 Copy_u8Number, SSD_t* SSD);

void SSD_voidEnable(SSD_t* SSD);

void SSD_voidDisable(SSD_t* SSD);


#endif
