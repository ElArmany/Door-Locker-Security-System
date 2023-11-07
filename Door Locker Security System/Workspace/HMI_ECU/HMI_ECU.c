/******************************************************************************
 *
 * Module: Human Machine Interface ECU
 *
 * File Name: HMI_APP.c
 *
 * Description: Source file for the Human machine interface application
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "HMI_ECU.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 tick = 0 ;

uint8 receive =0;

/*******************************************************************************
 *                     Functions Definitions                                   *
 *******************************************************************************/

/* Description:
 * The callback function called by the timer driver
 */
void Timer1_Tick()
{
	tick++;
}

/* Description:
 * Function responsible for setting the password for the first time
 * or if the user wanted to change the password
 * Return : status of the two entered passwords either its MATCHED or not
 */
uint8 SetPassword()
{
	uint8 i,key=KEYPAD_NOT_PRESSED;
	for (i=0 ; i<PASSWORD_SIZE ; i++){

		key = KEYPAD_GetPressedKey();
		_delay_ms(300);
		if ((key >=0) && (key <=9)){
			LCD_DisplayCharacter('*');
			UART_SendByte(key);
		}
		else {
			i--; /* To ensure that only numbers will be entered */
		}
	}

	key = KEYPAD_GetPressedKey();

	if (key == '='){
		LCD_ClearScreen();
		LCD_DisplayStringRowColumn(0,0,"Pls Re-Enter the");
		LCD_DisplayStringRowColumn(1,0,"same pass:");
	}
	LCD_MoveCursor(10,1);
	for (i=0 ; i<PASSWORD_SIZE ; i++){
		key = KEYPAD_GetPressedKey();
		_delay_ms(300);
		if ((key >=0) && (key <=9)){
			LCD_DisplayCharacter('*');
			UART_SendByte(key);
		}
		else {
			i--; /* To ensure that only numbers will be entered */
		}
	}

	key=KEYPAD_GetPressedKey();
	if (key == '='){
		receive = UART_ReceiveByte();
		_delay_ms(10);
	}

	return receive ;

}

/* Description:
 * Takes the password from the user and
 * sends it to CONTROL_ECU to check on it
 * Return : status of the entered password either its MATCHED with the saved one or not
 */
uint8 CheckPassword()
{
	uint8 key,i;

	for (i=0 ; i<PASSWORD_SIZE ; i++){
		key = KEYPAD_GetPressedKey();
		_delay_ms(300);
		if ((key >=0) && (key <=9)){
			LCD_DisplayCharacter('*');
			UART_SendByte(key);
			_delay_ms(10);
		}
		else {
			i--; /* To ensure that only numbers will be entered */
		}
	}
	key = KEYPAD_GetPressedKey();
	if (key == '='){
		receive = UART_ReceiveByte();
		_delay_ms(10);
	}
	return receive;
}

/* Description:
 * Displays the state of door opening and closing
 */
void OpenCloseDoor()
{

	LCD_ClearScreen();
	LCD_DisplayStringRowColumn(0,5,"Door is");
	LCD_DisplayStringRowColumn(1,4,"Unlocking !");

	tick=0;
	while (tick != 15);

	tick =0;
	LCD_ClearScreen();
	LCD_DisplayString("****Unlocked****");
	LCD_DisplayStringRowColumn(1,0,"Door is on HOLD");

	while(tick !=3);

	tick =0;
	LCD_ClearScreen();
	LCD_DisplayString("     Door is ");
	LCD_DisplayStringRowColumn(1,5,"Locking !");

	while(tick != 15);

	LCD_ClearScreen();
	LCD_DisplayString("   Door Locked !");
	_delay_ms(2000);
}

/* Description:
 * Function that asks user to enter a new password
 */
void SetPasswordMessage()
{
	LCD_ClearScreen();
	LCD_DisplayString("Pls Enter New");
	LCD_DisplayStringRowColumn(1,0,"Password:");
	LCD_MoveCursor(9,1);
}

/* Description:
 * Function that warns user that the entered password is wrong
 */
void WrongPasswordMessage()
{
	LCD_ClearScreen();
	LCD_DisplayString("WRONG PASSWORD");
	LCD_DisplayStringRowColumn(1,4,"TRY AGAIN");
	_delay_ms(1000); /*Show message for 1 second*/
}

/* Description:
 * Function that asks user to enter the system's password
 */
void EnterPasswordMessage()
{
	LCD_ClearScreen();
	LCD_DisplayString("Pls Enter Pass :");
	LCD_MoveCursor(0,1);
}

/* Description:
 * Function that displays the main menu
 */
void DisplayMainMenu()
{
	LCD_ClearScreen();
	LCD_DisplayString("+ : Open Door");
	LCD_DisplayStringRowColumn(1,0,"- : Change Pass");
}

/* Description:
 * Informs the user that the password has been set successfully
 */
void PasswordSuccessful()
{
	LCD_ClearScreen();
	LCD_DisplayString("Password Set");
	LCD_DisplayStringRowColumn(1,0,"Successfully");
	_delay_ms(1500); /* Show message for 1.5 second */
}

/* Description:
 * Password entered wrong for 3 consecutive times, display an ERROR for 1 minute
 */
void ErrorMessage()
{
	LCD_ClearScreen();
	UART_SendByte(WRONG_PASS);
	LCD_DisplayString("*****ERROR*****");
	tick =0;
	while(tick != 60); /*Display the message for 1 minute*/
}
