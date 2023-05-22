/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    TIMER               ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define TMR0_PRESCALER_8          2

/*timer 0 in compare match mode*/
void Timer0_voidRunTimer0CTCAsync(void(*Copy_pfCompareMatchInterrupt)(void));



#endif
