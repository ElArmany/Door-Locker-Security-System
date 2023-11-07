/******************************************************************************
 *
 * Module: Control Main Function
 *
 * File Name: Control_main.c
 *
 * Description: Main file for the control application
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#include "Control_ECU.h"

/*******************************************************************************
 *                            Main Function                                 *
 *******************************************************************************/

int main()
{
	/* Enable Global Interrupt I-Bit */
	SREG |= (1<<7);

	uint8 command;

	/* UART Configurations:
	 * 8-bit Mode
	 * Parity Check is Disabled
	 * One Stop Bit
	 * Baudrate = 9600 bps
	 */
	UART_ConfigType UART_Configuraions2 = {EIGHT_BIT,NO_PARITY,ONE_STOP_BIT,9600};

	/* Timer1 Configurations:
	 * Initial Value = 0
	 * Compare Value = 31249
	 * Prescaler = 256
	 * Mode : Compare Mode
	 */
	Timer1_ConfigType Timer1_Configurations2 = {0,31249,PRESCALER_256,COMPARE_MODE};

	/* I2C Configurations:
	 * Slave address of the TWI unit = 0x02
	 * Communication Speed = 400 kbit/s
	 */
	TWI_ConfigType TWI_Configurations = {0x02,400000};

	/*Initialize UART driver with the required configurations*/
	UART_init(&UART_Configuraions2);
	/*Initialize Timer driver with the required configurations*/
	Timer1_init(&Timer1_Configurations2);
	/*Initialize I2C driver with the required configurations*/
	TWI_init(&TWI_Configurations);
	/*Initialize The DC Motor*/
	DcMotor_Init();
	/*Initialize the Buzzer*/
	Buzzer_init();
	/* set the TIMER1_ticks to be the callback function */
	Timer1_setCallBack(Timer1_Tick);

	while(1){
		/* Receive a command from HMI_ECU to take a specific action */
		command = UART_ReceiveByte();

		switch(command){
		case FIRST_TIME_PASSWORD:
			/* The user needs to enter the password for the first time */
			SetNewPassword();
			break;
		case PASSWORD_CHECK:
			/* The user needs to verify the password to open the door or change password */
			VerifyPassword();
			break;
		case OPEN_DOOR:
			/* The user need to open the door */
			Door_Opening();
			break;
		case WRONG_PASS:
			/* The user entered the password wrong 3 consecutive times, Enable ALARM mode */
			Wrong_Password();
			break;
		case CHANGE_PASSWORD:
			/* The user needs to change the password */
			SetNewPassword();
			break;
		}

	}

}
