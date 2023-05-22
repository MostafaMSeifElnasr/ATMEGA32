/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    EXTI                ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

/*configurations*/
#define        INT0_LOW_LEVEL              0
#define        INT0_ON_CHANGE              1
#define        INT0_FALLING_EDGE           2
#define        INT0_RISING_EDGE            3

#define        INT1_LOW_LEVEL              0
#define        INT1_ON_CHANGE              1
#define        INT1_FALLING_EDGE           2
#define        INT1_RISING_EDGE            3

#define        INT2_FALLING_EDGE           0
#define        INT2_RISING_EDGE            1

#define        EXTI_INT0                   0
#define        EXTI_INT1                   1
#define        EXTI_INT2                   2


/*                       Prebuild configuration functions                       */
/********************************************************************************/

void EXTI_voidEnable_INT0pre(void);

/********************************************************************************/

void EXTI_voidEnable_INT1pre(void);

/********************************************************************************/

void EXTI_voidEnable_INT2pre(void);

/*******************************************************************************************************/
/*******************************************************************************************************/

/*                              Run time Functions                              */
/********************************************************************************/
/*available options for Copy_u8INT_ID are : INT0
                                            INT1
                                            INT2

, for Copy_u8Signal are :                   INT0_LOW_LEVEL
											INT0_ON_CHANGE
											INT0_FALLING_EDGE
											INT0_RISING_EDGE

											INT1_LOW_LEVEL
											INT1_ON_CHANGE
											INT1_FALLING_EDGE
											INT1_RISING_EDGE

											INT2_FALLING_EDGE
                                            INT2_RISING_EDGE
                                                                                */
void EXTI_voidEnableInterrupt(u8 Copy_u8INT_ID, u8 Copy_u8Signal);

/********************************************************************************/
void EXTI_voidDisableInterrupt(u8 Copy_u8INT_ID);

/********************************************************************************/
u8 EXTI_voidSetCallBackINT0(void(*Copy_pvToFunc)(void));

/********************************************************************************/
u8 EXTI_voidSetCallBackINT1(void(*Copy_pvToFunc)(void));

/********************************************************************************/
u8 EXTI_voidSetCallBackINT2(void(*Copy_pvToFunc)(void));


#endif
