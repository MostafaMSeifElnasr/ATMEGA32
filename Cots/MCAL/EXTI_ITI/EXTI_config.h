/*********************************************************/
/*********************************************************/
/************     Author: Mostafa Mahmoud     ************/
/************     Layer:  MCAL                ************/
/************     SWC:    EXTI                ************/
/************     Version:1.00                ************/
/*********************************************************/
/*********************************************************/

#ifndef EXTI_CONFIG_H_
#define EXTI_CONFIG_H_

/*                         Prebuild configuration Macros                        */
/********************************************************************************/

#define EXTI_INT0_SENSE                  EXTI_INT0_FALLINGEDGE

#define EXTI_INT0_LOWLEVEL               0
#define EXTI_INT0_ONCHANGE               1
#define EXTI_INT0_FALLINGEDGE            2
#define EXTI_INT0_RISINGEDGE             3

/********************************************************************************/

#define EXTI_INT1_SENSE                  EXTI_INT1_ONCHANGE

#define EXTI_INT1_LOWLEVEL               0
#define EXTI_INT1_ONCHANGE               1
#define EXTI_INT1_FALLINGEDGE            2
#define EXTI_INT1_RISINGEDGE             3

/********************************************************************************/

#define EXTI_INT2_SENSE                  EXTI_INT2_RISINGEDGE

#define EXTI_INT2_FALLINGEDGE            2
#define EXTI_INT2_RISINGEDGE             3

/********************************************************************************/


#endif
