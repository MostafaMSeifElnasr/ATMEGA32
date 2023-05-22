/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    ADC                 ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/**********************       Preprocessor configuration        *************************/
/****************************************************************************************/




/************************        Run time configuration         **************************/
/*****************************************************************************************/
#define ADMUX_MASK                0b11100000
#define PRESCALERMASK             0b11111000

#define ADMUX                     *((volatile u8*)(0x27))
#define ADMUX_REFS0               6          /*voltage reference selection*/
#define ADMUX_REFS1               7
#define ADMUX_ADLAR               5          /*1 : left adjustment for bits for 8bit mode*/
#define ADMUX_MUX0                0
#define ADMUX_MUX1                1
#define ADMUX_MUX2                2
#define ADMUX_MUX3                3
#define ADMUX_MUX4                4

#define ADCSRA                    *((volatile u8*)(0x26))
#define ADCSRA_ADEN               7          /*ADC Enable*/
#define ADCSRA_ADSC               6          /*start conversion*/
#define ADCSRA_ADATE              5          /*start conversion auto triggered by ext interrupt*/
#define ADCSRA_ADIF               4          /*ADC interrupt flag*/
#define ADCSRA_ADIE               3          /*ADC interrupt Enable*/
#define ADCSRA_ADPS2              2
#define ADCSRA_ADPS1              1
#define ADCSRA_ADPS0              0

#define ADCH                      *((volatile u8 *)(0x25))      //ADC high register
#define ADCL                      *((volatile u8 *)(0x24))      //ADC low register

#define SFIOR                     *((volatile u8 *)(0x50))      //ADC special function IO register
#define ADCR                      *((volatile u16*)(0x24))      //ADC data register for 10 bit resolution

#define CHANNEL0                  0
#define CHANNEL1                  1
#define CHANNEL2                  2
#define CHANNEL3                  3
#define CHANNEL4                  4
#define CHANNEL5                  5
#define CHANNEL6                  6
#define CHANNEL7                  7

#define ADC_PRESCALER2            1
#define ADC_PRESCALER4            2
#define ADC_PRESCALER8            3
#define ADC_PRESCALER16           4
#define ADC_PRESCALER32           5
#define ADC_PRESCALER64           6
#define ADC_PRESCALER128          7

#define EIGHT_bit_mode            1
#define TEN_bit_mode              2

#endif
