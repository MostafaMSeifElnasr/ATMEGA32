/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    KPD                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_PORT     DIO_u8PORTA

#define KPD_COL0	 DIO_u8PIN0
#define KPD_COL1	 DIO_u8PIN1
#define KPD_COL2	 DIO_u8PIN2
#define KPD_COL3     DIO_u8PIN3

#define KPD_ROW0     DIO_u8PIN4
#define KPD_ROW1     DIO_u8PIN5
#define KPD_ROW2     DIO_u8PIN6
#define KPD_ROW3     DIO_u8PIN7

#define COL_NUM      4
#define ROW_NUM      4

#define KPD_NO_PRESSED_KEY    1


#define KPD_VALUES  {{'a', 'b' , 'c' , 'd'} , {'e', 'f' , 'g' , 'h'},{'i', 'j' , 'k' , 'l'},{'m', 'n' , 'o' , 'p'}}


#endif
