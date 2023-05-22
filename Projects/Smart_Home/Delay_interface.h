/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    Delay               ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

void Delay_voidSync(u16 Copy_u16Time_ms);

void Delay_voidAsync(u16 Copy_u16Time_ms, void (*CallBackFuncPtr)(void));


#endif
