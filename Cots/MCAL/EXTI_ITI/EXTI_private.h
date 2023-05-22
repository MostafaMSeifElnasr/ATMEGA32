/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    EXTI                ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_

/*SIE : Specific Interrupt Enable*/
#define        GICR                   *((volatile u8*)0x5B)
#define        GICR_INT1              7
#define        GICR_INT0              6
#define        GICR_INT2              5

/*Interrupt flag*/
#define        GIFR                   *((volatile u8*)0x5A)

/*sense signal for INT0, INT1*/
#define        MCUCR                  *((volatile u8*)0x55)
#define        MCUCR_ISC00            0
#define        MCUCR_ISC01            1
#define        MCUCR_ISC10            2
#define        MCUCR_ISC11            3

/*Sense signal for INT2*/
#define        MCUCSR                 *((volatile u8*)0x54)
#define        MCUCSR_ISC2            6

/*configurations*/
#define        INT0_LOW_LEVEL         0
#define        INT0_ON_CHANGE         1
#define        INT0_FALLING_EDGE      2
#define        INT0_RISING_EDGE       3

#define        INT1_LOW_LEVEL         0
#define        INT1_ON_CHANGE         1
#define        INT1_FALLING_EDGE      2
#define        INT1_RISING_EDGE       3

#define        INT2_FALLING_EDGE      0
#define        INT2_RISING_EDGE       1

#define        EXTI_INT0              0
#define        EXTI_INT1              1
#define        EXTI_INT2              2

#endif
