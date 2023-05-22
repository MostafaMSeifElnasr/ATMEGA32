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

void PWM_voidProducePWM(u8 Copy_u8Channel, u16 Copy_u16Frequency);

/*function to set compare match value*/
void PWM_voidSetDutyCycle(u8 Copy_u8DutyCycle, u16 Copy_u16Frequency);

/*Set Servo angle (compare match value) with mapping from (0-100) to (0-180)*/
void PWM_voidSetDutyCycleRange0_180(u16 Copy_u8DutyCycle, u16 Copy_u16Frequency);


#define FREQUENCY_1000                   1000
#define FREQUENCY_500                    2000
#define FREQUENCY_400                    2500
#define FREQUENCY_250                    4000
#define FREQUENCY_200                    5000
#define FREQUENCY_100                    10000
#define FREQUENCY_50                     20000
#define FREQUENCY_40                     25000
#define FREQUENCY_25                     40000
#define FREQUENCY_20                     50000

#define CHANNEL_A            1
#define CHANNEL_B            2

#endif
