#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "util/delay.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "ADC_interface.h"
#include "CLCD2_interface.h"
#include "TWI_interface.h"
#include "EEPROM_interface.h"
#include "LED_interface.h"
#include "PWM_interface.h"
#include "GIE_interface.h"
#include "Timer_interface.h"
#include "Delay_interface.h"
#include "DC_interface.h"

/******************************************************************/
/*********************** Global variables *************************/
/******************************************************************/
u8 PW_A[5] = "999";

u8 ID_1[5] = "ALY";
u8 PW_1[5] = "111";

u8 ID_2[5];
u8 PW_2[5];

u8 ID_3[5];
u8 PW_3[5];

u8 ID_4[5];
u8 PW_4[5];

u8 ID_5[5];
u8 PW_5[5];


/******************************************************************/
/********************* functions prototypes ***********************/
/******************************************************************/

u8 String_u8CompareLength(u8 * Copy_pu8Str);

u8 String_u8CompareElements(u8 * Copy_pu8Str1, u8 * Copy_pu8Str2);

u8 Check_u8UserID(u8 * Copy_pu8UserID);

u8 Check_u8UserPW(u8 * Copy_pu8UserPW, u8 * Copy_pu8SavedUserPW[]);

void App_voidAdminAddUser(u16 Copy_u16Address, u8 * Copy_u8Str);

void App_voidAdminAddUserPW(u16 Copy_u16Address, u8 * Copy_u8Str);

u8 STR_u8StringToInt(u8 * Str);

void Play_Note(u16 Frequancy,u8 Delay_MilliSec);

/******************************************************************/
/****************************** main ******************************/
/******************************************************************/

int main(void)
{
	/**************  macros  ***************/
/*buzzer tune*/
#define C  	124
#define Db 	235
#define D  	334
#define Eb 	392
#define E  	520
#define F  	607
#define Gb 	685
#define G  	764
#define Ab 	835
#define A  	904
#define Bb 	967
#define B  	1028
#define C1 	1084

#define Try_times      3

	/************** Variables **************/

	u8 Local_u8OperatingMode = 0;          //admin or user *
	u8 Local_u8AdminMode = 0;              // add, modify, delete
	u8 Local_u8EnteredAdminPW[4];          //entered admin PW
	u8 Local_u8Iterator = 0;
	u8 Local_u8PWValidation = 0;           //approve the password
	u8 Local_u8EnteredUserName[4];         //user name entered
	u8 Local_u8UserNameValidation = 0;     //check for entered user name
	u8 Local_u8EnteredUserPW[4];
	u8 Local_u8NewIDNum;
	u8 Local_u8NewIDNumStr;
	u8 Local_u8NewIDStr[5];
	u8 Local_u8NewIDPW[5];
	u8 Local_u8UserIn = 0;
	u16 Reading = 0;

	/********* PINS configurations **********/
	/*LEDs*/
	LED_Init(DIO_u8PORTA, DIO_u8PIN1);
	LED_Init(DIO_u8PORTA, DIO_u8PIN2);

	/*LCD*/
	LCD_voidLCDInit();
	LCD_voidGoTORowCol(0,3);
	LCD_voidSendString("Welcome to");
	LCD_voidGoTORowCol(1,3);
	LCD_voidSendString("Smart Home");

	/*TWI*/
	TWI_voidMasterInitialize(NULL);

	/*OC1A (Servo motor)*/
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN5, DIO_u8PIN_OUTPUT);

	DIO_u8SetPinDirection(DIO_u8PORTA,DIO_u8PIN0, DIO_u8PIN_INPUT);

	/*RX*/
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN0, DIO_u8PIN_INPUT);

	/*TX*/
	DIO_u8SetPinDirection(DIO_u8PORTD, DIO_u8PIN1, DIO_u8PIN_OUTPUT);

	/********** UART Initialization *********/
	USART_voidInit();
	//Local_u8IDComp = Check_u8UserID(&Local_u8IDstr);
	/****************************************/
	/*************** Program ****************/
	/*set admin password in EEPROM*/
	App_voidAdminAddUserPW(15, "999");

	/*Set user 1 name and PW in EEPROM*/
	App_voidAdminAddUser(0, &ID_1);
	App_voidAdminAddUserPW(0, &PW_1);

	/*get user names and passwords from EEPROM*/
	/*get saved PW from EEPROM*/
	EEPROM_voidReceiveStr(145, PW_A, 4);

	EEPROM_voidReceiveStr(0, ID_1, 4);
	EEPROM_voidReceiveStr(5, PW_1, 4);

	EEPROM_voidReceiveStr(10, ID_2, 4);
	EEPROM_voidReceiveStr(15, PW_2, 4);

	EEPROM_voidReceiveStr(20, ID_3, 4);
	EEPROM_voidReceiveStr(25, PW_3, 4);

	EEPROM_voidReceiveStr(30, ID_4, 4);
	EEPROM_voidReceiveStr(35, PW_4, 4);

	EEPROM_voidReceiveStr(40, ID_5, 4);
	EEPROM_voidReceiveStr(45, PW_5, 4);

	/*Ask Admin or User mode*/
	USART_voidSendString("\r\nfor Admin mode, enter 1\r\nfor user mode, enter 2 : \r\n");
	USART_voidReceiveString(&Local_u8OperatingMode);
	if(Local_u8OperatingMode == '1')         //Admin mode (check for password)
	{
		/*check for the password*/
		Local_u8Iterator = 0;
		while(Local_u8Iterator < Try_times)
		{
			/*Ask for password*/

			LCD_voidClearScreen();
			LCD_voidGoTORowCol(0,0);
			LCD_voidSendString("Entr Admn PW:");
			USART_voidSendString("\r\nEnter Admin Password : \r\n");

			USART_voidReceiveString(Local_u8EnteredAdminPW);

			Local_u8PWValidation = String_u8CompareElements(Local_u8EnteredAdminPW, PW_A);

			if(Local_u8PWValidation == 1)  //right PW
			{
				USART_voidSendString("\r\nValid PW! \r\n");
				LCD_voidClearScreen();
				LCD_voidGoTORowCol(0,0);
				LCD_voidSendString("Valid PW!");
				Local_u8PWValidation = 11;
				break;
			}
			else
			{
				USART_voidSendString("\r\nWrong Password! Try again  ");
				LCD_voidClearScreen();
				LCD_voidGoTORowCol(0,0);
				LCD_voidSendString("Invalid PW!");
				Local_u8Iterator++;
			}
		}
	}
	//
	else if(Local_u8OperatingMode == '2')    //user mode (check for user name and password)
	{
		u8 Local_u8Iterator = 0;
		while(Local_u8Iterator < 3)
		{
			USART_voidSendString("\r\n      Enter your User name : \r\n");
			USART_voidReceiveString(Local_u8EnteredUserName);
			LCD_voidClearScreen();
			LCD_voidGoTORowCol(0,0);
			LCD_voidSendString("Entr Usr Name:");
			LCD_voidGoTORowCol(1,0);
			LCD_voidSendString(Local_u8EnteredUserName);

			if(String_u8CompareElements(Local_u8EnteredUserName, ID_1))
			{
				Local_u8UserNameValidation = 1;   //first user
				break;
			}
			else if(String_u8CompareElements(Local_u8EnteredUserName, ID_2))
			{
				Local_u8UserNameValidation = 2;   //second user
				break;
			}
			else if(String_u8CompareElements(Local_u8EnteredUserName, ID_3))
			{
				Local_u8UserNameValidation = 3;   //third user
				break;
			}
			else if(String_u8CompareElements(Local_u8EnteredUserName, ID_4))
			{
				Local_u8UserNameValidation = 4;   //fourth user
				break;
			}
			else if(String_u8CompareElements(Local_u8EnteredUserName, ID_5))
			{
				Local_u8UserNameValidation = 5;   //fifth user
				break;
			}
			else
			{
				Local_u8UserNameValidation = 0;   //invalid user
				Local_u8Iterator++;
				USART_voidSendString("   Wrong ID, Try again: \r\n");
				LCD_voidClearScreen();
				LCD_voidGoTORowCol(0,0);
				LCD_voidSendString("Invalid ID!");
			}
		}
		switch(Local_u8UserNameValidation)
		{
		case 0:
			USART_voidSendString("\r\nInvalid ID, System Locked !");
			LCD_voidClearScreen();
			LCD_voidGoTORowCol(0,0);
			LCD_voidSendString("SYS locked!");
			break;   //no ID matches Users for 3 times

		case 1:       //first user, check for password
			USART_voidSendString("\r\n Hello\r\n");
			LCD_voidGoTORowCol(0,6);
			LCD_voidClearScreen();
			LCD_voidSendString("HELLO");
			Local_u8PWValidation = Check_u8UserPW(Local_u8EnteredUserPW, PW_1);
			break;

		case 2:       //second user, check for password
			USART_voidSendString("\r\n Hello\r\n");
			LCD_voidGoTORowCol(0,6);
			LCD_voidClearScreen();
			LCD_voidSendString("HELLO");
			Local_u8PWValidation = Check_u8UserPW(Local_u8EnteredUserPW, PW_2);
			break;

		case 3:       //third user, check for password
			USART_voidSendString("\r\n Hello\r\n");
			LCD_voidGoTORowCol(0,6);
			LCD_voidClearScreen();
			LCD_voidSendString("HELLO");
			Local_u8PWValidation = Check_u8UserPW(Local_u8EnteredUserPW, PW_3);
			break;

		case 4:       //fourth user, check for password
			USART_voidSendString("\r\n Hello\r\n");
			LCD_voidGoTORowCol(0,6);
			LCD_voidClearScreen();
			LCD_voidSendString("HELLO");
			Local_u8PWValidation = Check_u8UserPW(Local_u8EnteredUserPW, PW_4);
			break;

		case 5:       //fifth user, check for password
			USART_voidSendString("\r\n Hello\r\n");
			LCD_voidGoTORowCol(0,6);
			LCD_voidClearScreen();
			LCD_voidSendString("HELLO");
			Local_u8PWValidation = Check_u8UserPW(Local_u8EnteredUserPW, PW_5);
			break;
		}
	}
	else
	{
		USART_voidSendString("Invalid mode number");
		LCD_voidClearScreen();
		LCD_voidGoTORowCol(0,0);
		LCD_voidSendString("Invlid MD no!");
		//system should be restarted
	}

	if(Local_u8PWValidation == 11)   //password approved, start admin mode or User mode
	{
		/*program functionality*/
		while(1)
		{
			if(Local_u8OperatingMode == '1')         //Admin mode
			{
				LCD_voidGoTORowCol(0,3);
				LCD_voidClearScreen();
				LCD_voidSendString("Admin mode");
				/*Admin mode "add, modify, delete users"*/
				USART_voidSendString("\r\nTo add new user or modify, enter 1\r\n"
						"To delete an old user, enter 2\r\nTo terminate, enter 3 :\r\n ");
				USART_voidReceiveString(&Local_u8AdminMode);
				LCD_voidGoTORowCol(1,0);
				LCD_voidSendString(Local_u8AdminMode);

				if(Local_u8AdminMode == '1')          //add new user
				{
					/*Get location of storing the new user*/
					USART_voidSendString("\r\nEnter the user ID from 1 to 5 : \r\n");
					USART_voidReceiveString(&Local_u8NewIDNumStr);
					LCD_voidClearScreen();
					LCD_voidGoTORowCol(0,0);
					LCD_voidSendString("Admin mode");
					LCD_voidGoTORowCol(1,0);
					LCD_voidSendString(Local_u8NewIDNumStr);
					Local_u8NewIDNum = STR_u8StringToInt(&Local_u8NewIDNumStr);

					if((Local_u8NewIDNum > 0) && (Local_u8NewIDNum <= 5))
					{
						/*New ID name*/
						USART_voidSendString("\r\nEnter the new user name : \r\n");
						USART_voidReceiveString(&Local_u8NewIDStr);
						LCD_voidGoTORowCol(1,0);
						LCD_voidSendString(Local_u8NewIDStr);

						/*New ID PW*/
						USART_voidSendString("\r\nEnter the new user name's PW : \r\n");
						USART_voidReceiveString(&Local_u8NewIDPW);
						LCD_voidGoTORowCol(1,0);
						LCD_voidSendString(Local_u8NewIDPW);

						App_voidAdminAddUser(Local_u8NewIDNum, &Local_u8NewIDStr);
						USART_voidSendString("\r\n\r\n    user name added \r\n");
						LCD_voidGoTORowCol(1,0);
						LCD_voidSendString("User+");

						App_voidAdminAddUserPW(Local_u8NewIDNum, &Local_u8NewIDPW);
						USART_voidSendString("\r\n     password added \r\n");
						LCD_voidGoTORowCol(1,9);
						LCD_voidSendString("PW+");
					}
					/*loop inside admin mode*/
				}
				else if(Local_u8AdminMode == '2')     //delete old user
				{
					/*Get location of the user to be deleted*/
					USART_voidSendString("\r\nEnter the user ID to delete from 1 to 5 : \r\n");
					USART_voidReceiveString(&Local_u8NewIDNumStr);
					Local_u8NewIDNum = STR_u8StringToInt(&Local_u8NewIDNumStr);
					LCD_voidGoTORowCol(1,0);
					LCD_voidSendString(Local_u8NewIDNumStr);

					/*give the required address a name (aaa)*/
					App_voidAdminAddUser(Local_u8NewIDNum, "aaa");

					/*assign the password to 000*/
					App_voidAdminAddUserPW(Local_u8NewIDNum, "000");

					USART_voidSendString("\r\nUser name was deleted successfully\r\n");
					LCD_voidGoTORowCol(1,0);
					LCD_voidSendString("User-");
				}
				else if(Local_u8AdminMode == '3')     //terminate
				{
					USART_voidSendString("\r\nSystem terminated!\r\n");
					LCD_voidClearScreen();
					LCD_voidGoTORowCol(1,0);
					LCD_voidSendString("SYS OFF");
					return 0;
				}
				else
				{
					USART_voidSendString("\r\nInvalid mode number!\r\n");
					LCD_voidClearScreen();
					LCD_voidGoTORowCol(0,0);
					LCD_voidSendString("Invlid MD no!");
					//return 0;               //system should be restarted
				}
			}

			/*USER mode*/
			else if(Local_u8OperatingMode == '2')
			{
				Local_u8UserIn = 1;
				USART_voidSendString("\r\nWelcome Home!\r\n");
				LCD_voidGoTORowCol(1,1);
				LCD_voidClearScreen();
				LCD_voidSendString("WELCOME HOME");
				/*Servo rotates by 90 degrees*/
				PWM_voidSetDutyCycleRange0_180(90, FREQUENCY_250);
				PWM_voidProducePWM(CHANNEL_A, FREQUENCY_250);

				/*LED ON*/
				LED_ON(DIO_u8PORTA, DIO_u8PIN1);

				/*buzzer*/
				Play_Note(500,250);
				Play_Note(700,250);
				Play_Note(800,250);
				Play_Note(1000,250);


				ADC_voidInit(ADC_PRESCALER128);
				while(Local_u8UserIn == 1) //system stuck in user mode
				{
					/*fan*/
					Reading = ADC_voidStartConversionSync(CHANNEL0);
					Reading = (Reading * (5000 /256) / 10);
					if(Reading > 28)
					{
						DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_HIGH);
					}
					else
					{
						DIO_u8SetPinValue(DIO_u8PORTA, DIO_u8PIN2, DIO_u8PIN_LOW);
					}
					LCD_voidGoTORowCol(1,0);
					LCD_voidSendVariable(Reading);

					_delay_ms(100);
				}
			}
		}
	}

	else    //wrong Admin password
	{
		USART_voidSendString("\r\nInvalid PW, System Locked !");
		return 0;
	}
}
/******************************************************************/
/******************* functions Implementation *********************/
/******************************************************************/

u8 String_u8CompareLength(u8 * Copy_pu8Str)
{
	u8 Local_u8Iterator = 0;

	while(Copy_pu8Str[Local_u8Iterator] != '\0')
	{
		Local_u8Iterator++;
	}

	return Local_u8Iterator;
}

u8 String_u8CompareElements(u8 * Copy_pu8Str1, u8 * Copy_pu8Str2)
{
	u8 Local_u8Iterator;
	if (String_u8CompareLength(Copy_pu8Str1) != String_u8CompareLength(Copy_pu8Str2))
	{
		return 0;
	}
	else
	{
		for (Local_u8Iterator=0;Copy_pu8Str1[Local_u8Iterator]!='\0';Local_u8Iterator++)
		{
			if (Copy_pu8Str1[Local_u8Iterator] != Copy_pu8Str2[Local_u8Iterator])
				return 0;
		}
		return 1;
	}
}

u8 Check_u8UserID(u8 * Copy_pu8UserID)
{
	u8 Local_u8Iterator = 0;
	while(Local_u8Iterator < 3)
	{
		USART_voidSendString("\r\nPlease Enter your ID : ");
		USART_voidReceiveString(Copy_pu8UserID);

		if(String_u8CompareElements(ID_1, Copy_pu8UserID))
		{
			return 1;   //first user
		}
		else if(String_u8CompareElements(ID_2, Copy_pu8UserID))
		{
			return 2;   //second user
		}
		else if(String_u8CompareElements(ID_3, Copy_pu8UserID))
		{
			return 3;   //third user
		}
		else
		{
			Local_u8Iterator++;
			USART_voidSendString("   Wrong ID, Try again\r\n");
		}
	}
	USART_voidSendString("\r\nInvalid ID, System Locked !");
	return 0;   //no ID matches Users for 3 times
}

u8 Check_u8UserPW(u8 * Copy_pu8UserPW, u8 * Copy_pu8SavedUserPW[])
{
	u8 Local_u8Iterator = 0;
	while(Local_u8Iterator < 3)
	{
		USART_voidSendString("\r\nEnter Your Password : ");
		USART_voidReceiveString(Copy_pu8UserPW);

		if(String_u8CompareElements(Copy_pu8UserPW, Copy_pu8SavedUserPW))
		{
			return 11;
		}
		else
		{
			Local_u8Iterator++;
			USART_voidSendString("   Wrong PW, Try again\r\n");
		}
	}
	USART_voidSendString("\r\nInvalid PW, System Locked !");
	return 0;   //no PW matches Users for 3 times
}

//void Application(void)
//{
//	/*Close the door (Servo -> 0 deg)*/
//	PWM_voidSetDutyCycleRange0_180(0, FREQUENCY_250);
//	PWM_voidProducePWM(CHANNEL_A, FREQUENCY_250);
//}

void App_voidAdminAddUser(u16 Copy_u16Address, u8 * Copy_u8Str)
{
	/*mapping address to eeprom address (1->0) (2->10) (3->20)*/
	Copy_u16Address = (Copy_u16Address - 1) *10;

	/*write the string to the required address*/
	EEPROM_voidSendString(Copy_u16Address, Copy_u8Str);
}

void App_voidAdminAddUserPW(u16 Copy_u16Address, u8 * Copy_u8Str)
{
	/*mapping address to eeprom address (1->5) (2->15) (3->25)*/
	Copy_u16Address = ((Copy_u16Address - 1) *10) + 5;

	/*write the string to the required address*/
	EEPROM_voidSendString(Copy_u16Address, Copy_u8Str);
}

u8 STR_u8StringToInt(u8 * Str)
{
	u8 i = 0;
	u8 n = 0;
	for(i=0;Str[i] != '\0';i++)
	{
		if(Str[i]>='0' && Str[i]<='9')
		{
			n=n*10+(Str[i]-'0');
		}
	}
	return n;
}

void Play_Note(u16 Frequancy,u8 Delay_MilliSec)
{
	for(int i=0; i<Delay_MilliSec ; i++)
	{
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_HIGH);
		_delay_us(Frequancy);
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN3,DIO_u8PIN_LOW);
		_delay_us(Frequancy);
	}
}
