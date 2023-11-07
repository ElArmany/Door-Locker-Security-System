 /******************************************************************************
 *
 * Module: Human Machine Interface ECU
 *
 * File Name: HMI_ECU.h
 *
 * Description: Header file for the Human machine interface application
 *
 * Author: Abdelrahman Tarek
 *
 *******************************************************************************/

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include "uart.h"
#include "avr/io.h"
#include <util/delay.h>


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASSWORD_SIZE 5

#define FIRST_TIME_PASSWORD 10
#define CHANGE_PASSWORD 20
#define PASSWORD_CHECK 30
#define OPEN_DOOR 40
#define WRONG_PASS 50

#define MATCHED 1
#define NOT_MATCHED 0

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description:
 * The callback function called by the timer driver
 */
void Timer1_Tick();

/* Description:
 * Function responsible for setting the password for the first time
 * or if the user wanted to change the password
 * Return : status of the two entered passwords either its MATCHED or not
 */
uint8 SetPassword();

/* Description:
 * Takes the password from the user and
 * sends it to CONTROL_ECU to check on it
 * Return : status of the entered password either its MATCHED with the saved one or not
 */
uint8 CheckPassword();

/* Description:
 * Displays the state of door opening and closing
 */
void OpenCloseDoor();

/* Description:
 * Function that asks user to enter a new password
 */
void SetPasswordMessage();

/* Description:
 * Function that warns user that the entered password is wrong
 */
void WrongPasswordMessage();

/* Description:
 * Function that asks user to enter the system's password
 */
void EnterPasswordMessage();

/* Description:
 * Function that displays the main menu
 */
void DisplayMainMenu();

/* Description:
 * Informs the user that the password has been set successfully
 */
void PasswordSuccessful();

/* Description:
 * Password entered wrong for 3 consecutive times, display an ERROR for 1 minute
 */
void ErrorMessage();

#endif /* HMI_ECU_H_ */
