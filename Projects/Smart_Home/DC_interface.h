/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  HAL                 ************/
/************     SWC:    DC_motor            ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef DC_INTERFACE_H_
#define DC_INTERFACE_H_

/*prebuild configuration*/

void DC_MotorInit(void);

void DC_MotorCWContinous(void);

void DC_MotorCCWContinous(void);

void DC_MotorStop(void);

#endif
