/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    Stepper             ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef STEPPER_INTERFACE_H_
#define STEPPER_INTERFACE_H_

void Stepper_voidInit(void);

void Stepper_voidRotateCWContinous(void);

void Stepper_voidRotateCCWContinous(void);

void Stepper_voidRotateCWAngle(f32 Copy_u8Angle);

void Stepper_voidRotateCCWAngle(f32 Copy_u8Angle);

void Stepper_voidStop(void);

#endif
