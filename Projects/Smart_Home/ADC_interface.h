/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    ADC                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*initialize ADC peripheral*/
void ADC_voidInit(u8 Copy_u8Prescaler);

/*start ADC conversion Asynchronous*/
void ADC_voidStartConversionAsync(u16 * Copy_u8Reading, u8 Copy_u8Channel);

/*Start ADC conversion Synchronous*/
u8 ADC_voidStartConversionSync(u8 Copy_u8Channel);

/*call back function for ISR*/
u8 ADC_voidSetCallBack(void(*Copy_PtrToFunc)(void));

/*Copy_u8Channel options*/
#define CHANNEL0                  0
#define CHANNEL1                  1
#define CHANNEL2                  2
#define CHANNEL3                  3
#define CHANNEL4                  4
#define CHANNEL5                  5
#define CHANNEL6                  6
#define CHANNEL7                  7

/*Copy_u8Prescaler options*/
#define ADC_PRESCALER2            1
#define ADC_PRESCALER4            2
#define ADC_PRESCALER8            3
#define ADC_PRESCALER16           4
#define ADC_PRESCALER32           5
#define ADC_PRESCALER64           6
#define ADC_PRESCALER128          7
#endif
