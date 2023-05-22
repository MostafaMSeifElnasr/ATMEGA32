/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    WDT                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_


#define SLEEP_TIME_1SEC       6

void WDT_voidEnable(void);

void WDT_SetSleepTime(u8 Copy_u8SleepTime);

void WDT_voidDisable(void);

#endif /* WDT_INTERFACE_H_ */
