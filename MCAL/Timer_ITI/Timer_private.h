/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    TIMER               ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef TIMER_PRIVATE_H_
#define TIMER_PRIVATE_H_

#define TCCR0             *((volatile u8*)0x53)        /*Timer0 control register*/
#define TCCR0_WGM00       6                            /*Waveform generation mode bit0*/
#define TCCR0_WGM01       3                            /*Waveform generation mode bit1*/
#define TCCR0_CS02        2                            /*Prescaler Bit2*/
#define TCCR0_CS01        1                            /*Prescaler Bit1*/
#define TCCR0_CS00        0                            /*Prescaler Bit0*/
#define TCCR0_COM1        5  //two bits for behavior of OC0 pin
#define TCCR0_COM0        4

#define OCR0              *((volatile u8*)0x5C)        /*Output compare register*/

#define TIMSK             *((volatile u8*)0x59)        /*Timer mask*/
#define TIMSK_OCIE0       1                            /*Output compare 0 interrupt enable*/



#define PRESCALER_MASK       0b11111000
#define DIVIDE_BY_8          0b11111010
#define DIVIDE_BY_64         0b11111011
#define DIVIDE_BY_256        0b00000100

/***************************           timer 1 registers            **************************/

#define TCCR1A             *((volatile u8*)0x4F)        /*Timer1A control register*/
#define TCCR1B             *((volatile u8*)0x4E)        /*Timer1B control register*/

#define ICR1               *((volatile u16*)0x46)
#define OCR1A              *((volatile u16*)0x4A)

/*wave generation mode*/
#define TCCR1A_WGM10        0
#define TCCR1A_WGM11        1

#define TCCR1A_COM1A1       7
#define TCCR1A_COM1A0       6

#define TCCR1B_WGM13        4
#define TCCR1B_WGM12        3
#define TCCR1_CS12          2                            /*Prescaler Bit2*/
#define TCCR1_CS11          1                            /*Prescaler Bit1*/
#define TCCR1_CS10          0                            /*Prescaler Bit0*/

#define TCNT1                *((volatile u16*)0x4c)      /*Timer counter 1 register*/

#define TIFR                 *((volatile u8*)0x58)
#define TIFR_OCF1A           4                           /*timer1 interrupt flag of OCR1A*/

#define TIMSK                *((volatile u8*)0x59)       /*timer1 interrupt enable*/
#define TIMSK_OCIE1A         4

#define PRESCALER_MASK       0b11111000
#define DIVIDE_BY_8          0b00000010
#define DIVIDE_BY_64         0b00000011
#define DIVIDE_BY_256        0b00000100
#define DIVIDE_BY_1024       0b00000101

#define      SREG     *((volatile u8*)0x5F)
#define      SREG_I   7


#endif
