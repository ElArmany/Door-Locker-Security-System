/******************************************************************************
 *
 * Module: Human Machine Interface ECU
 *
 * File Name: HMI_main.c
 *
 * Description: Main file for the Human machine interface application
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "HMI_ECU.h"

/*******************************************************************************
 *                            Main Function                                 *
 *******************************************************************************/

int main()
{
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	uint8 received_byte, key;

	/* UART Configurations:
	 * 8-bit Mode
	 * Parity Check is Disabled
	 * One Stop Bit
	 * Baudrate = 9600 bps
	 */
	UART_ConfigType UART_Configuartions = {EIGHT_BIT,NO_PARITY,ONE_STOP_BIT,9600};

	/* Timer1 Configurations:
	 * Initial Value = 0
	 * Compare Value = 31249
	 * Prescaler = 256
	 * Mode : Compare Mode
	 */
	Timer1_ConfigType Timer1_Configurations = {0,31249,PRESCALER_256,COMPARE_MODE};

	/*Initialize the LCD*/
	LCD_init();
	/*Initialize UART driver with the required configurations*/
	UART_init(&UART_Configuartions);
	/*Initialize Timer driver with the required configurations*/
	Timer1_init(&Timer1_Configurations);
	/* set the TIMER1_ticks to be the callback function */
	Timer1_setCallBack(Timer1_Tick);

	while(1){
		while(1){
			/*------------------Step 1-----------------*/
			SetPasswordMessage();
			/*Sending a command to the Control_ECU to set a first time password*/
			UART_SendByte(FIRST_TIME_PASSWORD);
			/*Call the functions used to give a password to the system and save it*/
			received_byte = SetPassword();

			if (received_byte == MATCHED)
			{
				/*If the two entered passwords are matched jump to Step 2*/
				PasswordSuccessful();
				break;
			}
			else if (received_byte == NOT_MATCHED)
			{
				/*The two passwords don't match, ask user to try again*/
				WrongPasswordMessage();
				SetPasswordMessage();
				UART_SendByte(FIRST_TIME_PASSWORD);
				received_byte = SetPassword();
				if (received_byte == MATCHED)
				{
					/*If the two entered passwords are matched jump to Step 2*/
					PasswordSuccessful();
					break;
				}
				else if (received_byte == NOT_MATCHED)
				{
					/*The two passwords don't match, ask user to try again*/
					WrongPasswordMessage();
					SetPasswordMessage();
					UART_SendByte(FIRST_TIME_PASSWORD);
					received_byte = SetPassword();
					if (received_byte == MATCHED)
					{
						/*If the two entered passwords are matched jump to Step 2*/
						PasswordSuccessful();
						break;
					}
					else
					{
						/*Password entered wrong for 3 consecutive times, display ERROR and enable Buzzer*/
						ErrorMessage();
					}
				}
			}
		}

		while(1)
		{
			/*------------------Step 2-----------------*/

			/*Display Main Menu*/
			DisplayMainMenu();

			key = KEYPAD_GetPressedKey();
			_delay_ms(500);

			if (key == '+') /*User chooses to open the door*/
			{
				/*------------------Step 3-----------------*/
				EnterPasswordMessage();
				/*Send a command to the Control_ECU to verify the password entered with the saved password*/
				UART_SendByte(PASSWORD_CHECK);
				received_byte = CheckPassword();
				if(received_byte== MATCHED)
				{
					/*If the two passwords are matched send a command to the Control_ECU to open the door*/
					UART_SendByte(OPEN_DOOR);
					OpenCloseDoor();
				}
				else if (received_byte == NOT_MATCHED)
				{
					/*If the password doesn't match ask the user to enter password again for the second time*/
					WrongPasswordMessage();
					EnterPasswordMessage();
					UART_SendByte(PASSWORD_CHECK);
					received_byte = CheckPassword();
					if (received_byte == MATCHED)
					{
						/*If the two passwords are matched send a command to the Control_ECU to open the door*/
						UART_SendByte(OPEN_DOOR);
						OpenCloseDoor();
					}
					else if (received_byte == NOT_MATCHED)
					{
						/*If the password doesn't match ask the user to enter password again for the last time*/
						WrongPasswordMessage();
						EnterPasswordMessage();
						UART_SendByte(PASSWORD_CHECK);
						received_byte = CheckPassword();
						if (received_byte == MATCHED)
						{
							/*If the two passwords are matched send a command to the Control_ECU to open the door*/
							UART_SendByte(OPEN_DOOR);
							OpenCloseDoor();
						}
						else
						{
							/*Password entered wrong for 3 consecutive times, display ERROR and enable Buzzer for 1 minute*/
							ErrorMessage();
						}
					}
				}
			}
			else if (key == '-') /*User chooses to change the password*/
			{
				/*------------------Step 4-----------------*/
				/*Ask user to enter the old password*/
				EnterPasswordMessage();
				/*Send a command to Control_ECU to verify the password*/
				UART_SendByte(PASSWORD_CHECK);
				received_byte = CheckPassword();
				if (received_byte == MATCHED)
				{
					/*Return to step 1 again and ask the user to enter the new password*/
					break;
				}
				else if (received_byte == NOT_MATCHED)
				{
					/*If the entered password doesn't match the saved one ask the user to enter the password again*/
					WrongPasswordMessage();
					EnterPasswordMessage();
					UART_SendByte(PASSWORD_CHECK);
					received_byte = CheckPassword();
					if (received_byte == MATCHED)
					{
						/*Return to step 1 again and ask the user to enter the new password*/
						break;
					}
					else if (received_byte == NOT_MATCHED)
					{
						/*If the entered password doesn't match the saved one ask the user to enter the password again*/
						WrongPasswordMessage();
						EnterPasswordMessage();
						UART_SendByte(PASSWORD_CHECK);
						received_byte = CheckPassword();
						if (received_byte == MATCHED){
							/*Return to step 1 again and ask the user to enter the new password*/
							break;
						}
						else if (received_byte == NOT_MATCHED)
						{
							/*Password entered wrong for 3 consecutive times, display ERROR and enable Buzzer for 1 minute*/
							ErrorMessage();
						}
					}
				}
			}
		}
	}
}

