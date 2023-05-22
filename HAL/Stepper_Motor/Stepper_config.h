/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    Stepper             ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef STEPPER_CONFIG_H_
#define STEPPER_CONFIG_H_

/*preprocessor configuration*/

/*Stepper motor port : DIO_u8PORTA , DIO_u8PORTB , DIO_u8PORTC , DIO_u8PORTD */
#define STEPPER_PORT    DIO_u8PORTA

#define STEPPER_PIN_1   DIO_u8PIN0
#define STEPPER_PIN_2   DIO_u8PIN1
#define STEPPER_PIN_3   DIO_u8PIN2
#define STEPPER_PIN_4   DIO_u8PIN3

/*step of stepper motor / 360 deg*/
#define STEPPER_STEP    0.5

#endif
