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

#define TMR1_PRESCALER            DIV_BY_8

/*timer 0 in compare match mode*/
void Timer0_voidRunTimer0CTCAsync(void(*Copy_pfCompareMatchInterrupt)(void));

/*non inverted PWM signal from timer0*/
void Timer0_voidRunPWMFastNonInverted(void);

/*set OCR0 (B3) value to adjust Duty Cycle (compare match value)*/
void Timer0_voidSetCR0Value(u8 Copy_u8CR0Value);

/*timer 0 overflow mode*/
void TIMER0_voidRunTimer0OFAsync(void(*ptr_pfCompareMatchInterrupt)(void),u8 Copy_u8PreLoad);

/*timer 1 init PWM mode*/
void Timer1_voidInitPWM(void);

/*funtion to set angle of servo (1000 - 2000)*/
void Timer1_voidSetAngle(u16 Copy_u16Angle);

void PWM_voidStartFrequency(u8 channel, u8 frequency); /*mcal*/

//void PWM_voidSetDutyCycle(u8 duty);

void Timer1_voidSetServoAngle(u8 angle);  /*ocr = angle * 10 / 750 */

void Timer1_voidDelay_ms(u8 Time_ms);  /*Sync and Asynch*/

/*initialize timer one ICU*/
void Timer1_voidICUInit(void);

/*Get ICR1 Value*/
u8 Timer1_u8GetICUReading(void);

/*Set ICU Trigger Edge , available options : ICU_RISING_EDGE , ICU_FALLING_EDGE*/
void ICU_voidSetTriggerEdge(u8 Copy_u8Edge);

void ICU_u8SetCallBack(void (*Copy_pvCallBackFunc)(void));

#endif
