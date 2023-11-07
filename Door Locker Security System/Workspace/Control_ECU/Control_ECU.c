/******************************************************************************
 *
 * Module: Control ECU
 *
 * File Name: Control_ECU.c
 *
 * Description: Source file for the Control application
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "Control_ECU.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

uint8 tick = 0;

uint8 eeprom_pass[PASSWORD_SIZE]; /*Array in which password will be saved*/

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
 * Receives the two passwords entered from the user and check if they are
 * similar, if they are matched set this password as the system's password
 * and save it in the EEPROM
 */
void SetNewPassword()
{
	uint8 key , i, pass1[PASSWORD_SIZE], pass2[PASSWORD_SIZE], check=0;
	for (i=0 ; i<PASSWORD_SIZE ; i++)
	{
		key = UART_ReceiveByte();
		pass1[i] = key;
		_delay_ms(50);
	}

	for (i=0 ; i<PASSWORD_SIZE ; i++)
	{
		key = UART_ReceiveByte();
		pass2[i] = key;
		_delay_ms(50);
	}

	for (i=0 ; i<PASSWORD_SIZE ; i++)
	{
		if (pass1[i] == pass2[i]){
			check++;
		}
	}
	if (check == 5)
	{
		Save_Password(pass1);
		UART_SendByte(MATCHED);
	}
	else
	{
		UART_SendByte(NOT_MATCHED);
	}
}

/* Description:
 * Compares the entered password with the password saved in the EEPROM
 */
void VerifyPassword()
{
	uint8 key, i, check=0, received_pass[5];

	for (i=0 ; i<PASSWORD_SIZE ; i++)
	{
		key = UART_ReceiveByte();
		received_pass[i] = key;
		_delay_ms(200);
	}

	Check_Saved_Password(eeprom_pass);

	for (i=0 ; i<PASSWORD_SIZE ; i++)
	{
		if (received_pass[i] == eeprom_pass[i])
		{
			check++;
		}
	}
	if (check == 5)
	{
		UART_SendByte(MATCHED);
	}
	else
	{
		UART_SendByte(NOT_MATCHED);
	}
}

/* Description:
 * Saves the system's password in the EEPROM
 */
void Save_Password(uint8* password)
{
	uint8 i;
	for (i=0 ; i<PASSWORD_SIZE ; i++ )
	{
		EEPROM_WriteByte((SLAVE_ADDRESS)+i,password[i]);
		_delay_ms(10);
	}
}

/* Description:
 * Get the password saved in the EEPROM to compare
 */
void Check_Saved_Password(uint8* password)
{
	uint8 i;
	for (i=0 ; i<PASSWORD_SIZE ; i++)
	{
		EEPROM_ReadByte((SLAVE_ADDRESS)+i,&password[i]);
		_delay_ms(10);
	}
}

/* Description:
 * Function to manage the door operations
 */
void Door_Opening()
{

	/* Reset timer and Open the door for 15 seconds */
	tick =0;
	DcMotor_Rotate(CW,100);

	while (tick != 15);

	/* Reset timer and hold the door for 3 seconds */
	tick =0;
	DcMotor_Rotate(STOP,0);

	while (tick != 3);

	/* Reset timer and Close the door for 15 seconds */
	tick =0;
	DcMotor_Rotate(CCW,100);

	while (tick != 15);

	/*Stop the door operation*/
	DcMotor_Rotate(STOP,0);
}

/* Description:
 * Function the enables the buzzer in case password has been entered
 * wrong for 3 consecutive times
 */
void Wrong_Password()
{
	/* Turn on the buzzer for 1 minute */
	Buzzer_ON();

	tick =0; /* Reset timer */

	while (tick != 60);

	Buzzer_OFF();
}
